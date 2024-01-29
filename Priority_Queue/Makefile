sort: main.o priority_queue.o
	gcc -o sort main.o priority_queue.o

main.o: main.c
	gcc -c -o main.o main.c

priority_queue.o: priority_queue.c
	gcc -c -o priority_queue.o priority_queue.c

run: sort
	./sort

valgrind: sort
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --show-reachable=yes ./sort

clean:
	rm -rf sort main.o priority_queue.o
