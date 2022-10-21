CROSS =
CC = $(CROSS)gcc

SRC_FILE=*.c
OBJ_FILE=test_02.o
TARGET=libtest02.a

all: ${TARGET}
.PHONY: all

${OBJ_FILE}: ${SRC_FILE}
	${CC} -c -fpic ${SRC_FILE} -o ${OBJ_FILE}
${TARGET}: ${OBJ_FILE}
	${CC} -shared ${OBJ_FILE} -o ${TARGET}
	mv ${TARGET} ../libs

clean:
	$(RM) ${TARGET} *.o
	${RM} ../libs/${TARGET}
.PHONY: clean
