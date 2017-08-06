/* 
 * File:   MultiKVStorage.h
 * Author: trungthanh
 *
 * Created on March 1, 2010, 3:43 PM
 */

#ifndef _MULTIKVSTORAGE_H
#define	_MULTIKVSTORAGE_H

#include "AbstractKVStorage.h"
#include <Poco/Mutex.h>
#include <list>

namespace openstars { namespace storage{
    class MultiKVStorage:public AbstractKVStorage // support multiple backend kv Storage: MemCached, BDB, ...
    {
    public:
        MultiKVStorage():m_mutex(), _totalStorages(){}
        typedef Poco::FastMutex MutexType;
    private:
        // total Storage
        typedef std::map<std::string , AbstractKVStorage::Ptr> TStrorageMap;
        typedef std::list<AbstractKVStorage::Ptr> TStorageList;
        typedef std::map<std::string , TStorageList::iterator > TNameIndex;
        mutable MutexType m_mutex;

        TStrorageMap _totalStorages;
        TStorageList _writeStorages;
        TStorageList _readStorages;

        TNameIndex _writeStorageIndex;
        TNameIndex _readStorageIndex;
    public:
        virtual void addStorage(const std::string& aName , const AbstractKVStorage::Ptr& stg)
        {
            MutexType::ScopedLock aLock(m_mutex);
            _removeStorage(aName);
            _addStorage(aName , stg);
        }
        
        virtual AbstractKVStorage::Ptr getStorage(const std::string& aName){
            MutexType::ScopedLock aLock(m_mutex);
            TStrorageMap::iterator aIt = this->_totalStorages.find(aName);
            if (aIt != _totalStorages.end() )
                return aIt->second;
            return AbstractKVStorage::Ptr();
        }
        
        virtual void removeStorage(const std::string& aName)
        {
            MutexType::ScopedLock aLock(m_mutex);
            _removeStorage(aName);
        }
        
        virtual void enableStorage(const std::string& aName , bool enable, TOperations operations)
        {
             MutexType::ScopedLock aLock(m_mutex);
            _enableStorage(aName , enable , operations );
        }

        template <class TStringContainer>
        void getReadStorageNames(TStringContainer& outNames)
        {
            TNameIndex aNameIndex;
            {
                MutexType::ScopedLock aLock(m_mutex);
                aNameIndex = _readStorageIndex;
            }
            TNameIndex::iterator aIt = aNameIndex.begin();
            TNameIndex::iterator aEndIt = aNameIndex.end();
            for (; aIt != aEndIt; aIt++)
            {
                outNames.push_back(aIt->first);
            }
        }

        template <class TStringContainer>
        void getWriteStorageNames(TStringContainer& outNames)
        {
            TNameIndex aNameIndex;
            {
                MutexType::ScopedLock aLock(m_mutex);
                aNameIndex = _writeStorageIndex;
            }
            TNameIndex::iterator aIt = aNameIndex.begin();
            TNameIndex::iterator aEndIt = aNameIndex.end();
            for (; aIt != aEndIt; aIt++)
            {
                outNames.push_back(aIt->first);
            }
        }

        void flush();
    protected:
        virtual void _addStorage(const std::string& aName , const AbstractKVStorage::Ptr& stg);
        virtual void _removeStorage(const std::string& aName);
        virtual void _enableStorage(const std::string& aName , bool enable, TOperations operations);
    private:
        

    public:
        virtual bool isReadable() const {
                MutexType::ScopedLock aLock(m_mutex);
                return _readStorages.size() > 0;
            }

        virtual bool isWritable() const {
                MutexType::ScopedLock aLock(m_mutex);
                return _writeStorages.size() > 0;
            }
    private:

        void getReadStorage(TStorageList& _return) const {
            MutexType::ScopedLock aLock(m_mutex);
            _return = _readStorages;
        }

        void getWriteStorage(TStorageList& _return) const {
            MutexType::ScopedLock aLock(m_mutex);
            _return = _writeStorages;
        }


    public:

        /*
         * of date value of existing key, error if it is not existed
         */
        virtual int32_t update(const KType &key, const VType &data);
            
        /*
         * add new key-value pair, error if it is already existed
         */
        virtual int32_t add(const KType &key, const VType &data);        
  	
        virtual int32_t put(const KType &key, const VType &data);

    protected:

        // read operation
        virtual int32_t _get(const void* inKeyData, const int& keyLen, void* outData, const int& datalen) const ;

                
        virtual int32_t _get(VType &_return, const KType &key) const ;

        virtual int32_t _multiGet(KVMap &_return, const KList &keys) const ;

        virtual bool _has(void* aKeyData, const int& aKeyLen) const ;

        //write operations
        virtual int32_t _put(const void* inKeyData, const int& keyLen, const void* inData, const int& datalen) ;
		 // should be overridden
        virtual int32_t _remove(void* aKey, int aKeyLen) ;// Must be overriden
    private:

    };

} }
#endif	/* _MULTIKVSTORAGE_H */

