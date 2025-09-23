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

#include "PA2.h"

Node* createNode(Record musicRecord)
{
	Node* pMem = malloc(sizeof(Node));
	if (pMem != NULL)
	{
		// Memory successfully allocated
		pMem->pLink = NULL;
		strcpy(pMem->data.artist, musicRecord.artist);
		strcpy(pMem->data.album, musicRecord.album);
		strcpy(pMem->data.song, musicRecord.song);
		strcpy(pMem->data.genre, musicRecord.genre);
		pMem->data.length.minute = musicRecord.length.minute;
		pMem->data.length.seconds = musicRecord.length.seconds;
		pMem->data.timesPlayed = musicRecord.timesPlayed;
		pMem->data.rating = musicRecord.rating;
	}
	return pMem;
}

bool insertContactAtFront(Node** pList, Record newData)
{
	Node* pCur = createNode(newData);
	if (*pList == NULL)
	{
		*pList = pCur;
		(*pList)->pPrev = NULL;
		(*pList)->pLink = NULL;
		return true;
	}
	if (pCur != NULL && *pList != NULL)
	{
		pCur->pLink = *pList;
		(*pList)->pPrev = pCur;
		pCur->pPrev = NULL;
		*pList = pCur;
		return true;
	}
	else
	{
		return false;
	}
}

bool insertContactInOrder(Node** pList, Record newData, sortType type)
{
	Node* pCur = createNode(newData), * pNext = *pList;
	bool success = false;
	while (success == false)
	{
		if (type == ARTIST1) // Sort by artist (A-Z)
		{
			char* artist = pCur->data.artist, * nextArtist = pNext->data.artist;
			if (artist[0] == '\"')
			{
				++artist;
			}
			if (nextArtist[0] == '\"')
			{
				++nextArtist;
			}
			if (pCur == NULL)
			{
				goto end;
			}
			if (strcmp(artist, nextArtist) > 0)
			{
				if (pNext->pLink == NULL)
				{
					// Enters in alphabetically at the end
					pCur->pLink = pNext->pLink;
					pNext->pLink = pCur;
					pCur->pPrev = pNext;
					success = true;
				}
				else
				{
					char* linkArtist = pNext->pLink->data.artist;
					if (linkArtist[0] == '\"')
					{
						++linkArtist;
					}
					if (strcmp(artist, linkArtist) <= 0)
					{
						// Enters in alphabetically
						pCur->pLink = pNext->pLink;
						pNext->pLink = pCur;
						pCur->pPrev = pNext;
						pCur->pLink->pPrev = pCur;
						success = true;
					}
					else
					{
						// needs to move along linked list
						pNext = pNext->pLink;
					}
				}

			}
			else // Comes before first node alphabetically
			{
				if (pCur != NULL)
				{
					pCur->pLink = *pList;
					(*pList)->pPrev = pCur;
					pCur->pPrev = NULL;
					*pList = pCur;
					success = true;
				}
			}

		}
		else if (type == ALBUM) // Sort by album name (A-Z)
		{
			if (pCur == NULL)
			{
				goto end;
			}
			if (strcmp(pCur->data.album, pNext->data.album) > 0)
			{
				if (pNext->pLink == NULL)
				{
					// Enters in alphabetically at the end
					pCur->pLink = pNext->pLink;
					pNext->pLink = pCur;
					pCur->pPrev = pNext;
					success = true;
				}
				else if (strcmp(pCur->data.album, pNext->pLink->data.album) <= 0)
				{
					// Enters in alphabetically
					pCur->pLink = pNext->pLink;
					pNext->pLink = pCur;
					pCur->pPrev = pNext;
					pCur->pLink->pPrev = pCur;
					success = true;
				}
				else
				{
					// needs to move along linked list
					pNext = pNext->pLink;
				}

			}
			else // Comes before first node alphabetically
			{
				if (pCur != NULL)
				{
					pCur->pLink = *pList;
					(*pList)->pPrev = pCur;
					pCur->pPrev = NULL;
					*pList = pCur;
					success = true;
				}
			}
		}
		else if (type == RATING) // Sort by Rating (1-5)
		{
			if (pCur == NULL)
			{
				goto end;
			}
			if ((pCur->data.rating > pNext->data.rating))
			{
				if (pNext->pLink == NULL)
				{
					// Enters in at the end
					pCur->pLink = pNext->pLink;
					pNext->pLink = pCur;
					pCur->pPrev = pNext;
					success = true;
				}
				else if (pCur->data.rating <= pNext->pLink->data.rating)
				{
					// Enters in
					pCur->pLink = pNext->pLink;
					pNext->pLink = pCur;
					pCur->pPrev = pNext;
					pCur->pLink->pPrev = pCur;
					success = true;
				}
				else
				{
					// needs to move along linked list
					pNext = pNext->pLink;
				}

			}
			else // Comes before first node
			{
				if (pCur != NULL)
				{
					pCur->pLink = *pList;
					(*pList)->pPrev = pCur;
					pCur->pPrev = NULL;
					*pList = pCur;
					success = true;
				}
			}
		}
		else if (type == TIMESPLAYED) // Sort by times played (largest-smallest)
		{
			if (pCur == NULL)
			{
				goto end;
			}
			if ((pCur->data.timesPlayed > pNext->data.timesPlayed))
			{
				if (pNext->pLink == NULL)
				{
					// Enters in at the end
					pCur->pLink = pNext->pLink;
					pNext->pLink = pCur;
					pCur->pPrev = pNext;
					success = true;
				}
				else if (pCur->data.timesPlayed <= pNext->pLink->data.timesPlayed)
				{
					// Enters in
					pCur->pLink = pNext->pLink;
					pNext->pLink = pCur;
					pCur->pPrev = pNext;
					pCur->pLink->pPrev = pCur;
					success = true;
				}
				else 
				{
					// needs to move along linked list
					pNext = pNext->pLink;
				}

			}
			else // Comes before first node
			{
				if (pCur != NULL)
				{
					pCur->pLink = *pList;
					(*pList)->pPrev = pCur;
					pCur->pPrev = NULL;
					*pList = pCur;
					success = true;
				}
			}
		}
	}
	end:
	return success;
}

