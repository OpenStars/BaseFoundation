/* 
 * File:   BackendActiveChecker.h
 * Author: trungthanh
 *
 * Created on March 5, 2014, 6:31 PM
 */

#ifndef BACKENDACTIVECHECKER_H
#define	BACKENDACTIVECHECKER_H

#include "Poco/Net/SocketStream.h"
#include "Distributed/BackendInfo.h"

namespace openstars{ namespace distributed {
    
class BackendActiveChecker {
public:
    class ICallback{
    public:
        virtual ~ICallback(){};
        virtual void deadBackend(const BackendInfo& aBackend) = 0;
        virtual void goodBackend(const BackendInfo& aBackend) = 0;
    };
public:
    BackendActiveChecker();
    
    virtual ~BackendActiveChecker();
       
    void setCallback(ICallback* callback){_callback = callback ;}
public:
    /*
     * check backend healthy or dead by connect to its endpoints
     */
    virtual bool checkBackend(const BackendInfo& aBackend);
    
private:
    BackendActiveChecker(const BackendActiveChecker& orig);
        
    ICallback* _callback;
};

}}
#endif	/* BACKENDACTIVECHECKER_H */

