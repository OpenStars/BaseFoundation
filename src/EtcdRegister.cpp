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
        const std::string key = _etcdTotalHostsKey +"/"+aService.path + "/" + aService.schema;
        const std::string value = Poco::format("%s:%d",aService.host,aService.port);
        std::cout<<"Add service key : " <<key <<" value : "<<value <<std::endl;
        etcd::Response res = _etcdClient->set(key,value).get();
        if(res.error_code() == 0) return true;
        else return false;
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
    const std::string key = this->_etcdTotalHostsKey + "/" + aService.path + "/" +aService.schema;
    const std::string value = Poco::format("%s:%d",aService.host,aService.port);
    etcd::Response res = _etcdClient->rmdir(key).get();
    if(res.error_code()==0) return true;
    return false;
}


