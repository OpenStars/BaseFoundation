/* 
 * File:   AbstractKVStorage.h
 * Author: trungthanh
 *
 * Created on January 12, 2010, 10:49 AM
 */

#ifndef _ABSTRACTKVSTORAGE_H
#define _ABSTRACTKVSTORAGE_H

#include "stdint.h"
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <Poco/SharedPtr.h>
#include <Poco/Util/Subsystem.h>
#include <Poco/ByteOrder.h>
#include <string.h>

#include <endian.h>

//#include <Storage/AbstractDatabase.h>

#define HAVE_OVERLOAD_TEMPLATE

namespace openstars {
    namespace storage {


        //-----------------------------------------------------------------------------
        //AbstractCursor

        class AbstractCursor {
        public:

            virtual ~AbstractCursor() {
            }
            virtual bool next(std::string& aKey, std::string& aVal) = 0;

            virtual void close() = 0;

            template <class SimpleKeyType, class SimpleValType>
            bool next(SimpleKeyType& aKey, SimpleValType& aVal) {
                std::string aSKey, aSVal;

                bool aRes = next(aSKey, aSVal);
                if ((aSKey.size() != sizeof (SimpleKeyType)) || (aSVal.size() != sizeof (SimpleValType)))
                    return false; // not fit
                if (aRes) {
                    //			aKey = *(SimpleKeyType*) (void*) aSKey.data();
                    //			aVal = *(SimpleValType*) (void*) aSVal.data();
                    ::memset((void*) &aKey, 0, sizeof (SimpleKeyType));
                    size_t aSize = sizeof (SimpleKeyType) > aSKey.length() ? aSKey.length() : sizeof (SimpleKeyType);
                    ::memcpy((void*) &aKey, (const void*) aSKey.data(), aSize);

                    aKey = Poco::ByteOrder::fromLittleEndian(aKey);

                    ::memset((void*) &aVal, 0, sizeof (SimpleValType));
                    aSize = sizeof (SimpleValType) > aSVal.length() ? aSVal.length() : sizeof (SimpleValType);
                    ::memcpy((void*) &aVal, (const void*) aSVal.data(), aSize);
                    aVal = Poco::ByteOrder::fromLittleEndian(aVal);

                }
                return aRes;
            }

            template <class SimpleKeyType>
            bool next(SimpleKeyType& aKey, std::string& aVal) {
                std::string aSKey;

                bool aRes = next(aSKey, aVal);
                if (aSKey.size() != sizeof (SimpleKeyType))
                    return false; // not fit
                if (aRes) {
                    ::memset((void*) &aKey, 0, sizeof (SimpleKeyType));
                    size_t aSize = sizeof (SimpleKeyType) > aSKey.length() ? aSKey.length() : sizeof (SimpleKeyType);
                    ::memcpy((void*) &aKey, (const void*) aSKey.data(), aSize);

                    aKey = Poco::ByteOrder::fromLittleEndian(aKey);

                    //			aKey = *(SimpleKeyType*) (void*) aSKey.data();
                }
                return aRes;
            }

            template <class SimpleValType>
            bool next(std::string& aKey, SimpleValType& aVal) {
                std::string aSVal;

                bool aRes = next(aKey, aSVal);
                if (aSVal.size() != sizeof (SimpleValType))
                    return false; // not fit
                if (aRes) {
                    //			aVal = *(SimpleValType*) (void*) aSVal.data();
                    ::memset((void*) &aVal, 0, sizeof (SimpleValType));
                    size_t aSize = sizeof (SimpleValType) > aSVal.length() ? aSVal.length() : sizeof (SimpleValType);
                    ::memcpy((void*) &aSVal, (const void*) aSVal.data(), aSize);

                    aVal = Poco::ByteOrder::fromLittleEndian(aVal);
                }
                return aRes;
            }


        };

        ///////////////////

        class AbstractKVStorage {
        public:

            typedef Poco::SharedPtr<AbstractKVStorage> Ptr;

            virtual ~AbstractKVStorage() {
            }
            typedef std::string KType;
            typedef std::string VType;
            typedef std::vector<KType> KList;
            typedef std::map<KType, VType> KVMap;
            typedef std::vector< std::pair < KType, VType> > KVList;
        public:



        public:

            virtual void compactData() {};

            virtual void syncCompactData() {};            
            
            virtual bool open() {
                return true;
            }

            virtual void close() {
            }

            virtual bool isReadable() const {
                return true;
            }

            virtual bool isWritable() const {
                return true;
            }

            virtual int32_t put(const KType &key, const char* data, uint32_t dataLength) {
                return _put(key, data, dataLength);
            }

