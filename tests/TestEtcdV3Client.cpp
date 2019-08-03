/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TestEtcdV3Client.cpp
 * Author: trungthanh
 *
 * Created on July 31, 2019, 7:58 AM
 */

#include <stdlib.h>
#include <iostream>
using namespace std;
#include "include/etcd/Client.hpp"
#include "include/etcd/SyncClient.hpp" 
/*
 * Simple C++ Test Suite
 */

void testPutGet() {
    std::cout << "TestEtcdV3Client test PutGet" << std::endl;
    etcd::SyncClient aSyncClient("http://127.0.0.1:2379");
//    auto aResSet = aSyncClient.set("/hello/system","This is TrustKeys Great");
//    cout<<"Set /hello/system res: "<<aResSet.action()
//            <<" keys: "<<aResSet.keys().size() <<endl;

    auto aResGet = aSyncClient.get("/hello/system");
    cout<<"Get value of /hello/system" << aResGet.value().as_string()<<endl;
    
}

void test2() {
    std::cout << "TestEtcdV3Client test 2" << std::endl;
    std::cout << "%TEST_FAILED% time=0 testname=test2 (TestEtcdV3Client) message=error message sample" << std::endl;
}

int main(int argc, char** argv) {
    
    std::cout << "%SUITE_STARTING% TestEtcdV3Client" << std::endl;
    std::cout << "%SUITE_STARTED%" << std::endl;
    testPutGet();
//
//    std::cout << "%TEST_STARTED% test1 (TestEtcdV3Client)" << std::endl;
//    test1();
//    std::cout << "%TEST_FINISHED% time=0 test1 (TestEtcdV3Client)" << std::endl;
//
//    std::cout << "%TEST_STARTED% test2 (TestEtcdV3Client)\n" << std::endl;
//    test2();
//    std::cout << "%TEST_FINISHED% time=0 test2 (TestEtcdV3Client)" << std::endl;
//
//    std::cout << "%SUITE_FINISHED% time=0" << std::endl;

    return (EXIT_SUCCESS);
}

