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

EtcdRegister::EtcdRegister(const EtcdRegister& orig) {
}

EtcdRegister::~EtcdRegister() {
    stop();
    delete _etcdClient;
}

void EtcdRegister::addService(const std::string& path, const std::string& host, const int port)
{
    _totalServices.push_back(ServiceInfo(path,host,port));
    if(!_started)
    {
        return;
    }
    else
    {
        addUsingCurrentSession(ServiceInfo(path,host,port));
    }
}

bool EtcdRegister::addUsingCurrentSession(const ServiceInfo& aService)
{
    try
    {
        const std::string key = _etcdTotalHostsKey +"/"+aService.path;
        const std::string value = Poco::format("%s:%d",aService.path,aService.port);
        etcd::Response res = _etcdClient->set(key,value).get();
        if(res.error_code() == 0) return true;
        else return false;
    }
    catch(...)
    {
        return false;
    }
   
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
   
    if(!_etcdClient)
    {
        _etcdClient = new etcd::Client(_etcdHosts);

    }
}


void EtcdRegister::unRegisterAll()
{
    for(size_t i= 0 ;i < _totalServices.size() ; i++)
    {
        if(_totalServices[i].added)
            _totalServices[i].added = ! this->removeUsingCurrentSession(_totalServices[i]);
    }
}

bool EtcdRegister::removeUsingCurrentSession(const ServiceInfo& aService)
{
    const std::string key = this->_etcdTotalHostsKey + "/" + aService.path;
    const std::string value = Poco::format("%s:%d",aService.host,aService.port);
    etcd::Response res = _etcdClient->rmdir(key).get();
    if(res.error_code()==0) return true;
    return false;
}


