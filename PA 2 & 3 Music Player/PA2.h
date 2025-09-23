/*

*/

#ifndef PA2_H
#define PA2_H

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct duration
{
	int minute, seconds;
} Duration;

typedef struct record
{
	char artist[25], album[25], song[25], genre[25];
	Duration length;
	int timesPlayed, rating;
} Record;

typedef struct node
{
	Record data;
	struct node* pLink, * pPrev;
} Node;

typedef enum displaytype
{
	JUSTPRINT, ARTIST
} displayType;

typedef enum sorttype
{
	ARTIST1, ALBUM, RATING, TIMESPLAYED
} sortType;

char* addQuote(char artist[]);
Node* createNode(Record musicRecord);
bool insertContactAtFront(Node** pList, Record newData);
bool insertContactInOrder(Node** pList, Record newData, sortType type);
bool deleteContact(Node** pList, char* song);
bool deleteAll(Node** pList);
bool editContact(Node* pList, Record searchRecord, int mode);
bool storeContacts(FILE* infile, Node* pList);
void displayList(Node* pList, displayType dis, char name[]);
bool load(FILE* infile, Node** headPtr, int* count);
bool shuffleList(int order[], const int count);
void play(Node* headPtr, const int count, int order[]);
bool loadSort(FILE* infile, Node** headPtr, int* count, sortType type);

#endif
