#ifndef TDISKSPEEDLOG_H
#define	TDISKSPEEDLOG_H

#include "TDayStat.h"
#include "PocoEx/TimeUtils.h"
#include <map>
#include "Poco/Mutex.h"
#include "Poco/Event.h"
#include "Poco/Thread.h"


#define TOTALSECS 60*60*24

struct diskSpeedLog {
    TDayStat<boost::atomic_uint32_t, uint32_t> rSpeedLog;
    TDayStat<boost::atomic_uint32_t, uint32_t> wSpeedLog;
    
    diskSpeedLog() {
        rSpeedLog.clear();
        wSpeedLog.clear();        
    }
};


struct dsSpeed {
  uint32_t rx;
  uint32_t wx;
};

typedef std::map<std::string, dsSpeed> dssSpeed;

class TDiskSpeedLog {
public:
    TDiskSpeedLog() {};
    virtual ~TDiskSpeedLog() {}
    
    void log(const std::string& iface, long long rs, long long ws, int seconds) {
        Poco::FastMutex::ScopedLock _lock(mutex);
        
        // check device 
        if (cardLog.find(iface) == cardLog.end()) {
            // empty
            diskSpeedLog* ilog = new diskSpeedLog();
            cardLog[iface] = ilog;
        }
        
        // store values
        diskSpeedLog* ilog = cardLog[iface];
        
        if (seconds < TOTALSECS) {
            ilog->rSpeedLog.set(seconds, rs);
            ilog->wSpeedLog.set(seconds, ws);
        }        
    }
    
    /**
     * Log netstat to store 
     * 
     * @param iface
     * @param rs
     * @param ss
     */
    void log(const std::string& iface, long long rs, long long ws) {
        log(iface, rs, ws, TimeUtils::getCurrentSeconds());
    }
    
    void getDssSpeed(int seconds, dssSpeed& dss) {
        Poco::FastMutex::ScopedLock _lock(mutex);
        
        for (std::map<std::string, diskSpeedLog*>::iterator it = cardLog.begin(); it != cardLog.end(); it++) {
            dsSpeed if_;
            if_.rx = it->second->rSpeedLog[seconds];
            if_.wx = it->second->wSpeedLog[seconds];
            
            dss[it->first] = if_;            
        }
    }

    
private:
    std::map<std::string, diskSpeedLog*> cardLog;
    Poco::FastMutex mutex;
};



#endif	/* TDISKSPEEDLOG_H */

