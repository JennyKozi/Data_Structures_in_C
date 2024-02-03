2-4tree: main.o 2-4tree.o
	gcc main.o 2-4tree.o -o 2-4tree

main.o: main.c
	gcc -c -o main.o main.c

2-4tree.o: 2-4tree.c
	gcc -c -o 2-4tree.o 2-4tree.c

run:
	./2-4tree

valgrind:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --show-reachable=yes ./2-4tree

clean:
	rm -rf 2-4tree main.o 2-4tree.o