/* 
 * File:   ZKRegisterTest.cpp
 * Author: trungthanh
 *
 * Created on Sep 14, 2015, 4:33:47 PM
 */

#include <stdlib.h>
#include <iostream>

/*
 * Simple C++ Test Suite
 */

//void test1() {
//    std::cout << "ZKRegisterTest test 1" << std::endl;
//}
//
//void test2() {
//    std::cout << "ZKRegisterTest test 2" << std::endl;
//    std::cout << "%TEST_FAILED% time=0 testname=test2 (ZKRegisterTest) message=error message sample" << std::endl;
//}
#include "ZKRegister.h"
using namespace std;
void testZKRegister()
{
    ZKRegister aReg("127.0.0.1:2181,127.0.0.1:2181");
    aReg.addService("/projects/test/zkregtest", "255.255.122.122", 1983,"thrift_binary");
    aReg.addService("/projects/test/zkregtest", "255.255.122.122", 1984,"thrift_binary");
    aReg.addService("/projects/test/zkregtest", "255.255.122.122", 1985,"thrift_binary");
    aReg.start();
    int i ;
    cout<<"nhap mot so de exit "<<endl;
    cin>>i;
    aReg.stop();
}

int main(int argc, char** argv) {
    std::cout << "%SUITE_STARTING% ZKRegisterTest" << std::endl;
    std::cout << "%SUITE_STARTED%" << std::endl;
    
//
//    std::cout << "%TEST_STARTED% test1 (ZKRegisterTest)" << std::endl;
//    test1();
//    std::cout << "%TEST_FINISHED% time=0 test1 (ZKRegisterTest)" << std::endl;
//
//    std::cout << "%TEST_STARTED% test2 (ZKRegisterTest)\n" << std::endl;
//    test2();
//    std::cout << "%TEST_FINISHED% time=0 test2 (ZKRegisterTest)" << std::endl;
//
//    std::cout << "%SUITE_FINISHED% time=0" << std::endl;

    return (EXIT_SUCCESS);
}

