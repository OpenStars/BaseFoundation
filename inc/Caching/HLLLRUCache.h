/* 
 * File:   HLLLRUCache.h
 * Author: trungthanh
 *
 * Created on March 20, 2014, 12:54 AM
 */

#ifndef UPCACHING_HLLLRUCACHE_H
#define	UPCACHING_HLLLRUCACHE_H



/*
 * Hash and list based caching
 */

#include "Caching/AbstractCache.h"
#include "Caching/AbstractReplacableCache.h"
#include <Poco/Mutex.h>

#include <boost/functional/hash.hpp>
#include <list>
#include <vector>
#include <algorithm>
#include <hashtable.h>
#include <iostream>

namespace openstars { namespace caching {
    
using namespace std;
/*
 * Hash linked key Cache
 * cac phan tu nam trong cac bucket cua bang bam. moi bucket la 1 sorted array 
 * Fix hash table size 
 * Locking: bucket based, spinlock 
 */
template <class _TKey, class _TValue, class _THash = boost::hash<_TKey> , class _MemSizeGetter = MemSizeGetter, class _MutexType = Up::Caching::SpinLock >
class HLLLRUCache: public AbstractReplacableCache<_TKey, _TValue, _MemSizeGetter>  {
    
protected:
    typedef AbstractCache<_TKey, _TValue, _MemSizeGetter> BaseClass;
    typedef AbstractReplacableCache<_TKey, _TValue, _MemSizeGetter> BaseLRUClass;
    typedef _TKey TKey;
    typedef _TValue TValue;
    typedef _THash THash;
    typedef typename AbstractCache< _TKey, _TValue >::data_manipulator data_manipulator;
    

    typedef std::pair<TKey, TValue > DataPair;

    struct listNode{
        listNode():data(), next(NULL), lruNext(NULL), lruPrev(NULL) {}
        DataPair data;
        listNode* next;
        listNode* lruNext;
        listNode* lruPrev;
    };
    struct TBucket{
        listNode* head;
        TBucket():head(NULL){}
        ~TBucket(){
            clear();
        }
        
        /*
         * clear item in bucket, return number of item before clear
         */
        size_t clear()
        {
            size_t count = 0;
            while (head!=NULL){
                listNode* toDelete = head;
                head = head->next;
                count++;
                delete toDelete;
            }
            return count;
        }
        
        int size() const
        {
            size_t count = 0;
            const listNode* aNode = head;
            while (aNode != NULL)
            {
                count++;
                aNode = aNode->next;
            }
            return count;
        }
        
        typedef listNode* listNodePtr;
        typedef const listNode* listNodePtrC;
        
        listNode** find(const TKey& aKey){
            listNode** aNode = &head;
            while ( (*aNode) && (*aNode)->data.first != aKey)
                aNode = &(*aNode)->next;
            return aNode;
        }

        const listNodePtrC* find(const TKey& aKey) const{
            const listNodePtrC* aNode = &head;
            while ( (*aNode) && (*aNode)->data.first != aKey)
                aNode = &(*aNode)->next;
            return aNode;
        }
        
        /*
         * setData, return true if it is not existed otherwise return false
         */
        bool setData(const DataPair& aPair)
        {
            listNode** aNode = find(aPair.first);
            if (aNode && (*aNode))
            {
                (*aNode)->data.second = aPair.second; // chi update value
                return false;
            }
            else {
                (*aNode) = new listNode();
                (*aNode)->data = aPair;                
                return true;
            }
        }
        
        bool updateData(const DataPair& aPair)
        {
            listNode** aNode = find(aPair.first);
            if (aNode && (*aNode))
            {
                (*aNode)->data.second = aPair.second;
                return true;
            }
            return false;            
        }
        
        /*
         * Neu co pair ung voi key roi thi return, chua co thi tao moi va return.
         */
        DataPair& getOrAddNewPair(const TKey& aKey, bool &isNew)
        {
            listNode** aNode = find(aKey);
            if (aNode && (*aNode))
            {
                isNew = false;
                return (*aNode)->data;                
            }
            else {
                (*aNode) = new listNode();
                (*aNode)->data.first = aKey;
                isNew = true;
                                
                return (*aNode)->data;
            }
        }
        
