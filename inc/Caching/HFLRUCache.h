/* 
 * File:   HFLRUCache.h
 * Author: trungthanh
 *
 * Created on September 27, 2012, 10:18 PM
 */

#ifndef HFLRUCACHE_H
#define	HFLRUCACHE_H


#include "Caching/AbstractCache.h"

#include "Poco/Mutex.h"
#include <boost/functional/hash.hpp>


#include <vector>
#include <algorithm>
#include <hashtable.h>
#include <iostream>

namespace openstars { namespace caching {
    
        using namespace std;

        /*
         * HashFlatLRUCache
         * cac phan tu nam trong cac bucket cua bang bam. moi bucket la 1 sorted array 
         * Fix hash table size 
         */
        template <class _TKey, class _TValue, class _THash = boost::hash<_TKey> >
        class HFLRUCache : public AbstractCache<_TKey, _TValue> {
        protected:

            typedef _TKey TKey;
            typedef _TValue TValue;
            typedef _THash THash;
            typedef typename AbstractCache< _TKey, _TValue >::data_manipulator data_manipulator;

            struct TLRUValue {
            public:

                operator TValue & () {
                    return _value;
                }

                operator const TValue & () const {
                    return _value;
                }
                // if a node's prevKey equal to itself key, it means prevNode is null.
                TKey _nextKey;
                TKey _prevKey; // triple key over head
                TValue _value;
            };
            typedef TLRUValue* TLRUValuePtr;
            typedef std::pair<TKey, TLRUValue > DataPair;
            typedef std::vector< DataPair > TBucket;
            typedef typename TBucket::iterator BIterator;
            typedef typename TBucket::const_iterator BConstIterator; // bucket iterator

            //    typedef Poco::FastMutex MutexType;
            typedef openstars::caching::SpinLock MutexType;
            typedef MutexType::ScopedLock ScopedLockType;

            typedef std::vector <TBucket> DataHolder;

            class KVLesser {
            public:

                bool operator()(const DataPair& p1, const DataPair& p2) {
                    return p1.first < p2.first;
                }

                bool operator() (const DataPair& p1, const TKey key2) {
                    return p1.first < key2;
                }

                bool operator() (const TKey& key1, const DataPair p2) {
                    return key1 < p2.first;
                }
            };

        public:

            HFLRUCache(size_t lruSize, size_t tableSize, int lockSize = 1) : _hf()
            , _data()//(tableSize + 1 , TBucket(0))
            , _tableSize(tableSize)
            , _size(0)
            , _lockSize(lockSize)
            , _maxSize(lruSize) {

                init();
            }

            virtual ~HFLRUCache() {
            }
        protected:
            void init();
        public:
            //////override from AbstractCache
            bool has(const TKey& key) const;

            virtual int add(const TKey& key, const TValue& value);

            virtual int put(const TKey& key, const TValue& value);

            virtual int update(const TKey& key, const TValue& value);

            virtual int add_or_update(const TKey& key, const TValue& value);

            virtual int remove(const TKey& key);

            virtual size_t size()const {
                return _size;
            }

            virtual size_t maxSize()const {
                return _maxSize;
            }

            virtual void setMaxSize(size_t aSize) {
                this->_maxSize = aSize;
            }

            virtual TValue* get(const TKey& key); // return null if Caching not exist

            // get and remove the data
            virtual bool pop(const TKey& key, TValue& value);

            virtual bool popTail(TKey& key, TValue& value);
            
            // manipulate if exist
            virtual bool manipulateCache(const TKey& key, data_manipulator* manipulator);

            // manipulate
            virtual int manipulateCache(const TKey& key, data_manipulator* notfound, data_manipulator* mnpfound);

            virtual void manipulate_all_readonly(data_manipulator* manipulator);
            // cac thao tac can thiet: insert , find, erase, has, get , operator []
        protected:
            bool _has(const TKey& key) const;

            virtual int _add(const TKey& key, const TValue& value);

            virtual int _put(const TKey& key, const TValue& value);

            virtual int _update(const TKey& key, const TValue& value);

            virtual int _remove(const TKey& key);
            
            virtual TValue* _get(const TKey& key); // return null if Caching not exist

