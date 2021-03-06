#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux
CND_DLIB_EXT=so
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/src/Caching/MemoryStats.o \
	${OBJECTDIR}/src/Distributed/BackendActiveChecker.o \
	${OBJECTDIR}/src/Distributed/BackendInfo.o \
	${OBJECTDIR}/src/Distributed/BackendManager.o \
	${OBJECTDIR}/src/Distributed/BasicProxyFactory.o \
	${OBJECTDIR}/src/Distributed/CHBackendManager.o \
	${OBJECTDIR}/src/Distributed/RepBackendManager.o \
	${OBJECTDIR}/src/Endpoint.o \
	${OBJECTDIR}/src/EndpointManager.o \
	${OBJECTDIR}/src/EtcdRegister.o \
	${OBJECTDIR}/src/Hashing/CastingHasher.o \
	${OBJECTDIR}/src/Hashing/DefaultHasher.o \
	${OBJECTDIR}/src/Hashing/MurmurHasher.o \
	${OBJECTDIR}/src/LiteEndpointManager.o \
	${OBJECTDIR}/src/NQueueCenterWorker.o \
	${OBJECTDIR}/src/NetUtil.o \
	${OBJECTDIR}/src/OpenBaseHandler.o \
	${OBJECTDIR}/src/SharedMemoryEx.o \
	${OBJECTDIR}/src/Storage/MultiKVStorage.o \
	${OBJECTDIR}/src/Storage/SnappyKVStorage.o \
	${OBJECTDIR}/src/Storage/StorageFactory.o \
	${OBJECTDIR}/src/TimeBasedLisenceManager.o \
	${OBJECTDIR}/src/Util/IDGenerator.o \
	${OBJECTDIR}/src/ZKRegister.o \
	${OBJECTDIR}/src/monitor/ServiceStatFetcher.o \
	${OBJECTDIR}/src/monitor/StatSubsystem.o \
	${OBJECTDIR}/src/monitor/TBackendLog.o \
	${OBJECTDIR}/src/monitor/TMonitorThriftHandler.o \
	${OBJECTDIR}/src/monitor/TMonitorThriftServer.o \
	${OBJECTDIR}/src/monitor/TStorageMonitorThriftHandler.o \
	${OBJECTDIR}/src/monitor/TStorageStatModule.o \
	${OBJECTDIR}/thrift/gen-cpp/MonitorReadService.o \
	${OBJECTDIR}/thrift/gen-cpp/OpenBaseService.o \
	${OBJECTDIR}/thrift/gen-cpp/StorageMonitorService.o \
	${OBJECTDIR}/thrift/gen-cpp/TBackendManagerService.o \
	${OBJECTDIR}/thrift/gen-cpp/TNodeServiceBase.o \
	${OBJECTDIR}/thrift/gen-cpp/TP2PService.o \
	${OBJECTDIR}/thrift/gen-cpp/backendmonitor_constants.o \
	${OBJECTDIR}/thrift/gen-cpp/backendmonitor_types.o \
	${OBJECTDIR}/thrift/gen-cpp/distributed_constants.o \
	${OBJECTDIR}/thrift/gen-cpp/distributed_types.o \
	${OBJECTDIR}/thrift/gen-cpp/monitor_constants.o \
	${OBJECTDIR}/thrift/gen-cpp/monitor_types.o \
	${OBJECTDIR}/thrift/gen-cpp/openbase_constants.o \
	${OBJECTDIR}/thrift/gen-cpp/openbase_types.o

# Test Directory
TESTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}/tests

# Test Files
TESTFILES= \
	${TESTDIR}/TestFiles/f2 \
	${TESTDIR}/TestFiles/f4 \
	${TESTDIR}/TestFiles/f1 \
	${TESTDIR}/TestFiles/f5 \
	${TESTDIR}/TestFiles/f6 \
	${TESTDIR}/TestFiles/zkregistertest

# Test Object Files
TESTOBJECTFILES= \
	${TESTDIR}/tests/EtcdRegTest.o \
	${TESTDIR}/tests/TestEtcdV3Client.o \
	${TESTDIR}/tests/TestZK.o \
	${TESTDIR}/tests/ZKRegisterTest.o \
	${TESTDIR}/tests/timebasedlisencemanagertest.o

# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk lib/libbasefoundation.a

lib/libbasefoundation.a: ${OBJECTFILES}
	${MKDIR} -p lib
	${RM} lib/libbasefoundation.a
	${AR} -rv lib/libbasefoundation.a ${OBJECTFILES} 
	$(RANLIB) lib/libbasefoundation.a

${OBJECTDIR}/src/Caching/MemoryStats.o: src/Caching/MemoryStats.cpp
	${MKDIR} -p ${OBJECTDIR}/src/Caching
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -DBUILD_LIBSTATGRAB -DHAVE_CONFIG_H -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/src/ -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Caching/MemoryStats.o src/Caching/MemoryStats.cpp

${OBJECTDIR}/src/Distributed/BackendActiveChecker.o: src/Distributed/BackendActiveChecker.cpp
	${MKDIR} -p ${OBJECTDIR}/src/Distributed
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -DBUILD_LIBSTATGRAB -DHAVE_CONFIG_H -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/src/ -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Distributed/BackendActiveChecker.o src/Distributed/BackendActiveChecker.cpp

${OBJECTDIR}/src/Distributed/BackendInfo.o: src/Distributed/BackendInfo.cpp
	${MKDIR} -p ${OBJECTDIR}/src/Distributed
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -DBUILD_LIBSTATGRAB -DHAVE_CONFIG_H -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/src/ -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Distributed/BackendInfo.o src/Distributed/BackendInfo.cpp

${OBJECTDIR}/src/Distributed/BackendManager.o: src/Distributed/BackendManager.cpp
	${MKDIR} -p ${OBJECTDIR}/src/Distributed
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -DBUILD_LIBSTATGRAB -DHAVE_CONFIG_H -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/src/ -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Distributed/BackendManager.o src/Distributed/BackendManager.cpp

${OBJECTDIR}/src/Distributed/BasicProxyFactory.o: src/Distributed/BasicProxyFactory.cpp
	${MKDIR} -p ${OBJECTDIR}/src/Distributed
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -DBUILD_LIBSTATGRAB -DHAVE_CONFIG_H -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/src/ -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Distributed/BasicProxyFactory.o src/Distributed/BasicProxyFactory.cpp

${OBJECTDIR}/src/Distributed/CHBackendManager.o: src/Distributed/CHBackendManager.cpp
	${MKDIR} -p ${OBJECTDIR}/src/Distributed
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -DBUILD_LIBSTATGRAB -DHAVE_CONFIG_H -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/src/ -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Distributed/CHBackendManager.o src/Distributed/CHBackendManager.cpp

