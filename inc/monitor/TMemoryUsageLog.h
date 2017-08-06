
#ifndef TMEMORYUSAGELOG_H
#define	TMEMORYUSAGELOG_H

#include "TDayStat.h"
#include "PocoEx/TimeUtils.h"

#include "Poco/Event.h"

#define TOTALSECS 60*60*24

struct memoryUsageLog {
    
    TDayStat<boost::atomic_uint64_t, uint64_t> totalMem;
    TDayStat<boost::atomic_uint64_t, uint64_t> freeMem;    
    TDayStat<boost::atomic_uint64_t, uint64_t> usedMem;
    TDayStat<boost::atomic_uint64_t, uint64_t> cacheMem;
    
    memoryUsageLog() {
        totalMem.clear();
        freeMem.clear();
        usedMem.clear();
        cacheMem.clear();        
    }
};

class TMemoryUsageLog {
public:
    TMemoryUsageLog(){};
    virtual ~TMemoryUsageLog(){};
    
    void log (long long total, long long free, long long used, long long cache, int seconds) {
        _memoryLog.totalMem.set(seconds, total);
        _memoryLog.freeMem.set(seconds, free);
        _memoryLog.usedMem.set(seconds, used);
        _memoryLog.cacheMem.set(seconds, cache);        
    }
    
    void log(long long total, long long free, long long used, long long cache) {
        log(total, free, used, cache, TimeUtils::getCurrentSeconds());
    }
    
    memoryUsageLog& getData() {
        return _memoryLog;
    }
    
private:
    memoryUsageLog _memoryLog;
};


#endif	/* TMEMORYUSAGELOG_H */

