/* 
 * File:   ServiceStatFetcher.h
 * Author: trungthanh
 *
 * Created on October 18, 2012, 11:00 AM
 */

#ifndef SERVICESTATFETCHER_H
#define	SERVICESTATFETCHER_H

#include <Storage/CachePersistentBase.h>
#include <Storage/MultiKVStorage.h>
#include <Caching/CacheBase.h>

class ServiceStatFetcher{
public:
    ServiceStatFetcher(){}
    virtual ~ServiceStatFetcher(){}
public:
    virtual uint64_t getCacheSize() { return 0; }

    virtual uint64_t getCacheMaxSize() { return 0; }

    virtual void  getReadStorage(std::vector< std::string >& _return){};

    virtual void  getWriteStorage(std::vector< std::string >& _return){};

    virtual uint64_t getSavingQueue(){return 0;}

    virtual uint64_t getWarmingQueue(){return 0;}

    virtual void getProcessMemInfo(uint64_t& memUsed, uint64_t& virtSize){};

    virtual uint64_t getCacheMemSize(){return 0;}
    
public:
    /*factory method*/
    static ServiceStatFetcher* createFetcher(
        openstars::caching::CacheBase& aCache,
        openstars::storage::CachePersistentBase& aCachePersistent,
            openstars::storage::MultiKVStorage& aStorage
    );
    
};


#endif	/* SERVICESTATFETCHER_H */

