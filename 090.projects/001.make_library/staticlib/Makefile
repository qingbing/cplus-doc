# 静态库, 文件后缀为 .a 或 .lib
# 静态库核心命令
# 生成目标文件: gcc -c %.c -o %.o
# 将目标文件打包: ar rcs ${TARGET} ${OBJ}

CUSTOM_LIBS = /code/clibs
TARGET = ${CUSTOM_LIBS}/libStaticTest.a
SRC = $(wildcard *.c)
OBJ = $(patsubst %.c, %.o, ${SRC})

all: ${TARGET}

${TARGET}: ${OBJ}
	${AR} rcs ${TARGET} ${OBJ}

%.o: %.c
	${CC} -c $^ -o $@

clean:
	${RM} ${OBJ} ${TARGET}

show:
	@echo TARGET: ${TARGET}
	@echo SRC: ${SRC}
	@echo OBJ: ${OBJ}

.PHONY: all
