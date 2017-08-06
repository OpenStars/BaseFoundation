/* 
 * File:   ARCLKCache.h
 * Author: trungthanh
 *
 * Created on April 10, 2014, 5:24 PM
 */

#ifndef UPCACHING_ARCLKCACHE_H
#define	UPCACHING_ARCLKCACHE_H



/*
 * arc cache based on pointer linked list
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
template <class _TKey, class _TValue, class _THash = boost::hash<_TKey> , class _MemSizeGetter = MemSizeGetter>
class ARCLKCache: public Up::Caching::AbstractCache<_TKey, _TValue, _MemSizeGetter>  {
#ifndef MAX
#define MAX(a, b) ( (a) > (b) ? (a) : (b) )
#define MIN(a, b) ( (a) < (b) ? (a) : (b) )
#endif
    
protected:
    typedef AbstractCache<_TKey, _TValue, _MemSizeGetter> BaseClass;
    typedef _TKey TKey;
    typedef _TValue TValue;
    typedef _THash THash;
    typedef typename AbstractCache< _TKey, _TValue >::data_manipulator data_manipulator;
    

    typedef std::pair<TKey, TValue > DataPair;
    
    enum TARCState{
      ENoneState = 0,
      EMRU=1,
      EMFU=2,
      EMRUG=3,
      EMFUG=4        
    };

    struct listNode{
        listNode():data(), next(NULL), arcNext(NULL), arcPrev(NULL) {}
        DataPair data;
        listNode* next;
        listNode* arcNext;
        listNode* arcPrev;
        unsigned char bstate;        
        
        void arcUnlink()
        {
            listNode* aNext = arcNext;
            listNode* aPrev = arcPrev;
            if (aNext)
                aNext->arcPrev = aPrev;
            if (aPrev)
                aPrev->arcNext = aNext;
            arcNext = arcPrev = NULL;
            //bstate = ENoneState;
        }
        
    };
    
    struct TARCList{
        TARCList(unsigned char state):size(0), head(NULL),tail(NULL), bstate(state){}
        
        size_t size;
        listNode* head;
        listNode* tail;
    private:
        unsigned char bstate;        

    public:
        void addNode(listNode* aNode)
        {
            if (aNode == NULL)
                return;
            if (aNode == head)
                return;
            aNode->arcUnlink();
            
            aNode->arcNext = head;
            if (head)
                head->arcPrev = aNode;
            head = aNode;
            if (tail == NULL)
                tail = aNode;
            aNode->bstate = bstate;
            size ++;
        }
        
        void removeNode(listNode* aNode)
        {
            if (aNode == NULL)
                return;
            if (aNode == head)
                head = aNode->arcNext;
            if (aNode == tail)
                tail = aNode->arcPrev;
            aNode->arcUnlink();
            size --;
        }
    };

    
    struct TBucket{
        listNode* head;
        TBucket():head(NULL){}
        ~TBucket(){
            clear();
        }

        bool isEmpty() const {
            return (head == NULL);
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
        
        listNode** findOrAdd(const TKey& aKey, bool &isNew)
        {
            listNode** aNode = find(aKey);
            if (aNode && (*aNode))
            {
                isNew = false;
                return (aNode);                
            }
            else {
                (*aNode) = new listNode();
                (*aNode)->data.first = aKey;
                isNew = true;

                return (aNode);
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
        
        
        listNode* remove(const TKey& aKey)
        {
            listNode** aNode = find(aKey);
            if (aNode && (*aNode) && ( (*aNode)->data.first == aKey))
            {
                listNode* removed = *aNode;
                *aNode = removed->next;
                //delete removed;
                return removed;
            }
            return NULL;            
        }
        
        listNode* remove(const TKey& aKey, TValue& oldValue)
        {
            listNode** aNode = find(aKey);
            if (aNode && (*aNode) && ( (*aNode)->data.first == aKey))
            {
                listNode* removed = *aNode;
                *aNode = removed->next;
                oldValue = removed->data.second;
                // removed;
                return removed;
            }
            return NULL;
        }
        
        
    };
    
    TARCList* getArcList(unsigned char bstate)
    {
        switch(bstate)
        {
            case EMRU:
                return &this->_mru;
            case EMFU:
                return &this->_mfu;
            case EMRUG:
                return &this->_mrug;
            case EMFUG:
                return &this->_mfug;
            
            default:
                return NULL;
        }        
        return NULL;
    }
    
    TARCList* getArcList(listNode* aNode)
    {
        if (aNode == NULL)
            return NULL;
        return getArcList(aNode->bstate);
    }
    
    typedef Poco::FastMutex MutexType;
    typedef MutexType::ScopedLock ScopedLockType;

    typedef std::vector <TBucket> DataHolder;

    
public:

    ARCLKCache(size_t arcSize, int tableSize, int lockSize = 1) 
    :BaseClass()
    ,_hf()
    , _data()//(tableSize + 1 , TBucket(0))
    , _tableSize(tableSize)
    , _psize(arcSize/4)
    ,_maxSize(arcSize*101/200)
    , _lockSize(lockSize)
    ,_mru(EMRU)
    ,_mfu(EMFU)
    ,_mrug(EMRUG)
    ,_mfug(EMFUG)
    
    {
        init();
    }

    virtual ~ARCLKCache() {
    }
protected:
    void init();
public:
    //////override from AbstractCache
    bool has(const TKey& key) const ;
    
    virtual int add(const TKey& key, const TValue& value) ;

    virtual int put(const TKey& key, const TValue& value) ;

    virtual int update(const TKey& key, const TValue& value) ;

    virtual int remove(const TKey& key) ;

    virtual size_t size()const {return this->_mru.size + _mfu.size + _mfug.size + _mrug.size; }
    
    virtual size_t maxSize()const {return _maxSize;}

    virtual void setMaxSize(size_t aSize) {_maxSize = aSize; }
    

    virtual TValue* get(const TKey& key) ; // return null if Caching not exist

    // get and remove the data
    virtual bool pop(const TKey& key, TValue& value);
        
//    virtual bool popTail(TKey& key, TValue& value);    
    
    // manipulate if exist
    virtual bool manipulateCache(const TKey& key, data_manipulator* manipulator) ;

    // manipulate
    virtual int manipulateCache(const TKey& key, data_manipulator* notfound, data_manipulator* mnpfound) ;    
    
    virtual void manipulate_all_readonly(data_manipulator* manipulator);

public:
    void insert(const DataPair& aPair) {
        this->put(aPair.first, aPair.second);
    }

    void erase(const TKey& key) {
        this->remove(key);
    }

    bool get(const TKey& key, TValue& outVal)  {
        ReadCommand cmd(key, outVal);

        ScopedLockType aLock ( _arcMutex );

        this->_arcLookupRead(key, &cmd);
        return cmd.executed;
    }

    TValue& operator[](const TKey& key) {
        ScopedLockType aLock ( _arcMutex );
        bool isNew;
        listNode* aNode = this->_arcLookup(key, isNew);
        if (aNode)
            return aNode->data.second;
        
    }

    void clear() {
    }

protected:

    bool _isEmpty(const TBucket& bucket) const {
        return (bucket.isEmpty() );
    }

    std::size_t _bucketID(const TKey& key) const {
        return (_hf(key) & _tableSize);
    }
    
        
    TBucket& _getBucket(const TKey& key) {
        return _data[ _bucketID(key) ];
    }

    void _evict();
    
    virtual void _evictNode(listNode* node){};
    virtual bool _fetchNode(listNode* node){return false;};
    virtual void _destroyNode(listNode* node){
        delete node;
    };
    
    class NodeCommand{
    public:
        virtual void excute(listNode*) = 0;
    };
    
    virtual void _arcBalance(size_t aSize)
    {
    /* First move objects from MRU/MFU to their respective ghost lists. */
       while (_mru.size + _mfu.size + aSize > _maxSize) {        
           if (_mru.size > _psize) {
               listNode* obj = _mru.tail;//__arc_state_lru(&cache->mru);
               this->_moveNode(obj, EMRUG);
           } else if (_mfu.size > 0) {
               listNode *obj = _mfu.tail;//__arc_state_lru(&cache->mfu);
               this->_moveNode(obj, EMFUG);
           } else {
               break;
           }
       }

       /* Then start removing objects from the ghost lists. */
       while (_mrug.size + _mfug.size > _maxSize) {        
           if (_mfug.size > _psize) {
               listNode* obj = _mfug.tail;
               this->_moveNode(obj, ENoneState);
               
           } else if (_mrug.size > 0) {
               listNode* obj = _mrug.tail;
               this->_moveNode(obj, ENoneState);               
           } else {
               break;
           }
       }    
    }
    
    
    listNode* _moveNode(listNode** node, TARCState state){
        TARCList* currentList = this->getArcList(*node);
        TARCList* targetList = this->getArcList(state);

        listNode* currentNode = *node;
        if (currentList)
        {
            currentList->removeNode(*node);
        }
        

        if (targetList == NULL) {
            /* The object is being removed from the cache, destroy it. */
            *node = (*node)->next;
            
            this->_destroyNode(currentNode);
            
            return NULL;
        } else {
            if (state == EMRUG || state == EMFUG) {
                /* The object is being moved to one of the ghost lists, evict
                 * the object from the cache. */
               _evictNode(currentNode);
            } else if (currentNode->bstate != EMRU && currentNode->bstate != EMFU) {
                /* The object is being moved from one of the ghost lists into
                 * the MRU or MFU list, fetch the object into the cache. */
                this->_arcBalance(1);
                if (this->_fetchNode(currentNode)) {
                    /* If the fetch fails, put the object back to the list
                     * it was in before. */
                    currentList = this->getArcList(*node);
                    currentList->addNode(currentNode);                    
                    return NULL;
                }
            }
            //else this->_arcBalance(0);

            currentNode->bstate = state;
            targetList->addNode(currentNode);
            return currentNode;
        }             
        
    } 
    
    listNode* _moveNode(listNode* node, TARCState state){
        TARCList* currentList = this->getArcList(node);
        TARCList* targetList = this->getArcList(state);

        if (currentList)
        {
            currentList->removeNode(node);
        }
        

        if (targetList == NULL) {
            /* The object is being removed from the cache, destroy it. */
            //*node = (*node)->next;
            TKey aKey = node->data.first;
            std::size_t hashkey = _bucketID(aKey);
            listNode* removed = _data[hashkey].remove(aKey);
            assert(removed == node);
            this->_destroyNode(node);
            
            return NULL;
        } else {
            if (state == EMRUG || state == EMFUG) {
                /* The object is being moved to one of the ghost lists, evict
                 * the object from the cache. */
               _evictNode(node);
            } else if (node->bstate != EMRU && node->bstate != EMFU) {
                /* The object is being moved from one of the ghost lists into
                 * the MRU or MFU list, fetch the object into the cache. */
                this->_arcBalance(1);
                if (this->_fetchNode(node)) {
                    /* If the fetch fails, put the object back to the list
                     * it was in before. */
                    currentList = this->getArcList(node);
                    currentList->addNode(node);                    
                    return NULL;
                }
            }
//            else
//                this->_arcBalance(1);

            node->bstate = state;
            targetList->addNode(node);
            return node;
        }

              
        
    }     
    
    listNode* _arcLookup(const TKey& key, bool& isNew
            , NodeCommand* cmd = NULL
            , NodeCommand* onNewCmd = NULL
            , NodeCommand* onOldCmd = NULL)
    {
        std::size_t hashkey = _bucketID(key);
        isNew = false;
        listNode** aNode = this->_data[hashkey].findOrAdd(key, isNew);
        if ( aNode == NULL || *aNode == NULL )
            return NULL;
        
        if (isNew){
            (*aNode)->bstate = EMRU;
            this->_mru.addNode(*aNode);        
            this->_arcBalance(0);
        } 
        else 
        {
            listNode* aResultNode = NULL;
            if ( (*aNode)->bstate == EMRU || (*aNode)->bstate == EMFU) {
                /* Object is already in the cache, move it to the head of the
                 * MFU list. */
                
                aResultNode = _moveNode( aNode, EMFU);

            } else if ((*aNode)->bstate == EMRUG) {
                _psize = MIN(_maxSize, _psize + MAX(_mfug.size / _mrug.size, 1));
                aResultNode = _moveNode(aNode, EMFU);
            } else if ((*aNode)->bstate == EMFUG) {
                _psize = MAX(0, _psize - MAX(_mrug.size / _mfug.size, 1));
                aResultNode = _moveNode( aNode, EMFU);
            } else {
                assert(0);
            }
            if (!aResultNode)
                return NULL;
            if (cmd)
                cmd->excute(aResultNode);
            if ( onOldCmd)
                onOldCmd->excute(aResultNode);
            return aResultNode;            
        }
        
        if (cmd)
            cmd->excute(*aNode);
        if (isNew && onNewCmd)
            onNewCmd->excute(*aNode);
        return (*aNode);
    }
    
    
    
    listNode* _arcLookupRead(const TKey& key, NodeCommand* cmd = NULL) const
    {
        ARCLKCache* pThis = const_cast <ARCLKCache* >(this);
        std::size_t hashkey = _bucketID(key);
        bool isNew = false;
        TBucket& aBucket = const_cast<TBucket&>(_data[hashkey]);
        listNode** aNode = aBucket.find(key);
        if (aNode && (*aNode))
        {
            
            if (cmd)
                cmd->excute(*aNode);
            if ( (*aNode)->bstate == EMRU || (*aNode)->bstate == EMFU) {
                /* Object is already in the cache, move it to the head of the
                 * MFU list. */
                return pThis->_moveNode( aNode, EMFU);
            } else if ((*aNode)->bstate == EMRUG) {
                pThis->_psize = MIN(_maxSize, _psize + MAX(_mfug.size / _mrug.size, 1));
                return pThis->_moveNode(aNode, EMFU);
            } else if ((*aNode)->bstate == EMFUG) {
                pThis->_psize = MAX(0, _psize - MAX(_mrug.size / _mfug.size, 1));
                return pThis->_moveNode( aNode, EMFU);
            } else {
                assert(0);
            }            
            return (*aNode);        
        }
        return NULL;
    }

    
    
    bool _arcLookupRemove(const TKey& key,NodeCommand* cmd = NULL)
    {
        std::size_t hashkey = _bucketID(key);
        bool isNew = false;
        listNode** aNode = this->_data[hashkey].find(key);
        if (aNode && (*aNode))
        {
            if (cmd)
                cmd->excute(*aNode);
            this->_moveNode(aNode, ENoneState);
            return true;
        }
        return false;        
    }
    
    class WriteCommand: public NodeCommand{
        const TKey& key;
        const TValue& value;
    public:
        bool executed;
    public: 
        WriteCommand(const TKey& k, const TValue& v)
                :key(k), value(v),executed(false)
                {
                }
        
        virtual void excute(listNode* node){
            if (node){
                node->data.second = value;
                executed = true;
            }
        }        
    };

    class ReadCommand: public NodeCommand{
        const TKey& key;
        TValue& value;
    public:
        bool executed;
    public: 
        ReadCommand(const TKey& k, TValue& v)
                :key(k), value(v),executed(false)
                {
                }
        
        virtual void excute(listNode* node){
            if (node){
                value = node->data.second;
                executed = true;
            }
        }        
    };

    class ReadPCommand: public NodeCommand{
        const TKey& key;
    public:
        TValue* value;
    public:
        bool executed;
    public: 
        ReadPCommand(const TKey& k)
                :key(k), value(NULL),executed(false)
                {
                }
        
        virtual void excute(listNode* node){
            if (node){
                value = &node->data.second;
                executed = true;
            }
        }        
    };
    
    class ManipulateCommand: public NodeCommand
    {
    
        data_manipulator* manipulator;
    public:
        bool excuted;
        bool result;
    public:
        ManipulateCommand(data_manipulator* mp):manipulator(mp),excuted(false),result(false){}
        
        virtual void excute(listNode* node) 
        {
            if (node&& manipulator)
            {
                result = manipulator->manipulate(node->data.first, node->data.second);
                excuted = true;
            }
        }
    };
    
