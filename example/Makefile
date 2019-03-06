CC=clang
CFALGS=-emit-llvm -S -g
CC_LINK=llvm-link
LINK_FLAGS=-S

all: if-else multi-func

if-else: if-else.c
	${CC} ${CFALGS} $^ -o $@.bc
	${CC} $@.bc -o $@

multi-func: multi-func.c sub-func.c
	${CC} ${CFALGS} multi-func.c -o multi-func.bc
	${CC} ${CFALGS} sub-func.c -o sub-func.bc
	${CC_LINK} -S sub-func.bc multi-func.bc -o all.bc

clean:
	rm -f *.bc if-else multi-func *.dot *.out
