mergesort: main.o list.o
	gcc -o mergesort main.o list.o

main.o: main.c
	gcc -c -o main.o main.c

list.o: list.c
	gcc -c -o list.o list.c

run: mergesort
	./mergesort

valgrind: mergesort
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --show-reachable=yes ./mergesort

clean:
	rm -rf mergesort main.o list.o
