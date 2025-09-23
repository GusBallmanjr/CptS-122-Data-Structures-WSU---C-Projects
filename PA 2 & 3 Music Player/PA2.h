/*
	Programmer: Gus Ballman
	Class: CptS 122, Lab Section 01
	Date: 9/22/2025
	Description: Program reads music record data (artist name, song name, album name, genre name, rating, timesplayed, length of the song) from a csv file and will allow the user to select from 11 differnt options. Option one loads the information from the file 
	into a doubly linked list and insert each new line of data into its own record node at the front of teh linked list. Option two stores the data that is in the linked list into the csv file after deleting the cvs file's previous contents. Option 3 will display 
	either all of the records stored in the linked list, or one artist in which the user chooses. Option 4 will allow the user to manually insert a new record into the linked list. Option 5 allows teh user to delete a record from the linked list, Option 6 will allow 
	the user to edit any attribute of a record. Option 7 will allow the user to sort the data by artist name, album name, timesplayed, or the rating of the song. Option 8 allows the user to edit teh rating of any particular song. Option 9 allows the user to display
	the songs in the order that they are given (this mimicks a play feature). Option 10 randomly shuffles the order of the songs. Option 11 stores the stored records into the csv file and will terminate the program.
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

