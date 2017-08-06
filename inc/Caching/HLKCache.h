/* 
 * File:   HLKCache.h
 * Author: trungthanh
 *
 * Created on March 19, 2014, 9:40 AM
 */

#ifndef UPCACHINGH_LKCACHE_H
#define	UPCACHINGH_LKCACHE_H

/*
 * Hash Key based caching
 */

#include <Caching/AbstractCache.h>

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
 * HashFlatCache
 * cac phan tu nam trong cac bucket cua bang bam. moi bucket la 1 sorted array 
 * Fix hash table size 
 * Locking: bucket based, spinlock 
 */
template <class _TKey, class _TValue, class _THash = boost::hash<_TKey> , class _MemSizeGetter = MemSizeGetter>
class HLKCache: public AbstractCache<_TKey, _TValue, _MemSizeGetter>  {
    
protected:
    typedef AbstractCache<_TKey, _TValue, _MemSizeGetter> BaseClass;
    typedef _TKey TKey;
    typedef _TValue TValue;
    typedef _THash THash;
    typedef typename AbstractCache< _TKey, _TValue >::data_manipulator data_manipulator;
    
    typedef std::pair<TKey, TValue> DataPair;
    struct listNode{
        listNode():data(), next(NULL) {}
        DataPair data;
        listNode* next;
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
            while( (*aNode) && ((*aNode)->data.first != aKey) )
                aNode = &(*aNode)->next;
            return aNode;
        }

        listNode** find(const TKey& aKey, listNode*** parent){
            listNode** aNode = &head;
            *parent = NULL;
            while ( (*aNode) && (*aNode)->data.first != aKey) 
            {
                *parent = aNode;
                aNode = &(*aNode)->next;
            }
            return aNode;
        }
        
        bool bringToTop(listNode** aNode, listNode** aParentNode)
        {
            
            if (aNode && (*aNode) && aParentNode && (*aParentNode) )
            {
                listNode* aCurrent = *aNode;
                listNode* aParent = *aParentNode;
                aParent->next = aCurrent->next;
                aCurrent->next = head;
                head = aCurrent;
                return true;
            }    
            return false;
        }
        
        bool toTop(const int& aKey)
        {
            listNode** aNode;
            listNode** aParentNode;
            aNode = find(aKey, &aParentNode);
            return bringToTop(aNode, aParentNode);
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
            listNode** parent;
            listNode** aNode = find(aPair.first, &parent);
            bool result = false;
            if (aNode && (*aNode)) 
            {
                (*aNode)->data.second = aPair.second;                
            }
            else {
                (*aNode) = new listNode();
                (*aNode)->data = aPair;
                return true;
            }
            /* bring it to top*/
            bringToTop(aNode, parent);
            return result;
        }
        
        bool updateData(const DataPair& aPair)
        {
            listNode** parent;
            listNode** aNode = find(aPair.first, &parent);
            if (aNode && (*aNode))
            {
                (*aNode)->data.second = aPair.second;
                bringToTop(aNode, parent);
                return true;
            }
            return false;            
        }
        
        /*
         * Neu co pair ung voi key roi thi return, chua co thi tao moi va return.
         */
        DataPair& getOrAddNewPair(const TKey& aKey, bool &isNew)
        {
            listNode** parent;
            listNode** aNode = find(aKey , &parent);
            if (aNode && (*aNode))
            {
                isNew = false;
                DataPair& aResult = (*aNode)->data;
                this->bringToTop(aNode, parent);
                return aResult;                
            }
            else {
                (*aNode) = new listNode();
                (*aNode)->data.first = aKey;
                isNew = true;
                DataPair& aResult = (*aNode)->data;
                this->bringToTop(aNode, parent);
                return aResult;                
            }
        }
        
        bool getValue(const TKey& aKey, TValue& outValue) const
        {
            listNode** parent;
            /*const listNodePtrC* */
            TBucket& aThis = const_cast<TBucket&> (*this);
            listNode** aNode = aThis.find(aKey, &parent);
            if (aNode && (*aNode) && ( (*aNode)->data.first == aKey))
            {
                outValue = (*aNode)->data.second;
                aThis.bringToTop(aNode, parent);
                return true;
            }
            return false;
            
        }
        
