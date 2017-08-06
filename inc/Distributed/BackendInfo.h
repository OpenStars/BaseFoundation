/* 
 * File:   BackendInfo.h
 * Author: trungthanh
 *
 * Created on August 16, 2012, 1:10 PM
 */
// backend description for consistent hash

#ifndef BACKENDINFO_H
#define BACKENDINFO_H

#include <stdint.h>
#include <string>
#include <iostream>
#include "Hashing/Hasher.h"

namespace openstars {
    namespace distributed {
        typedef openstars::hashing::HashType HashType;

        class BackendInfo {
        public:

            enum TStatus {
                EReady = 1,
                EInActiveForAdding = 2, // data is moving from next node to this node
                EInActiveForRemoving = 3, // data is moving from this node to prev node in the ring
                EReadyRemove = 4,
                EUnexpectedDown = 5, // backend down
            };

            struct EndpointLesser { // for host/port finding
                bool operator()(const BackendInfo& be1, const BackendInfo & be2);
            };

            struct EndpointEqual { // for host/port finding
                bool operator()(const BackendInfo& be1, const BackendInfo & be2);
            };
            BackendInfo(const std::string host, int port, HashType startRange, int weight = 1, TStatus status = EReady);
            BackendInfo(const BackendInfo& orig);
            virtual ~BackendInfo();

        public:
            // range compare
            bool operator<(const BackendInfo& other) const;
            bool operator==(const BackendInfo& other) const;

            void operator=(const BackendInfo& other);
            //        void operator =(const openstars::Distributed::TBackendInfo& other);
            //        void assignTo(openstars::Distributed::TBackendInfo& other)const;

            void setInfo(const std::string host, int port, HashType startRange, int weight = 1, TStatus status = EReady);
            void getInfo(std::string& host, int& port, HashType& startRange, int& weight, TStatus& status);
        public:

            const std::string& getHost()const {
                return _host;
            }

            void getHost(std::string& _return)const {
                _return = _host;
            }

            void setHost(const std::string& host);

            int getPort()const {
                return _port;
            }

            void setPort(const int port);

            HashType getStartRange()const {
                return _startRange;
            }

            void setStartRange(const HashType startRange);

            int getWeight()const {
                return _weight;
            }

            void setWeight(const int weight);

            bool isValid()const;

            TStatus getStatus()const {
                return _status;
            }

            void setStatus(TStatus status) {
                _status = status;
            }

        private:
            std::string _host;
            int _port;
            HashType _startRange; // for consistent hash clustering (horizontal scale)
            int _weight; // for load read load balancing (replication model)
            TStatus _status; //
        };

    }
}
#endif /* BACKENDINFO_H */

