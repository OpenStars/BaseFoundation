
#ifndef TSTATMODULE_H
#define	TSTATMODULE_H

#include "TCpuUsageLog.h"
#include "TMemoryUsageLog.h"
#include "TSysLoadLog.h"
#include "TDiskSpeedLog.h"
#include "TNetSpeedLog.h"
#include "Poco/Util/Subsystem.h"

#include <thread>


class StatSubsystem : public Poco::Util::Subsystem {
public:
    StatSubsystem();
    virtual ~StatSubsystem();

    virtual const char* name() const { return "StatModuleSubsystem";};
    virtual void initialize(Poco::Util::Application& );
    virtual void uninitialize();
    virtual void reinitialize(Poco::Util::Application& );
    
    static StatSubsystem& getInstance();
    void printStat(std::ostream& output);


    TCpuUsageLog& getCPULog() {
        return _cpuLog;
    }
    
    TMemoryUsageLog& getMemoryUsageLog() {
        return _memoryLog;
    }
    
    TSysLoadLog& getSysLoadLog() {
        return _sysloadLog;
    }
    
    TDiskSpeedLog& getDiskSpeedLog() {
        return _diskspeedLog;
    }
    
    TNetSpeedLog& getNetSpeedLog() {
        return _netspeedLog;
    }
    
    
private:
    StatSubsystem(const StatSubsystem& orig);
    
    static StatSubsystem*    _instance;
    
    TCpuUsageLog _cpuLog;
    
    TMemoryUsageLog _memoryLog;
    
    TSysLoadLog _sysloadLog;
    
    TDiskSpeedLog _diskspeedLog;
    
    TNetSpeedLog _netspeedLog;
    
    volatile bool _enableRunning;
    
    std::thread* collectThread;
    
};

#endif	/* TSTATMODULE_H */

