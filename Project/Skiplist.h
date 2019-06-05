#pragma once
#pragma warning(disable:4996)
#ifndef _SKIPLIST_H_
#define _SKIPLIST_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <iostream>
#include <random>
#include <vector>	// vector
#include <algorithm>	// shuffle
#include <ctime>	// time
#include <chrono> //for random

//maximum number of level
#define MAXLEVEL 24
//maximum times for search
#define MAX 10000
//debug model(for testing)
#define DEBUG 0

//define the type and structure of key, Node and skip list
typedef int ElementType;
typedef struct node Node;
struct node
{
	ElementType key;
	Node** forward;
	//the forward is a pointer array containing all the successors of the node in every level with its existence.
};

typedef struct skiplist SkipList;
struct skiplist
{
	int level;
	Node* head; // the head of the skip list
};

//create a skiplist with no key node and if successful the function returns a pointer to it, otherwise NULL
SkipList* CreateSL(int inrec_p);//p is the variable controlling the probabilty

//create a new node with random level and definite key
Node* CreateNode(int level, ElementType key);

//when insert a node with value key, the level of the new node is decided by a random algorithm
int RandomLevel();

//for insertion: if successful, return true; else return false
bool Insert(SkipList *sl, ElementType key);

//for deletion: if successful, return true; else return false
bool Delete(SkipList *sl, ElementType key);

//for searching a node with key:  if successful, return its address; else return NULL
void Search(SkipList *sl, ElementType key);

//for outputing the trace of searching a node in skip list
void PrintTrace(ElementType route[][2], int row);

//for outputing the structure of the skiplist
void Print(SkipList *sl);

//to destroy the whole skiplist and free for room
void Free(SkipList *sl);

//reset the global variable factor rec_p
void setFactorP(int p);

void test();
#endif // !_SKIPLIST_H_
