/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   LiteEndpointManager.h
 * Author: trungthanh
 *
 * Created on August 5, 2017, 5:00 PM
 */

#ifndef LITEENDPOINTMANAGER_H
#define LITEENDPOINTMANAGER_H
#include "Endpoint.h"

#include "Util/SpinLock.h"
#include "Poco/Mutex.h"
#include "Poco/SharedPtr.h"
#include "Poco/Event.h"
#include "Poco/ActiveMethod.h"
#include <map>
/*
 * LiteEndpointManager
 * using 1 zookeeper/etcd connection for monitoring 
 * multiple services 's endpoints 
 * It is different to EndpointManager
 * Todo: Continue develop this class
 */
class LiteEndpointManager {
public:
    LiteEndpointManager();
    virtual ~LiteEndpointManager();
    
public:
    
    virtual void start();
    
    virtual void stop();
    
    virtual void addService(const std::string& basePath);
    
    /**
     * get random endpoint from endpoints 
     * @param outEndpoint: output endpoint
     * @return true if endpoint is from zookeeper list 
     *		
     */
    virtual bool getEndpoint(const std::string& basePath, Endpoint& outEndpoint) const;
    
    /**
     * Get all endpoints from zookeeper / etcd
     * @param outEndpoints : all endpoint
     * @return 
     */
    virtual bool getEndpoint(const std::string& basePath, std::vector< Endpoint >& outEndpoints)const;
    
    
public:
    
    /**
     * 
     * @param zkServer zookeeper server such as 127.0.0.1:2181,xyz.a.a.a:2181
     * @param zkBasePath base path for endpoint : /abc/xyz
     */
    void loadEndpoints(const std::string& zkServer);
    
    void setDefaultEndpoint(const std::string& basePath, const Endpoint& aEndpoint);
    
    
private:
    LiteEndpointManager(const LiteEndpointManager& orig);

    class LiteCallback;
    friend class LiteEndpointManager::LiteCallback;
    
    typedef std::vector<Endpoint> TEndpoints;
    
    struct TServiceEp{
        Endpoint defaultEnpoint;
        mutable int  _currentIndex;
        TEndpoints totalEndpoints;
    };
    
    std::map< std::string, Poco::SharedPtr<TServiceEp> > name2Infos;
    
};

#endif /* LITEENDPOINTMANAGER_H */