${OBJECTDIR}/src/Distributed/RepBackendManager.o: src/Distributed/RepBackendManager.cpp
	${MKDIR} -p ${OBJECTDIR}/src/Distributed
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -DBUILD_LIBSTATGRAB -DHAVE_CONFIG_H -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/src/ -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Distributed/RepBackendManager.o src/Distributed/RepBackendManager.cpp

${OBJECTDIR}/src/Endpoint.o: src/Endpoint.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -DBUILD_LIBSTATGRAB -DHAVE_CONFIG_H -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/src/ -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Endpoint.o src/Endpoint.cpp

${OBJECTDIR}/src/EndpointManager.o: src/EndpointManager.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -DBUILD_LIBSTATGRAB -DHAVE_CONFIG_H -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/src/ -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/EndpointManager.o src/EndpointManager.cpp

${OBJECTDIR}/src/EtcdRegister.o: src/EtcdRegister.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -DBUILD_LIBSTATGRAB -DHAVE_CONFIG_H -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/src/ -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/EtcdRegister.o src/EtcdRegister.cpp

${OBJECTDIR}/src/Hashing/CastingHasher.o: src/Hashing/CastingHasher.cpp
	${MKDIR} -p ${OBJECTDIR}/src/Hashing
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -DBUILD_LIBSTATGRAB -DHAVE_CONFIG_H -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/src/ -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Hashing/CastingHasher.o src/Hashing/CastingHasher.cpp

${OBJECTDIR}/src/Hashing/DefaultHasher.o: src/Hashing/DefaultHasher.cpp
	${MKDIR} -p ${OBJECTDIR}/src/Hashing
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -DBUILD_LIBSTATGRAB -DHAVE_CONFIG_H -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/src/ -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Hashing/DefaultHasher.o src/Hashing/DefaultHasher.cpp

${OBJECTDIR}/src/Hashing/MurmurHasher.o: src/Hashing/MurmurHasher.cpp
	${MKDIR} -p ${OBJECTDIR}/src/Hashing
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -DBUILD_LIBSTATGRAB -DHAVE_CONFIG_H -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/src/ -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Hashing/MurmurHasher.o src/Hashing/MurmurHasher.cpp

${OBJECTDIR}/src/LiteEndpointManager.o: src/LiteEndpointManager.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -DBUILD_LIBSTATGRAB -DHAVE_CONFIG_H -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/src/ -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/LiteEndpointManager.o src/LiteEndpointManager.cpp

${OBJECTDIR}/src/NQueueCenterWorker.o: src/NQueueCenterWorker.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -DBUILD_LIBSTATGRAB -DHAVE_CONFIG_H -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/src/ -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/NQueueCenterWorker.o src/NQueueCenterWorker.cpp

${OBJECTDIR}/src/NetUtil.o: src/NetUtil.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -DBUILD_LIBSTATGRAB -DHAVE_CONFIG_H -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/src/ -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/NetUtil.o src/NetUtil.cpp

${OBJECTDIR}/src/OpenBaseHandler.o: src/OpenBaseHandler.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -DBUILD_LIBSTATGRAB -DHAVE_CONFIG_H -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/src/ -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/OpenBaseHandler.o src/OpenBaseHandler.cpp

${OBJECTDIR}/src/SharedMemoryEx.o: src/SharedMemoryEx.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -DBUILD_LIBSTATGRAB -DHAVE_CONFIG_H -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/src/ -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/SharedMemoryEx.o src/SharedMemoryEx.cpp

${OBJECTDIR}/src/Storage/MultiKVStorage.o: src/Storage/MultiKVStorage.cpp
	${MKDIR} -p ${OBJECTDIR}/src/Storage
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -DBUILD_LIBSTATGRAB -DHAVE_CONFIG_H -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/src/ -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Storage/MultiKVStorage.o src/Storage/MultiKVStorage.cpp

${OBJECTDIR}/src/Storage/SnappyKVStorage.o: src/Storage/SnappyKVStorage.cpp
	${MKDIR} -p ${OBJECTDIR}/src/Storage
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -DBUILD_LIBSTATGRAB -DHAVE_CONFIG_H -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/src/ -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Storage/SnappyKVStorage.o src/Storage/SnappyKVStorage.cpp

${OBJECTDIR}/src/Storage/StorageFactory.o: src/Storage/StorageFactory.cpp
	${MKDIR} -p ${OBJECTDIR}/src/Storage
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -DBUILD_LIBSTATGRAB -DHAVE_CONFIG_H -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/src/ -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Storage/StorageFactory.o src/Storage/StorageFactory.cpp

${OBJECTDIR}/src/TimeBasedLisenceManager.o: src/TimeBasedLisenceManager.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -DBUILD_LIBSTATGRAB -DHAVE_CONFIG_H -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/src/ -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/TimeBasedLisenceManager.o src/TimeBasedLisenceManager.cpp

${OBJECTDIR}/src/Util/IDGenerator.o: src/Util/IDGenerator.cpp
	${MKDIR} -p ${OBJECTDIR}/src/Util
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -DBUILD_LIBSTATGRAB -DHAVE_CONFIG_H -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/src/ -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Util/IDGenerator.o src/Util/IDGenerator.cpp

${OBJECTDIR}/src/ZKRegister.o: src/ZKRegister.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -DBUILD_LIBSTATGRAB -DHAVE_CONFIG_H -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/src/ -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/ZKRegister.o src/ZKRegister.cpp

${OBJECTDIR}/src/monitor/ServiceStatFetcher.o: src/monitor/ServiceStatFetcher.cpp
	${MKDIR} -p ${OBJECTDIR}/src/monitor
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -DBUILD_LIBSTATGRAB -DHAVE_CONFIG_H -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/src/ -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/monitor/ServiceStatFetcher.o src/monitor/ServiceStatFetcher.cpp

${OBJECTDIR}/src/monitor/StatSubsystem.o: src/monitor/StatSubsystem.cpp
	${MKDIR} -p ${OBJECTDIR}/src/monitor
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -DBUILD_LIBSTATGRAB -DHAVE_CONFIG_H -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/src/ -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/monitor/StatSubsystem.o src/monitor/StatSubsystem.cpp

${OBJECTDIR}/src/monitor/TBackendLog.o: src/monitor/TBackendLog.cpp
	${MKDIR} -p ${OBJECTDIR}/src/monitor
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -DBUILD_LIBSTATGRAB -DHAVE_CONFIG_H -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/src/ -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/monitor/TBackendLog.o src/monitor/TBackendLog.cpp

