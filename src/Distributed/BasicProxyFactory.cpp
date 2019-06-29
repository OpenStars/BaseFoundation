/* 
 * File:   BasicProxyFactory.cpp
 * Author: trungthanh
 * 
 * Created on September 5, 2012, 3:04 PM
 */

#include <stdint.h>
#include "Distributed/BasicProxyFactory.h"
#include "Distributed/CHBackendManager.h"
#include "Distributed/RepBackendManager.h"
#include "Hashing/CastingHasher.h"
#include "Hashing/DefaultHasher.h"
#include "Hashing/MurmurHasher.h"

namespace openstars {
    namespace distributed {

        std::string BasicProxyFactory::_backendMngrType; // type of backend manager
        std::string BasicProxyFactory::_backendInfosFileName;
        std::string BasicProxyFactory::_zkServers;
        std::string BasicProxyFactory::_zkPath;
        std::string BasicProxyFactory::_hasherType;

        void BasicProxyFactory::init(Poco::Util::Application& app) {
            if (_backendMngrType.length() == 0)
                _backendMngrType = app.config().getString("service.distributed.backendmanager.type", "consistent-hash");

            if (_backendInfosFileName.length() == 0) {
                _backendInfosFileName = app.config().getString("service.distributed.backendmanager.cfg", "zproxy.conf");
            }

            if (_zkServers.length() == 0) {
                _zkServers = app.config().getString("service.distributed.zookeeper-servers", "");
            }

            if (_zkPath.length() == 0) {
                _zkPath = app.config().getString("service.distributed.backends.zookeeper-basepath", "");
            }

            if (_hasherType.length() == 0)
                _hasherType = app.config().getString("service.distributed.hasher", "");

            cout << "zkServers:" << _zkServers << " zkPath " << _zkPath << endl;
        }

        BackendManager* BasicProxyFactory::getBackendManager() {
            static openstars::distributed::BackendManager* aBackendMng = NULL;
            static Poco::SharedPtr< openstars::distributed::BackendManager > aBEPtr;
            cout << "BasicProxyFactory::getBackendManager" << endl;
            if (aBackendMng == NULL) {
                if (_backendMngrType == "consistent-hash")
                    aBackendMng = new openstars::distributed::CHBackendManager();
                else if (_backendMngrType == "roundrobin" || _backendMngrType == "round-robin") {
                    aBackendMng = new openstars::distributed::RepBackendManager();
                }
                else {
                    aBackendMng = new openstars::distributed::CHBackendManager();
                }
                aBEPtr = aBackendMng;

                if (_backendInfosFileName.length() > 0)
                    aBackendMng->load(_backendInfosFileName);

                if (_zkServers.length() > 0 && _zkPath.length() > 0)
                    aBackendMng->loadZkConfig(_zkServers, _zkPath);

                if (_hasherType == "casting") {
                    aBackendMng->setHasher(new openstars::hashing::CastingHasher);
                }
                else if (_hasherType == "murmur") {
                    aBackendMng->setHasher(new openstars::hashing::MurmurHasher);
                } else if (_hasherType == "default") {
                    aBackendMng->setHasher(new openstars::hashing::DefaultHasher);
                }
            }
            return aBackendMng;
        }

    }
}