            virtual bool _pop(const TKey& key, TValue& value);

            virtual bool _manipulateCache(const TKey& key, data_manipulator* manipulator);
            // manipulate
            virtual int _manipulateCache(const TKey& key, data_manipulator* notfound, data_manipulator* mnpfound);

        public:

            bool get(const TKey& key, TValue& outVal)  {
                std::size_t hashkey = _bucketID(key);
                ScopedLockType aLock(_lruMutex);

                if (_isEmpty(_data[hashkey]))
                    return false;
                this->_linkToTopLRU(key, hashkey);
                if ( _getValInBucket(outVal, key, _data[hashkey]) )
                {
                    this->_linkToTopLRU(key, hashkey);
                    return true;                    
                }
                return false;
                
            }

            void clear() {
                ScopedLockType aLock(_lruMutex);
                
                for (size_t aIndex=0; aIndex < _data.size(); aIndex++) {
                    TBucket emptyBucket;
                    emptyBucket.swap(_data[aIndex]);
                    _size -= emptyBucket.size();
                }
                //_data.clear();
                this->_lruHeadIsSet = this->_lruTailIsSet = false;
                //_size = 0;
            }

        protected:

            bool _isEmpty(const TBucket& bucket) const {
                return (bucket.size() == 0);
            }

            std::size_t _bucketID(const TKey& key) const {
                return (_hf(key) & _tableSize);
            }

            TBucket& _getBucket(const TKey& key) {
                return _data[ _bucketID(key) ];
            }

            // search in vector

            bool _hasInBucket(const TKey& key, const TBucket& bucket) const {
                BConstIterator aIt = std::lower_bound(bucket.begin(), bucket.end(),
                        key, KVLesser());
                if (aIt != bucket.end() && aIt->first == key)
                    return true;
                return false;
            }

            bool _getValInBucket(TValue& outVal, const TKey& key, const TBucket& bucket) const {
                BConstIterator aIt = std::lower_bound(bucket.begin(), bucket.end(),
                        key, KVLesser());
                if (aIt != bucket.end() && aIt->first == key) {
                    outVal = aIt->second;
                    return true;
                }
                return false;
            }

            bool _insertToBucket(const DataPair& aPair, TBucket& bucket) {
                BIterator aIt = std::lower_bound(bucket.begin(), bucket.end(),
                        aPair, KVLesser());
                if (aIt != bucket.end() && aIt->first == aPair.first) {
                    /*memory tracking*/
                    this->decMem(aIt->second._value);                    
                    aIt->second._value = aPair.second._value;

                    /*memory tracking*/
                    this->incMem(aIt->second._value);
                    return false;
                }
                bucket.insert(aIt, aPair);
                /*memory tracking*/
                this->_memSize += this->sizeOfSpecialData( (const void*)&aPair, 0 );
                //this->incMem(aPair);
                
                _size++;
                return true;
            }

            bool _updateToBucket(const DataPair& aPair, TBucket& bucket) {
                BIterator aIt = std::lower_bound(bucket.begin(), bucket.end(),
                        aPair, KVLesser());
                if (aIt != bucket.end() && aIt->first == aPair.first) {
                    /*memory tracking*/
                    this->decMem(aIt->second._value);                    

                    aIt->second._value = aPair.second._value;

                    /*memory tracking*/
                    this->incMem(aIt->second._value);
                    return true;
                }
                return false;
            }

            // get value reference of a key, if it is not existed , insert a new item and return

            TValue& _getInsertInBucket(const TKey& key, TBucket& bucket) {
                BIterator aIt = std::lower_bound(bucket.begin(), bucket.end(),
                        key, KVLesser());
                if (aIt != bucket.end() && aIt->first == key) {
                    return aIt->second._value;
                }
                DataPair aPair;
                aPair.first = key;
                aPair.second._nextKey = key;
                aPair.second._prevKey = key;
                BIterator aInsertedIt = bucket.insert(aIt, aPair);
                _size++;
                return aInsertedIt->second._value;
            }

