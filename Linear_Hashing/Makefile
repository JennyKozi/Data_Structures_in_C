mvote: main.o hash_table.o 2d_list.o
	gcc -o mvote main.o hash_table.o 2d_list.o

main.o: main.c
	gcc -c -o main.o main.c

hash_table.o: hash_table.c
	gcc -c -o hash_table.o hash_table.c

2d_list.o: 2d_list.c
	gcc -c -o 2d_list.o 2d_list.c

run:
	./mvote -f data/voters50000.csv -b 4

valgrind:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --show-reachable=yes ./mvote -f data/voters500.csv -b 3

clean:
	rm -rf mvote main.o hash_table.o 2d_list.o