
#ifndef TCPUUSAGELOG_H
#define	TCPUUSAGELOG_H


#include "TDayStat.h"
#include "PocoEx/TimeUtils.h"
#include "Poco/Event.h"

#define TOTALSECS 60*60*24

struct cpuUsageLog {
    
    TDayStat<boost::atomic_uint32_t, uint32_t> userCPU;
    TDayStat<boost::atomic_uint32_t, uint32_t> kernelCPU;
    TDayStat<boost::atomic_uint32_t, uint32_t> idleCPU;
    TDayStat<boost::atomic_uint32_t, uint32_t> iowaitCPU;
    TDayStat<boost::atomic_uint32_t, uint32_t> swapCPU;
    TDayStat<boost::atomic_uint32_t, uint32_t> niceCPU;
    TDayStat<boost::atomic_uint32_t, uint32_t> totalCPU;
    
    
    cpuUsageLog() {
        userCPU.clear();
        kernelCPU.clear();
        idleCPU.clear();
        iowaitCPU.clear();
        swapCPU.clear();
        niceCPU.clear();
        totalCPU.clear();
    }
};

/**
 * CPULog
 * 
 */
class TCpuUsageLog {
public:
    TCpuUsageLog() {};
    virtual ~TCpuUsageLog() {};
        
    void log (long long user, long long kernel, long long idle, long long iowait, long long swap, long long nice, long long total, int seconds) {
        _cpuLog.kernelCPU.set(seconds, kernel);
        _cpuLog.userCPU.set(seconds, user);
        _cpuLog.idleCPU.set(seconds, idle);
        _cpuLog.iowaitCPU.set(seconds, iowait);
        _cpuLog.swapCPU.set(seconds, swap);
        _cpuLog.niceCPU.set(seconds, nice);
        _cpuLog.totalCPU.set(seconds, total);
    }
    
    void log (long long user, long long kernel, long long idle, long long iowait, long long swap, long long nice, long long total) {
        log(user, kernel, idle, iowait, swap, nice, total, TimeUtils::getCurrentSeconds());
    }
    
    cpuUsageLog& getData() {
        return _cpuLog;
    }
    
private:
    cpuUsageLog _cpuLog;
    
};



#endif	/* TCPUUSAGELOG_H */

