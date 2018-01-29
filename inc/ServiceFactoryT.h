/*
 * File:   SessionFactory.h
 * Author: trungthanh
 *
 * Created on February 27, 2011, 10:49 AM
 * Updated on Otc 04 2012
 */

#ifndef STORE_APP_SERVICEFACTORY_H
#define	STORE_APP_SERVICEFACTORY_H

#include "Poco/Util/Application.h"
#include "Poco/StringTokenizer.h"
#include "Poco/NumberFormatter.h"

#include "Storage/MultiKVStorage.h"
#include "Storage/AbstractKVStorage.h"
#include "Storage/KVStorageFactory.h"
#include "Storage/EvictProcessors.h"
#include "monitor/TBackendLog.h"
#include "PocoEx/NetUtil.h"

#include <iostream>

#include "monitor/ServiceStatFetcher.h"



#define service_factory_tmpl template <class CacheType, class CacheFactoryType, class ObjectStgType, class PersistentType, class ModelType>
#define service_factory_clss ServiceFactoryT<CacheType, CacheFactoryType, ObjectStgType, PersistentType, ModelType>

service_factory_tmpl
class ServiceFactoryT {
private:

public:
    static void init(Poco::Util::Application& app
        ,const std::string& configKeyThriftServicePort = "sns.thrift.port"
        ,const std::string& configKeyThriftCfgPort = "sns.thrift.config.port"

        ,const std::string& configKeyICacheOption = "sns.icache" // hash table size
        ,const std::string& configKeySecondCacheEnable = "sns.secondcache.enable" // hash table size
        ,const std::string& configKeySecondCacheOption = "sns.secondcache" // hash table size
        ,const std::string& configKeyStorages = "sns.storages" // storages 

        ,const std::string& configKeyReadDataStorage = "sns.storage.read"
        ,const std::string& configKeyWriteDataStorage = "sns.storage.write"

        ,const std::string& configKeyServiceName = "sns.service.name"    
    
    );

    static Poco::SharedPtr<CacheType> getCache();
    static Poco::SharedPtr<CacheType> getSecondCache(); // cache using in dumping
    static Poco::SharedPtr<ObjectStgType> getBEStorage();
    static Poco::SharedPtr<PersistentType> getStorage();
    static Poco::SharedPtr<openstars::storage::MultiKVStorage> getKVStorage();
    static Poco::SharedPtr<ModelType> getModel();   
    static Poco::SharedPtr<ServiceStatFetcher> getStatFetcher();

protected:
    static void initStorages(Poco::Util::Application& app,const std::string& configName);
    static void initStorage(Poco::Util::Application& app,const std::string& configName, int stgIndex);
	
	/**
	 * Create storages from semicolon separated configuration strings
	 * 
     * @param configStrings 
     */
	static void initStorages(const std::string& configStrings);
	/**
	 * Create storage by StorageFactory from a configuration string
	 * 
     * @param configString comma separated name=value pair.
	 * Required parameters:
	 * - name
	 * - type (accepted values: remote | zdb2 | kc | leveldb)
	 * 
	 * More specific parameters depend on storage type.
	 * 
	 * Examples:
	 * name=zdb2,type=zdb2,partitions=4,env=/data/zdb2_data/updb/,dbname=updb,tabletype=I64GTable,appendonly=0,reservedsize=1024
	 * name=remote,type=remote,host=127.0.0.1,port=5678
	 * name=kc,type=kc,path=/tmp/kc,baseName=test,dbType=.kch,partitions=1,dbOptions=#abc=45#def=3
	 * name=leveldb,type=leveldb,path=/tmp/leveldb,baseName=test,partitions=1
     */
	static void initStorage(const std::string& configString);

public:
    static int _svrPort;
    static std::string _svrHost;
    static int _recoveryPort;
    static int _cfgPort;
    static int _workerCount;
    static int _savingThread;
    static int _warmingThread;

    static std::string _cacheOption;
    static std::string _secondCacheOption;
    
    static bool _enableSecondCache; // for dumping, not supported yet (doit later)
    
    static std::string _serviceName;
    static int _enableAsyncVisist;
    
