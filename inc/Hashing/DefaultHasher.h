/* 
 * File:   DefaultHasher.h
 * Author: trungthanh
 *
 * Created on October 10, 2012, 12:21 PM
 */

#ifndef DEFAULTHASHER_H
#define DEFAULTHASHER_H

#include <Hashing/Hasher.h>

namespace openstars {
    namespace hashing {

        class DefaultHasher : public Hasher {
        public:
            virtual HashType hash(const std::string& aKey) const;
            virtual HashType hash(const int32_t aKey) const;
            virtual HashType hash(const int64_t aKey) const;
            virtual HashType hash(const void* aKey, int keySize) const;
        public:
            static HashType hashdata(const void* aKey, int keySize);
        };

    }
}
#endif /* DEFAULTHASHER_H */

