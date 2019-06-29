/* 
 * File:   ZKRegister.h
 * Author: trungthanh
 *
 * Created on September 14, 2015, 1:51 PM
 * 
 * Simple Zookeeper Service register, one connection, multiple services
 */

#ifndef ZKREGISTER_H
#define	ZKREGISTER_H

#include <string>
#include <vector>
#include <stdint.h>

#include "Poco/SharedPtr.h"
#include "Poco/ActiveMethod.h"
#include "Poco/Event.h"

#include <list>
#include <map>

namespace zk {
    class ZooKeeperAdapter;
}
typedef Poco::SharedPtr<zk::ZooKeeperAdapter> ZooKeeperAdapterPtr;

class ZKRegisterObserver{
public:
    virtual ~ZKRegisterObserver(){}
public:
    virtual void onRegisterSuccess(const std::string& path, const std::string& host, const int port, const std::string& schema) = 0;    
    virtual void onRegisterFailed(const std::string& path, const std::string& host, const int port, const std::string& schema) = 0;
};

struct ServiceInfo{
    ServiceInfo()
    :path()
    ,host()
    ,port(0)
    ,schema()
    ,added(false)
    {
        
    }
    ServiceInfo(const std::string& aPath, const std::string& aHost, const int aPort, const std::string& aSchema)
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

class ZKRegister {
public:
    ZKRegister(const std::string& aZkHosts, const std::string& aZkTotalHostsKey = std::string("/corp/zookeeper/farm/totalhosts") );
    void setZkHosts(const std::string& aZkHosts, const std::string& aZkTotalHostsKey = std::string("/corp/zookeeper/farm/totalhosts") )
    {
        _zkHosts = aZkHosts;
        _zkTotalHostsKey = aZkTotalHostsKey;
    }
    virtual ~ZKRegister();
private:
    ZKRegister(const ZKRegister& orig);
    
public:
    void addService(const std::string& path, const std::string& host, const int port, const std::string& schema = "dummy");
    void start();
    void stop();
protected:
    void initConnection();
    void registerAll();
    void unRegisterAll();
    bool addUsingCurrentSession(const ServiceInfo& aService);
    bool removeUsingCurrentSession(const ServiceInfo& aService);
    void mergeZKFarm();
private:
    bool _started;
    
    // Initial zk hosts
    std::string _zkHosts;
    std::string _zkTotalHosts;
    
    // key in zookeeper farm that store information about whole farm
    std::string _zkTotalHostsKey; 
    std::vector<ServiceInfo> _totalServices;
    
    ZooKeeperAdapterPtr _zkClient;
    int _failedCount;
    Poco::Event _stopMonitorEvent;
    Poco::Event _wakeupMonitorEvent;
    class ZKRegister_private;
    ZKRegister_private* _pZkCallback;
    
};

#endif	/* ZKREGISTER_H */

