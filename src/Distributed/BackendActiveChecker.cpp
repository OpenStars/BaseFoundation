/* 
 * File:   BackendActiveChecker.cpp
 * Author: trungthanh
 */

#include "Distributed/BackendActiveChecker.h"
#include "Poco/Net/StreamSocket.h"

namespace openstars{ namespace distributed {

BackendActiveChecker::BackendActiveChecker():_callback(NULL) {
}


BackendActiveChecker::~BackendActiveChecker() {
}

bool BackendActiveChecker::checkBackend(const BackendInfo& aBackend)
{
    Poco::Net::StreamSocket aSocket;
    Poco::Net::SocketAddress addr(aBackend.getHost(), aBackend.getPort());
    try {
        Poco::Timespan timeout(100000); /*100ms*/
        aSocket.connect(addr, timeout);
        aSocket.close();
    } catch(...)
    {
        try { 
            aSocket.close(); 
        } catch(...)
        {
            
        }
        if (this->_callback)
            _callback->deadBackend(aBackend);
        return false;
    }
    if (this->_callback)
        _callback->goodBackend(aBackend);
    return true;

    
}



}}