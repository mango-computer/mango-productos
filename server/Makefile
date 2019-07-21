# Makefile

SHELL := sh -e
SCRIPTS = "debian/postinst configure" "debian/postrm remove"
CFLAGS = `pkg-config --cflags --libs gtk+-3.0 gmodule-2.0 gthread-2.0`
PROJECT_NAME = Mango Camila
BIN_NAME = server-mp

# -O0 -Wall -Wextra -ggdb

all: build

build:

	gcc servidor_mp.c $(CFLAGS) -o $(BIN_NAME) -lpthread -std=c99 -O0 -Wall -Wextra


