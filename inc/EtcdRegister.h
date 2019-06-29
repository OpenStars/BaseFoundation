/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   EtcdRegister.h
 * Author: lehaisonmath6
 *
 * Created on June 18, 2019, 2:42 PM
 */

#ifndef ETCDREGISTER_H
#define ETCDREGISTER_H

#include<string>
#include<vector>
#include<stdint.h>

#include"Poco/SharedPtr.h"
#include "Poco/ActiveMethod.h"
#include "Poco/Event.h"

#include<list>
#include<map>
#include <memory>
#include <iostream>

namespace etcd {
    class Client;
}


typedef etcd::Client *  EtcdAdapterPtr;

class EtcdRegisterObserver{
public:
    virtual ~EtcdRegisterObserver(){}
public:
    virtual void onRegisterSucess(const std::string& path,const std::string& host,const std::string& port) = 0;
    virtual void onRegisterFailed(const std::string& path,const std::string& host,const std::string& port) = 0;
    
};

struct ServiceEtcdInfo {
    ServiceEtcdInfo()
    :path()
    ,host()
    ,port(0)
    ,schema()
    ,added(false)
    {
    }
    ServiceEtcdInfo(const std::string& aPath,const std::string& aHost,const int aPort,const std::string& aSchema)
    :path(aPath)
    ,host(aHost)
    ,port(aPort)
    ,schema(aSchema)
    ,added(false)
    {
        
    }
    std::string path;
    std::string host;
    int port;
    std::string schema;
   
    bool added;
};

class EtcdRegister {
public:
    EtcdRegister(const std::string& aEtcdHosts, const std::string& aEtcdTotalHostsKey = std::string("/corp/etcdconfig/farm/totalhosts") );
    void setEtcdHosts(const std::string& aEtcdHosts, const std::string& aEtcdTotalHostsKey = std::string("/corp/etcdconfig/farm/totalhosts") )
    {
        _etcdHosts = aEtcdHosts;
//      aEtcdHosts  std::cout<<"etcdtotalhostkey : "<<aEtcdTotalHostsKey<<std::endl;
        _etcdTotalHosts= aEtcdTotalHostsKey;
        _etcdTotalHostsKey = aEtcdTotalHostsKey;
    }
    virtual ~EtcdRegister();
private:
    EtcdRegister(const EtcdRegister& orig);
    
public:
    void addService(const std::string& path, const std::string& host, const int port,const std::string& schema ="dummy");
    void start();
    void stop();
protected:
    void initConnection();
    void registerAll();
    void unRegisterAll();
    bool addUsingCurrentSession(const ServiceEtcdInfo& aService);
    bool removeUsingCurrentSession(const ServiceEtcdInfo& aService);
    void mergeEtcdFarm();
private:
    bool _started;
    
    // Initial etcd hosts
    std::string _etcdHosts;
    std::string _etcdTotalHosts;
    
    // key in etcd farm that store information about whole farm
    std::string _etcdTotalHostsKey; 
    std::vector<ServiceEtcdInfo> _totalServices;
    
    EtcdAdapterPtr _etcdClient;
    int _failedCount;
    Poco::Event _stopMonitorEvent;
    Poco::Event _wakeupMonitorEvent;

};

#endif /* ETCDREGISTER_H */

