/* 
 * File:   EvictProcessors.h
 * Author: trungthanh
 *
 * Created on March 23, 2014, 9:12 PM
 */

#ifndef UPSTORAGE_EVICTPROCESSORS_H
#define	UPSTORAGE_EVICTPROCESSORS_H

#include <boost/unordered_map.hpp>
#include "Poco/Mutex.h"

namespace openstars { namespace storage{

template <class _TKey, class _TValue>
class AbstractEvictedProcessor{
public:
    typedef _TKey TKey;
    typedef _TValue TValue;
    virtual ~AbstractEvictedProcessor(){}
public:
 
    virtual bool popEvictedDirty(TKey& key, TValue& value, bool& enableAsyncFlush) = 0;
        
    virtual bool pushDirtyKeyValue(const TKey& key, const TValue& value,bool& enableAsyncFlush) = 0;
    
    virtual bool tryPopEvicted(const TKey& key, TValue& value) {return false;}
    
    virtual size_t size() const {return 0; }
    
};

template <class _TKey, class _TValue>
class IgnoreAllEvictProcessor:public AbstractEvictedProcessor<_TKey, _TValue>
{
    public:
        typedef _TKey TKey;
    
        typedef _TValue TValue;

    
        virtual bool popEvictedDirty(TKey& key, TValue& value, bool& enableAsyncFlush) 
        {  
            return false;
        };
    
        virtual bool pushDirtyKeyValue(const TKey& key, const TValue& value,bool& enableAsyncFlush) {
            return false;
        }
        
};
    
template <class _TKey, class _TValue>
class SafeEvictProcessor:public AbstractEvictedProcessor<_TKey, _TValue>
{
    public:
        typedef _TKey TKey;
    
        typedef _TValue TValue;
    private:
        boost::unordered_map<TKey, TValue> _evictedMap;
        typedef Poco::FastMutex MutexType;
        typedef MutexType::ScopedLock ScopedLockType;
        MutexType _mutex;
        
    public:
    
        virtual bool popEvictedDirty(TKey& key, TValue& value, bool& enableAsyncFlush) 
        {  
            enableAsyncFlush = _evictedMap.size() == 0;
            if (enableAsyncFlush)
                return false;
            else
            {
                ScopedLockType aLock(_mutex);
                typename boost::unordered_map<TKey, TValue>::iterator aIt = _evictedMap.begin();
                key = aIt->first;
                value = aIt->second;
                _evictedMap.erase(aIt);
            }
            return true;
        };
    
        virtual bool pushDirtyKeyValue(const TKey& key, const TValue& value,bool& enableAsyncFlush) {
            ScopedLockType aLock(_mutex);
            _evictedMap[key] = value;
            enableAsyncFlush = false;   
            return true;
        }
        
        virtual bool tryPopEvicted(const TKey& key, TValue& value) {
            if (_evictedMap.size() == 0)
                return false;
            ScopedLockType aLock(_mutex);
            typename boost::unordered_map<TKey, TValue>::iterator aIt = _evictedMap.find(key);
            if (aIt != _evictedMap.end())
            {
                value = aIt->second;                
                return true;
            }
            
            return false;
        }
        
        virtual size_t size() const {return _evictedMap.size();}
};
    



} } //Up::Storage



#endif	/* EVICTPROCESSORS_H */