            virtual int32_t put(const void* inKeyData,
                    const int& keyLen, const void* inData, const int& datalen) {
                return _put(inKeyData, keyLen, inData, datalen);
            }; // should be overridden

            virtual int32_t put(const KType &key, const VType &data) {
                return _put(key, data);
            }

            virtual int32_t multiPut(const KVMap& keyvals) {
                return _multiPut(keyvals);
            }

            virtual int32_t multiPut(const KVList& keyvals) {
                return _multiPut(keyvals);
            }

            virtual int32_t remove(const KType &key) {
                return _remove(key);
            }

            virtual int32_t multiRemove(const KList & keys) {
                return _multiRemove(keys);
            }

            virtual int32_t get(VType &_return, const KType &key) const {
                return _get(_return, key);
            }

            virtual int32_t get(const void* inKeyData, const int& keyLen, void* outData, const int& datalen) const {
                return _get(inKeyData, keyLen, outData, datalen);
            }

            virtual int32_t multiGet(KVMap &_return, const KList &keys) const {
                return _multiGet(_return, keys);
            }

            virtual bool has(const KType &key) const {
                return _has(key);
            }

            /*
             * of date value of existing key, error if it is not existed
             */
            virtual int32_t update(const KType &key, const VType &data) {
                return 0;
            }

            /*
             * add new key-value pair, error if it is already existed
             */
            virtual int32_t add(const KType &key, const VType &data) {
                return 0;
            }

            virtual void flush() {
            }

            virtual Poco::SharedPtr<AbstractCursor> iterate() {
                return Poco::SharedPtr<AbstractCursor>();
            }


#ifdef HAVE_OVERLOAD_TEMPLATE

            template <class SimpleKey, class SimpleVal>
            int32_t put(const SimpleKey& aKey, const SimpleVal& aVal) {
                SimpleKey aLitlleKey = Poco::ByteOrder::toLittleEndian(aKey);
                SimpleVal aLittleVal = Poco::ByteOrder::toLittleEndian(aVal);

                return _put((void*) & aLitlleKey, sizeof (SimpleKey), (void*) & aLittleVal, sizeof (SimpleVal));
            }

            template <class SimpleKey, class SimpleVal>
            int32_t multiPut(const std::map<SimpleKey, SimpleVal>& keysvals) {
                KVMap aKvs;
                typename std::map<SimpleKey, SimpleVal>::const_iterator aIt = keysvals.begin();
                for (; aIt != keysvals.end(); aIt++) {
                    SimpleKey aKey = Poco::ByteOrder::toLittleEndian(aIt->first);
                    SimpleVal aVal = Poco::ByteOrder::toLittleEndian(aIt->second);
                    aKvs[ std::string((const char*) (&aKey), sizeof (SimpleKey)) ] = std::string((const char*) (&aVal), sizeof (SimpleVal));
                }
                return _multiPut(aKvs);
            }

            template <class SimpleVal>
            int32_t multiPut(const std::map<KType, SimpleVal>& keysvals) {
                KVMap aKvs;
                typename std::map<KType, SimpleVal>::const_iterator aIt = keysvals.begin();
                for (; aIt != keysvals.end; aIt++) {
                    SimpleVal aVal = Poco::ByteOrder::toLittleEndian(aIt->second);
                    aKvs[ aIt->first ] = std::string((const char*) (&aVal), sizeof (SimpleVal));
                }
                return _multiPut(aKvs);
            }

            template <class SimpleKey>
            int32_t multiPut(const std::map<SimpleKey, VType>& keysvals) {
                KVMap aKvs;
                typename std::map<SimpleKey, VType>::const_iterator aIt = keysvals.begin();
                for (; aIt != keysvals.end; aIt++) {
                    SimpleKey aKey = Poco::ByteOrder::toLittleEndian(aIt->first);
                    aKvs[ std::string((const char*) (&aKey), sizeof (SimpleKey)) ] = aIt->second;
                }
                return _multiPut(aKvs);
            }

            template <class SimpleKey >
            int32_t put(const SimpleKey& aKey, const VType& aSVal) {
                SimpleKey aLittleKey = Poco::ByteOrder::toLittleEndian(aKey);
                return _put((void*) & aLittleKey, sizeof (SimpleKey), (void*) aSVal.data(), aSVal.length());
            }

            template <class SimpleVal>
            int32_t put(const KType& aSKey, const SimpleVal& aVal) {
                SimpleVal aLittleVal = Poco::ByteOrder::toLittleEndian(aVal);
                int32_t aRes = _put((void*) aSKey.data(), aSKey.length(), (void*) & aLittleVal, sizeof (SimpleVal));
                return aRes;
            }

