CC=clang
CFALGS=-emit-llvm -S

all: if-else multi-func

if-else: if-else.c
	${CC} ${CFALGS} $^ -o $@.bc
	${CC} $@.bc -o $@

multi-func: multi-func.c
	${CC} ${CFALGS} $^ -o $@.bc
	${CC} $@.bc -o $@

clean:
	rm -f *.bc if-else multi-func
