huffman_tree_exe : mybtree.o myhtree.o main.o
	gcc -g -o huffman_tree_exe mybtree.o myhtree.o main.o

mybtree.o : mybtree.c
	gcc -g -c -o mybtree.o mybtree.c

myhtree.o : myhtree.c
	gcc -g -c -o myhtree.o myhtree.c

main.o : main.c
	gcc -g -c -o main.o main.c

clean :
	rm *.o huffman_tree_exe
