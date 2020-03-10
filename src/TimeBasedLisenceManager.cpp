/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TimeBasedLisenceManager.cpp
 * Author: trungthanh
 * 
 * Created on January 14, 2020, 11:52 AM
 */

#include "TimeBasedLisenceManager.h"
#include <thread>
#include <chrono>
#include <iostream>

#include "time.h"

TimeBasedLisenceManager::TimeBasedLisenceManager(int64_t aExpiredTimestamp)
: expiringTimestamp(aExpiredTimestamp)
, started(false){
}

//TimeBasedLisenceManager::TimeBasedLisenceManager(const TimeBasedLisenceManager& orig) {
//}

TimeBasedLisenceManager::~TimeBasedLisenceManager() {
}

void TimeBasedLisenceManager::start(){
    if (started ){
        return;
    }
    started = true;
    std::thread aThread([this](){
        while (true) {
            auto currentTime = time(nullptr);
            if (currentTime > this->expiringTimestamp){
                std::cout<<"exiting ...";
                exit(10); // end the process
            }
            std::this_thread::sleep_for(std::chrono::seconds(5));
//            std::this_thread::sleep_for(std::chrono::minutes(1));
        }
    });
    
    aThread.detach();
}
