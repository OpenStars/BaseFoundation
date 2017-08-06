/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AbstractStorageFactory.h
 * Author: trungthanh
 *
 * Created on August 5, 2017, 12:37 AM
 */

#ifndef ABSTRACTSTORAGEFACTORY_H
#define ABSTRACTSTORAGEFACTORY_H

namespace openstars{ namespace storage { 
    class AbstractKVStorage;
} }

class AbstractStorageFactory {
public:
    AbstractStorageFactory() {};
    virtual ~AbstractStorageFactory() {};
    
    virtual openstars::storage::AbstractKVStorage* createStorage(const std::string& creatingOption , std::string& name , int& rwmode) = 0;
private:

};

#endif /* ABSTRACTSTORAGEFACTORY_H */

