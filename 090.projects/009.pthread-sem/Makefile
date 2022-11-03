# 预定义目标文件
ifndef TARGET
TARGET:=demo.out
endif

SRC = $(wildcard *.c)
OBJ = $(patsubst %.c, %.o, ${SRC})

all: ${TARGET}

${TARGET}: ${OBJ}
	${CC} $^ -o $@ -lpthread

%.o: %.c
	${CC} -c $^ -o $@ -lpthread

clean:
	${RM} ${OBJ} ${TARGET}

show:
	@echo TARGET: ${TARGET}
	@echo SRC: ${SRC}
	@echo OBJ: ${OBJ}

.PHONY: all clean show