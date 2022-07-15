/**
 * Autogenerated by Thrift Compiler (0.16.0)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#ifndef TNodeServiceBase_H
#define TNodeServiceBase_H

#include <thrift/TDispatchProcessor.h>
#include <thrift/async/TConcurrentClientSyncInfo.h>
#include <memory>
#include "distributed_types.h"

namespace openstars { namespace distributed {

#ifdef _MSC_VER
  #pragma warning( push )
  #pragma warning (disable : 4250 ) //inheriting methods via dominance 
#endif

class TNodeServiceBaseIf {
 public:
  virtual ~TNodeServiceBaseIf() {}
  virtual int32_t iPing(const int32_t value) = 0;
  virtual TSyncTransactionIDType startSyncTo(const TBackendInfo& desNode) = 0;
  virtual void getSyncStatus(TDataMovingStatus& _return, const TSyncTransactionIDType tid) = 0;
};

class TNodeServiceBaseIfFactory {
 public:
  typedef TNodeServiceBaseIf Handler;

  virtual ~TNodeServiceBaseIfFactory() {}

  virtual TNodeServiceBaseIf* getHandler(const ::apache::thrift::TConnectionInfo& connInfo) = 0;
  virtual void releaseHandler(TNodeServiceBaseIf* /* handler */) = 0;
  };

class TNodeServiceBaseIfSingletonFactory : virtual public TNodeServiceBaseIfFactory {
 public:
  TNodeServiceBaseIfSingletonFactory(const ::std::shared_ptr<TNodeServiceBaseIf>& iface) : iface_(iface) {}
  virtual ~TNodeServiceBaseIfSingletonFactory() {}

  virtual TNodeServiceBaseIf* getHandler(const ::apache::thrift::TConnectionInfo&) override {
    return iface_.get();
  }
  virtual void releaseHandler(TNodeServiceBaseIf* /* handler */) override {}

 protected:
  ::std::shared_ptr<TNodeServiceBaseIf> iface_;
};

class TNodeServiceBaseNull : virtual public TNodeServiceBaseIf {
 public:
  virtual ~TNodeServiceBaseNull() {}
  int32_t iPing(const int32_t /* value */) override {
    int32_t _return = 0;
    return _return;
  }
  TSyncTransactionIDType startSyncTo(const TBackendInfo& /* desNode */) override {
    TSyncTransactionIDType _return = 0;
    return _return;
  }
  void getSyncStatus(TDataMovingStatus& /* _return */, const TSyncTransactionIDType /* tid */) override {
    return;
  }
};

typedef struct _TNodeServiceBase_iPing_args__isset {
  _TNodeServiceBase_iPing_args__isset() : value(false) {}
  bool value :1;
} _TNodeServiceBase_iPing_args__isset;

class TNodeServiceBase_iPing_args {
 public:

  TNodeServiceBase_iPing_args(const TNodeServiceBase_iPing_args&) noexcept;
  TNodeServiceBase_iPing_args& operator=(const TNodeServiceBase_iPing_args&) noexcept;
  TNodeServiceBase_iPing_args() noexcept
                              : value(0) {
  }

  virtual ~TNodeServiceBase_iPing_args() noexcept;
  int32_t value;

  _TNodeServiceBase_iPing_args__isset __isset;

  void __set_value(const int32_t val);

