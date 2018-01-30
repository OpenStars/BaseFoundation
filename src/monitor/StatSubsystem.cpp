#include "monitor/StatSubsystem.h"
#include "Poco/DateTimeFormat.h"
#include "Poco/Util/Application.h"
#include "Poco/DateTimeFormatter.h"
#include <thread>
#include <iostream>
#include <statgrab.h>


using namespace std;
using namespace Poco::Util;
using namespace Poco;

StatSubsystem::StatSubsystem() {
}

StatSubsystem::StatSubsystem(const StatSubsystem& orig) {
}

StatSubsystem::~StatSubsystem() {
}

/*
 * System interfaces
 */
StatSubsystem* StatSubsystem::_instance = 0;

StatSubsystem& StatSubsystem::getInstance() {
    if (_instance) {
        return *_instance;
    }
    throw "Instance Error!";
}

void StatSubsystem::initialize(Application& app) {
    try {
        app.logger().information("Monitor Module starting ...");
        _instance = this;

        //Initialize libstatgrab ignoring initialization error
        sg_init(1);

        std::thread* collectThread = new std::thread(
                [this]() {
                    while (true) {
                        {
                            size_t entries;

                            sg_disk_io_stats *nios = sg_get_disk_io_stats_diff(&entries);

                            for (size_t i = 0; i < entries; i++) {
                                _diskspeedLog.log(nios[i].disk_name, nios[i].read_bytes, nios[i].write_bytes);
                            }
                        }

                        {
                            sg_cpu_stats *cpustat = sg_get_cpu_stats_diff(NULL);
                            cpustat = sg_get_cpu_stats_diff(NULL);

                            this->_cpuLog.log(
                                    cpustat->user,
                                    cpustat->kernel,
                                    cpustat->idle,
                                    cpustat->iowait,
                                    cpustat->swap,
                                    cpustat->nice,
                                    cpustat->total
                                    );
                        }

                        {
                            sg_mem_stats *memstat = sg_get_mem_stats(NULL);

                            this->_memoryLog.log(
                                    memstat->total,
                                    memstat->free,
                                    memstat->used,
                                    memstat->cache
                                    );
                        }

                        {
                            size_t entries;

                            sg_network_io_stats *nios = sg_get_network_io_stats_diff(&entries);

                            for (size_t i = 0; i < entries; i++) {
                                this->_netspeedLog.log(nios[i].interface_name, nios[i].rx, nios[i].tx);
                            }

                        }

                        {
                            sg_load_stats *load = sg_get_load_stats(NULL);
                            this->_sysloadLog.log((long long) 1000 * load->min1, (long long) 1000 * load->min5, (long long) 1000 * load->min15);
                        }
                    }

                }
        ); // thread function 

        app.logger().information("Monitor Module started ...");

    } catch (Poco::Exception&) {
        app.logger().information("Monitor Module failed ...");
    }
}

void StatSubsystem::uninitialize() {
    Application& app = Application::instance();
    try {
        app.logger().information("Stat module Server stopping ...");

        app.logger().information("Stat module Server stopped ...");

    } catch (Poco::Exception&) {
        app.logger().information("Thrift Server failed ...");
    }
}

void StatSubsystem::reinitialize(Application& app) {

}

/**
 * Print Readable timeformat
 *
 * @param val
 * @return
 */
static
std::string printDateTime(int64_t val) {
    return DateTimeFormatter::format(
            Poco::Timestamp(val),
            Poco::DateTimeFormat::ASCTIME_FORMAT);
}

/**
 * Printout status
 * 
 * @param output
 */
void StatSubsystem::printStat(std::ostream& output) {
    output << "STARTTIME: " << printDateTime(Poco::Util::Application::instance().startTime().epochMicroseconds()).c_str() << std::endl;
    output << "UPTIME: "
            << Poco::Util::Application::instance().uptime().totalHours() << " h | "
            << Poco::Util::Application::instance().uptime().totalMinutes() << " m | "
            << Poco::Util::Application::instance().uptime().totalSeconds() << " s "
            << std::endl;
    output << "****************************************************" << std::endl;

}