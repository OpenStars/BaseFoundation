/* 
 * File:   MultiKVStorage.cpp
 * Author: trungthanh
 * 
 * Created on March 1, 2010, 3:43 PM
 */

#include <list>

#include <Storage/MultiKVStorage.h>
#include <string.h>

using namespace openstars::storage;


void MultiKVStorage::_addStorage(const std::string& aName, const AbstractKVStorage::Ptr& stg) {
    if (stg)
        _totalStorages[aName] = stg;

}

void MultiKVStorage::_removeStorage(const std::string& aName) {
    TNameIndex::iterator aWriteIt = _writeStorageIndex.find(aName);
    if (aWriteIt != _writeStorageIndex.end()) {
        _writeStorages.erase(aWriteIt->second);
        _writeStorageIndex.erase(aWriteIt);
    }

    TNameIndex::iterator aReadIt = _readStorageIndex.find(aName);
    if (aReadIt != _readStorageIndex.end()) {
        _readStorages.erase(aReadIt->second);
        _readStorageIndex.erase(aReadIt);
    }
    _totalStorages.erase(aName);
}

void MultiKVStorage::_enableStorage(const std::string& aName, bool enable, TOperations operations) {
    if (_totalStorages.find(aName) == _totalStorages.end())
        return;

    if (operations & ERead) {
        // enable/disable  read
        TNameIndex::iterator aReadIt = _readStorageIndex.find(aName);
        if (enable) {
            if (aReadIt == _readStorageIndex.end()) {
                _readStorages.push_front(_totalStorages[aName]);
                _readStorageIndex[aName] = _readStorages.begin();
            }

        } else { // disable read
            if (aReadIt != _readStorageIndex.end()) {
                _readStorages.erase(aReadIt->second);
                _readStorageIndex.erase(aReadIt);
            }

        }
    }

    if (operations & EWrite) {
        TNameIndex::iterator aWriteIt = _writeStorageIndex.find(aName);
        if (enable) {
            if (aWriteIt == _writeStorageIndex.end()) {
                _writeStorages.push_front(_totalStorages[aName]);
                _writeStorageIndex[aName] = _writeStorages.begin();
            }

        } else { // disable read
            if (aWriteIt != _writeStorageIndex.end()) {
                _writeStorages.erase(aWriteIt->second);
                _writeStorageIndex.erase(aWriteIt);
            }

        }

    }
}

int32_t MultiKVStorage::_get(const void* inKeyData, const int& keyLen, void* outData, const int& datalen) const {
    TStorageList aStgs;
    getReadStorage(aStgs);
    KType aKey( (const char*) inKeyData, keyLen) ;
    VType aTmpVal;
    for (TStorageList::iterator aIt = aStgs.begin(); aIt != aStgs.end(); aIt++) {
        if (*aIt)
            if ((*aIt)->get(aTmpVal , aKey) == 0)
            {
                ::memcpy(outData, aTmpVal.data() , aTmpVal.length() > datalen ? datalen:aTmpVal.length()  );
                return 0;
            }
    }
    return -1;
};



int32_t MultiKVStorage::_get(VType &_return, const KType &key) const {
    TStorageList aStgs;
    getReadStorage(aStgs);
    for (TStorageList::iterator aIt = aStgs.begin(); aIt != aStgs.end(); aIt++) {
        if (*aIt)
            if ((*aIt)->get(_return , key) == 0)
                return 0;
    }
    return -1;
}

int32_t MultiKVStorage::_multiGet(KVMap &_return, const KList &keys) const {

    TStorageList aStgs;
    getReadStorage(aStgs);
    for (TStorageList::iterator aIt = aStgs.begin(); aIt != aStgs.end(); aIt++) {
        if (*aIt)
            if ((*aIt)->multiGet(_return , keys) == 0)
                return 0;
    }

    return -1;
}

bool MultiKVStorage::_has(void* aKeyData, const int& aKeyLen) const {
    TStorageList aStgs;
    getReadStorage(aStgs);
    KType aKey ( (const char*) aKeyData , aKeyLen );
    for (TStorageList::iterator aIt = aStgs.begin(); aIt != aStgs.end(); aIt++) {
        if (*aIt)
            if ((*aIt)->has(aKey) )
                return true;
    }
    return false;
} // need overide

//write operations

int32_t MultiKVStorage::_put(const void* inKeyData, const int& keyLen, const void* inData, const int& datalen) {
    TStorageList aStgs;
    this->getWriteStorage(aStgs);
    KType aKey ( (const char*) inKeyData , keyLen );
    VType aVal ( (const char*) inData, datalen) ;
    int32_t aRes = 0;
    for (TStorageList::iterator aIt = aStgs.begin(); aIt != aStgs.end(); aIt++) {
        if (*aIt)
            if ((*aIt)->put(aKey , aVal) != 0)
                aRes = -1;
    }
    return aRes;
}; // should be overridden

int32_t MultiKVStorage::_remove( void* aKeyData, int aKeyLen) {

    TStorageList aStgs;
    this->getWriteStorage(aStgs);
    KType aKey ( (const char*) aKeyData , aKeyLen );

    int32_t aRes = 0;
    for (TStorageList::iterator aIt = aStgs.begin(); aIt != aStgs.end(); aIt++) {
        if (*aIt)
            if ((*aIt)->remove(aKey ) != 0)
                aRes = -1;
    }
    return aRes;
}
void MultiKVStorage::flush(){
    TStorageList aStgs;
    this->getWriteStorage(aStgs);
    for (TStorageList::iterator aIt = aStgs.begin(); aIt != aStgs.end(); aIt++) {
        if (*aIt)
            (*aIt)->flush();
    }
}

int32_t MultiKVStorage::update(const KType &key, const VType &data)
{
    TStorageList aStgs;
    this->getWriteStorage(aStgs);

    int32_t aRes = 0;
    for (TStorageList::iterator aIt = aStgs.begin(); aIt != aStgs.end(); aIt++) {
        if (*aIt)
            if ((*aIt)->update(key, data ) != 0)
                aRes = -1;
    }
    return aRes;
}

/*
 * add new key-value pair, error if it is already existed
 */
int32_t MultiKVStorage::add(const KType &key, const VType &data)
{
    TStorageList aStgs;
    this->getWriteStorage(aStgs);

    int32_t aRes = 0;
    for (TStorageList::iterator aIt = aStgs.begin(); aIt != aStgs.end(); aIt++) {
        if (*aIt)
            if ((*aIt)->add(key, data ) != 0)
                aRes = -1;
    }
    return aRes;
}

int32_t MultiKVStorage::put(const KType &key, const VType &data)
{
    TStorageList aStgs;
    this->getWriteStorage(aStgs);

    int32_t aRes = 0;
    for (TStorageList::iterator aIt = aStgs.begin(); aIt != aStgs.end(); aIt++) {
        if (*aIt)
            if ((*aIt)->put(key, data ) != 0)
                aRes = -1;
    }
    return aRes;
}
