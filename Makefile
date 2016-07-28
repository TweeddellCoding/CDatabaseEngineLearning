CFLAGS=-Wall -g

program: main.o tpqdb.o
	cc -o tpqdb main.o tpqdb.o

main.o: main.c
	cc -c main.c
tpqdb.o: tpqdb.c tpqdb.h
	cc -c tpqdb.c

clean:
	rm -rf tpqdb *.o