CROSS =
CC = $(CROSS)gcc

SRC_FILE=*.c
OBJ_FILE=test_02.o
TARGET=../libs/libtest02.so

all: ${TARGET}
.PHONY: all

${OBJ_FILE}: ${SRC_FILE}
	${CC} -c -fpic ${SRC_FILE} -o ${OBJ_FILE}
${TARGET}: ${OBJ_FILE}
	${CC} -shared ${OBJ_FILE} -o ${TARGET}
#	# mv ${TARGET} ../libs

clean:
	$(RM) ${TARGET} *.o
.PHONY: clean
