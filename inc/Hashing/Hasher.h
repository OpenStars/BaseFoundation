/* 
 * File:   Hasher.h
 * Author: trungthanh
 *
 * Created on October 10, 2012, 11:50 AM
 */

#ifndef ABSTRACTHASHER_H
#define ABSTRACTHASHER_H

#include <stddef.h>
#include <stdint.h>
#include <string>


namespace openstars{
    namespace hashing {
        typedef size_t HashType;

        class Hasher {
        public:

            virtual ~Hasher() {
            }
        public:

            HashType operator()(const std::string& aKey) const {
                return hash(aKey);
            }

            HashType operator()(const int32_t aKey) const {
                return hash(aKey);
            }

            HashType operator()(const uint32_t aKey) const {
                return hash(aKey);
            }

            HashType operator()(const int64_t aKey) const {
                return hash(aKey);
            }

            HashType operator()(const uint64_t aKey) const {
                return hash(aKey);
            }

            HashType operator()(const void* aKey, int keySize) const {
                return hash(aKey, keySize);
            }

            virtual HashType hash(const std::string& aKey) const = 0;

            virtual HashType hash(const int32_t aKey) const = 0;

            virtual HashType hash(const uint32_t aKey) const {
                int32_t aI32Key = aKey;
                return hash(aI32Key);
            }

            virtual HashType hash(const int64_t aKey) const = 0;

            virtual HashType hash(const uint64_t aKey) const {
                int64_t aI64Key = aKey;
                return hash(aI64Key);
            }

            virtual HashType hash(const void* aKey, int keySize) const = 0;

        };




    }
}
#endif /* ABSTRACTHASHER_H */

