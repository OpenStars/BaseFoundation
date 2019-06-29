/* 
 * File:   BasicBackendManagerHandler.h
 * Author: trungthanh
 *
 * Created on September 5, 2012, 3:38 PM
 */

#ifndef BASICBACKENDMANAGERHANDLER_H
#define BASICBACKENDMANAGERHANDLER_H
#include <TBackendManagerService.h>
#include "Distributed/BackendManager.h"

namespace openstars {
    namespace distributed {

        class BasicBackendManagerHandler : public openstars::distributed::TBackendManagerServiceIf {
        public:

            BasicBackendManagerHandler(BackendManager* aMngr);
            virtual ~BasicBackendManagerHandler();
        public:
            virtual void getBackends(std::vector<openstars::distributed::TBackendInfo> & _return);
            virtual void getBEWrite(std::vector<openstars::distributed::TBackendInfo> & _return, const std::string& key);
            virtual void getBERead(std::vector<openstars::distributed::TBackendInfo> & _return, const std::string& key);
            virtual void addBackend(const openstars::distributed::TBackendInfo& aNode);
            virtual void updateBackend(const openstars::distributed::TBackendInfo& aNode);
            virtual void removeBackend(const openstars::distributed::TBackendInfo& aNode);

        private:
            BackendManager* _backendMngr;
        };

    }
}
#endif /* BASICBACKENDMANAGERHANDLER_H */

