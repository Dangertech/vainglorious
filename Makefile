BINNAME=vain
DEF_FILE=/usr/share/vainglorious/defscroll.txt

CC=g++

SRC=main.cpp args.cpp render.cpp util.cpp
FLAGS=-lncurses

build:
	${CC} -o ${BINNAME} ${SRC} ${FLAGS} -DDEF_FILE=\"${DEF_FILE}\"

debug:
	${CC} -o ${BINNAME} ${SRC} ${FLAGS} -DDEF_FILE=\"${DEF_FILE}\" -ggdb
