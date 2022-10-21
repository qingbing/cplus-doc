CROSS =
CC = $(CROSS)gcc

.PHONY: all run clean show

all: run

SRCS = $(wildcard ./*.c)
TARGET = demo.out

show:
	@echo ${SRCS}
	@echo ${TARGET}

${TARGET}: ${SRCS}
	${CC} $^ -o ${TARGET}

run: ${TARGET}
	./${TARGET}

clean:
	${RM} ${TARGET}
