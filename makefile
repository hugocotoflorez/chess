FILES = board.c pieces.c graphics.c main.c
EXEC_NAME = chess

CC = gcc -Wall

all:
	$(CC) $(FILES) -o $(EXEC_NAME)


debug:
	$(CC) $(FILES) -o $(EXEC_NAME) -g


fast:
	$(CC) $(FILES) -o $(EXEC_NAME) -O3
