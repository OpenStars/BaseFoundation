/* 
 * File:   StorageFactory.h
 * Author: trungthanh
 *
 * Created on October 14, 2014, 1:34 PM
 */

#ifndef STORE_APP_STORAGEFACTORY_H
#define	STORE_APP_STORAGEFACTORY_H


#include "Poco/Util/Application.h"
#include "Poco/StringTokenizer.h"
#include "Poco/NumberFormatter.h"

#include "Storage/MultiKVStorage.h"
#include "Storage/AbstractKVStorage.h"
#include "Storage/AbstractStorageFactory.h"
#include "monitor/TBackendLog.h"
#include "PocoEx/NetUtil.h"

#include <iostream>

#include "SimpleServiceFactory.h"

class StorageFactory: public SimpleServiceFactory {
public:
    using SimpleServiceFactory::svrPort;
    using SimpleServiceFactory::svrHost;
    using SimpleServiceFactory::zkHosts;
    using SimpleServiceFactory::zkPath;
public:
    static void init(Poco::Util::Application& app
        ,const std::string& configKeyStorages = "sns.storages" // storages 
        , AbstractStorageFactory* aFactory = NULL
    )
    {
        initStorages(app, configKeyStorages);
        SimpleServiceFactory::init(app);
        _kvFactory = aFactory;
    }

    
    static Poco::SharedPtr<openstars::storage::MultiKVStorage> getKVStorage();
    
    static AbstractStorageFactory* _kvFactory;
    
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
};

inline Poco::SharedPtr<openstars::storage::MultiKVStorage> StorageFactory::getKVStorage() {
    static Poco::SharedPtr<openstars::storage::MultiKVStorage> aKVStg;
    if (!aKVStg) {
        aKVStg = new openstars::storage::MultiKVStorage();
    }
    return aKVStg;
}


inline void StorageFactory::initStorages(Poco::Util::Application& app,const std::string& configName){
    int storageCount = app.config().getInt(configName + ".numstore" , 0);
    std::cout << "numstore: " << storageCount << std::endl;
    for (int aIndex = 0 ; aIndex< storageCount ; aIndex ++ ){
         initStorage(app, configName+ ".store" , aIndex);
    }
}


inline void StorageFactory::initStorage(Poco::Util::Application& app,const std::string& configName, int stgIndex){
    std::string aCfgKey;
    if (stgIndex > 0)
        aCfgKey = configName + "[" + Poco::NumberFormatter::format(stgIndex) + "]";
    else aCfgKey = configName;
    std::string aStgConfig = app.config().getString(aCfgKey, "");
    if (aStgConfig.length() > 0 ){
        initStorages(aStgConfig);
    }

}


inline void StorageFactory::initStorages(const std::string& configStrings) {
	Poco::StringTokenizer tknz(configStrings, ";", Poco::StringTokenizer::TOK_IGNORE_EMPTY | Poco::StringTokenizer::TOK_TRIM);
	Poco::StringTokenizer::Iterator it;
	for (it = tknz.begin(); it != tknz.end(); ++it) {
		initStorage(*it);
	}
}


inline void StorageFactory::initStorage(const std::string& configString) {
	std::string name;
	int rwmode;
        if (_kvFactory)
        {
            openstars::storage::AbstractKVStorage::Ptr stg = _kvFactory->createStorage(configString, name, rwmode);	
            if (getKVStorage()->getStorage(name).get() !=  NULL)
            {
                //existed, abort 
                return;
            }
            getKVStorage()->addStorage(name, stg);
            getKVStorage()->enableStorage(name, true, (openstars::storage::TOperations)rwmode );
        }
}

#endif	/* STORAGEFACTORY_H */

