#pragma once

#include<stdio.h>
#include<stdlib.h>

typedef struct btreenode{
	char ch;
	int freq;
	int code[50];
	struct btreenode *left;
	struct btreenode *right;
}btreenode;

btreenode *makebtreenode();

void makeleftnode(btreenode *parent, btreenode *child);
void makerightnode(btreenode *parent, btreenode *child);

void removenode(btreenode *t);