        bool getValue(const TKey& aKey, TValue& outValue) const
        {
            const listNodePtrC* aNode = find(aKey);
            if (aNode && (*aNode) && ( (*aNode)->data.first == aKey))
            {
                outValue = (*aNode)->data.second;
                return true;
            }
            return false;
            
        }
        
        TValue* getValuePtr(const TKey& aKey)
        {
            listNode** aNode = find(aKey);
            if (aNode && (*aNode) && ( (*aNode)->data.first == aKey))
            {
                return &(*aNode)->data.second;                
            }
            return NULL;
        }

        const TValue* getValuePtr(const TKey& aKey) const
        {
            const listNodePtrC* aNode = find(aKey);
            if (aNode && (*aNode) && ( (*aNode)->data.first == aKey))
            {
                return &(*aNode)->data.second;
                
            }
            return NULL;
        }
        
        
        bool remove(const TKey& aKey)
        {
            listNode** aNode = find(aKey);
            if (aNode && (*aNode) && ( (*aNode)->data.first == aKey))
            {
                listNode* removed = *aNode;
                *aNode = removed->next;
                delete removed;
                return true;
            }
            return false;            
        }
        
        bool remove(const TKey& aKey, TValue& oldValue)
        {
            listNode** aNode = find(aKey);
            if (aNode && (*aNode) && ( (*aNode)->data.first == aKey))
            {
                listNode* removed = *aNode;
                *aNode = removed->next;
                oldValue = removed->data.second;
                delete removed;
                return true;
            }
            return false;            
        }
        
        
    };
    
//    typedef Poco::FastMutex MutexType;
    typedef _MutexType MutexType;
    typedef typename MutexType::ScopedLock ScopedLockType;

    typedef std::vector <TBucket> DataHolder;

    class KVLesser {
    public:
        bool operator()(const DataPair& p1, const DataPair& p2) {
            return p1.first < p2.first;
        }
        
        bool operator() (const DataPair& p1, const TKey key2){
            return p1.first < key2;
        }
        bool operator() (const TKey& key1, const DataPair p2){
            return key1 < p2.first;
        }
    };
    
public:

    HLLLRUCache(size_t lruSize, int tableSize, int lockSize = 1) 
    :BaseLRUClass(lruSize)
    ,_hf()
    , _data()//(tableSize + 1 , TBucket(0))
    , _tableSize(tableSize)
    , _size(0)
    , _lockSize(lockSize)
    ,_lruHead(NULL)
    ,_lruTail(NULL)
    {
        init();
    }

    virtual ~HLLLRUCache() {
    }
protected:
    void init();
public:
    //////override from AbstractCache
    bool has(const TKey& key) const ;
    
    virtual int add(const TKey& key, const TValue& value) ;

    virtual int put(const TKey& key, const TValue& value) ;

    virtual int update(const TKey& key, const TValue& value) ;

    virtual int add_or_update(const TKey& key, const TValue& value) ;

    virtual int remove(const TKey& key) ;

    virtual size_t size()const {return _size; }

    virtual TValue* get(const TKey& key) ; // return null if Caching not exist

    // get and remove the data
    virtual bool pop(const TKey& key, TValue& value);
        
    virtual bool popTail(TKey& key, TValue& value);    
    
    // manipulate if exist
    virtual bool manipulateCache(const TKey& key, data_manipulator* manipulator) ;

    // manipulate
    virtual int manipulateCache(const TKey& key, data_manipulator* notfound, data_manipulator* mnpfound) ;    
    
    virtual void manipulate_all_readonly(data_manipulator* manipulator);

public:
    void insert(const DataPair& aPair) {
        std::size_t hashkey = _bucketID(aPair.first);
        ScopedLockType aLock ( _lruMutex );
        _insertToBucket(aPair, _data[ hashkey ]);
    }

    void erase(const TKey& key) {
        std::size_t hashkey = _bucketID(key);
        ScopedLockType aLock ( _lruMutex );
        if (_isEmpty(_data[hashkey])) 
            return;
        _removeFromBucket(key, _data[hashkey]);
    }

    bool get(const TKey& key, TValue& outVal)  {
        std::size_t hashkey = _bucketID(key);
        ScopedLockType aLock ( _lruMutex );
        
        if (_isEmpty(_data[hashkey])) 
            return false;
        if (_getValInBucket(outVal, key, _data[hashkey]) )
        {
            this->_linkToTopLRU(key, hashkey);
            return true;
        }
        return false;
    }

