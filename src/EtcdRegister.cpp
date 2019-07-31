/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   EtcdRegister.cpp
 * Author: lehaisonmath6
 * 
 * Created on June 18, 2019, 2:42 PM
 */

#include "EtcdRegister.h"

#include "etcd/Client.hpp"
#include "Poco/URI.h"
#include "Poco/Path.h"
#include "Poco/StringTokenizer.h"
#include "Poco/NumberParser.h"
#include <Poco/Format.h>

#include <iostream>
#include <set>
#include <pplx/pplxtasks.h>
using namespace std;

EtcdRegister::EtcdRegister(const std::string& aEtcdHosts,const std::string& aEtcdTotalHostsKey) 
: _started(false)
,_etcdHosts(aEtcdHosts)
,_etcdTotalHosts()
,_etcdTotalHostsKey(aEtcdTotalHostsKey)
{
    
}


EtcdRegister::~EtcdRegister() {
    stop();
    delete _etcdClient;
}

void EtcdRegister::addService(const std::string& path, const std::string& host, const int port,const std::string& schema)
{
  
    _totalServices.push_back(ServiceEtcdInfo(path,host,port,schema));
 
    if(!_started)
    {
        return;
    }
    else
    {
        addUsingCurrentSession(ServiceEtcdInfo(path,host,port,schema));
    }
}

bool EtcdRegister::addUsingCurrentSession(const ServiceEtcdInfo& aService)
{
    try
    {
       
        Poco::URI uri;
        uri.setScheme(aService.schema);
        uri.setHost(aService.host);
        uri.setPort(aService.port);
        
        
        std::string svr_name = Poco::format("%s:%s:%d",aService.schema,aService.host,aService.port);

        Poco::Path regPath(aService.path);
        regPath.append(svr_name);
        
        const std::string key = regPath.toString();
        const std::string value = uri.toString();
        std::cout<<"Add service key : "<< key << " value : "<<value<<std::endl;
           
        etcd::Response res = _etcdClient->set(key,value).get();
        if(res.error_code() == 0) 
            return true;
        else 
            return false;
        return true;
    }
    catch(...)
    {
        return false;
    }
   
}

void EtcdRegister::registerAll()
{
    for(size_t i = 0 ;i< _totalServices.size();i++)
        _totalServices[i].added = this->addUsingCurrentSession(_totalServices[i]);
}

void EtcdRegister::start()
{
    if(_started) return;

    this->initConnection();
    registerAll();
    _started = true;
    mergeEtcdFarm();
}

void EtcdRegister::mergeEtcdFarm() 
{
    
}

void EtcdRegister::stop()
{
    if (!_started) return;
    this->initConnection();
    this->unRegisterAll();
    _started = false;
}

void EtcdRegister::initConnection()
{
     
 
    if(_etcdTotalHosts.length()==0) _etcdTotalHosts = _etcdHosts;
    if(_etcdTotalHosts.length()==0) return;
   
    _etcdClient = new etcd::Client(_etcdHosts);
}


void EtcdRegister::unRegisterAll()
{
    for(size_t i= 0 ;i < _totalServices.size() ; i++)
    {
        if(_totalServices[i].added)
            _totalServices[i].added = ! this->removeUsingCurrentSession(_totalServices[i]);
    }
}

bool EtcdRegister::removeUsingCurrentSession(const ServiceEtcdInfo& aService)
{
    try{
        Poco::URI uri;
        uri.setScheme(aService.schema);
        uri.setHost(aService.host);
        uri.setPort(aService.port);
        std::string svr_name = Poco::format("%s:%s:%d", aService.schema, aService.host, aService.port);

        Poco::Path regPath(aService.path);
        regPath.append(svr_name);
        const std::string key = regPath.toString();
       
        etcd::Response res = _etcdClient->rm(key).get();
        if(res.error_code() == 0) return true;
        else return false;
    }
    catch(...){
        return false;
    }
}

void EtcdRegister::setEtcdHosts(const std::string& aEtcdHosts, const std::string& aEtcdTotalHostsKey  )
{
    
   this-> _etcdHosts = aEtcdHosts;
    _etcdTotalHostsKey = aEtcdTotalHostsKey;
}