    /*
     * for save flushing dirty evicted key-value
     */
    static int _enableSafeAsyncWrite;
    
   
    static std::string _zkServers;
    static std::string _zkRegPath;
    static std::string _zkScheme;
    static bool smartSaving;
    static int smartSavingThreshold;
    
};

service_factory_tmpl
int service_factory_clss ::_svrPort = 0;

service_factory_tmpl
std::string service_factory_clss ::_svrHost;

service_factory_tmpl
int service_factory_clss ::_recoveryPort = 0;

service_factory_tmpl
int service_factory_clss ::_cfgPort = 0;

service_factory_tmpl
int service_factory_clss ::_workerCount = 5;

service_factory_tmpl
int service_factory_clss ::_savingThread = 1;

service_factory_tmpl
int service_factory_clss ::_warmingThread = 1;

service_factory_tmpl
std::string service_factory_clss::_cacheOption=""; // hash table size of icache

service_factory_tmpl
std::string service_factory_clss::_secondCacheOption=""; // hash table size of icache

    
service_factory_tmpl
bool service_factory_clss::_enableSecondCache = true; // for dumping

service_factory_tmpl
int service_factory_clss ::_enableAsyncVisist = 0;

service_factory_tmpl
int service_factory_clss ::_enableSafeAsyncWrite = 0;

service_factory_tmpl
std::string service_factory_clss::_serviceName = "NonameService";

service_factory_tmpl
std::string service_factory_clss:: _zkServers;

service_factory_tmpl
std::string service_factory_clss:: _zkRegPath;

service_factory_tmpl
std::string service_factory_clss:: _zkScheme;

service_factory_tmpl
bool service_factory_clss::smartSaving = false;

service_factory_tmpl
int service_factory_clss::smartSavingThreshold = 20000;


