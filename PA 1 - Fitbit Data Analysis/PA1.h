/*
	Author: Gus Ballman
	Class: CptS 122, Fall 2025; Lab Section 01
	Date: 8/28/2025
	Description:

*/

#ifndef PA1	_H
#define PA1_H

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum sleep
{
	NONE = 0, ASLEEP = 1, AWAKE = 2, REALLYAWAKE = 3
} Sleep;

typedef enum bool
{
	FALSE = 0, TRUE = 1
} Bool;

typedef struct fitbit
{
	char patient[10], minute[9];
	double calories, distance;
	unsigned int floors, heartRate, steps;
	Sleep sleepLevel;
} FitbitData;

int collectData(char str[100], FitbitData fitbitList[], const int lineCount);
Bool repeatedLine(FitbitData fitbitList[], const int lineCount);
int lineCheck(char str[], int startPoint);
void cleanDataGaps(char str[]);
double averageHeartRate(FitbitData fitbitList[], const int lineCount);
double totalCalories(FitbitData fitbitList[], const int lineCount);
double totalDistance(FitbitData fitbitList[], const int lineCount);
int totalFloors(FitbitData fitbitList[], int lineCount);
int poorestSleep(FitbitData fitbitList[], char* sleepStart, char* sleepEnd, int lineCount);
int maxSteps(FitbitData fitbitList[], int lineCount);

#endif