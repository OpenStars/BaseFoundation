
#ifndef MONITOR_THRIFTHANDLER_H
#define	MONITOR_THRIFTHANDLER_H


#include "Poco/Stopwatch.h"
#include "StatSubsystem.h"
#include "PocoEx/TimeUtils.h"
#include "OpenBaseHandler.h"
#include "MonitorReadService.h"

using namespace openstars::base::monitor;

class TMonitorThriftHandler :
    virtual public MonitorReadServiceIf, public OpenBaseHandler {
public:
    TMonitorThriftHandler();
    virtual ~TMonitorThriftHandler();
    
    openstars::base::service_status::type getStatus() {
        return openstars::base::service_status::ALIVE;
    }
    
    void getName(std::string& _return) {
        _return = "Monitor-KB";
    }

    virtual void getCurrentStat(systemStat& _return) {
        int current = TimeUtils::getCurrentSeconds();
        if (current > 5)
            current -= 3;
        
        /** cpu stat */
        cpuUsageLog& cpuData = StatSubsystem::getInstance().getCPULog().getData();        
        _return.cpu.kernelCPU        = cpuData.kernelCPU[current];
        _return.cpu.userCPU          = cpuData.userCPU[current];
        _return.cpu.idleCPU          = cpuData.idleCPU[current];
        _return.cpu.niceCPU          = cpuData.niceCPU[current];
        _return.cpu.swapCPU          = cpuData.swapCPU[current];
        _return.cpu.iowaitCPU        = cpuData.iowaitCPU[current];
        _return.cpu.totalCPU         = cpuData.totalCPU[current];
        
        
        /** memory */
        memoryUsageLog& memoryData = StatSubsystem::getInstance().getMemoryUsageLog().getData();
        _return.memory.totalMem      = memoryData.totalMem[current];
        _return.memory.usedMem       = memoryData.usedMem[current];
        _return.memory.freeMem       = memoryData.freeMem[current];
        _return.memory.cacheMem      = memoryData.cacheMem[current];
        
        
        /** system load */
        sysloadLog& sysloadLog = StatSubsystem::getInstance().getSysLoadLog().getData();
        _return.sysload.load1m       = sysloadLog.load1m[current];
        _return.sysload.load5m       = sysloadLog.load5m[current];
        _return.sysload.load15m      = sysloadLog.load15m[current];
        
        
        /** network */
        TNetSpeedLog& netSpeedLog = StatSubsystem::getInstance().getNetSpeedLog();
        ifsSpeed ifs;
        netSpeedLog.getIfsSpeed(current, ifs);
        for (ifsSpeed::iterator it = ifs.begin(); it != ifs.end(); it++) {
            networkStat nst;
            nst.readSpeed = it->second.rx;
            nst.writeSpeed = it->second.sx;
            
            _return.networks[it->first] = nst;
        }
                        
        
        /** disk io */
        TDiskSpeedLog& diskSpeedLog = StatSubsystem::getInstance().getDiskSpeedLog();
        dssSpeed dss;
        diskSpeedLog.getDssSpeed(current, dss);
        for (dssSpeed::iterator it = dss.begin(); it != dss.end(); it++) {
            diskStat dst;
            dst.readSpeed = it->second.rx;
            dst.writeSpeed = it->second.wx;
            
            _return.disks[it->first] = dst;
        }
    }
    
    virtual void getStat(systemStat& _return, const int32_t seconds) {
        int current = seconds;
        
                /** cpu stat */
        cpuUsageLog& cpuData = StatSubsystem::getInstance().getCPULog().getData();        
        _return.cpu.kernelCPU        = cpuData.kernelCPU[current];
        _return.cpu.userCPU          = cpuData.userCPU[current];
        _return.cpu.idleCPU          = cpuData.idleCPU[current];
        _return.cpu.niceCPU          = cpuData.niceCPU[current];
        _return.cpu.swapCPU          = cpuData.swapCPU[current];
        _return.cpu.iowaitCPU        = cpuData.iowaitCPU[current];
        _return.cpu.totalCPU         = cpuData.totalCPU[current];
        
        
        /** memory */
        memoryUsageLog& memoryData = StatSubsystem::getInstance().getMemoryUsageLog().getData();
        _return.memory.totalMem      = memoryData.totalMem[current];
        _return.memory.usedMem       = memoryData.usedMem[current];
        _return.memory.freeMem       = memoryData.freeMem[current];
        _return.memory.cacheMem      = memoryData.cacheMem[current];
        
        
        /** system load */
        sysloadLog& sysloadLog = StatSubsystem::getInstance().getSysLoadLog().getData();
        _return.sysload.load1m       = sysloadLog.load1m[current];
        _return.sysload.load5m       = sysloadLog.load5m[current];
        _return.sysload.load15m      = sysloadLog.load15m[current];
        
        
        /** network */
        TNetSpeedLog& netSpeedLog = StatSubsystem::getInstance().getNetSpeedLog();
        ifsSpeed ifs;
        netSpeedLog.getIfsSpeed(current, ifs);
        for (ifsSpeed::iterator it = ifs.begin(); it != ifs.end(); it++) {
            networkStat nst;
            nst.readSpeed = it->second.rx;
            nst.writeSpeed = it->second.sx;
            
            _return.networks[it->first] = nst;
        }
                        
        
        /** disk io */
        TDiskSpeedLog& diskSpeedLog = StatSubsystem::getInstance().getDiskSpeedLog();
        dssSpeed dss;
        diskSpeedLog.getDssSpeed(current, dss);
        for (dssSpeed::iterator it = dss.begin(); it != dss.end(); it++) {
            diskStat dst;
            dst.readSpeed = it->second.rx;
            dst.writeSpeed = it->second.wx;
            
            _return.disks[it->first] = dst;
        }
    }

private:

};

#endif	

