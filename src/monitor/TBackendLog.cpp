/* 
 * File:   TBackendLog.cpp
 * Author: trungthanh
 * 
 * Created on October 5, 2012, 1:21 AM
 */

#include "monitor/TBackendLog.h"
#include "PocoEx/TimeUtils.h"
#include "thriftutil/TCompressSerializer.h"

void TCacheLog::clearAt(const int seconds){
    cacheHit.set( seconds , 0);
    cacheMissed.set(seconds, 0);
}

void TCacheLog::addCacheMissed(const int seconds, int count){
    cacheMissed.add(seconds , count);
}

void TCacheLog::addCacheHit(const int seconds, int count){
    cacheHit.add(seconds , count);
}

void TOperationLog::clearAt(const int seconds){
    operationCount.set(seconds, 0);
    cacheHit.set(seconds, 0);
    persistentHit.set(seconds, 0);
    excuteTime.set(seconds,0);
}

void TOperationLog::addCacheHit(int seconds, int count){
    cacheHit.add(seconds, count);
}

void TOperationLog::addExcuteTime(int seconds, int count){
    excuteTime.add(seconds, count);
}

void TOperationLog::addHit(int seconds, int count){
    operationCount.add(seconds, count);
}

void TOperationLog::addPersistentHit(int seconds, int count){
    this->persistentHit.add(seconds, count);
}

void TBackendLog::log(uint64_t dirtyCount, uint64_t coldCount, uint64_t maxCacheSize, uint64_t cacheSize, uint64_t procMem, uint64_t procVirt, uint64_t cacheMemSize){
    int seconds = TimeUtils::getCurrentSeconds();

    this->savingQueue.set(seconds, dirtyCount);

    this->warmingQueue.set(seconds, coldCount);

    this->cache.cacheMaxSize.set(seconds,maxCacheSize);

    this->cache.cacheSize.set(seconds, cacheSize);

    this->cache.cacheMemSize.set(seconds, cacheMemSize);
    
    this->processMem.set(seconds, procMem);

    this->processVirt.set(seconds, procVirt);

    // clear future
    int toClear = seconds+10;
    toClear = toClear % TSECOND;
    cache.clearAt(toClear);
    read.clearAt(toClear);
    write.clearAt(toClear);
    
    
}

void TBackendLog::addReadCounts(int seconds, const int hit, const int cacheHit, int persistentHit, int excuteTime){
    read.addHit(seconds, hit);
    read.addCacheHit(seconds, cacheHit);
    read.addExcuteTime(seconds, excuteTime);
    read.addPersistentHit(seconds, persistentHit);
}

void TBackendLog::addWriteCounts(int seconds, const int hit, const int cacheHit, int persistentHit, int excuteTime){
    write.addHit(seconds, hit);
    write.addCacheHit(seconds, cacheHit);
    write.addExcuteTime(seconds, excuteTime);
    write.addPersistentHit(seconds, persistentHit);
}

void TBackendLog::addCacheCounter(int seconds, const int cacheHit, const int cacheMissed){
    cache.addCacheHit(seconds, cacheHit);
    cache.addCacheMissed(seconds, cacheMissed);
}

TBackendLogCollector::TBackendLogCollector(TBackendLog& aLog)
:start(this,& TBackendLogCollector::_collectingFunc)
,_backendLog(aLog)
,_fetcher(NULL)
,_enable(true)
{
    
}

void TBackendLogCollector::_collectingFunc(){
        Poco::Thread::sleep(1000);
        _enable = true;
        while (_enable) {
            
            if (_fetcher){
                // cache stat
                uint64_t dirtyCount = _fetcher->getSavingQueue();
                uint64_t coldCount = _fetcher->getWarmingQueue();
                uint64_t maxCacheSize = _fetcher->getCacheMaxSize();
                uint64_t cacheSize = _fetcher->getCacheSize();
                uint64_t procMem  = 0;
                uint64_t procVirt = 0;
                
                _fetcher->getProcessMemInfo(procMem, procVirt);
                
                uint64_t cacheMemSize = _fetcher->getCacheMemSize();
                
                _backendLog.log(dirtyCount, coldCount, maxCacheSize, cacheSize ,procMem, procVirt, cacheMemSize);
            }
            Poco::Thread::sleep(1000);
        }    
        _stopEvent.set();
}

void TBackendLogCollector::stop(){
    if (!_enable)
        return;
    _enable = false;
    while (!_stopEvent.tryWait(1))
        _enable = false;
//    _stopEvent.wait();
}