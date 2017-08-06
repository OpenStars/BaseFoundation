/* 
 * File:   MemoryStats.cpp
 * Author: trungthanh
 * 
 * Created on October 17, 2012, 2:44 PM
 */

#include "Caching/MemoryStats.h"

#include <sys/time.h>
#include <sys/resource.h>

#include <unistd.h>
#include <ios>
#include <iostream>
#include <fstream>
#include <string>


MemoryStats::MemoryStats() {
}

//MemoryStats::MemoryStats(const MemoryStats& orig) {
//}

MemoryStats::~MemoryStats() {
}

//////////////////////////////////////////////////////////////////////////////
// this code is from stackoverflow
// process_mem_usage(double &, double &) - takes two doubles by reference,
// attempts to read the system-dependent data for a process' virtual memory
// size and resident set size, and return the results in KB.
//
// On failure, returns 0.0, 0.0


void process_mem_usage(double& vm_usage, double& resident_set)
{
   using std::ios_base;
   using std::ifstream;
   using std::string;

   vm_usage     = 0.0;
   resident_set = 0.0;

   // 'file' stat seems to give the most reliable results
   //
   ifstream stat_stream("/proc/self/stat",ios_base::in);

   // dummy vars for leading entries in stat that we don't care about
   //
   string pid, comm, state, ppid, pgrp, session, tty_nr;
   string tpgid, flags, minflt, cminflt, majflt, cmajflt;
   string utime, stime, cutime, cstime, priority, nice;
   string O, itrealvalue, starttime;

   // the two fields we want
   //
   unsigned long vsize;
   long rss;

   stat_stream >> pid >> comm >> state >> ppid >> pgrp >> session >> tty_nr
               >> tpgid >> flags >> minflt >> cminflt >> majflt >> cmajflt
               >> utime >> stime >> cutime >> cstime >> priority >> nice
               >> O >> itrealvalue >> starttime >> vsize >> rss; // don't care about the rest

   stat_stream.close();

   long page_size_kb = sysconf(_SC_PAGE_SIZE) / 1024; // in case x86-64 is configured to use 2MB pages
   vm_usage     = vsize / 1024.0;
   resident_set = rss * page_size_kb;
}



void MemoryStats::grabInitialMem(){
    this->grabMemInfo(_initialMemory);
}

void MemoryStats::grabMemInfo(MemoryInfo& _return){
    double vm, res;
    process_mem_usage(vm, res);
    _return.processMem = res;
    _return.processVirt = vm;
    
}

const MemoryInfo& MemoryStats::getInitialMemory()const{
    return _initialMemory;
}
