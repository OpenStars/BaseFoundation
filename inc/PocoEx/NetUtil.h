/* 
 * File:   NetUtil.h
 * Author: trungthanh
 *
 * Created on October 21, 2013, 4:35 PM
 */

#ifndef NETUTIL_H
#define	NETUTIL_H

#include <string>
#include <vector>

class NetUtil {
public:
    static bool getHostIPAddr(const std::string& filter, std::vector<std::string>& outIP);
    static bool hasIPInThisHost(const std::string& ip);
private:

};

#endif	/* NETUTIL_H */

