/* 
 * File:   BackendManager.cpp
 * Author: trungthanh
 * 
 * Created on August 21, 2012, 2:28 PM
 */

#include "Distributed/BackendManager.h"
#include "Poco/Path.h"
#include "Poco/NumberParser.h"
#include "Poco/StringTokenizer.h"

#include <fstream>
//#include "distributed_types.h"

#include <Hashing/DefaultHasher.h>

/** ZK */
#include "zkadapter/zkadapter.h"


using namespace std;

namespace openstars {
    namespace distributed {

        class BackendManager::BackendManagerPrivate : public ZKEventListener {
        public:

            BackendManagerPrivate(BackendManager* p) : _zkClient(), parent(p) {
            }

            virtual ~BackendManagerPrivate() {
            }
            friend class BackendManager;
            virtual void eventReceived(const EventSource<ZKWatcherEvent> &source, const ZKWatcherEvent &e);

        private:
            Poco::SharedPtr<ZooKeeperAdapter> _zkClient;
            BackendManager* parent;
        };

        BackendManager::BackendManager() : startChecking(this, &BackendManager::checkConnectionImpl)
        , _pkeyHasher(NULL)
        , _keyHasher()
        , _private(new BackendManager::BackendManagerPrivate(this))
        , _zkServers()
        , _zkPath()
        , _runningChecking(false)
        , _doneCheckingEvent() {
            setHasher(new openstars::hashing::DefaultHasher);
        }

        BackendManager::~BackendManager() {
            this->stopChecking();
        }

        void MultiOpClusterInfo::add(const BackendInfo& aBackend, const int32_t aKey) {
            std::vector< TMultiKeysBackendInfo > ::iterator aIt =
                    std::lower_bound(infos.begin(), infos.end(), aBackend);
            if (aIt != infos.end() && *aIt == aBackend) {
                aIt->_i32Keys.push_back(aKey);
            } else {
                TMultiKeysBackendInfo aInfo;
                aInfo._backend = aBackend;
                aInfo._i32Keys.push_back(aKey);
                infos.insert(aIt, aInfo);
            }
        }

        void MultiOpClusterInfo::add(const BackendInfo& aBackend, const int64_t aKey) {
            std::vector< TMultiKeysBackendInfo > ::iterator aIt =
                    std::lower_bound(infos.begin(), infos.end(), aBackend);
            if (aIt != infos.end() && *aIt == aBackend) {
                aIt->_i64Keys.push_back(aKey);
            } else {
                TMultiKeysBackendInfo aInfo;
                aInfo._backend = aBackend;
                aInfo._i64Keys.push_back(aKey);
                infos.insert(aIt, aInfo);
            }

        }

        void MultiOpClusterInfo::add(const BackendInfo& aBackend, const std::string& aKey) {
            std::vector< TMultiKeysBackendInfo > ::iterator aIt =
                    std::lower_bound(infos.begin(), infos.end(), aBackend);
            if (aIt != infos.end() && *aIt == aBackend) {
                aIt->_stringKeys.push_back(aKey);
            } else {
                TMultiKeysBackendInfo aInfo;
                aInfo._backend = aBackend;
                aInfo._stringKeys.push_back(aKey);
                infos.insert(aIt, aInfo);
            }

        }


        /////////////////////////

        void BackendManager::setHasher(const Poco::SharedPtr<openstars::hashing::Hasher>& aHasher) {
            this->_keyHasher = aHasher;
            _pkeyHasher = _keyHasher.get();
        }

        // using default hash function

        HashType BackendManager::hash(const std::string& aKey) {
            if (_pkeyHasher == NULL)
                return 0;
            return _pkeyHasher->hash(aKey);
        }

        HashType BackendManager::hash(const int32_t aKey) {
            if (_pkeyHasher == NULL)
                return 0;
            return _pkeyHasher->hash(aKey);
        }

        HashType BackendManager::hash(const int64_t aKey) {
            if (_pkeyHasher == NULL)
                return 0;
            return _pkeyHasher->hash(aKey);
        }

        HashType BackendManager::hash(const void* aKey, int keySize) {
            if (_pkeyHasher == NULL)
                return 0;
            return _pkeyHasher->hash(aKey, keySize);
        }

