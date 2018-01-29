/* 
 * File:   Endpoint.h
 * Author: trungthanh
 *
 * Created on November 19, 2012, 7:01 PM
 */

#ifndef ENDPOINT_H
#define	ENDPOINT_H

#include <string>


class Endpoint
{
public:
    enum TType{
	EUnknown=-1,
	EAnyType = 0,
	EHttp,
	EThriftBinary,
	EThriftCompact,
        EGrpc,
        EGrpcWeb
    };
public:
    Endpoint();
    Endpoint(const std::string& aHost, int aPort, TType aType);
    Endpoint(const Endpoint& orig);
    
    const Endpoint& operator = (const Endpoint& other);

    bool operator == (const Endpoint& other) const;
    bool operator < (const Endpoint& other) const;
    /*
     * Check if endpoint is open, this is a blocking function
     */
    bool isGoodEndpoint();
public:
    std::string host;
    int port;
    TType type;
};

#endif	/* ENDPOINT_H */

