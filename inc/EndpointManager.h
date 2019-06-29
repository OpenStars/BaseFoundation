/* 
 * File:   EndpointManager.h
 * Author: trungthanh
 *
 * Created on November 19, 2012, 7:00 PM
 */

#ifndef ENDPOINTMANAGER_H
#define	ENDPOINTMANAGER_H

#include "Endpoint.h"

#include "Poco/Mutex.h"
#include "Poco/SharedPtr.h"
#include "Poco/Event.h"
#include "Poco/ActiveMethod.h"

class EndpointManagerPrivate;

class EndpointManager//:public ZKEventListener
{
    friend class EndpointManagerPrivate;
public:
    EndpointManager(const Endpoint& defaultEndpoint=Endpoint(), Endpoint::TType preferType = Endpoint::EAnyType);

    
    /**
     * destructor
     */
    virtual ~EndpointManager();
public:
    
    /**
     * get random endpoint from endpoints 
     * @param outEndpoint: output endpoint
     * @return true if endpoint is from zookeeper list 
     *		
     */
    virtual bool getEndpoint(Endpoint& outEndpoint) const;
    
    /**
     * Get all endpoints from zookeeper
     * @param outEndpoints : all endpoint
     * @return 
     */
    virtual bool getEndpoint(std::vector< Endpoint >& outEndpoints)const;
    
    
public:
    
    /**
     * 
     * @param zkServer zookeeper server such as 127.0.0.1:2181,xyz.a.a.a:2181
     * @param zkBasePath base path for endpoint : /abc/xyz
     */
    void loadEndpoint(const std::string& zkServer, const std::string& zkBasePath);
    
    void setDefaultEndpoint(const Endpoint& aEndpoint);
    
protected:    
    void doLoadEndpoint(bool reconnect = false);
    
    bool parseEndpoint(const std::string& endpointPath, Endpoint& result);
       
    void checkConnectionImpl();
    
    void removeEndpoint(const Endpoint& aEndpoint);
private:
    
    EndpointManager(const EndpointManager& orig);
    
    void replaceAll(std::vector< Endpoint >& endpoints);

    void stopChecking();
    
    Poco::ActiveMethod<void , void , EndpointManager> startChecking;

private:
    typedef Poco::FastMutex MutexType;
    
    typedef MutexType::ScopedLock ScopedLockType;
    
    mutable MutexType _mutex;
    
    Endpoint _defaultEnpoint;
    
    /*only accept endpoint equal to _preferType (if _preferType differs from EAnyType)*/
    Endpoint::TType _preferType; 
    
//    Poco::SharedPtr<ZooKeeperAdapter> _zkClient;
    
    /*zookeeper servers*/
    std::string _zkServers;
    
    /*base path for services*/
    std::string _zkBasePath; 
    
    /*endpoints from zoo keeper*/
    std::vector< Endpoint > _endpoints;
    
    mutable int  _currentIndex;
    
    volatile bool _runningChecking;
    
    EndpointManagerPrivate *_private;
    
    Poco::Event _doneEvent;
    Poco::Event _stopMonitorEvent;
    
    
};

#endif	/* ENDPOINTMANAGER_H */