${OBJECTDIR}/src/monitor/TMonitorThriftHandler.o: src/monitor/TMonitorThriftHandler.cpp
	${MKDIR} -p ${OBJECTDIR}/src/monitor
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -DBUILD_LIBSTATGRAB -DHAVE_CONFIG_H -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/src/ -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/monitor/TMonitorThriftHandler.o src/monitor/TMonitorThriftHandler.cpp

${OBJECTDIR}/src/monitor/TMonitorThriftServer.o: src/monitor/TMonitorThriftServer.cpp
	${MKDIR} -p ${OBJECTDIR}/src/monitor
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -DBUILD_LIBSTATGRAB -DHAVE_CONFIG_H -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/src/ -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/monitor/TMonitorThriftServer.o src/monitor/TMonitorThriftServer.cpp

${OBJECTDIR}/src/monitor/TStorageMonitorThriftHandler.o: src/monitor/TStorageMonitorThriftHandler.cpp
	${MKDIR} -p ${OBJECTDIR}/src/monitor
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -DBUILD_LIBSTATGRAB -DHAVE_CONFIG_H -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/src/ -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/monitor/TStorageMonitorThriftHandler.o src/monitor/TStorageMonitorThriftHandler.cpp

${OBJECTDIR}/src/monitor/TStorageStatModule.o: src/monitor/TStorageStatModule.cpp
	${MKDIR} -p ${OBJECTDIR}/src/monitor
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -DBUILD_LIBSTATGRAB -DHAVE_CONFIG_H -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/src/ -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/monitor/TStorageStatModule.o src/monitor/TStorageStatModule.cpp

${OBJECTDIR}/thrift/gen-cpp/MonitorReadService.o: thrift/gen-cpp/MonitorReadService.cpp
	${MKDIR} -p ${OBJECTDIR}/thrift/gen-cpp
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -DBUILD_LIBSTATGRAB -DHAVE_CONFIG_H -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/src/ -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/thrift/gen-cpp/MonitorReadService.o thrift/gen-cpp/MonitorReadService.cpp

${OBJECTDIR}/thrift/gen-cpp/OpenBaseService.o: thrift/gen-cpp/OpenBaseService.cpp
	${MKDIR} -p ${OBJECTDIR}/thrift/gen-cpp
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -DBUILD_LIBSTATGRAB -DHAVE_CONFIG_H -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/src/ -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/thrift/gen-cpp/OpenBaseService.o thrift/gen-cpp/OpenBaseService.cpp

${OBJECTDIR}/thrift/gen-cpp/StorageMonitorService.o: thrift/gen-cpp/StorageMonitorService.cpp
	${MKDIR} -p ${OBJECTDIR}/thrift/gen-cpp
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -DBUILD_LIBSTATGRAB -DHAVE_CONFIG_H -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/src/ -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/thrift/gen-cpp/StorageMonitorService.o thrift/gen-cpp/StorageMonitorService.cpp

${OBJECTDIR}/thrift/gen-cpp/TBackendManagerService.o: thrift/gen-cpp/TBackendManagerService.cpp
	${MKDIR} -p ${OBJECTDIR}/thrift/gen-cpp
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -DBUILD_LIBSTATGRAB -DHAVE_CONFIG_H -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/src/ -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/thrift/gen-cpp/TBackendManagerService.o thrift/gen-cpp/TBackendManagerService.cpp

${OBJECTDIR}/thrift/gen-cpp/TNodeServiceBase.o: thrift/gen-cpp/TNodeServiceBase.cpp
	${MKDIR} -p ${OBJECTDIR}/thrift/gen-cpp
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -DBUILD_LIBSTATGRAB -DHAVE_CONFIG_H -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/src/ -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/thrift/gen-cpp/TNodeServiceBase.o thrift/gen-cpp/TNodeServiceBase.cpp

${OBJECTDIR}/thrift/gen-cpp/TP2PService.o: thrift/gen-cpp/TP2PService.cpp
	${MKDIR} -p ${OBJECTDIR}/thrift/gen-cpp
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -DBUILD_LIBSTATGRAB -DHAVE_CONFIG_H -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/src/ -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/thrift/gen-cpp/TP2PService.o thrift/gen-cpp/TP2PService.cpp

${OBJECTDIR}/thrift/gen-cpp/backendmonitor_constants.o: thrift/gen-cpp/backendmonitor_constants.cpp
	${MKDIR} -p ${OBJECTDIR}/thrift/gen-cpp
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -DBUILD_LIBSTATGRAB -DHAVE_CONFIG_H -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/src/ -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/thrift/gen-cpp/backendmonitor_constants.o thrift/gen-cpp/backendmonitor_constants.cpp

${OBJECTDIR}/thrift/gen-cpp/backendmonitor_types.o: thrift/gen-cpp/backendmonitor_types.cpp
	${MKDIR} -p ${OBJECTDIR}/thrift/gen-cpp
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -DBUILD_LIBSTATGRAB -DHAVE_CONFIG_H -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/src/ -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/thrift/gen-cpp/backendmonitor_types.o thrift/gen-cpp/backendmonitor_types.cpp

${OBJECTDIR}/thrift/gen-cpp/distributed_constants.o: thrift/gen-cpp/distributed_constants.cpp
	${MKDIR} -p ${OBJECTDIR}/thrift/gen-cpp
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -DBUILD_LIBSTATGRAB -DHAVE_CONFIG_H -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/src/ -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/thrift/gen-cpp/distributed_constants.o thrift/gen-cpp/distributed_constants.cpp

${OBJECTDIR}/thrift/gen-cpp/distributed_types.o: thrift/gen-cpp/distributed_types.cpp
	${MKDIR} -p ${OBJECTDIR}/thrift/gen-cpp
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -DBUILD_LIBSTATGRAB -DHAVE_CONFIG_H -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/src/ -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/thrift/gen-cpp/distributed_types.o thrift/gen-cpp/distributed_types.cpp

${OBJECTDIR}/thrift/gen-cpp/monitor_constants.o: thrift/gen-cpp/monitor_constants.cpp
	${MKDIR} -p ${OBJECTDIR}/thrift/gen-cpp
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -DBUILD_LIBSTATGRAB -DHAVE_CONFIG_H -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/src/ -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/thrift/gen-cpp/monitor_constants.o thrift/gen-cpp/monitor_constants.cpp

${OBJECTDIR}/thrift/gen-cpp/monitor_types.o: thrift/gen-cpp/monitor_types.cpp
	${MKDIR} -p ${OBJECTDIR}/thrift/gen-cpp
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -DBUILD_LIBSTATGRAB -DHAVE_CONFIG_H -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/src/ -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/thrift/gen-cpp/monitor_types.o thrift/gen-cpp/monitor_types.cpp

