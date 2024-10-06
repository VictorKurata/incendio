CC=gcc
CFLAGS=-pthread -Wall
OBJ=main.o functions.o

all: incendio_simulacao

incendio_simulacao: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJ) incendio_simulacao
