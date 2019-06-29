namespace cpp openstars.distributed
namespace java openstars.distributed


exception TDeadBackend{
    1: i32 error,
    2: string host,
    3: i32 port
    4: string message
}

typedef i64 THashType
typedef i64 TSyncTransactionIDType

// status when moving data from a node to new not
struct TDataMovingStatus{
    1: THashType fromHash,
    2: THashType toHash,
    3: i64 totalItem,   
    4: i64 numChecked,
    5: i64 numMoved,
    6: bool running,
}

enum TProtocolType{
    EUnknown = 0,
    EBinaryProtocol = 1,
    ECompactProtocol = 2,
    EMemcacheProtocol = 3,
    EHTTPProtocol = 4,
    EWebsocketProtocol = 5,
    ERawTCPProtocol = 6,
    EGrpc=10,
    EGrpcWeb,
    
}

enum TBackendStatus{
    EReady = 1,
    EInActiveForAdding = 2, // data is moving from next node to this node
    EInActiveForRemoving = 3, // data is moving from this node to prev node in the ring
    EReadyRemove = 4
}

struct TBackendInfo{
    1: string host,
    2: i32 port,
    3: THashType startRange,
    4: i32 weight,
    5: TBackendStatus status,
    6: string servicePath, // all service in cluster must have the same path
   
}

service TNodeServiceBase{
    i32 iPing(1:i32 value), 

    // must return the same value to tell that service is still alive
    // anything to detect work load? // minutely , hourly, daily rw count...
    // QT GUI software to monitor services
    
     TSyncTransactionIDType startSyncTo(1:TBackendInfo desNode),
     
     TDataMovingStatus getSyncStatus(1: TSyncTransactionIDType tid),

     

}

service TBackendManagerService{

    list<TBackendInfo> getBackends(),

    list<TBackendInfo> getBEWrite(1:string key),

    list<TBackendInfo> getBERead(1:string key),

    void addBackend(1:TBackendInfo aNode),

    // change status, weight
    void updateBackend(1:TBackendInfo aNode),

    void removeBackend(1:TBackendInfo aNode),

}

service TP2PService extends TBackendManagerService{

}