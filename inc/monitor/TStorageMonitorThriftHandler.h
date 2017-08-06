/* 
 * File:   TStorageMonitorThriftHandler.h
 * Author: trungthanh
 *
 * Created on October 4, 2012, 4:11 PM
 */

#ifndef TSTORAGEMONITORTHRIFTHANDLER_H
#define	TSTORAGEMONITORTHRIFTHANDLER_H

#include "monitor/TMonitorThriftHandler.h"
#include "StorageMonitorService.h"
#include "thriftutil/TThriftServer.h"


namespace openstars { namespace storage {
        class CachePersistentBase;
        class MultiKVStorage;
    }
    namespace caching{
        class CacheBase;
    }

};

using namespace openstars::base::monitor;
using namespace openstars::base::storage::monitor;

class AbstractStorageFactory;

class TStorageMonitorThriftHandler
        : virtual public StorageMonitorServiceIf
        , public ::TMonitorThriftHandler {
public:
    TStorageMonitorThriftHandler(openstars::caching::CacheBase* aCache = NULL ,openstars::storage::CachePersistentBase* aCachePersistent = NULL, 
            openstars::storage::MultiKVStorage* aStorage = NULL);
    TStorageMonitorThriftHandler(const TStorageMonitorThriftHandler& orig);
    virtual ~TStorageMonitorThriftHandler();
    
    typedef openstars::base::transport::TThriftServer< 
                openstars::base::storage::monitor::StorageMonitorServiceIf,
                openstars::base::storage::monitor::StorageMonitorServiceProcessor,
                apache::thrift::protocol::TBinaryProtocolFactory > TStorageMonitorServer;
public:
  virtual void getCurrentCacheStorageStat(backendStat& _return);

  virtual void getCacheStorageStat(backendStat& _return, const int32_t seconds);
  
  virtual void setCacheMaxSize(int32_t newMaxSize);

  virtual void enableStorageBackend(const bool isRead, const bool isEnable, const std::string& beName);

  virtual void saveDataToBackend(const bool enable) ;

  virtual void enableWarming(const bool enable) ;
  
  virtual void compactData(const std::string& storageName);
  
  virtual void closeStorage(const std::string& stgName);

  virtual void openStorage(const std::string& stgCreateOption);
  
  /*Todo: implement these function*/
  virtual void getZKServicePath(std::string& _return){};
  
  virtual void getZKConfigPath(std::string& _return) {};

  void checkZKService(){}

  void checkZKConfigPath(){}

  virtual void registerServiceZK(const std::string& basePath, const std::string& scheme){}
  virtual void registerConfigZK(const std::string& basePath, const std::string& scheme) {}

  void addListenServicePort(int32_t newPort){}

public:
    void setCacheStorage(openstars::caching::CacheBase* aCache,openstars::storage::CachePersistentBase* aCachePersistent , 
            openstars::storage::MultiKVStorage* aStorage ) {
        _cache = aCache;
        _cachePersistent = aCachePersistent;
        _storage = aStorage;
    };

private:
    openstars::caching::CacheBase* _cache;
    openstars::storage::CachePersistentBase* _cachePersistent;
    openstars::storage::MultiKVStorage* _storage;

};

#endif	/* TSTORAGEMONITORTHRIFTHANDLER_H */

