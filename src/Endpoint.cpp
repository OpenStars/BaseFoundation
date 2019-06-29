/* 
 * File:   Endpoint.cpp
 * Author: trungthanh
 * 
 * Created on November 19, 2012, 7:01 PM
 */

#include "Endpoint.h"
#include "Poco/Net/StreamSocket.h"


Endpoint::Endpoint()
:host("")
,port(0)
,type(EUnknown)
{
}

Endpoint::Endpoint(const std::string& aHost, int aPort, TType aType)
:host(aHost)
,port(aPort)
,type(aType)
{
    
}

Endpoint::Endpoint(const Endpoint& orig)
:host(orig.host)
,port(orig.port)
,type(orig.type)
{
}

const Endpoint& Endpoint::operator =(const Endpoint& other){
    host = other.host;
    port = other.port;
    type = other.type;
    return other;
}

bool Endpoint::isGoodEndpoint()
{
    Poco::Net::StreamSocket aSocket;
    Poco::Net::SocketAddress addr(host,  port);
    try {
        Poco::Timespan timeout(100000); /*100ms*/
        aSocket.connect(addr, timeout);
        aSocket.close();
    } catch(...)
    {
        try { 
            aSocket.close(); 
        } catch(...)
        {
            
        }
        return false;
    }
    return true;
}

bool Endpoint::operator <(const Endpoint& other) const 
{
    if (this->port == other.port)
        return this->host < other.host;
    return port<other.port;
}

bool Endpoint::operator ==(const Endpoint& other) const
{
    return (port == other.port && host == other.host);
}