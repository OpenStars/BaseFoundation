/* 
 * File:   SimpleServiceFactory.h
 * Author: trungthanh
 *
 * Created on October 15, 2014, 5:43 PM
 */

#ifndef SIMPLESERVICEFACTORY_H
#define	SIMPLESERVICEFACTORY_H


#include "Poco/Util/Application.h"
#include "Poco/StringTokenizer.h"
#include "Poco/NumberFormatter.h"

#include "PocoEx/NetUtil.h"
#include <iostream>

class SimpleServiceFactory {
public:
    static int svrPort;
    static int cfgPort;    
    static std::string svrHost;
    static std::string zkHosts;
    static std::string zkPath;
    
public:
    static void init(Poco::Util::Application& app)
    {
        if (svrPort <= 0)
            svrPort = app.config().getInt("sns.thrift.port", 8303);
        if (cfgPort <=0 )
            cfgPort = app.config().getInt("sns.thrift.config.port", 0);
        std::cout<<"service port:"<<svrPort<<std::endl;
        std::cout<<"configuration service port:"<<cfgPort<<std::endl;
        

        if(svrHost.length() == 0)
            svrHost = app.config().getString("sns.thrift.host" , "");
        if (!NetUtil::hasIPInThisHost(svrHost))
        {
            std::vector<std::string> ips;
            if (svrHost.length() > 0)
                    NetUtil::getHostIPAddr(svrHost, ips);
            else
                NetUtil::getHostIPAddr("10.", ips);
            if (ips.size() > 0)
                svrHost = ips[0];
            else svrHost = "127.0.0.1";

        }
        
        if (zkHosts.length() == 0)
            zkHosts = app.config().getString("sns.service.zkservers","");
        if (zkPath.length() == 0)
            zkPath = app.config().getString("sns.service.reg_path","");
      
        std::cout<<"zkHosts:"<<zkHosts<<
                std::endl<<"zkPath:"<<zkPath
                <<std::endl<<"please check host :"<<svrHost<<std::endl;
        
    }

    
protected:

public:
};


#endif	/* SIMPLESERVICEFACTORY_H */

