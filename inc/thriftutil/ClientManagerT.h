/* 
 * File:   ClientManagerT.h
 * Author: trung
 *
 * Created on August 6, 2010, 3:41 PM
 */

#ifndef CLIENTMANAGERT_H
#define	CLIENTMANAGERT_H
#include <Poco/Mutex.h>
#include <Poco/SharedPtr.h>
#include <Poco/NumberFormatter.h>
#include <vector>
#include <map>



template <class _ClientType>
class ClientManagerT
{
    typedef  std::vector< Poco::SharedPtr< _ClientType > > TClientList;
    typedef  std::vector<  _ClientType*  > TClientPList;
    typedef std::map<std::string, TClientPList> TClientHolder;
protected:
    static _ClientType* fastGetClient(const std::string& host, const int& port)
    {
        Poco::Mutex::ScopedLock aLock(m_mutex);
        std::string aHostPort = host + ":" + Poco::NumberFormatter::format(port);

        TClientPList& aList = m_clientMap[ aHostPort ];
        if (aList.size() > 0)
        {
            _ClientType* aClient = aList.back();
            aList.pop_back();
            return aClient;

        }
        return NULL;
    }
public:
    static  _ClientType * getClient(const std::string& host, const int& port, bool framed = true)
    {
        _ClientType* aClient = fastGetClient(host , port);
        if (!aClient)
        {
            try {
                aClient = new _ClientType(host , port , framed);
                {
                    Poco::Mutex::ScopedLock aLock(m_mutex);
                    m_clients.push_back( aClient );
                }
            }
            catch(...)
            {
                if (aClient){
                    Poco::Mutex::ScopedLock aLock(m_mutex);
                    m_clients.push_back( aClient );
                }
                    //delete aClient;

//                return NULL;
            }
        }

        return aClient;
    }

    static void releaseClient(  _ClientType * aClient, const std::string& host, const int& port)
    {
        if (aClient)
            aClient->checkConnectionExpired();
        {
            Poco::Mutex::ScopedLock aLock(m_mutex);
            std::string aHostPort = host + ":" + Poco::NumberFormatter::format(port);

            TClientPList& aList = m_clientMap[ aHostPort ];
            aList.push_back(aClient);
        }
    }

public:
    static TClientHolder m_clientMap;
    static TClientList m_clients; // just for release
    static Poco::Mutex  m_mutex;
};

template <class _ClientType>
typename ClientManagerT<_ClientType>::TClientHolder ClientManagerT<_ClientType>::m_clientMap;

template <class _ClientType>
typename ClientManagerT<_ClientType>::TClientList ClientManagerT<_ClientType>::m_clients;


template <class _ClientType>
Poco::Mutex ClientManagerT<_ClientType>::m_mutex;



template <class _ClientType>
class UniqueClientManagerT
{
public:
    typedef std::map<std::string, Poco::SharedPtr< _ClientType > > TClientHolder;
    static  _ClientType*  getClient(const std::string& host, const int& port)
    {
//        return   new _ClientType(host , port , true);
        Poco::Mutex::ScopedLock aLock(m_mutex);
        std::string aHostPort = host + ":" + Poco::NumberFormatter::format(port);

        typename TClientHolder::iterator aIt = m_clientMap.find(aHostPort);

        Poco::SharedPtr< _ClientType >& aClient = m_clientMap[ aHostPort ];
        if (aIt == m_clientMap.end() )
        {
            m_clientMap[ aHostPort ] = new _ClientType(host , port , true);
            return m_clientMap[ aHostPort ].get();

        }
        else
            return aIt->second.get();
        return NULL; // Error
        //return aClient.get();
    }


public:
    static TClientHolder m_clientMap;
    static Poco::Mutex  m_mutex;
};

template <class _ClientType>
typename UniqueClientManagerT<_ClientType>::TClientHolder UniqueClientManagerT<_ClientType>::m_clientMap;


template <class _ClientType>
Poco::Mutex UniqueClientManagerT<_ClientType>::m_mutex;

template <class _ClientType>
class ClientWrapperT
{
public:
    ClientWrapperT(const ClientWrapperT<_ClientType>& other)
            :m_client(NULL)
            ,m_host(other.m_host)
            ,m_port(other.m_port)
            ,m_framed(other.m_framed)
    {
        
    }
    ClientWrapperT(const std::string& host, const int& port, bool framed = true)
            :m_client(NULL)
            ,m_host(host)
            ,m_port(port)
            ,m_framed(framed)
    {

    }
    ~ClientWrapperT()
    {
        if (m_client)
            ClientManagerT<_ClientType>::releaseClient(m_client, m_host, m_port);
    }
public:

    _ClientType*  operator->() {
        if (!m_client)
            m_client = ClientManagerT<_ClientType>::getClient(m_host,  m_port , m_framed);
        return m_client;
    }

private:
    _ClientType* m_client;
    std::string m_host;
    int m_port;
    bool m_framed;
};

#endif	/* CLIENTMANAGERT_H */

