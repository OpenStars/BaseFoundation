/* 
 * File:   DefaultHasher.cpp
 * Author: trungthanh
 * 
 * Created on October 10, 2012, 12:21 PM
 */

#include <Hashing/DefaultHasher.h>

#include <functional>
#include "hashkit/hashkit.h"

#define default_hash_fn hashkit_jenkins


namespace openstars { namespace hashing {

HashType DefaultHasher::hash(const std::string& aKey) const {
    return ::default_hash_fn(aKey.data(), aKey.size() * sizeof (char), 0);
}

HashType DefaultHasher::hash(const int32_t aKey) const {
    typedef int32_t value_type;
    return ::default_hash_fn(reinterpret_cast<const char*> (&aKey), sizeof (value_type), 0);    
}

HashType DefaultHasher::hash(const int64_t aKey)  const{
    typedef int64_t value_type;
    return ::default_hash_fn(reinterpret_cast<const char*> (&aKey), sizeof (value_type), 0);    
    
}

HashType DefaultHasher::hash(const void* aKey, int keySize) const{
    return default_hash_fn( reinterpret_cast<const char*>(aKey), keySize, 0  );
}

HashType DefaultHasher::hashdata(const void* aKey, int keySize){
    return default_hash_fn( reinterpret_cast<const char*>(aKey), keySize, 0  );
}

} }