        void BackendManager::getBackendR(BackendInfo &_return, const std::string& aKey) {
            HashType aHash = hash(aKey);
            this->getBackendRByHash(_return, aHash);
#ifdef _DEBUG
            cout << "Read hash: " << aHash << " backend: " << _return.getHost() << ":" << _return.getPort() << " " << _return.getStartRange() << endl;
#endif
        }

        void BackendManager::getBackendR(BackendInfo &_return, const int32_t aKey) {
            HashType aHash = hash(aKey);
            return this->getBackendRByHash(_return, aHash);
        }

        void BackendManager::getBackendR(BackendInfo &_return, const int64_t aKey) {
            HashType aHash = hash(aKey);
            return this->getBackendRByHash(_return, aHash);
        }

        void BackendManager::getBackendR(BackendInfo &_return, const void* aKey, int keySize) {
            HashType aHash = hash(aKey, keySize);
            this->getBackendRByHash(_return, aHash);

        }

        void BackendManager::getListBackendR(std::vector<BackendInfo> & _return, const std::string& aKey) {
            HashType aHash = hash(aKey);
            return this->getListBackendRByHash(_return, aHash);
        }

        void BackendManager::getListBackendR(std::vector<BackendInfo> & _return, const int32_t aKey) {
            HashType aHash = hash(aKey);
            return this->getListBackendRByHash(_return, aHash);

        }

        void BackendManager::getListBackendR(std::vector<BackendInfo> & _return, const int64_t aKey) {
            HashType aHash = hash(aKey);
            return this->getListBackendRByHash(_return, aHash);

        }

        void BackendManager::getListBackendR(std::vector<BackendInfo> & _return, const void* aKey, int keySize) {
            HashType aHash = hash(aKey, keySize);
            return this->getListBackendRByHash(_return, aHash);

        }

        void BackendManager::getBackendW(std::vector<BackendInfo> & _return, const std::string& aKey) {
            HashType aHash = hash(aKey);
            this->getBackendWByHash(_return, aHash);

#ifdef _DEBUG
            if (_return.size() > 0) {

                cout << "hash: " << aHash << " backend: " << _return[0].getHost() << ":" << _return[0].getPort() << _return[0].getStartRange() << endl;
            }
#endif
        }

        void BackendManager::getBackendW(std::vector<BackendInfo> & _return, const int32_t aKey) {
            HashType aHash = hash(aKey);
            this->getBackendWByHash(_return, aHash);

        }

        void BackendManager::getBackendW(std::vector<BackendInfo> & _return, const int64_t aKey) {
            HashType aHash = hash(aKey);
            this->getBackendWByHash(_return, aHash);

        }

        void BackendManager::getBackendW(std::vector<BackendInfo> & _return, const void* aKey, int keySize) {
            HashType aHash = hash(aKey, keySize);
            this->getBackendWByHash(_return, aHash);
        }

        void BackendManager::calculateBackendsR(MultiOpClusterInfo& aClusterInfo, const std::vector<int32_t>& keys) {
            openstars::distributed::BackendInfo aBackend("", -1, 0);

            for (std::vector<int32_t>::const_iterator aIt = keys.begin(); aIt != keys.end(); aIt++) {
                this->getBackendR(aBackend, *aIt);
                if (aBackend.isValid()) {
                    aClusterInfo.add(aBackend, *aIt);
                } // Todo: log key that invalid backend 
            }

        }

        void BackendManager::calculateBackendsR(MultiOpClusterInfo& aClusterInfo, const std::vector<int64_t>& keys) {
            openstars::distributed::BackendInfo aBackend("", -1, 0);
            for (std::vector<int64_t>::const_iterator aIt = keys.begin(); aIt != keys.end(); aIt++) {
                this->getBackendR(aBackend, *aIt);
                if (aBackend.isValid()) {
                    aClusterInfo.add(aBackend, *aIt);
                } // Todo: log key that invalid backend 
            }

        }

        void BackendManager::calculateBackendsR(MultiOpClusterInfo& aClusterInfo, const std::vector<std::string>& keys) {
            openstars::distributed::BackendInfo aBackend("", -1, 0);
            for (std::vector<std::string>::const_iterator aIt = keys.begin(); aIt != keys.end(); aIt++) {
                this->getBackendR(aBackend, *aIt);
                if (aBackend.isValid()) {
                    aClusterInfo.add(aBackend, *aIt);
                } // Todo: log key that invalid backend 
            }

        }

