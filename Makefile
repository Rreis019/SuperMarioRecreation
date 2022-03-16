CC = g++
CFLAGS 	= -IC:/mingw64/include -Wall  -Iinclude#include flags 
LDFLAGS = -LC:/mingw64/lib   -lmingw32 -lSDL2main -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lSDL2 -lws2_32 #linker flags
SRC = $(wildcard src/*.cpp src/Core/*.cpp src/Screens/*.cpp src/GUI/*.cpp src/Entities/*.cpp) 
OBJ  =  $(SRC:.cpp=.o)

BIN = bin/Release/SuperMario.exe
all: CFLAGS += -O3
all : LDFLAGS += -static-libstdc++ -static-libgcc #include libstd++ and libgcc on executable to be able run another machine 
all: LDFLAGS += -s #remove debug symbols
all: link 
all: execute

debug: CFLAGS += -DDEBUG -g
debug: BIN = bin/Debug/SuperMario.exe
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
	$(CC)   $^ $(LDFLAGS) -o  $(BIN)

%.o: %.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	del src\*.o  src\Core\*.o src\GUI\*.o src\Entities\*.o  src\Screens\*.o


