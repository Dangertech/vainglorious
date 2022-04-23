BINNAME=vain
DEF_FILE_LOC=/usr/share/vainglorious/
DEF_FILE_NAME=default.scroll
BINLOC=/usr/local/bin

CC=g++
DEF_FILE=${DEF_FILE_LOC}${DEF_FILE_NAME}

SRC=main.cpp args.cpp render.cpp util.cpp file.cpp theme.cpp
FLAGS=-lncurses

build:
	${CC} -o ${BINNAME} ${SRC} ${FLAGS} -DDEF_FILE=\"${DEF_FILE}\"

install: build
	mkdir -p ${DEF_FILE_LOC}
	cp data/default.scroll ${DEF_FILE_LOC}${DEF_FILE_NAME}
	cp ${BINNAME} ${BINLOC}/

debug:
	${CC} -o ${BINNAME} ${SRC} ${FLAGS} -DDEF_FILE=\"${DEF_FILE}\" -ggdb
