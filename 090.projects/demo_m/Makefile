# 通用变量
CROSS =
CC = $(CROSS)gcc
CXX = $(CROSS)g++
DEBUG = -g -O2
CFLAGS = $(DEBUG) -Wall -c
RM = rm -rf

# 头文件目录设置
# HEADER_PATH = -I ./test_01/ ./test_01/
HEADER_PATH = -I ./libs
# 库文件目录
LIB_PATH = -L ./libs/

# 所有源文件
SRCS = $(wildcard ./*.c ./test_01/*.c)
# OBJS = $(patsubst %.c, %.o, ${SRCS})

VERSION = 1.0.1
TARGET = main

all: main
.PHONY: all clean test02 show

show:
	@echo ${SRCS}
	@echo ${OBJS}

# LIBS = -ldiv
LIBS =
# LIBS = libdiv.a

main: ${SRCS} test02
	${CC} ${SRCS} -o $@ ${LIB_PATH} ${LIBS} ${HEADER_PATH} -l stmath -l symath -l test02
#	${CC} $^ -o $@ ${LIB_PATH} ${LIBS} ${HEADER_PATH} -l stmath -l symath -l test02

# MAKEFLAGS= 让父级的 MAKEFLAGS 值不传递
test02:
	${MAKE} -C test_02
#	${MAKE} -C test_02 -f Makefile

clean:
	$(RM) ${TARGET} *.o
	${MAKE} -C test_02 clean
#	${MAKE} -C test_02 -f Makefile clean
