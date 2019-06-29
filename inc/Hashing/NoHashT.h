/* 
 * File:   NoHash64.h
 * Author: trungthanh
 *
 * Created on July 24, 2011, 10:39 PM
 */

#ifndef NOHASH64_H
#define	NOHASH64_H

#include <string>
#include "Poco/ByteOrder.h"

template <class TType>
class NoHashT {
public:

    NoHashT() {
    };
public:

    template <class T>
    TType operator () (const T& key)const {
        return *(TType*) (&key);
    }

    TType operator () (const std::string& key)const {
        if (key.length() == 0)
            return 0;
        TType aRes = 0;
        void* aChar = (void*) (&aRes);
        size_t aLength = key.length();
        if (aLength > sizeof (TType))
            aLength = sizeof (TType);
        ::memcpy((void*) aChar, (const void*) key.data(), aLength);
        return Poco::ByteOrder::fromLittleEndian(aRes);
        //return *(int64_t*)( key.data() );                
    }
    
    TType operator () (const void *kBuf_, uint16_t kSize_ )const {
        if (kSize_ <= 0)
            return 0;
        TType aRes = 0;
        void* aChar = (void*) (&aRes);
        size_t aLength = kSize_;
        if (aLength > sizeof (TType))
            aLength = sizeof (TType);
        ::memcpy((void*) aChar, kBuf_, aLength);
        return Poco::ByteOrder::fromLittleEndian(aRes);
        
    }

    std::string unHash(TType aInt)const {
        TType aLittleInt = Poco::ByteOrder::toLittleEndian(aInt);
        return std::string((char*) &aLittleInt, sizeof (TType) );
    }


};

class NoHash64 {
public:

    NoHash64() {
    };
public:

    template <class T>
    int64_t operator () (const T& key)const {
        return *(int64_t*) (&key);
    }

    int64_t operator () (const std::string& key)const {
        if (key.length() == 0)
            return 0;
        int64_t aRes = 0;
        void* aChar = (void*) (&aRes);
        size_t aLength = key.length();
        if (aLength > sizeof (int64_t))
            aLength = sizeof (int64_t);
        ::memcpy((void*) aChar, (const void*) key.data(), aLength);
        return Poco::ByteOrder::fromLittleEndian(aRes);
        //return *(int64_t*)( key.data() );                
    }

    int64_t operator () (const void *kBuf_, uint16_t kSize_ )const {
        if (kSize_ <= 0)
            return 0;
        int64_t aRes = 0;
        void* aChar = (void*) (&aRes);
        size_t aLength = kSize_;
        if (aLength > sizeof (int64_t))
            aLength = sizeof (int64_t);
        ::memcpy((void*) aChar, kBuf_, aLength);
        return Poco::ByteOrder::fromLittleEndian(aRes);
        
    }

    
    std::string unHash(int64_t aInt)const {
        int64_t aLittleInt = Poco::ByteOrder::toLittleEndian(aInt);
        return std::string((char*) &aLittleInt, sizeof (aInt));
    }


};


#endif	/* NOHASH64_H */

