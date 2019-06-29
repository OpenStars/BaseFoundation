/*
 * File:   TClient.h
 * Author: thanhnt
 *
 * Created on October 2, 2012, 9:35 AM
 */

#ifndef _TCLIENT_H
#define	_TCLIENT_H

#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/protocol/TCompactProtocol.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TTransportUtils.h>
#include <iostream>
#include <assert.h>
#include <Poco/Timestamp.h>

#include <thrift/transport/TBufferTransports.h>

template <class _ThriftServiceClient, class _TThriftProtocol = apache::thrift::protocol::TBinaryProtocol, int KExpiredPeriodInSecond = 7200 >
class TClient : public _ThriftServiceClient {
public:

    TClient() :
    _ThriftServiceClient(apache::thrift::stdcxx::shared_ptr<apache::thrift::protocol::TProtocol>()) {

    }

    virtual ~TClient() {
        close();
    }

    TClient(const std::string &host, int port, bool framed = false) :
    _ThriftServiceClient(apache::thrift::stdcxx::shared_ptr<apache::thrift::protocol::TProtocol>()) {
        open(host, port, framed);
    }

    bool open(const std::string &host, int port, bool framed = false) {
        close();
        this->_host = host;
        this->_port = port;
        this->_framed = framed;

        return doOpen();
    }

    bool checkConnectionExpired() {
        Poco::Timestamp aTime;
        if (aTime.epochTime() - _timestamp > KExpiredPeriodInSecond) {
            close();
            doOpen();
            return true;
        }
        return false;

    }

    bool doOpen() {
        Poco::Timestamp aTime;
        _timestamp = aTime.epochTime();
        bool result = true;
        try {
            this->_socket = apache::thrift::stdcxx::shared_ptr<apache::thrift::transport::TTransport > (new apache::thrift::transport::TSocket(this->_host, this->_port));
            if (this->_framed) {
                this->_transport = apache::thrift::stdcxx::shared_ptr<apache::thrift::transport::TTransport > (new apache::thrift::transport::TFramedTransport(this->_socket));
            } else {
                this->_transport = apache::thrift::stdcxx::shared_ptr<apache::thrift::transport::TTransport > (new apache::thrift::transport::TBufferedTransport(this->_socket));
            }

            this->_protocol = apache::thrift::stdcxx::shared_ptr<apache::thrift::protocol::TProtocol > (new _TThriftProtocol(this->_transport));

            //bind service client protocol
            _ThriftServiceClient::piprot_ = _protocol;
            _ThriftServiceClient::poprot_ = _protocol;
            _ThriftServiceClient::iprot_ = _protocol.get();
            _ThriftServiceClient::oprot_ = _protocol.get();

            if (this->_transport != 0)
                this->_transport->open();

            result &= isOpen();
        } catch (...) {
            result = false;
            //throw;
        }

        if (!result)
            close();
        return result;
    }

    void close() {
        if (_transport != 0)
            _transport->close();
        _socket.reset();
        _transport.reset();
        _protocol.reset();
    }

    bool isOpen() const {
        if (_socket == 0 || _transport == 0 || _protocol == 0)
            return false;

        return _transport->isOpen();
    }

    bool sureOpen() {
        if (isOpen())
            return true;
        else
            return open(_host, _port, _framed);
    }

private:
    apache::thrift::stdcxx::shared_ptr<apache::thrift::transport::TTransport> _socket;
    apache::thrift::stdcxx::shared_ptr<apache::thrift::transport::TTransport> _transport;
    apache::thrift::stdcxx::shared_ptr<apache::thrift::protocol::TProtocol> _protocol;
    std::string _host;
    int _port;
    bool _framed;
    Poco::Int64 _timestamp;
};


template <class _ThriftServiceClient >
class TClientCompact : public TClient<_ThriftServiceClient, apache::thrift::protocol::TCompactProtocol> {
public:

    TClientCompact(const std::string &host, int port, bool framed = false) :
    TClient<_ThriftServiceClient, apache::thrift::protocol::TCompactProtocol>(host, port, framed) {
    }
};

template <class ThriftClient>
class TMemBufClient {
private:
    apache::thrift::stdcxx::shared_ptr<apache::thrift::transport::TMemoryBuffer> memBuf;
    apache::thrift::stdcxx::shared_ptr<apache::thrift::protocol::TProtocol> protocol;
    apache::thrift::stdcxx::shared_ptr<ThriftClient> client;
public:

    TMemBufClient() {
        lazyInit();
    }

    ThriftClient* operator->() {
        return client.get();
    }

    apache::thrift::stdcxx::shared_ptr<apache::thrift::transport::TMemoryBuffer> getMemBuff()const {
        return memBuf;
    }

    void lazyInit() {
        if (memBuf == 0)
            memBuf = apache::thrift::stdcxx::shared_ptr<apache::thrift::transport::TMemoryBuffer > (new apache::thrift::transport::TMemoryBuffer());
        if (protocol == 0)
            protocol = apache::thrift::stdcxx::shared_ptr<apache::thrift::protocol::TProtocol > (new apache::thrift::protocol::TBinaryProtocol(memBuf));
        if (client == 0)
            client = apache::thrift::stdcxx::shared_ptr<ThriftClient > (new ThriftClient(protocol));
    }
};


#endif	/* _TCLIENT_H */

