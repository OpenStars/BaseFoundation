/**
 * Autogenerated by Thrift Compiler (0.11.0)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#ifndef TBackendManagerService_H
#define TBackendManagerService_H

#include <thrift/TDispatchProcessor.h>
#include <thrift/async/TConcurrentClientSyncInfo.h>
#include "distributed_types.h"

namespace openstars { namespace distributed {

#ifdef _MSC_VER
  #pragma warning( push )
  #pragma warning (disable : 4250 ) //inheriting methods via dominance 
#endif

class TBackendManagerServiceIf {
 public:
  virtual ~TBackendManagerServiceIf() {}
  virtual void getBackends(std::vector<TBackendInfo> & _return) = 0;
  virtual void getBEWrite(std::vector<TBackendInfo> & _return, const std::string& key) = 0;
  virtual void getBERead(std::vector<TBackendInfo> & _return, const std::string& key) = 0;
  virtual void addBackend(const TBackendInfo& aNode) = 0;
  virtual void updateBackend(const TBackendInfo& aNode) = 0;
  virtual void removeBackend(const TBackendInfo& aNode) = 0;
};

class TBackendManagerServiceIfFactory {
 public:
  typedef TBackendManagerServiceIf Handler;

  virtual ~TBackendManagerServiceIfFactory() {}

  virtual TBackendManagerServiceIf* getHandler(const ::apache::thrift::TConnectionInfo& connInfo) = 0;
  virtual void releaseHandler(TBackendManagerServiceIf* /* handler */) = 0;
};

class TBackendManagerServiceIfSingletonFactory : virtual public TBackendManagerServiceIfFactory {
 public:
  TBackendManagerServiceIfSingletonFactory(const ::apache::thrift::stdcxx::shared_ptr<TBackendManagerServiceIf>& iface) : iface_(iface) {}
  virtual ~TBackendManagerServiceIfSingletonFactory() {}

  virtual TBackendManagerServiceIf* getHandler(const ::apache::thrift::TConnectionInfo&) {
    return iface_.get();
  }
  virtual void releaseHandler(TBackendManagerServiceIf* /* handler */) {}

 protected:
  ::apache::thrift::stdcxx::shared_ptr<TBackendManagerServiceIf> iface_;
};

class TBackendManagerServiceNull : virtual public TBackendManagerServiceIf {
 public:
  virtual ~TBackendManagerServiceNull() {}
  void getBackends(std::vector<TBackendInfo> & /* _return */) {
    return;
  }
  void getBEWrite(std::vector<TBackendInfo> & /* _return */, const std::string& /* key */) {
    return;
  }
  void getBERead(std::vector<TBackendInfo> & /* _return */, const std::string& /* key */) {
    return;
  }
  void addBackend(const TBackendInfo& /* aNode */) {
    return;
  }
  void updateBackend(const TBackendInfo& /* aNode */) {
    return;
  }
  void removeBackend(const TBackendInfo& /* aNode */) {
    return;
  }
};


class TBackendManagerService_getBackends_args {
 public:

  TBackendManagerService_getBackends_args(const TBackendManagerService_getBackends_args&);
  TBackendManagerService_getBackends_args& operator=(const TBackendManagerService_getBackends_args&);
  TBackendManagerService_getBackends_args() {
  }

  virtual ~TBackendManagerService_getBackends_args() throw();

