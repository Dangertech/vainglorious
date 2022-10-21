BINNAME=vain
DEF_FILE_LOC=/usr/share/vainglorious/
DEF_FILE_NAME=default.scroll
BINLOC=/usr/local/bin

SRC = main.cpp args.cpp render.cpp util.cpp file.cpp theme.cpp
OBJ = main.o args.o render.o util.o file.o theme.o
FLAGS=-lncurses
# to be added by the user
EXTRAS=

CC=g++
DEF_FILE=${DEF_FILE_LOC}${DEF_FILE_NAME}

default: compile link

compile: ${SRC}
	${CC} -c ${SRC} -DDEF_FILE=\"${DEF_FILE}\" ${EXTRAS}

link: ${OBJ}
	${CC} -o ${BINNAME} ${OBJ} ${FLAGS} -DDEF_FILE=\"${DEF_FILE}\" ${EXTRAS}

install: ${BINNAME}
	mkdir -p ${DEF_FILE_LOC}
	cp data/default.scroll ${DEF_FILE}
	chmod 644 ${DEF_FILE}
	cp ${BINNAME} ${BINLOC}/

clean:
	rm -f ${OBJ}

debug:
	${CC} -o ${BINNAME} ${SRC} ${FLAGS} -DDEF_FILE=\"${DEF_FILE}\" -ggdb