    TValue& operator[](const TKey& key) {
        std::size_t hashkey = _bucketID(key);
        ScopedLockType aLock ( _lruMutex );
        
        return this->_getInsertInBucket(key, _data[hashkey] );
    }

    void clear() {
        for (size_t aIndex = 0; aIndex < _data.size() ; aIndex++){
            TBucket emptyBucket;
            ScopedLockType aLock( _lruMutex );
            _size -= emptyBucket.clear();
            //_size -= emptyBucket.size();
        }
        //_data.clear();
        _size = 0;
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

        return bucket.getValuePtr(key) != NULL;
    }

    bool _getValInBucket(TValue& outVal, const TKey& key, const TBucket& bucket) const {
        return bucket.getValue(key, outVal);
    }

    bool _insertToBucket(const DataPair& aPair, TBucket& bucket) {
        if (bucket.setData(aPair) )
        {
            _size++;
            return true;
        }

        return false;
    }

    bool _updateToBucket(const DataPair& aPair, TBucket& bucket) {
        return bucket.updateData(aPair);
    }
    
    // get value reference of a key, if it is not existed , insert a new item and return

    TValue& _getInsertInBucket(const TKey& key, TBucket& bucket) {
        bool isNew = false;
        TValue& aValue = bucket.getOrAddNewPair(key, isNew).second;
        if (isNew){
            _size++;
            /*this->incMem( std::make_pair(key, TLRUValue()) );*/
        }
        return aValue;
    }

    TValue* _getInBucket(const TKey& key, TBucket& bucket) {
        return bucket.getValuePtr(key);        
    }
    
        
//    TLRUValue* _getLruValueInBucket(const TKey& key, TBucket& bucket) {
//        return bucket.getValuePtr(key);
//    }

    bool _removeFromBucket(const TKey& key, TBucket& bucket) {
        if (bucket.remove(key) )
        {
             _size--;
             return true;
        }
        return false;
    }

    
    bool _removeFromBucket(const TKey& key, TValue& outValue, TBucket& bucket) {
        if(bucket.remove(key, outValue))
        {
            _size--;
            return true;
        }
        return false;
    }
    
    void _linkToTopLRU(const TKey& key);
    void _linkToTopLRU(const TKey& key, size_t bucketID); //bucketID must be equal to _bucketID(key)
    void _unlinkLRU(const TKey& key);
    void _unlinkLRU(const TKey& key, size_t bucketID);
    void _unlinkLRUNode(const TKey& key, listNode* aNode);
    void _evict();
    
    virtual bool _pop(const TKey& key, TValue& value);
protected:
    THash _hf;
    DataHolder _data;
    size_t _tableSize; // _tableSize is (2^n-1)
    std::size_t _size;
    size_t _lockSize;
    //std::vector< MutexType > _mutexs;
    //MutexType*  _mutexs;