${OBJECTDIR}/thrift/gen-cpp/openbase_constants.o: thrift/gen-cpp/openbase_constants.cpp
	${MKDIR} -p ${OBJECTDIR}/thrift/gen-cpp
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -DBUILD_LIBSTATGRAB -DHAVE_CONFIG_H -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/src/ -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/thrift/gen-cpp/openbase_constants.o thrift/gen-cpp/openbase_constants.cpp

${OBJECTDIR}/thrift/gen-cpp/openbase_types.o: thrift/gen-cpp/openbase_types.cpp
	${MKDIR} -p ${OBJECTDIR}/thrift/gen-cpp
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -DBUILD_LIBSTATGRAB -DHAVE_CONFIG_H -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/src/ -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/thrift/gen-cpp/openbase_types.o thrift/gen-cpp/openbase_types.cpp

# Subprojects
.build-subprojects:

# Build Test Targets
.build-tests-conf: .build-tests-subprojects .build-conf ${TESTFILES}
.build-tests-subprojects:
	cd ../../contribs/UPPoco && ${MAKE}  -f Makefile CONF=Debug

${TESTDIR}/TestFiles/f2: ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc} -o ${TESTDIR}/TestFiles/f2 $^ ${LDLIBSOPTIONS}  -std=c++0x -Llib -L../../contribs/Test/Catch -L../../contribs/Poco/lib -L../../contribs/ApacheThrift/lib -L../../contribs/LibEvent/lib -lpthread -ldl 

${TESTDIR}/TestFiles/f4: ${TESTDIR}/tests/EtcdRegTest.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc} -o ${TESTDIR}/TestFiles/f4 $^ ${LDLIBSOPTIONS}   -Llib -L../../contribs/Test/Catch -L../../contribs/Poco/lib -L../../contribs/ApacheThrift/lib -L../../contribs/LibEvent/lib -lpthread -ldl 

${TESTDIR}/TestFiles/f1: ${TESTDIR}/tests/TestZK.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc} -o ${TESTDIR}/TestFiles/f1 $^ ${LDLIBSOPTIONS}   -Llib -L../../contribs/Test/Catch -L../../contribs/Poco/lib -L../../contribs/ApacheThrift/lib -L../../contribs/LibEvent/lib -lpthread -ldl 

${TESTDIR}/TestFiles/f5: ${TESTDIR}/tests/TestEtcdV3Client.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc} -o ${TESTDIR}/TestFiles/f5 $^ ${LDLIBSOPTIONS}   -Llib -L../../contribs/Test/Catch -L../../contribs/Poco/lib -L../../contribs/ApacheThrift/lib -L../../contribs/LibEvent/lib -lpthread -ldl 

${TESTDIR}/TestFiles/f6: ${TESTDIR}/tests/timebasedlisencemanagertest.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc} -o ${TESTDIR}/TestFiles/f6 $^ ${LDLIBSOPTIONS}   -Llib -L../../contribs/Test/Catch -L../../contribs/Poco/lib -L../../contribs/ApacheThrift/lib -L../../contribs/LibEvent/lib -lpthread -ldl 

${TESTDIR}/TestFiles/zkregistertest: ${TESTDIR}/tests/ZKRegisterTest.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc} -o ${TESTDIR}/TestFiles/zkregistertest $^ ${LDLIBSOPTIONS}   -Llib -L../../contribs/Test/Catch -L../../contribs/Poco/lib -L../../contribs/ApacheThrift/lib -L../../contribs/LibEvent/lib -lpthread -ldl ../../contribs/UPPoco/lib/libuppocod.a 


${TESTDIR}/tests/EtcdRegTest.o: tests/EtcdRegTest.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -DBUILD_LIBSTATGRAB -DHAVE_CONFIG_H -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/src/ -I. -std=c++11 -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/EtcdRegTest.o tests/EtcdRegTest.cpp


${TESTDIR}/tests/TestZK.o: tests/TestZK.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -DBUILD_LIBSTATGRAB -DHAVE_CONFIG_H -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/src/ -I. -std=c++11 -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/TestZK.o tests/TestZK.cpp


${TESTDIR}/tests/TestEtcdV3Client.o: tests/TestEtcdV3Client.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -DBUILD_LIBSTATGRAB -DHAVE_CONFIG_H -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/src/ -I. -std=c++11 -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/TestEtcdV3Client.o tests/TestEtcdV3Client.cpp


${TESTDIR}/tests/timebasedlisencemanagertest.o: tests/timebasedlisencemanagertest.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -DBUILD_LIBSTATGRAB -DHAVE_CONFIG_H -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/src/ -I. -std=c++11 -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/timebasedlisencemanagertest.o tests/timebasedlisencemanagertest.cpp


${TESTDIR}/tests/ZKRegisterTest.o: tests/ZKRegisterTest.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -DBUILD_LIBSTATGRAB -DHAVE_CONFIG_H -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/src/ -I. -std=c++11 -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/ZKRegisterTest.o tests/ZKRegisterTest.cpp


${OBJECTDIR}/src/Caching/MemoryStats_nomain.o: ${OBJECTDIR}/src/Caching/MemoryStats.o src/Caching/MemoryStats.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/Caching
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/Caching/MemoryStats.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -DBUILD_LIBSTATGRAB -DHAVE_CONFIG_H -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/src/ -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Caching/MemoryStats_nomain.o src/Caching/MemoryStats.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/Caching/MemoryStats.o ${OBJECTDIR}/src/Caching/MemoryStats_nomain.o;\
	fi

${OBJECTDIR}/src/Distributed/BackendActiveChecker_nomain.o: ${OBJECTDIR}/src/Distributed/BackendActiveChecker.o src/Distributed/BackendActiveChecker.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/Distributed
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/Distributed/BackendActiveChecker.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -DBUILD_LIBSTATGRAB -DHAVE_CONFIG_H -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/src/ -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Distributed/BackendActiveChecker_nomain.o src/Distributed/BackendActiveChecker.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/Distributed/BackendActiveChecker.o ${OBJECTDIR}/src/Distributed/BackendActiveChecker_nomain.o;\
	fi

${OBJECTDIR}/src/Distributed/BackendInfo_nomain.o: ${OBJECTDIR}/src/Distributed/BackendInfo.o src/Distributed/BackendInfo.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/Distributed
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/Distributed/BackendInfo.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -DBUILD_LIBSTATGRAB -DHAVE_CONFIG_H -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/src/ -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Distributed/BackendInfo_nomain.o src/Distributed/BackendInfo.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/Distributed/BackendInfo.o ${OBJECTDIR}/src/Distributed/BackendInfo_nomain.o;\
	fi

