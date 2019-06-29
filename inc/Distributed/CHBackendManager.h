/* 
 * File:   CHBackendManager.h
 * Author: trungthanh
 *
 * Created on August 30, 2012, 3:57 PM
 */

#ifndef CHBACKENDMANAGER_H
#define CHBACKENDMANAGER_H
#include "Distributed/BackendManager.h"

#include <Poco/RWLock.h>

namespace openstars {
    namespace distributed {
        // backend manager for consistent hash proxy : write to all, read from one.

        /*
         * Keys are hashed and hash values are distributed in a ring 0,1, ... M
         * Node are located at a ring position with value S1, S2, ... Sn
         * 
         *  0, 1 .....S1,.....S2 , .....Sn,.......M-1,M
         * when access to a key/value with hash value h, its Node is Sk which: Sk >= h > S(k-1), if h > Sn its
         * node would be S1
         * 
         */
        class CHBackendManager : public BackendManager {
        public:
            typedef Poco::RWLock MutexType;
            typedef Poco::RWLock::ScopedLock ScopedLockType;
            CHBackendManager();
            virtual ~CHBackendManager();
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
            virtual void updateBackend(const BackendInfo& aBackend);
            virtual void replaceAll(std::vector<BackendInfo>& newBackends);

        protected:
            void _getBackendRByHash(BackendInfo &_return, const HashType aHashKey);
            void _getListBackendRByHash(std::vector<BackendInfo> & _return, const HashType aHashKey);
            void _getBackendWByHash(std::vector<BackendInfo> & _return, const HashType aHashKey);

            // these function is not used very frequently
            void _addBackend(const BackendInfo& aBackend);
            void _removeBackend(const BackendInfo& aBackend);
            void _updateBackend(const BackendInfo& aBackend);

        private:
            CHBackendManager(const CHBackendManager& orig);
        protected:
            typedef std::vector<BackendInfo> TBackendListType;
            std::vector<BackendInfo> _backends;
            Poco::RWLock _mutex;
        };

    }
}

#endif /* CHBACKENDMANAGER_H */

