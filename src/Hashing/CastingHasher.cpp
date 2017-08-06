/* 
 * File:   CastingHasher.cpp
 * Author: trungthanh
 * 
 * Created on October 10, 2012, 12:33 PM
 */

#include <Hashing/CastingHasher.h>
#include "Poco/ByteOrder.h"
#include <string.h>
#include <iostream>
using namespace std;

namespace openstars { namespace hashing {

HashType CastingHasher::hash(const std::string& aKey)  const{
    HashType aHash = 0;
    size_t aSize = sizeof(HashType);
    if (aSize > aKey.length() )
	aSize = aKey.length();
    ::memcpy(&aHash, (const void*)aKey.data(), aSize );
    return Poco::ByteOrder::fromLittleEndian(aHash);
}

HashType CastingHasher::hash(const int32_t aKey) const {
    return (HashType)(aKey);
    //    HashType aHash = aKey;
//    ::memcpy((void*)&aHash, (const void*)&aKey, sizeof(aKey) );
//    return aHash;
}

HashType CastingHasher::hash(const int64_t aKey) const {
    return aKey;
    
}

HashType CastingHasher::hash(const void* aKey, int keySize)  const{
    HashType aHash = 0;
    int aSize = sizeof(HashType);
    if (aSize > keySize)
	aSize = keySize;
    ::memcpy(&aHash, aKey, keySize );
    return Poco::ByteOrder::fromLittleEndian(aHash);
}

} }