            template <class SimpleKey, class SimpleVal>
            int32_t get(SimpleVal& aVal, const SimpleKey& aKey) const {
                SimpleKey aLittleKey = Poco::ByteOrder::toLittleEndian(aKey);

                int32_t aRes = _get((void*) & aLittleKey, sizeof (SimpleKey), (void*) & aVal, sizeof (SimpleVal));
                aVal = Poco::ByteOrder::fromLittleEndian(aVal);
                return aRes;
            }

            template <class SimpleKey >
            int32_t get(VType& aSVal, const SimpleKey& aKey) const {
                SimpleKey aLittleKey = Poco::ByteOrder::toLittleEndian(aKey);

                KType aSKey((char*) (void*) & aLittleKey, sizeof (SimpleKey));

                int32_t aRes = _get(aSVal, aSKey); // string - string
                return aRes;
            }

            template < class SimpleVal>
            int32_t get(SimpleVal& aVal, const KType& aSKey) const {
                int aRes = _get((void*) aSKey.data(), aSKey.length(), (void*) & aVal, sizeof (SimpleVal));
                aVal = Poco::ByteOrder::fromLittleEndian(aVal);
                return aRes;
            }

            template <class SimpleKey>
            int32_t remove(const SimpleKey& aKey) {
                SimpleKey aLittleKey = Poco::ByteOrder::toLittleEndian(aKey);
                return _remove(KType((char*) (void*) &aLittleKey, sizeof (SimpleKey)));
            }
#endif



        protected:
            // KV Storage

            virtual int32_t _put(const KType &key, const char* data, uint32_t dataLength) {
                return _put((void*) key.data(), key.length(), data, dataLength);
            }

            virtual int32_t _put(const KType &key, const VType &data) 
            {
                return _put((void*) key.data(), key.length(), data.data(), data.length());
            }


            virtual int32_t _put(const void* inKeyData, const int& keyLen, const void* inData, const int& datalen) = 0;

            virtual int32_t _multiPut(const KVMap& keyvals) {
                KVMap::const_iterator aIt = keyvals.begin();
                int32_t aRes = 0;
                for (; aIt != keyvals.end(); aIt++) {
                    aRes += _put(aIt->first, aIt->second);
                }
                return aRes;
            }// should override for some remote KVStorage

            virtual int32_t _multiPut(const KVList& keyvals) {
                KVList::const_iterator aIt = keyvals.begin();
                int32_t aRes = 0;
                for (; aIt != keyvals.end(); aIt++) {
                    aRes += _put(aIt->first, aIt->second);
                }
                return aRes;
            } // should override for some remote KVStorage

            virtual int32_t _remove(const KType &key) {
                return _remove((void*) key.data(), key.length());
            }

            virtual int32_t _remove(void* aKey, int aKeyLen) {
                return -1;
            }; // Must be overriden

            virtual int32_t _multiRemove(const KList & keys) {
                KList::const_iterator aIt = keys.begin();
                KList::const_iterator aEndIt = keys.end();
                int aRes = 0;
                for (; aIt != aEndIt; aIt++)
                    aRes += _remove(*aIt);
                return aRes;
            }

            virtual int32_t _get(VType &_return, const KType &key) const = 0;

            virtual int32_t _get(const void* inKeyData, const int& keyLen, void* outData, const int& datalen) const = 0;


            virtual int32_t _multiGet(KVMap &_return, const KList &keys) const = 0;

            virtual bool _has(const KType &key) const {
                return _has((void*) key.data(), key.length());
            }

            virtual bool _has(void* aKeyData, const int& aKeyLen) const {
                return true;
            } // need override
        };

        class NullStorage : public AbstractKVStorage {
        protected:

            virtual const char* name() const {
                return "NULL Storage ";
            }

            virtual void initialize(Poco::Util::Application& app) {
            };
            /// Initializes the subsystem.

            virtual void uninitialize() {
            };

            virtual int32_t _get(VType &_return, const KType &key) const {
                return -1;
            }

            virtual int32_t _get(const void* inKeyData, const int& keyLen, void* outData, const int& datalen) const {
                return -1;
            }

            virtual int32_t _multiGet(KVMap &_return, const KList &keys) const {
                return -1;
            }

        };

        enum TOperations {
            ENone = 0,
            ERead = 1,
            EWrite = 2,
            EReadWrite = 3
        };


    }
}



#endif /* _ABSTRACTKVSTORAGE_H */

