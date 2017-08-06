/* 
 * File:   EndpointManager.cpp
 * Author: trungthanh
 * 
 * Created on November 19, 2012, 7:00 PM
 */

#include "EndpointManager.h"
#include "Poco/Path.h"
#include "Poco/StringTokenizer.h"
#include "Poco/NumberParser.h"

#include <iostream>

#include "zkadapter/zkadapter.h"


using namespace std;

class EndpointManagerPrivate :public ZKEventListener
{
public:
    EndpointManagerPrivate(EndpointManager* aEp):parent(aEp){}
    
    void eventReceived(const EventSource<ZKWatcherEvent> &source, const ZKWatcherEvent &e);
public:
    EndpointManager* parent;
    Poco::SharedPtr<ZooKeeperAdapter> _zkClient;
};

EndpointManager::EndpointManager(const Endpoint& defaultEndpoint,Endpoint::TType preferType)
:startChecking(this, &EndpointManager::checkConnectionImpl )
,_mutex()
,_defaultEnpoint(defaultEndpoint)
,_preferType(preferType)
//,_zkClient()
,_zkServers()
,_zkBasePath()
,_endpoints()
,_currentIndex(0)
,_runningChecking(false)
,_private(new EndpointManagerPrivate (this) )
{
}


EndpointManager::~EndpointManager()
{
    this->stopChecking();
    delete _private;
    _private = NULL;
}

/**
 * 
 * @param zkServer
 * @param zkBasePath
 */
void EndpointManager::loadEndpoint(const std::string& zkServer, const std::string& zkBasePath)
{
    cout<<"loadEndpoint:"<<zkServer<<endl;
    this->_zkServers = zkServer;
    this->_zkBasePath = zkBasePath;
    this->doLoadEndpoint(true);
}


/**
 * load endpoint from zookeeper
 */
void EndpointManager::doLoadEndpoint(bool reconnect)
{
    ZooKeeperConfig config(this->_zkServers, ZooKeeperConfig::defaultLeasedTimeout, true, 1000);
    if (!_private->_zkClient)
        _private->_zkClient =  new ZooKeeperAdapter(config, _private, true);

    try {
        if (reconnect)
                _private->_zkClient->reconnect();
	vector<string> nodeList;     
	_private->_zkClient->getNodeChildren(nodeList, this->_zkBasePath, _private, _private);      

	std::vector<Endpoint> endpoints;
	cout<<"_zkBasePath:"<<_zkBasePath<<endl;

	for (size_t aIndex = 0 ; aIndex < nodeList.size(); aIndex++)
	{
	    Endpoint endpoint;
	    if (this->parseEndpoint(nodeList[aIndex], endpoint ) )
	    {
		cout<<"got endpoint: "<<endpoint.host<<" : "<<endpoint.port<<" : "<<endpoint.type<<endl;
		endpoints.push_back(endpoint);
	    }
	}

	if (endpoints.size() > 0)
		this->replaceAll(endpoints);
    } 
    catch (...) 
    {
	
    }

    this->startChecking();
    
}

/**
 * 
 * @param endpoints
 */
void EndpointManager::replaceAll(std::vector<Endpoint>& newEndpoints){
    
    std::vector<Endpoint> oldEndpoints;
    {
        ScopedLockType aLock(_mutex, false);
        oldEndpoints = _endpoints;
    }

    std::sort(newEndpoints.begin(), newEndpoints.end() );
    std::vector<Endpoint> missingEndpoints;
    std::vector<Endpoint> addedEndpoints;
    
    std::set_difference(oldEndpoints.begin(), oldEndpoints.end()
            ,newEndpoints.begin(), newEndpoints.end()
            ,std::inserter(missingEndpoints, missingEndpoints.end() ) );

    std::set_difference(newEndpoints.begin(), newEndpoints.end()
            ,oldEndpoints.begin(), oldEndpoints.end()
            ,std::inserter(addedEndpoints, addedEndpoints.end() ) );
    
    if (missingEndpoints.size() == 0 && addedEndpoints.size() > 0)
    {
        ScopedLockType aLock(_mutex, true);
        _endpoints.swap(newEndpoints);
        std::sort(_endpoints.begin(), _endpoints.end() );    
        return;
    } 
    else {
        // check missing backend
        
        for (std::vector<Endpoint>::iterator aIt=missingEndpoints.begin(); aIt != missingEndpoints.end(); aIt++)
        {
            //neu chet that thi remove di
            if (!aIt->isGoodEndpoint())
                this->removeEndpoint(*aIt);
            else //van con song ma mat zookeeper
                ;//logWrongDeadEndpoint(*aIt);
                
        }
        
        //for (auto aIt = addedEndpoints.begin(); aIt != addedEndpoints.end() ; aIt++)
        if (addedEndpoints.size() > 0)
        {
            ScopedLockType aLock(_mutex, true);
            _endpoints.insert(_endpoints.end(), addedEndpoints.begin(), addedEndpoints.end() );
            std::sort(_endpoints.begin(), _endpoints.end() );    
            /*
            if (aChecker.checkEndpoint(*aIt))
                this->addEndpoint(*aIt);
            else
                this->logWrongLiveEndpoint(*aIt);
             */
        }
        
    }
    
        
}

/**
 * 
 * @param endpointPath
 * @param result
 * @return 
 */
