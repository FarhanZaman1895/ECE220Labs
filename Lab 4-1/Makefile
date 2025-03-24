CC = gcc
DEBUG_FLAGS = -ggdb
SRC = ./src
OBJ = ./obj

output: $(OBJ)/buffer.o  $(OBJ)/io.o $(OBJ)/main.o
	$(CC) -o output $(OBJ)/*.o $(DEBUG_FLAGS)

$(OBJ)/buffer.o: $(SRC)/buffer.c
	$(CC) -c $(SRC)/buffer.c -o $(OBJ)/buffer.o $(DEBUG_FLAGS)

$(OBJ)/io.o: $(SRC)/io.c
	$(CC) -c $(SRC)/io.c -o $(OBJ)/io.o $(DEBUG_FLAGS)

$(OBJ)/main.o: $(SRC)/main.c
	$(CC) -c $(SRC)/main.c -o $(OBJ)/main.o $(DEBUG_FLAGS)

clean:
	rm output
	rm $(OBJ)/*.o
