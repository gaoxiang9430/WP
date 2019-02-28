CXX=g++
CXXFLAGS=-fno-rtti -O0 -g
LLVM_CXXFLAGS=`llvm-config --cxxflags`
LLVM_LDFLAGS := `llvm-config --ldflags --libs --system-libs`

all: bb_toposort_sccs

bb_toposort_sccs: bb_toposort_sccs.cpp
	${CXX} ${CXXFLAGS} $^ ${LLVM_CXXFLAGS} ${LLVM_LDFLAGS} -o $@

clean:
	rm bb_toposort_sccs
