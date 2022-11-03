# c语言动态库制作

## 1 动态链接库介绍

- 动态链接库不会把代码编译到使用的二进制文件中，而是在与运行时才去加载，所以需要维护一个地址
  - -fPIC 产生位置无关的代码
  - -shared 共享
  - -l(小写) 指定链接库
  - -I(大写) 指定头文件目录，默认当前目录
  - -L(大写) 手动指定库文件搜索目录，默认只链接共享目录
- 动态库理解
  - 好处是程序和库文件分离，分别发版，库文件可以多处共享
  - 动态库后缀
    - windows: .dll
    - linux: .so
  - 动态: 编译和运行时才去加载(动态加载)
  - 链接: 指库文件和二进制程序分离，用某种手段维护两者之间的关系
- 库名: 必须以 "lib" 开始， 编译和运行链接时不需要 "lib"
- 默认动态库路径配置文件: /etc/ld.so.conf; /etd/ld.so.conf.d/*.conf
- 默认动态库路径目录: /usr/lib; /usr/local/lib
- 运行时可以手动指定动态目录
  - LD_LIBRARY_PATH(linux)
  - DYLD_LIBRARY_PATH(mac)
  - 当前终端指定: LD_LIBRARY_PATH=xxx; export LD_LIBRARY_PATH;


## 2 编译动态库

- 分步编译动态库

```shell
# 生成目标文件
gcc -c -fPIC %.c -o %.o
# 生成动态库
gcc -shared ${OBJ} -o lib{libName}.so
```

- 一步编译动态库

```shell
gcc -fPIC -shared *.c -o lib{libName}.so
```

## 3 动态库 makefile 编译 demo

```Makefile
# 静态库, 文件后缀为 .so 或 .dll
# 动态库核心命令
# 生成目标文件: gcc -c -fPIC %.c -o %.o
# 生成动态库: gcc -shared ${OBJ} -o ${TARGET}

CUSTOM_LIBS = /code/clibs
TARGET = ${CUSTOM_LIBS}/libSyncTest.so
SRC = $(wildcard *.c)
OBJ = $(patsubst %.c, %.o, ${SRC})

all: ${TARGET}

${TARGET}: ${OBJ}
	${CC} -shared $+ -o ${TARGET}

%.o: %.c
	${CC} -c -fPIC $^ -o $@

clean:
	${RM} ${OBJ} ${TARGET}

show:
	@echo TARGET: ${TARGET}
	@echo SRC: ${SRC}
	@echo OBJ: ${OBJ}

.PHONY: all
```

## 4 使用动态库

方法一: 将动态库放在默认动态库路径目录(/usr/local/lib)下，然后 "sudo ldconfig"
方法二: 创建一个用户动态库目录 "/opt/clibs", 然后 "sudo echo /opt/clibs > /etc/ld.so.conf.d/custom.conf", 再执行 "sudo ldconfig"， 后续只需要将动态放置在该用户目录即可。
    每次发布新包都需要 "sudo ldconfig" 一次
方法三: 配置用户动态目录变量 LD_LIBRARY_PATH=xxx; export LD_LIBRARY_PATH;

- 指定动态库编译

```shell
gcc -l{libName} -L./ ${OBJ} -o ${TARGET}
```
