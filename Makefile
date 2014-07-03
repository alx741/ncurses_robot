CC = gcc
LIBS = -lncurses -lmenu -lform -lpanel

interface:
	${CC} game.c interface.c queue.c commands.c hdwr/driver.c  -o robot ${LIBS} -g

