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
#include <thread>
#include <unistd.h>
#include <memory>
#include <chrono>
using namespace std;
void SetToEtcd(std::string key,std::string value,std::string url);

EtcdRegister::EtcdRegister(const std::string& aEtcdHosts,const std::string& aEtcdTotalHostsKey) 
: _started(false)
,_etcdHosts(aEtcdHosts)
,_etcdTotalHosts()
,_etcdTotalHostsKey(aEtcdTotalHostsKey)
{
    
}


EtcdRegister::~EtcdRegister() {
    stop();
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
//        std::thread task(addUsingCurrentSession,ServiceEtcdInfo(path,host,port,schema),this->_etcdClient);
        
    }
}

bool EtcdRegister::addUsingCurrentSession(const ServiceEtcdInfo& aService)
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
        this->_listKeyValEtcd.push_back(KeyValueEtcd(key,value));
//        std::thread task(SetToEtcd,key,value,_etcdHosts);
//        task.join();
        return true;
}
void RegisterToEcdt(std::vector<KeyValueEtcd> listKV,std::string url){
    EtcdAdapterPtr client = std::make_shared<etcd::Client>(url);

    for(size_t t= 0 ;t < listKV.size();t++){
        while(true){
            etcd::Response res = client->set(listKV[t].key,listKV[t].value).get();
            if (res.error_code() != 0){
                std::cout<<t<<" Set key: "<<listKV[t].key<<" value: "<<listKV[t].value <<" failed!"<<std::endl;
            }
            else
            {
                std::cout<<t<<" Set key: "<<listKV[t].key<<" value: "<<listKV[t].value <<" sucesss!"<<std::endl;
                break;
            }
//            std::this_thread::sleep_for(std::chrono::seconds(5));
        }
    }
}
void SetToEtcd(std::string key,std::string value,std::string url){
   EtcdAdapterPtr client = std::make_shared<etcd::Client>(url);
   long int i = 0;
   while(true){
       etcd::Response res = client->set(key,value).get();
       if ( res.error_code() == 0) 
       {
           std::cout<<"Set key: "<<key<<" value: "<<value<<" success!"<<std::endl;
           return;
       }
       std::cout<<i<<" Set key: "<<key<<" value: "<<value<<" failed!"<<std::endl;
       i++;
       std::this_thread::sleep_for(std::chrono::seconds(5));
   }
}

void EtcdRegister::registerAll()
{
    for(size_t i = 0 ;i< _totalServices.size();i++)
        _totalServices[i].added = this->addUsingCurrentSession(_totalServices[i]);
    std::thread task(RegisterToEcdt,this->_listKeyValEtcd,_etcdHosts);
    task.detach();
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
   
    _etcdClient =  std::make_shared<etcd::Client>(_etcdHosts);
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
        Poco::URI uri;
        uri.setScheme(aService.schema);
        uri.setHost(aService.host);
        uri.setPort(aService.port);
        std::string svr_name = Poco::format("%s:%s:%d", aService.schema, aService.host, aService.port);

        Poco::Path regPath(aService.path);
        regPath.append(svr_name);
        const std::string key = regPath.toString();
       
        etcd::Response res = _etcdClient->rm(key).get();
        
        if(res.error_code() == 0)
        {
            std::cout<<"Del key: "<<key<<" success!"<<std::endl;
            return true;
        }
        else
        {
            std::cout<<"Del key: "<<key<<" failed!"<<std::endl;
            return false;
        }
}

void EtcdRegister::setEtcdHosts(const std::string& aEtcdHosts, const std::string& aEtcdTotalHostsKey  )
{
    
   this-> _etcdHosts = aEtcdHosts;
    _etcdTotalHostsKey = aEtcdTotalHostsKey;
}