${OBJECTDIR}/src/Distributed/BackendManager_nomain.o: ${OBJECTDIR}/src/Distributed/BackendManager.o src/Distributed/BackendManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/Distributed
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/Distributed/BackendManager.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -DBUILD_LIBSTATGRAB -DHAVE_CONFIG_H -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/src/ -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Distributed/BackendManager_nomain.o src/Distributed/BackendManager.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/Distributed/BackendManager.o ${OBJECTDIR}/src/Distributed/BackendManager_nomain.o;\
	fi

${OBJECTDIR}/src/Distributed/BasicProxyFactory_nomain.o: ${OBJECTDIR}/src/Distributed/BasicProxyFactory.o src/Distributed/BasicProxyFactory.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/Distributed
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/Distributed/BasicProxyFactory.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -DBUILD_LIBSTATGRAB -DHAVE_CONFIG_H -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/src/ -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Distributed/BasicProxyFactory_nomain.o src/Distributed/BasicProxyFactory.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/Distributed/BasicProxyFactory.o ${OBJECTDIR}/src/Distributed/BasicProxyFactory_nomain.o;\
	fi

${OBJECTDIR}/src/Distributed/CHBackendManager_nomain.o: ${OBJECTDIR}/src/Distributed/CHBackendManager.o src/Distributed/CHBackendManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/Distributed
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/Distributed/CHBackendManager.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -DBUILD_LIBSTATGRAB -DHAVE_CONFIG_H -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/src/ -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Distributed/CHBackendManager_nomain.o src/Distributed/CHBackendManager.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/Distributed/CHBackendManager.o ${OBJECTDIR}/src/Distributed/CHBackendManager_nomain.o;\
	fi

${OBJECTDIR}/src/Distributed/RepBackendManager_nomain.o: ${OBJECTDIR}/src/Distributed/RepBackendManager.o src/Distributed/RepBackendManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/Distributed
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/Distributed/RepBackendManager.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -DBUILD_LIBSTATGRAB -DHAVE_CONFIG_H -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/src/ -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Distributed/RepBackendManager_nomain.o src/Distributed/RepBackendManager.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/Distributed/RepBackendManager.o ${OBJECTDIR}/src/Distributed/RepBackendManager_nomain.o;\
	fi

${OBJECTDIR}/src/Endpoint_nomain.o: ${OBJECTDIR}/src/Endpoint.o src/Endpoint.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/Endpoint.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -DBUILD_LIBSTATGRAB -DHAVE_CONFIG_H -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/src/ -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Endpoint_nomain.o src/Endpoint.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/Endpoint.o ${OBJECTDIR}/src/Endpoint_nomain.o;\
	fi

${OBJECTDIR}/src/EndpointManager_nomain.o: ${OBJECTDIR}/src/EndpointManager.o src/EndpointManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/EndpointManager.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -DBUILD_LIBSTATGRAB -DHAVE_CONFIG_H -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/src/ -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/EndpointManager_nomain.o src/EndpointManager.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/EndpointManager.o ${OBJECTDIR}/src/EndpointManager_nomain.o;\
	fi

${OBJECTDIR}/src/EtcdRegister_nomain.o: ${OBJECTDIR}/src/EtcdRegister.o src/EtcdRegister.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/EtcdRegister.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -DBUILD_LIBSTATGRAB -DHAVE_CONFIG_H -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/src/ -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/EtcdRegister_nomain.o src/EtcdRegister.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/EtcdRegister.o ${OBJECTDIR}/src/EtcdRegister_nomain.o;\
	fi

${OBJECTDIR}/src/Hashing/CastingHasher_nomain.o: ${OBJECTDIR}/src/Hashing/CastingHasher.o src/Hashing/CastingHasher.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/Hashing
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/Hashing/CastingHasher.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -DBUILD_LIBSTATGRAB -DHAVE_CONFIG_H -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/src/ -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Hashing/CastingHasher_nomain.o src/Hashing/CastingHasher.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/Hashing/CastingHasher.o ${OBJECTDIR}/src/Hashing/CastingHasher_nomain.o;\
	fi

${OBJECTDIR}/src/Hashing/DefaultHasher_nomain.o: ${OBJECTDIR}/src/Hashing/DefaultHasher.o src/Hashing/DefaultHasher.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/Hashing
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/Hashing/DefaultHasher.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -DBUILD_LIBSTATGRAB -DHAVE_CONFIG_H -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/src/ -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Hashing/DefaultHasher_nomain.o src/Hashing/DefaultHasher.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/Hashing/DefaultHasher.o ${OBJECTDIR}/src/Hashing/DefaultHasher_nomain.o;\
	fi

${OBJECTDIR}/src/Hashing/MurmurHasher_nomain.o: ${OBJECTDIR}/src/Hashing/MurmurHasher.o src/Hashing/MurmurHasher.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/Hashing
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/Hashing/MurmurHasher.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -DBUILD_LIBSTATGRAB -DHAVE_CONFIG_H -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/src/ -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Hashing/MurmurHasher_nomain.o src/Hashing/MurmurHasher.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/Hashing/MurmurHasher.o ${OBJECTDIR}/src/Hashing/MurmurHasher_nomain.o;\
	fi

${OBJECTDIR}/src/LiteEndpointManager_nomain.o: ${OBJECTDIR}/src/LiteEndpointManager.o src/LiteEndpointManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/LiteEndpointManager.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -DBUILD_LIBSTATGRAB -DHAVE_CONFIG_H -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/src/ -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/LiteEndpointManager_nomain.o src/LiteEndpointManager.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/LiteEndpointManager.o ${OBJECTDIR}/src/LiteEndpointManager_nomain.o;\
	fi

${OBJECTDIR}/src/NQueueCenterWorker_nomain.o: ${OBJECTDIR}/src/NQueueCenterWorker.o src/NQueueCenterWorker.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/NQueueCenterWorker.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -DBUILD_LIBSTATGRAB -DHAVE_CONFIG_H -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/src/ -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/NQueueCenterWorker_nomain.o src/NQueueCenterWorker.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/NQueueCenterWorker.o ${OBJECTDIR}/src/NQueueCenterWorker_nomain.o;\
	fi

${OBJECTDIR}/src/NetUtil_nomain.o: ${OBJECTDIR}/src/NetUtil.o src/NetUtil.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/NetUtil.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -DBUILD_LIBSTATGRAB -DHAVE_CONFIG_H -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/src/ -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/NetUtil_nomain.o src/NetUtil.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/NetUtil.o ${OBJECTDIR}/src/NetUtil_nomain.o;\
	fi

${OBJECTDIR}/src/OpenBaseHandler_nomain.o: ${OBJECTDIR}/src/OpenBaseHandler.o src/OpenBaseHandler.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/OpenBaseHandler.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -DBUILD_LIBSTATGRAB -DHAVE_CONFIG_H -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/src/ -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/OpenBaseHandler_nomain.o src/OpenBaseHandler.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/OpenBaseHandler.o ${OBJECTDIR}/src/OpenBaseHandler_nomain.o;\
	fi

