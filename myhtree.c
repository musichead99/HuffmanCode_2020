// 최소 힙 트리 //
#include<stdio.h>
#include<stdlib.h>
#include "mybtree.h"
#include "myhtree.h"

void init_heap(heaptype* h)
{
	h->heap_size = 0;
}

heaptype *create()
{
	return (heaptype*)malloc(sizeof(heaptype));
}

void insert_min_heap(heaptype *h,btreenode *e)
{
	int i = ++h->heap_size;

	while(i != 1 && e->freq < h->heap[i/2]->freq)
	{
		h->heap[i] = h->heap[i/2];
		i /= 2;
	}
	h->heap[i] = e;
}

btreenode* delete_min_heap(heaptype *h)
{
	int parent = 1;
	int child = 2;
	btreenode* item = h->heap[1];
	btreenode* tmp = h->heap[h->heap_size--];

	while(child <= h->heap_size)
	{
		if((child < h->heap_size) && (h->heap[child]->freq > h->heap[child+1]->freq))
		{
			child++;
		}
		if(tmp->freq <= h->heap[child]->freq) break;

		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent] = tmp;
	return item;
}