bool EndpointManager::parseEndpoint(const std::string& endpointPath, Endpoint& result){
  cout<<"parseEndpoint: "<<endpointPath<<endl;
    /** parse nodes */
    Poco::Path path(endpointPath); // UNIX style        
    std::string node = path.directory(path.depth());


    Poco::StringTokenizer parseToken(node, ":");
    cout<<"node: "<<node<<endl;
    
    if (parseToken.count() == 3) {
        
	result.host = parseToken[1];
        result.port =  Poco::NumberParser::parse( parseToken[2].c_str());
	result.type = Endpoint::EUnknown;
	
        std::string scheme = parseToken[0];
        Poco::StringTokenizer schemeStk(scheme,"_");
        try {
            if (schemeStk.count() > 1)
	    {
		if (schemeStk[0] == "thrift" && schemeStk[1] == "binary")
		{
		    result.type = Endpoint::EThriftBinary;
		}
		else if (schemeStk[0] == "thrift" && schemeStk[1] == "compact")
		{
		    result.type = Endpoint::EThriftCompact;
		} else if (schemeStk[0] == "http") 
		{
		    result.type = Endpoint::EHttp;
		} else 
		    result.type = Endpoint::EUnknown;

	    } else if (schemeStk.count() == 1){
		if (schemeStk[0] == "http") 
		{
		    result.type = Endpoint::EHttp;
		};
	    }
	    else 
		return false;
            
        }catch(...){
            return false;
        }
	if (this->_preferType == Endpoint::EAnyType)
	    return true;
	if (this->_preferType == result.type)
	    return true;
    }    
    return false;
}

void EndpointManager::setDefaultEndpoint(const Endpoint& aEndpoint)
{
    ScopedLockType aLock(_mutex);
    this->_defaultEnpoint = aEndpoint;
}


/**
 * getEndpoint
 * @param outEndpoint
 * @return 
 */
bool EndpointManager::getEndpoint(Endpoint& outEndpoint) const
{
    ScopedLockType aLock(_mutex);
    
    size_t aSize = this->_endpoints.size();
    if (this->_currentIndex >= aSize)
	_currentIndex = 0;
    if (aSize == 0)
    {
	outEndpoint = this->_defaultEnpoint;
	return false;
    }
    
    outEndpoint = this->_endpoints[_currentIndex];
    _currentIndex++;
    return true;
}

/**
 * get All endpoint
 * @param outEndpoints : all leaded endpoint
 * @return true if endpoints are from zookeeper, false if it is default endpoint
 */
bool EndpointManager::getEndpoint(std::vector<Endpoint>& outEndpoints) const
{
    ScopedLockType aLock(_mutex);
    size_t aSize = this->_endpoints.size();
    if (aSize > 0){
	outEndpoints = this->_endpoints;	
	return true;
    }
    outEndpoints.push_back(this->_defaultEnpoint);
    return false;
}

void EndpointManagerPrivate::eventReceived(const EventSource<ZKWatcherEvent>& source, const ZKWatcherEvent& e)
{
    
    if (e.getState() == ZOO_CONNECTED_STATE && (e.getType() == ZOO_DELETED_EVENT || e.getType() == ZOO_SESSION_EVENT ) )
    {
        if (this->_zkClient)
            if (this->_zkClient->getState() == ZooKeeperAdapter::AS_CONNECTED)        
                parent->doLoadEndpoint(false);
    } 
    else if(e.getState() == ZOO_EXPIRED_SESSION_STATE && (e.getType() == ZOO_DELETED_EVENT || e.getType() == ZOO_SESSION_EVENT ) )
    {
        parent->doLoadEndpoint(false);
    }   
    
}

void EndpointManager::stopChecking()
{
    if (!_runningChecking)
	return;
    _runningChecking = false;
    _stopMonitorEvent.set();
    while (! _doneEvent.tryWait(1000) )
        _runningChecking = false;
    _doneEvent.wait();
    
}

void EndpointManager::removeEndpoint(const Endpoint& aEndpoint)
{
    ScopedLockType aLock(_mutex);
    std::vector< Endpoint >::iterator aIt = std::lower_bound(_endpoints.begin(), _endpoints.end(), aEndpoint);
        
    if (aIt != _endpoints.end() && *aIt == aEndpoint)
        _endpoints.erase(aIt);
}

void EndpointManager::checkConnectionImpl()
{
    if (_runningChecking)
	return;
    _runningChecking = true;
    
    while (_runningChecking)
    {
        if (_stopMonitorEvent.tryWait(10000) ){
            _runningChecking = false;
            break;
        }
	//Poco::Thread::sleep(10000);
	if (!_runningChecking)
	    break;
	try {
	    vector<string> nodeList;     
	    _private->_zkClient->getNodeChildren(nodeList, this->_zkBasePath, _private, _private);      

	    std::vector<Endpoint> endpoints;
	    cout<<"_zkBasePath:"<<_zkBasePath<<endl;

	    for (size_t aIndex = 0 ; aIndex < nodeList.size(); aIndex++)
	    {
		Endpoint endpoint;
		if (this->parseEndpoint(nodeList[aIndex], endpoint ) )
		{
		    cout<<"got endpoint: "<<endpoint.host<<" : "<<endpoint.port<<" : "<<endpoint.type<<endl;
		    endpoints.push_back(endpoint);
		}
	    }

	    this->replaceAll(endpoints);
	} 
	catch (ZooKeeperException& e) 
	{
		if (_runningChecking) 
		{
		    _runningChecking = false;
		    this->doLoadEndpoint();
		}
		return;        
	}
	catch (...) 
	{
		if (_runningChecking) 
		{
		    _runningChecking = false;
		    this->doLoadEndpoint();
		}
		return ;
	}	
    };
    
    _runningChecking = false;
    _doneEvent.set();
    return ;
}