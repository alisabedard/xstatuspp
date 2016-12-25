CFLAGS=-O0 -W -Wall -Werror -march=sandybridge -pipe -ggdb
CFLAGS+=-DLINUX
CFLAGS+=-D_GNU_SOURCE
CC=/usr/bin/cc
static=libjb/libjb.a
