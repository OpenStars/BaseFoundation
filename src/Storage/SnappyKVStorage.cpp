/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SnappyKVStorage.cpp
 * Author: trungthanh
 * 
 * Created on March 12, 2018, 10:16 PM
 */


#include "Storage/SnappyKVStorage.h"
#include "snappy/snappy.h"

namespace openstars {
namespace storage {


SnappyKVStorage::SnappyKVStorage(AbstractKVStorage::Ptr aBackendKV):_kv(aBackendKV) {
}


SnappyKVStorage::~SnappyKVStorage() {
}

int32_t SnappyKVStorage::_put(const void* inKeyData, const int& keyLen,
        const void* inData, const int& datalen)
{
    if (!_kv)
        return -1;
    std::string compressedData;
    snappy::Compress((const char*)inData, datalen, &compressedData);
    std::string aKey((const char*)inKeyData, keyLen);

    return _kv->put(aKey, compressedData);
}

int32_t SnappyKVStorage::_get(VType &_return, const KType &key) const
{
    if (!_kv)
        return -1;
    std::string aRawVal;
    int32_t aRes =  _kv->get(aRawVal, key) ;
    if (aRes != 0)
        return aRes;
    if (!snappy::Uncompress(aRawVal.data(), aRawVal.length(), &_return) )
        _return = aRawVal;
    return 0;   
}

int32_t SnappyKVStorage::_get(const void* inKeyData, const int& keyLen,
        void* outData, const int& datalen) const
{
    if (!_kv)
        return -1;
    std::string aKey((const char*)inKeyData, keyLen);
    std::string aValue;
    int32_t aRes = _get(aValue, aKey);
    if (aRes !=0 )
        return aRes;
    size_t aLen = datalen > aValue.length()? aValue.length(): datalen;
    ::memcpy(outData, aValue.data(), aLen);
    return 0;
}

int32_t SnappyKVStorage::_multiGet(KVMap &_return, const KList &keys) const
{

    size_t aSize  = keys.size();
    
    for (size_t aIndex = 0; aIndex < aSize; aIndex++)
    {
	VType aValue;
	if (this->_get(aValue, keys[aIndex] ) == 0)
	{
	    if (aValue.length() > 0 )
		_return[keys [aIndex] ] = aValue;
	}
    }
    return (_return.size() == keys.size() ? 0: -1);
    
}


} }