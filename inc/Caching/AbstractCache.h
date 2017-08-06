/* 
 * File:   AbstractCache.h
 * Author: trungthanh
 *
 * Created on September 21, 2012, 7:15 AM
 * 
 * Abstract class of caching
 * 
 */

#ifndef UP_CACHING_ABSTRACTCACHE_H
#define	UP_CACHING_ABSTRACTCACHE_H

#include "Caching/CacheBase.h"
#include "Caching/MemoryStats.h"

#include "boost/atomic.hpp"
#include <boost/smart_ptr/detail/spinlock.hpp>

namespace openstars { namespace caching {
    
        template <class _TKey, class _TValue>
        class CacheObserver
        {
        public:
            typedef _TKey TKey;
            typedef _TValue TValue;
        public:
            virtual void added(const TKey& key, const TValue& value) = 0;
            virtual void removed(const TKey& key, const TValue& value) = 0;

            virtual bool evictable(const TKey& key, const TValue& value) {return true;}

            virtual void evicted(const TKey& key, const TValue& value) = 0;

            virtual void missed(const TKey& key)
            {
            };
        };

        enum TOperationResult
        {
            EFailed = -1,
            EUnknown = 0,
            EAdded = 1,
            EOverwritten = 2,
            ERemoved = 3,
            EManipulated

        };

        template <class _TKey, class _TValue, class _MemSizeGetter = MemSizeGetter>
        class AbstractCache : public CacheBase
        {
        public:
            typedef _TKey TKey;
            typedef _TValue TValue;
            typedef CacheObserver<_TKey, _TValue> ObserverType;
            typedef _MemSizeGetter SizeGetter;

        public:

            AbstractCache() : _observer(NULL), _memSize(0)
            {
            }
        public:
            // atomic data manipulator without external locking

            class data_manipulator
            {
            public:
                virtual bool manipulate(const TKey& key, TValue& value) = 0;
            };

        public:
            virtual bool has(const TKey& key) const = 0;

            virtual int add(const TKey& key, const TValue& value) = 0;

            virtual int put(const TKey& key, const TValue& value) = 0;

            virtual int putAndMarkDirty(const TKey& key, const TValue& value){
                return put(key,value);
            }

            virtual int update(const TKey& key, const TValue& value) = 0;

            virtual int remove(const TKey& key) = 0;

            virtual TValue* get(const TKey& key) = 0; // return null if Caching not exist

            virtual bool get(const TKey& key, TValue& value) = 0;

            virtual void clear() = 0;

            virtual size_t size()const = 0;

            virtual size_t maxSize()const = 0;

            virtual void setMaxSize(size_t aSize) = 0;

            // get and remove the data

            virtual bool pop(const TKey& key, TValue& value)
            {
                return false;
            };
            
            virtual bool supportDirty()const{
                return false;
            }
            
            virtual bool popHeadDirty(TKey& key, TValue& value)
            {
                return false;
            };
            
            virtual bool popHeadDirty(TKey& key, TValue& value, data_manipulator* manipulator)
            {
                return false;
            };            
            
            virtual size_t dirtySize()const 
            {
                return 0;
            }

            // atomic manipulate data
            // manipulate if exist
            virtual bool manipulateCache(const TKey& key, data_manipulator* manipulator) = 0;

            // manipulate
            virtual int manipulateCache(const TKey& key, data_manipulator* notfound, data_manipulator* mnpfound) = 0;

            //scan Caching and manipulate (copy of) each item

            virtual void manipulate_all_readonly(data_manipulator* manipulator)
            {
            }

            //clear items and manipulate them

            virtual void manipulate_all_clear(data_manipulator* manipulator)
            {
            }

            virtual void setObserver(ObserverType* observer)
            {
                _observer = observer;
            }

            virtual void startEvict() {}
            virtual void stopEvict(){}
            
        public:

            size_t getMemSize()
            {
                return this->_memSize;
            }

        protected:

            /* memory monitoring functions */
            template <class _T>
            void incMem(const _T& aItem)
            {
                if (_enableMemTracking)
                    _memSize += _sizeGetter(aItem);
            }

            template <class _T>
            void decMem(const _T& aItem)
            {
                if (_enableMemTracking)
                    _memSize -= _sizeGetter(aItem);
            }

            virtual size_t sizeOfSpecialData(const void* dataPtr, int type)
            {
                return 0;
            }

            void incMem2(const void* dataPtr, int type)
            {
                if (_enableMemTracking)
                    _memSize += sizeOfSpecialData(dataPtr, type);
            }

            void decMem2(const void* dataPtr, int type)
            {
                if (_enableMemTracking)
                    _memSize -= sizeOfSpecialData(dataPtr, type);
            }

        protected:
            ObserverType* _observer;
            boost::atomic< size_t > _memSize;
            SizeGetter _sizeGetter;
        };
        

        class SpinLock {
        private:
          typedef enum {Locked, Unlocked} LockState;
          boost::atomic<LockState> state_;

        public:
          SpinLock()  : state_(Unlocked) {
          }

          void lock()
          {
            unsigned k = 0;  
            while (state_.exchange(Locked, boost::memory_order_acquire) == Locked) {
              /* wait */
                boost::detail::yield( k );
                k++;
            }
          }
          void unlock()
          {
            state_.store(Unlocked, boost::memory_order_release);
          }
        public:
            class ScopedLock
                    /// A class that simplifies thread synchronization
                    /// with a mutex.
                    /// The constructor accepts a Mutex (and optionally
                    /// a timeout value in milliseconds) and locks it.
                    /// The destructor unlocks the mutex.
            {
            public:
                    explicit ScopedLock(SpinLock& mutex): _mutex(mutex)
                    {
                            _mutex.lock();
                    }

//                    ScopedLock(M& mutex, long milliseconds): _mutex(mutex)
//                    {
//                            _mutex.lock(milliseconds);
//                    }

                    ~ScopedLock()
                    {
                            _mutex.unlock();
                    }

            private:
                    SpinLock& _mutex;

                    ScopedLock();
                    ScopedLock(const ScopedLock&);
                    ScopedLock& operator = (const ScopedLock&);
            };            
        };        

    }
}

#endif	/* ABSTRACTCACHE_H */