  bool operator == (const TBackendManagerService_getBackends_args & /* rhs */) const
  {
    return true;
  }
  bool operator != (const TBackendManagerService_getBackends_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const TBackendManagerService_getBackends_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class TBackendManagerService_getBackends_pargs {
 public:


  virtual ~TBackendManagerService_getBackends_pargs() throw();

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _TBackendManagerService_getBackends_result__isset {
  _TBackendManagerService_getBackends_result__isset() : success(false) {}
  bool success :1;
} _TBackendManagerService_getBackends_result__isset;

class TBackendManagerService_getBackends_result {
 public:

  TBackendManagerService_getBackends_result(const TBackendManagerService_getBackends_result&);
  TBackendManagerService_getBackends_result& operator=(const TBackendManagerService_getBackends_result&);
  TBackendManagerService_getBackends_result() {
  }

  virtual ~TBackendManagerService_getBackends_result() throw();
  std::vector<TBackendInfo>  success;

  _TBackendManagerService_getBackends_result__isset __isset;

  void __set_success(const std::vector<TBackendInfo> & val);

  bool operator == (const TBackendManagerService_getBackends_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    return true;
  }
  bool operator != (const TBackendManagerService_getBackends_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const TBackendManagerService_getBackends_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _TBackendManagerService_getBackends_presult__isset {
  _TBackendManagerService_getBackends_presult__isset() : success(false) {}
  bool success :1;
} _TBackendManagerService_getBackends_presult__isset;

class TBackendManagerService_getBackends_presult {
 public:


  virtual ~TBackendManagerService_getBackends_presult() throw();
  std::vector<TBackendInfo> * success;

  _TBackendManagerService_getBackends_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

typedef struct _TBackendManagerService_getBEWrite_args__isset {
  _TBackendManagerService_getBEWrite_args__isset() : key(false) {}
  bool key :1;
} _TBackendManagerService_getBEWrite_args__isset;

class TBackendManagerService_getBEWrite_args {
 public:

  TBackendManagerService_getBEWrite_args(const TBackendManagerService_getBEWrite_args&);
  TBackendManagerService_getBEWrite_args& operator=(const TBackendManagerService_getBEWrite_args&);
  TBackendManagerService_getBEWrite_args() : key() {
  }

  virtual ~TBackendManagerService_getBEWrite_args() throw();
  std::string key;

  _TBackendManagerService_getBEWrite_args__isset __isset;

  void __set_key(const std::string& val);

  bool operator == (const TBackendManagerService_getBEWrite_args & rhs) const
  {
    if (!(key == rhs.key))
      return false;
    return true;
  }
  bool operator != (const TBackendManagerService_getBEWrite_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const TBackendManagerService_getBEWrite_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class TBackendManagerService_getBEWrite_pargs {
 public:


  virtual ~TBackendManagerService_getBEWrite_pargs() throw();
  const std::string* key;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _TBackendManagerService_getBEWrite_result__isset {
  _TBackendManagerService_getBEWrite_result__isset() : success(false) {}
  bool success :1;
} _TBackendManagerService_getBEWrite_result__isset;

class TBackendManagerService_getBEWrite_result {
 public:

  TBackendManagerService_getBEWrite_result(const TBackendManagerService_getBEWrite_result&);
  TBackendManagerService_getBEWrite_result& operator=(const TBackendManagerService_getBEWrite_result&);
  TBackendManagerService_getBEWrite_result() {
  }

  virtual ~TBackendManagerService_getBEWrite_result() throw();
  std::vector<TBackendInfo>  success;

  _TBackendManagerService_getBEWrite_result__isset __isset;

  void __set_success(const std::vector<TBackendInfo> & val);

  bool operator == (const TBackendManagerService_getBEWrite_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    return true;
  }
  bool operator != (const TBackendManagerService_getBEWrite_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const TBackendManagerService_getBEWrite_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _TBackendManagerService_getBEWrite_presult__isset {
  _TBackendManagerService_getBEWrite_presult__isset() : success(false) {}
  bool success :1;
} _TBackendManagerService_getBEWrite_presult__isset;

class TBackendManagerService_getBEWrite_presult {
 public:


  virtual ~TBackendManagerService_getBEWrite_presult() throw();
  std::vector<TBackendInfo> * success;

  _TBackendManagerService_getBEWrite_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

typedef struct _TBackendManagerService_getBERead_args__isset {
  _TBackendManagerService_getBERead_args__isset() : key(false) {}
  bool key :1;
} _TBackendManagerService_getBERead_args__isset;

class TBackendManagerService_getBERead_args {
 public:

  TBackendManagerService_getBERead_args(const TBackendManagerService_getBERead_args&);
  TBackendManagerService_getBERead_args& operator=(const TBackendManagerService_getBERead_args&);
  TBackendManagerService_getBERead_args() : key() {
  }

  virtual ~TBackendManagerService_getBERead_args() throw();
  std::string key;

  _TBackendManagerService_getBERead_args__isset __isset;

  void __set_key(const std::string& val);

  bool operator == (const TBackendManagerService_getBERead_args & rhs) const
  {
    if (!(key == rhs.key))
      return false;
    return true;
  }
  bool operator != (const TBackendManagerService_getBERead_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const TBackendManagerService_getBERead_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class TBackendManagerService_getBERead_pargs {
 public:


  virtual ~TBackendManagerService_getBERead_pargs() throw();
  const std::string* key;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _TBackendManagerService_getBERead_result__isset {
  _TBackendManagerService_getBERead_result__isset() : success(false) {}
  bool success :1;
} _TBackendManagerService_getBERead_result__isset;

class TBackendManagerService_getBERead_result {
 public:

  TBackendManagerService_getBERead_result(const TBackendManagerService_getBERead_result&);
  TBackendManagerService_getBERead_result& operator=(const TBackendManagerService_getBERead_result&);
  TBackendManagerService_getBERead_result() {
  }

  virtual ~TBackendManagerService_getBERead_result() throw();
  std::vector<TBackendInfo>  success;

  _TBackendManagerService_getBERead_result__isset __isset;

  void __set_success(const std::vector<TBackendInfo> & val);

  bool operator == (const TBackendManagerService_getBERead_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    return true;
  }
  bool operator != (const TBackendManagerService_getBERead_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const TBackendManagerService_getBERead_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _TBackendManagerService_getBERead_presult__isset {
  _TBackendManagerService_getBERead_presult__isset() : success(false) {}
  bool success :1;
} _TBackendManagerService_getBERead_presult__isset;

class TBackendManagerService_getBERead_presult {
 public:


  virtual ~TBackendManagerService_getBERead_presult() throw();
  std::vector<TBackendInfo> * success;

  _TBackendManagerService_getBERead_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

typedef struct _TBackendManagerService_addBackend_args__isset {
  _TBackendManagerService_addBackend_args__isset() : aNode(false) {}
  bool aNode :1;
} _TBackendManagerService_addBackend_args__isset;

class TBackendManagerService_addBackend_args {
 public:

  TBackendManagerService_addBackend_args(const TBackendManagerService_addBackend_args&);
  TBackendManagerService_addBackend_args& operator=(const TBackendManagerService_addBackend_args&);
  TBackendManagerService_addBackend_args() {
  }

  virtual ~TBackendManagerService_addBackend_args() throw();
  TBackendInfo aNode;

  _TBackendManagerService_addBackend_args__isset __isset;

  void __set_aNode(const TBackendInfo& val);

  bool operator == (const TBackendManagerService_addBackend_args & rhs) const
  {
    if (!(aNode == rhs.aNode))
      return false;
    return true;
  }
  bool operator != (const TBackendManagerService_addBackend_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const TBackendManagerService_addBackend_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class TBackendManagerService_addBackend_pargs {
 public:


  virtual ~TBackendManagerService_addBackend_pargs() throw();
  const TBackendInfo* aNode;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class TBackendManagerService_addBackend_result {
 public:

  TBackendManagerService_addBackend_result(const TBackendManagerService_addBackend_result&);
  TBackendManagerService_addBackend_result& operator=(const TBackendManagerService_addBackend_result&);
  TBackendManagerService_addBackend_result() {
  }

  virtual ~TBackendManagerService_addBackend_result() throw();

  bool operator == (const TBackendManagerService_addBackend_result & /* rhs */) const
  {
    return true;
  }
  bool operator != (const TBackendManagerService_addBackend_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const TBackendManagerService_addBackend_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class TBackendManagerService_addBackend_presult {
 public:


  virtual ~TBackendManagerService_addBackend_presult() throw();

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

typedef struct _TBackendManagerService_updateBackend_args__isset {
  _TBackendManagerService_updateBackend_args__isset() : aNode(false) {}
  bool aNode :1;
} _TBackendManagerService_updateBackend_args__isset;

class TBackendManagerService_updateBackend_args {
 public:

  TBackendManagerService_updateBackend_args(const TBackendManagerService_updateBackend_args&);
  TBackendManagerService_updateBackend_args& operator=(const TBackendManagerService_updateBackend_args&);
  TBackendManagerService_updateBackend_args() {
  }

  virtual ~TBackendManagerService_updateBackend_args() throw();
  TBackendInfo aNode;

  _TBackendManagerService_updateBackend_args__isset __isset;

  void __set_aNode(const TBackendInfo& val);

  bool operator == (const TBackendManagerService_updateBackend_args & rhs) const
  {
    if (!(aNode == rhs.aNode))
      return false;
    return true;
  }
  bool operator != (const TBackendManagerService_updateBackend_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const TBackendManagerService_updateBackend_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class TBackendManagerService_updateBackend_pargs {
 public:


  virtual ~TBackendManagerService_updateBackend_pargs() throw();
  const TBackendInfo* aNode;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class TBackendManagerService_updateBackend_result {
 public:

  TBackendManagerService_updateBackend_result(const TBackendManagerService_updateBackend_result&);
  TBackendManagerService_updateBackend_result& operator=(const TBackendManagerService_updateBackend_result&);
  TBackendManagerService_updateBackend_result() {
  }

  virtual ~TBackendManagerService_updateBackend_result() throw();

  bool operator == (const TBackendManagerService_updateBackend_result & /* rhs */) const
  {
    return true;
  }
  bool operator != (const TBackendManagerService_updateBackend_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const TBackendManagerService_updateBackend_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class TBackendManagerService_updateBackend_presult {
 public:


  virtual ~TBackendManagerService_updateBackend_presult() throw();

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

typedef struct _TBackendManagerService_removeBackend_args__isset {
  _TBackendManagerService_removeBackend_args__isset() : aNode(false) {}
  bool aNode :1;
} _TBackendManagerService_removeBackend_args__isset;

class TBackendManagerService_removeBackend_args {
 public:

  TBackendManagerService_removeBackend_args(const TBackendManagerService_removeBackend_args&);
  TBackendManagerService_removeBackend_args& operator=(const TBackendManagerService_removeBackend_args&);
  TBackendManagerService_removeBackend_args() {
  }

  virtual ~TBackendManagerService_removeBackend_args() throw();
  TBackendInfo aNode;

  _TBackendManagerService_removeBackend_args__isset __isset;

  void __set_aNode(const TBackendInfo& val);

  bool operator == (const TBackendManagerService_removeBackend_args & rhs) const
  {
    if (!(aNode == rhs.aNode))
      return false;
    return true;
  }
  bool operator != (const TBackendManagerService_removeBackend_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const TBackendManagerService_removeBackend_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class TBackendManagerService_removeBackend_pargs {
 public:


  virtual ~TBackendManagerService_removeBackend_pargs() throw();
  const TBackendInfo* aNode;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class TBackendManagerService_removeBackend_result {
 public:

  TBackendManagerService_removeBackend_result(const TBackendManagerService_removeBackend_result&);
  TBackendManagerService_removeBackend_result& operator=(const TBackendManagerService_removeBackend_result&);
  TBackendManagerService_removeBackend_result() {
  }

  virtual ~TBackendManagerService_removeBackend_result() throw();

  bool operator == (const TBackendManagerService_removeBackend_result & /* rhs */) const
  {
    return true;
  }
  bool operator != (const TBackendManagerService_removeBackend_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const TBackendManagerService_removeBackend_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class TBackendManagerService_removeBackend_presult {
 public:


  virtual ~TBackendManagerService_removeBackend_presult() throw();

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

class TBackendManagerServiceClient : virtual public TBackendManagerServiceIf {
 public:
  TBackendManagerServiceClient(apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) {
    setProtocol(prot);
  }
  TBackendManagerServiceClient(apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) {
    setProtocol(iprot,oprot);
  }
 private:
  void setProtocol(apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) {
  setProtocol(prot,prot);
  }
  void setProtocol(apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) {
    piprot_=iprot;
    poprot_=oprot;
    iprot_ = iprot.get();
    oprot_ = oprot.get();
  }
 public:
  apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> getInputProtocol() {
    return piprot_;
  }
  apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> getOutputProtocol() {
    return poprot_;
  }
  void getBackends(std::vector<TBackendInfo> & _return);
  void send_getBackends();
  void recv_getBackends(std::vector<TBackendInfo> & _return);
  void getBEWrite(std::vector<TBackendInfo> & _return, const std::string& key);
  void send_getBEWrite(const std::string& key);
  void recv_getBEWrite(std::vector<TBackendInfo> & _return);
  void getBERead(std::vector<TBackendInfo> & _return, const std::string& key);
  void send_getBERead(const std::string& key);
  void recv_getBERead(std::vector<TBackendInfo> & _return);
  void addBackend(const TBackendInfo& aNode);
  void send_addBackend(const TBackendInfo& aNode);
  void recv_addBackend();
  void updateBackend(const TBackendInfo& aNode);
  void send_updateBackend(const TBackendInfo& aNode);
  void recv_updateBackend();
  void removeBackend(const TBackendInfo& aNode);
  void send_removeBackend(const TBackendInfo& aNode);
  void recv_removeBackend();
 protected:
  apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> piprot_;
  apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> poprot_;
  ::apache::thrift::protocol::TProtocol* iprot_;
  ::apache::thrift::protocol::TProtocol* oprot_;
};

class TBackendManagerServiceProcessor : public ::apache::thrift::TDispatchProcessor {
 protected:
  ::apache::thrift::stdcxx::shared_ptr<TBackendManagerServiceIf> iface_;
  virtual bool dispatchCall(::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, const std::string& fname, int32_t seqid, void* callContext);
 private:
  typedef  void (TBackendManagerServiceProcessor::*ProcessFunction)(int32_t, ::apache::thrift::protocol::TProtocol*, ::apache::thrift::protocol::TProtocol*, void*);
  typedef std::map<std::string, ProcessFunction> ProcessMap;
  ProcessMap processMap_;
  void process_getBackends(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
  void process_getBEWrite(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
  void process_getBERead(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
  void process_addBackend(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
  void process_updateBackend(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
  void process_removeBackend(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
 public:
  TBackendManagerServiceProcessor(::apache::thrift::stdcxx::shared_ptr<TBackendManagerServiceIf> iface) :
    iface_(iface) {
    processMap_["getBackends"] = &TBackendManagerServiceProcessor::process_getBackends;
    processMap_["getBEWrite"] = &TBackendManagerServiceProcessor::process_getBEWrite;
    processMap_["getBERead"] = &TBackendManagerServiceProcessor::process_getBERead;
    processMap_["addBackend"] = &TBackendManagerServiceProcessor::process_addBackend;
    processMap_["updateBackend"] = &TBackendManagerServiceProcessor::process_updateBackend;
    processMap_["removeBackend"] = &TBackendManagerServiceProcessor::process_removeBackend;
  }

  virtual ~TBackendManagerServiceProcessor() {}
};

class TBackendManagerServiceProcessorFactory : public ::apache::thrift::TProcessorFactory {
 public:
  TBackendManagerServiceProcessorFactory(const ::apache::thrift::stdcxx::shared_ptr< TBackendManagerServiceIfFactory >& handlerFactory) :
      handlerFactory_(handlerFactory) {}

  ::apache::thrift::stdcxx::shared_ptr< ::apache::thrift::TProcessor > getProcessor(const ::apache::thrift::TConnectionInfo& connInfo);

 protected:
  ::apache::thrift::stdcxx::shared_ptr< TBackendManagerServiceIfFactory > handlerFactory_;
};

class TBackendManagerServiceMultiface : virtual public TBackendManagerServiceIf {
 public:
  TBackendManagerServiceMultiface(std::vector<apache::thrift::stdcxx::shared_ptr<TBackendManagerServiceIf> >& ifaces) : ifaces_(ifaces) {
  }
  virtual ~TBackendManagerServiceMultiface() {}
 protected:
  std::vector<apache::thrift::stdcxx::shared_ptr<TBackendManagerServiceIf> > ifaces_;
  TBackendManagerServiceMultiface() {}
  void add(::apache::thrift::stdcxx::shared_ptr<TBackendManagerServiceIf> iface) {
    ifaces_.push_back(iface);
  }
 public:
  void getBackends(std::vector<TBackendInfo> & _return) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->getBackends(_return);
    }
    ifaces_[i]->getBackends(_return);
    return;
  }

  void getBEWrite(std::vector<TBackendInfo> & _return, const std::string& key) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->getBEWrite(_return, key);
    }
    ifaces_[i]->getBEWrite(_return, key);
    return;
  }

  void getBERead(std::vector<TBackendInfo> & _return, const std::string& key) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->getBERead(_return, key);
    }
    ifaces_[i]->getBERead(_return, key);
    return;
  }

  void addBackend(const TBackendInfo& aNode) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->addBackend(aNode);
    }
    ifaces_[i]->addBackend(aNode);
  }

  void updateBackend(const TBackendInfo& aNode) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->updateBackend(aNode);
    }
    ifaces_[i]->updateBackend(aNode);
  }

  void removeBackend(const TBackendInfo& aNode) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->removeBackend(aNode);
    }
    ifaces_[i]->removeBackend(aNode);
  }

};

// The 'concurrent' client is a thread safe client that correctly handles
// out of order responses.  It is slower than the regular client, so should
// only be used when you need to share a connection among multiple threads
class TBackendManagerServiceConcurrentClient : virtual public TBackendManagerServiceIf {
 public:
  TBackendManagerServiceConcurrentClient(apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) {
    setProtocol(prot);
  }
  TBackendManagerServiceConcurrentClient(apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) {
    setProtocol(iprot,oprot);
  }
 private:
  void setProtocol(apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) {
  setProtocol(prot,prot);
  }
  void setProtocol(apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) {
    piprot_=iprot;
    poprot_=oprot;
    iprot_ = iprot.get();
    oprot_ = oprot.get();
  }
 public:
  apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> getInputProtocol() {
    return piprot_;
  }
  apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> getOutputProtocol() {
    return poprot_;
  }
  void getBackends(std::vector<TBackendInfo> & _return);
  int32_t send_getBackends();
  void recv_getBackends(std::vector<TBackendInfo> & _return, const int32_t seqid);
  void getBEWrite(std::vector<TBackendInfo> & _return, const std::string& key);
  int32_t send_getBEWrite(const std::string& key);
  void recv_getBEWrite(std::vector<TBackendInfo> & _return, const int32_t seqid);
  void getBERead(std::vector<TBackendInfo> & _return, const std::string& key);
  int32_t send_getBERead(const std::string& key);
  void recv_getBERead(std::vector<TBackendInfo> & _return, const int32_t seqid);
  void addBackend(const TBackendInfo& aNode);
  int32_t send_addBackend(const TBackendInfo& aNode);
  void recv_addBackend(const int32_t seqid);
  void updateBackend(const TBackendInfo& aNode);
  int32_t send_updateBackend(const TBackendInfo& aNode);
  void recv_updateBackend(const int32_t seqid);
  void removeBackend(const TBackendInfo& aNode);
  int32_t send_removeBackend(const TBackendInfo& aNode);
  void recv_removeBackend(const int32_t seqid);
 protected:
  apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> piprot_;
  apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> poprot_;
  ::apache::thrift::protocol::TProtocol* iprot_;
  ::apache::thrift::protocol::TProtocol* oprot_;
  ::apache::thrift::async::TConcurrentClientSyncInfo sync_;
};

#ifdef _MSC_VER
  #pragma warning( pop )
#endif

}} // namespace

#endif
