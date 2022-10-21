CROSS =
CC = $(CROSS)gcc

.PHONY: all run clean show

all: run

SRCS = $(wildcard ./*.c)
TARGET = demo

show:
	@echo ${SRCS}
	@echo ${TARGET}

${TARGET}: ${SRCS}
	echo ${SRCS}
	${CC} $^ -o ${TARGET}

run: ${TARGET}
	sh -c ${TARGET}

clean:
	${RM} ${TARGET}
