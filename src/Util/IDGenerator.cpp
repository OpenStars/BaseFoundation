/* 
 * File:   IDGenerator.cpp
 * Author: trungthanh
 * 
 * Created on July 14, 2015, 8:57 AM
 */

#include "Util/IDGenerator.h"
namespace Util {
    

IDGenerator::IDGenerator(const std::string mfName)
:mappingFileName(mfName){
    init();
}
//
//IDGenerator::IDGenerator(const IDGenerator& orig) {
//}


IDGenerator::~IDGenerator() {
}

void IDGenerator::init()
{
    mappingFile = boost::shared_ptr< boost::interprocess::managed_mapped_file > (
            new boost::interprocess::managed_mapped_file(
            boost::interprocess::open_or_create, mappingFileName.data(), 1048576)
            );

}

IDGenerator::TCounter IDGenerator::_getOrCreateCounterByName(const std::string& counterName)
{
    CounterMap::iterator it = mapCounters.find(counterName);
    if (it == mapCounters.end() )
    {
        int64_t* pCounter = mappingFile->find_or_construct<int64_t>(counterName.c_str())();
        mapCounters[counterName].counter = pCounter;
        return pCounter;
    }
    return it->second;
}


IDGenerator::TCounter IDGenerator::_getCounterByName(const std::string& counterName)
{
    CounterMap::iterator it = mapCounters.find(counterName);
    if (it == mapCounters.end() )
    {
        return TCounter ();
    }
    return it->second;
}

int32_t IDGenerator::createGenerator(const std::string& genName)
{
    Util::SpinLock::ScopedLock aLock(mutex);
    _getOrCreateCounterByName(genName);
    return 0;
}

int64_t IDGenerator::getNext(const std::string& counterName)
{
    Util::SpinLock::ScopedLock aLock(mutex);
    TCounter aCounter = _getCounterByName(counterName);
    if (aCounter.counter)
        return ++(*aCounter.counter);
    return 0;
}

int64_t IDGenerator::getCurrent(const std::string& counterName)
{
    Util::SpinLock::ScopedLock aLock(mutex);
    TCounter aCounter = _getCounterByName(counterName);
    if (aCounter.counter)
        return (*aCounter.counter);
    return 0;
}

int64_t IDGenerator::getStepValue(const std::string& counterName, const int64_t step)
{
    Util::SpinLock::ScopedLock aLock(mutex);
    TCounter aCounter = _getCounterByName(counterName);
    if (aCounter.counter) {
        int64_t aRes = *aCounter.counter;
        (*aCounter.counter) += step;
        return (aRes);
    }
    return 0;    
}

}//namespace Util