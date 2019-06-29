/* 
 * File:   BasicBackendManagerHandler.cpp
 * Author: trungthanh
 * 
 * Created on September 5, 2012, 3:38 PM
 */

#include "Distributed/BasicBackendManagerHandler.h"

namespace openstars{ namespace distributed{

BasicBackendManagerHandler::BasicBackendManagerHandler(BackendManager* aMngr):
_backendMngr(aMngr){
}


BasicBackendManagerHandler::~BasicBackendManagerHandler() {
}

// assign from model list to thrift list
static void assign(std::vector<Up::Distributed::TBackendInfo> & _return, const std::vector< Up::Distributed::BackendInfo>& aBackends){
    _return.resize( aBackends.size() );
    for (int aIndex = 0; aIndex < aBackends.size(); aIndex++)
    {
        aBackends[aIndex].assignTo( _return[aIndex] );
    }   
}

void BasicBackendManagerHandler::getBackends(std::vector<Up::Distributed::TBackendInfo> & _return){
    if (_backendMngr){
        std::vector< Up::Distributed::BackendInfo> aBackends;
        _backendMngr->getAllBackends(aBackends);
        assign(_return, aBackends);
    }
}

void BasicBackendManagerHandler::getBEWrite(std::vector<Up::Distributed::TBackendInfo> & _return, const std::string& key){
    if (_backendMngr){
        std::vector< Up::Distributed::BackendInfo> aBackends;
        _backendMngr->getBackendW(aBackends , key);
        assign(_return, aBackends);
    }

        
}

void BasicBackendManagerHandler::getBERead(std::vector<Up::Distributed::TBackendInfo> & _return, const std::string& key) {
    if (_backendMngr){
        std::vector< Up::Distributed::BackendInfo> aBackends;
        _backendMngr->getListBackendR(aBackends , key);
        assign(_return, aBackends);
    }
    
}

void BasicBackendManagerHandler::addBackend(const Up::Distributed::TBackendInfo& aNode) {
    if (_backendMngr){
        Up::Distributed::BackendInfo aBackend("",-1,1);
        aBackend = aNode;
        _backendMngr->addBackend(aBackend);
    }    
}

void BasicBackendManagerHandler::updateBackend(const Up::Distributed::TBackendInfo& aNode) {
    if (_backendMngr){
        Up::Distributed::BackendInfo aBackend("",-1,1);
        aBackend = aNode;
        _backendMngr->updateBackend(aBackend);
    }    
    
}

void BasicBackendManagerHandler::removeBackend(const Up::Distributed::TBackendInfo& aNode) {
    if (_backendMngr){
        Up::Distributed::BackendInfo aBackend("",-1,1);
        aBackend = aNode;
        _backendMngr->removeBackend(aBackend);
    }    
    
}


} }