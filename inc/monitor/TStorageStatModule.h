/*
 * File:   TStorageStatModule.h
 * Author: trungthanh
 *
 * Created on October 4, 2012, 4:25 PM
 */

#ifndef TSTORAGESTATMODULE_H
#define	TSTORAGESTATMODULE_H

#include "StatSubsystem.h"
#include <monitor/TBackendLog.h>
#include <Storage/CachePersistentBase.h>



class TStorageStatModule : public StatSubsystem, public openstars::storage::CachePersistentObserver{
public:
    virtual const char* name() const { return "TStorageStatModuleSubsystem";};
    virtual void initialize(Poco::Util::Application& );
    virtual void uninitialize();

public:
    static TStorageStatModule& getInstance();

public:
    TStorageStatModule();
    virtual ~TStorageStatModule();
public:
    void setStatusFetcher(ServiceStatFetcher* aFetcher);
    
    TBackendLog& getBackendLog(){
        return _backendLog;
    }

public:
    void addCount(int count, bool isWrite);
    
protected:
    //Overrides from CachePersistentObserver
    virtual void hitCache(Poco::Int64 execTime , bool isWrite) ;
    virtual void missedCache(Poco::Int64 execTime , bool isWrite) ;
    virtual void hitPersistent(Poco::Int64 execTime , bool isWrite);
        
private:
    static TStorageStatModule*    _storageinstance ;
    TStorageStatModule(const TStorageStatModule& orig);
protected:
    TBackendLog _backendLog;
    TBackendLogCollector * _backendLogCollector;
    ServiceStatFetcher* _fetcher;

};

#endif	/* TSTORAGESTATMODULE_H */