            TValue* _getInBucket(const TKey& key, TBucket& bucket) {
                BIterator aIt = std::lower_bound(bucket.begin(), bucket.end(),
                        key, KVLesser());
                if (aIt != bucket.end() && aIt->first == key) {
                    return &(TValue&) aIt->second;
                }
                return NULL;
            }

            TLRUValue* _getLruValueInBucket(const TKey& key, TBucket& bucket) {
                BIterator aIt = std::lower_bound(bucket.begin(), bucket.end(),
                        key, KVLesser());
                if (aIt != bucket.end() && aIt->first == key) {
                    return &aIt->second;
                }
                return NULL;
            }

            bool _removeFromBucket(const TKey& key, TBucket& bucket) {
                BIterator aIt = std::lower_bound(bucket.begin(), bucket.end(),
                        key, KVLesser());

                if (aIt != bucket.end() && aIt->first == key) {
                    bucket.erase(aIt);
                    _size--;
                    return true;
                }
                return false;
            }

            bool _removeFromBucket(const TKey& key, TValue& outValue, TBucket& bucket) {
                BIterator aIt = std::lower_bound(bucket.begin(), bucket.end(),
                        key, KVLesser());

                if (aIt != bucket.end() && aIt->first == key) {
                    outValue = aIt->second._value;
                    bucket.erase(aIt);
                    _size--;
                    return true;
                }
                return false;
            }


        private:

            void _linkToTopLRU(const TKey& key);
            void _linkToTopLRU(const TKey& key, size_t bucketID); //bucketID must be equal to _bucketID(key)
            void _unlinkLRU(const TKey& key);
            void _unlinkLRU(const TKey& key, size_t bucketID);
            void _unlinkLRUNode(const TKey& key, TLRUValue& aNode);
            void _evict();
        
        protected:
            //for calculating size of lru item
            virtual size_t sizeOfSpecialData(const void* dataPtr, int type){ 
                const DataPair* aPairPtr = (const DataPair*)dataPtr;
                return this->_sizeGetter(aPairPtr->first) 
                        + this->_sizeGetter(aPairPtr->second._nextKey)
                        + this->_sizeGetter(aPairPtr->second._prevKey)
                        + this->_sizeGetter(aPairPtr->second._value);
            }            

        protected:
            THash _hf;
            DataHolder _data;
            size_t _tableSize; // _tableSize is (2^n-1)
            std::size_t _size;
            size_t _lockSize;
            size_t _maxSize;
            TKey _lruHead;
            TKey _lruTail;
            bool _lruHeadIsSet;
            bool _lruTailIsSet;
            mutable MutexType _lruMutex;
            bool _isEvicting;


        };
        ////////////////
#define HFLRUCache_DeclareTmpl template <class _TKey, class _TValue, class _THash >
#define HFLRUCache_Clss HFLRUCache<_TKey, _TValue, _THash>

        HFLRUCache_DeclareTmpl
        void HFLRUCache_Clss::_linkToTopLRU(const _TKey& key) {
            //_unlinkLRU()
            if (key == _lruHead)
                return;
            std::size_t hashkey = _bucketID(key);
            this->_linkToTopLRU(key, hashkey);

        }

        HFLRUCache_DeclareTmpl
        void HFLRUCache_Clss::_linkToTopLRU(const _TKey& key, size_t hashkey) {
            //_unlinkLRU()
            if (_lruHeadIsSet && (key == _lruHead))
                return;
            TBucket& aCurrentBucket = _data[hashkey];

            TLRUValuePtr aLruNode = this->_getLruValueInBucket(key, aCurrentBucket);

            if (aLruNode == NULL){
                return;
            }
            if (!(_lruHeadIsSet && _lruTailIsSet)) {
                _lruHead = _lruTail = key;
                aLruNode->_prevKey = key;
                aLruNode->_nextKey = key;
                _lruTailIsSet = _lruHeadIsSet = true;
                return;
            }
            if (_lruTail == key) {
                _lruTail = aLruNode->_prevKey;
            }
            _unlinkLRUNode(key, *aLruNode);
            TLRUValue* headNode = _getLruValueInBucket(_lruHead, _data[ _bucketID(_lruHead) ]);
            if (headNode == NULL){
                return;
            }
            aLruNode->_nextKey = _lruHead;
            if (_lruHead != headNode->_prevKey) // if a node's prevKey equal to itself key, it means prevNode is null.
                aLruNode->_prevKey = headNode->_prevKey;
            else
                aLruNode->_prevKey = key;
            headNode->_prevKey = key;
            _lruHead = key;

            

        }