bool deleteContact(Node** pList, char* song)
{
	Node* pCur = *pList;
	bool success = false;

	if (pCur == NULL)
	{
		return success;
	}
	while (pCur != NULL && success == false)
	{
		if (strcmp(pCur->data.song, song) == 0 && pCur == (*pList))
		{
			// Found Contact - deleting first node
			*pList = pCur->pLink;
			if (*pList != NULL)
			{
				(*pList)->pPrev = NULL;
			}
			free(pCur);
			success = true;
		}
		else if (strcmp(pCur->data.song, song) == 0 && pCur != (*pList))
		{
			pCur->pPrev->pLink = pCur->pLink;
			pCur->pLink->pPrev = pCur->pPrev;
			free(pCur);
			success = true;
		}
		else
		{
			// needs to move along linked list
			if (pCur->pLink == NULL && success == false)
			{
				break; // Not Found before end of list
			}
			else
			{
				pCur = pCur->pLink;
			}
		}
	}
	return success;
}

bool deleteAll(Node** pList)
{
	Node* pCur = *pList;

	if (pCur == NULL)
	{
		return false;
	}
	while (*pList != NULL)
	{
		pCur = *pList;
		*pList = pCur->pLink;
		free(pCur);
	}
	return true;
}

bool editContact(Node* pList, Record searchRecord, int mode)
{
	Node* pCur = pList;
	bool success = false;
	char change[50] = "", answer = '\0';
	int changeNum = 0;

	while (success == false)
	{
		if (strcmp(pCur->data.artist, searchRecord.artist) == 0 && strcmp(pCur->data.song, searchRecord.song) == 0)
		{
			success = true;
		}
		else
		{
			// needs to move along linked list
			if (pCur->pLink == NULL && success == false)
			{
				goto end; // Not Found before end of list
			}
			else
			{
				pCur = pCur->pLink;
			}
		}
	}

	if (mode == 1)
	{
		goto rating1;
	}

	name: 
	fputs("Would you like to edit the artist name for this record\? (Y/N)\n", stdout);
	scanf(" %c", &answer);
	if (answer != 'Y' && answer != 'N')
	{
		fputs("Invalid Input, Try Again.\n", stdout);
		system("Pause");
		system("cls");
		goto name;
	}
	else if (answer == 'Y')
	{
		fputs("What would you like to change it to\? ", stdout);
		getchar();
		for (int i = 0; i < 25; ++i)
		{
			scanf("%c", &change[i]);
			if (change[i] == '\n')
			{
				change[i] = '\0';
				break;
			}
		}
		strcpy(pCur->data.artist, change);
		success == true;
	}

	album:
	fputs("Would you like to edit the album name for this record\? (Y/N)\n", stdout);
	scanf(" %c", &answer);
	if (answer != 'Y' && answer != 'N')
	{
		fputs("Invalid Input, Try Again.\n", stdout);
		system("Pause");
		system("cls");
		goto album;
	}
	else if (answer == 'Y')
	{
		fputs("What would you like to change it to\? ", stdout);
		getchar();
		for (int i = 0; i < 25; ++i)
		{
			scanf("%c", &change[i]);
			if (change[i] == '\n')
			{
				change[i] = '\0';
				break;
			}
		}
		strcpy(pCur->data.album, change);
		success == true;
	}

	song:
	fputs("Would you like to edit the song name for this record\? (Y/N)\n", stdout);
	scanf(" %c", &answer);
	if (answer != 'Y' && answer != 'N')
	{
		fputs("Invalid Input, Try Again.\n", stdout);
		system("Pause");
		system("cls");
		goto song;
	}
	else if (answer == 'Y')
	{
		fputs("What would you like to change it to\? ", stdout);
		getchar();
		for (int i = 0; i < 25; ++i)
		{
			scanf("%c", &change[i]);
			if (change[i] == '\n')
			{
				change[i] = '\0';
				break;
			}
		}
		strcpy(pCur->data.song, change);
		success == true;
	}

	genre:
	fputs("Would you like to edit the genre for this record\? (Y/N)\n", stdout);
	scanf(" %c", &answer);
	if (answer != 'Y' && answer != 'N')
	{
		fputs("Invalid Input, Try Again.\n", stdout);
		system("Pause");
		system("cls");
		goto genre;
	}
	else if (answer == 'Y')
	{
		fputs("What would you like to change it to\? ", stdout);
		getchar();
		for (int i = 0; i < 25; ++i)
		{
			scanf("%c", &change[i]);
			if (change[i] == '\n')
			{
				change[i] = '\0';
				break;
			}
		}
		strcpy(pCur->data.song, change);
		success == true;
	}

	minutes:
	fputs("Would you like to edit the length in minutes for this record\? (Y/N)\n", stdout);
	scanf(" %c", &answer);
	if (answer != 'Y' && answer != 'N')
	{
		fputs("Invalid Input, Try Again.\n", stdout);
		system("Pause");
		system("cls");
		goto minutes;
	}
	else if (answer == 'Y')
	{
		fputs("What would you like to change it to\? ", stdout);
		scanf("%d", &changeNum);
		pCur->data.length.minute = changeNum;
		success == true;
	}

	seconds:
	fputs("Would you like to edit the length in seconds for this record\? (Y/N)\n", stdout);
	scanf(" %c", &answer);
	if (answer != 'Y' && answer != 'N')
	{
		fputs("Invalid Input, Try Again.\n", stdout);
		system("Pause");
		system("cls");
		goto seconds;
	}
	else if (answer == 'Y')
	{
		fputs("What would you like to change it to\? ", stdout);
		scanf("%d", &changeNum);
		pCur->data.length.seconds = changeNum;
		success == true;
	}

	times:
	fputs("Would you like to edit the number of times played for this record? (Y/N)\n", stdout);
	scanf(" %c", &answer);
	if (answer != 'Y' && answer != 'N')
	{
		fputs("Invalid Input, Try Again.\n", stdout);
		system("Pause");
		system("cls");
		goto times;
	}
	else if (answer == 'Y')
	{
		fputs("What would you like to change it to\? ", stdout);
		scanf("%d", &changeNum);
		pCur->data.timesPlayed = changeNum;
		success == true;
	}

	rating:
	fputs("Would you like to edit the rating for this record\? (Y/N)\n", stdout);
	scanf(" %c", &answer);
	if (answer != 'Y' && answer != 'N')
	{
		fputs("Invalid Input, Try Again.\n", stdout);
		system("Pause");
		system("cls");
		goto rating;
	}
	else if (answer == 'Y')
	{
	rating1:
		tryAgainRate:
		fputs("What would you like to change it to\? ", stdout);
		scanf("%d", &changeNum);
		if (changeNum <= 0 || changeNum >= 6)
		{
			fputs("Invalid Input, Try again\n", stdout);
			system("cls");
			goto tryAgainRate;
		}
		pCur->data.rating = changeNum;
		success == true;
	}
end:
	return success;
}

