#ifndef CACHEFACTORY_H
#define CACHEFACTORY_H

#include <string>
#include <Caching/AbstractCache.h>
#include <Caching/HFLRUCache.h>

#include "Caching/HLKCache.h"
#include "Caching/HLKLRUCache.h"
#include "Caching/HLLLRUCache.h"
#include "Caching/DirtyLRUCache.h"
#include "Caching/ARCLLCache.h"

#include <Poco/StringTokenizer.h>
#include <Poco/NumberParser.h>

namespace openstars { namespace caching {

        template <class _TKey, class _TValue>
        class AbstractCacheFactory {
        public:

            AbstractCacheFactory() {
            }

            virtual ~AbstractCacheFactory() {
            }
        public:
            virtual AbstractCache<_TKey, _TValue> * createCache() = 0;
            virtual AbstractCache<_TKey, _TValue> * createCache(const std::string& options) = 0;
        };

        template <class _TKey, class _TValue, class _THash = boost::hash<_TKey> >
        class BasicCacheFactory {
        public:

            BasicCacheFactory() {
                _hashTableSize = 1000000;
                _lruSize = 1000000;
                _lockSize = 102400;
                _expireTime = 60 * 60 * 1000; // 1h
				_lruExpire = 0;
				_hotPercent = -1;
				_accessPercentStep = -1;
				
            }
        protected:
            // default
            size_t _hashTableSize;
            size_t _lruSize;
            size_t _lockSize;
            size_t _expireTime;	//milisecond
			size_t _lruExpire;	//expire time in seconds for BagLRUCache
            _TKey _deletedKey;
            std::string _type;
			int _hotPercent;
			int _accessPercentStep;

        public:
            virtual AbstractCache<_TKey, _TValue> * createCache();
            virtual AbstractCache<_TKey, _TValue> * createCache(const std::string& options);

        protected:
            void parseOptions(const std::string& options);
        };
        

        /////////////////////////////////

        template <class _TKey, class _TValue, class _THash >
        AbstractCache<_TKey, _TValue> * BasicCacheFactory<_TKey, _TValue, _THash> ::createCache() {
            std::string name = _type;
            cout<<"cache type: "<<name<<endl;
            
            if (name == "hlkcache") {
                return new openstars::caching::HLKCache<_TKey, _TValue, _THash > (_hashTableSize, _lockSize);
            }
            
            else if (name == "hflrucache" || name=="hlklrucache") {
#ifdef _DEBUG
                cout<<"create hflrucache "<<endl;
#endif
                return new openstars::caching::HLKLRUCache<_TKey, _TValue, _THash > (_lruSize, _hashTableSize, _lockSize);
            }
            else if (name == "dirtylrucache") {
                return new openstars::caching::DirtyLRUCache<_TKey, _TValue, _THash > (_lruSize, _hashTableSize, _lockSize);
            }
            else if (name == "dirtylrucache_fastmutex") {
                return new openstars::caching::DirtyLRUCache<_TKey, _TValue, _THash, MemSizeGetter, Poco::FastMutex > (_lruSize, _hashTableSize, _lockSize);
            }
            else if (name == "hlllrucache") {
                return new openstars::caching::HLLLRUCache<_TKey, _TValue, _THash > (_lruSize, _hashTableSize, _lockSize);
            }
            else if (name == "hlllrucache_fastmutex") {
                return new openstars::caching::HLLLRUCache<_TKey, _TValue, _THash , MemSizeGetter, Poco::FastMutex > (_lruSize, _hashTableSize, _lockSize);
            }
            else if (name == "hflrucacheold") {
                return new openstars::caching::HFLRUCache<_TKey, _TValue, _THash > (_lruSize, _hashTableSize, _lockSize);
            }
            else if (name == "arcllcache" || name == "arcllcache_spinlock") {
                return new openstars::caching::ARCLLCache<_TKey, _TValue, _THash > (_lruSize, _hashTableSize, _lockSize);
            }
            else if (name == "arcllcache_fastmutex") {
                return new openstars::caching::ARCLLCache<_TKey, _TValue, _THash, MemSizeGetter, Poco::FastMutex > (_lruSize, _hashTableSize, _lockSize);
            }

            return NULL;
        }

        template <class _TKey, class _TValue, class _THash >
        AbstractCache<_TKey, _TValue> * BasicCacheFactory<_TKey, _TValue, _THash> ::createCache(const std::string& options) {
            this->parseOptions(options);
            return createCache();
        }

        template <class _TKey, class _TValue, class _THash >
        void BasicCacheFactory<_TKey, _TValue, _THash> ::parseOptions(const std::string& options) {
            
#ifdef _DEBUG
            cout<<"Caching options: "<<options<<endl;
#endif
            Poco::StringTokenizer aStk(options, ",");
            for (size_t aIndex = 0; aIndex < aStk.count(); aIndex++) {
                std::string aOption = aStk[aIndex];
                Poco::StringTokenizer aStk2(aOption, "=");
                if (aStk2.count() < 2) {
                    cout << aOption;
                    continue;
                }
                std::string aName = aStk2[0];
                std::string aValue = aStk2[1];
                if (aName == "type") {
                    _type = aValue;
#ifdef _DEBUG
                    cout<<"cache type: "<<_type<<endl;
#endif
                }

                if (aName == "tablesize") {
                    this->_hashTableSize = Poco::NumberParser::parse64(aValue);
                }

                if (aName == "lrusize") {
                    this->_lruSize = Poco::NumberParser::parse64(aValue);
                }

                if(aName == "expiretime"){
                    _expireTime = Poco::NumberParser::parse64(aValue);
                }
				if (aName == "hotpercent") {
					_hotPercent = Poco::NumberParser::parse(aValue);
				}
				if (aName == "accessstep") {
					_accessPercentStep = Poco::NumberParser::parse(aValue);
				}

            }

        }


        

    }
}


#endif // CACHEFACTORY_H