protected:
    THash _hf;
    DataHolder _data;
    size_t _tableSize; // _tableSize is (2^n-1)
    std::size_t _psize;
    std::size_t _maxSize;
    size_t _lockSize;


    TARCList _mru;
    TARCList _mfu;
    TARCList _mrug;
    TARCList _mfug;
    
    
    mutable MutexType _arcMutex;
    
};
////////////////
#define ARCLKCache_DeclareTmpl template <class _TKey, class _TValue, class _THash , class _MemSizeGetter>
#define ARCLKCache_Clss ARCLKCache<_TKey, _TValue, _THash, _MemSizeGetter>


ARCLKCache_DeclareTmpl 
void ARCLKCache_Clss::init() {
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
    this->incMem(_data);
    this->_memSize += sizeof(*this);

}


ARCLKCache_DeclareTmpl 
bool ARCLKCache_Clss::has(const TKey& key) const {
    std::size_t hashkey = _bucketID(key);
    
    ScopedLockType aLock( _arcMutex );

    if (_isEmpty(_data[hashkey])) 
        return false;

    return this->_arcLookupRead(key) != NULL;
}



ARCLKCache_DeclareTmpl    
int ARCLKCache_Clss::add(const TKey& key, const TValue& value) {
    
    ScopedLockType aLock( _arcMutex );
    
    bool isNew;
    WriteCommand add(key, value);
    this->_arcLookup(key, isNew, NULL, &add);
    if (add.executed)
        return EAdded;
    return EFailed;
    
}

