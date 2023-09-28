#pragma once

#include<stdio.h>
#include<stdlib.h>
#include "mybtree.h"

typedef struct heaptype{
	btreenode* heap[1024];
	int heap_size;
}heaptype;

void init_heap(heaptype* h);
heaptype *create();

void insert_min_heap(heaptype *h,btreenode* e);
btreenode* delete_min_heap(heaptype *h);
