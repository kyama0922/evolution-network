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
CND_PLATFORM=GNU-Linux-x86
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
	${OBJECTDIR}/_ext/1522578363/evolution_network_factory.o \
	${OBJECTDIR}/_ext/824854343/evolution_network_function.o \
	${OBJECTDIR}/_ext/1545248249/evolution_network_protocol.o \
	${OBJECTDIR}/_ext/812711262/evolution_network_socket.o \
	${OBJECTDIR}/_ext/812711262/evolution_network_tcp_bindsocket.o \
	${OBJECTDIR}/_ext/812711262/evolution_network_tpc_connectsocket.o \
	${OBJECTDIR}/_ext/812711262/evolution_network_udp_bindsocket.o \
	${OBJECTDIR}/_ext/812711262/evolution_network_udp_transceiversocket.o


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
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libevolution-network.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libevolution-network.a: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libevolution-network.a
	${AR} -rv ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libevolution-network.a ${OBJECTFILES} 
	$(RANLIB) ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libevolution-network.a

${OBJECTDIR}/_ext/1522578363/evolution_network_factory.o: ../factory/evolution_network_factory.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1522578363
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DNODEBUG=1 -D_LINUX=1 -D_X64=1 -Dnullptr=0 -I../.. -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1522578363/evolution_network_factory.o ../factory/evolution_network_factory.cpp

${OBJECTDIR}/_ext/824854343/evolution_network_function.o: ../function/evolution_network_function.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/824854343
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DNODEBUG=1 -D_LINUX=1 -D_X64=1 -Dnullptr=0 -I../.. -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/824854343/evolution_network_function.o ../function/evolution_network_function.cpp

${OBJECTDIR}/_ext/1545248249/evolution_network_protocol.o: ../protocol/evolution_network_protocol.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1545248249
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DNODEBUG=1 -D_LINUX=1 -D_X64=1 -Dnullptr=0 -I../.. -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1545248249/evolution_network_protocol.o ../protocol/evolution_network_protocol.cpp

${OBJECTDIR}/_ext/812711262/evolution_network_socket.o: ../socket/evolution_network_socket.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/812711262
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DNODEBUG=1 -D_LINUX=1 -D_X64=1 -Dnullptr=0 -I../.. -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/812711262/evolution_network_socket.o ../socket/evolution_network_socket.cpp

${OBJECTDIR}/_ext/812711262/evolution_network_tcp_bindsocket.o: ../socket/evolution_network_tcp_bindsocket.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/812711262
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DNODEBUG=1 -D_LINUX=1 -D_X64=1 -Dnullptr=0 -I../.. -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/812711262/evolution_network_tcp_bindsocket.o ../socket/evolution_network_tcp_bindsocket.cpp

${OBJECTDIR}/_ext/812711262/evolution_network_tpc_connectsocket.o: ../socket/evolution_network_tpc_connectsocket.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/812711262
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DNODEBUG=1 -D_LINUX=1 -D_X64=1 -Dnullptr=0 -I../.. -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/812711262/evolution_network_tpc_connectsocket.o ../socket/evolution_network_tpc_connectsocket.cpp

${OBJECTDIR}/_ext/812711262/evolution_network_udp_bindsocket.o: ../socket/evolution_network_udp_bindsocket.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/812711262
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DNODEBUG=1 -D_LINUX=1 -D_X64=1 -Dnullptr=0 -I../.. -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/812711262/evolution_network_udp_bindsocket.o ../socket/evolution_network_udp_bindsocket.cpp

${OBJECTDIR}/_ext/812711262/evolution_network_udp_transceiversocket.o: ../socket/evolution_network_udp_transceiversocket.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/812711262
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DNODEBUG=1 -D_LINUX=1 -D_X64=1 -Dnullptr=0 -I../.. -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/812711262/evolution_network_udp_transceiversocket.o ../socket/evolution_network_udp_transceiversocket.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libevolution-network.a

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