bool storeContacts(FILE* infile, Node* pList)
{
	Node* pCur = pList;

	if (pCur == NULL)
	{
		return false;
	}
	while (pCur != NULL)
	{
		fprintf(infile, "%s,", pCur->data.artist);
		fprintf(infile, "%s,", pCur->data.album);
		fprintf(infile, "%s,", pCur->data.song);
		fprintf(infile, "%s,", pCur->data.genre);
		fprintf(infile, "%d:%d,", pCur->data.length.minute, pCur->data.length.seconds);
		fprintf(infile, "%d,", pCur->data.timesPlayed);
		fprintf(infile, "%d", pCur->data.rating);
		pCur = pCur->pLink;
		if (pCur != NULL)
		{
			fprintf(infile, "\n");
		}
	}
	return true;
}

void displayList(Node* pList, displayType dis, char name[])
{
	Node* pCur = pList;
	bool success = false;
	if (pList == NULL)
	{
		fputs("There are no records.\n", stdout);
	}
	while (pCur != NULL && dis == JUSTPRINT)
	{
		fputs(pCur->data.artist, stdout);
		fprintf(stdout, "\t");
		fputs(pCur->data.album, stdout);
		fprintf(stdout, "\t");
		fputs(pCur->data.song, stdout);
		fprintf(stdout, "\t");
		fputs(pCur->data.genre, stdout);
		fprintf(stdout, "\t");
		fprintf(stdout, "%d:%d\t", pCur->data.length.minute, pCur->data.length.seconds);
		fprintf(stdout, "%d\t", pCur->data.timesPlayed);
		fprintf(stdout, "%d\n", pCur->data.rating);
		pCur = pCur->pLink;
		success = true;
	}
	while (pCur != NULL && dis == ARTIST)
	{
		if (strcmp(pCur->data.artist, name) == 0)
		{
			fputs(pCur->data.artist, stdout);
			fprintf(stdout, "\n");
			fputs(pCur->data.album, stdout);
			fprintf(stdout, "\n");
			fputs(pCur->data.song, stdout);
			fprintf(stdout, "\n");
			fputs(pCur->data.genre, stdout);
			fprintf(stdout, "\n");
			fprintf(stdout, "%d:%d\n", pCur->data.length.minute, pCur->data.length.seconds);
			fprintf(stdout, "%d\n", pCur->data.timesPlayed);
			fprintf(stdout, "%d\n", pCur->data.rating);
			pCur = pCur->pLink;
			success = true;
		}
		else // Does not match desired artist
		{
			pCur = pCur->pLink;
		}
	}
	if (success == false && dis == ARTIST)
	{
		fputs("No artist was found\n", stdout);
	}
}

