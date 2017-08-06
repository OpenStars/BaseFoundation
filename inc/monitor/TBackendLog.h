/* 
 * File:   TBackendLog.h
 * Author: trungthanh
 *
 * Created on October 5, 2012, 1:21 AM
 */

#ifndef TBACKENDLOG_H
#define	TBACKENDLOG_H

#include <stdint.h>

#include "Poco/ActiveMethod.h"
#include "Poco/Event.h"

#include "monitor/ServiceStatFetcher.h"
#include "monitor/TDayStat.h"


struct TCacheLog{
    std::string cacheType;
    TCacheLog(){
        cacheMaxSize.clear();
        cacheSize.clear();
        cacheHit.clear();
        cacheMissed.clear();
    }
    TDayStat<boost::atomic_uint64_t, uint64_t> cacheMaxSize;
    TDayStat<boost::atomic_uint64_t, uint64_t> cacheSize;
    TDayStat<boost::atomic_uint64_t, uint64_t> cacheHit;
    TDayStat<boost::atomic_uint64_t, uint64_t> cacheMissed;

    TDayStat<boost::atomic_uint64_t, uint64_t> cacheMemSize;

    void addCacheHit(const int seconds, int count);
    void addCacheMissed(const int seconds, int count);
    void clearAt(const int seconds);

};

struct TOperationLog{
    TOperationLog(){
        operationCount.clear();
        cacheHit.clear();
        persistentHit.clear();
        excuteTime.clear();
    }
    
    TDayStat<boost::atomic_uint64_t, uint64_t> operationCount;
    TDayStat<boost::atomic_uint64_t, uint64_t> cacheHit;
    TDayStat<boost::atomic_uint64_t, uint64_t> persistentHit;
    TDayStat<boost::atomic_uint64_t, uint64_t> excuteTime;

    void clearAt(const int seconds);
    void addHit(int seconds, int count);
    void addCacheHit(int seconds, int count);
    void addPersistentHit(int seconds, int count);
    void addExcuteTime(int seconds, int count);

};

struct TBackendLog{
    TBackendLog(){
        savingQueue.clear();
        warmingQueue.clear();
    }
    
    TCacheLog cache;
    TDayStat<boost::atomic_uint64_t, uint64_t> savingQueue;
    TDayStat<boost::atomic_uint64_t, uint64_t> warmingQueue;
    TOperationLog read;
    TOperationLog write;

    TDayStat<boost::atomic_uint64_t, uint64_t> processMem;
    TDayStat<boost::atomic_uint64_t, uint64_t> processVirt;
    
    std::vector< std::string > readStorage;
    std::vector< std::string > writeStorage;
    
    // this would be called from collector's thread
    void log(uint64_t dirtyCount,  uint64_t coldCount, uint64_t maxCacheSize, uint64_t cacheSize, uint64_t procMem, uint64_t procVirt, uint64_t cacheMemSize);
    
    //these would be called from service 's thread
    void addReadCounts( int seconds, const int hit, const int cacheHit, int persistentHit, int excuteTime );
    void addWriteCounts( int seconds, const int hit, const int cacheHit, int persistentHit, int excuteTime );
    void addCacheCounter(int seconds, const int cacheHit, const int cacheMissed);

};


class TBackendLogCollector{
public:
    TBackendLogCollector(TBackendLog& aLog);
    
    
    Poco::ActiveMethod < void, void , TBackendLogCollector> start;
    void stop();
    void setFetcher(ServiceStatFetcher* aFetcher){ _fetcher = aFetcher; }
private:
    void _collectingFunc();
protected:
    TBackendLog& _backendLog;
    ServiceStatFetcher* _fetcher;
    volatile bool _enable;
    Poco::Event _stopEvent;
};

#endif	/* TBACKENDLOG_H */

