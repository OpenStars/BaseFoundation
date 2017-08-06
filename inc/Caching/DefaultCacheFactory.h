/* 
 * File:   DefaultCacheFactory.h
 * Author: anhn
 *
 * Created on December 28, 2014, 10:17 AM
 */

#ifndef DEFAULTCACHEFACTORY_H
#define	DEFAULTCACHEFACTORY_H

#include <string>

#include "Caching/AbstractCache.h"
#include "Caching/HFLRUCache.h"
#include "Caching/HLKCache.h"
#include "Caching/HLKLRUCache.h"
#include "Caching/HLLLRUCache.h"
#include "Caching/ARCLLCache.h"

#include "Poco/StringTokenizer.h"
#include "Poco/NumberParser.h"

namespace openstars {
namespace caching {

template <class _TKey, class _TValue, class _THash = boost::hash<_TKey> >
class DefaultCacheFactory {
public:

	DefaultCacheFactory() {
		_hashTableSize = 10000;
		_lruSize = 10000;
		_lockSize = 1024;
		_expireTime = 60 * 60 * 1000; // 1h
		_lruExpire = 0;
		_hotPercent = -1;
		_accessPercentStep = -1;

	}
protected:
	size_t _hashTableSize;
	size_t _lruSize;
	size_t _lockSize;
	size_t _expireTime; //milliseconds
	size_t _lruExpire; //expire time in seconds for BagLRUCache
	std::string _type;
	int _hotPercent;
	int _accessPercentStep;

public:
	virtual AbstractCache<_TKey, _TValue> * createCache();
	virtual AbstractCache<_TKey, _TValue> * createCache(const std::string& options);

protected:
	void parseOptions(const std::string& options);
	_TKey fromString(const std::string& aSKey);
};


/////////////////////////////////

template <class _TKey, class _TValue, class _THash >
AbstractCache<_TKey, _TValue> * DefaultCacheFactory<_TKey, _TValue, _THash> ::createCache() {
	std::string cacheType = _type;
	cout << "cache type: " << cacheType << endl;
        if (cacheType == "hlkcache") {
		return new openstars::caching::HLKCache<_TKey, _TValue, _THash > (_hashTableSize, _lockSize);
	} else if (cacheType == "hflrucache" || cacheType == "hlklrucache") {
		return new openstars::caching::HLKLRUCache<_TKey, _TValue, _THash > (_lruSize, _hashTableSize, _lockSize);
	} else if (cacheType == "hlllrucache") {
		return new openstars::caching::HLLLRUCache<_TKey, _TValue, _THash > (_lruSize, _hashTableSize, _lockSize);
	} else if (cacheType == "hlllrucache_fastmutex") {
		return new openstars::caching::HLLLRUCache<_TKey, _TValue, _THash, MemSizeGetter, Poco::FastMutex > (_lruSize, _hashTableSize, _lockSize);
	} else if (cacheType == "arcllcache" || cacheType == "arcllcache_spinlock") {
		return new openstars::caching::ARCLLCache<_TKey, _TValue, _THash > (_lruSize, _hashTableSize, _lockSize);
	} else if (cacheType == "arcllcache_fastmutex") {
		return new openstars::caching::ARCLLCache<_TKey, _TValue, _THash, MemSizeGetter, Poco::FastMutex > (_lruSize, _hashTableSize, _lockSize);
	}
	return new openstars::caching::HLKCache<_TKey, _TValue, _THash > (_hashTableSize, _lockSize);
}

template <class _TKey, class _TValue, class _THash >
AbstractCache<_TKey, _TValue> * DefaultCacheFactory<_TKey, _TValue, _THash> ::createCache(const std::string& options) {
	this->parseOptions(options);
	return createCache();
}

template <class _TKey, class _TValue, class _THash >
void DefaultCacheFactory<_TKey, _TValue, _THash> ::parseOptions(const std::string& options) {
	/*options look likes: type=hfcache,tablesize=2000000,lrusize=3000000,deletedkey=-1,locksize=4 */
	Poco::StringTokenizer aStk(options, ",");
	for (int aIndex = 0; aIndex < aStk.count(); aIndex++) {
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
		} else if (aName == "tablesize") {
			_hashTableSize = Poco::NumberParser::parse64(aValue);
		} else if (aName == "lrusize") {
			_lruSize = Poco::NumberParser::parse64(aValue);
		} else if (aName == "expiretime") {
			_expireTime = Poco::NumberParser::parse64(aValue);
		} else if (aName == "hotpercent") {
			_hotPercent = Poco::NumberParser::parse(aValue);
		} else if (aName == "accessstep") {
			_accessPercentStep = Poco::NumberParser::parse(aValue);
		}
	}

}


}


#endif	/* DEFAULTCACHEFACTORY_H */

