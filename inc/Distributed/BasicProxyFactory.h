/* 
 * File:   BasicProxyFactory.h
 * Author: trungthanh
 *
 * Created on September 5, 2012, 3:04 PM
 */

#ifndef BASICPROXYFACTORY_H
#define BASICPROXYFACTORY_H

#include <Poco/Util/Application.h>
#include "Distributed/BackendManager.h"

namespace openstars {
    namespace distributed {

        class BasicProxyFactory {
        public:
            static void init(Poco::Util::Application& app);
            static BackendManager* getBackendManager();
        public:
            static std::string _backendMngrType; // type of backend manager
            static std::string _backendInfosFileName;
            static std::string _hasherType;

            static std::string _zkServers;
            static std::string _zkPath;
        };

    }
}

#endif /* BASICPROXYFACTORY_H */