        void BackendManager::calculateBackendsW(MultiOpClusterInfo& aClusterInfo, const std::vector<int32_t>& keys) {
            std::vector<openstars::distributed::BackendInfo> aBackends;

            for (std::vector<int32_t>::const_iterator aIt = keys.begin(); aIt != keys.end(); aIt++) {
                this->getBackendW(aBackends, *aIt);
                for (std::vector<openstars::distributed::BackendInfo>::iterator aBit = aBackends.begin();
                        aBit != aBackends.end(); aBit++) {
                    if (aBit->isValid()) {
                        aClusterInfo.add(*aBit, *aIt);
                    } // Todo: log key that invalid backend 
                }
            }

        }

        void BackendManager::calculateBackendsW(MultiOpClusterInfo& aClusterInfo, const std::vector<int64_t>& keys) {
            std::vector<openstars::distributed::BackendInfo> aBackends;

            for (std::vector<int64_t>::const_iterator aIt = keys.begin(); aIt != keys.end(); aIt++) {
                this->getBackendW(aBackends, *aIt);
                for (std::vector<openstars::distributed::BackendInfo>::iterator aBit = aBackends.begin();
                        aBit != aBackends.end(); aBit++) {
                    if (aBit->isValid()) {
                        aClusterInfo.add(*aBit, *aIt);
                    } // Todo: log key that invalid backend 
                }
            }

        }

        void BackendManager::calculateBackendsW(MultiOpClusterInfo& aClusterInfo, const std::vector<std::string>& keys) {
            std::vector<openstars::distributed::BackendInfo> aBackends;

            for (std::vector<std::string>::const_iterator aIt = keys.begin(); aIt != keys.end(); aIt++) {
                this->getBackendW(aBackends, *aIt);
                for (std::vector<openstars::distributed::BackendInfo>::iterator aBit = aBackends.begin();
                        aBit != aBackends.end(); aBit++) {
                    if (aBit->isValid()) {
                        aClusterInfo.add(*aBit, *aIt);
                    } // Todo: log key that invalid backend 
                }
            }

        }

        void BackendManager::write(const std::string& fileName) {
            std::ofstream aFile(fileName.c_str());
            std::vector<BackendInfo> allBackend;
            this->getAllBackends(allBackend);
            // write size
            aFile << allBackend.size() << std::endl;
            for (int aIndex = 0; aIndex < allBackend.size(); aIndex++) {
                // write each backend
                aFile << allBackend[aIndex].getHost() << " "
                        << allBackend[aIndex].getPort() << " "
                        << allBackend[aIndex].getStartRange() << " "
                        << allBackend[aIndex].getWeight() << " "
                        << allBackend[aIndex].getStatus() << " " << std::endl << std::endl;

            }
        }

        void BackendManager::load(const std::string& fileName) {
            try {
                std::ifstream aFile(fileName.c_str());
                int numBE = 0;
                aFile >> numBE;
                cout << "number of loaded backend: " << numBE << endl;
                for (int aIndex = 0; aIndex < numBE; aIndex++) {
                    std::string host;
                    int port;
                    long startRange;
                    int weight;
                    int status;
                    aFile >> host >> port >> startRange >> weight>>status;
                    //            openstars::distributed::TBackendInfo aBackend;
                    //            int aStatus;
                    //            aFile >> aBackend.host 
                    //                    >> aBackend.port 
                    //                    >> aBackend.startRange 
                    //                    >> aBackend.weight 
                    //                    >> aStatus;
                    //            aBackend.status = (openstars::distributed::TBackendStatus::type)aStatus;
                    //            cout<< aBackend.host<<" "<<aBackend.port<<" "<<aBackend.startRange<<" "<<aBackend.weight<<" "<<aBackend.status<<endl;
                    BackendInfo aModelBE(host, port, startRange, weight, BackendInfo::TStatus(status));

                    this->addBackend(aModelBE);
                }
            } catch (...) {

            }
        }

        void BackendManager::loadZkConfig(const std::string& zkHosts, const std::string& zkParentPath) {
            this->_zkServers = zkHosts;
            this->_zkPath = zkParentPath;
            this->doLoadZkConfig(true);
        }

