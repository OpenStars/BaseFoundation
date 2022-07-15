/* 
 * File:   TCompressSerializer.h
 * Author: thanhnt
 *
 * Created on September 2, 2012, 11:29 PM
 */

#ifndef _TCOMPRESSSERIALIZER_H
#define	_TCOMPRESSSERIALIZER_H

#include <thrift/protocol/TProtocol.h>
#include <thrift/protocol/TBinaryProtocol.h>
#include "thrift/protocol/TCompactProtocol.h"
#include <thrift/protocol/TJSONProtocol.h>
#include <thrift/protocol/TDebugProtocol.h>

#include <thrift/transport/TTransportUtils.h>
#include <thrift/transport/TFileTransport.h>
#include <thrift/transport/TZlibTransport.h>
#include <snappy/snappy.h>

#include <memory>

using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;

template <class _TType, class _TProtocolType = TBinaryProtocol >
class TCompressSerializer {
public:

    typedef _TType TType;

    static int32_t Serialize(std::shared_ptr<TMemoryBuffer> &memBuf, const TType&value) {
        try {
            if (memBuf == 0)
                memBuf = std::shared_ptr<TMemoryBuffer > (new TMemoryBuffer());

            _TProtocolType binProt(memBuf);
            //memBuf->resetBuffer();
            value.write(&binProt);
        } catch (...) {
            return -1;
        }
        return 0;
    }

    static int32_t Deserialize(TType&value, const std::shared_ptr<TMemoryBuffer> &memBuf) {
        if (memBuf == 0)
            return -1;

        try {
            _TProtocolType binProt(memBuf);
            value.read(&binProt);
        } catch (...) {
            return -1;
        }
        return 0;
    }

    static int32_t Serialize(std::string &strBuf, const TType&value) {
        std::shared_ptr<TMemoryBuffer > memBuf;
        Serialize(memBuf, value);
        if (memBuf == 0)
            return -1;

        uint8_t *pBuf = NULL;
        uint32_t nSize = 0;
        memBuf->getBuffer(&pBuf, &nSize);
        if (pBuf == NULL || nSize <= 0)
            return -1;

        snappy::Compress((const char*) pBuf, nSize, &strBuf);
        return 0;
    }

    static int32_t Deserialize(TType&value, const std::string &strBuf) {
        std::string tmp;        
        if (snappy::Uncompress(strBuf.data(), strBuf.length(), &tmp)) {
            std::shared_ptr<TMemoryBuffer> memBuf(new TMemoryBuffer((uint8_t*) tmp.data(), tmp.size(), TMemoryBuffer::OBSERVE));
            return Deserialize(value, memBuf);
        } else {
            std::shared_ptr<TMemoryBuffer> memBuf(new TMemoryBuffer((uint8_t*) strBuf.data(), strBuf.size(), TMemoryBuffer::OBSERVE));
            return Deserialize(value, memBuf);
        }
    }

    template <class _MType>
    static int32_t SerializeT(std::string& strBuf, const _MType& value) {
        TType thriftObj;
        value.assignTo(thriftObj); // Need to care about thriftObj.__isset.*
        return Serialize(strBuf, (const TType&) thriftObj);

    }

    template <class _MType>
    static int32_t DeserializeT(_MType& value, const std::string& strBuf) {
        TType thriftObj;
        int32_t res = 0;
        res = Deserialize(thriftObj, strBuf);
        value.assignFrom(thriftObj);
        return res;
    }

};

template <class _TType, class _TProtocolType = TCompactProtocol>
class TThriftSerializer {
public:

    typedef _TType TType;

    static int Serialize(std::shared_ptr<TMemoryBuffer> &memBuf, const TType& value) {
        try {
            if (memBuf == 0)
                memBuf = std::shared_ptr<TMemoryBuffer > (new TMemoryBuffer());

            _TProtocolType prot(memBuf);
            value.write(&prot);
        } catch (...) {
            return -1;
        }
        return 0;
    }

    static int Deserialize(TType& value, const std::shared_ptr<TMemoryBuffer>& memBuf) {
        if (!memBuf)
            return -1;

        try {
            _TProtocolType binProt(memBuf);
            value.read(&binProt);
        } catch (...) {
            return -1;
        }
        return 0;
    }

    static int32_t SerializeT(std::string& strBuf, const TType& value) {

        std::shared_ptr<TMemoryBuffer > buf = std::shared_ptr<TMemoryBuffer > (new TMemoryBuffer());

        int32_t ret = Serialize(buf, value);
        if (ret == 0) {
            uint8_t* pBuf = NULL;
            uint32_t size = 0;
            buf->getBuffer(&pBuf, &size);
            snappy::Compress((const char*) pBuf, size, &strBuf);
        }
        return ret;
    }

    static int32_t Serialize(std::string& strBuf, const TType& value) {
        return SerializeT(strBuf, value);
    }

    static int32_t DeserializeT(TType& value, const std::string& strBuf) {
        int32_t res = 0;
        size_t uncompressSize = 0;
        if (snappy::GetUncompressedLength(strBuf.data(), strBuf.length(), &uncompressSize)) {
            if (uncompressSize < 1L << 32) {

                std::shared_ptr<TMemoryBuffer > buf =
                        std::shared_ptr<TMemoryBuffer > (new TMemoryBuffer(uncompressSize));

                if (snappy::RawUncompress(strBuf.data(), strBuf.length(), (char*) buf->getWritePtr(uncompressSize))) {
                    return Deserialize(value, buf);
                }
            }
        }
		std::shared_ptr<TMemoryBuffer> buf(new TMemoryBuffer((uint8_t*)strBuf.data(), (uint32_t)strBuf.length()));
        return Deserialize(value, buf);
    }

};

template <class TObj, class MObj>
class CompressStringToObjectFunctor {
public:

    void operator()(const std::string& aData, MObj& aObj) {
        TCompressSerializer<TObj> aSerializer;
        aSerializer.DeserializeT(aObj, aData);
    }
};


#endif	/* _TCOMPRESSSERIALIZER_H */

