prog: main.o graph.o list.o queue.o
	gcc main.o graph.o list.o queue.o -o prog
	
main.o: main.c
	gcc -c -o main.o main.c

graph.o: graph.c
	gcc -c -o graph.o graph.c
	
list.o: list.c
	gcc -c -o list.o list.c
	
queue.o: queue.c
	gcc -c -o queue.o queue.c

run:
	./prog graph.txt

valgrind:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --show-reachable=yes ./prog graph.txt

clean:
	rm -rf prog main.o graph.o list.o queue.o