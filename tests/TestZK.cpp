/* 
 * File:   TestZK.cpp
 * Author: trungthanh
 *
 * Created on Mar 16, 2014, 12:57:46 AM
 */

#include <stdlib.h>
#include <iostream>
//#include "zktreeutil/ZkAdaptor.h"
//#include "zkclient/zkadapter.h"
#include "Poco/SharedPtr.h"
#include "Poco/MD5Engine.h"
#include "PocoEx/NetUtil.h"
#include "PocoEx/SharedMemoryEx.h"

using namespace std;

/*
 * Simple C++ Test Suite
 */

void testNetUtil() {

    std::vector<std::string> ips;
    NetUtil::getHostIPAddr("10.198", ips);
    for (size_t aIndex = 0 ; aIndex < ips.size() ; aIndex++)
        cout<<ips[aIndex]<<endl;
    
}

void testSHM()
{
    SharedMemoryEx aSHM(std::string("hometrungthanhtestshm"), 1024,  SharedMemoryEx::AM_WRITE, NULL ,  true);
    aSHM.setAutoUnlink(false);
    *aSHM.begin() = 'a';
    
}

//void test2() {
//    std::cout << "TestZK test 2" << std::endl;
//    std::cout << "%TEST_FAILED% time=0 testname=test2 (TestZK) message=error message sample" << std::endl;
//}

int main(int argc, char** argv) {
//    std::cout << "%SUITE_STARTING% TestZK" << std::endl;
//    std::cout << "%SUITE_STARTED%" << std::endl;
//
//    std::cout << "%TEST_STARTED% test1 (TestZK)" << std::endl;
//   // test1();
//    std::cout << "%TEST_FINISHED% time=0 test1 (TestZK)" << std::endl;
//
//    std::cout << "%TEST_STARTED% test2 (TestZK)\n" << std::endl;
//   // test2();
//    std::cout << "%TEST_FINISHED% time=0 test2 (TestZK)" << std::endl;
//
//    std::cout << "%SUITE_FINISHED% time=0" << std::endl;

    //testNetUtil();
    testSHM ();
    return (EXIT_SUCCESS);
}

