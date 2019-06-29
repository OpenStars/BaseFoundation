/* 
 * File:   NetUtil.cpp
 * Author: trungthanh
 * 
 * Created on October 21, 2013, 4:36 PM
 */

#include "PocoEx/NetUtil.h"
#include "Poco/Net/IPAddress.h"
#include "Poco/Net/NetworkInterface.h"


bool NetUtil::getHostIPAddr(const std::string& filter, std::vector<std::string>& outIPs)
{
    try {
        Poco::Net::NetworkInterface::NetworkInterfaceList aList = Poco::Net::NetworkInterface::list();
        for (std::vector<Poco::Net::NetworkInterface>::iterator aIt = aList.begin(); aIt != aList.end() ; aIt++)
        {
            std::string aIP = (*aIt).address().toString();
            if (aIP.find(filter) == 0)
            {
                outIPs.push_back(aIP);
            }
        }
    } catch(...)
    {
        
    }
    return outIPs.size() > 0;
}

bool NetUtil::hasIPInThisHost(const std::string& ip)
{
    try {
        Poco::Net::NetworkInterface::NetworkInterfaceList aList = Poco::Net::NetworkInterface::list();
        for (std::vector<Poco::Net::NetworkInterface>::iterator aIt = aList.begin(); aIt != aList.end() ; aIt++)
        {
            std::string aIP = (*aIt).address().toString();
            if (aIP == ip)
            {
                return true;
            }
        }
    } catch(...)
    {
        
    }
    
    return false;
}