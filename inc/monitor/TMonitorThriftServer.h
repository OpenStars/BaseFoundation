#ifndef MONITOR_THRIFTSERVER_H
#define	MONITOR_THRIFTSERVER_H

#include "Poco/SharedPtr.h"
#include "Poco/Thread.h"
#include "Poco/Util/Application.h"

class TMonitorThriftServer : public Poco::Util::Subsystem {
public:
    TMonitorThriftServer();
    TMonitorThriftServer(const TMonitorThriftServer& orig);
    virtual ~TMonitorThriftServer();

    // subsystem interfaces
    virtual const char* name() const { return "TBigListThriftServer";};
    virtual void initialize(Poco::Util::Application& app);
    virtual void uninitialize();
    virtual void reinitialize(Poco::Util::Application& app);

private:
    Poco::SharedPtr<Poco::Thread> m_pcsThread;
    
};

#endif	/* MONITOR_THRIFTSERVER_H */

