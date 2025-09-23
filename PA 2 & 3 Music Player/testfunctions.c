/*

*/

#include "PA2.h"

void testInsert()
{
	Record test = { .artist = "\"Perry, Katy\"", .album = "Witness", .song = "Chained to the Rhythm", .genre = "pop", .length.minute = 4, .length.seconds = 36, .timesPlayed = -1, .rating = 6};
	Node* headPtr = NULL;
	bool success = false;
	success = insertContactAtFront(&headPtr, test);

	if (success == false)
	{
		printf("insert failed\n");
	}
	else
	{
		printf("insert succeeded\n");
	}

	if (headPtr == NULL)
	{
		printf("headPtr was not updated\n");
	}
	else
	{
		printf("headPtr was updated\n");
	}
	printf("Artist: %s, Album: %s, song: %s, genre: %s, length: %d:%d, times played: %d, rating: %d\n", headPtr->data.artist, headPtr->data.album, headPtr->data.song, headPtr->data.genre, headPtr->data.length.minute, headPtr->data.length.seconds, headPtr->data.timesPlayed, headPtr->data.rating);
}

void testDelete()
{
	Record test = { .artist = "\"Perry, Katy\"", .album = "Witness", .song = "Chained to the Rhythm", .genre = "pop", .length.minute = 4, .length.seconds = 36, .timesPlayed = -1, .rating = 6 };
	Node* headPtr = NULL;
	bool success = false;

	success = insertContactAtFront(&headPtr, test);
	success = deleteContact(&headPtr, "Chained to the Rhythm");
	if (success == false)
	{
		printf("delete failed\n");
	}
	else
	{
		printf("delete succeeded\n");
	}

	if (headPtr == NULL)
	{
		printf("headPtr was updated\n");
	}
	else
	{
		printf("headPtr was not updated\n");
	}
}

void testShuffle()
{
	// Do to the fact that my shuffle function only creates the order and does not play them, this is a test of my play function rather than my shuffle function because a shuffled order is given.
	Record test1 = { .artist = "\"Perry, Katy\"", .album = "Witness", .song = "Chained to the Rhythm", .genre = "pop", .length.minute = 4, .length.seconds = 36, .timesPlayed = -1, .rating = 6 }, test2 = { .artist = "\"ron\"", .album = "Wi", .song = "ahhhhhhh", .genre = "pop", .length.minute = 4, .length.seconds = 36, .timesPlayed = 3, .rating = 4}, test3 = { .artist = "\"Bill\"", .album = "Hi", .song = "yppppp Rhythm", .genre = "pop", .length.minute = 4, .length.seconds = 36, .timesPlayed = 0, .rating = 1 };;
	int order[3] = { 2, 0, 1 }; // Minus 1 to account for arrays being 0 indexed
	Node* headPtr = NULL;
	insertContactAtFront(&headPtr, test1); // third node
	insertContactAtFront(&headPtr, test2); // second node
	insertContactAtFront(&headPtr, test3); // first node
	play(headPtr, 4, order);

	// Should play katy perry then bill, and then ron
}