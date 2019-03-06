CXX=g++
CXXFLAGS=-fno-rtti -O0 -g
LLVM_CXXFLAGS=`llvm-config --cxxflags`
LLVM_LDFLAGS := `llvm-config --ldflags --libs --system-libs`

all: main ipbb cfa
	${CXX} ${CXXFLAGS} ipbb.o main.o cfa.o ${LLVM_CXXFLAGS} ${LLVM_LDFLAGS} -o main

main: main.cpp
	${CXX} ${CXXFLAGS} $^ ${LLVM_CXXFLAGS} ${LLVM_LDFLAGS} -c -o $@.o

cfa: ControlFlowAnalyzer.cpp
	${CXX} ${CXXFLAGS} $^ ${LLVM_CXXFLAGS} ${LLVM_LDFLAGS} -c -o $@.o

ipbb: InterProceduralBasicBlock.cpp
	${CXX} ${CXXFLAGS} $^ ${LLVM_CXXFLAGS} ${LLVM_LDFLAGS} -c -o $@.o

clean:
	rm main *.dot *.o

