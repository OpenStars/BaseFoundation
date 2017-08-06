namespace cpp openstars.base.monitor
namespace java openstars.base.monitor
namespace php Monitor

include "openbase.thrift"

/**
 * CPU usage
 */
struct cpuStat {
    1:i32 userCPU,
    2:i32 kernelCPU,
    3:i32 idleCPU,
    4:i32 iowaitCPU,
    5:i32 swapCPU,
    6:i32 niceCPU,
    7:i32 totalCPU
}

/**
 * Memory usage
 */
struct memoryStat {
    1:i64 totalMem,
    2:i64 freeMem,
    3:i64 usedMem,
    4:i64 cacheMem,
}

/**
 * System Load
 */
struct systemLoad {
    1:double load1m,
    2:double load5m,
    3:double load15m,
}

/**
 * disk speed
 */
struct diskStat {
    1:i64 readSpeed,
    2:i64 writeSpeed,
}
typedef map<string, diskStat> diskStats

/**
 * network stat
 */
struct networkStat {
    1:i64 readSpeed,
    2:i64 writeSpeed,
}
typedef map<string, networkStat> networkStats

/**
 * system stat
 */
struct systemStat {
    1:cpuStat cpu,
    2:memoryStat memory,
    3:systemLoad sysload,
    4:diskStats disks,
    5:networkStats networks,
    6:i64 timestamp,
    7:i32 seconds
}


/**
 * Exception
 */
exception InvalidOperation {
	1: i16 errorCode,
	2: string why
}

/**/
service MonitorReadService extends openbase.OpenBaseService {
	systemStat getCurrentStat() throws (1:InvalidOperation e),
	systemStat getStat(1:i32 seconds) throws (1:InvalidOperation e),
	
}
