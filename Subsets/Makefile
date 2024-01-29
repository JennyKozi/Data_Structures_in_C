subsets: main.o stack.o
	gcc -o subsets main.o stack.o

main.o: main.c
	gcc -c -o main.o main.c

stack.o: stack.c
	gcc -c -o stack.o stack.c

run: subsets
	./subsets

clean:
	rm -rf subsets main.o stack.o
