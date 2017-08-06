namespace cpp openstars.base.storage.monitor
namespace java openstars.base.storage.monitor
namespace php Monitor

include "monitor.thrift"

struct cacheStat{
    1: string cacheType,
    2: i64 cacheMaxSize,
    3: i64 cacheSize,
    4: i64 cacheHit,
    5: i64 cacheMiss
    6: i64 cacheMemSize, // estimate size of internal cache
}

struct opStat{
    1: i64 operationCount,
    2: i64 cacheHit,
    3: i64 persistentHit // zdb or remote or kyoto ...
    4: i64 excuteTime;
}

/*disk base storage stat*/
struct storageStat{ 
    1: i64 count,
    2: i64 sizeKb,
    3: i64 minSizeKb, //size after compact
}

/* cache - storage stat */
struct backendStat{
    1: cacheStat cache,
    2: i64 savingQueueSize,
    3: i64 warmingQueueSize,
    4: opStat readStat,
    5: opStat writeStat,
    6: list<string> writeStorage,
    7: list<string> readStorage,
    8: i64 processMemKb,
    9: i64 processVirtKb,
    10: map<string, storageStat> storages
}


/**/
service StorageMonitorService extends monitor.MonitorReadService{
    backendStat getCurrentCacheStorageStat(),

    backendStat getCacheStorageStat(1:i32 seconds),

    void enableStorageBackend(1:bool isRead, 2: bool isEnable, 3:string beName),

    void setCacheMaxSize(1:i32 newMaxSize),

    //start flush data from cache to persistent storage
    void saveDataToBackend(1:bool enable),

    //enable / disable warming
    void enableWarming(1: bool enable),

    //compact data - for services using zdb/zdb2...
    void compactData(1: string storageName),

    // close a key/value storage
    void closeStorage(1:string stgName),

    ///Open new db on the fly. param is open option of a db
    void openStorage(1:string stgCreateOption),

    string getZKServicePath(),
    
    string getZKConfigPath(),

    void checkZKService(),

    void checkZKConfigPath(),

    void registerServiceZK(1:string basePath, 2:string scheme),

    void registerConfigZK(1:string basePath, 2:string scheme),

    void addListenServicePort(1:i32 newPort),
}
