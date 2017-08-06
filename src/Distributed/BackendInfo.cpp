/* 
 * File:   BackendInfo.cpp
 * Author: trungthanh
 * 
 * Created on August 16, 2012, 1:10 PM
 */

#include "Distributed/BackendInfo.h"

namespace openstars{ namespace distributed {
    

BackendInfo::BackendInfo(const std::string host, int port , HashType startRange, int weight, TStatus status)
:_host(host)
,_port(port)
,_startRange(startRange)
,_weight(weight)
,_status(status)
{
}

BackendInfo::BackendInfo(const BackendInfo& orig)
:_host(orig._host)
,_port(orig._port)
,_startRange(orig._startRange)
,_weight(orig._weight)
,_status(orig._status)
{
}

BackendInfo::~BackendInfo() {
}

bool BackendInfo::EndpointLesser::operator ()(const BackendInfo& be1, const BackendInfo& be2){
    if (be1._port == be2._port)
        return be1._host < be2._host;
    return be1._port < be2._port;    
}

bool BackendInfo::EndpointEqual::operator ()(const BackendInfo& be1, const BackendInfo& be2){
    return (be1._port == be2._port && be1._host == be2._host);
}

void BackendInfo::operator = (const BackendInfo& other){
    _host = other._host;
    _port = other._port;
    _startRange = other._startRange;
    _weight = other._weight;
    _status = other._status;
    
}
//
//void BackendInfo::operator = (const Up::Distributed::TBackendInfo& other){
//    _host = other.host;
//    _port = other.port;
//    _startRange = other.startRange;
//    _weight = other.weight;
//    _status = (TStatus)other.status;    
//}
//
//void BackendInfo::assignTo( Up::Distributed::TBackendInfo& other)const{
//    other.host = _host;
//    other.port = _port;
//    other.startRange = _startRange;
//    other.weight = _weight;
//    other.status = (Up::Distributed::TBackendStatus::type)_status;
//}

bool BackendInfo::operator ==(const BackendInfo& other)const{
    return (_startRange == other._startRange && _port == other._port && _host == other._host);
}

bool BackendInfo::operator <(const BackendInfo& other)const{
    if (_startRange == other._startRange){
        if (_port == other._port)
            return _host < other._host;
        return _port < other._port;
    }        
    else 
        return _startRange < other._startRange;
}

void BackendInfo::setInfo(const std::string host, int port, HashType startRange, int weight, TStatus status){
    _host = host;
    _port = port;
    _startRange = startRange;
    _weight = weight;
    _status = status;
}

void BackendInfo::getInfo(std::string& host, int& port, HashType& startRange, int& weight, TStatus& status){
    host = _host;
    port = _port;
    startRange = _startRange;
    weight = _weight;
    status = _status;
}

void BackendInfo::setHost(const std::string& host){
    _host = host;
}

void BackendInfo::setPort(const int port){
    _port = port;
}

void BackendInfo::setStartRange(const HashType startRange){
    _startRange = startRange;
}

void BackendInfo::setWeight(const int weight){
    _weight = weight;
}

bool BackendInfo::isValid() const{
    return (_port > 0 && _host.length() > 0);
}

} }