TARGET:=common.out sum.out

SRC = $(wildcard *.c)
OBJ = $(patsubst %.c, %.o, ${SRC})

all: ${TARGET}

%.out: %.o
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