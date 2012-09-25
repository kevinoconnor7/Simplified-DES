CC=g++
CFLAGS=-I.
DEPS = des.h
OBJ = des.o main.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

sdes: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)