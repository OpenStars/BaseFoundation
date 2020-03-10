/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TimeBasedLisenceManager.h
 * Author: trungthanh
 *
 * Created on January 14, 2020, 11:52 AM
 */

#ifndef TIMEBASEDLISENCEMANAGER_H
#define TIMEBASEDLISENCEMANAGER_H
#include <stdint.h>

/*
 * Cách đơn giản để quản lý bản quyền dịch vụ phần mềm, kiểm tra việc quá hạn,
 * Nếu quá hạn thì sẽ stop luôn.
 */
class TimeBasedLisenceManager {
public:
    TimeBasedLisenceManager(int64_t aExpiredTimestamp);
    TimeBasedLisenceManager(const TimeBasedLisenceManager& orig);
    virtual ~TimeBasedLisenceManager();
public:
    void start();
    void extendTime(int64_t aTime){
        expiringTimestamp += aTime;
    }
private:
    int64_t expiringTimestamp;
    volatile bool started; 
};

#endif /* TIMEBASEDLISENCEMANAGER_H */