    listNode* _lruHead;
    listNode* _lruTail;
    bool _lruHeadIsSet;
    bool _lruTailIsSet;
    mutable MutexType _lruMutex;
    
};
////////////////
#define HLLLRUCache_DeclareTmpl template <class _TKey, class _TValue, class _THash , class _MemSizeGetter, class _MutexType>
#define HLLLRUCache_Clss HLLLRUCache<_TKey, _TValue, _THash, _MemSizeGetter, _MutexType>

HLLLRUCache_DeclareTmpl
void HLLLRUCache_Clss::_linkToTopLRU(const _TKey& key) {
   //_unlinkLRU()
   if (key == _lruHead)
       return;
   std::size_t hashkey = _bucketID(key);
   this->_linkToTopLRU(key, hashkey);

}

HLLLRUCache_DeclareTmpl
void HLLLRUCache_Clss::_linkToTopLRU(const _TKey& key, size_t hashkey) {
   //_unlinkLRU()
//   if (_lruHeadIsSet && (key == _lruHead))
//       return;
   TBucket& aCurrentBucket = _data[hashkey];

   listNode* aLruNode = *aCurrentBucket.find(key);
   
   if (aLruNode == NULL){
       return;
   }

   if (aLruNode == _lruHead)
       return;

   if (!(_lruHead != NULL && _lruTail !=NULL )) {
       _lruHead = _lruTail = aLruNode;
       aLruNode->lruNext = NULL;
       aLruNode->lruPrev = NULL;
       return;
   }
   if (_lruTail == aLruNode) {
       _lruTail = aLruNode->lruPrev;
   }
   
   _unlinkLRUNode(key, aLruNode);
   listNode* headNode = _lruHead;//_getLruValueInBucket(_lruHead, _data[ _bucketID(_lruHead) ]);
   if (headNode == NULL){
       return;
   }
   aLruNode->lruNext = _lruHead;
   if (_lruHead->lruPrev) // if a node's prevKey equal to itself key, it means prevNode is null.
       aLruNode->lruPrev = headNode->lruPrev;
   else
       aLruNode->lruPrev = NULL;
   headNode->lruPrev = aLruNode; 
   _lruHead = aLruNode;

}

HLLLRUCache_DeclareTmpl
void HLLLRUCache_Clss::_unlinkLRUNode(const TKey& /*key*/, listNode* aNode) {
    listNode* aNext = aNode->lruNext;
    listNode* aPrev = aNode->lruPrev;
    if (aNext)
        aNext->lruPrev = aPrev;
    if (aPrev)
        aPrev->lruNext = aNext;
    aNode->lruPrev = aNode->lruNext = NULL;

//   if (aNode.nextKey != key) {
//       size_t next_hashkey = _bucketID(aNode.nextKey);
//       TLRUValue* aNextNode = this->_getLruValueInBucket(aNode.nextKey, _data[ next_hashkey ]);
//       if (aNextNode != NULL) {
//           if (aNode.prevKey != key)
//               aNextNode->prevKey = aNode.prevKey;
//           else
//               aNextNode->prevKey = aNode.nextKey; /* no prev for next node */
//       }
//   }
//
//   if (aNode.prevKey != key) {
//       size_t pre_hashkey = _bucketID(aNode.prevKey);
//
//       TLRUValue* aPreNode = this->_getLruValueInBucket(aNode.prevKey, _data[ pre_hashkey ]);
//       if (aPreNode != NULL) {
//           if (aNode.nextKey != key )
//               aPreNode->nextKey = aNode.nextKey;
//           else
//               aPreNode->nextKey = aNode.prevKey; /* no next for prev node */
//       }
//
//   }
//   aNode.nextKey = aNode.prevKey = key;
//
}

HLLLRUCache_DeclareTmpl
void HLLLRUCache_Clss::_unlinkLRU(const _TKey& key) {
   std::size_t hashkey = _bucketID(key);
   TBucket& aCurrentBucket = _data[hashkey];

   listNode* aLruNode = *aCurrentBucket.find(key);//this->_getLruValueInBucket(key, aCurrentBucket);

   if (aLruNode == NULL)
       return;

   if (_lruHead == aLruNode)
       _lruHead = aLruNode->lruNext;
   if (_lruTail == aLruNode)
       _lruTail = aLruNode->lruPrev;
   _unlinkLRUNode(key, aLruNode);

}

HLLLRUCache_DeclareTmpl
void HLLLRUCache_Clss::_unlinkLRU(const _TKey& key, size_t hashkey) {
   //    std::size_t hashkey = _bucketID(key);
//   TBucket& aCurrentBucket = _data[hashkey];
//
//   TLRUValue* aLruNode = this->_getLruValueInBucket(key, aCurrentBucket);
//
//   if (aLruNode == NULL) {
//       return;
//   }
//
//
//   if (_lruHead == key && key != aLruNode->nextKey)
//       _lruHead = aLruNode->nextKey;
//   if (_lruTail == key && key != aLruNode->prevKey)
//       _lruTail = aLruNode->prevKey;
//   _unlinkLRUNode(key, *aLruNode);
   TBucket& aCurrentBucket = _data[hashkey];

   listNode* aLruNode = *aCurrentBucket.find(key);//this->_getLruValueInBucket(key, aCurrentBucket);

   if (aLruNode == NULL)
       return;

   if (_lruHead == aLruNode)
       _lruHead = aLruNode->lruNext;
   if (_lruTail == aLruNode)
       _lruTail = aLruNode->lruPrev;
   _unlinkLRUNode(key, aLruNode);

}


HLLLRUCache_DeclareTmpl 
void HLLLRUCache_Clss::init() {
    //calculate table size
    size_t aSize = 1;
    while (aSize < _tableSize)
        aSize = aSize<<1;
    _data.resize(aSize + 1);
    _tableSize = aSize - 1; // all bits of table size is 1.
    
    // calculate lock size;
    aSize = 1;
    while (aSize < _lockSize)
        aSize = aSize << 1;
    //_mutexs = new MutexType[aSize+1];
    //_mutexs.resize( aSize + 1);
    _lockSize = aSize - 1;
    
    // calculate initial estimated memory size
    //this->_memSize += sizeof(_mutexs) + (aSize+1)* sizeof(MutexType); //
    this->_memSize += this->_sizeGetter(_data);
    this->_memSize += sizeof(*this);
    this->_lruHeadIsSet = _lruTailIsSet = false;
    BaseLRUClass::_isEvicting = false;
    this->incMem(_data);
    this->_memSize += sizeof(*this);

}


HLLLRUCache_DeclareTmpl 
bool HLLLRUCache_Clss::has(const TKey& key) const {
    std::size_t hashkey = _bucketID(key);
    
    ScopedLockType aLock( _lruMutex );

    if (_isEmpty(_data[hashkey])) 
        return false;

    return _hasInBucket(key, _data[hashkey]);
}

HLLLRUCache_DeclareTmpl    
int HLLLRUCache_Clss::add(const TKey& key, const TValue& value) {
    std::size_t hashkey = _bucketID(key);
    
    ScopedLockType aLock( _lruMutex );
    
    TBucket& aBucket = _data[hashkey];
    
    if (_hasInBucket(key, aBucket ) )
        return EFailed;
    
    this->_insertToBucket( std::make_pair(key, value) , aBucket );
    this->_linkToTopLRU(key, hashkey);
    _evict();
    return EAdded;
    
}

HLLLRUCache_DeclareTmpl
int HLLLRUCache_Clss::put(const TKey& key, const TValue& value) {
    std::size_t hashkey = _bucketID(key);
    ScopedLockType aLock(_lruMutex );

    TBucket& aBucket = _data[hashkey];

    
    int _return = EOverwritten;
    if (this->_insertToBucket( std::make_pair(key, value) , aBucket ) )
        _return = EAdded;
    
    this->_linkToTopLRU(key, hashkey);
    
    _evict();

    return _return;;
    
}

HLLLRUCache_DeclareTmpl
int HLLLRUCache_Clss::update(const TKey& key, const TValue& value) {
    std::size_t hashkey = _bucketID(key);
    ScopedLockType aLock( _lruMutex );


    TBucket& aBucket = _data[hashkey];

    if (!this->_updateToBucket(std::make_pair(key, value), aBucket))
        return EFailed;

    this->_linkToTopLRU(key, hashkey);
    this->_evict();
    return EOverwritten;
}

HLLLRUCache_DeclareTmpl
int HLLLRUCache_Clss::add_or_update(const TKey& key, const TValue& value) 
{
    return put(key, value);
}

HLLLRUCache_DeclareTmpl
int HLLLRUCache_Clss::remove(const TKey& key) {
    std::size_t hashkey = _bucketID(key);
    ScopedLockType aLock( _lruMutex );

    int _return = EFailed;
    this->_unlinkLRU(key); //Todo: other thread access key here 

    TBucket& aBucket = _data[hashkey];

    if (_isEmpty(aBucket))
        return EFailed;

    if (_removeFromBucket(key, aBucket))
        _return = ERemoved;

    return _return;
    
}


HLLLRUCache_DeclareTmpl
_TValue* HLLLRUCache_Clss::get(const TKey& key) {
    std::size_t hashkey = _bucketID(key);
    ScopedLockType aLock( _lruMutex );

    TBucket& aBucket = _data[hashkey];
    _TValue* result = this->_getInBucket(key, aBucket);
    if (result == NULL && BaseClass::_observer != NULL){
        BaseClass::_observer->missed(key);
    }
    if(result)
        this->_linkToTopLRU(key, hashkey);
    return result;
}

HLLLRUCache_DeclareTmpl
bool HLLLRUCache_Clss::pop(const TKey& key, TValue& value){
    std::size_t hashkey = _bucketID(key);
    ScopedLockType aLock( _lruMutex );

    this->_unlinkLRU(key, hashkey);

    TBucket& aBucket = _data[hashkey];
    return this->_removeFromBucket(key, value, aBucket);
}

HLLLRUCache_DeclareTmpl
bool HLLLRUCache_Clss::_pop(const TKey& key, TValue& value){
    std::size_t hashkey = _bucketID(key);
    this->_unlinkLRU(key, hashkey);
    TBucket& aBucket = _data[hashkey];
    return this->_removeFromBucket(key, value, aBucket);
}

HLLLRUCache_DeclareTmpl
bool HLLLRUCache_Clss::popTail(TKey& key, TValue& value){
    ScopedLockType aLock( this->_lruMutex );
    if (this->_lruTail)
        key = _lruTail->data.first;
    
    std::size_t hashkey = _bucketID(key);

    this->_unlinkLRU(key, hashkey);

    TBucket& aBucket = _data[hashkey];
    return this->_removeFromBucket(key, value, aBucket);
}

HLLLRUCache_DeclareTmpl
bool HLLLRUCache_Clss::manipulateCache(const TKey& key, data_manipulator* manipulator) {
    if (!manipulator)
        return false;
    std::size_t hashkey = _bucketID(key);
    ScopedLockType aLock( _lruMutex );

    this->_linkToTopLRU(key, hashkey);
    this->_evict();
    
    
    TBucket& aBucket = _data[hashkey];
    TValue* pValue = this->_getInBucket(key, aBucket);
    if (pValue){
        
        //this->decMem(*pValue);
        
        bool result = manipulator->manipulate(key, *pValue);
        
        //this->incMem(*pValue);
        
        return result;
    }
    return false;    
}

HLLLRUCache_DeclareTmpl
int HLLLRUCache_Clss::manipulateCache(const TKey& key, data_manipulator* notfound, data_manipulator* mnpfound) {
    if ( (!notfound ) || (!mnpfound) )
        return EFailed;
    std::size_t hashkey = _bucketID(key);
    ScopedLockType aLock( _lruMutex );

    TBucket& aBucket = _data[hashkey];

    int _return = 0;

    TValue* pValue = this->_getInBucket(key, aBucket);
    if (pValue == NULL) {
        pValue = &this->_getInsertInBucket(key, aBucket);
        notfound->manipulate(key, *pValue);
        //Todo: notify observers
    }
    if (pValue){
        //this->decMem(*pValue);
        _return = mnpfound->manipulate(key, *pValue);
        //this->incMem(*pValue);
    }
    else
        _return = EFailed;
    if (_return != EFailed){
        this->_linkToTopLRU(key, hashkey);
        this->_evict();
    }    
        
    return EFailed;
}

HLLLRUCache_DeclareTmpl
void HLLLRUCache_Clss::_evict() {
    if (BaseLRUClass::_evictThread.isRunning()) {
        BaseLRUClass::_evictEvent.set();
        return;
    }      
    if (BaseLRUClass::_isEvicting)
        return;
    size_t aSize = _size; // _dataHolder.size();
    if (aSize <= BaseLRUClass::_maxSize)
        return;
    BaseLRUClass::_isEvicting = true;
    size_t wishSize = BaseLRUClass::_maxSize - BaseLRUClass::_maxSize / 10000;
    TValue aValue;

    while (_size > wishSize) {
        if (_lruTail == NULL)
            return;
        TKey aKey = _lruTail->data.first;
        if (!this->_pop(aKey, aValue)) {
            BaseLRUClass::_isEvicting = false;
            return;
        }
        if (AbstractCache<TKey, TValue>::_observer) {
            AbstractCache<TKey, TValue>::_observer->evicted(aKey, aValue);
        }
    }
    BaseLRUClass::_isEvicting = false;

}

HLLLRUCache_DeclareTmpl
void HLLLRUCache_Clss::manipulate_all_readonly(data_manipulator* manipulator){
    for (size_t aIndex = 0; aIndex < _data.size() ; aIndex++){
        TBucket emptyBucket;
        
        TBucket& aBucket = _data[aIndex];
        TKey key;
        TValue value;
        listNode* aNode = aBucket.head;
        while (aNode!= NULL){
            {
                ScopedLockType aLock( _lruMutex );
                key = aNode->data.first;
                value = aNode->data.second;            
                aNode = aNode->next;
            }
            manipulator->manipulate( key, value );
        }
        
    }
    
}

}}


#endif	/* HLLLRUCACHE_H */

