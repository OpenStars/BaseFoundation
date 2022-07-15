/**
 * Autogenerated by Thrift Compiler (0.16.0)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#ifndef backendmonitor_TYPES_H
#define backendmonitor_TYPES_H

#include <iosfwd>

#include <thrift/Thrift.h>
#include <thrift/TApplicationException.h>
#include <thrift/TBase.h>
#include <thrift/protocol/TProtocol.h>
#include <thrift/transport/TTransport.h>

#include <functional>
#include <memory>
#include "monitor_types.h"


namespace openstars { namespace base { namespace storage { namespace monitor {

class cacheStat;

class opStat;

class storageStat;

class backendStat;

typedef struct _cacheStat__isset {
  _cacheStat__isset() : cacheType(false), cacheMaxSize(false), cacheSize(false), cacheHit(false), cacheMiss(false), cacheMemSize(false) {}
  bool cacheType :1;
  bool cacheMaxSize :1;
  bool cacheSize :1;
  bool cacheHit :1;
  bool cacheMiss :1;
  bool cacheMemSize :1;
} _cacheStat__isset;

class cacheStat : public virtual ::apache::thrift::TBase {
 public:

  cacheStat(const cacheStat&);
  cacheStat& operator=(const cacheStat&);
  cacheStat() noexcept
            : cacheType(),
              cacheMaxSize(0),
              cacheSize(0),
              cacheHit(0),
              cacheMiss(0),
              cacheMemSize(0) {
  }

  virtual ~cacheStat() noexcept;
  std::string cacheType;
  int64_t cacheMaxSize;
  int64_t cacheSize;
  int64_t cacheHit;
  int64_t cacheMiss;
  int64_t cacheMemSize;

  _cacheStat__isset __isset;

  void __set_cacheType(const std::string& val);

  void __set_cacheMaxSize(const int64_t val);

  void __set_cacheSize(const int64_t val);

  void __set_cacheHit(const int64_t val);

  void __set_cacheMiss(const int64_t val);

  void __set_cacheMemSize(const int64_t val);

  bool operator == (const cacheStat & rhs) const
  {
    if (!(cacheType == rhs.cacheType))
      return false;
    if (!(cacheMaxSize == rhs.cacheMaxSize))
      return false;
    if (!(cacheSize == rhs.cacheSize))
      return false;
    if (!(cacheHit == rhs.cacheHit))
      return false;
    if (!(cacheMiss == rhs.cacheMiss))
      return false;
    if (!(cacheMemSize == rhs.cacheMemSize))
      return false;
    return true;
  }
  bool operator != (const cacheStat &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const cacheStat & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot) override;
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const override;

  virtual void printTo(std::ostream& out) const;
};

void swap(cacheStat &a, cacheStat &b);

std::ostream& operator<<(std::ostream& out, const cacheStat& obj);

typedef struct _opStat__isset {
  _opStat__isset() : operationCount(false), cacheHit(false), persistentHit(false), excuteTime(false) {}
  bool operationCount :1;
  bool cacheHit :1;
  bool persistentHit :1;
  bool excuteTime :1;
} _opStat__isset;

class opStat : public virtual ::apache::thrift::TBase {
 public:

  opStat(const opStat&) noexcept;
  opStat& operator=(const opStat&) noexcept;
  opStat() noexcept
         : operationCount(0),
           cacheHit(0),
           persistentHit(0),
           excuteTime(0) {
  }

  virtual ~opStat() noexcept;
  int64_t operationCount;
  int64_t cacheHit;
  int64_t persistentHit;
  int64_t excuteTime;

  _opStat__isset __isset;

  void __set_operationCount(const int64_t val);

  void __set_cacheHit(const int64_t val);

  void __set_persistentHit(const int64_t val);

  void __set_excuteTime(const int64_t val);

  bool operator == (const opStat & rhs) const
  {
    if (!(operationCount == rhs.operationCount))
      return false;
    if (!(cacheHit == rhs.cacheHit))
      return false;
    if (!(persistentHit == rhs.persistentHit))
      return false;
    if (!(excuteTime == rhs.excuteTime))
      return false;
    return true;
  }
  bool operator != (const opStat &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const opStat & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot) override;
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const override;

  virtual void printTo(std::ostream& out) const;
};

void swap(opStat &a, opStat &b);

std::ostream& operator<<(std::ostream& out, const opStat& obj);

typedef struct _storageStat__isset {
  _storageStat__isset() : count(false), sizeKb(false), minSizeKb(false) {}
  bool count :1;
  bool sizeKb :1;
  bool minSizeKb :1;
} _storageStat__isset;

class storageStat : public virtual ::apache::thrift::TBase {
 public:

  storageStat(const storageStat&) noexcept;
  storageStat& operator=(const storageStat&) noexcept;
  storageStat() noexcept
              : count(0),
                sizeKb(0),
                minSizeKb(0) {
  }

  virtual ~storageStat() noexcept;
  int64_t count;
  int64_t sizeKb;
  int64_t minSizeKb;

  _storageStat__isset __isset;

  void __set_count(const int64_t val);

  void __set_sizeKb(const int64_t val);

  void __set_minSizeKb(const int64_t val);

  bool operator == (const storageStat & rhs) const
  {
    if (!(count == rhs.count))
      return false;
    if (!(sizeKb == rhs.sizeKb))
      return false;
    if (!(minSizeKb == rhs.minSizeKb))
      return false;
    return true;
  }
  bool operator != (const storageStat &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const storageStat & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot) override;
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const override;

  virtual void printTo(std::ostream& out) const;
};

void swap(storageStat &a, storageStat &b);

std::ostream& operator<<(std::ostream& out, const storageStat& obj);

typedef struct _backendStat__isset {
  _backendStat__isset() : cache(false), savingQueueSize(false), warmingQueueSize(false), readStat(false), writeStat(false), writeStorage(false), readStorage(false), processMemKb(false), processVirtKb(false), storages(false) {}
  bool cache :1;
  bool savingQueueSize :1;
  bool warmingQueueSize :1;
  bool readStat :1;
  bool writeStat :1;
  bool writeStorage :1;
  bool readStorage :1;
  bool processMemKb :1;
  bool processVirtKb :1;
  bool storages :1;
} _backendStat__isset;

class backendStat : public virtual ::apache::thrift::TBase {
 public:

  backendStat(const backendStat&);
  backendStat& operator=(const backendStat&);
  backendStat() noexcept
              : savingQueueSize(0),
                warmingQueueSize(0),
                processMemKb(0),
                processVirtKb(0) {
  }

  virtual ~backendStat() noexcept;
  cacheStat cache;
  int64_t savingQueueSize;
  int64_t warmingQueueSize;
  opStat readStat;
  opStat writeStat;
  std::vector<std::string>  writeStorage;
  std::vector<std::string>  readStorage;
  int64_t processMemKb;
  int64_t processVirtKb;
  std::map<std::string, storageStat>  storages;

  _backendStat__isset __isset;

  void __set_cache(const cacheStat& val);

  void __set_savingQueueSize(const int64_t val);

  void __set_warmingQueueSize(const int64_t val);

  void __set_readStat(const opStat& val);

  void __set_writeStat(const opStat& val);

  void __set_writeStorage(const std::vector<std::string> & val);

  void __set_readStorage(const std::vector<std::string> & val);

  void __set_processMemKb(const int64_t val);

  void __set_processVirtKb(const int64_t val);

  void __set_storages(const std::map<std::string, storageStat> & val);

  bool operator == (const backendStat & rhs) const
  {
    if (!(cache == rhs.cache))
      return false;
    if (!(savingQueueSize == rhs.savingQueueSize))
      return false;
    if (!(warmingQueueSize == rhs.warmingQueueSize))
      return false;
    if (!(readStat == rhs.readStat))
      return false;
    if (!(writeStat == rhs.writeStat))
      return false;
    if (!(writeStorage == rhs.writeStorage))
      return false;
    if (!(readStorage == rhs.readStorage))
      return false;
    if (!(processMemKb == rhs.processMemKb))
      return false;
    if (!(processVirtKb == rhs.processVirtKb))
      return false;
    if (!(storages == rhs.storages))
      return false;
    return true;
  }
  bool operator != (const backendStat &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const backendStat & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot) override;
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const override;

  virtual void printTo(std::ostream& out) const;
};

void swap(backendStat &a, backendStat &b);

std::ostream& operator<<(std::ostream& out, const backendStat& obj);

}}}} // namespace

#endif
