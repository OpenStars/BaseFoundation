/* 
 * File:   MemoryStats.h
 * Author: trungthanh
 *
 * Created on October 17, 2012, 2:44 PM
 */

#ifndef MEMORYSTATS_H
#define	MEMORYSTATS_H

#include <string>
#include <vector>
#include <stdint.h>
#include <stddef.h>

class MemSizeGetter{
public:
    template <class T> 
    size_t operator()(const T& aItem)const{
        return getSize(aItem);
    }
    
    virtual size_t getSize(const int32_t aItem)const { return sizeof(aItem); };
    virtual size_t getSize(const uint32_t aItem)const { return sizeof(aItem); };
    virtual size_t getSize(const int64_t aItem)const { return sizeof(aItem); };
    virtual size_t getSize(const uint64_t aItem)const { return sizeof(aItem); };
    virtual size_t getSize(const int16_t aItem)const { return sizeof(aItem); };
    virtual size_t getSize(const uint16_t aItem)const { return sizeof(aItem); };
    virtual size_t getSize(const int8_t aItem)const { return sizeof(aItem); };
    virtual size_t getSize(const uint8_t aItem)const { return sizeof(aItem); };
    virtual size_t getSize(const std::string& aItem)const {return sizeof(aItem) + aItem.length() ; }

    template <class T>
    size_t getSize(const std::vector<T>& aItem)const{
        size_t aKQ = sizeof(aItem);
        size_t aSize = aItem.size();
        for (size_t aIndex = 0; aIndex< aSize; aIndex++)
            aKQ += getSize(aItem[aIndex]);
        return aKQ;
    }

    size_t getSize(const std::vector<int32_t>& aItem)const{
        size_t aKQ = sizeof(aItem);
        aKQ += aItem.size() * sizeof(int32_t);
        return aKQ;
    }

    size_t getSize(const std::vector<uint32_t>& aItem)const{
        size_t aKQ = sizeof(aItem);
        aKQ += aItem.size() * sizeof(uint32_t);
        return aKQ;
    }
    
    size_t getSize(const std::vector<int64_t>& aItem)const{
        size_t aKQ = sizeof(aItem);
        aKQ += aItem.size() * sizeof(int64_t);
        return aKQ;
    }
    
    size_t getSize(const std::vector<uint64_t>& aItem)const{
        size_t aKQ = sizeof(aItem);
        aKQ += aItem.size() * sizeof(uint64_t);
        return aKQ;
    }

    size_t getSize(const std::vector<int8_t>& aItem)const{
        size_t aKQ = sizeof(aItem);
        aKQ += aItem.size() * sizeof(int8_t);
        return aKQ;
    }

    size_t getSize(const std::vector<uint8_t>& aItem)const{
        size_t aKQ = sizeof(aItem);
        aKQ += aItem.size() * sizeof(int8_t);
        return aKQ;
    }

    template <class T1, class T2>
    size_t getSize(const std::pair<T1, T2>& aItem)const{
        return  getSize(aItem.first) + getSize(aItem.second);
    }

    
    template <class T>
    size_t getSize(const T& aItem) const {return sizeof(aItem); }
};

struct MemoryInfo{
    int64_t processMem; // memory size of process in kb
    int64_t processVirt; // virtual memory size in kb
};



class MemoryStats {
public:
    MemoryStats();
    virtual ~MemoryStats();
public:
    //
    void grabInitialMem();
    
    void grabMemInfo(MemoryInfo& _return);
    
    const MemoryInfo& getInitialMemory()const ;
    
private:
    MemoryStats(const MemoryStats& orig);
protected:
    MemoryInfo _initialMemory;

};


#endif	/* MEMORYSTATS_H */

