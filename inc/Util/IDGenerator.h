/* 
 * File:   IDGenerator.h
 * Author: trungthanh
 *
 * Created on July 14, 2015, 8:57 AM
 */

#ifndef IDGENERATOR_H
#define	IDGENERATOR_H

#include <string>

#include <boost/shared_ptr.hpp>
#include <boost/interprocess/file_mapping.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <boost/interprocess/containers/vector.hpp>
#include <boost/interprocess/managed_mapped_file.hpp>
#include <boost/interprocess/sync/interprocess_mutex.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>

#include "Util/SpinLock.h"

#include <map>

namespace Util{
    
class AbstractIDGenerator {
public:
    virtual ~AbstractIDGenerator(){}
    virtual int32_t createGenerator(const std::string& genName) = 0;
    virtual int64_t getNext(const std::string& counterName) = 0;
    virtual int64_t getCurrent(const std::string& counterName) = 0;
    virtual int64_t getStepValue(const std::string& genName, const int64_t step) = 0;
};

/*SharedMem ID Generator*/
class IDGenerator: public AbstractIDGenerator {
public:
    IDGenerator(const std::string mfName);
    virtual ~IDGenerator();
public:
    virtual int32_t createGenerator(const std::string& genName);
    virtual int64_t getNext(const std::string& counterName);
    virtual int64_t getCurrent(const std::string& counterName);
    virtual int64_t getStepValue(const std::string& counterName, const int64_t step);
public:
    struct TCounter{
        TCounter():counter(NULL){}
        TCounter(int64_t* ptr):counter(ptr){}
        int64_t *counter;
    };
    
private:
    void init();
    TCounter _getOrCreateCounterByName(const std::string& counterName);
    TCounter _getCounterByName(const std::string& counterName);
private:
    IDGenerator(const IDGenerator& orig);
    
    std::string mappingFileName;
    boost::shared_ptr< boost::interprocess::managed_mapped_file > mappingFile;
    Util::SpinLock mutex;
    typedef std::map<std::string, TCounter > CounterMap;
    CounterMap mapCounters;
    
};

}

#endif	/* IDGENERATOR_H */

