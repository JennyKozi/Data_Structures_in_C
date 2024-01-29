project: main.o doubly-linked-list.o
	gcc -o project main.o doubly-linked-list.o

main.o: main.c
	gcc -c -o main.o main.c

doubly-linked-list.o: doubly-linked-list.c
	gcc -c -o doubly-linked-list.o doubly-linked-list.c

run: project
	./project

valgrind: project
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --show-reachable=yes ./project

clean:
	rm -rf project main.o doubly-linked-list.o