${OBJECTDIR}/src/SharedMemoryEx_nomain.o: ${OBJECTDIR}/src/SharedMemoryEx.o src/SharedMemoryEx.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/SharedMemoryEx.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -DBUILD_LIBSTATGRAB -DHAVE_CONFIG_H -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/src/ -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/SharedMemoryEx_nomain.o src/SharedMemoryEx.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/SharedMemoryEx.o ${OBJECTDIR}/src/SharedMemoryEx_nomain.o;\
	fi

${OBJECTDIR}/src/Storage/MultiKVStorage_nomain.o: ${OBJECTDIR}/src/Storage/MultiKVStorage.o src/Storage/MultiKVStorage.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/Storage
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/Storage/MultiKVStorage.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -DBUILD_LIBSTATGRAB -DHAVE_CONFIG_H -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/src/ -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Storage/MultiKVStorage_nomain.o src/Storage/MultiKVStorage.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/Storage/MultiKVStorage.o ${OBJECTDIR}/src/Storage/MultiKVStorage_nomain.o;\
	fi

${OBJECTDIR}/src/Storage/SnappyKVStorage_nomain.o: ${OBJECTDIR}/src/Storage/SnappyKVStorage.o src/Storage/SnappyKVStorage.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/Storage
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/Storage/SnappyKVStorage.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -DBUILD_LIBSTATGRAB -DHAVE_CONFIG_H -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/src/ -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Storage/SnappyKVStorage_nomain.o src/Storage/SnappyKVStorage.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/Storage/SnappyKVStorage.o ${OBJECTDIR}/src/Storage/SnappyKVStorage_nomain.o;\
	fi

${OBJECTDIR}/src/Storage/StorageFactory_nomain.o: ${OBJECTDIR}/src/Storage/StorageFactory.o src/Storage/StorageFactory.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/Storage
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/Storage/StorageFactory.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -DBUILD_LIBSTATGRAB -DHAVE_CONFIG_H -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/src/ -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Storage/StorageFactory_nomain.o src/Storage/StorageFactory.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/Storage/StorageFactory.o ${OBJECTDIR}/src/Storage/StorageFactory_nomain.o;\
	fi

${OBJECTDIR}/src/TimeBasedLisenceManager_nomain.o: ${OBJECTDIR}/src/TimeBasedLisenceManager.o src/TimeBasedLisenceManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/TimeBasedLisenceManager.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -DBUILD_LIBSTATGRAB -DHAVE_CONFIG_H -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/src/ -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/TimeBasedLisenceManager_nomain.o src/TimeBasedLisenceManager.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/TimeBasedLisenceManager.o ${OBJECTDIR}/src/TimeBasedLisenceManager_nomain.o;\
	fi

${OBJECTDIR}/src/Util/IDGenerator_nomain.o: ${OBJECTDIR}/src/Util/IDGenerator.o src/Util/IDGenerator.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/Util
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/Util/IDGenerator.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -DBUILD_LIBSTATGRAB -DHAVE_CONFIG_H -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/src/ -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Util/IDGenerator_nomain.o src/Util/IDGenerator.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/Util/IDGenerator.o ${OBJECTDIR}/src/Util/IDGenerator_nomain.o;\
	fi

${OBJECTDIR}/src/ZKRegister_nomain.o: ${OBJECTDIR}/src/ZKRegister.o src/ZKRegister.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/ZKRegister.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -DBUILD_LIBSTATGRAB -DHAVE_CONFIG_H -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/src/ -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/ZKRegister_nomain.o src/ZKRegister.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/ZKRegister.o ${OBJECTDIR}/src/ZKRegister_nomain.o;\
	fi

${OBJECTDIR}/src/monitor/ServiceStatFetcher_nomain.o: ${OBJECTDIR}/src/monitor/ServiceStatFetcher.o src/monitor/ServiceStatFetcher.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/monitor
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/monitor/ServiceStatFetcher.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -DBUILD_LIBSTATGRAB -DHAVE_CONFIG_H -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/src/ -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/monitor/ServiceStatFetcher_nomain.o src/monitor/ServiceStatFetcher.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/monitor/ServiceStatFetcher.o ${OBJECTDIR}/src/monitor/ServiceStatFetcher_nomain.o;\
	fi

${OBJECTDIR}/src/monitor/StatSubsystem_nomain.o: ${OBJECTDIR}/src/monitor/StatSubsystem.o src/monitor/StatSubsystem.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/monitor
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/monitor/StatSubsystem.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -DBUILD_LIBSTATGRAB -DHAVE_CONFIG_H -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/src/ -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/monitor/StatSubsystem_nomain.o src/monitor/StatSubsystem.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/monitor/StatSubsystem.o ${OBJECTDIR}/src/monitor/StatSubsystem_nomain.o;\
	fi

${OBJECTDIR}/src/monitor/TBackendLog_nomain.o: ${OBJECTDIR}/src/monitor/TBackendLog.o src/monitor/TBackendLog.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/monitor
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/monitor/TBackendLog.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -DBUILD_LIBSTATGRAB -DHAVE_CONFIG_H -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/src/ -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/monitor/TBackendLog_nomain.o src/monitor/TBackendLog.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/monitor/TBackendLog.o ${OBJECTDIR}/src/monitor/TBackendLog_nomain.o;\
	fi

${OBJECTDIR}/src/monitor/TMonitorThriftHandler_nomain.o: ${OBJECTDIR}/src/monitor/TMonitorThriftHandler.o src/monitor/TMonitorThriftHandler.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/monitor
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/monitor/TMonitorThriftHandler.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -DBUILD_LIBSTATGRAB -DHAVE_CONFIG_H -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/src/ -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/monitor/TMonitorThriftHandler_nomain.o src/monitor/TMonitorThriftHandler.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/monitor/TMonitorThriftHandler.o ${OBJECTDIR}/src/monitor/TMonitorThriftHandler_nomain.o;\
	fi

${OBJECTDIR}/src/monitor/TMonitorThriftServer_nomain.o: ${OBJECTDIR}/src/monitor/TMonitorThriftServer.o src/monitor/TMonitorThriftServer.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/monitor
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/monitor/TMonitorThriftServer.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -DBUILD_LIBSTATGRAB -DHAVE_CONFIG_H -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/src/ -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/monitor/TMonitorThriftServer_nomain.o src/monitor/TMonitorThriftServer.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/monitor/TMonitorThriftServer.o ${OBJECTDIR}/src/monitor/TMonitorThriftServer_nomain.o;\
	fi

