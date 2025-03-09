CC = gcc
DEBUG_FLAGS = -ggdb
SRC = ./src
OBJ = ./obj

$(OBJ)/io.o: $(SRC)/io.c
	$(CC) -c $(SRC)/io.c -o $(OBJ)/io.o $(DEBUG_FLAGS)

$(OBJ)/main.o: $(SRC)/main.c
	$(CC) -c $(SRC)/main.c -o $(OBJ)/main.o

output: $(OBJ)/io.o $(OBJ)/main.o
	$(CC) -o output $(OBJ)/main.o $(OBJ)/io.o $(DEBUG_FLAGS)

clean:
	rm output
	rm $(OBJ)/*.o
