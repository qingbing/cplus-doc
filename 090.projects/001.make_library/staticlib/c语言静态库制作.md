# c语言静态库制作

## 1 静态链接库介绍

- 编译时会把库中的代码编译到二进制文件中，当程序编译完成后，该库文件可删除
  - -l(小写) 指定链接库
  - -I(大写) 指定头文件目录，默认当前目录
  - -L(大写) 手动指定库文件搜索目录，默认只链接共享目录
- 静态链理解
  - 好处库文件包含在二进制文件中，库文件不需要单独部署
  - 静态库后缀
    - windows: .lib
    - linux: .a
  - 静态: 库文件已经编译在二进制文件中，运行是不需要库文件依赖
- 库名: 必须以 "lib" 开始， 编译和运行链接时不需要 "lib"

## 2 编译静态库

- 分步编译静态库

```shell
# 生成目标文件
gcc -c %.c -o %.o
# 将目标文件打包
ar rcs lib{libName}.a ${OBJ}
```

- 指定静态库编译

```shell
gcc -l{libName} -L./ ${OBJ} -o ${TARGET}
```

## 3 静态库 makefile 编译 demo

```Makefile
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
```