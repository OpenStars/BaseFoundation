/**
 * Autogenerated by Thrift Compiler (0.16.0)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#include "monitor_types.h"

#include <algorithm>
#include <ostream>

#include <thrift/TToString.h>

namespace openstars { namespace base { namespace monitor {


cpuStat::~cpuStat() noexcept {
}


void cpuStat::__set_userCPU(const int32_t val) {
  this->userCPU = val;
}

void cpuStat::__set_kernelCPU(const int32_t val) {
  this->kernelCPU = val;
}

void cpuStat::__set_idleCPU(const int32_t val) {
  this->idleCPU = val;
}

void cpuStat::__set_iowaitCPU(const int32_t val) {
  this->iowaitCPU = val;
}

void cpuStat::__set_swapCPU(const int32_t val) {
  this->swapCPU = val;
}

void cpuStat::__set_niceCPU(const int32_t val) {
  this->niceCPU = val;
}

void cpuStat::__set_totalCPU(const int32_t val) {
  this->totalCPU = val;
}
std::ostream& operator<<(std::ostream& out, const cpuStat& obj)
{
  obj.printTo(out);
  return out;
}


uint32_t cpuStat::read(::apache::thrift::protocol::TProtocol* iprot) {

  ::apache::thrift::protocol::TInputRecursionTracker tracker(*iprot);
  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;


  while (true)
  {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == ::apache::thrift::protocol::T_STOP) {
      break;
    }
    switch (fid)
    {
      case 1:
        if (ftype == ::apache::thrift::protocol::T_I32) {
          xfer += iprot->readI32(this->userCPU);
          this->__isset.userCPU = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 2:
        if (ftype == ::apache::thrift::protocol::T_I32) {
          xfer += iprot->readI32(this->kernelCPU);
          this->__isset.kernelCPU = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 3:
        if (ftype == ::apache::thrift::protocol::T_I32) {
          xfer += iprot->readI32(this->idleCPU);
          this->__isset.idleCPU = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 4:
        if (ftype == ::apache::thrift::protocol::T_I32) {
          xfer += iprot->readI32(this->iowaitCPU);
          this->__isset.iowaitCPU = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 5:
        if (ftype == ::apache::thrift::protocol::T_I32) {
          xfer += iprot->readI32(this->swapCPU);
          this->__isset.swapCPU = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 6:
        if (ftype == ::apache::thrift::protocol::T_I32) {
          xfer += iprot->readI32(this->niceCPU);
          this->__isset.niceCPU = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 7:
        if (ftype == ::apache::thrift::protocol::T_I32) {
          xfer += iprot->readI32(this->totalCPU);
          this->__isset.totalCPU = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      default:
        xfer += iprot->skip(ftype);
        break;
    }
    xfer += iprot->readFieldEnd();
  }

  xfer += iprot->readStructEnd();

  return xfer;
}

uint32_t cpuStat::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  ::apache::thrift::protocol::TOutputRecursionTracker tracker(*oprot);
  xfer += oprot->writeStructBegin("cpuStat");

  xfer += oprot->writeFieldBegin("userCPU", ::apache::thrift::protocol::T_I32, 1);
  xfer += oprot->writeI32(this->userCPU);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("kernelCPU", ::apache::thrift::protocol::T_I32, 2);
  xfer += oprot->writeI32(this->kernelCPU);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("idleCPU", ::apache::thrift::protocol::T_I32, 3);
  xfer += oprot->writeI32(this->idleCPU);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("iowaitCPU", ::apache::thrift::protocol::T_I32, 4);
  xfer += oprot->writeI32(this->iowaitCPU);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("swapCPU", ::apache::thrift::protocol::T_I32, 5);
  xfer += oprot->writeI32(this->swapCPU);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("niceCPU", ::apache::thrift::protocol::T_I32, 6);
  xfer += oprot->writeI32(this->niceCPU);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("totalCPU", ::apache::thrift::protocol::T_I32, 7);
  xfer += oprot->writeI32(this->totalCPU);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  return xfer;
}

void swap(cpuStat &a, cpuStat &b) {
  using ::std::swap;
  swap(a.userCPU, b.userCPU);
  swap(a.kernelCPU, b.kernelCPU);
  swap(a.idleCPU, b.idleCPU);
  swap(a.iowaitCPU, b.iowaitCPU);
  swap(a.swapCPU, b.swapCPU);
  swap(a.niceCPU, b.niceCPU);
  swap(a.totalCPU, b.totalCPU);
  swap(a.__isset, b.__isset);
}

cpuStat::cpuStat(const cpuStat& other0) noexcept {
  userCPU = other0.userCPU;
  kernelCPU = other0.kernelCPU;
  idleCPU = other0.idleCPU;
  iowaitCPU = other0.iowaitCPU;
  swapCPU = other0.swapCPU;
  niceCPU = other0.niceCPU;
  totalCPU = other0.totalCPU;
  __isset = other0.__isset;
}
cpuStat& cpuStat::operator=(const cpuStat& other1) noexcept {
  userCPU = other1.userCPU;
  kernelCPU = other1.kernelCPU;
  idleCPU = other1.idleCPU;
  iowaitCPU = other1.iowaitCPU;
  swapCPU = other1.swapCPU;
  niceCPU = other1.niceCPU;
  totalCPU = other1.totalCPU;
  __isset = other1.__isset;
  return *this;
}
void cpuStat::printTo(std::ostream& out) const {
  using ::apache::thrift::to_string;
  out << "cpuStat(";
  out << "userCPU=" << to_string(userCPU);
  out << ", " << "kernelCPU=" << to_string(kernelCPU);
  out << ", " << "idleCPU=" << to_string(idleCPU);
  out << ", " << "iowaitCPU=" << to_string(iowaitCPU);
  out << ", " << "swapCPU=" << to_string(swapCPU);
  out << ", " << "niceCPU=" << to_string(niceCPU);
  out << ", " << "totalCPU=" << to_string(totalCPU);
  out << ")";
}


memoryStat::~memoryStat() noexcept {
}


void memoryStat::__set_totalMem(const int64_t val) {
  this->totalMem = val;
}

void memoryStat::__set_freeMem(const int64_t val) {
  this->freeMem = val;
}

void memoryStat::__set_usedMem(const int64_t val) {
  this->usedMem = val;
}

void memoryStat::__set_cacheMem(const int64_t val) {
  this->cacheMem = val;
}
std::ostream& operator<<(std::ostream& out, const memoryStat& obj)
{
  obj.printTo(out);
  return out;
}


uint32_t memoryStat::read(::apache::thrift::protocol::TProtocol* iprot) {

  ::apache::thrift::protocol::TInputRecursionTracker tracker(*iprot);
  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;


  while (true)
  {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == ::apache::thrift::protocol::T_STOP) {
      break;
    }
    switch (fid)
    {
      case 1:
        if (ftype == ::apache::thrift::protocol::T_I64) {
          xfer += iprot->readI64(this->totalMem);
          this->__isset.totalMem = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 2:
        if (ftype == ::apache::thrift::protocol::T_I64) {
          xfer += iprot->readI64(this->freeMem);
          this->__isset.freeMem = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 3:
        if (ftype == ::apache::thrift::protocol::T_I64) {
          xfer += iprot->readI64(this->usedMem);
          this->__isset.usedMem = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 4:
        if (ftype == ::apache::thrift::protocol::T_I64) {
          xfer += iprot->readI64(this->cacheMem);
          this->__isset.cacheMem = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      default:
        xfer += iprot->skip(ftype);
        break;
    }
    xfer += iprot->readFieldEnd();
  }

  xfer += iprot->readStructEnd();

  return xfer;
}

uint32_t memoryStat::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  ::apache::thrift::protocol::TOutputRecursionTracker tracker(*oprot);
  xfer += oprot->writeStructBegin("memoryStat");

  xfer += oprot->writeFieldBegin("totalMem", ::apache::thrift::protocol::T_I64, 1);
  xfer += oprot->writeI64(this->totalMem);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("freeMem", ::apache::thrift::protocol::T_I64, 2);
  xfer += oprot->writeI64(this->freeMem);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("usedMem", ::apache::thrift::protocol::T_I64, 3);
  xfer += oprot->writeI64(this->usedMem);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("cacheMem", ::apache::thrift::protocol::T_I64, 4);
  xfer += oprot->writeI64(this->cacheMem);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  return xfer;
}

void swap(memoryStat &a, memoryStat &b) {
  using ::std::swap;
  swap(a.totalMem, b.totalMem);
  swap(a.freeMem, b.freeMem);
  swap(a.usedMem, b.usedMem);
  swap(a.cacheMem, b.cacheMem);
  swap(a.__isset, b.__isset);
}

memoryStat::memoryStat(const memoryStat& other2) noexcept {
  totalMem = other2.totalMem;
  freeMem = other2.freeMem;
  usedMem = other2.usedMem;
  cacheMem = other2.cacheMem;
  __isset = other2.__isset;
}
memoryStat& memoryStat::operator=(const memoryStat& other3) noexcept {
  totalMem = other3.totalMem;
  freeMem = other3.freeMem;
  usedMem = other3.usedMem;
  cacheMem = other3.cacheMem;
  __isset = other3.__isset;
  return *this;
}
void memoryStat::printTo(std::ostream& out) const {
  using ::apache::thrift::to_string;
  out << "memoryStat(";
  out << "totalMem=" << to_string(totalMem);
  out << ", " << "freeMem=" << to_string(freeMem);
  out << ", " << "usedMem=" << to_string(usedMem);
  out << ", " << "cacheMem=" << to_string(cacheMem);
  out << ")";
}


systemLoad::~systemLoad() noexcept {
}


void systemLoad::__set_load1m(const double val) {
  this->load1m = val;
}

void systemLoad::__set_load5m(const double val) {
  this->load5m = val;
}

void systemLoad::__set_load15m(const double val) {
  this->load15m = val;
}
std::ostream& operator<<(std::ostream& out, const systemLoad& obj)
{
  obj.printTo(out);
  return out;
}


uint32_t systemLoad::read(::apache::thrift::protocol::TProtocol* iprot) {

  ::apache::thrift::protocol::TInputRecursionTracker tracker(*iprot);
  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;


  while (true)
  {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == ::apache::thrift::protocol::T_STOP) {
      break;
    }
    switch (fid)
    {
      case 1:
        if (ftype == ::apache::thrift::protocol::T_DOUBLE) {
          xfer += iprot->readDouble(this->load1m);
          this->__isset.load1m = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 2:
        if (ftype == ::apache::thrift::protocol::T_DOUBLE) {
          xfer += iprot->readDouble(this->load5m);
          this->__isset.load5m = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 3:
        if (ftype == ::apache::thrift::protocol::T_DOUBLE) {
          xfer += iprot->readDouble(this->load15m);
          this->__isset.load15m = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      default:
        xfer += iprot->skip(ftype);
        break;
    }
    xfer += iprot->readFieldEnd();
  }

  xfer += iprot->readStructEnd();

  return xfer;
}

uint32_t systemLoad::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  ::apache::thrift::protocol::TOutputRecursionTracker tracker(*oprot);
  xfer += oprot->writeStructBegin("systemLoad");

  xfer += oprot->writeFieldBegin("load1m", ::apache::thrift::protocol::T_DOUBLE, 1);
  xfer += oprot->writeDouble(this->load1m);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("load5m", ::apache::thrift::protocol::T_DOUBLE, 2);
  xfer += oprot->writeDouble(this->load5m);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("load15m", ::apache::thrift::protocol::T_DOUBLE, 3);
  xfer += oprot->writeDouble(this->load15m);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  return xfer;
}

void swap(systemLoad &a, systemLoad &b) {
  using ::std::swap;
  swap(a.load1m, b.load1m);
  swap(a.load5m, b.load5m);
  swap(a.load15m, b.load15m);
  swap(a.__isset, b.__isset);
}

systemLoad::systemLoad(const systemLoad& other4) noexcept {
  load1m = other4.load1m;
  load5m = other4.load5m;
  load15m = other4.load15m;
  __isset = other4.__isset;
}
systemLoad& systemLoad::operator=(const systemLoad& other5) noexcept {
  load1m = other5.load1m;
  load5m = other5.load5m;
  load15m = other5.load15m;
  __isset = other5.__isset;
  return *this;
}
void systemLoad::printTo(std::ostream& out) const {
  using ::apache::thrift::to_string;
  out << "systemLoad(";
  out << "load1m=" << to_string(load1m);
  out << ", " << "load5m=" << to_string(load5m);
  out << ", " << "load15m=" << to_string(load15m);
  out << ")";
}


diskStat::~diskStat() noexcept {
}


void diskStat::__set_readSpeed(const int64_t val) {
  this->readSpeed = val;
}

void diskStat::__set_writeSpeed(const int64_t val) {
  this->writeSpeed = val;
}
std::ostream& operator<<(std::ostream& out, const diskStat& obj)
{
  obj.printTo(out);
  return out;
}


uint32_t diskStat::read(::apache::thrift::protocol::TProtocol* iprot) {

  ::apache::thrift::protocol::TInputRecursionTracker tracker(*iprot);
  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;


  while (true)
  {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == ::apache::thrift::protocol::T_STOP) {
      break;
    }
    switch (fid)
    {
      case 1:
        if (ftype == ::apache::thrift::protocol::T_I64) {
          xfer += iprot->readI64(this->readSpeed);
          this->__isset.readSpeed = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 2:
        if (ftype == ::apache::thrift::protocol::T_I64) {
          xfer += iprot->readI64(this->writeSpeed);
          this->__isset.writeSpeed = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      default:
        xfer += iprot->skip(ftype);
        break;
    }
    xfer += iprot->readFieldEnd();
  }

  xfer += iprot->readStructEnd();

  return xfer;
}

uint32_t diskStat::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  ::apache::thrift::protocol::TOutputRecursionTracker tracker(*oprot);
  xfer += oprot->writeStructBegin("diskStat");

  xfer += oprot->writeFieldBegin("readSpeed", ::apache::thrift::protocol::T_I64, 1);
  xfer += oprot->writeI64(this->readSpeed);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("writeSpeed", ::apache::thrift::protocol::T_I64, 2);
  xfer += oprot->writeI64(this->writeSpeed);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  return xfer;
}

void swap(diskStat &a, diskStat &b) {
  using ::std::swap;
  swap(a.readSpeed, b.readSpeed);
  swap(a.writeSpeed, b.writeSpeed);
  swap(a.__isset, b.__isset);
}

diskStat::diskStat(const diskStat& other6) noexcept {
  readSpeed = other6.readSpeed;
  writeSpeed = other6.writeSpeed;
  __isset = other6.__isset;
}
diskStat& diskStat::operator=(const diskStat& other7) noexcept {
  readSpeed = other7.readSpeed;
  writeSpeed = other7.writeSpeed;
  __isset = other7.__isset;
  return *this;
}
void diskStat::printTo(std::ostream& out) const {
  using ::apache::thrift::to_string;
  out << "diskStat(";
  out << "readSpeed=" << to_string(readSpeed);
  out << ", " << "writeSpeed=" << to_string(writeSpeed);
  out << ")";
}


networkStat::~networkStat() noexcept {
}


void networkStat::__set_readSpeed(const int64_t val) {
  this->readSpeed = val;
}

void networkStat::__set_writeSpeed(const int64_t val) {
  this->writeSpeed = val;
}
std::ostream& operator<<(std::ostream& out, const networkStat& obj)
{
  obj.printTo(out);
  return out;
}


uint32_t networkStat::read(::apache::thrift::protocol::TProtocol* iprot) {

  ::apache::thrift::protocol::TInputRecursionTracker tracker(*iprot);
  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;


  while (true)
  {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == ::apache::thrift::protocol::T_STOP) {
      break;
    }
    switch (fid)
    {
      case 1:
        if (ftype == ::apache::thrift::protocol::T_I64) {
          xfer += iprot->readI64(this->readSpeed);
          this->__isset.readSpeed = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 2:
        if (ftype == ::apache::thrift::protocol::T_I64) {
          xfer += iprot->readI64(this->writeSpeed);
          this->__isset.writeSpeed = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      default:
        xfer += iprot->skip(ftype);
        break;
    }
    xfer += iprot->readFieldEnd();
  }

  xfer += iprot->readStructEnd();

  return xfer;
}

uint32_t networkStat::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  ::apache::thrift::protocol::TOutputRecursionTracker tracker(*oprot);
  xfer += oprot->writeStructBegin("networkStat");

  xfer += oprot->writeFieldBegin("readSpeed", ::apache::thrift::protocol::T_I64, 1);
  xfer += oprot->writeI64(this->readSpeed);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("writeSpeed", ::apache::thrift::protocol::T_I64, 2);
  xfer += oprot->writeI64(this->writeSpeed);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  return xfer;
}

void swap(networkStat &a, networkStat &b) {
  using ::std::swap;
  swap(a.readSpeed, b.readSpeed);
  swap(a.writeSpeed, b.writeSpeed);
  swap(a.__isset, b.__isset);
}

networkStat::networkStat(const networkStat& other8) noexcept {
  readSpeed = other8.readSpeed;
  writeSpeed = other8.writeSpeed;
  __isset = other8.__isset;
}
networkStat& networkStat::operator=(const networkStat& other9) noexcept {
  readSpeed = other9.readSpeed;
  writeSpeed = other9.writeSpeed;
  __isset = other9.__isset;
  return *this;
}
void networkStat::printTo(std::ostream& out) const {
  using ::apache::thrift::to_string;
  out << "networkStat(";
  out << "readSpeed=" << to_string(readSpeed);
  out << ", " << "writeSpeed=" << to_string(writeSpeed);
  out << ")";
}


systemStat::~systemStat() noexcept {
}


void systemStat::__set_cpu(const cpuStat& val) {
  this->cpu = val;
}

void systemStat::__set_memory(const memoryStat& val) {
  this->memory = val;
}

void systemStat::__set_sysload(const systemLoad& val) {
  this->sysload = val;
}

void systemStat::__set_disks(const diskStats& val) {
  this->disks = val;
}

void systemStat::__set_networks(const networkStats& val) {
  this->networks = val;
}

void systemStat::__set_timestamp(const int64_t val) {
  this->timestamp = val;
}

void systemStat::__set_seconds(const int32_t val) {
  this->seconds = val;
}
std::ostream& operator<<(std::ostream& out, const systemStat& obj)
{
  obj.printTo(out);
  return out;
}


uint32_t systemStat::read(::apache::thrift::protocol::TProtocol* iprot) {

  ::apache::thrift::protocol::TInputRecursionTracker tracker(*iprot);
  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;


  while (true)
  {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == ::apache::thrift::protocol::T_STOP) {
      break;
    }
    switch (fid)
    {
      case 1:
        if (ftype == ::apache::thrift::protocol::T_STRUCT) {
          xfer += this->cpu.read(iprot);
          this->__isset.cpu = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 2:
        if (ftype == ::apache::thrift::protocol::T_STRUCT) {
          xfer += this->memory.read(iprot);
          this->__isset.memory = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 3:
        if (ftype == ::apache::thrift::protocol::T_STRUCT) {
          xfer += this->sysload.read(iprot);
          this->__isset.sysload = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 4:
        if (ftype == ::apache::thrift::protocol::T_MAP) {
          {
            this->disks.clear();
            uint32_t _size10;
            ::apache::thrift::protocol::TType _ktype11;
            ::apache::thrift::protocol::TType _vtype12;
            xfer += iprot->readMapBegin(_ktype11, _vtype12, _size10);
            uint32_t _i14;
            for (_i14 = 0; _i14 < _size10; ++_i14)
            {
              std::string _key15;
              xfer += iprot->readString(_key15);
              diskStat& _val16 = this->disks[_key15];
              xfer += _val16.read(iprot);
            }
            xfer += iprot->readMapEnd();
          }
          this->__isset.disks = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 5:
        if (ftype == ::apache::thrift::protocol::T_MAP) {
          {
            this->networks.clear();
            uint32_t _size17;
            ::apache::thrift::protocol::TType _ktype18;
            ::apache::thrift::protocol::TType _vtype19;
            xfer += iprot->readMapBegin(_ktype18, _vtype19, _size17);
            uint32_t _i21;
            for (_i21 = 0; _i21 < _size17; ++_i21)
            {
              std::string _key22;
              xfer += iprot->readString(_key22);
              networkStat& _val23 = this->networks[_key22];
              xfer += _val23.read(iprot);
            }
            xfer += iprot->readMapEnd();
          }
          this->__isset.networks = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 6:
        if (ftype == ::apache::thrift::protocol::T_I64) {
          xfer += iprot->readI64(this->timestamp);
          this->__isset.timestamp = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 7:
        if (ftype == ::apache::thrift::protocol::T_I32) {
          xfer += iprot->readI32(this->seconds);
          this->__isset.seconds = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      default:
        xfer += iprot->skip(ftype);
        break;
    }
    xfer += iprot->readFieldEnd();
  }

  xfer += iprot->readStructEnd();

  return xfer;
}

uint32_t systemStat::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  ::apache::thrift::protocol::TOutputRecursionTracker tracker(*oprot);
  xfer += oprot->writeStructBegin("systemStat");

  xfer += oprot->writeFieldBegin("cpu", ::apache::thrift::protocol::T_STRUCT, 1);
  xfer += this->cpu.write(oprot);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("memory", ::apache::thrift::protocol::T_STRUCT, 2);
  xfer += this->memory.write(oprot);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("sysload", ::apache::thrift::protocol::T_STRUCT, 3);
  xfer += this->sysload.write(oprot);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("disks", ::apache::thrift::protocol::T_MAP, 4);
  {
    xfer += oprot->writeMapBegin(::apache::thrift::protocol::T_STRING, ::apache::thrift::protocol::T_STRUCT, static_cast<uint32_t>(this->disks.size()));
    std::map<std::string, diskStat> ::const_iterator _iter24;
    for (_iter24 = this->disks.begin(); _iter24 != this->disks.end(); ++_iter24)
    {
      xfer += oprot->writeString(_iter24->first);
      xfer += _iter24->second.write(oprot);
    }
    xfer += oprot->writeMapEnd();
  }
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("networks", ::apache::thrift::protocol::T_MAP, 5);
  {
    xfer += oprot->writeMapBegin(::apache::thrift::protocol::T_STRING, ::apache::thrift::protocol::T_STRUCT, static_cast<uint32_t>(this->networks.size()));
    std::map<std::string, networkStat> ::const_iterator _iter25;
    for (_iter25 = this->networks.begin(); _iter25 != this->networks.end(); ++_iter25)
    {
      xfer += oprot->writeString(_iter25->first);
      xfer += _iter25->second.write(oprot);
    }
    xfer += oprot->writeMapEnd();
  }
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("timestamp", ::apache::thrift::protocol::T_I64, 6);
  xfer += oprot->writeI64(this->timestamp);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("seconds", ::apache::thrift::protocol::T_I32, 7);
  xfer += oprot->writeI32(this->seconds);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  return xfer;
}

void swap(systemStat &a, systemStat &b) {
  using ::std::swap;
  swap(a.cpu, b.cpu);
  swap(a.memory, b.memory);
  swap(a.sysload, b.sysload);
  swap(a.disks, b.disks);
  swap(a.networks, b.networks);
  swap(a.timestamp, b.timestamp);
  swap(a.seconds, b.seconds);
  swap(a.__isset, b.__isset);
}

systemStat::systemStat(const systemStat& other26) {
  cpu = other26.cpu;
  memory = other26.memory;
  sysload = other26.sysload;
  disks = other26.disks;
  networks = other26.networks;
  timestamp = other26.timestamp;
  seconds = other26.seconds;
  __isset = other26.__isset;
}
systemStat& systemStat::operator=(const systemStat& other27) {
  cpu = other27.cpu;
  memory = other27.memory;
  sysload = other27.sysload;
  disks = other27.disks;
  networks = other27.networks;
  timestamp = other27.timestamp;
  seconds = other27.seconds;
  __isset = other27.__isset;
  return *this;
}
void systemStat::printTo(std::ostream& out) const {
  using ::apache::thrift::to_string;
  out << "systemStat(";
  out << "cpu=" << to_string(cpu);
  out << ", " << "memory=" << to_string(memory);
  out << ", " << "sysload=" << to_string(sysload);
  out << ", " << "disks=" << to_string(disks);
  out << ", " << "networks=" << to_string(networks);
  out << ", " << "timestamp=" << to_string(timestamp);
  out << ", " << "seconds=" << to_string(seconds);
  out << ")";
}


InvalidOperation::~InvalidOperation() noexcept {
}


void InvalidOperation::__set_errorCode(const int16_t val) {
  this->errorCode = val;
}

void InvalidOperation::__set_why(const std::string& val) {
  this->why = val;
}
std::ostream& operator<<(std::ostream& out, const InvalidOperation& obj)
{
  obj.printTo(out);
  return out;
}


uint32_t InvalidOperation::read(::apache::thrift::protocol::TProtocol* iprot) {

  ::apache::thrift::protocol::TInputRecursionTracker tracker(*iprot);
  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;


  while (true)
  {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == ::apache::thrift::protocol::T_STOP) {
      break;
    }
    switch (fid)
    {
      case 1:
        if (ftype == ::apache::thrift::protocol::T_I16) {
          xfer += iprot->readI16(this->errorCode);
          this->__isset.errorCode = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 2:
        if (ftype == ::apache::thrift::protocol::T_STRING) {
          xfer += iprot->readString(this->why);
          this->__isset.why = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      default:
        xfer += iprot->skip(ftype);
        break;
    }
    xfer += iprot->readFieldEnd();
  }

  xfer += iprot->readStructEnd();

  return xfer;
}

uint32_t InvalidOperation::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  ::apache::thrift::protocol::TOutputRecursionTracker tracker(*oprot);
  xfer += oprot->writeStructBegin("InvalidOperation");

  xfer += oprot->writeFieldBegin("errorCode", ::apache::thrift::protocol::T_I16, 1);
  xfer += oprot->writeI16(this->errorCode);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("why", ::apache::thrift::protocol::T_STRING, 2);
  xfer += oprot->writeString(this->why);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  return xfer;
}

void swap(InvalidOperation &a, InvalidOperation &b) {
  using ::std::swap;
  swap(a.errorCode, b.errorCode);
  swap(a.why, b.why);
  swap(a.__isset, b.__isset);
}

InvalidOperation::InvalidOperation(const InvalidOperation& other28) : TException() {
  errorCode = other28.errorCode;
  why = other28.why;
  __isset = other28.__isset;
}
InvalidOperation& InvalidOperation::operator=(const InvalidOperation& other29) {
  errorCode = other29.errorCode;
  why = other29.why;
  __isset = other29.__isset;
  return *this;
}
void InvalidOperation::printTo(std::ostream& out) const {
  using ::apache::thrift::to_string;
  out << "InvalidOperation(";
  out << "errorCode=" << to_string(errorCode);
  out << ", " << "why=" << to_string(why);
  out << ")";
}

const char* InvalidOperation::what() const noexcept {
  try {
    std::stringstream ss;
    ss << "TException - service has thrown: " << *this;
    this->thriftTExceptionMessageHolder_ = ss.str();
    return this->thriftTExceptionMessageHolder_.c_str();
  } catch (const std::exception&) {
    return "TException - service has thrown: InvalidOperation";
  }
}

}}} // namespace
