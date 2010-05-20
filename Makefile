UNAME := $(shell uname)
ifeq ($(UNAME), Darwin)
LDFLAGS=-framework OpenGL -framework GLUT
else
LDFLAGS=-lglut
endif

CFLAGS=-O -Wall -Werror -Wextra -pedantic -std=c99

all: main test_maze

main: main.o maze.o malloc.o

test_maze: test_maze.o maze.o malloc.o
