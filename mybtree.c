#include<stdio.h>
#include<stdlib.h>
#include "mybtree.h"

btreenode *makebtreenode()
{
	btreenode *tmp;
	tmp = (btreenode*)malloc(sizeof(btreenode));
	tmp->left = NULL;
	tmp->right = NULL;

	return tmp;
}

void makeleftnode(btreenode *parent, btreenode *child)
{
	if(parent->left != NULL)
	{
		removenode(parent->left);
	}
	parent->left = child;
}

void makerightnode(btreenode *parent, btreenode *child)
{
	if(parent->right != NULL)
	{
		removenode(parent->right);
	}
	parent->right = child;
}

void removenode(btreenode *t)
{
	if(t == NULL)
	{
		return;
	}
	removenode(t->left);
	removenode(t->right);
	free(t);
	t = NULL;
}
