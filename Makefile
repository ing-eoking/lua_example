CC=gcc
CFLAGS= -Wall -g -O -I deps/lua/src/

LUA_CORE = $(patsubst %.o, deps/lua/src/%.o, \
	lapi.o lcode.o lctype.o ldebug.o ldo.o ldump.o lfunc.o lgc.o llex.o \
	lmem.o lobject.o lopcodes.o lparser.o lstate.o lstring.o ltable.o \
	ltm.o lundump.o lvm.o lzio.o)
LUA_LIB = $(patsubst %.o, deps/lua/src/%.o, \
	lauxlib.o lbaselib.o lcorolib.o ldblib.o liolib.o \
	lmathlib.o loslib.o lstrlib.o ltablib.o lutf8lib.o loadlib.o linit.o)

all: main
main: main.o $(LUA_LIB) $(LUA_CORE)
	$(CC) main.o $(LUA_LIB) $(LUA_CORE) -o main -lm

main.o: main.c
	make -C deps/lua
	$(CC) -c main.c -o main.o $(CFLAGS)

clean:
	rm -rf main
	rm -rf *.o
	rm -rf deps/lua/src/*.o
