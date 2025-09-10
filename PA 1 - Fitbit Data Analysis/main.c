/*
	Author: Gus Ballman
	Class: CptS 122, Fall 2025; Lab Section 01
	Date: 8/28/2025
	Description:

*/

#include "PA1.h"

int main(void)
{
	FILE* inputStream = fopen("FitbitData.csv", "r");
	FitbitData fitbitList[1440];
	Bool repeat = FALSE;
	char str[100] = "";
	int lineCount = 0, collectResult = 0, maxStepsIndex = 0;
	char sleepStart[10] = "", sleepEnd[10] = "";

	if (inputStream != NULL) // File exists and is open
	{
		while (fgets(str, 100, inputStream) != NULL) // File exists and is opened
		{
			cleanDataGaps(str);
			collectResult = collectData(str, fitbitList, lineCount);
			if (collectResult == 1)
			{
				repeat = repeatedLine(&fitbitList, lineCount);
				if (repeat == FALSE)
				{
					// Line is unique and of target patient
					lineCount++;
				}
			}
		}

		fclose(inputStream);
		FILE* outputStream = fopen("Results.csv", "w");

		poorestSleep(fitbitList, sleepStart, sleepEnd, lineCount);
		maxStepsIndex = maxSteps(fitbitList, lineCount);
		
		fprintf(outputStream, "Total Calories,Total Distance,Total Floors,Total Steps, Avg Heartrate, Max Steps, Sleep\n");

		fprintf(outputStream, "%.2lf, %.2lf, %d, %.2lf, %d, %s,%s,%s\n",
			totalCalories(fitbitList, lineCount), totalDistance(fitbitList, lineCount), totalFloors(fitbitList, lineCount), averageHeartRate(fitbitList, lineCount), fitbitList[maxStepsIndex].steps, fitbitList[maxStepsIndex].minute, sleepStart, sleepEnd);
	}


	return 0;
}