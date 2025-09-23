/*
	Author: Gus Ballman
	Class: CptS 122, Fall 2025; Lab Section 01
	Date: 8/28/2025
	Description:

*/

#include "PA1.h"

/*
Function Name : collectdata()
Date Created : 9 / 2 / 2025
Description : This function tokenizes data from csv file and then implements it into struct array.
Inputs : The inputs are an array of the fitbitdata struct and the line count integer.
Output : The output is an integer that represents whether the data is of the target patient or not (0 for no, 1 for yes)
*/
int collectData(char str[100], FitbitData fitbitList[], const int lineCount)
{
	char str2[100] = "", * token;

	token = strtok(str, ",");

	if (token == NULL || strcmp(token, "12cx7") != 0)
	{
		return 0; // Not target patient, need to read over this data
	}

	// Else: 

	strcpy(fitbitList[lineCount].patient, token);

	token = strtok(NULL, ",");
	if (token != NULL)
	{
		strcpy(str2, token);
		strcpy(fitbitList[lineCount].minute, token);
	}
	else
	{
		return 0;
	}

	token = strtok(NULL, ",");
	if (token != NULL)
	{
		strcpy(str2, token);
		fitbitList[lineCount].calories = (str2[0] == '&') ? -1 : atof(str2);
	}
	else
	{
		fitbitList[lineCount].calories = -1; // Invalid Data
	}

	token = strtok(NULL, ",");
	if (token != NULL)
	{
		strcpy(str2, token);
		fitbitList[lineCount].distance = (str2[0] == '&') ? -1 : atof(str2);
	}
	else
	{
		fitbitList[lineCount].distance = -1; // Invalid Data
	}

	token = strtok(NULL, ",");
	if (token != NULL)
	{
		strcpy(str2, token);
		fitbitList[lineCount].floors = (str2[0] == '&') ? -1 : atoi(str2);
	}
	else
	{
		fitbitList[lineCount].floors = -1; // Invalid Data
	}


	token = strtok(NULL, ",");
	if (token != NULL)
	{
		strcpy(str2, token);
		fitbitList[lineCount].heartRate = (str2[0] == '&') ? -1 : atoi(str2);
	}
	else
	{
		fitbitList[lineCount].heartRate = -1; // Invalid Data
	}

	token = strtok(NULL, ",");
	if (token != NULL)
	{
		strcpy(str2, token);
		fitbitList[lineCount].steps = (str2[0] == '&') ? -1 : atoi(str2);
	}
	else
	{
		fitbitList[lineCount].steps = -1; // Invalid Data
	}

	token = strtok(NULL, ",");
	if (token != NULL)
	{
		strcpy(str2, token);
		fitbitList[lineCount].sleepLevel = (str2[0] == '&') ? 0 : atoi(str2);
	}
	else
	{
		fitbitList[lineCount].sleepLevel = 0; // Invalid Data
	}
	return 1;
}

/*
Function Name : repeatedLine()
Date Created : 9 / 2 / 2025
Description : This function checks to see if there is any repeated lines within the struct of the fitbitdata.
Inputs : The inputs are an array of the fitbitdata struct and the line count integer.
Output : The output is an an enum type (1 or 0) representing True (there is a repeated line) or False (there is no repeated line)
*/
Bool repeatedLine(FitbitData fitbitList[], const int lineCount)
{
	if (lineCount <= 1) // Cannot Compare yet
	{
		return FALSE;
	}

	for (int tempCount = 0; tempCount < lineCount /* Checks all lines before current line */;
		++tempCount)
	{
		if (strcmp(fitbitList[lineCount].minute, fitbitList[tempCount].minute) == 0 &&
			fitbitList[lineCount].calories == fitbitList[tempCount].calories &&
			fitbitList[lineCount].distance == fitbitList[tempCount].distance &&
			fitbitList[lineCount].floors == fitbitList[tempCount].floors &&
			fitbitList[lineCount].heartRate == fitbitList[tempCount].heartRate &&
			fitbitList[lineCount].steps == fitbitList[tempCount].steps &&
			fitbitList[lineCount].sleepLevel == fitbitList[tempCount].sleepLevel)
		{
			// All variables in line match another lines data: Repeated line
			return TRUE;
		}
	}
	return FALSE;
}

/*
Function Name : lineCheck()
Date Created : 9 / 3 / 2025
Description : This function checks for missing data within a line of the csv file.
Inputs : The inputs are a a string (which contains the line from the csv file) and an integer representing the starting point index within the string.
Output : The output is an integer that represents a -1 if no missing data is found or an integer that represents the index at which the missing data was found.
*/
int lineCheck(char str[], int startPoint)
{
	int index = startPoint, length = strlen(str);
	while (str[index] != '\0' && str[index + 1] != '\0') // Not at end of string
	{
		if (str[index] == ',' && str[index + 1] == ',') // two delimiters back to back
		{
			return index; // returns place at which double delimiter exists
		}
		++index;
	}
	if (str[length - 1] == ',') // ends in a comma and missing data
	{
		return length - 1;
	}
	return -1;
}

