CC=g++
CFLAGS=-lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_image -std=c++11
EXEC=game

all: clean buildfolder $(EXEC)

game: ./build/main.o
	$(CC) ./build/*.o -o game $(CFLAGS)

./build/main.o: main.cpp ./build/tools.o ./build/window.o ./build/player.o ./build/text.o 
	$(CC) -o ./build/main.o -c main.cpp -I ./include $(CFLAGS)

./build/tools.o: ./src/tools.cpp 
	$(CC) -o ./build/tools.o -c ./src/tools.cpp -I ./include $(CFLAGS)

./build/window.o: ./src/window.cpp ./build/tools.o 
	$(CC) -o ./build/window.o -c ./src/window.cpp -I ./include $(CFLAGS)

./build/player.o: ./src/player.cpp ./build/window.o ./build/tools.o 
	$(CC) -o ./build/player.o -c ./src/player.cpp -I ./include $(CFLAGS)

./build/text.o: ./src/text.cpp ./build/tools.o 
	$(CC) -o ./build/text.o -c ./src/text.cpp -I ./include $(CFLAGS)


#for testing sdl lib
testsdl: testsdl.cpp
	$(CC) -o testsdl testsdl.cpp -lSDL2main -lSDL2

clean:
	rm -rf build/

buildfolder:
	@mkdir build
