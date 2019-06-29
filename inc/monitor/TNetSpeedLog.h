
#ifndef TNETSPEEDLOG_H
#define	TNETSPEEDLOG_H

#include <map>
#include "TDayStat.h"
#include "PocoEx/TimeUtils.h"

#include "Poco/Event.h"
#include "Poco/Mutex.h"

#define TOTALSECS 60*60*24

struct speedLog {
    TDayStat<boost::atomic_uint32_t, uint32_t> rSpeedLog;
    TDayStat<boost::atomic_uint32_t, uint32_t> sSpeedLog;

    
    speedLog() {
        rSpeedLog.clear();
        sSpeedLog.clear();        
    }
};

struct ifSpeed {
  uint32_t rx;
  uint32_t sx;
};

typedef std::map<std::string, ifSpeed> ifsSpeed;


/**
 * Log Storage
 */
class TNetSpeedLog {
public:
    TNetSpeedLog(){}
    virtual ~TNetSpeedLog(){}
    
    void log(const std::string& iface, long long rs, long long ss, int seconds) {
        Poco::FastMutex::ScopedLock _lock(mutex);
        
        // check iface 
        if (cardLog.find(iface) == cardLog.end()) {
            // empty
            speedLog* ilog = new speedLog();
            cardLog[iface] = ilog;
        }
        
        // store values
        speedLog* ilog = cardLog[iface];
        
        if (seconds < TOTALSECS) {
            ilog->rSpeedLog.set(seconds, rs);
            ilog->sSpeedLog.set(seconds, ss);
        }        
    }
    
    /**
     * Log netstat to store 
     * 
     * @param iface
     * @param rs
     * @param ss
     */
    void log(const std::string& iface, long long rs, long long ss) {
        log(iface, rs, ss, TimeUtils::getCurrentSeconds());
    }

    /**
     * Get current speed
     * 
     * @param seconds
     * @param ifs
     */
    void getIfsSpeed(int seconds, ifsSpeed& ifs) {
        Poco::FastMutex::ScopedLock _lock(mutex);
        
        for (std::map<std::string, speedLog*>::iterator it = cardLog.begin(); it != cardLog.end(); it++) {
            ifSpeed if_;
            if_.rx = it->second->rSpeedLog[seconds];
            if_.sx = it->second->sSpeedLog[seconds];
            
            ifs[it->first] = if_;            
        }
    }
private:
    std::map<std::string, speedLog*> cardLog;
    Poco::FastMutex mutex;
};



#endif	/* TNETSPEEDLOG_H */

