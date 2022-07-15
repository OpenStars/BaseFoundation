// This autogenerated skeleton file illustrates how to build a server.
// You should copy it to another filename to avoid overwriting it.

#include "StorageMonitorService.h"
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

using namespace  ::openstars::base::storage::monitor;

class StorageMonitorServiceHandler : virtual public StorageMonitorServiceIf {
 public:
  StorageMonitorServiceHandler() {
    // Your initialization goes here
  }

  void getCurrentCacheStorageStat(backendStat& _return) {
    // Your implementation goes here
    printf("getCurrentCacheStorageStat\n");
  }

  void getCacheStorageStat(backendStat& _return, const int32_t seconds) {
    // Your implementation goes here
    printf("getCacheStorageStat\n");
  }

  void enableStorageBackend(const bool isRead, const bool isEnable, const std::string& beName) {
    // Your implementation goes here
    printf("enableStorageBackend\n");
  }

  void setCacheMaxSize(const int32_t newMaxSize) {
    // Your implementation goes here
    printf("setCacheMaxSize\n");
  }

  void saveDataToBackend(const bool enable) {
    // Your implementation goes here
    printf("saveDataToBackend\n");
  }

  void enableWarming(const bool enable) {
    // Your implementation goes here
    printf("enableWarming\n");
  }

  void compactData(const std::string& storageName) {
    // Your implementation goes here
    printf("compactData\n");
  }

  void closeStorage(const std::string& stgName) {
    // Your implementation goes here
    printf("closeStorage\n");
  }

  void openStorage(const std::string& stgCreateOption) {
    // Your implementation goes here
    printf("openStorage\n");
  }

  void getZKServicePath(std::string& _return) {
    // Your implementation goes here
    printf("getZKServicePath\n");
  }

  void getZKConfigPath(std::string& _return) {
    // Your implementation goes here
    printf("getZKConfigPath\n");
  }

  void checkZKService() {
    // Your implementation goes here
    printf("checkZKService\n");
  }

  void checkZKConfigPath() {
    // Your implementation goes here
    printf("checkZKConfigPath\n");
  }

  void registerServiceZK(const std::string& basePath, const std::string& scheme) {
    // Your implementation goes here
    printf("registerServiceZK\n");
  }

  void registerConfigZK(const std::string& basePath, const std::string& scheme) {
    // Your implementation goes here
    printf("registerConfigZK\n");
  }

  void addListenServicePort(const int32_t newPort) {
    // Your implementation goes here
    printf("addListenServicePort\n");
  }

};

int main(int argc, char **argv) {
  int port = 9090;
  ::std::shared_ptr<StorageMonitorServiceHandler> handler(new StorageMonitorServiceHandler());
  ::std::shared_ptr<TProcessor> processor(new StorageMonitorServiceProcessor(handler));
  ::std::shared_ptr<TServerTransport> serverTransport(new TServerSocket(port));
  ::std::shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
  ::std::shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

  TSimpleServer server(processor, serverTransport, transportFactory, protocolFactory);
  server.serve();
  return 0;
}