ARCLKCache_DeclareTmpl
int ARCLKCache_Clss::put(const TKey& key, const TValue& value) {
    ScopedLockType aLock( _arcMutex );
       
    bool isNew;
    WriteCommand add(key,value);
    WriteCommand update(key,value);
    this->_arcLookup(key, isNew, NULL, &add, &update);
    if (add.executed)
        return EAdded;
    else if (update.executed)
        return EOverwritten;
}

ARCLKCache_DeclareTmpl
int ARCLKCache_Clss::update(const TKey& key, const TValue& value) {
    std::size_t hashkey = _bucketID(key);
    ScopedLockType aLock( _arcMutex );


    TBucket& aBucket = _data[hashkey];
    WriteCommand cmd(key, value);
    this->_arcLookupRead(key, &cmd);
    if (!cmd.executed)
        return EFailed;
    return EOverwritten;
}


ARCLKCache_DeclareTmpl
int ARCLKCache_Clss::remove(const TKey& key) {
    ScopedLockType aLock( _arcMutex );

    return this->_arcLookupRemove(key);
    
    
}


ARCLKCache_DeclareTmpl
_TValue* ARCLKCache_Clss::get(const TKey& key) {

    ScopedLockType aLock( _arcMutex );
    ReadPCommand readp(key);
    this->_arcLookupRead(key, & readp);
    if (readp.executed){
        return readp.value;
    }
    return NULL;
}