        HFLRUCache_DeclareTmpl
        void HFLRUCache_Clss::_unlinkLRUNode(const TKey& key, TLRUValue& aNode) {

            if (aNode._nextKey != key) {
                size_t next_hashkey = _bucketID(aNode._nextKey);
                TLRUValue* aNextNode = this->_getLruValueInBucket(aNode._nextKey, _data[ next_hashkey ]);
                if (aNextNode != NULL) {
                    if (aNode._prevKey != key)
                        aNextNode->_prevKey = aNode._prevKey;
                    else
                        aNextNode->_prevKey = aNode._nextKey; /* no prev for next node */
                }
            }

            if (aNode._prevKey != key) {
                size_t pre_hashkey = _bucketID(aNode._prevKey);

                TLRUValue* aPreNode = this->_getLruValueInBucket(aNode._prevKey, _data[ pre_hashkey ]);
                if (aPreNode != NULL) {
                    if (aNode._nextKey != key )
                        aPreNode->_nextKey = aNode._nextKey;
                    else
                        aPreNode->_nextKey = aNode._prevKey; /* no next for prev node */
                }

            }
            aNode._nextKey = aNode._prevKey = key;

        }

        HFLRUCache_DeclareTmpl
        void HFLRUCache_Clss::_unlinkLRU(const _TKey& key) {
            std::size_t hashkey = _bucketID(key);
            TBucket& aCurrentBucket = _data[hashkey];

            TLRUValue* aLruNode = this->_getLruValueInBucket(key, aCurrentBucket);

            if (aLruNode == NULL)
                return;

            if (_lruHead == key)
                _lruHead = aLruNode->_nextKey;
            if (_lruTail == key)
                _lruTail = aLruNode->_prevKey;
            _unlinkLRUNode(key, *aLruNode);

        }

        HFLRUCache_DeclareTmpl
        void HFLRUCache_Clss::_unlinkLRU(const _TKey& key, size_t hashkey) {
            //    std::size_t hashkey = _bucketID(key);
            TBucket& aCurrentBucket = _data[hashkey];

            TLRUValue* aLruNode = this->_getLruValueInBucket(key, aCurrentBucket);

            if (aLruNode == NULL) {
                return;
            }
            
            
            if (_lruHead == key && key != aLruNode->_nextKey)
                _lruHead = aLruNode->_nextKey;
            if (_lruTail == key && key != aLruNode->_prevKey)
                _lruTail = aLruNode->_prevKey;
            _unlinkLRUNode(key, *aLruNode);

        }

        HFLRUCache_DeclareTmpl
        void HFLRUCache_Clss::init() {
            //calculate table size
            size_t aSize = 1;
            while (aSize < _tableSize)
                aSize = aSize << 1;
            _data.resize(aSize + 1);
            _tableSize = aSize - 1; // all bits of table size is 1.

            // calculate lock size;
            aSize = 1;
            while (aSize < _lockSize)
                aSize = aSize << 1;
            _lockSize = aSize - 1;

            this->_lruHeadIsSet = _lruTailIsSet = false;
            _isEvicting = false;
            this->incMem(_data);
            this->_memSize += sizeof(*this);
        }

        HFLRUCache_DeclareTmpl
        bool HFLRUCache_Clss::has(const TKey& key) const {
            ScopedLockType aLock(_lruMutex);
            return _has(key);
        }
        
        HFLRUCache_DeclareTmpl
        bool HFLRUCache_Clss::_has(const TKey& key) const {
            std::size_t hashkey = _bucketID(key);


            if (_isEmpty(_data[hashkey]))
                return false;

            return _hasInBucket(key, _data[hashkey]);
        }        

        HFLRUCache_DeclareTmpl
        int HFLRUCache_Clss::add(const TKey& key, const TValue& value) {
            ScopedLockType aLock(_lruMutex);
            return _add(key, value);
        }

