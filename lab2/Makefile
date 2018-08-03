CXX = g++					# compiler
CXXFLAGS = -g -Wall -Wno-unused-label -MMD -O2 -std=c++0x
MAKEFILE_NAME = ${firstword ${MAKEFILE_LIST}}	# makefile name

OBJECTS = simulation.o node.o buffer.o packet.o global.o
EXEC = simulation.out

DEPENDS = ${OBJECTS:.o=.d}			# substitute ".o" with ".d"
.PHONY : all clean

all : ${EXEC}					# build all executables

#############################################################

${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} $^ -o $@

#########################################################
${OBJECT} : ${MAKEFILE_NAME}			# OPTIONAL : changes to this file => recompile


clean :						# remove files that can be regenerated
	rm -f *.d *.o ${EXEC}
