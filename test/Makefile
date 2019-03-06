CXX=g++
CXXFLAGS=-fno-rtti -O0 -g
LLVM_CXXFLAGS=`llvm-config --cxxflags`
LLVM_LDFLAGS := `llvm-config --ldflags --libs --system-libs`

all: TestControlFlowAnalysis cfa
	${CXX} ${CXXFLAGS} TestControlFlowAnalysis.o cfa.o ${LLVM_CXXFLAGS} ${LLVM_LDFLAGS} -o TestControlFlowAnalysis

TestControlFlowAnalysis: TestControlFlowAnalysis.cpp
	${CXX} ${CXXFLAGS} $^ ${LLVM_CXXFLAGS} ${LLVM_LDFLAGS} -c -o $@.o

cfa: ../src/ControlFlowAnalyzer.cpp
	${CXX} ${CXXFLAGS} $^ ${LLVM_CXXFLAGS} ${LLVM_LDFLAGS} -c -o $@.o

clean:
	rm *.dot *.o

