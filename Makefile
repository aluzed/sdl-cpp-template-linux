CC=g++
CFLAGS=-lSDL2main -lSDL2 -std=c++11
EXEC=game

all: $(EXEC)

game: ./build/main.o
	$(CC) ./build/*.o -o game $(CFLAGS)

./build/main.o: main.cpp ./build/window.o ./build/player.o
	$(CC) -o ./build/main.o -c main.cpp -I ./include $(CFLAGS)

./build/player.o: ./src/player.cpp ./build/window.o
	$(CC) -o ./build/player.o -c ./src/player.cpp -I ./include $(CFLAGS)

./build/window.o: ./src/window.cpp
	$(CC) -o ./build/window.o -c ./src/window.cpp -I ./include $(CFLAGS)

#for testing sdl lib
testsdl: testsdl.cpp
	$(CC) -o testsdl testsdl.cpp -lSDL2main -lSDL2

clean:
	rm -rf build/*