        TValue* getValuePtr(const TKey& aKey)
        {
            listNode** parent;
            listNode** aNode = find(aKey, &parent);
            if (aNode && (*aNode) && ( (*aNode)->data.first == aKey))
            {
                TValue* aResult = &(*aNode)->data.second;
                this->bringToTop(aNode, parent);
                return aResult;
                
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
    //typedef std::vector< DataPair > TBucket;
//    typedef typename TBucket::iterator BIterator;
//    typedef typename TBucket::const_iterator BConstIterator; // bucket iterator
    
//    typedef Poco::FastMutex MutexType;
    typedef Up::Caching::SpinLock MutexType;
    typedef MutexType::ScopedLock ScopedLockType;

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

    HLKCache(int tableSize, int lockSize = 1) : _hf()
    , _data()//(tableSize + 1 , TBucket(0))
    , _tableSize(tableSize)
    , _size(0)
    , _lockSize(lockSize){
        init();
    }

    virtual ~HLKCache() {
        delete [] _mutexs;
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

    virtual size_t maxSize()const {return size() ; };

    virtual void setMaxSize(size_t aSize){};

    virtual TValue* get(const TKey& key) ; // return null if Caching not exist

    // get and remove the data
    virtual bool pop(const TKey& key, TValue& value);

    // manipulate if exist
    virtual bool manipulateCache(const TKey& key, data_manipulator* manipulator) ;

    // manipulate
    virtual int manipulateCache(const TKey& key, data_manipulator* notfound, data_manipulator* mnpfound) ;    
    
    virtual void manipulate_all_readonly(data_manipulator* manipulator);

public:
    void insert(const DataPair& aPair) {
        std::size_t hashkey = _bucketID(aPair.first);
        ScopedLockType aLock ( _mutexByBucketID(hashkey) );
        _insertToBucket(aPair, _data[ hashkey ]);
    }

    void erase(const TKey& key) {
        std::size_t hashkey = _bucketID(key);
        ScopedLockType aLock ( _mutexByBucketID(hashkey) );
        if (_isEmpty(_data[hashkey])) 
            return;
        _removeFromBucket(key, _data[hashkey]);
    }

    bool get(const TKey& key, TValue& outVal)  {
        std::size_t hashkey = _bucketID(key);
        ScopedLockType aLock ( _mutexByBucketID(hashkey) );
        
        if (_isEmpty(_data[hashkey])) 
            return false;
        return _getValInBucket(outVal, key, _data[hashkey]);
    }

    TValue& operator[](const TKey& key) {
        std::size_t hashkey = _bucketID(key);
        ScopedLockType aLock ( _mutexByBucketID(hashkey) );
        
        return this->_getInsertInBucket(key, _data[hashkey] );
    }

    void clear() {
        for (size_t aIndex = 0; aIndex < _data.size() ; aIndex++){
            TBucket emptyBucket;
            ScopedLockType aLock( this->_mutexByBucketID(aIndex) );
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
    
    MutexType& _mutexByBucketID(const size_t aHash)const{
        return this->_mutexs[ aHash & this->_lockSize ];
    }
    
    MutexType& _mutexByKey(const TKey& key)const{
        return _mutexByBucketID( _bucketID(key) );
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
            _size++;
        return true;
    }

    bool _updateToBucket(const DataPair& aPair, TBucket& bucket) {
        return bucket.updateData(aPair);
    }
    
    // get value reference of a key, if it is not existed , insert a new item and return

    TValue& _getInsertInBucket(const TKey& key, TBucket& bucket) {
        bool isNew = false;
        TValue& aValue = bucket.getOrAddNewPair(key, isNew).second;
        if (isNew)
            _size++;
        return aValue;
    }

    TValue* _getInBucket(const TKey& key, TBucket& bucket) {
        return bucket.getValuePtr(key);
        return NULL;
    }
    
    
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
            this->decMem(key);
            this->decMem(outValue);
            return true;
        }
        return false;
    }
    
protected:
    THash _hf;
    DataHolder _data;
    size_t _tableSize; // _tableSize is (2^n-1)
    std::size_t _size;
    size_t _lockSize;
    //std::vector< MutexType > _mutexs;
    MutexType*  _mutexs;
};
////////////////
#define HLKCache_DeclareTmpl template <class _TKey, class _TValue, class _THash , class _MemSizeGetter>
#define HLKCache_Clss HLKCache<_TKey, _TValue, _THash, _MemSizeGetter>

HLKCache_DeclareTmpl 
void HLKCache_Clss::init() {
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
    _mutexs = new MutexType[aSize+1];
    //_mutexs.resize( aSize + 1);
    _lockSize = aSize - 1;
    
    // calculate initial estimated memory size
    this->_memSize += sizeof(_mutexs) + (aSize+1)* sizeof(MutexType); //
    this->_memSize += this->_sizeGetter(_data);
    this->_memSize += sizeof(*this);
}


HLKCache_DeclareTmpl 
bool HLKCache_Clss::has(const TKey& key) const {
    std::size_t hashkey = _bucketID(key);
    
    ScopedLockType aLock( _mutexByBucketID(hashkey) );

    if (_isEmpty(_data[hashkey])) 
        return false;

    return _hasInBucket(key, _data[hashkey]);
}

HLKCache_DeclareTmpl    
int HLKCache_Clss::add(const TKey& key, const TValue& value) {
    std::size_t hashkey = _bucketID(key);
    
    ScopedLockType aLock( _mutexByBucketID(hashkey) );
    
    TBucket& aBucket = _data[hashkey];
    
    if (_hasInBucket(key, aBucket ) )
        return EFailed;
    
    this->_insertToBucket( std::make_pair(key, value) , aBucket );
    
    return EAdded;
    
}

HLKCache_DeclareTmpl
int HLKCache_Clss::put(const TKey& key, const TValue& value) {
    std::size_t hashkey = _bucketID(key);
    ScopedLockType aLock( _mutexByBucketID(hashkey) );

    TBucket& aBucket = _data[hashkey];
    
    if (this->_insertToBucket( std::make_pair(key, value) , aBucket ) )
        return EAdded;
    
    return EOverwritten;
    
}

HLKCache_DeclareTmpl
int HLKCache_Clss::update(const TKey& key, const TValue& value) {
    std::size_t hashkey = _bucketID(key);
    ScopedLockType aLock( _mutexByBucketID(hashkey) );

    TBucket& aBucket = _data[hashkey];
    if (!this->_updateToBucket( std::make_pair(key , value) , aBucket ) )
        return EFailed;
    
    return EOverwritten;
}

HLKCache_DeclareTmpl
int HLKCache_Clss::add_or_update(const TKey& key, const TValue& value) 
{
    return put(key, value);
}

HLKCache_DeclareTmpl
int HLKCache_Clss::remove(const TKey& key) {
    std::size_t hashkey = _bucketID(key);
    ScopedLockType aLock( _mutexByBucketID(hashkey) );

    TBucket& aBucket = _data[hashkey];
    
    if (_isEmpty(aBucket)) 
        return EFailed;
    
    if (_removeFromBucket(key, aBucket) )
        return ERemoved;
    
    return EFailed;
}


HLKCache_DeclareTmpl
_TValue* HLKCache_Clss::get(const TKey& key) {
    std::size_t hashkey = _bucketID(key);
    ScopedLockType aLock( _mutexByBucketID(hashkey) );

    TBucket& aBucket = _data[hashkey];
    _TValue* result = this->_getInBucket(key, aBucket);
    if (result == NULL && BaseClass::_observer != NULL){
        BaseClass::_observer->missed(key);
    }
    return result;
}

HLKCache_DeclareTmpl
bool HLKCache_Clss::pop(const TKey& key, TValue& value){
    std::size_t hashkey = _bucketID(key);
    ScopedLockType aLock( _mutexByBucketID(hashkey) );

    TBucket& aBucket = _data[hashkey];
    return this->_removeFromBucket(key, value, aBucket);
}

HLKCache_DeclareTmpl
bool HLKCache_Clss::manipulateCache(const TKey& key, data_manipulator* manipulator) {
    if (!manipulator)
        return false;
    std::size_t hashkey = _bucketID(key);
    ScopedLockType aLock( _mutexByBucketID(hashkey) );

    TBucket& aBucket = _data[hashkey];
    TValue* pValue = this->_getInBucket(key, aBucket);
    if (pValue){
        
        this->decMem(*pValue);
        
        bool result = manipulator->manipulate(key, *pValue);
        
        this->incMem(*pValue);
        
        return result;
    }
    return false;    
}

HLKCache_DeclareTmpl
int HLKCache_Clss::manipulateCache(const TKey& key, data_manipulator* notfound, data_manipulator* mnpfound) {
    if ( (!notfound ) || (!mnpfound) )
        return EFailed;
    std::size_t hashkey = _bucketID(key);
    ScopedLockType aLock( _mutexByBucketID(hashkey) );

    TBucket& aBucket = _data[hashkey];
    
    TValue* pValue = this->_getInBucket(key, aBucket);
    if (pValue == NULL){
        pValue = &this->_getInsertInBucket(key, aBucket);
        notfound->manipulate(key, *pValue);
        //Todo: notify observers
    }
    if (pValue){
        this->decMem(*pValue);
        mnpfound->manipulate(key, *pValue);
        this->incMem(*pValue);
        return EManipulated;
    }
    return EFailed;
}

HLKCache_DeclareTmpl
void HLKCache_Clss::manipulate_all_readonly(data_manipulator* manipulator){
    for (size_t aIndex = 0; aIndex < _data.size() ; aIndex++){
        TBucket emptyBucket;
        
        TBucket& aBucket = _data[aIndex];
//        size_t aSize = 0;
//        {
//            ScopedLockType aLock( this->_mutexByBucketID(aIndex) );
//            aSize = _data[aIndex].size();
//        }
        TKey key;
        TValue value;
        listNode* aNode = aBucket.head;
        while (aNode!= NULL){
             ScopedLockType aLock( this->_mutexByBucketID(aIndex) );
            key = aNode->data.first;
            value = aNode->data.second;            
            aNode = aNode->next;
            manipulator->manipulate( key, value );
        }
        
//        for (int bucketIndex = 0 ; bucketIndex < aSize; bucketIndex++ )
//        {
//            {
//                ScopedLockType aLock( this->_mutexByBucketID(aIndex) );
//                aSize = _data[aIndex].size();
//                if (bucketIndex >= aSize)
//                    break;
//                key = aBucket[bucketIndex].first;
//                value = aBucket[bucketIndex].second;
//            }
//            manipulator->manipulate( key, value );
//        }
    }
    
}

} }

#endif	/* HLKCACHE_H */

