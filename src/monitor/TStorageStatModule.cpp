/* 
 * File:   TStorageStatModule.cpp
 * Author: trungthanh
 * 
 * Created on October 4, 2012, 4:25 PM
 */

#include "monitor/TStorageStatModule.h"
#include "PocoEx/TimeUtils.h"
#include "monitor/TStorageMonitorThriftHandler.h"

using namespace Poco::Util;

TStorageStatModule* TStorageStatModule::_storageinstance = NULL;
TStorageStatModule::TStorageStatModule(): _backendLog()
,_backendLogCollector(NULL)
,_fetcher(NULL){
}


TStorageStatModule::~TStorageStatModule() {
    delete _backendLogCollector;
}


TStorageStatModule& TStorageStatModule::getInstance() {
    if (_storageinstance) {
        return *_storageinstance;
    }
    throw "Instance Error!";
}

void TStorageStatModule::initialize(Application &app){
    StatSubsystem::initialize(app);
    _storageinstance = this;
    _backendLogCollector = new TBackendLogCollector(_backendLog);
    if (_fetcher)
        _backendLogCollector->setFetcher(_fetcher);
    _backendLogCollector->start();
    
}

void TStorageStatModule::uninitialize(){
    if (_backendLogCollector){
        _backendLogCollector->stop();
        delete _backendLogCollector;
        _backendLogCollector = NULL;
    }
    StatSubsystem::uninitialize();
}

void TStorageStatModule::setStatusFetcher(ServiceStatFetcher* aFetcher){
    _fetcher = aFetcher;
    if (_backendLogCollector)
        _backendLogCollector->setFetcher(_fetcher);
}

void TStorageStatModule::hitCache(Poco::Int64 execTime , bool isWrite){
    int seconds = TimeUtils::getCurrentSeconds();

    if (isWrite)
        _backendLog.addWriteCounts(seconds, 0, 1, 0, execTime );
    else
        _backendLog.addReadCounts(seconds, 0, 1, 0, execTime );
    
    _backendLog.addCacheCounter(seconds, 1 , 0);
}

void TStorageStatModule::missedCache(Poco::Int64 execTime , bool isWrite) {
    int seconds = TimeUtils::getCurrentSeconds();
    _backendLog.addCacheCounter(seconds, 0, 1);
}

void TStorageStatModule::hitPersistent(Poco::Int64 execTime , bool isWrite) {
    int seconds = TimeUtils::getCurrentSeconds();
    if (isWrite)
        _backendLog.addWriteCounts(seconds, 0, 0, 1, execTime);
    else 
        _backendLog.addReadCounts(seconds, 0, 0, 1, execTime);
        
}

void TStorageStatModule::addCount(int count, bool isWrite)
{
    int seconds = TimeUtils::getCurrentSeconds();
    if (isWrite)
        _backendLog.addWriteCounts(seconds, count, 0, 0, 0);
    else
        _backendLog.addReadCounts(seconds, count, 0, 0, 0);
}
