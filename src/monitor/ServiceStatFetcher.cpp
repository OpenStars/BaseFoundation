/* 
 * File:   ServiceStatFetcher.cpp
 * Author: trungthanh
 * 
 * Created on October 18, 2012, 11:00 AM
 */

#include "monitor/ServiceStatFetcher.h"
#include <Caching/MemoryStats.h>

class BackendStatFetcher:public ServiceStatFetcher{
public:
    typedef openstars::caching::CacheBase CacheType;
    typedef openstars::storage::CachePersistentBase CachePersistent;
    
    BackendStatFetcher(CacheType& aCache 
        , CachePersistent& aCachePersistent
        , openstars::storage::MultiKVStorage& aStorage)
    :_cache(aCache)
    ,_cachePersistent(aCachePersistent)
    ,_storage(aStorage){}
    
public:
    virtual uint64_t getCacheSize() { return _cache.size(); }
    
    virtual uint64_t getCacheMaxSize() { return _cache.maxSize(); }

    virtual void  getReadStorage(std::vector< std::string >& _return){
        _storage.getReadStorageNames(_return);
    };

    virtual void  getWriteStorage(std::vector< std::string >& _return){
        _storage.getWriteStorageNames(_return);
    }

    virtual uint64_t getSavingQueue(){
        return _cachePersistent.savingQueueSize();
    }

    virtual uint64_t getWarmingQueue(){
        return _cachePersistent.warmingQueueSize();
    }
    
    virtual void getProcessMemInfo(uint64_t& memUsed, uint64_t& virtSize){
        static MemoryStats aTool;
        
        MemoryInfo aInfo;
        aTool.grabMemInfo(aInfo);
        
        memUsed = aInfo.processMem;
        virtSize = aInfo.processVirt;
        
    }

    virtual uint64_t getCacheMemSize(){
        return _cache.getMemSize();
    }
    
protected:
    CacheType& _cache;
    CachePersistent& _cachePersistent;
    openstars::storage::MultiKVStorage& _storage;
};

ServiceStatFetcher* ServiceStatFetcher::createFetcher(
    openstars::caching::CacheBase& aCache, 
    openstars::storage::CachePersistentBase& aCachePersistent,
        openstars::storage::MultiKVStorage& aStorage ) {
    
    return new BackendStatFetcher(aCache, aCachePersistent, aStorage);
}
