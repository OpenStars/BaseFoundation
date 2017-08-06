/*
 * File:   TThriftServer.h
 * Author: thanhnt
 *
 * Created on December 24, 2009, 10:27 PM
 */

#ifndef _TTHRIFTSERVER_H
#define	_TTHRIFTSERVER_H


#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/protocol/TCompactProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/concurrency/PosixThreadFactory.h>
#include <thrift/server/TThreadPoolServer.h>
#include <thrift/server/TThreadedServer.h>
#include <thrift/server/TNonblockingServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TTransportUtils.h>

#include <Poco/Util/Application.h>
#include <Poco/NotificationQueue.h>
#include <Poco/Thread.h>

using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;
using namespace apache::thrift::server;
using namespace apache::thrift::concurrency;

using namespace Poco::Util;
//#define THREADPOOL_SERVER 1
#define NONBLOCKING_SERVER 1

namespace openstars {
namespace base {
namespace transport {

template <class _ThriftIface, class _ThriftProcessor, class _ThriftProtocolFactory = apache::thrift::protocol::TBinaryProtocolFactory>
class TThriftServer : public Poco::Util::Subsystem {
public:
	typedef _ThriftIface ThriftIface;
	typedef _ThriftProcessor ThriftProcessor;

protected:

	class ServerThread : public Poco::Runnable {
	private:
		int m_port;
		int m_workerCount;
		boost::shared_ptr<ThriftProcessor> m_thriftProcessor;
		boost::shared_ptr<TServer> m_server;
	public:

		ServerThread(int port, int workerCount, boost::shared_ptr<ThriftProcessor> thriftProcessor)
		: m_port(port)
		, m_workerCount(workerCount)
		, m_thriftProcessor(thriftProcessor) {
			assert(m_port > 0 && m_workerCount > 0);
		}
	public:

		boost::shared_ptr<TServer> getServer() {
			return m_server;
		}

		void run() {
			Application &app = Application::instance();
			try {
				app.logger().information("Thrift transport starting ...");


				//protocol factory
				boost::shared_ptr<TProtocolFactory> protocolFactory(new _ThriftProtocolFactory());

#ifdef SIMPLE_SERVER
				TSimpleServer server(m_thriftProcessor, serverTransport, transportFactory, protocolFactory);
#endif

#ifdef THREADED_SERVER
				TThreadedServer server(m_thriftProcessor, serverTransport, transportFactory, protocolFactory);
#endif

#ifdef THREADPOOL_SERVER
				//int workerCount = app.config().getInt("thrift-server.threadpool.size", 400);
				shared_ptr<ThreadManager> threadManager = ThreadManager::newSimpleThreadManager(m_workerCount);
				shared_ptr<PosixThreadFactory> threadFactory = shared_ptr<PosixThreadFactory > (new PosixThreadFactory());
				threadManager->threadFactory(threadFactory);
				threadManager->start();
				TThreadPoolServer server(m_thriftProcessor, serverTransport, transportFactory, protocolFactory, threadManager);
#endif

#ifdef NONBLOCKING_SERVER
				//int workerCount = app.config().getInt("thrift-server.nb_threadpool.size", 10);
				boost::shared_ptr<ThreadManager> threadManager = ThreadManager::newSimpleThreadManager(m_workerCount);
				boost::shared_ptr<PosixThreadFactory> threadFactory(new PosixThreadFactory());
				threadManager->threadFactory(threadFactory);
				threadManager->start();


				TNonblockingServer* aServer = new TNonblockingServer(m_thriftProcessor
						, protocolFactory
						, m_port, threadManager);
				aServer->setNumIOThreads(m_workerCount);
				m_server = boost::shared_ptr<TServer>(aServer);

#endif
				// start server
				app.logger().information("Thrift transport started");
				//server.serve();
				m_server->serve();

			} catch (...) {
				app.logger().error("Thrift transport failed");
				throw;
			}
		}
	}; //ServerThread

protected:
	int m_port;
	int m_workerCount;
	Poco::SharedPtr<Poco::Thread> m_svrThread;
	Poco::SharedPtr<ServerThread> m_svrThreadCore;
	Poco::SharedPtr<Poco::NotificationQueue> m_notifQueue;

	boost::shared_ptr<ThriftIface > m_serverHandler;
	boost::shared_ptr<ThriftProcessor> m_thriftProcessor;

	void lazyInit() {
		if (m_thriftProcessor == 0)
			m_thriftProcessor = boost::shared_ptr<ThriftProcessor > (new ThriftProcessor(m_serverHandler));

		if (!m_svrThreadCore)
			m_svrThreadCore = new ServerThread(m_port, m_workerCount, m_thriftProcessor);

		if (!m_svrThread)
			m_svrThread = new Poco::Thread();
	}

private:
	TThriftServer(const TThriftServer<ThriftIface, ThriftProcessor >& orig); //not implemented

public:

	virtual ~TThriftServer() {
		uninitialize();
		m_serverHandler.reset();
		//m_workerHandler.reset();
		m_thriftProcessor.reset();
	}

	TThriftServer(int port, int workerCount
			, boost::shared_ptr<ThriftIface > thriftServerHandler
			, boost::shared_ptr<ThriftProcessor> thriftProcessor = boost::shared_ptr<ThriftProcessor>())
	: m_port(port), m_workerCount(workerCount)
	, m_serverHandler(thriftServerHandler)
	, m_thriftProcessor(thriftProcessor) {
		assert(m_serverHandler != 0);
	}

	boost::shared_ptr<ThriftIface > serverHandler() const {
		return m_serverHandler;
	}

	boost::shared_ptr<ThriftProcessor> thriftProcessor() const {
		return m_thriftProcessor;
	}

	boost::shared_ptr<TServer> thriftServer() {
		return this->m_svrThreadCore->getServer();
	}

	int32_t getQueuingSize() const {
		if (!m_notifQueue)
			return 0;
		return m_notifQueue->size();
	}





public:

	const char* name() const {
		return "ThriftServer Sub-system";
	};

	void initialize(Application& app) {
		lazyInit();
		m_svrThread->start(*m_svrThreadCore);
	}

	void uninitialize() {
		if (m_svrThreadCore && m_svrThreadCore->getServer()) {
			m_svrThreadCore->getServer()->stop();
		}
		m_svrThread = NULL;
	}

	void reinitialize(Application& app) {
		uninitialize();
		initialize(app);
	}
};

}
}
}
#endif	/* _TTHRIFTSERVER_H */

