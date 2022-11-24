TARGET:=server.out client.out

SRC = $(wildcard *.c)
OBJ = $(patsubst %.c, %.o, ${SRC})

all: ${TARGET}

%.o: %.c
	${CC} -c $^ -o $@

server.out: server.o
	${CC} $^ -o $@

client.out: client.o
	${CC} $^ -o $@

clean:
	${RM} ${OBJ} ${TARGET}

show:
	@echo TARGET: ${TARGET}
	@echo SRC: ${SRC}
	@echo OBJ: ${OBJ}

.PHONY: all clean show