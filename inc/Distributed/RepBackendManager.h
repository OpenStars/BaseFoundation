/* 
 * File:   RepBackendManager.h
 * Author: trungthanh
 *
 * Created on August 29, 2012, 11:55 AM
 */

#ifndef REPBACKENDMANAGER_H
#define REPBACKENDMANAGER_H
#include "Distributed/BackendManager.h"
#include <Poco/RWLock.h>

namespace openstars {
    namespace distributed {
        // backend manager for replication proxy : write to all, read from one.

        class RepBackendManager : public BackendManager {
        public:
            typedef Poco::RWLock MutexType;
            typedef Poco::RWLock::ScopedLock ScopedLockType;
            RepBackendManager();
            virtual ~RepBackendManager();
        public:

            virtual void getAllBackends(std::vector<BackendInfo> & _return) {
                _return = _backends;
            }
            virtual void getBackendRByHash(BackendInfo &_return, const HashType aHashKey);
            virtual void getListBackendRByHash(std::vector<BackendInfo> & _return, const HashType aHashKey);
            virtual void getBackendWByHash(std::vector<BackendInfo> & _return, const HashType aHashKey);

            // these function is not used very frequently
            virtual void addBackend(const BackendInfo& aBackend);
            virtual void removeBackend(const BackendInfo& aBackend);

            virtual void updateBackend(const BackendInfo& aBackend) {
            }
            void replaceAll(std::vector<BackendInfo>& newBackends);
        protected:
            void _getBackendRByHash(BackendInfo &_return, const HashType aHashKey);
            void _getListBackendRByHash(std::vector<BackendInfo> & _return, const HashType aHashKey);
            void _getBackendWByHash(std::vector<BackendInfo> & _return, const HashType aHashKey);

            // these function is not used very frequently
            void _addBackend(const BackendInfo& aBackend);
            void _removeBackend(const BackendInfo& aBackend);

        private:
            RepBackendManager(const RepBackendManager& orig);
        protected:
            std::vector<BackendInfo> _backends;
            int _currentCount;
            int _currentIndex;
            Poco::RWLock _mutex;
        };

    }
}

#endif /* REPBACKENDMANAGER_H */

