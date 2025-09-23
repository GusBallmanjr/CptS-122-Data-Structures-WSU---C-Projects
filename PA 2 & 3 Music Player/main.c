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
#include "test.h"

int main(void)
{
	FILE* inputStream = NULL;
	Node* headPtr = NULL;
	Record searchRecord = { .artist = "", .album = "", .song = "", .genre = "", .length.minute = 0, .length.seconds = 0, .timesPlayed = 0, .rating = 0 }, newRecord = { .artist = "", .album = "", .song = "", .genre = "", .length.minute = 0, .length.seconds = 0, .timesPlayed = 0, .rating = 0 };
	sortType type = 0;
	int selection = 0, displaySelection = 0, count = 0, mode = 0, order[25] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25 };
	char name[50] = "", song[25] = "";
	srand(time(NULL));

	/*testInsert();
	testDelete();
	testShuffle();*/

mainMenu:
	system("cls");
	fputs("Main Menu:\n(1) Load\n(2) Store\n(3) Display\n(4) Insert\n(5) Delete\n(6) Edit\n(7) Sort\n(8) Rate\n(9) Play\n(10) Shuffle\n(11) Exit\n", stdout);
	scanf("%d", &selection);

	if (selection <= 0 || selection > 11)
	{
		fputs("Invalid Input. Try Again\n", stdout);
		system("pause");
		goto mainMenu;
	}

	switch (selection)
	{
	case 1: // Load
		inputStream = fopen("musicPlayList.csv", "r");
		load(inputStream, &headPtr, &count);
		goto mainMenu;
		break;

	case 2: // Store
		store:
		fclose(inputStream);
		inputStream = fopen("musicPlayList.csv", "w");
		if (selection == 2 && storeContacts(inputStream, headPtr) == true)
		{
			fputs("Store was successful.\n", stdout);
			system("pause");
		}
		else if (selection == 2 && storeContacts(inputStream, headPtr) != true)
		{
			fputs("Store failed.\n", stdout);
			system("pause");
		}
		fclose(inputStream);
		inputStream = fopen("musicPlayList.csv", "r");
		if (selection == 11) // exit sequence
		{
			goto exit;
		}
		else // back to main menu
		{
			goto mainMenu;
		}
		break;

	case 3: // Display
		display:
		system("cls");
		fputs("(1) Display all saved songs\n(2) Display specific artist\n", stdout);
		scanf("%d", &displaySelection);
		if (displaySelection > 2 || displaySelection < 1)
		{
			fputs("Invalid Input. Try Again\n", stdout);
			system("pause");
			goto display;
		}
		else if (displaySelection == 1)
		{
			system("cls");
			displayList(headPtr, JUSTPRINT, "a");
			fputs("\n", stdout);
			system("pause");
			goto mainMenu;
		}
		else // displaySelection == 2
		{
			fputs("Which artist would you like to display?\n", stdout);
			getchar();
			for (int i = 0; i < 25; ++i)
			{
				scanf("%c", &name[i]);
				if (name[i] == '\n')
				{
					name[i] = '\0';
					break;
				}
			}
			fputs("Which song from that artist would you like to display?\n", stdout);
			getchar();
			for (int i = 0; i < 25; ++i)
			{
				scanf("%c", &song[i]);
				if (song[i] == '\n')
				{
					song[i] = '\0';
					break;
				}
			}
			system("cls");
			displayList(headPtr, ARTIST, name);
			system("pause");
			goto mainMenu;
		}

		break;

	case 4: // Insert
		system("cls");
		fputs("What is the name of the artist for this new record\?\n", stdout);
		scanf("%s", newRecord.artist);
		fputs("What is the name of the album for this new record\?\n", stdout);
		scanf("%s", newRecord.album);
		fputs("What is the name of the song for this new record\?\n", stdout);
		scanf("%s", newRecord.song);
		fputs("What is the name of the genre for this new record\?\n", stdout);
		scanf("%s", newRecord.genre);
		fputs("How long is the song\? Format: (Minutes):(Seconds)\n", stdout);
		scanf("%s", name);
		newRecord.length.minute = atoi(strtok(name, ":"));
		newRecord.length.seconds = atoi(strtok(NULL, "\0"));
		fputs("How many times has the song been listened to\?\n", stdout);
		scanf("%d", &newRecord.timesPlayed);
		fputs("What is the rating of the song\? (1-5)\n", stdout);
		scanf("%d", &newRecord.rating);
		insertContactAtFront(&headPtr, newRecord);
		++count;
		system("cls");
		goto mainMenu;
		break;

	case 5: // Delete
		system("cls");
		fputs("Which song would you like to delete\?\n", stdout);
		getchar();
		for (int i = 0; i < 25; ++i)
		{
			scanf("%c", &song[i]);
			if (song[i] == '\n')
			{
				song[i] = '\0';
				break;
			}
		}
		if (deleteContact(&headPtr, song))
		{
			fputs("Song has been deleted.\n", stdout);
			--count;
		}
		else
		{
			fputs("Deletion failed; Song not found.\n", stdout);
		}
		system("pause");
		system("cls");
		goto mainMenu;
		break;

	case 6: // Edit
		mode = 0;

		edit:
		system("cls");
		fputs("Which artist would you like to edit?\n", stdout);
		getchar();
		for (int i = 0; i < 25; ++i)
		{
			scanf("%c", &searchRecord.artist[i]);
			if (searchRecord.artist[i] == '\n')
			{
				searchRecord.artist[i] = '\0';
				break;
			}
		}
		fputs("Which song by that artist would you like to edit?\n", stdout);
		for (int i = 0; i < 25; ++i)
		{
			scanf("%c", &searchRecord.song[i]);
			if (searchRecord.song[i] == '\n')
			{
				searchRecord.song[i] = '\0';
				break;
			}
		}
		editContact(headPtr, searchRecord, mode);
		goto mainMenu;
		break;

	case 7: // Sort
		system("cls");
		fputs("Sort by:\n(1) Artist\n(2) Album Title\n(3) Rating\n(4) Number of Times Played\n", stdout);
		scanf("%d", &type);
		--type;
	sort:
		if (deleteAll(&headPtr))
		{
			if (loadSort(inputStream, &headPtr, &count, type) == true)
			{
				fputs("Sort was successful\n", stdout);
			}
		}
		system("pause");
		system("cls");
		goto mainMenu;
		break;

	case 8: // Rate
		
		mode = 1;
		goto edit;
		break;

	case 9: // Play
		system("cls");
		play(headPtr, count, order);
		system("pause");
		system("cls");
		goto mainMenu;
		break;

	case 10: // shuffle
		system("cls");
		if (shuffleList(order, count) == true)
		{
			fputs("Shuffle Successful\n", stdout);
		}
		else
		{
			fputs("Shuffle Failed\n", stdout);
		}
		system("pause");
		system("cls");
		goto mainMenu;
		break;

	case 11: // Exit
		system("cls");
		goto store;
		break;
	}



	fclose(inputStream);

	exit:
	return 0;

}
