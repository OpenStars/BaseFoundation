/* 
 * File:   TSerializer.h
 * Author: thanhnt
 *
 * Created on October 2, 2012, 11:29 PM
 */

#ifndef _TSERIALIZER_H
#define	_TSERIALIZER_H

#include <thrift/protocol/TProtocol.h>
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/protocol/TJSONProtocol.h>
#include <thrift/protocol/TDebugProtocol.h>
#include <thrift/transport/TTransportUtils.h>
#include <thrift/transport/TFileTransport.h>

using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;

template <class _TType, class _TProtocolType = TBinaryProtocol >
class TSerializer {
public:

	typedef _TType TType;

	static int32_t Serialize(boost::shared_ptr<TMemoryBuffer> &memBuf, const TType&value) {
		try {
			if (memBuf == 0)
				memBuf = boost::shared_ptr<TMemoryBuffer > (new TMemoryBuffer());

			_TProtocolType proto(memBuf);
			//memBuf->resetBuffer();
			value.write(&proto);
		} catch (...) {
			return -1;
		}
		return 0;
	}

	static int32_t Deserialize(TType&value, const boost::shared_ptr<TMemoryBuffer> &memBuf) {
		if (memBuf == 0)
			return -1;

		try {
			_TProtocolType proto(memBuf);
			value.read(&proto);
		} catch (...) {
			return -1;
		}
		return 0;
	}

	static int32_t Serialize(std::string &strBuf, const TType&value) {
		boost::shared_ptr<TMemoryBuffer > memBuf;
		Serialize(memBuf, value);
		if (memBuf == 0)
			return -1;

		uint8_t *pBuf = NULL;
		uint32_t nSize = 0;
		memBuf->getBuffer(&pBuf, &nSize);
		if (pBuf == NULL || nSize <= 0)
			return -1;

		strBuf.append((char*) pBuf, nSize);
		return 0;
	}

	static int32_t Deserialize(TType&value, const std::string &strBuf) {
		boost::shared_ptr<TMemoryBuffer> memBuf(new TMemoryBuffer((uint8_t*) strBuf.data(), strBuf.size(), TMemoryBuffer::OBSERVE));
		return Deserialize(value, memBuf);
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
		int32_t res = Deserialize(thriftObj, strBuf);
		value.assignFrom(thriftObj);
		return res;
	}

};

class TNoneSerializer {
public:

	static int32_t SerializeT(std::string& strBuf, const std::string& value) {
		strBuf = value;
		return 0;
	}

	static int32_t DeserializeT(std::string& value, const std::string& strBuf) {
		value = strBuf;
		return 0;
	}

};

#include <string.h>

template <class T>
class TCastingSerializer {
public:

	static int32_t SerializeT(std::string& strBuf, const T& value) {
		std::string str((const char*) &value, sizeof (T));
		strBuf.swap(str);
		return 0;
	}

	static int32_t DeserializeT(T& value, const std::string& strBuf) {
		value = 0;
		int len = sizeof (T);
		if (len > strBuf.length())
			len = strBuf.length();
		if (len > 0)
			::memcpy(&value, strBuf.data(), len);
		return 0;
	}

};

template <class TObj, class MObj>
class StringToObjectFunctor {
public:

	void operator()(const std::string& aData, MObj& aObj) {
		TSerializer<TObj> aSerializer;
		aSerializer.DeserializeT(aObj, aData);
	}
};


#endif	/* _TSERIALIZER_H */