service_factory_tmpl
void service_factory_clss::init(Poco::Util::Application& app
        ,const std::string& configKeyThriftServicePort //= "sns.thrift.port"
        ,const std::string& configKeyThriftCfgPort //= "sns.thrift.config.port"

        ,const std::string& configKeyICacheOption// = "sns.icache" // hash table size
        ,const std::string& configKeySecondCacheEnable// = "sns.secondcache.enable" // hash table size
        ,const std::string& configKeySecondCacheOption //= "sns.secondcache" // hash table size

        ,const std::string& configKeyStorages //= "sns.storages" // storages 

        ,const std::string& configKeyReadDataStorage //= "sns.storage.read"
        ,const std::string& configKeyWriteDataStorage //= "sns.storage.write"

        ,const std::string& configKeyServiceName //= "sns.service.name"

) {
    if (_svrPort <= 0)
        _svrPort = app.config().getInt(configKeyThriftServicePort, 8303);
    std::cout<<"service port:"<<_svrPort<<std::endl;
    
    if(_svrHost.length() == 0)
        _svrHost = app.config().getString("sns.thrift.host" , "");
    if (!NetUtil::hasIPInThisHost(_svrHost))
    {
        std::vector<std::string> ips;
        if (_svrHost.length() > 0)
                NetUtil::getHostIPAddr(_svrHost, ips);
        else
            NetUtil::getHostIPAddr("10.", ips);
        if (ips.size() > 0)
            _svrHost = ips[0];
        else _svrHost = "127.0.0.1";
        
    }
    std::cout << "please check host :" <<_svrHost << std::endl;
    
    if (_recoveryPort <=0 )
        _recoveryPort = app.config().getInt("sns.thrift.recovery.port" , 0);
    std::cout<<"recovery port:"<<_recoveryPort <<std::endl;
    
    if (_cfgPort <= 0)
        _cfgPort = app.config().getInt(configKeyThriftCfgPort, 8304);
    std::cout<<"config port:"<<_cfgPort<<std::endl;

    if (_workerCount == 5)
        _workerCount = app.config().getInt("sns.thrift.service.workercount" , 5);
    std::cout<<"worker count: "<<_workerCount<<std::endl;
    
    if (_cacheOption.length() == 0)
        _cacheOption = app.config().getString(configKeyICacheOption , "");
    
    _enableSecondCache = app.config().getBool(configKeySecondCacheEnable, _enableSecondCache); // for dumping
    
    _secondCacheOption = app.config().getString(configKeySecondCacheOption, ""); // cache using when dumping data
    
    _enableAsyncVisist = app.config().getInt("sns.storage.async_visit", 1);  
    
    if (_enableAsyncVisist)
        _enableSafeAsyncWrite = app.config().getInt("sns.storage.safe_async_visit", 0);  
    
    std::cout<<"_enableAsyncVisist:"<<_enableAsyncVisist<<" _enableSafeAsyncWrite:" <<_enableSafeAsyncWrite<<std::endl;
    //////
    
    if (_savingThread == 1)
        _savingThread = app.config().getInt("sns.cachepersistent.savingthread",1);
    if (_warmingThread == 1)
        _warmingThread = app.config().getInt("sns.cachepersistent.warmingthread",1);

    _serviceName = app.config().getString(configKeyServiceName , "NoNameService");
    
    initStorages(app, configKeyStorages);

    const std::string aReadStorageNames = app.config().getString(configKeyReadDataStorage, "");
    Poco::StringTokenizer aReadTkn(aReadStorageNames, ", ;");
    for (size_t aIndex = 0; aIndex < aReadTkn.count(); aIndex++) {
        app.logger().information("Enable Read to " + aReadTkn[aIndex]);
        getKVStorage()->enableStorage(aReadTkn[aIndex], true, openstars::storage::ERead);

    }

    const std::string aWriteStorageNames = app.config().getString(configKeyWriteDataStorage, "");
    Poco::StringTokenizer aWriteTkn(aWriteStorageNames, ", ;");
    for (size_t aIndex = 0; aIndex < aWriteTkn.count(); aIndex++) {
        app.logger().information("Enable Write to " + aWriteTkn[aIndex]);
        getKVStorage()->enableStorage(aWriteTkn[aIndex], true, openstars::storage::EWrite);

    }
    ///////zookeeper options
    if (_zkServers.length() == 0)
        _zkServers  =  app.config().getString("sns.service.zkservers", "127.0.0.1:2181");
    if (_zkRegPath.length() == 0)
        _zkRegPath = app.config().getString("sns.service.reg_path" , "/up-division/noconfig/services");
    if (_zkScheme.length() == 0)
        _zkScheme = app.config().getString("sns.service.scheme" , "notset_scheme");

    smartSaving = app.config().getBool("sns.service.smartsaving.enable", false);
    
    smartSavingThreshold = app.config().getInt("sns.service.smartsaving.threshold", 20000);
    
}

service_factory_tmpl
Poco::SharedPtr<CacheType> service_factory_clss::getCache() {
    static Poco::SharedPtr<CacheType> aCache;
    if (!aCache) {
        CacheFactoryType aFactory;
        aCache = aFactory.createCache(_cacheOption);//new CacheType(_icacheMaxSize, _icacheTableSize, _icacheLockSet, _icacheLockSetSize);
    }
    return aCache;
}

service_factory_tmpl
Poco::SharedPtr<CacheType> service_factory_clss::getSecondCache() {
    if (!_enableSecondCache)
	return Poco::SharedPtr<CacheType>();
    
    static Poco::SharedPtr<CacheType> aSecondCache;
    if (!aSecondCache) {
        CacheFactoryType aFactory;
        aSecondCache = aFactory.createCache(_secondCacheOption);//new CacheType(_icacheMaxSize, _secondCacheTableSize, _secondCacheLockSet, _secondCacheLockSetSize);
    }
    return aSecondCache;
}




service_factory_tmpl
Poco::SharedPtr<ObjectStgType> service_factory_clss::getBEStorage() {
    static Poco::SharedPtr<ObjectStgType> aBEStg;
    if (!aBEStg) {
        aBEStg = new ObjectStgType(service_factory_clss::getKVStorage());
    }
    return aBEStg;
}

