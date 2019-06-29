
#include "monitor/TMonitorThriftServer.h"
#include "monitor/TMonitorThriftHandler.h"

#include <thrift/server/TSimpleServer.h>
#include <thrift/server/TThreadPoolServer.h>
#include <thrift/server/TThreadedServer.h>
#include <thrift/server/TNonblockingServer.h>
#include <thrift/transport/TNonblockingServerSocket.h>
#include <thrift/transport/TTransportUtils.h>
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/concurrency/PosixThreadFactory.h>



using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;
using namespace apache::thrift::server;
using namespace apache::thrift::concurrency;

using namespace Poco::Util;


using apache::thrift::stdcxx::shared_ptr;


// Runable thread
template <class ServiceHandler, class ServiceProcessor>
class TServerThread : public Poco::Runnable
{
private:
        Application* _app;
        int _port;

public:
        TServerThread(Application* app, int port = 9091, const std::string& bindHost = "*") {
                _app = app;
                _port = port;
        }

        virtual void run()
        {
            try
            {
                _app->logger().information("Thrift Monitor starting ...");

                apache::thrift::stdcxx::shared_ptr<ServiceHandler> handler(new ServiceHandler());
                apache::thrift::stdcxx::shared_ptr<TProcessor> processor(new ServiceProcessor(handler));
                apache::thrift::stdcxx::shared_ptr<TNonblockingServerTransport> serverTransport(new TNonblockingServerSocket(_port));
                apache::thrift::stdcxx::shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
                apache::thrift::stdcxx::shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());


                int workerCount = _app->config().getInt("thrift.nb_threadpool.size", 1);

                if (workerCount > 0) {
                    apache::thrift::stdcxx::shared_ptr<ThreadManager> threadManager = ThreadManager::newSimpleThreadManager(workerCount);
                    apache::thrift::stdcxx::shared_ptr<PosixThreadFactory> threadFactory = apache::thrift::stdcxx::shared_ptr<PosixThreadFactory>(new PosixThreadFactory());
                    threadManager->threadFactory(threadFactory);
                    
                    threadManager->start();

                    TNonblockingServer server(processor, protocolFactory,
                                                    serverTransport, threadManager);

                    // start server
                    _app->logger().information("Thrift Monitor started");
                    server.serve();

                } else {
                    TNonblockingServer server(processor, protocolFactory, serverTransport);

                    // start server
                    _app->logger().information("Thrift Monitor started");
                    server.serve();
                }


            }
            catch(...)
            {
                 _app->logger().error("Thrift Monitor failed");
            }
        }
};


TMonitorThriftServer::TMonitorThriftServer() {
}

TMonitorThriftServer::TMonitorThriftServer(const TMonitorThriftServer& orig) {
}

TMonitorThriftServer::~TMonitorThriftServer() {
}

/*
 * System interfaces
 */
void TMonitorThriftServer::initialize(Application& app) {
        try {
            app.logger().information("Monitor Thrift Server starting ...");

            int port = app.config().getInt("thrift-monitor.listen", 10001);

            TServerThread<TMonitorThriftHandler, MonitorReadServiceProcessor>* coreThread
                    = new TServerThread<TMonitorThriftHandler, MonitorReadServiceProcessor>(&app, port);

            
            m_pcsThread = new Poco::Thread();
            m_pcsThread->start(*coreThread);

            // continue
            app.logger().information("Thrift Server started ...");

        } catch (Poco::Exception&) {
            app.logger().information("Thrift Server failed ...");
        }
}

void TMonitorThriftServer::uninitialize()
{
        Application& app	= Application::instance();
        try {
            app.logger().information("Thrift Server stop ...");
            app.logger().information("Thrift Server stopped ...");

        } catch (Poco::Exception&) {
            app.logger().information("Thrift Server failed ...");
        }
}

void TMonitorThriftServer::reinitialize(Application& app) {

}
