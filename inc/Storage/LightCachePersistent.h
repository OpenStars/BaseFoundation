/* 
 * File:   LightCachePersistent.h
 * Author: trungthanh
 *
 * Created on October 2, 2012, 9:58 AM
 * Reduce copy on flushing to key-value abstraction 
 * Use with ThriftObjectStorage
 */

#ifndef UP_STORAGE_CACHEPERSISTENT_H
#define	UP_STORAGE_CACHEPERSISTENT_H

#include "Storage/CachePersistentBase.h"
#include "Storage/EvictProcessors.h"

#include <boost/unordered_set.hpp>
#include <boost/interprocess/sync/interprocess_mutex.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>

#include <Poco/Event.h>
#include <Poco/Thread.h>
#include <Poco/Runnable.h>
#include <Poco/RunnableAdapter.h>
#include <Poco/Timer.h>
#include <Poco/Stopwatch.h>
#include <Poco/Notification.h>
#include <Poco/NotificationCenter.h>

#include <Caching/AbstractCache.h>
#include <Storage/ObjectStorage.h>




namespace openstars { namespace storage{



#define CachePersistent_Tmpl     template <class _TKey, class _TValue, class  _ThriftType, class _ObjectStorage >
#define CachePersistent_Clss CachePersistent<_TKey, _TValue, _ThriftType, _ObjectStorage>
    
template <class _TKey, class _TValue, class  _ThriftType, class _ObjectStorage >
class CachePersistent
        :public CachePersistentBase
        , public openstars::caching::CacheObserver<_TKey, _TValue>{
    public:
        typedef _TKey TKey;
        typedef _TValue TValue;
        typedef _ThriftType ThriftType;
        typedef _ObjectStorage TObjectStorage;
        typedef boost::interprocess::interprocess_mutex MutexType;
        typedef boost::interprocess::scoped_lock<MutexType> ScopedLockType;
        typedef CachePersistent<_TKey, _TValue, _ThriftType, _ObjectStorage> ThisClass;
        // learn this style from boss :D 
        class KeySet:  public MutexType {public: boost::unordered_set<TKey> keys;};
        
        typedef openstars::caching::AbstractCache<_TKey, _TValue> CacheType;
        typedef AbstractEvictedProcessor<_TKey, _TValue> EvictProcessorType;

    public:
        CachePersistent(CacheType* Caching, CacheType* secondCache, TObjectStorage* Storage);
        virtual ~CachePersistent(){
        }
        
        
    public:
        class data_visitor{
        public:
            virtual bool visit(const TKey& key, TValue& value) = 0;
            virtual data_visitor* clone() { return NULL ;}
        };
        
      
    public:
        
        /* 
         * Function: visit
         * Purpose: visit item in Caching, if it is not in Caching, get its data from
         * objectstorage then put it to Caching and visit again
         * this should be a little slow if item is not in Caching but it would not block
         * other threads.
         */
        void visit(const TKey& key, data_visitor* aVisistor);

        /* Function: visitCache
         * Purpose: visit item in Caching
         * return false if item is not in Caching
         */
        bool visitCache(const TKey& key, data_visitor* aVisistor);

         /* Function: visitCacheOrWarm
          * Purpose: visit item in Caching or warming Up the item
          * Flow: if (_enableWarmingUp==false) it call visitCache
          *         otherwise it visit Caching if it exist
          *         if item not existed in Caching, put the key to the WarmingKeySet
          * return false if item is not in Caching
          */
        bool visitCacheOrWarm(const TKey& key, data_visitor* aVisistor, bool visistAfterWarm = false);
        
        void put(const TKey& key, const TValue& value);
       
        bool get(const TKey& key, TValue& value);
        
        bool getCache(const TKey& key, TValue& value);
        
        bool getOrWarmCache(const TKey& key, TValue& value);
        
        bool remove(const TKey& key);
        
        bool removeCache(const TKey& key);

        bool hasCache(const TKey& key);
               
        void startSaving();
        
        void stopSaving();
        
        void startWarmingUp();// start warming thread
        
        void stopWarmingUp(); // stop warming thread
        
        void startDumping() {}; // not need right now
        
        size_t savingQueueSize();//number of dirty objects
        
        size_t warmingQueueSize();//number of objects being warming Up
        
        void clearWarmingQueue();
        
        void enableAsyncFlush(bool enable){ this->_asyncFlush = enable; }
        
    public:
        void setObserver(CachePersistentObserver* observer){_observer = observer; }
        
        void setEvictProcessor(Poco::SharedPtr< EvictProcessorType > aProcessor){
            this->_evictProcessor = aProcessor;
        }
        
	void setNumSavingThread(int numThread);
        
	void setNumWarmingThread(int numThread);
        
        //if dirty cache size greather than _smartSavingThreshold, it will auto startsaving, when it is empty, it will automatic stop saving
        void setSmartSaving(bool smart){_smartSaving = smart;}
        
        void setSmartSavingThreshold(size_t aThreshold) {_smartSavingThreshold = aThreshold;}
        
        /*
         * override from CacheObserver
         */
        virtual void added(const TKey& key, const TValue& value){};
        
        virtual void removed(const TKey& key, const TValue& value){};
        
        virtual void evicted(const TKey& key, const TValue& value)
        {
            if (this->_evictProcessor)
            {
                if (this->removeDirtyKey(key) ){
                    _evictProcessor->pushDirtyKeyValue(key,value, _enableAsyncFlush);
                }
            }
        }

        virtual void missed(const TKey& key)
        {
        };
        
        /*
         * evicting processor
         */
        virtual bool popEvictedDirty(TKey& key, TValue& value)
        {
            if (this->_evictProcessor)
            {
                return _evictProcessor->popEvictedDirty(key, value, this->_enableAsyncFlush);
            }
            return false;
        }
        
        bool popDirtyKeyValue(TKey& key, ThriftType& value){
            class ThriftVisitor:public data_visitor{
            public:
                ThriftVisitor(ThriftType& v):thriftvalue(v){}
                virtual bool visit(const TKey& key, TValue& value)
                {
                    value.assignTo(thriftvalue);
                    return false;
                }
                ThriftType& thriftvalue;                
            };

            if ( _cache->supportDirty() )
            {
                TValue value1;
                ThriftVisitor aVisitor(value);
                visit_manipulator manipulator(&aVisitor, false);
                return _cache->popHeadDirty(key, value1, &manipulator);                
            }            
            
            
            ThriftVisitor aVisitor(value);
            while (_enableSavingThread && (this->popDirtyKey(key ) ) ) 
            {
                //if (!this->getCache( key, value) ){
                if (!this->visitCache(key, &aVisitor)) {                    
                    return false; 
                } 
                else
                    return true;
            }
            return false;

        }
        
        bool popDirtyKeyValue(TKey& key, TValue& value)
        {
            if (popEvictedDirty(key, value) )
                return true;
            while (_enableSavingThread && (this->popDirtyKey(key ) ) ) 
            {
                if (!this->getCache( key, value) ){
                    
                    return false; 
                } 
                else
                    return true;
            }
            return false;
        }
        
    protected:
        inline void _waitForEnable(){
            while (!_enable){
                Poco::Thread::sleep(0);
            }
        }
        void saveObject(const TKey& key);
        void warmObject(const TKey& key);
        bool popDirtyKey(TKey& key);
        bool isDirtyKey(const TKey& key);
        bool removeDirtyKey(const TKey& key);
        bool popWarmingKey(TKey& key);
        void _savingThreadFunc();
        void _warmingThreadFunc();
    protected:
        Poco::RunnableAdapter < ThisClass > _savingRunner;
        Poco::RunnableAdapter < ThisClass > _warmingRunner;
        CacheType* _cache;
        CacheType* _secondCache; //
        TObjectStorage* _storage;
        
        KeySet _dirtyKeys;
        KeySet _dirtyKeysSaving;
        KeySet _warmingKeys;
        
        bool _enable;
        volatile bool _isDumping;

        /*
         * this option is set by developer to enable async flush, async flush is
         * enable only this option is true and _enableAsyncFlush is true
         */
        bool _asyncFlush; 
        
        /*this option is detect by system to enable async flush or not*/
        bool _enableAsyncFlush;
        
        volatile bool _enableWarmingUp;
        volatile bool _enableSavingThread;
        volatile bool _forceSavingStop; //set true if called stopSaving, false if called startSaving
        Poco::Event _changeEvent;
        Poco::Event _warmEvent;
        Poco::Thread* _savingThread;
	int _numSavingThread;
        Poco::Thread* _warmingThread;
	int _numWarmingThread;
        CachePersistentObserver* _observer;
        Poco::SharedPtr< EvictProcessorType > _evictProcessor;
        bool _smartSaving;
        size_t _smartSavingThreshold;
        Poco::Timer _smartSavingTimer;
        
    private:
        void smartSavingTimerFunc(Poco::Timer&)
        {
            if (!_forceSavingStop && ! _enableSavingThread)
                this->startSaving();
                //this->_enableSavingThread = true;
        }
    public:
        // utility classes
        class get_visitor: public data_visitor{
        public:
            get_visitor(TValue& aValue):_value(aValue),_got(false){}
        public:
            virtual bool visit(const TKey& key, TValue& value) {
                _value = value;
                _got = true;
                return false;
            }
        public:
            TValue& _value;
            bool _got;
            
        };
    
        class set_visistor: public data_visitor{
        public:
            set_visistor(const TValue& aValue):_value(aValue),_set(false){}
        public:
            virtual bool visit(const TKey& key, TValue& value) {
                value = _value;
                _set = true;
                return true;
            }
        public:
            const TValue& _value;
            bool _set;
            
        };
    
    private:
        class visit_manipulator: public  CacheType::data_manipulator{
        public:
            visit_manipulator( typename CachePersistent_Clss::data_visitor* aVisistor,
                    bool needCopy = false):_visitor(aVisistor), _visited(false), 
                            _changed(false), _needCopy(needCopy), copied(false){}
        public:
            data_visitor* _visitor;
            bool _visited;
            bool _changed;
            bool _needCopy;
            //Poco::SharedPtr<TValue> _copiedValue;
            ThriftType _copiedValue;
            bool copied;
        public:
            bool manipulate(const TKey& key, TValue& value) {
                _visited = true;
                if (_visitor)
                    _changed = _visitor->visit(key, value);
                if (_changed && _needCopy){
//                    _copiedValue = new TValue;
//                    *_copiedValue = value;
                    value.assignTo(_copiedValue);
                    copied = true;
                }
                return _changed;
            }

        };
            
};

CachePersistent_Tmpl
CachePersistent_Clss::CachePersistent(typename CachePersistent_Clss::CacheType* Caching, typename CachePersistent_Clss::CacheType* secondCache, _ObjectStorage* Storage)
:_savingRunner(*this, &CachePersistent_Clss::_savingThreadFunc )
,_warmingRunner(*this, &CachePersistent_Clss::_warmingThreadFunc )
,_cache(Caching)
,_secondCache(secondCache) //
,_storage(Storage)
,_dirtyKeys()
,_warmingKeys()
,_enable(true)
,_isDumping(false)
,_asyncFlush(true)
,_enableAsyncFlush(true)
,_enableWarmingUp(true)
,_enableSavingThread(true)
,_forceSavingStop(false)
,_changeEvent()
,_warmEvent()
,_savingThread(new Poco::Thread[1] )
,_numSavingThread(1)
,_warmingThread(new Poco::Thread[1])
,_numWarmingThread(1)
,_observer(NULL)
,_evictProcessor()
,_smartSaving(false)
,_smartSavingThreshold(20000)
,_smartSavingTimer(60000)
{
    _enable = true;
    this->startWarmingUp();
    this->startSaving();
    if(_cache)
        _cache->setObserver(this);
}

CachePersistent_Tmpl
void CachePersistent_Clss::visit(const _TKey& key, data_visitor* aVisistor){
    Poco::Stopwatch aWatch;
    aWatch.start();
    visit_manipulator manipulator(aVisistor, !this->_asyncFlush);
    _waitForEnable();
    CacheType* pCache = _cache;
    if (this->_isDumping && _secondCache != NULL)
        pCache = _secondCache;
    
    if (pCache)
        pCache->manipulateCache(key, &manipulator);
    else
        return;
    if (!manipulator._visited){
        TValue value;
        //lay cache da bi evicted tu lan truoc 
        if (this->_evictProcessor && _evictProcessor->tryPopEvicted(key, value))
        {
            // load value
            pCache->add(key, value); // to make sure it is not overwrite hot object (may be warmed by another thread

            // visit again
            pCache->manipulateCache(key, &manipulator);
                
            aWatch.stop();
            if (_observer)
                _observer->hitCache(aWatch.elapsed() , manipulator._changed );
            saveObject(key); // add back to dirty 
            
        } // read from persistent storage
        else{        
        
            if (_observer)
                _observer->missedCache(aWatch.elapsed() , false);
            aWatch.start();
            if (_storage)
                _storage->get(key, value);
            aWatch.stop();
            if (_observer)
                _observer->hitPersistent(aWatch.elapsed() , false);
            // load value
            pCache->add(key, value); // to make sure it is not overwrite hot object (may be warmed by another thread

            // visit again
            pCache->manipulateCache(key, &manipulator);
        }
    } else {
        aWatch.stop();
        if (_observer)
            _observer->hitCache(aWatch.elapsed() , manipulator._changed );
    }
    
    if (manipulator._changed ){
        if (this->_asyncFlush && _enableAsyncFlush)
            saveObject(key);
        else {
            Poco::Stopwatch aWatch;
            aWatch.start();

            if (this->_storage && manipulator.copied)
            {
                _storage->put(key, manipulator._copiedValue);
            }
            else 
                return; 
            aWatch.stop();
            if (_observer)
                _observer->hitPersistent( aWatch.elapsed(), true);
            
        }
    }
    
}

CachePersistent_Tmpl
bool CachePersistent_Clss::visitCache(const _TKey& key, data_visitor* aVisistor){
   
    visit_manipulator manipulator(aVisistor);
    _waitForEnable();
    CacheType* pCache = _cache;
    if (this->_isDumping && _secondCache != NULL)
        pCache = _secondCache;
    Poco::Stopwatch aWatch;
    aWatch.start();
    
    if (pCache)
        pCache->manipulateCache(key, &manipulator);
    else
        return false;
    aWatch.stop();
    if (!manipulator._visited){
        if (_observer)
            _observer->missedCache(aWatch.elapsed() , false);
        return false;
    } 
    else {
        //aWatch.stop();
        if (_observer)
            _observer->hitCache(aWatch.elapsed() , manipulator._changed );
    }
    
    if (manipulator._changed ){
//        if (_observer)
//            _observer->hitCache(aWatch.elapsed() , manipulator._changed );
        
        saveObject(key);
    }
    return true;
    
}

CachePersistent_Tmpl
bool CachePersistent_Clss::visitCacheOrWarm(const TKey& key, data_visitor* aVisistor, bool visistAfterWarm ){
    if ( !visitCache(key, aVisistor) ) {
        if ( _enableWarmingUp )
            warmObject(key);
        return false;
    }
    return true;
}

CachePersistent_Tmpl
void CachePersistent_Clss::saveObject(const _TKey& key)
{
    if (_smartSaving && !this->_enableSavingThread && !this->_forceSavingStop)
    {
        size_t currentDirty = this->savingQueueSize();
        if (currentDirty > this->_smartSavingThreshold)
            this->startSaving();
    }
    
    if ( _cache->supportDirty() )
    {
        _changeEvent.set();
        return;
    }
    {
	ScopedLockType aLock(this->_dirtyKeysSaving);
	if (_dirtyKeysSaving.keys.find(key ) != _dirtyKeysSaving.keys.end() )
        {
            _changeEvent.set();
	    return; // khong can insert		
        }
    }
    
    {
	ScopedLockType aLock(this->_dirtyKeys);
	_dirtyKeys.keys.insert(key);
	_changeEvent.set();
    }
    
}

CachePersistent_Tmpl
void CachePersistent_Clss::warmObject(const _TKey& key){
    ScopedLockType aLock(this->_warmingKeys);
    _warmingKeys.keys.insert(key);
    this->_warmEvent.set();
}

CachePersistent_Tmpl
void CachePersistent_Clss::setNumSavingThread(int numThread)
{
    if (numThread <=0  || numThread == this->_numSavingThread)
	return;
    bool running = _enableSavingThread && (_savingThread != NULL) && (_savingThread->isRunning() );

    if (running)
    {
	this->stopSaving();
    }
    
    delete[] this->_savingThread;
    
    _numSavingThread = numThread;
    
    _savingThread = new Poco::Thread[numThread];
    
    if (running)
    {
	this->startSaving();
    }
}

CachePersistent_Tmpl
void CachePersistent_Clss::setNumWarmingThread(int numThread)
{
    if (numThread <=0  || numThread == this->_numWarmingThread)
	return;
    bool running = _enableWarmingUp&& (_warmingThread != NULL) && (_warmingThread->isRunning() );

    if (running)
    {
	this->stopWarmingUp();
    }
    
    delete[] this->_warmingThread;
    
    _warmingThread = new Poco::Thread[numThread];
    _numWarmingThread = numThread;
    
    if (running)
    {
	this->startWarmingUp();
    }
}


CachePersistent_Tmpl
void CachePersistent_Clss::_savingThreadFunc(){
    cout<<" saving thread func "<<endl;
    
    TKey key;
    cout<<"_enableSavingThread:"<<_enableSavingThread<<endl;
    while (this->_enableSavingThread ){

        ThriftType value;
        while (_enableSavingThread && (this->popDirtyKeyValue(key , value ) ) ) 
        {
            Poco::Stopwatch aWatch;
            aWatch.start();
            if (this->_storage){
                _storage->put(key, value);
            }
            value = ThriftType();
            aWatch.stop();
            if (_observer)
                _observer->hitPersistent( aWatch.elapsed(), true);
        }
        
        if (_enableSavingThread && _smartSaving)
        {
            _enableSavingThread = false; // auto stop saving
            if (!_forceSavingStop)
            {
                //start timer
                try {
                    this->_smartSavingTimer.start(Poco::TimerCallback< CachePersistent >(*this, &CachePersistent::smartSavingTimerFunc ));
                } 
                catch (...)
                {
                    
                }
            }
            break;
        }
        if (_enableSavingThread)
            this->_changeEvent.wait();

    }
    cout <<" stop saving thread "<<endl;
}

CachePersistent_Tmpl
void CachePersistent_Clss::_warmingThreadFunc(){
    cout<<" warming thread func "<<endl;
    
    while (this->_enableWarmingUp ){
        //this->_changeEvent.wait();
        
        if (!_enableWarmingUp)
            return;
        TKey key;
        while (_enableWarmingUp && this->popWarmingKey(key ) ) {
            TValue value;
            if (this->getCache( key, value) )
                continue; //data warmed
            
            Poco::Stopwatch aWatch;
            aWatch.start();
            
            if (this->_storage)
                _storage->get(key, value);
            else continue;
            aWatch.stop();
            if (_observer)
                _observer->hitPersistent(aWatch.elapsed() , false);
            _cache->add(key, value);
        }
        this->_warmEvent.wait();
        
    }    
}

CachePersistent_Tmpl
bool CachePersistent_Clss::popDirtyKey(_TKey& key){
    ScopedLockType aLock(this->_dirtyKeysSaving);
    
    if (_dirtyKeysSaving.keys.size() == 0 && _dirtyKeys.keys.size() > 0)
    {
	ScopedLockType aLock(this->_dirtyKeys); //careful dead lock
	_dirtyKeys.keys.swap(_dirtyKeysSaving.keys);
    }

    if (_dirtyKeysSaving.keys.size() > 0){
        key = *_dirtyKeysSaving.keys.begin();
        _dirtyKeysSaving.keys.erase(key);
        return true;
    }

    return false;
}

CachePersistent_Tmpl
bool CachePersistent_Clss::isDirtyKey(const _TKey& key){
    ScopedLockType aLock(this->_dirtyKeysSaving);
    
    if (_dirtyKeysSaving.keys.size() == 0 && _dirtyKeys.keys.size() > 0)
    {
	ScopedLockType aLock(this->_dirtyKeys); //careful dead lock
	_dirtyKeys.keys.swap(_dirtyKeysSaving.keys);
    }

    if (_dirtyKeysSaving.keys.size() > 0){
        if (_dirtyKeysSaving.keys.find(key) != _dirtyKeysSaving.keys.end())
            return true;
    }

    return false;
}

CachePersistent_Tmpl
bool CachePersistent_Clss::removeDirtyKey(const _TKey& key){
    bool removed = false;
    if (_dirtyKeysSaving.keys.size() > 0)
    {
        ScopedLockType aLock(this->_dirtyKeysSaving);
        {
            removed = _dirtyKeysSaving.keys.erase(key) > 0;
        }
    }    
    if ( (!removed ) && (_dirtyKeys.keys.size() > 0) )
    {
	ScopedLockType aLock(this->_dirtyKeys); //careful dead lock
	removed = _dirtyKeys.keys.erase(key) > 0;
    }

    return removed;
}

CachePersistent_Tmpl
bool CachePersistent_Clss::popWarmingKey(_TKey& key){
    ScopedLockType aLock(this->_warmingKeys);
    if (_warmingKeys.keys.size() > 0){
        key = *_warmingKeys.keys.begin();
        _warmingKeys.keys.erase(key);
        return true;
    }
    return false;
    
}

CachePersistent_Tmpl
void CachePersistent_Clss::put(const TKey& key, const TValue& value){
    if (this->_asyncFlush){
        _cache->putAndMarkDirty(key, value);
        saveObject(key);
    } else {
        _cache->put(key, value);
        if (this->_storage)
            _storage->put(key, value);
    }
}

CachePersistent_Tmpl
bool CachePersistent_Clss::get(const TKey& key, TValue& value){
    get_visitor aVisitor(value);
    this->visit(key, &aVisitor);
    return aVisitor._got;
}

CachePersistent_Tmpl
bool CachePersistent_Clss::getCache(const TKey& key, TValue& value){
    get_visitor aVisitor(value);
    this->visitCache(key, &aVisitor);
    return aVisitor._got;    
}

CachePersistent_Tmpl
bool CachePersistent_Clss::getOrWarmCache(const TKey& key, TValue& value){
    get_visitor aVisitor(value);
    this->visitCacheOrWarm(key, &aVisitor, false);
    return aVisitor._got;    
}

CachePersistent_Tmpl
bool CachePersistent_Clss::remove(const TKey& key){
    if (_storage)
        _storage->remove(key);
    return _cache->remove(key);
}

CachePersistent_Tmpl
bool CachePersistent_Clss::removeCache(const TKey& key){
    return _cache->remove(key);    
}

CachePersistent_Tmpl
bool CachePersistent_Clss::hasCache(const TKey& key){
    return _cache->has(key);
}

CachePersistent_Tmpl
void CachePersistent_Clss::startSaving(){
   
    _forceSavingStop = false;
    if ( (_savingThread != NULL) && (_savingThread->isRunning() ) )
	return;
    this->_enableSavingThread = true;
    for (int aIndex = 0; aIndex < this->_numSavingThread ; aIndex ++){
	_changeEvent.set();
        if (_savingThread[aIndex].isRunning())
	    continue;
	_savingThread[aIndex].start(this->_savingRunner);
	_changeEvent.set();
    }
    
    
}

CachePersistent_Tmpl
void CachePersistent_Clss::stopSaving(){
 
    _forceSavingStop = true;
    cout<<"stopSaving begin"<<endl;
    _enableSavingThread = false;
    for (int aIndex = 0; aIndex < this->_numSavingThread ; aIndex ++)
    {
	_changeEvent.set();
    }
    
    for (int aIndex = 0; aIndex < this->_numSavingThread ; aIndex ++)
    {
	if (_savingThread[aIndex].isRunning())
	{	
	    _changeEvent.set();
	    while (!_savingThread[aIndex].tryJoin(1000) )
	    {
		_enableSavingThread = false;
		_changeEvent.set();
	    }
	}
    }
    cout<<"stopSaving ok"<<endl;
    
}

CachePersistent_Tmpl
void CachePersistent_Clss::startWarmingUp(){

    if ( (_warmingThread != NULL) && (_warmingThread->isRunning() ) )
	return;
    this->_enableWarmingUp = true;
    for (int aIndex = 0; aIndex < this->_numWarmingThread ; aIndex ++){
	if (_warmingThread[aIndex].isRunning())
	    continue;
	_warmingThread[aIndex].start(this->_warmingRunner);
	_warmEvent.set();
    }
    
}

CachePersistent_Tmpl
void CachePersistent_Clss::stopWarmingUp(){

    _enableWarmingUp = false;
    
    for (int aIndex = 0; aIndex < this->_numWarmingThread ; aIndex ++)
    {
	_warmEvent.set();
    }
    
    for (int aIndex = 0; aIndex < this->_numWarmingThread ; aIndex ++)
    {
	if (_warmingThread[aIndex].isRunning())
	{	
	    _warmEvent.set();
	    while (!_warmingThread[aIndex].tryJoin(1000) )
	    {
		_enableWarmingUp = false;
		_warmEvent.set();
	    }
	}
    }
    
} 

CachePersistent_Tmpl
size_t CachePersistent_Clss::savingQueueSize(){
    if (_cache->supportDirty() )
        return _cache -> dirtySize();
    size_t aSize = _dirtyKeys.keys.size() + _dirtyKeysSaving.keys.size();
    if (this->_evictProcessor)
        aSize += this->_evictProcessor->size();
    return aSize;
}

CachePersistent_Tmpl
size_t CachePersistent_Clss::warmingQueueSize(){
    ScopedLockType aLock(this->_warmingKeys);
    return _warmingKeys.keys.size();
}

CachePersistent_Tmpl
void CachePersistent_Clss::clearWarmingQueue(){
    ScopedLockType aLock(this->_warmingKeys);
    return _warmingKeys.keys.clear();
}


} }

#endif	/* CACHEPERSISTENT_H */

