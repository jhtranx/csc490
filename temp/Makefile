#CXX=clang++
CXX=g++

CXXFLAGS= -g -std=c++14 

BINARIES=dataProj

all: ${BINARIES}


dataProj: statTool.o stats.o statTool.o demogCombo.o demogData.o raceDemogData.o psData.o psCombo.o parse.o main.o
	${CXX} $^ -o $@



clean:
	/bin/rm -f ${BINARIES} *.o 
