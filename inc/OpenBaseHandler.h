

#ifndef OPEN_BASE_HANDLER_H
#define OPEN_BASE_HANDLER_H

#include <thrift/server/TServer.h>
#include <thrift/concurrency/Mutex.h>
#include <thrift/server/TServer.h>

#include <time.h>
#include <string>
#include <map>

#include "OpenBaseService.h"
// Todo: Chuyen qua dung Poco::Mutex

using apache::thrift::concurrency::Mutex;
// using apache::thrift::concurrency::ReadWriteMutex;
using apache::thrift::server::TServer;

struct ReadWriteInt : Mutex {
    int64_t value;
};

struct ReadWriteCounterMap : Mutex,
std::map<std::string, ReadWriteInt> {
};

class OpenBaseHandler : virtual public openstars::base::OpenBaseServiceIf {
public:
    OpenBaseHandler();
    virtual ~OpenBaseHandler();

public:
    /** Name & version */
    void getName(std::string& _return);

    virtual void getVersion(std::string& _return) {
        _return = "";
    }

    /** Status */
    virtual openstars::base::service_status::type getStatus() = 0;

    virtual void getStatusDetails(std::string& _return) {
        _return = "";
    }

    /** Options */
    void setOption(const std::string& key, const std::string& value);
    void getOption(std::string& _return, const std::string& key);
    void getOptions(std::map<std::string, std::string> & _return);


    /** Initialize Service */
    int64_t aliveSince();

    virtual void reinitialize() {
    }

    virtual void shutdown() {
        if (server_.get() != NULL) {
            server_->stop();
        }
    }

    /** Atomic counter */
    int64_t incrementCounter(const std::string& key, int64_t amount = 1);
    int64_t setCounter(const std::string& key, int64_t value);

    void getCounters(std::map<std::string, int64_t>& _return);
    int64_t getCounter(const std::string& key);

    /**
     * Set server handle for shutdown method
     */
    void setServer(std::shared_ptr<TServer> server) {
        server_ = server;
    }

    void getCpuProfile(std::string& _return, int32_t durSecs) {
        _return = "";
    }

private:
    std::string name_;
    int64_t aliveSince_;

    std::map<std::string, std::string> options_;
    apache::thrift::concurrency::Mutex optionsLock_;

    ReadWriteCounterMap counters_;

    std::shared_ptr<TServer> server_;

};

#endif /* OPEN_BASE_HANDLER_H */