        void BackendManager::doLoadZkConfig(bool reconnect) {

            std::vector<BackendInfo> backends;

            ZooKeeperConfig config(this->_zkServers, 100, true, 1000);
            try {
                if (!_private->_zkClient)
                    _private->_zkClient = new ZooKeeperAdapter(config, _private.get(), true);
                if (reconnect)
                    _private->_zkClient->reconnect();

                vector<string> nodeList;
                _private->_zkClient->getNodeChildren(nodeList, _zkPath, _private.get(), _private.get());

                cout << "_zkPath:" << _zkPath << endl;

                for (size_t aIndex = 0; aIndex < nodeList.size(); aIndex++) {
                    parseBackend(nodeList[aIndex], backends);
                }
            } catch (...) {

            }
            if (backends.size() > 0)
                this->replaceAll(backends);
            this->startChecking();

        }

        bool BackendManager::parseBackend(const std::string& sPath, std::vector<BackendInfo>& backends) {
            cout << "parse backend: " << sPath << endl;
            /** parse nodes */
            Poco::Path path(sPath); // UNIX style        
            std::string node = path.directory(path.depth());


            Poco::StringTokenizer parseToken(node, ":");
            cout << "node: " << node << endl;

            if (parseToken.count() == 3) {
                openstars::distributed::BackendInfo aInfo("", -1, 0);

                aInfo.setHost(parseToken[1]);
                aInfo.setPort(Poco::NumberParser::parse(parseToken[2].c_str()));
                std::string scheme = parseToken[0];
                Poco::StringTokenizer schemeStk(scheme, "_");
                try {
                    if (schemeStk.count() > 0) {
                        try {
                            aInfo.setStartRange(Poco::NumberParser::parse64(schemeStk[ schemeStk.count() - 1 ]));
                        } catch (...) {
                            aInfo.setStartRange(Poco::NumberParser::parseHex64(schemeStk[ schemeStk.count() - 1 ]));
                        }
                    }

                } catch (...) {

                }
                cout << "adding backend " << aInfo.getHost() << " " << aInfo.getPort() << " " << aInfo.getStartRange() << endl;
                if (aInfo.isValid()) {
                    backends.push_back(aInfo);
                    return true;
                }
            }
            return false;
        }

        void BackendManager::BackendManagerPrivate::eventReceived(const EventSource<ZKWatcherEvent>& source, const ZKWatcherEvent& e) {
            cout << "eventReceived: " << e.getPath() << " " << e.getState() << "  " << e.getType() << endl;

            //doLoadZkConfig();

            if (e.getState() == ZOO_CONNECTED_STATE && (e.getType() == ZOO_DELETED_EVENT || e.getType() == ZOO_SESSION_EVENT)) {
                if (this->_zkClient)
                    if (this->_zkClient->getState() == ZooKeeperAdapter::AS_CONNECTED)
                        this->parent->doLoadZkConfig(false);
            }
            else if (e.getState() == ZOO_EXPIRED_SESSION_STATE && (e.getType() == ZOO_DELETED_EVENT || e.getType() == ZOO_SESSION_EVENT)) {
                parent->doLoadZkConfig(false);
            }

        }

        void BackendManager::checkConnectionImpl() {
            if (_runningChecking)
                return;
            _runningChecking = true;

            while (_runningChecking) {
                //Poco::Thread::sleep(10000);
                if (_stopCheckingEvent.tryWait(10000))
                    break;

                try {
                    vector<string> nodeList;
                    _private->_zkClient->getNodeChildren(nodeList, _zkPath, _private.get(), _private.get());

                    std::vector<BackendInfo> backends;
                    cout << "_zkPath:" << _zkPath << endl;

                    for (size_t aIndex = 0; aIndex < nodeList.size(); aIndex++) {
                        parseBackend(nodeList[aIndex], backends);
                    }

                    this->replaceAll(backends);
                } catch (ZooKeeperException& e) {
                    if (_runningChecking) {
                        _runningChecking = false;
                        this->doLoadZkConfig();
                    }
                    return;
                } catch (...) {
                    if (_runningChecking) {
                        _runningChecking = false;
                        this->doLoadZkConfig();
                    }
                    return;
                }
            };

            _runningChecking = false;
            _doneCheckingEvent.set();
            return;
        }

        void BackendManager::stopChecking() {
            if (!_runningChecking)
                return;
            _runningChecking = false;
            _stopCheckingEvent.set();
            try {
                _doneCheckingEvent.wait(100000);
            } catch (...) {

            }

        }

    }
}// namespace 

