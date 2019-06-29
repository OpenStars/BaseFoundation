/* 
 * File:   MurmurHasher.h
 * Author: thanhnt
 *
 * Created on Otc 10, 2012, 3:17 PM
 */

#ifndef MURMURHASH_H
#define MURMURHASH_H

#include <string>
#include <stdint.h>
#include <Hashing/Hasher.h>

using namespace std;

namespace openstars {
    namespace hashing {

        class MurmurHasher : public Hasher {
        public:

            MurmurHasher() {
            };

            virtual HashType hash(const std::string& aKey) const;
            virtual HashType hash(const int32_t aKey) const;
            virtual HashType hash(const int64_t aKey) const;
            virtual HashType hash(const void* aKey, int keySize) const;

            static uint64_t MurmurHashString(const string& key);

            static uint64_t MurmurHash64A(const void * key, int len);
        public:

            template <class T>
            uint64_t operator()(const T& key) const {
                return MurmurHash64A((void*) &key, sizeof (T));
            }

            uint64_t operator()(const std::string& key) const {
                return MurmurHashString(key);
            }

        private:

            static uint64_t MurmurHash64A(const void * key, int len, unsigned int seed);
        };

    }
}



#endif /* MURMURHASH_H */

