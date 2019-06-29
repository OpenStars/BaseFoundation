/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SnappyKVStorage.h
 * Author: trungthanh
 *
 * Created on March 12, 2018, 10:16 PM
 */

#ifndef SNAPPYKVSTORAGE_H
#define SNAPPYKVSTORAGE_H

#include "Storage/AbstractKVStorage.h"

namespace openstars {
namespace storage {

class SnappyKVStorage : public AbstractKVStorage{   
public:
    
    SnappyKVStorage(AbstractKVStorage::Ptr aBackendKV);
    
    virtual ~SnappyKVStorage();

    void compactData() {
        if (_kv)
            _kv->compactData();
    };

    void syncCompactData() {
        if (_kv)
            _kv->syncCompactData();        
    };

    virtual bool open() {
        if (_kv)
            _kv->open();
        return true;
    }

    virtual void close() {
        if (_kv)
            _kv->close();
    }
    
    void flush() {
        if (_kv)
            _kv->flush();
    }
    
protected:
    int32_t _put(const void* inKeyData, const int& keyLen, const void* inData, const int& datalen) override ;
    
    int32_t _get(VType &_return, const KType &key) const override ;

    int32_t _get(const void* inKeyData, const int& keyLen, void* outData, const int& datalen) const override ;
    
    int32_t _multiGet(KVMap &_return, const KList &keys) const override ;
    
private:
    SnappyKVStorage(const SnappyKVStorage& orig);
    
private:
    AbstractKVStorage::Ptr _kv;
};

} }

#endif /* SNAPPYKVSTORAGE_H */