char* addQuote(char artist[])
{
	int i = strlen(artist);
	char str[30] = "\"";
	strcat(str, artist);
	strcpy(artist, str);
	artist[i + 1] = '\"';
	artist[i + 2] = '\0';
	return artist;
}

bool load(FILE* infile, Node** headPtr, int* count)
{
	char str[100] = "";
	int len = 0;
	Record newData;
	bool success = false;
	*count = 0;
	while (fgets(str, 100, infile) != NULL)
	{
		if (str[0] == '\"')
		{
			strcpy(newData.artist, strtok(str, "\"")); // checks for " first
			strcpy(newData.album, strtok(NULL, ","));
			strcpy(newData.song, strtok(NULL, ","));
			strcpy(newData.genre, strtok(NULL, ","));
			newData.length.minute = atoi(strtok(NULL, ":"));
			newData.length.seconds = atoi(strtok(NULL, ","));
			newData.timesPlayed = atoi(strtok(NULL, ","));
			newData.rating = atoi(strtok(NULL, ","));
			strcpy(newData.artist, addQuote(newData.artist));
			success = insertContactAtFront(headPtr, newData);
			++(*count);
		}
		else
		{
			strcpy(newData.artist, strtok(str, ",")); // checks for ,
			strcpy(newData.album, strtok(NULL, ","));
			strcpy(newData.song, strtok(NULL, ","));
			strcpy(newData.genre, strtok(NULL, ","));
			newData.length.minute = atoi(strtok(NULL, ":"));
			newData.length.seconds = atoi(strtok(NULL, ","));
			newData.timesPlayed = atoi(strtok(NULL, ","));
			newData.rating = atoi(strtok(NULL, ","));
			success = insertContactAtFront(headPtr, newData);
			++(*count);
		}
	}
	return success;
}

