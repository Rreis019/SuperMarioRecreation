CC = g++
CFLAGS 	= -IC:/mingw64/include -Wall  -Iinclude#include flags 

MYSQLIB =  -LC:/mingw64/lib -lmysqlclient -lmysql
LDFLAGS = -lws2_32#linker flags
SRC = $(wildcard src/*.cpp) 
OBJ  =  $(SRC:.cpp=.o)

BIN = bin/Release/serverSQL.exe
all: CFLAGS += -O3
all: LDFLAGS += -static-libstdc++ -static-libgcc
all: LDFLAGS += -s #remove debug symbols
all: link 
all: execute

debug: CFLAGS += -DDEBUG -g
debug: BIN = bin/Debug/serverSQL.exe
debug: link
debug: execute
dirs:
	mkdir src
	@echo > src/main.cpp
	mkdir include
	mkdir bin
	cd bin && mkdir Debug && mkdir Release
execute: 
	$(BIN)

link: $(OBJ)
	$(CC)  $(MYSQLIB) $^ $(LDFLAGS) -o  $(BIN) 

%.o: %.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	del src\*.o


