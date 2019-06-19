/* 
 * File:   ZKRegister.cpp
 * Author: trungthanh
 * 
 * Created on September 14, 2015, 1:51 PM
 */

#include "ZKRegister.h"

#include "zkadapter/zkadapter.h"

#include "Poco/URI.h"
#include "Poco/Path.h"
#include "Poco/StringTokenizer.h"
#include "Poco/NumberParser.h"
#include <Poco/Format.h>

#include <iostream>
#include <set>

using namespace std;


ZKRegister::ZKRegister(const std::string& aZkHosts, const std::string& aZkTotalHostsKey)
:_started(false)
,_zkHosts(aZkHosts)
,_zkTotalHosts()
,_zkTotalHostsKey(aZkTotalHostsKey)

{
    
}



ZKRegister::~ZKRegister() {
    stop();
}

void ZKRegister::addService(const std::string& path, const std::string& host, const int port, const std::string& schema)
{
    _totalServices.push_back(ServiceInfo(path, host, port, schema) );
    if (!_started)
    {
        return;
    } 
    else {
        addUsingCurrentSession(ServiceInfo(path, host, port, schema) );
    }
}
void ZKRegister::start()
{
    if (_started)
        return;
    // init connection
    this->initConnection();
    registerAll();
    _started = true;
    mergeZKFarm();
}

void ZKRegister::stop()
{
    if (!_started)
        return;
    this->initConnection();
    this->unRegisterAll();
    _started = false;
}

void ZKRegister::initConnection()
{
    if (_zkTotalHosts.length() == 0)
        _zkTotalHosts = _zkHosts;
    if (_zkTotalHosts.length() == 0)
        return;
    try {
        if (!_zkClient){
            ZooKeeperConfig config(this->_zkHosts, ZooKeeperConfig::defaultLeasedTimeout, true, 1000);
            _zkClient = (ZooKeeperAdapterPtr) new ZooKeeperAdapter(config);
            _zkClient->reconnect();           
        }
    }catch(...){
        ZooKeeperConfig config(this->_zkHosts, ZooKeeperConfig::defaultLeasedTimeout, true, 1000);
        _zkClient = (ZooKeeperAdapterPtr) new ZooKeeperAdapter(config);
        _zkClient->reconnect();        
    }
}

bool isHostPort(const std::string& aString){
    try {
        Poco::StringTokenizer aStk(aString, ":");
        if (aStk.count() != 2)
            return false;
        if (Poco::NumberParser::parse(aStk[1]) <= 0)
            return false;
        return true;
    } catch( ... )
    {
        return false;
    }
    return false;
}

void ZKRegister::mergeZKFarm()
{
    //Todo: implement this
    std::string serverZK;
    try{
        serverZK = _zkClient->getNodeData(_zkTotalHostsKey);
    }
    catch(ZooKeeperException ex)
    {
        cout<<"getNodeData exception "<<ex.what()<<endl;
    }
    catch(...)
    {
        cout<<"getNodeData exception"<<endl;
    }
    std::set<std::string> oldHosts; // from serverZK
    Poco::StringTokenizer aStk(serverZK, ", ");
    for (size_t i = 0 ; i < aStk.count(); i++){
        
        if (aStk[i].length() > 0)
            if (isHostPort(aStk[i]))
                oldHosts.insert(aStk[i]);
    }
    
    std::set<std::string> currentHosts; // from serverZK
    Poco::StringTokenizer aStk2(this->_zkHosts, ", ");
    for (size_t i = 0 ; i < aStk2.count(); i++){
        
        if (aStk2[i].length() > 0)
            if (isHostPort(aStk2[i]))
                currentHosts.insert(aStk2[i]);
    }
    
    if (currentHosts == oldHosts)
        return;
    
    std::set<std::string> newHosts = oldHosts;
    for (std::set<std::string> ::iterator aIt = currentHosts.begin(); aIt != currentHosts.end() ; aIt ++ )
        newHosts.insert(*aIt);
    
    std::string newServerZK;
    size_t newCount = newHosts.size();
    size_t index=0;
    for (std::set<std::string> ::iterator aIt = newHosts.begin(); aIt != newHosts.end(); aIt++, index++)
    {
        if (index+1< newCount){
            newServerZK = newServerZK + (*aIt) + ",";
        }
        else 
            newServerZK = newServerZK + *aIt;
    }
    this->_zkTotalHosts = newServerZK;
    try {
        _zkClient->setNodeData(_zkTotalHostsKey, newServerZK);
    } catch (...){
        try {
            _zkClient->reconnect();
            _zkClient->createNode(_zkTotalHostsKey, newServerZK);
        }catch(...)
        {
            
        }
    }
    
}

void ZKRegister::registerAll(){
    for (size_t i = 0 ; i < _totalServices.size(); i ++)
        _totalServices[i].added = this->addUsingCurrentSession(_totalServices[i]);
}

bool ZKRegister::addUsingCurrentSession(const ServiceInfo& aService)
{
    try{
        Poco::URI uri;
        uri.setScheme(aService.schema);
        uri.setHost(aService.host);
        uri.setPort(aService.port);

        // format node-name
        std::string svr_name = Poco::format("%s:%s:%d", aService.schema, aService.host, aService.port);

        Poco::Path regPath(aService.path);
        regPath.append(svr_name);

        return _zkClient->createNode(regPath.toString(), uri.toString());
    } 
    catch(...)
    {
        return false;
    }
}

void ZKRegister::unRegisterAll(){
    for (size_t i = 0 ; i < _totalServices.size(); i ++)
        if (_totalServices[i].added)
            _totalServices[i].added = !this->removeUsingCurrentSession(_totalServices[i]);
}

bool ZKRegister::removeUsingCurrentSession(const ServiceInfo& aService)
{
    try{
        Poco::URI uri;
        uri.setScheme(aService.schema);
        uri.setHost(aService.host);
        uri.setPort(aService.port);

        // format node-name
        std::string svr_name = Poco::format("%s:%s:%d", aService.schema, aService.host, aService.port);

        Poco::Path regPath(aService.path);
        regPath.append(svr_name);

        
        return _zkClient->deleteNode(regPath.toString());
    } 
    catch(...)
    {
        return false;
    }    
}