${OBJECTDIR}/src/monitor/TStorageMonitorThriftHandler_nomain.o: ${OBJECTDIR}/src/monitor/TStorageMonitorThriftHandler.o src/monitor/TStorageMonitorThriftHandler.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/monitor
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/monitor/TStorageMonitorThriftHandler.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -DBUILD_LIBSTATGRAB -DHAVE_CONFIG_H -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/src/ -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/monitor/TStorageMonitorThriftHandler_nomain.o src/monitor/TStorageMonitorThriftHandler.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/monitor/TStorageMonitorThriftHandler.o ${OBJECTDIR}/src/monitor/TStorageMonitorThriftHandler_nomain.o;\
	fi

${OBJECTDIR}/src/monitor/TStorageStatModule_nomain.o: ${OBJECTDIR}/src/monitor/TStorageStatModule.o src/monitor/TStorageStatModule.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/monitor
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/monitor/TStorageStatModule.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -DBUILD_LIBSTATGRAB -DHAVE_CONFIG_H -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/src/ -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/monitor/TStorageStatModule_nomain.o src/monitor/TStorageStatModule.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/monitor/TStorageStatModule.o ${OBJECTDIR}/src/monitor/TStorageStatModule_nomain.o;\
	fi

${OBJECTDIR}/thrift/gen-cpp/MonitorReadService_nomain.o: ${OBJECTDIR}/thrift/gen-cpp/MonitorReadService.o thrift/gen-cpp/MonitorReadService.cpp 
	${MKDIR} -p ${OBJECTDIR}/thrift/gen-cpp
	@NMOUTPUT=`${NM} ${OBJECTDIR}/thrift/gen-cpp/MonitorReadService.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -DBUILD_LIBSTATGRAB -DHAVE_CONFIG_H -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/src/ -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/thrift/gen-cpp/MonitorReadService_nomain.o thrift/gen-cpp/MonitorReadService.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/thrift/gen-cpp/MonitorReadService.o ${OBJECTDIR}/thrift/gen-cpp/MonitorReadService_nomain.o;\
	fi

${OBJECTDIR}/thrift/gen-cpp/OpenBaseService_nomain.o: ${OBJECTDIR}/thrift/gen-cpp/OpenBaseService.o thrift/gen-cpp/OpenBaseService.cpp 
	${MKDIR} -p ${OBJECTDIR}/thrift/gen-cpp
	@NMOUTPUT=`${NM} ${OBJECTDIR}/thrift/gen-cpp/OpenBaseService.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -DBUILD_LIBSTATGRAB -DHAVE_CONFIG_H -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/src/ -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/thrift/gen-cpp/OpenBaseService_nomain.o thrift/gen-cpp/OpenBaseService.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/thrift/gen-cpp/OpenBaseService.o ${OBJECTDIR}/thrift/gen-cpp/OpenBaseService_nomain.o;\
	fi

${OBJECTDIR}/thrift/gen-cpp/StorageMonitorService_nomain.o: ${OBJECTDIR}/thrift/gen-cpp/StorageMonitorService.o thrift/gen-cpp/StorageMonitorService.cpp 
	${MKDIR} -p ${OBJECTDIR}/thrift/gen-cpp
	@NMOUTPUT=`${NM} ${OBJECTDIR}/thrift/gen-cpp/StorageMonitorService.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -DBUILD_LIBSTATGRAB -DHAVE_CONFIG_H -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/src/ -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/thrift/gen-cpp/StorageMonitorService_nomain.o thrift/gen-cpp/StorageMonitorService.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/thrift/gen-cpp/StorageMonitorService.o ${OBJECTDIR}/thrift/gen-cpp/StorageMonitorService_nomain.o;\
	fi

${OBJECTDIR}/thrift/gen-cpp/TBackendManagerService_nomain.o: ${OBJECTDIR}/thrift/gen-cpp/TBackendManagerService.o thrift/gen-cpp/TBackendManagerService.cpp 
	${MKDIR} -p ${OBJECTDIR}/thrift/gen-cpp
	@NMOUTPUT=`${NM} ${OBJECTDIR}/thrift/gen-cpp/TBackendManagerService.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -DBUILD_LIBSTATGRAB -DHAVE_CONFIG_H -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/src/ -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/thrift/gen-cpp/TBackendManagerService_nomain.o thrift/gen-cpp/TBackendManagerService.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/thrift/gen-cpp/TBackendManagerService.o ${OBJECTDIR}/thrift/gen-cpp/TBackendManagerService_nomain.o;\
	fi

${OBJECTDIR}/thrift/gen-cpp/TNodeServiceBase_nomain.o: ${OBJECTDIR}/thrift/gen-cpp/TNodeServiceBase.o thrift/gen-cpp/TNodeServiceBase.cpp 
	${MKDIR} -p ${OBJECTDIR}/thrift/gen-cpp
	@NMOUTPUT=`${NM} ${OBJECTDIR}/thrift/gen-cpp/TNodeServiceBase.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -DBUILD_LIBSTATGRAB -DHAVE_CONFIG_H -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/src/ -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/thrift/gen-cpp/TNodeServiceBase_nomain.o thrift/gen-cpp/TNodeServiceBase.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/thrift/gen-cpp/TNodeServiceBase.o ${OBJECTDIR}/thrift/gen-cpp/TNodeServiceBase_nomain.o;\
	fi

${OBJECTDIR}/thrift/gen-cpp/TP2PService_nomain.o: ${OBJECTDIR}/thrift/gen-cpp/TP2PService.o thrift/gen-cpp/TP2PService.cpp 
	${MKDIR} -p ${OBJECTDIR}/thrift/gen-cpp
	@NMOUTPUT=`${NM} ${OBJECTDIR}/thrift/gen-cpp/TP2PService.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -DBUILD_LIBSTATGRAB -DHAVE_CONFIG_H -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/src/ -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/thrift/gen-cpp/TP2PService_nomain.o thrift/gen-cpp/TP2PService.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/thrift/gen-cpp/TP2PService.o ${OBJECTDIR}/thrift/gen-cpp/TP2PService_nomain.o;\
	fi

