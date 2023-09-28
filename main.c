#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include "mybtree.h"
#include "myhtree.h"
#define NUM_ASCII 128
#define MAX_DATA 1024

typedef struct table{
	char ch;
	char code[MAX_DATA];
}table;

int is_leaf(btreenode* node)
{
	return (node->right == NULL && node->left == NULL);
}

/* huffman tree를 만드는 함수 */

btreenode* huffmantree(int freq[])
{
	heaptype *h = create();
	init_heap(h);
	btreenode* tmp;
	int i;

	for(i=0;i<NUM_ASCII;i++)
	{
		if(freq[i] != 0)
		{
			tmp = makebtreenode();
			tmp->ch = (char)i;
			tmp->freq = freq[i];
			insert_min_heap(h,tmp);
		}
	}

	for(i=0;h->heap_size >= 2;i++)
	{
		tmp = makebtreenode();
		tmp->ch = '\0';
		makeleftnode(tmp,delete_min_heap(h));
		makerightnode(tmp,delete_min_heap(h));
		tmp->freq = tmp->left->freq + tmp->right->freq;
		insert_min_heap(h,tmp);
	}
	tmp = h->heap[h->heap_size--];

	return tmp;
}

/* 코딩 전 문자의 빈도수를 측정하는 함수 */

void preincode(char st[],int len,int freq[])
{
	int i;

	for(i=0;i<len;i++)
	{
		freq[(int)st[i]]++;
	}
}

/* 만들어진 hufffman tree를 가지고 huffman code를 만듦 */

void huffmancode(btreenode *root,int cd[],table* t,int index)
{
	int i;
	if(root->left)
	{
		cd[index] = 1;
		huffmancode(root->left,cd,t,index+1);
	}
	if(root->right)
	{
		cd[index] = 0;
		huffmancode(root->right,cd,t,index+1);
	}
	if(is_leaf(root))
	{
		t[(int)root->ch].ch = root->ch;
		
		for(i=0;i<index;i++)
		{
			t[(int)root->ch].code[i] = cd[i]+48;
		}
		t[(int)root->ch].code[i] = '\0';
	}

}

/* Encode 함수, 만든 huffman code를 file로 내보냄 */

void encoding(char st[],table *t,int size)
{
	int fd, i;

	fd = open("huffman_encode.txt", O_WRONLY | O_CREAT | O_TRUNC, 0664);
	
	for(i=0;i < size;i++)
	{
		dprintf(fd,"%s",t[st[i]].code);	
	}
	close(fd);
}

/* Decode 함수 */

void decoding(btreenode *root)
{
	int i, fd1, fd2, size;
	char code[MAX_DATA];
	btreenode *tmp = root;

	fd1 = open("huffman_encode.txt", O_RDONLY, 0664);
	fd2 = open("huffman_decode.txt", O_WRONLY | O_CREAT | O_TRUNC, 0664);
	while(1)
	{
		size = read(fd1,code,MAX_DATA);
		if(!size) break;

		for(i=0;i<size+1;i++)
		{
			if(is_leaf(tmp))
			{
				dprintf(fd2,"%c",tmp->ch);
				tmp = root;
			}
			if(code[i] == '0')
			{
				tmp = tmp->right;
			}
			else if(code[i] == '1')
			{
				tmp = tmp->left;
			}
		}
	}

	close(fd1);
	close(fd2);
}

int main(int argc,char* argv[])
{
	int i, cd[MAX_DATA], fd, size;
	int charfreq[NUM_ASCII] = {0,};
	char st[MAX_DATA], c;
	btreenode *root;

	if(argc != 2) 
	{
		printf("wrong usage\n");
		return 0;
	}	

	fd = open(argv[1],O_RDONLY);

	size = read(fd,st,MAX_DATA);

	st[size] = '\0';

	preincode(st,size,charfreq);
	root = huffmantree(charfreq);

	table *t = (table*)calloc(NUM_ASCII,sizeof(table));
	
	huffmancode(root,cd,t,0);

	encoding(st,t,size);

	printf("------------Encoding-----------\n");
	sleep(1);
	printf("Encoding Complete : huffman_encode.txt\n");
	printf("Do you want to decode it? : <y/n> ");
	scanf("%c",&c);
	if(c == 'y')
	{
		decoding(root);
		printf("-----------Decoding-----------\n");
		sleep(1);
		printf("Decoding Complete : huffman_decode.txt\n");
	}

	removenode(root);
	free(t);

	return 0;
}
