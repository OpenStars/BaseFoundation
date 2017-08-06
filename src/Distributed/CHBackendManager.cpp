/* 
 * File:   CHBackendManager.cpp
 * Author: trungthanh
 * 
 * Created on August 30, 2012, 3:57 PM
 */

#include "Distributed/CHBackendManager.h"
#include "Distributed/BackendActiveChecker.h"

#include <vector>
#include <algorithm>
#include <set>

namespace openstars{ namespace distributed {
CHBackendManager::CHBackendManager() : _backends()
{
}

//CHBackendManager::CHBackendManager(const CHBackendManager& orig) {
//}

CHBackendManager::~CHBackendManager() {
    
}

void CHBackendManager::getBackendRByHash(BackendInfo &_return, const HashType aHashKey){
    ScopedLockType aLock(_mutex);
    _getBackendRByHash(_return, aHashKey);
}

void CHBackendManager::getListBackendRByHash(std::vector<BackendInfo> & _return, const HashType aHashKey){
    ScopedLockType aLock(_mutex);
    _getListBackendRByHash(_return, aHashKey);
}

void CHBackendManager::getBackendWByHash(std::vector<BackendInfo> & _return, const HashType aHashKey){
    ScopedLockType aLock(_mutex);
    _getBackendWByHash(_return, aHashKey);
}
    
