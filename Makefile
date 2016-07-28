CFLAGS=-Wall -g

program: main.o tpqdb.o
	cc -o bin/tpqdb obj/main.o obj/tpqdb.o -v

main.o: 
	cc -c src/main.c -o obj/main.o
tpqdb.o: 
	cc -c src/tpqdb.c -o obj/tpqdb.o

clean:
	rm -rf bin/tpqdb obj/*.o