bool shuffleList(int order[], const int count)
{
	for (int i = 0; i < (count - 1); ++i)
	{
		order[i] = (rand() % count);
		for (int j = 0; j < (count - 1); ++j)
		{
		check:
			if (order[i] == order[j] && i != j)
			{
				order[i] = (rand() % 6);
				goto check; // Check again to make sure new number does not match others
			}
		}
	}
	return true;
}

void play(Node* headPtr, const int count, int order[])
{
	Node* pCur = headPtr;
	for (int j = 0; j < (count - 1); ++j)
	{
		pCur = headPtr;
		for (int i = 0; i < order[j]; ++i)
		{
			pCur = pCur->pLink;
		}
		fputs(pCur->data.artist, stdout);
		fprintf(stdout, "\t");
		fputs(pCur->data.album, stdout);
		fprintf(stdout, "\t");
		fputs(pCur->data.song, stdout);
		fprintf(stdout, "\t");
		fputs(pCur->data.genre, stdout);
		fprintf(stdout, "\t");
		fprintf(stdout, "%d:%d\t", pCur->data.length.minute, pCur->data.length.seconds);
		fprintf(stdout, "%d\t", pCur->data.timesPlayed);
		fprintf(stdout, "%d\n", pCur->data.rating);
	}
}

bool loadSort(FILE* infile, Node** headPtr, int* count, sortType type)
{
	char str[100] = "", temp[30] = "";
	Node* pCur = NULL;
	Record newData;
	bool success = false;
	*count = 0;
	rewind(infile);
	while (fgets(str, 100, infile) != NULL)
	{
		if (str[0] == '\"')
		{
			strcpy(newData.artist, strtok(str, "\"")); // checks for " first
			strcpy(newData.album, strtok(NULL, ","));
			strcpy(newData.song, strtok(NULL, ","));
			strcpy(newData.genre, strtok(NULL, ","));
			newData.length.minute = atoi(strtok(NULL, ":"));
			newData.length.seconds = atoi(strtok(NULL, ","));
			newData.timesPlayed = atoi(strtok(NULL, ","));
			newData.rating = atoi(strtok(NULL, ","));
			if (*headPtr == NULL) // Empty List
			{
				strcpy(newData.artist, addQuote(newData.artist));
				success = insertContactAtFront(headPtr, newData);
			}
			else // Not Empty
			{
				strcpy(newData.artist, addQuote(newData.artist));
				success = insertContactInOrder(headPtr, newData, type);

			}
			++(*count);
		}
		else
		{
			strcpy(newData.artist, strtok(str, ",")); // checks for ,
			strcpy(newData.album, strtok(NULL, ","));
			strcpy(newData.song, strtok(NULL, ","));
			strcpy(newData.genre, strtok(NULL, ","));
			newData.length.minute = atoi(strtok(NULL, ":"));
			newData.length.seconds = atoi(strtok(NULL, ","));
			newData.timesPlayed = atoi(strtok(NULL, ","));
			newData.rating = atoi(strtok(NULL, ","));
			if (*headPtr == NULL) // Empty List
			{
				success = insertContactAtFront(headPtr, newData);
			}
			else // Not Empty
			{
				success = insertContactInOrder(headPtr, newData, type);
			}
			++(*count);
		}
	}
	return success;

}