    // these function is not used very frequently
void CHBackendManager::addBackend(const BackendInfo& aBackend){
    ScopedLockType aLock(_mutex, true);
    _addBackend(aBackend);
}

void CHBackendManager::removeBackend(const BackendInfo& aBackend){
    ScopedLockType aLock(_mutex, true);
    _removeBackend(aBackend);
}

//////////////////////// non threadsafe functions
void CHBackendManager::_getBackendRByHash(BackendInfo &_return, const HashType aHashKey){
    size_t aSize = _backends.size();
    if (aSize == 0){
        _return.setHost("");
        _return.setPort(-1);                
        return;
    }
    BackendInfo tmp("", -1, aHashKey, 1);
    TBackendListType::const_iterator aIt = std::lower_bound( _backends.begin(), _backends.end(), tmp );
    if (aIt == _backends.end() )
        _return = *(_backends.begin());
    else
        _return = *aIt;

    // check status of backend
    BackendInfo::TStatus aStatus = _return.getStatus();
    if ( aStatus != BackendInfo::EReady && aStatus != BackendInfo::EInActiveForRemoving ){
        // read for previous node
        if (aSize == 1) { // no available node
            _return.setPort(-1);
            return;
        }
        if (aIt != _backends.end() ){
            aIt ++;  // 
            if (aIt == _backends.end() )
                _return = *(_backends.begin());
            else
                _return = *aIt;
            
        } else {
            _return = *(_backends.begin() + 1);
        }
        
    }

    
}

// tam thoi lay 1 cai da.
void CHBackendManager::_getListBackendRByHash(std::vector<BackendInfo> & _return, const HashType aHashKey){
//    BackendInfo aBackend("",-1,0);
//    _getBackendRByHash(aBackend, aHashKey);
//    if (aBackend.getHost().length() > 0 && aBackend.getPort() > 0)
//        _return.push_back(aBackend);


    _getBackendWByHash(_return, aHashKey);
}

void CHBackendManager::_getBackendWByHash(std::vector<BackendInfo> & _return, const HashType aHashKey){
    BackendInfo tmp("", -1, aHashKey, 1);
    size_t aSize = _backends.size();
    if (aSize == 0){
        return;
    }    
    TBackendListType::const_iterator aIt = std::lower_bound( _backends.begin(), _backends.end(), tmp );
    bool goFirst = false;
    if (aIt == _backends.end() ){
        tmp = *(_backends.begin());
	goFirst = true;
    }
    else
        tmp = *aIt;
    
    _return.push_back(tmp);
    BackendInfo::TStatus aStatus = tmp.getStatus();
    if (aSize == 1)
	return;

    if (aStatus == BackendInfo::EReady)
    {
	// Nếu có các nút ở cùng 1 vị trí trong ring thì add cả vào 
	if (goFirst)
	    aIt = _backends.begin();
	while (++aIt != _backends.end())
	{
	    if (aIt->getStartRange() == tmp.getStartRange() && aIt->getStatus() == BackendInfo::EReady)
	    {
		_return.push_back(*aIt);
	    }
	    else
		break;
	}
	return;
    }
    
    //write data to previous node, đoạn này chưa chuẩn lắm 
    if (aIt != _backends.end() ){
        aIt ++;  // 
        if (aIt == _backends.end() )
            tmp = *(_backends.begin());
        else
            tmp = *aIt;

    } else {
        tmp = *(_backends.begin() + 1);
    }
    _return.push_back(tmp);
    
}

void CHBackendManager::replaceAll(std::vector<BackendInfo>& newBackends)
{
    std::vector<BackendInfo> oldBackends;
    {
        ScopedLockType aLock(_mutex, false);
        oldBackends = _backends;
    }

    std::sort(newBackends.begin(), newBackends.end() );
    std::vector<BackendInfo> missingBackends;
    std::vector<BackendInfo> addedBackends;
    
    std::set_difference(oldBackends.begin(), oldBackends.end()
            ,newBackends.begin(), newBackends.end()
            ,std::inserter(missingBackends, missingBackends.end() ) );

    std::set_difference(newBackends.begin(), newBackends.end()
            ,oldBackends.begin(), oldBackends.end()
            ,std::inserter(addedBackends, addedBackends.end() ) );
    
    if (missingBackends.size() == 0 && addedBackends.size() > 0)
    {
        ScopedLockType aLock(_mutex, true);
        _backends.swap(newBackends);
        std::sort(_backends.begin(), _backends.end() );    
        return;
    } 
    else {
        // check missing backend
        BackendActiveChecker aChecker;
        
        for (std::vector<BackendInfo>::iterator aIt=missingBackends.begin(); aIt != missingBackends.end(); aIt++)
        {
            //neu chet that thi remove di
            if (!aChecker.checkBackend(*aIt))
                this->removeBackend(*aIt);
            else //van con song ma mat zookeeper
                logWrongDeadBackend(*aIt);
                
        }
        
        //for (auto aIt = addedBackends.begin(); aIt != addedBackends.end() ; aIt++)
        if (addedBackends.size() > 0)
        {
            ScopedLockType aLock(_mutex, true);
            _backends.insert(_backends.end(), addedBackends.begin(), addedBackends.end() );
            std::sort(_backends.begin(), _backends.end() );    
            /*
            if (aChecker.checkBackend(*aIt))
                this->addBackend(*aIt);
            else
                this->logWrongLiveBackend(*aIt);
             */
        }
        
    }
    
    
    
}

// these function is not used very frequently
void CHBackendManager::_addBackend(const BackendInfo& aBackend){
    this->_backends.push_back(aBackend);
    std::sort(_backends.begin(), _backends.end() );
}


void CHBackendManager::_removeBackend(const BackendInfo& aBackend){
    BackendInfo::EndpointEqual isEqual;
    for (int aIndex = _backends.size() - 1; aIndex >= 0; aIndex--){
        if ( isEqual( _backends[aIndex] , aBackend ) )
            _backends.erase( _backends.begin() + aIndex );
    }
}

void CHBackendManager::updateBackend(const BackendInfo& aBackend){
    ScopedLockType aLock(_mutex, true);
    _updateBackend(aBackend);
    
}

void CHBackendManager::_updateBackend(const BackendInfo& aBackend){
    size_t aSize = _backends.size();
    for (size_t aIndex = 0; aIndex < aSize; aIndex++){
        if (_backends[aIndex] == aBackend){
            _backends[aIndex] = aBackend; // just funny. 
        }
    }
}

} }