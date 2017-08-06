/* 
 * File:   CachePersistentBase.h
 * Author: trungthanh
 *
 * Created on October 18, 2012, 10:47 AM
 */

#ifndef _STORAGE_CACHEPERSISTENTBASE_H
#define	_STORAGE_CACHEPERSISTENTBASE_H

#include <Poco/Types.h>
#include <string>

namespace openstars { namespace storage{

class CachePersistentObserver{
public:
    virtual void hitCache(Poco::Int64 execTime , bool isWrite) = 0;
    virtual void missedCache(Poco::Int64 execTime , bool isWrite) = 0;
    virtual void hitPersistent(Poco::Int64 execTime , bool isWrite) = 0;
};    
    
    
/*
 * class CachePersistentBase
 * Description: base class for CachePersistent, this support monitoring params, operating cache-storage 
 */
class CachePersistentBase {
public:
        virtual void startSaving() = 0;
        
        virtual void stopSaving() = 0;
        
        virtual void startWarmingUp() = 0;// start warming thread
        
        virtual void stopWarmingUp() = 0; // stop warming thread
        
        virtual void startDumping()  = 0; // not need right now
        
        virtual size_t savingQueueSize() = 0;//number of dirty objects
        
        virtual size_t warmingQueueSize() = 0;//number of objects being warming Up
        
    
};

}}
#endif	/* _STORAGE_CACHEPERSISTENTBASE_H */

