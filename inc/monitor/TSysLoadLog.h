#ifndef TSYSLOADLOG_H
#define	TSYSLOADLOG_H

#include "TDayStat.h"
#include "PocoEx/TimeUtils.h"
#include "Poco/Event.h"

struct sysloadLog {
    
    TDayStat<boost::atomic_uint32_t, uint32_t> load1m;
    TDayStat<boost::atomic_uint32_t, uint32_t> load5m;
    TDayStat<boost::atomic_uint32_t, uint32_t> load15m;
    
    
    sysloadLog() {
        load1m.clear();
        load5m.clear();
        load15m.clear();        
    }
};

class TSysLoadLog {
public:
    TSysLoadLog(){}
    virtual ~TSysLoadLog(){}
    
    void log (long long load1m, long long load5m, long long load15m, int seconds) {
        _sysloadLog.load1m.set(seconds, load1m);
        _sysloadLog.load5m.set(seconds, load5m);
        _sysloadLog.load15m.set(seconds, load15m);
    }
    
    void log (long long load1m, long long load5m, long long load15m) {
        log(load1m, load5m, load15m, TimeUtils::getCurrentSeconds());
    }
    
    sysloadLog& getData() {
        return _sysloadLog;
    }
    
private:
    sysloadLog _sysloadLog;
};

#endif	/* TSYSLOADLOG_H */

