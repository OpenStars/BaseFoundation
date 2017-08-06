/* 
 * File:   BackendManager.h
 * Author: trungthanh
 *
 * Created on August 21, 2012, 2:28 PM
 */

#ifndef BACKENDMANAGER_H
#define BACKENDMANAGER_H

#include "Distributed/BackendInfo.h"
#include "Hashing/DefaultHasher.h"
#include <vector>
#include "Poco/SharedPtr.h"

#include "Poco/Mutex.h"
#include "Poco/Event.h"
#include "Poco/ActiveMethod.h"



namespace openstars {
    namespace distributed {

        // information of multiget/multiput ... operations

        struct TMultiKeysBackendInfo {

            TMultiKeysBackendInfo() : _backend("", -1, 1) {
            }
            BackendInfo _backend;
            std::vector< int32_t > _i32Keys;
            std::vector< int64_t > _i64Keys;
            std::vector< std::string > _stringKeys;

            bool operator<(const TMultiKeysBackendInfo& other)const {
                return _backend < other._backend;
            }

            bool operator<(const BackendInfo& other)const {
                return _backend < other;
            }

            bool operator==(const TMultiKeysBackendInfo& other)const {
                return _backend == other._backend;
            }

            bool operator==(const BackendInfo& other)const {
                return _backend == other;
            }


        };

        struct MultiOpClusterInfo {
            std::vector< TMultiKeysBackendInfo > infos;
            void add(const BackendInfo& aBackend, const int32_t aKey);
            void add(const BackendInfo& aBackend, const int64_t aKey);
            void add(const BackendInfo& aBackend, const std::string& aKey);
        };

        class BackendManager {
        public:
            BackendManager();
            virtual ~BackendManager();
        public:
            virtual void getAllBackends(std::vector<BackendInfo> & _return) = 0;
            // when read, need only one BackendInfo? 
            virtual void getBackendR(BackendInfo &_return, const std::string& aKey);
            virtual void getBackendR(BackendInfo &_return, const int32_t aKey);
            virtual void getBackendR(BackendInfo &_return, const int64_t aKey);
            virtual void getBackendR(BackendInfo &_return, const void* aKey, int keySize);

            // when read 
            virtual void getListBackendR(std::vector<BackendInfo> & _return, const std::string& aKey);
            virtual void getListBackendR(std::vector<BackendInfo> & _return, const int32_t aKey);
            virtual void getListBackendR(std::vector<BackendInfo> & _return, const int64_t aKey);
            virtual void getListBackendR(std::vector<BackendInfo> & _return, const void* aKey, int keySize);


            virtual void getBackendRByHash(BackendInfo &_return, const HashType aHashKey) = 0;
            virtual void getListBackendRByHash(std::vector<BackendInfo> & _return, const HashType aHashKey) = 0;

            //
            virtual void getBackendW(std::vector<BackendInfo> & _return, const std::string& aKey);
            virtual void getBackendW(std::vector<BackendInfo> & _return, const int32_t aKey);
            virtual void getBackendW(std::vector<BackendInfo> & _return, const int64_t aKey);
            virtual void getBackendW(std::vector<BackendInfo> & _return, const void* aKey, int keySize);

            virtual void getBackendWByHash(std::vector<BackendInfo> & _return, const HashType aHashKey) = 0;

            virtual void calculateBackendsR(MultiOpClusterInfo& aClusterInfo, const std::vector<int32_t>& aKeys);
            virtual void calculateBackendsR(MultiOpClusterInfo& aClusterInfo, const std::vector<int64_t>& aKeys);
            virtual void calculateBackendsR(MultiOpClusterInfo& aClusterInfo, const std::vector<std::string>& aKeys);

            virtual void calculateBackendsW(MultiOpClusterInfo& aClusterInfo, const std::vector<int32_t>& aKeys);
            virtual void calculateBackendsW(MultiOpClusterInfo& aClusterInfo, const std::vector<int64_t>& aKeys);
            virtual void calculateBackendsW(MultiOpClusterInfo& aClusterInfo, const std::vector<std::string>& aKeys);

            HashType hash(const std::string& aKey);
            HashType hash(const int32_t aKey);
            HashType hash(const int64_t aKey);
            HashType hash(const void* aKey, int keySize);

            virtual void addBackend(const BackendInfo& aBackend) = 0;
            virtual void updateBackend(const BackendInfo& aBackend) = 0;
            virtual void removeBackend(const BackendInfo& aBackend) = 0;

            virtual void replaceAll(std::vector<BackendInfo>& newBackends) {
            };

            virtual void checkBEStatus() {
            };

            // load backends info from file
            virtual void load(const std::string& fileName);
            //write backends info to file
            virtual void write(const std::string& fileName);

            void setHasher(const Poco::SharedPtr<openstars::hashing::Hasher>& aHasher);

            /*
             * each backend is registered with path /up-division/services/updb/scheme_range:host:port
             */
            void loadZkConfig(const std::string& zkHost, const std::string& zkParentPath);

            void logWrongDeadBackend(const BackendInfo& aBackend) {
            };

            void logWrongLiveBackend(const BackendInfo& aBackend) {
            };
        protected:
            void doLoadZkConfig(bool reconnect = false);


            // parse and add backend by its register path
            bool parseBackend(const std::string& path, std::vector<BackendInfo>& backends);
        private:
            BackendManager(const BackendManager& orig);

            void checkConnectionImpl();

            Poco::ActiveMethod<void, void, BackendManager> startChecking;

            void stopChecking();

        protected:
            openstars::hashing::Hasher* _pkeyHasher;
            Poco::SharedPtr<openstars::hashing::Hasher> _keyHasher;

            //
            class BackendManagerPrivate;
            friend class BackendManagerPrivate;
            Poco::SharedPtr<BackendManagerPrivate> _private;
            //    Poco::SharedPtr<ZooKeeperAdapter> _zkClient;    
            std::string _zkServers;
            std::string _zkPath;

            bool _runningChecking;

            Poco::Event _doneCheckingEvent;
            Poco::Event _stopCheckingEvent;

        };

    }
}
#endif /* BACKENDMANAGER_H */

