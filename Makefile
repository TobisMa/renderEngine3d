all: game

game:
	gcc -std=c99 -I ./include -I src src/*.c -o main -Wall -Wno-missing-braces -L ./lib/ -lraylib -lopengl32 -lgdi32 -lwinmm