        HFLRUCache_DeclareTmpl
        int HFLRUCache_Clss::_add(const TKey& key, const TValue& value) {

            std::size_t hashkey = _bucketID(key);

            TBucket& aBucket = _data[hashkey];

            if (_hasInBucket(key, aBucket))
                return EFailed;
            DataPair aPair;
            aPair.first = key;
            TLRUValue &aLruVal = aPair.second;
            aLruVal._nextKey = aLruVal._prevKey = key;
            aLruVal._value = value;

            this->_insertToBucket(aPair, aBucket);

            this->_linkToTopLRU(key, hashkey);
            this->_evict();
            return EAdded;

        }

        HFLRUCache_DeclareTmpl
        int HFLRUCache_Clss::put(const TKey& key, const TValue& value) {
            ScopedLockType aLock(_lruMutex);
            return _put(key, value);
        }

        HFLRUCache_DeclareTmpl
        int HFLRUCache_Clss::_put(const TKey& key, const TValue& value) {
            int _return = 0;
            std::size_t hashkey = _bucketID(key);
            TBucket& aBucket = _data[hashkey];


            DataPair aPair;
            aPair.first = key;
            TLRUValue &aLruVal = aPair.second;
            aLruVal._nextKey = aLruVal._prevKey = key;
            aLruVal._value = value;

            if (this->_insertToBucket(aPair, aBucket))
                _return = EAdded;
            else
                _return = EOverwritten;
            this->_linkToTopLRU(key, hashkey);
            this->_evict();
            return _return;
        }

        HFLRUCache_DeclareTmpl
        int HFLRUCache_Clss::update(const TKey& key, const TValue& value) {
            ScopedLockType aLock(_lruMutex);

            return _update(key, value);

        }

        HFLRUCache_DeclareTmpl
        int HFLRUCache_Clss::_update(const TKey& key, const TValue& value) {
            std::size_t hashkey = _bucketID(key);
            

            DataPair aPair;
            aPair.first = key;
            TLRUValue &aLruVal = aPair.second;
            aLruVal._value = value;

            TBucket& aBucket = _data[hashkey];
            if (!this->_updateToBucket(aPair, aBucket))
                return EFailed;

            this->_linkToTopLRU(key, hashkey);
            this->_evict();
            
            return EOverwritten;

        }

        HFLRUCache_DeclareTmpl
        int HFLRUCache_Clss::add_or_update(const TKey& key, const TValue& value) {
            return put(key, value);
        }

        HFLRUCache_DeclareTmpl
        int HFLRUCache_Clss::remove(const TKey& key) {
            ScopedLockType aLock(_lruMutex);
            return _remove(key);
        }

        HFLRUCache_DeclareTmpl
        int HFLRUCache_Clss::_remove(const TKey& key) {
            std::size_t hashkey = _bucketID(key);
            int _return = EFailed;
            this->_unlinkLRU(key); //Todo: other thread access key here 

            TBucket& aBucket = _data[hashkey];

            if (_isEmpty(aBucket))
                return EFailed;

            if (_removeFromBucket(key, aBucket))
                _return = ERemoved;
            
            return _return;
        }

        HFLRUCache_DeclareTmpl
        _TValue* HFLRUCache_Clss::get(const TKey& key) {

            ScopedLockType aLock(_lruMutex);
            return _get(key);
        }

        HFLRUCache_DeclareTmpl
        _TValue* HFLRUCache_Clss::_get(const TKey& key) {
            std::size_t hashkey = _bucketID(key);

            this->_linkToTopLRU(key, hashkey);
            this->_evict();

            TBucket& aBucket = _data[hashkey];
            return this->_getInBucket(key, aBucket);
        }

        HFLRUCache_DeclareTmpl
        bool HFLRUCache_Clss::pop(const TKey& key, TValue& value) {
            ScopedLockType aLock(_lruMutex);
            return _pop(key, value);
        }
        
        HFLRUCache_DeclareTmpl
        bool HFLRUCache_Clss::_pop(const TKey& key, TValue& value) {

            std::size_t hashkey = _bucketID(key);
            this->_unlinkLRU(key, hashkey);

            TBucket& aBucket = _data[hashkey];
            bool result = this->_removeFromBucket(key, value, aBucket);
            return result;
        }

