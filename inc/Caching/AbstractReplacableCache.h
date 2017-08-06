/* 
 * File:   AbstractLRUCache.h
 * Author: trungthanh
 *
 * Created on March 23, 2014, 6:01 PM
 */

#ifndef ABSTRACTLRUCACHE_H
#define	ABSTRACTLRUCACHE_H

#include <boost/functional/hash.hpp>
#include <boost/atomic.hpp>
#include <list>
#include <vector>
#include <algorithm>

#include "Caching/AbstractCache.h"
#include "Poco/RunnableAdapter.h"
#include "Poco/Thread.h"

namespace openstars { namespace caching {

template <class _TKey, class _TValue, class _THash = boost::hash<_TKey> , class _MemSizeGetter = MemSizeGetter>
class AbstractReplacableCache: public AbstractCache<_TKey, _TValue, _MemSizeGetter> 
{
    public:
        typedef _TKey TKey;
        typedef _TValue TValue;

        AbstractReplacableCache(size_t lruSize) 
            :_maxSize(lruSize)
            ,_isEvicting(false)
            , _enableEvict(true)
            ,_runnable(*this, &AbstractReplacableCache::evictFunc)
        {        
        }
        
        virtual ~AbstractReplacableCache()
        {
            this->stopEvict();
        }

        virtual bool popTail(TKey& key, TValue& value) = 0;
        
        virtual size_t maxSize()const {
            return _maxSize;
        }

        virtual void setMaxSize(size_t aSize) {
            this->_maxSize = aSize;
        }
        
    protected:
        void startEvict()
        {
            if (_evictThread.isRunning())
                return;
            _enableEvict = true;
            _evictThread.start(_runnable);
        }
        void stopEvict()
        {
            if (_evictThread.isRunning())
            {
                _enableEvict = false;
                _evictEvent.set();
                _enableEvict = false;                
                _evictThread.join();
            }
            
        }
        
        virtual void _evictThreadFunc() ;
    private:
        void evictFunc(){
            _evictThreadFunc();
        };
    protected:
        size_t _maxSize;

        volatile bool _isEvicting;
        volatile  bool _enableEvict;
        Poco::RunnableAdapter<AbstractReplacableCache > _runnable;
        Poco::Thread _evictThread;
        Poco::Event _evictEvent;
        
        
};

template <class _TKey, class _TValue, class _THash , class _MemSizeGetter >
void AbstractReplacableCache<_TKey, _TValue, _THash, _MemSizeGetter> ::_evictThreadFunc() {
    while (_enableEvict) {
        this->_evictEvent.wait();
        if (!_enableEvict)
            break;

        
        size_t aSize = this->size(); // _dataHolder.size();
        if (aSize <= this->_maxSize)
            continue;
        _isEvicting = true;
        size_t wishSize = _maxSize - _maxSize / 10000;
        TValue aValue;

        while (this->size() > wishSize) {
            
            if (!_enableEvict)
                break;           
            TKey aKey;
            if (!this->popTail(aKey, aValue)) {
                _isEvicting = false;
                break;
            }
            if (AbstractCache<TKey, TValue>::_observer) {
                AbstractCache<TKey, TValue>::_observer->evicted(aKey, aValue);
            }
        }
        _isEvicting = false;

    }
}

}} 

#endif	/* ABSTRACTLRUCACHE_H */

