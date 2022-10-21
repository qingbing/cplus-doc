# 动态库核心命令
# 生成目标文件: gcc -c -fpic add.c -o add.o
# 生成动态库: gcc -shared  ./add.o  ./sub.o -o libmymath.a

# 通用变量
CROSS =
CC = ${CROSS}gcc
CXX = ${CROSS}g++
RM = rm -rf

# 所有源文件
SRCS = $(wildcard ./*.c)
OBJS = $(patsubst %.c, %.o, ${SRCS})

TARGET = libsymath.a

all: ${TARGET}
.PHONY: all

.PHONY: test
test:
	@echo ${SRCS}
	@echo ${OBJS}

${OBJS}: %.o : %.c
	${CC} -c -fpic $< -o $@

${TARGET}: ${OBJS}
	gcc -shared ${OBJS} -o ${TARGET}

clean:
	$(RM) ${TARGET} *.o
.PHONY: clean
