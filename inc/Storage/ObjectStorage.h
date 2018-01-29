/* 
 * File:   ObjectStorage.h
 * Author: trungthanh
 *
 * Created on February 16, 2012, 2:22 PM
 */

#ifndef ZBACKENDSTORAGE_H
#define	ZBACKENDSTORAGE_H

#include <Poco/SharedPtr.h>
#include <Storage/AbstractKVStorage.h>
#include <assert.h>
#include <iostream>

using namespace std;
/*
 * Backend Storage is used to persistent object to key-value Storage.
 * 
 */
namespace openstars { namespace storage{
    
template <class _KeyType, class _ValueType>
class NULLObjectStorage{
public:
    typedef _ValueType MObj;
    typedef _KeyType KType;
    
public:
    bool get(const KType& aKey, MObj& aObj) {
        cout<<"get from Storage "<<aKey<<endl;
        return true;
    }
    bool put(const KType& aKey, const MObj& aObj) {
        cout<<"put to Storage "<<aKey<<" "<<aObj<<endl;
        return true;
    }
    bool remove(const KType& aKey) {
        cout<<"remove from Storage "<<aKey<<endl;
        
        return true;
    }    
};


template <class _KeyType, class _ValueType, class _SerializerType>
class ObjectStorage {
public:
    typedef _SerializerType TSerializer;
    typedef _ValueType MObj;
    typedef _KeyType KType;

    ObjectStorage(const Poco::SharedPtr<openstars::storage::AbstractKVStorage>& stg) : m_storage(stg) {
        assert(m_storage);
    }


public:

    bool get(const KType& aKey, MObj& aObj) {
        std::string aBuf;
        if (!m_storage->isReadable())
            return false;

        if (m_storage->get(aBuf, aKey) != 0)
            return false;
        try {
            if (TSerializer::DeserializeT(aObj, aBuf) < 0) {
                return false;
            }

        } catch (...) {
            cout << "ko deserial dc roi catch" << endl;
        }

        return true;
    }

    bool put(const KType& aKey, const MObj& aObj) {
        if (!m_storage->isWritable())
            return false;
        std::string aBuf;
        if (TSerializer::SerializeT(aBuf, aObj) < 0)
            return false;


        if (m_storage->put(aKey, aBuf) != 0) {
            return false;
        }
        return true;
    }

    bool remove(const KType& aKey) {
        if (!m_storage->isWritable())
            return false;
        if (m_storage->remove(aKey) != 0)
            return false;
        return true;
    }

    void setKVStorage(const Poco::SharedPtr<openstars::storage::AbstractKVStorage>& stg) {
        if (stg) {
            m_storage = stg;
            m_pstorage = m_storage.get();
        }
    }

    ////////////////////////


protected:
    Poco::SharedPtr<openstars::storage::AbstractKVStorage> m_storage;
    openstars::storage::AbstractKVStorage* m_pstorage;

};

template <class _KeyType, class _ValueType, class _ThriftType, class _SerializerType>
class ThriftObjectStorage {
public:
    typedef _SerializerType TSerializer;
    typedef _ValueType MObj;
    typedef _KeyType KType;
    typedef _ThriftType ThriftType;

    ThriftObjectStorage(const Poco::SharedPtr<openstars::storage::AbstractKVStorage>& stg) : m_storage(stg) {
        assert(m_storage);
    }


public:

    bool get(const KType& aKey, MObj& aObj) {
        std::string aBuf;
        if (!m_storage->isReadable())
            return false;

        if (m_storage->get(aBuf, aKey) != 0)
            return false;
        try {
            if (TSerializer::DeserializeT(aObj, aBuf) < 0) {
                return false;
            }

        } catch (...) {
            cout << "ko deserial dc roi catch" << endl;
        }

        return true;
    }

    bool put(const KType& aKey, const MObj& aObj) {
        if (!m_storage->isWritable())
            return false;
        std::string aBuf;
        if (TSerializer::SerializeT(aBuf, aObj) < 0)
            return false;


        if (m_storage->put(aKey, aBuf) != 0) {
            return false;
        }
        return true;
    }
    
    bool put(const KType& aKey, const ThriftType& aObj) {
        if (!m_storage->isWritable())
            return false;
        std::string aBuf;
        if (TSerializer::Serialize(aBuf, aObj) < 0)
            return false;

        if (m_storage->put(aKey, aBuf) != 0) {
            return false;
        }
        return true;
    }    

    bool remove(const KType& aKey) {
        if (!m_storage->isWritable())
            return false;
        if (m_storage->remove(aKey) != 0)
            return false;
        return true;
    }

    void setKVStorage(const Poco::SharedPtr<openstars::storage::AbstractKVStorage>& stg) {
        if (stg) {
            m_storage = stg;
            m_pstorage = m_storage.get();
        }
    }

    ////////////////////////


protected:
    Poco::SharedPtr<openstars::storage::AbstractKVStorage> m_storage;
    openstars::storage::AbstractKVStorage* m_pstorage;

};

} } // namespace 

#endif	/* ZBACKENDSTORAGE_H */