service_factory_tmpl
Poco::SharedPtr<PersistentType> service_factory_clss::getStorage() {
    static Poco::SharedPtr<PersistentType> aPersistentStorage;
    if (!aPersistentStorage) {
        aPersistentStorage = new PersistentType(getCache(), getSecondCache(), getBEStorage() );
        if (_enableSafeAsyncWrite > 0) {
                aPersistentStorage -> setEvictProcessor(
                new openstars::storage::SafeEvictProcessor<typename PersistentType::TKey,typename PersistentType::TValue> );
                
                getCache()->startEvict();
        }
        aPersistentStorage->setNumSavingThread(_savingThread);
        aPersistentStorage->setNumWarmingThread(_warmingThread);
        aPersistentStorage->setSmartSaving(smartSaving);
        aPersistentStorage->setSmartSavingThreshold(smartSavingThreshold);
        std::cout<<"_savingThread: "<<_savingThread << " ; _warmingThread:"<<_warmingThread<<std::endl;
        std::cout<<"smartSaving:"<<smartSaving<<" smartSavingThreshold:"<<smartSavingThreshold<<std::endl;
    }
    return aPersistentStorage;
}

service_factory_tmpl
Poco::SharedPtr<openstars::storage::MultiKVStorage> service_factory_clss::getKVStorage() {
    static Poco::SharedPtr<openstars::storage::MultiKVStorage> aKVStg;
    if (!aKVStg) {
        aKVStg = new openstars::storage::MultiKVStorage();
    }
    return aKVStg;
}


service_factory_tmpl
Poco::SharedPtr<ModelType> service_factory_clss::getModel() {
    static Poco::SharedPtr<ModelType> aModel;
    if (!aModel) {
        aModel = new ModelType(getStorage());
    }
    return aModel;
}

service_factory_tmpl
void service_factory_clss::initStorages(Poco::Util::Application& app,const std::string& configName){
    int storageCount = app.config().getInt(configName + ".numstore" , 0);
    std::cout<<"numstore: "<<storageCount<<std::endl;
    for (int aIndex = 0 ; aIndex< storageCount ; aIndex ++ ){
         initStorage(app, configName+ ".store" , aIndex);
    }
}

service_factory_tmpl
void service_factory_clss::initStorage(Poco::Util::Application& app,const std::string& configName, int stgIndex){
    std::string aCfgKey;
    if (stgIndex > 0)
        aCfgKey = configName + "[" + Poco::NumberFormatter::format(stgIndex) + "]";
    else aCfgKey = configName;
    std::string aStgConfig = app.config().getString(aCfgKey, "");
    if (aStgConfig.length() > 0 ){
        initStorages(aStgConfig);
    }

}

service_factory_tmpl
void service_factory_clss::initStorages(const std::string& configStrings) {
	Poco::StringTokenizer tknz(configStrings, ";", Poco::StringTokenizer::TOK_IGNORE_EMPTY | Poco::StringTokenizer::TOK_TRIM);
	Poco::StringTokenizer::Iterator it;
	for (it = tknz.begin(); it != tknz.end(); ++it) {
		initStorage(*it);
	}
}

service_factory_tmpl
void service_factory_clss::initStorage(const std::string& configString) {
	std::string name;
	int rwmode;
    openstars::storage::KVStorageFactory aFactory;
    openstars::storage::AbstractKVStorage::Ptr stg = aFactory.createStorage(configString, name, rwmode);	
    if (getKVStorage()->getStorage(name).get() !=  NULL)
    {
        //existed, abort 
	return;
    }
    std::cout<<"initializing storage for : "<<configString<<" with parsed name:"<<name<<std::endl;
    getKVStorage()->addStorage(name, stg);
    std::cout<<"ok1"<<std::endl;
    getKVStorage()->enableStorage(name, true, (openstars::storage::TOperations)rwmode );
    std::cout<<"ok"<<std::endl;
}

service_factory_tmpl
Poco::SharedPtr<ServiceStatFetcher> service_factory_clss::getStatFetcher(){
    static Poco::SharedPtr<ServiceStatFetcher> aFetcher;
    if (!aFetcher){
        aFetcher = ServiceStatFetcher::createFetcher(
                *service_factory_clss::getCache()
                , *service_factory_clss::getStorage()
                , *service_factory_clss::getKVStorage()
                );
    }
    return aFetcher;
}

#endif	/* SERVICEFACTORY_H */