ARCLKCache_DeclareTmpl
bool ARCLKCache_Clss::pop(const TKey& key, TValue& value){
    ScopedLockType aLock( _arcMutex );
    ReadCommand pop(key, value);
    this->_arcLookupRemove(key, &pop);
    return (pop.executed);        
}


ARCLKCache_DeclareTmpl
bool ARCLKCache_Clss::manipulateCache(const TKey& key, data_manipulator* manipulator) {
    if (!manipulator)
        return false;
    ScopedLockType aLock( _arcMutex );
    ManipulateCommand cmd(manipulator);
    this->_arcLookupRead(key, &cmd);
    if (cmd.excuted)
        return true;
}

ARCLKCache_DeclareTmpl
int ARCLKCache_Clss::manipulateCache(const TKey& key, 
        data_manipulator* notfound, data_manipulator* mnpfound) {
    if ( (!notfound ) || (!mnpfound) )
        return EFailed;
    ScopedLockType aLock( _arcMutex );
    ManipulateCommand miss(notfound);
    ManipulateCommand hit(mnpfound);
    bool isNew;
    this->_arcLookup(key, isNew, NULL, &miss, &hit);

}

ARCLKCache_DeclareTmpl
void ARCLKCache_Clss::_evict() {
    

}

ARCLKCache_DeclareTmpl
void ARCLKCache_Clss::manipulate_all_readonly(data_manipulator* manipulator){
    for (size_t aIndex = 0; aIndex < _data.size() ; aIndex++){
        TBucket emptyBucket;
        
        TBucket& aBucket = _data[aIndex];
        TKey key;
        TValue value;
        listNode* aNode = aBucket.head;
        while (aNode!= NULL){
            {
                ScopedLockType aLock( _arcMutex );
                key = aNode->data.first;
                value = aNode->data.second;            
                aNode = aNode->next;
            }
            manipulator->manipulate( key, value );
        }
        
    }
    
}

#endif	/* ARCLKCACHE_H */

