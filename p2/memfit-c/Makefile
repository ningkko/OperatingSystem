SHELL:=/bin/bash
CC:=clang
CFLAGS:=-Wall -Werror -Wextra -std=c99 -Wshadow -Wno-unused-parameter -Wno-unused-variable -g
LFLAGS:=-lm
PROGRAM:=memfit
DEBUGGER:=gdb

%.o: %.c
	${CC} -c $^ -o $@ ${CFLAGS}

${PROGRAM}: main.o block.o simulation.o
	${CC} ${LFLAGS} -o $@ $^

block_test: block_test.o block.o
	${CC} ${LFLAGS} -o $@ $^

.PHONY: clean
clean:
	@rm -rf ${PROGRAM} *.o

.PHONY: test
test: ${PROGRAM} block_test
	./block_test
	./${PROGRAM} ../input.txt

.PHONY: debug
debug: ${PROGRAM}
	${DEBUGGER} ${PROGRAM} -ex 'run ../input.txt' || stty sane
