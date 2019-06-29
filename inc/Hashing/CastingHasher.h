/* 
 * File:   CastingHasher.h
 * Author: trungthanh
 *
 * Created on October 10, 2012, 12:33 PM
 */

#ifndef CASTINGHASHER_H
#define CASTINGHASHER_H

#include "Hashing/Hasher.h"

namespace openstars {
    namespace hashing {

        class CastingHasher : public Hasher {
        public:
            virtual HashType hash(const std::string& aKey) const;
            virtual HashType hash(const int32_t aKey) const;
            virtual HashType hash(const int64_t aKey) const;
            virtual HashType hash(const void* aKey, int keySize) const;


        };

    }
}

#endif /* CASTINGHASHER_H */

