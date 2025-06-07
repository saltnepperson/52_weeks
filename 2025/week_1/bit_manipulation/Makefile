CC=gcc
CFLAGS=-Wall -g
OBJ=main.o

build: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $<

run: build
	./main