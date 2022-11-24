# 预定义目标文件
ifndef TARGET
TARGET:=demo.out
endif

SRC = $(wildcard *.c)
OBJ = $(patsubst %.c, %.o, ${SRC})
TARGET = server.out client.out

all: ${TARGET}
	
%.out: %.o
# ${TARGET}: ${OBJ}
	${CC} $^ -o $@

%.o: %.c
	${CC} -c $^ -o $@

clean:
	${RM} ${OBJ} ${TARGET}

show:
	@echo TARGET: ${TARGET}
	@echo SRC: ${SRC}
	@echo OBJ: ${OBJ}

.PHONY: all clean show