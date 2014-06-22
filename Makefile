CC = gcc
LIBS = -lncurses -lmenu -lform -lpanel

interface:
	${CC} interface.c -o inter ${LIBS}

