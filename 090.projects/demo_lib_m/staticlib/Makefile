# 静态库核心命令
# 生成目标文件: gcc -c add.c -o add.o
# 将目标文件打包: ar rcs libmymath.so  ./add.o  ./sub.o

# 通用变量
CROSS =
CC = ${CROSS}gcc
CXX = ${CROSS}g++
RM = rm -rf

# 所有源文件
SRCS = $(wildcard ./*.c)
OBJS = $(patsubst %.c, %.o, ${SRCS})

TARGET = libstmath.so

all: ${TARGET}
.PHONY: all

.PHONY: test
test:
	@echo ${SRCS}
	@echo ${OBJS}

${OBJS}: %.o : %.c
	${CC} -c $< -o $@

${TARGET}: ${OBJS}
	ar rcs ${TARGET} ${OBJS}

clean:
	$(RM) ${TARGET} *.o
.PHONY: clean