  bool operator == (const TNodeServiceBase_iPing_args & rhs) const
  {
    if (!(value == rhs.value))
      return false;
    return true;
  }
  bool operator != (const TNodeServiceBase_iPing_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const TNodeServiceBase_iPing_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class TNodeServiceBase_iPing_pargs {
 public:


  virtual ~TNodeServiceBase_iPing_pargs() noexcept;
  const int32_t* value;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _TNodeServiceBase_iPing_result__isset {
  _TNodeServiceBase_iPing_result__isset() : success(false) {}
  bool success :1;
} _TNodeServiceBase_iPing_result__isset;

class TNodeServiceBase_iPing_result {
 public:

  TNodeServiceBase_iPing_result(const TNodeServiceBase_iPing_result&) noexcept;
  TNodeServiceBase_iPing_result& operator=(const TNodeServiceBase_iPing_result&) noexcept;
  TNodeServiceBase_iPing_result() noexcept
                                : success(0) {
  }

  virtual ~TNodeServiceBase_iPing_result() noexcept;
  int32_t success;

  _TNodeServiceBase_iPing_result__isset __isset;

  void __set_success(const int32_t val);

  bool operator == (const TNodeServiceBase_iPing_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    return true;
  }
  bool operator != (const TNodeServiceBase_iPing_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const TNodeServiceBase_iPing_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _TNodeServiceBase_iPing_presult__isset {
  _TNodeServiceBase_iPing_presult__isset() : success(false) {}
  bool success :1;
} _TNodeServiceBase_iPing_presult__isset;

class TNodeServiceBase_iPing_presult {
 public:


  virtual ~TNodeServiceBase_iPing_presult() noexcept;
  int32_t* success;

  _TNodeServiceBase_iPing_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

typedef struct _TNodeServiceBase_startSyncTo_args__isset {
  _TNodeServiceBase_startSyncTo_args__isset() : desNode(false) {}
  bool desNode :1;
} _TNodeServiceBase_startSyncTo_args__isset;

class TNodeServiceBase_startSyncTo_args {
 public:

  TNodeServiceBase_startSyncTo_args(const TNodeServiceBase_startSyncTo_args&);
  TNodeServiceBase_startSyncTo_args& operator=(const TNodeServiceBase_startSyncTo_args&);
  TNodeServiceBase_startSyncTo_args() noexcept {
  }

  virtual ~TNodeServiceBase_startSyncTo_args() noexcept;
  TBackendInfo desNode;

  _TNodeServiceBase_startSyncTo_args__isset __isset;

  void __set_desNode(const TBackendInfo& val);

  bool operator == (const TNodeServiceBase_startSyncTo_args & rhs) const
  {
    if (!(desNode == rhs.desNode))
      return false;
    return true;
  }
  bool operator != (const TNodeServiceBase_startSyncTo_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const TNodeServiceBase_startSyncTo_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class TNodeServiceBase_startSyncTo_pargs {
 public:


  virtual ~TNodeServiceBase_startSyncTo_pargs() noexcept;
  const TBackendInfo* desNode;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _TNodeServiceBase_startSyncTo_result__isset {
  _TNodeServiceBase_startSyncTo_result__isset() : success(false) {}
  bool success :1;
} _TNodeServiceBase_startSyncTo_result__isset;

class TNodeServiceBase_startSyncTo_result {
 public:

  TNodeServiceBase_startSyncTo_result(const TNodeServiceBase_startSyncTo_result&) noexcept;
  TNodeServiceBase_startSyncTo_result& operator=(const TNodeServiceBase_startSyncTo_result&) noexcept;
  TNodeServiceBase_startSyncTo_result() noexcept
                                      : success(0) {
  }

  virtual ~TNodeServiceBase_startSyncTo_result() noexcept;
  TSyncTransactionIDType success;

  _TNodeServiceBase_startSyncTo_result__isset __isset;

  void __set_success(const TSyncTransactionIDType val);

  bool operator == (const TNodeServiceBase_startSyncTo_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    return true;
  }
  bool operator != (const TNodeServiceBase_startSyncTo_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const TNodeServiceBase_startSyncTo_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _TNodeServiceBase_startSyncTo_presult__isset {
  _TNodeServiceBase_startSyncTo_presult__isset() : success(false) {}
  bool success :1;
} _TNodeServiceBase_startSyncTo_presult__isset;

class TNodeServiceBase_startSyncTo_presult {
 public:


  virtual ~TNodeServiceBase_startSyncTo_presult() noexcept;
  TSyncTransactionIDType* success;

  _TNodeServiceBase_startSyncTo_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

typedef struct _TNodeServiceBase_getSyncStatus_args__isset {
  _TNodeServiceBase_getSyncStatus_args__isset() : tid(false) {}
  bool tid :1;
} _TNodeServiceBase_getSyncStatus_args__isset;

class TNodeServiceBase_getSyncStatus_args {
 public:

  TNodeServiceBase_getSyncStatus_args(const TNodeServiceBase_getSyncStatus_args&) noexcept;
  TNodeServiceBase_getSyncStatus_args& operator=(const TNodeServiceBase_getSyncStatus_args&) noexcept;
  TNodeServiceBase_getSyncStatus_args() noexcept
                                      : tid(0) {
  }

  virtual ~TNodeServiceBase_getSyncStatus_args() noexcept;
  TSyncTransactionIDType tid;

  _TNodeServiceBase_getSyncStatus_args__isset __isset;

  void __set_tid(const TSyncTransactionIDType val);

  bool operator == (const TNodeServiceBase_getSyncStatus_args & rhs) const
  {
    if (!(tid == rhs.tid))
      return false;
    return true;
  }
  bool operator != (const TNodeServiceBase_getSyncStatus_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const TNodeServiceBase_getSyncStatus_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class TNodeServiceBase_getSyncStatus_pargs {
 public:


  virtual ~TNodeServiceBase_getSyncStatus_pargs() noexcept;
  const TSyncTransactionIDType* tid;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _TNodeServiceBase_getSyncStatus_result__isset {
  _TNodeServiceBase_getSyncStatus_result__isset() : success(false) {}
  bool success :1;
} _TNodeServiceBase_getSyncStatus_result__isset;

class TNodeServiceBase_getSyncStatus_result {
 public:

  TNodeServiceBase_getSyncStatus_result(const TNodeServiceBase_getSyncStatus_result&) noexcept;
  TNodeServiceBase_getSyncStatus_result& operator=(const TNodeServiceBase_getSyncStatus_result&) noexcept;
  TNodeServiceBase_getSyncStatus_result() noexcept {
  }

  virtual ~TNodeServiceBase_getSyncStatus_result() noexcept;
  TDataMovingStatus success;

  _TNodeServiceBase_getSyncStatus_result__isset __isset;

  void __set_success(const TDataMovingStatus& val);

  bool operator == (const TNodeServiceBase_getSyncStatus_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    return true;
  }
  bool operator != (const TNodeServiceBase_getSyncStatus_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const TNodeServiceBase_getSyncStatus_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _TNodeServiceBase_getSyncStatus_presult__isset {
  _TNodeServiceBase_getSyncStatus_presult__isset() : success(false) {}
  bool success :1;
} _TNodeServiceBase_getSyncStatus_presult__isset;

class TNodeServiceBase_getSyncStatus_presult {
 public:


  virtual ~TNodeServiceBase_getSyncStatus_presult() noexcept;
  TDataMovingStatus* success;

  _TNodeServiceBase_getSyncStatus_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

class TNodeServiceBaseClient : virtual public TNodeServiceBaseIf {
 public:
  TNodeServiceBaseClient(std::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) {
    setProtocol(prot);
  }
  TNodeServiceBaseClient(std::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, std::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) {
    setProtocol(iprot,oprot);
  }
 private:
  void setProtocol(std::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) {
  setProtocol(prot,prot);
  }
  void setProtocol(std::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, std::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) {
    piprot_=iprot;
    poprot_=oprot;
    iprot_ = iprot.get();
    oprot_ = oprot.get();
  }
 public:
  std::shared_ptr< ::apache::thrift::protocol::TProtocol> getInputProtocol() {
    return piprot_;
  }
  std::shared_ptr< ::apache::thrift::protocol::TProtocol> getOutputProtocol() {
    return poprot_;
  }
  int32_t iPing(const int32_t value) override;
  void send_iPing(const int32_t value);
  int32_t recv_iPing();
  TSyncTransactionIDType startSyncTo(const TBackendInfo& desNode) override;
  void send_startSyncTo(const TBackendInfo& desNode);
  TSyncTransactionIDType recv_startSyncTo();
  void getSyncStatus(TDataMovingStatus& _return, const TSyncTransactionIDType tid) override;
  void send_getSyncStatus(const TSyncTransactionIDType tid);
  void recv_getSyncStatus(TDataMovingStatus& _return);
 protected:
  std::shared_ptr< ::apache::thrift::protocol::TProtocol> piprot_;
  std::shared_ptr< ::apache::thrift::protocol::TProtocol> poprot_;
  ::apache::thrift::protocol::TProtocol* iprot_;
  ::apache::thrift::protocol::TProtocol* oprot_;
};

class TNodeServiceBaseProcessor : public ::apache::thrift::TDispatchProcessor {
 protected:
  ::std::shared_ptr<TNodeServiceBaseIf> iface_;
  virtual bool dispatchCall(::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, const std::string& fname, int32_t seqid, void* callContext) override;
 private:
  typedef  void (TNodeServiceBaseProcessor::*ProcessFunction)(int32_t, ::apache::thrift::protocol::TProtocol*, ::apache::thrift::protocol::TProtocol*, void*);
  typedef std::map<std::string, ProcessFunction> ProcessMap;
  ProcessMap processMap_;
  void process_iPing(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
  void process_startSyncTo(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
  void process_getSyncStatus(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
 public:
  TNodeServiceBaseProcessor(::std::shared_ptr<TNodeServiceBaseIf> iface) :
    iface_(iface) {
    processMap_["iPing"] = &TNodeServiceBaseProcessor::process_iPing;
    processMap_["startSyncTo"] = &TNodeServiceBaseProcessor::process_startSyncTo;
    processMap_["getSyncStatus"] = &TNodeServiceBaseProcessor::process_getSyncStatus;
  }

  virtual ~TNodeServiceBaseProcessor() {}
};

class TNodeServiceBaseProcessorFactory : public ::apache::thrift::TProcessorFactory {
 public:
  TNodeServiceBaseProcessorFactory(const ::std::shared_ptr< TNodeServiceBaseIfFactory >& handlerFactory) noexcept :
      handlerFactory_(handlerFactory) {}

  ::std::shared_ptr< ::apache::thrift::TProcessor > getProcessor(const ::apache::thrift::TConnectionInfo& connInfo) override;

 protected:
  ::std::shared_ptr< TNodeServiceBaseIfFactory > handlerFactory_;
};

class TNodeServiceBaseMultiface : virtual public TNodeServiceBaseIf {
 public:
  TNodeServiceBaseMultiface(std::vector<std::shared_ptr<TNodeServiceBaseIf> >& ifaces) : ifaces_(ifaces) {
  }
  virtual ~TNodeServiceBaseMultiface() {}
 protected:
  std::vector<std::shared_ptr<TNodeServiceBaseIf> > ifaces_;
  TNodeServiceBaseMultiface() {}
  void add(::std::shared_ptr<TNodeServiceBaseIf> iface) {
    ifaces_.push_back(iface);
  }
 public:
  int32_t iPing(const int32_t value) override {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->iPing(value);
    }
    return ifaces_[i]->iPing(value);
  }

  TSyncTransactionIDType startSyncTo(const TBackendInfo& desNode) override {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->startSyncTo(desNode);
    }
    return ifaces_[i]->startSyncTo(desNode);
  }

  void getSyncStatus(TDataMovingStatus& _return, const TSyncTransactionIDType tid) override {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->getSyncStatus(_return, tid);
    }
    ifaces_[i]->getSyncStatus(_return, tid);
    return;
  }

};

// The 'concurrent' client is a thread safe client that correctly handles
// out of order responses.  It is slower than the regular client, so should
// only be used when you need to share a connection among multiple threads
class TNodeServiceBaseConcurrentClient : virtual public TNodeServiceBaseIf {
 public:
  TNodeServiceBaseConcurrentClient(std::shared_ptr< ::apache::thrift::protocol::TProtocol> prot, std::shared_ptr<::apache::thrift::async::TConcurrentClientSyncInfo> sync) : sync_(sync)
{
    setProtocol(prot);
  }
  TNodeServiceBaseConcurrentClient(std::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, std::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot, std::shared_ptr<::apache::thrift::async::TConcurrentClientSyncInfo> sync) : sync_(sync)
{
    setProtocol(iprot,oprot);
  }
 private:
  void setProtocol(std::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) {
  setProtocol(prot,prot);
  }
  void setProtocol(std::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, std::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) {
    piprot_=iprot;
    poprot_=oprot;
    iprot_ = iprot.get();
    oprot_ = oprot.get();
  }
 public:
  std::shared_ptr< ::apache::thrift::protocol::TProtocol> getInputProtocol() {
    return piprot_;
  }
  std::shared_ptr< ::apache::thrift::protocol::TProtocol> getOutputProtocol() {
    return poprot_;
  }
  int32_t iPing(const int32_t value) override;
  int32_t send_iPing(const int32_t value);
  int32_t recv_iPing(const int32_t seqid);
  TSyncTransactionIDType startSyncTo(const TBackendInfo& desNode) override;
  int32_t send_startSyncTo(const TBackendInfo& desNode);
  TSyncTransactionIDType recv_startSyncTo(const int32_t seqid);
  void getSyncStatus(TDataMovingStatus& _return, const TSyncTransactionIDType tid) override;
  int32_t send_getSyncStatus(const TSyncTransactionIDType tid);
  void recv_getSyncStatus(TDataMovingStatus& _return, const int32_t seqid);
 protected:
  std::shared_ptr< ::apache::thrift::protocol::TProtocol> piprot_;
  std::shared_ptr< ::apache::thrift::protocol::TProtocol> poprot_;
  ::apache::thrift::protocol::TProtocol* iprot_;
  ::apache::thrift::protocol::TProtocol* oprot_;
  std::shared_ptr<::apache::thrift::async::TConcurrentClientSyncInfo> sync_;
};

#ifdef _MSC_VER
  #pragma warning( pop )
#endif

}} // namespace

#endif
