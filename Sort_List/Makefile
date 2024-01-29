sort: main.o list.o
	gcc -o sort main.o list.o

main.o: main.c
	gcc -c -o main.o main.c

list.o: list.c
	gcc -c -o list.o list.c

run: sort
	./sort

valgrind: sort
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --show-reachable=yes ./sort

clean:
	rm -rf sort main.o list.o