        HFLRUCache_DeclareTmpl
        bool HFLRUCache_Clss::popTail(TKey& key, TValue& value) {
            ScopedLockType aLock(_lruMutex);
            key = this->_lruTail;
            return _pop(key, value);
        }
        
        HFLRUCache_DeclareTmpl
        bool HFLRUCache_Clss::manipulateCache(const TKey& key, data_manipulator* manipulator) {
            if (!manipulator)
                return false;
            ScopedLockType aLock(_lruMutex);

            return _manipulateCache(key, manipulator);
        }

        HFLRUCache_DeclareTmpl
        bool HFLRUCache_Clss::_manipulateCache(const TKey& key, data_manipulator* manipulator) {

            std::size_t hashkey = _bucketID(key);
            this->_linkToTopLRU(key, hashkey);
            this->_evict();


            TBucket& aBucket = _data[hashkey];
            TValue* pValue = this->_getInBucket(key, aBucket);
            if (pValue)
                return manipulator->manipulate(key, *pValue);
            return false;
        }

        HFLRUCache_DeclareTmpl
        int HFLRUCache_Clss::manipulateCache(const TKey& key, data_manipulator* notfound, data_manipulator* mnpfound) {
            if ((!notfound) || (!mnpfound))
                return EFailed;
            ScopedLockType aLock(_lruMutex);
            return _manipulateCache(key, notfound, mnpfound);
        }

        HFLRUCache_DeclareTmpl
        int HFLRUCache_Clss::_manipulateCache(const TKey& key, data_manipulator* notfound, data_manipulator* mnpfound) {
            int _return = 0;
            std::size_t hashkey = _bucketID(key);
            TBucket& aBucket = _data[hashkey];
            
            TValue* pValue = this->_getInBucket(key, aBucket);
            if (pValue == NULL) {
                pValue = &this->_getInsertInBucket(key, aBucket);
                notfound->manipulate(key, *pValue);
                //Todo: notify observers
            }
            if (pValue){
                this->decMem(*pValue);
                _return = mnpfound->manipulate(key, *pValue);
                this->incMem(*pValue);
            }
            else
                _return = EFailed;
            if (_return != EFailed){
                this->_linkToTopLRU(key, hashkey);
                this->_evict();
            }
            return _return;
        }

        HFLRUCache_DeclareTmpl
        void HFLRUCache_Clss::_evict() {
            if (_isEvicting)
                return;
            size_t aSize = _size; // _dataHolder.size();
            if (aSize <= this->_maxSize)
                return;
            _isEvicting = true;
            size_t wishSize = _maxSize - _maxSize / 10000;
            TValue aValue;

            while (_size > wishSize) {
                TKey aKey = _lruTail;
                if (!this->_pop(aKey, aValue)) {
                    _isEvicting = false;
                    return;
                }
                if (AbstractCache<TKey, TValue>::_observer) {
                    AbstractCache<TKey, TValue>::_observer->evicted(aKey, aValue);
                }
            }
            _isEvicting = false;

        }
        
        HFLRUCache_DeclareTmpl
        void HFLRUCache_Clss::manipulate_all_readonly(data_manipulator* manipulator) {
            for (size_t aIndex = 0; aIndex < _data.size(); aIndex++) {
                TBucket emptyBucket;

                TBucket& aBucket = _data[aIndex];
                size_t aSize = 0;
                {
                    ScopedLockType aLock( this->_lruMutex );
                    aSize = _data[aIndex].size();
                }
                TKey key;
                TValue value;
                for (size_t bucketIndex = 0; bucketIndex < aSize; bucketIndex++) {
                    {
                        ScopedLockType aLock( this->_lruMutex );
                        aSize = _data[aIndex].size();
                        if (bucketIndex >= aSize)
                            break;
                        key = aBucket[bucketIndex].first;
                        value = aBucket[bucketIndex].second;
                    }
                    manipulator->manipulate(key, value);
                }
            }

        }

    }
}


#endif	/* HFLRUCACHE_H */

