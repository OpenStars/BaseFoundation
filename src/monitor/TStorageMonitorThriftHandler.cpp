/* 
 * File:   TStorageMonitorThriftHandler.cpp
 * Author: trungthanh
 * 
 * Created on October 4, 2012, 4:11 PM
 */

#include "monitor/TStorageMonitorThriftHandler.h"
#include "monitor/TStorageStatModule.h"
#include "PocoEx/TimeUtils.h"

#include "Caching/CacheBase.h"
#include "Storage/AbstractStorageFactory.h"
#include "Storage/MultiKVStorage.h"



TStorageMonitorThriftHandler::TStorageMonitorThriftHandler(
        openstars::caching::CacheBase* aCache,
        openstars::storage::CachePersistentBase* aCachePersistent,
        openstars::storage::MultiKVStorage* aStorage)
: _cache(aCache)
, _cachePersistent(aCachePersistent)
, _storage(aStorage)
{
}

TStorageMonitorThriftHandler::TStorageMonitorThriftHandler(const TStorageMonitorThriftHandler& orig)
{
}

TStorageMonitorThriftHandler::~TStorageMonitorThriftHandler()
{
}

void TStorageMonitorThriftHandler::getCurrentCacheStorageStat(backendStat& _return)
{
    int seconds = TimeUtils::getCurrentSeconds();
    if (seconds > 5)
        seconds -= 3;
    return this->getCacheStorageStat(_return, seconds);
}

void TStorageMonitorThriftHandler::getCacheStorageStat(backendStat& _return, const int32_t seconds)
{
    try {
        TBackendLog& aLog = TStorageStatModule::getInstance().getBackendLog();
        // cache stats
        _return.cache.cacheHit = aLog.cache.cacheHit.get(seconds);
        _return.cache.cacheMaxSize = aLog.cache.cacheMaxSize.get(seconds);
        _return.cache.cacheMiss = aLog.cache.cacheMissed.get(seconds);
        _return.cache.cacheSize = aLog.cache.cacheSize.get(seconds);
        _return.cache.cacheType = "NewCache"; //Todo: set cacheType
        _return.cache.cacheMemSize = aLog.cache.cacheMemSize.get(seconds);

        //storage stats
        _return.readStat.cacheHit = aLog.read.cacheHit.get(seconds);
        _return.readStat.excuteTime = aLog.read.excuteTime.get(seconds);
        _return.readStat.persistentHit = aLog.read.persistentHit.get(seconds);
        _return.readStat.operationCount = aLog.read.operationCount.get(seconds);

        _return.writeStat.cacheHit = aLog.write.cacheHit.get(seconds);
        _return.writeStat.excuteTime = aLog.write.excuteTime.get(seconds);
        _return.writeStat.persistentHit = aLog.write.persistentHit.get(seconds);
        _return.writeStat.operationCount = aLog.write.operationCount.get(seconds);

        _return.savingQueueSize = aLog.savingQueue.get(seconds);
        _return.warmingQueueSize = aLog.warmingQueue.get(seconds);

        _return.processMemKb = aLog.processMem.get(seconds);
        _return.processVirtKb = aLog.processVirt.get(seconds);
        if (_storage) {
            _storage->getReadStorageNames(_return.readStorage);
            _storage->getWriteStorageNames(_return.writeStorage);
        }

    } catch (...) {

    }

}

void TStorageMonitorThriftHandler::enableStorageBackend(const bool isRead, const bool isEnable, const std::string& beName)
{
    if (_storage)
        _storage->enableStorage(beName, isEnable, isRead ? openstars::storage::ERead : openstars::storage::EWrite);
}

void TStorageMonitorThriftHandler::saveDataToBackend(const bool enable)
{
    if (!_cachePersistent)
        return;
    if (enable)
        _cachePersistent->startSaving();
    else
        _cachePersistent->stopSaving();
}

void TStorageMonitorThriftHandler::enableWarming(const bool enable)
{
    if (!_cachePersistent)
        return;
    if (enable)
        _cachePersistent->startWarmingUp();
    else
        _cachePersistent->stopWarmingUp();
}

void TStorageMonitorThriftHandler::compactData(const std::string& storageName)
{
    if (_storage) {
        openstars::storage::AbstractKVStorage::Ptr aStg = _storage->getStorage(storageName);
        if (aStg)
            aStg->compactData();
    }
}

void TStorageMonitorThriftHandler::setCacheMaxSize(int32_t newMaxSize)
{
    if (_cache)
        _cache->setMaxSize(newMaxSize);
}

void TStorageMonitorThriftHandler::closeStorage(const std::string& stgName)
{
    if (_storage){
        _storage->removeStorage(stgName);
    }
}

void TStorageMonitorThriftHandler::openStorage(const std::string& stgCreateOption)
{
    if (_storage)
    {
        //openstars::storage::KVStorageFactory aFactory;
//        std::string aName;
//        int rwOption = 0;
//        openstars::storage::AbstractKVStorage* aStg = aFactory.createStorage(stgCreateOption, aName, rwOption);
//        if (aStg){
//            _storage->removeStorage(aName);
//            _storage->addStorage(aName, aStg);
//            _storage->enableStorage(aName, true, openstars::storage::TOperations(rwOption) );
//        }
    } 
} 
