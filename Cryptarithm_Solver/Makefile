cryptarithm: main.o stack.o
	gcc -o cryptarithm main.o stack.o

main.o: main.c
	gcc -c -o main.o main.c

stack.o: stack.c
	gcc -c -o stack.o stack.c

run: cryptarithm
	./cryptarithm

clean:
	rm -rf cryptarithm main.o stack.o