${OBJECTDIR}/thrift/gen-cpp/backendmonitor_constants_nomain.o: ${OBJECTDIR}/thrift/gen-cpp/backendmonitor_constants.o thrift/gen-cpp/backendmonitor_constants.cpp 
	${MKDIR} -p ${OBJECTDIR}/thrift/gen-cpp
	@NMOUTPUT=`${NM} ${OBJECTDIR}/thrift/gen-cpp/backendmonitor_constants.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -DBUILD_LIBSTATGRAB -DHAVE_CONFIG_H -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/src/ -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/thrift/gen-cpp/backendmonitor_constants_nomain.o thrift/gen-cpp/backendmonitor_constants.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/thrift/gen-cpp/backendmonitor_constants.o ${OBJECTDIR}/thrift/gen-cpp/backendmonitor_constants_nomain.o;\
	fi

${OBJECTDIR}/thrift/gen-cpp/backendmonitor_types_nomain.o: ${OBJECTDIR}/thrift/gen-cpp/backendmonitor_types.o thrift/gen-cpp/backendmonitor_types.cpp 
	${MKDIR} -p ${OBJECTDIR}/thrift/gen-cpp
	@NMOUTPUT=`${NM} ${OBJECTDIR}/thrift/gen-cpp/backendmonitor_types.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -DBUILD_LIBSTATGRAB -DHAVE_CONFIG_H -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/src/ -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/thrift/gen-cpp/backendmonitor_types_nomain.o thrift/gen-cpp/backendmonitor_types.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/thrift/gen-cpp/backendmonitor_types.o ${OBJECTDIR}/thrift/gen-cpp/backendmonitor_types_nomain.o;\
	fi

${OBJECTDIR}/thrift/gen-cpp/distributed_constants_nomain.o: ${OBJECTDIR}/thrift/gen-cpp/distributed_constants.o thrift/gen-cpp/distributed_constants.cpp 
	${MKDIR} -p ${OBJECTDIR}/thrift/gen-cpp
	@NMOUTPUT=`${NM} ${OBJECTDIR}/thrift/gen-cpp/distributed_constants.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -DBUILD_LIBSTATGRAB -DHAVE_CONFIG_H -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/src/ -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/thrift/gen-cpp/distributed_constants_nomain.o thrift/gen-cpp/distributed_constants.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/thrift/gen-cpp/distributed_constants.o ${OBJECTDIR}/thrift/gen-cpp/distributed_constants_nomain.o;\
	fi

${OBJECTDIR}/thrift/gen-cpp/distributed_types_nomain.o: ${OBJECTDIR}/thrift/gen-cpp/distributed_types.o thrift/gen-cpp/distributed_types.cpp 
	${MKDIR} -p ${OBJECTDIR}/thrift/gen-cpp
	@NMOUTPUT=`${NM} ${OBJECTDIR}/thrift/gen-cpp/distributed_types.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -DBUILD_LIBSTATGRAB -DHAVE_CONFIG_H -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/src/ -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/thrift/gen-cpp/distributed_types_nomain.o thrift/gen-cpp/distributed_types.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/thrift/gen-cpp/distributed_types.o ${OBJECTDIR}/thrift/gen-cpp/distributed_types_nomain.o;\
	fi

${OBJECTDIR}/thrift/gen-cpp/monitor_constants_nomain.o: ${OBJECTDIR}/thrift/gen-cpp/monitor_constants.o thrift/gen-cpp/monitor_constants.cpp 
	${MKDIR} -p ${OBJECTDIR}/thrift/gen-cpp
	@NMOUTPUT=`${NM} ${OBJECTDIR}/thrift/gen-cpp/monitor_constants.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -DBUILD_LIBSTATGRAB -DHAVE_CONFIG_H -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/src/ -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/thrift/gen-cpp/monitor_constants_nomain.o thrift/gen-cpp/monitor_constants.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/thrift/gen-cpp/monitor_constants.o ${OBJECTDIR}/thrift/gen-cpp/monitor_constants_nomain.o;\
	fi

${OBJECTDIR}/thrift/gen-cpp/monitor_types_nomain.o: ${OBJECTDIR}/thrift/gen-cpp/monitor_types.o thrift/gen-cpp/monitor_types.cpp 
	${MKDIR} -p ${OBJECTDIR}/thrift/gen-cpp
	@NMOUTPUT=`${NM} ${OBJECTDIR}/thrift/gen-cpp/monitor_types.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -DBUILD_LIBSTATGRAB -DHAVE_CONFIG_H -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/src/ -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/thrift/gen-cpp/monitor_types_nomain.o thrift/gen-cpp/monitor_types.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/thrift/gen-cpp/monitor_types.o ${OBJECTDIR}/thrift/gen-cpp/monitor_types_nomain.o;\
	fi

${OBJECTDIR}/thrift/gen-cpp/openbase_constants_nomain.o: ${OBJECTDIR}/thrift/gen-cpp/openbase_constants.o thrift/gen-cpp/openbase_constants.cpp 
	${MKDIR} -p ${OBJECTDIR}/thrift/gen-cpp
	@NMOUTPUT=`${NM} ${OBJECTDIR}/thrift/gen-cpp/openbase_constants.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -DBUILD_LIBSTATGRAB -DHAVE_CONFIG_H -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/src/ -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/thrift/gen-cpp/openbase_constants_nomain.o thrift/gen-cpp/openbase_constants.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/thrift/gen-cpp/openbase_constants.o ${OBJECTDIR}/thrift/gen-cpp/openbase_constants_nomain.o;\
	fi

${OBJECTDIR}/thrift/gen-cpp/openbase_types_nomain.o: ${OBJECTDIR}/thrift/gen-cpp/openbase_types.o thrift/gen-cpp/openbase_types.cpp 
	${MKDIR} -p ${OBJECTDIR}/thrift/gen-cpp
	@NMOUTPUT=`${NM} ${OBJECTDIR}/thrift/gen-cpp/openbase_types.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -DBUILD_LIBSTATGRAB -DHAVE_CONFIG_H -DTHREADED -D_GNU_SOURCE -Iinc -I../../contribs/LibEvent/include -I../../contribs/Boost/include -I../../contribs/Poco/include -I../../contribs/ApacheThrift/include -I../../contribs/SpecialContribs -I../../contribs/SpecialContribs/include -Ithrift/gen-cpp -I../../contribs/SpecialContribs/src/hashkit -I../../contribs/SpecialContribs/src/libstatgrab -I../../contribs/SpecialContribs/src/ -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/thrift/gen-cpp/openbase_types_nomain.o thrift/gen-cpp/openbase_types.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/thrift/gen-cpp/openbase_types.o ${OBJECTDIR}/thrift/gen-cpp/openbase_types_nomain.o;\
	fi

# Run Test Targets
.test-conf:
	@if [ "${TEST}" = "" ]; \
	then  \
	    ${TESTDIR}/TestFiles/f2 || true; \
	    ${TESTDIR}/TestFiles/f4 || true; \
	    ${TESTDIR}/TestFiles/f1 || true; \
	    ${TESTDIR}/TestFiles/f5 || true; \
	    ${TESTDIR}/TestFiles/f6 || true; \
	    ${TESTDIR}/TestFiles/zkregistertest || true; \
	else  \
	    ./${TEST} || true; \
	fi

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
