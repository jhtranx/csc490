#CXX=clang++
CXX=g++

CXXFLAGS= -g -O3 -std=c++14 

BINARIES=dataProj testPSState testPSSort testBelowPSort

all: ${BINARIES}

tests: ${BINARIES}
	./testPSState
	./testPSSort
	./testBelowPSort

dataProj: dataAQ.o demogState.o demogData.o raceDemogData.o psData.o psCombo.o parse.o main.o
	${CXX} $^ -o $@

testPSState: testPSState.o dataAQ.o demogState.o demogData.o raceDemogData.o psData.o psCombo.o  parse.o  tddFuncs.o
	${CXX} $^ -o $@

testPSSort: testPSSort.o dataAQ.o demogState.o demogData.o raceDemogData.o psData.o psCombo.o  parse.o tddFuncs.o
	${CXX} $^ -o $@

testBelowPSort: testBelowPSort.o dataAQ.o demogState.o demogData.o raceDemogData.o psData.o psCombo.o  parse.o tddFuncs.o
	${CXX} $^ -o $@

clean:
	/bin/rm -f ${BINARIES} *.o 
