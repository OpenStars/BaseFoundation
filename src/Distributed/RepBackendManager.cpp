/* 
 * File:   RepBackendManager.cpp
 * Author: trungthanh
 * 
 * Created on August 29, 2012, 11:55 AM
 */

#include "Distributed/RepBackendManager.h"
#include <vector>

namespace openstars{ namespace distributed {

RepBackendManager::RepBackendManager() : _backends()
,_currentCount(0)
,_currentIndex(0)
{
    _currentIndex = 0;
}

//RepBackendManager::RepBackendManager(const RepBackendManager& orig) {
//}

RepBackendManager::~RepBackendManager() {
    
}

void RepBackendManager::getBackendRByHash(BackendInfo &_return, const HashType aHashKey){
    ScopedLockType aLock(_mutex);
    _getBackendRByHash(_return, aHashKey);
}

void RepBackendManager::getListBackendRByHash(std::vector<BackendInfo> & _return, const HashType aHashKey){
    ScopedLockType aLock(_mutex);
    _getListBackendRByHash(_return, aHashKey);
}

void RepBackendManager::getBackendWByHash(std::vector<BackendInfo> & _return, const HashType aHashKey){
    ScopedLockType aLock(_mutex);
    _getBackendWByHash(_return, aHashKey);
}
    
    // these function is not used very frequently
void RepBackendManager::addBackend(const BackendInfo& aBackend){
    ScopedLockType aLock(_mutex, true);
    _addBackend(aBackend);
}

void RepBackendManager::removeBackend(const BackendInfo& aBackend){
    ScopedLockType aLock(_mutex, true);
    _removeBackend(aBackend);
}
//////////////////////// non threadsafe functions
void RepBackendManager::_getBackendRByHash(BackendInfo &_return, const HashType aHashKey){
    if (_backends.size() == 0){
        _return.setHost("");
        _return.setPort(-1);                
        return;
    }
    if (_currentIndex >= _backends.size() || _currentIndex < 0 )
        _currentIndex = 0;
    _currentCount ++ ;
    _return = _backends[ _currentIndex ];
    if (_currentCount > _return.getWeight()  )
    {
        _currentCount = 0;
        _currentIndex ++;
    }
    
}

// tam thoi lay 1 cai da.
void RepBackendManager::_getListBackendRByHash(std::vector<BackendInfo> & _return, const HashType aHashKey){
    BackendInfo aBackend("",-1,0);
    _getBackendRByHash(aBackend, aHashKey);
    if (aBackend.getHost().length() > 0 && aBackend.getPort() > 0)
        _return.push_back(aBackend);
    
}
void RepBackendManager::_getBackendWByHash(std::vector<BackendInfo> & _return, const HashType aHashKey){
    // write to all
    _return = _backends;
}

// these function is not used very frequently
void RepBackendManager::_addBackend(const BackendInfo& aBackend){
    this->_backends.push_back(aBackend);
}
void RepBackendManager::_removeBackend(const BackendInfo& aBackend){
    BackendInfo::EndpointEqual isEqual;
    for (int aIndex = _backends.size() - 1; aIndex >= 0; aIndex--){
        if ( isEqual( _backends[aIndex] , aBackend ) )
            _backends.erase( _backends.begin() + aIndex );
    }
}

void RepBackendManager::replaceAll(std::vector<BackendInfo>& newBackends)
{
    ScopedLockType aLock(_mutex, true);
    _backends.swap(newBackends);
    std::sort(_backends.begin(), _backends.end() );    
}


} }