/*
Function Name : cleanDataGaps()
Date Created : 9 / 4 / 2025
Description : This function fills in any missing gaps in the csv data.
Inputs : The inputs are an the string that contains a line from the input csv file.
Output : There are no outputs.
*/
void cleanDataGaps(char str[])
{
	int index = 0, startPoint = 0, length = strlen(str);
	while (str[startPoint] != '\0') // Not at end of string (allows for the system to check for multiple double delimiters (i.e. missing data) in one line)
	{
		index = lineCheck(str, startPoint);
		if (index == length - 1) // ends in zero and missing data
		{
			str[index + 1] = '&';
			str[index + 2] = '\0';
			length += 1; // Adjust to everything being moved down
		}
		else if (index != -1) // found delimiters back to back
		{
			// Program found two delimiters back to back
			for (int i = length /* Start at end of string */; i > index + 1 /* i has to move all the char after the double delimiter down one */ ; --i)
			{
				str[i + 1] = str[i]; // Move down one
			}

			str[index + 1] = '&'; // & is placeholder for gap in data
			++index;
			startPoint = index + 2;
		}
		++startPoint;
	}
}

/*
Function Name : averageheartRate()
Date Created : 9 / 5 / 2025
Description : This function calculates the average heartrate based off all of the tokenized (and valid) heartrate data.
Inputs : The inputs are an array of the fitbitdata struct and the line count integer.
Output : The output is an a double that is the total heartrates divided by the number of valid data points (i.e. the average heartrate)
*/
double averageHeartRate(FitbitData fitbitList[], const int lineCount)
{
	double total = 0.0;
	int count = 0;
	for (int index = 0; index < lineCount; ++index)
	{
		if (fitbitList[index].heartRate >= 0 && fitbitList[index].heartRate <= 180)
		{
			total += fitbitList[index].heartRate;
			++count; // Counts how many valid heartRates were added in order to find most accurate average
		}
	}
	return count == 0 ? 0 : total / count; // Cannot Divide by zero
}

/*
Function Name : totalCalories()
Date Created : 9 / 5 / 2025
Description : This function calculates the total number of calories burned during the time interval of the data.
Inputs : The inputs are an array of the fitbitdata struct and the line count integer.
Output : The output is an a double that is the total number of calories burned during the 24 hour time interval
*/
double totalCalories(FitbitData fitbitList[], const int lineCount)
{
	double total = 0.0;
	for (int index = 0; index < lineCount; ++index)
	{
		if (fitbitList[index].calories >= 0 && fitbitList[index].calories <= 100)
		{
			total += fitbitList[index].calories;
		}
	}
	return total;
}

/*
Function Name : totalDistance()
Date Created : 9 / 5 / 2025
Description : This function calculates the total distance traveled during the time interval of the data.
Inputs : The inputs are an array of the fitbitdata struct and the line count integer.
Output : The output is an a double that is the total distance traveled during the 24 hour time interval
*/
double totalDistance(FitbitData fitbitList[], const int lineCount)
{
	double total = 0.0;
	for (int index = 0; index < lineCount; ++index)
	{
		if (fitbitList[index].distance >= 0 && fitbitList[index].distance <= 100)
		{
			total += fitbitList[index].distance;
		}
	}
	return total;
}

/*
Function Name : totalfloors()
Date Created : 9 / 5 / 2025
Description : This function calculates the total number of floors traveled during the time interval of the data.
Inputs : The inputs are an array of the fitbitdata struct and the line count integer.
Output : The output is an an integer that is the total number floors traveled during the 24 hour time interval
*/
int totalFloors(FitbitData fitbitList[], int lineCount)
{
	int total = 0.0;
	for (int index = 0; index < lineCount; ++index)
	{
		if (fitbitList[index].floors >= 0 && fitbitList[index].floors <= 100)
		{
			total += fitbitList[index].floors;
		}
	}
	return total;
}

/*
Function Name : poorestSleep()
Date Created : 9 / 5 / 2025
Description : This function calculates when patient 12xc7 had the poorest sleep during the night.
Inputs : The inputs are an array of the fitbitdata struct, the line count integer, and two strings representing the start and end time of the poor sleep interval.
Output : The output is the sum total of the sleepLevels during the poor sleep time interval.
*/
int poorestSleep(FitbitData fitbitList[], char* sleepStart, char* sleepEnd, int lineCount)
{
	int  n = 0, total = 0, max = 0;
	char copy[50] = "";
	for (int index = 0; index < lineCount; ++index)
	{
		strcpy(copy, fitbitList[index].minute);
		int hour = atoi(strtok(copy, ":"));

		if (hour >= 21 || hour <= 8) // 9 hours after noon (9 pm) to 20 hours after noon (8 am) assuming data starts at midnight
		{
			total = 0;
			n = index;
			while (n < lineCount && fitbitList[n].sleepLevel > 1) // Target SleepLevels
			{
				total += fitbitList[n].sleepLevel;
				++n;
			}
			if (total >= max)
			{
				max = total;
				strncpy(sleepStart, fitbitList[index].minute, 9);
				strncpy(sleepEnd, fitbitList[n - 1].minute, 9); // - 1 accounts for the last increment
			}
		}
	}
	return max;
}

/*
Function Name : maxSteps()
Date Created : 9 / 5 / 2025
Description : This function calculates teh max amount of steps taken in the 24 hour time period.
Inputs : The inputs are an array of the fitbitdata struct and the line count integer.
Output : The output is index correlating with the most amount of steps taken in the later part of the day in the fitbitList struct array.
*/
int maxSteps(FitbitData fitbitList[], int lineCount)
{
	int max = -1, maxIndex = 1440;
	char copy[50] = "";

	for (int index = 0; index < lineCount; ++index)
	{
		if (fitbitList[index].steps >= 0)
		{
			if (fitbitList[index].steps > max)
			{
				max = fitbitList[index].steps;
				maxIndex = index;
			}
			else if (fitbitList[index].steps == max)
			{
				
				if (strcmp(fitbitList[index].minute, fitbitList[maxIndex].minute) > 0)
				{
					maxIndex = index;
				}
			}
		}
	}
	return maxIndex;
}