UNAME := $(shell uname)
ifeq ($(UNAME), Darwin)
LDFLAGS=-framework OpenGL -framework GLUT
else
LDFLAGS=-lglut
endif

CFLAGS=-O -Wall -Werror -Wextra -pedantic -std=c99

all: main
