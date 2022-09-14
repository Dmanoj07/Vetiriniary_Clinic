/*
*****************************************************************************
						Assignment 1 - Milestone 3

Full Name  : Manoj Dhami
Student ID#:121613202
Email      :mdhami7@myseneca.ca
Section    :NDD
Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
***/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include "core.h"
#include "clinic.h"

//
// Copy your work done from Milestone #1 (core.c) into this file
// - Organize your functions in the same order as they are listed in the core.h file
// - Also copy the commented "sections" to help with finding functions quickly!
//
void clearInputBuffer(void)
{
	// Discard all remaining char's from the standard input buffer:
	while (getchar() != '\n')
	{
		; // do nothing!
	}
}


// Wait for user to input the "enter" key to continue
void suspend(void)
{
	printf("<ENTER> to continue...");
	clearInputBuffer();
	putchar('\n');
}

int inputInt()
{

	int value = 0;
	char value1 = 'x';
	int flag = 0;
	do
	{
		if (scanf(" %d%c", &value, &value1) == 2 && value1 == '\n')
		{
			flag = 1;
		}
		else
		{
			clearInputBuffer();
			printf("Error! Input a whole number: ");
		}

	} while (flag == 0);
	return value;
}
int inputIntPositive()
{
	int value = 0;
	do
	{
		value = inputInt();
		if (value <= 0)
		{
			printf("ERROR! Value must be > 0: ");
		}
	} while (value <= 0);
	return value;
}

int inputIntRange(int min, int max)
{
	int value = 0;
	do
	{
		value = inputInt();
		if (value < min || value > max)
		{
			printf("ERROR! Value must be between %d and %d inclusive: ", min, max);
		}

	} while (value < min || value > max);
	return value;
}

char inputCharOption(const char alpha[])
{
	char value = 'a';
	int flag = 0, i = 0;

	do
	{
		
		scanf(" %c", &value);
		
		
		if(getchar() == '\n')
		{
			
			for (i = 0; alpha[i] != '\0'; i++)
			{
				if (value == alpha[i])
				{
					flag = 1;
				}
			}
			if (!flag)
			{
				printf("ERROR: Character must be one of [%s]: ", alpha);
			}
		}
		else
		{
			printf("ERROR: Character must be one of [%s]: ", alpha);
			clearInputBuffer();
		}
		
	
	} while (!flag );
	return value;
}
void inputCString(char* alpha, int min, int max)
{
	char value[50] = { "a" };
	int i = 0;

	do
	{

		scanf(" %50[^\n]", value);
		clearInputBuffer();
		if (strlen(value) < min && (min != max))
		{
			printf("ERROR: String length must be between %d and %d chars: ", min, max);
		}
		else if ((strlen(value) < min || strlen(value) > max) && min == max)
		{
			printf("Invalid 10-digit number! Number: ");
		}
		else if (strlen(value) > max && (min != max))
		{
			printf("ERROR: String length must be no more than %d chars: ",

				max);
		}
		else
		{
			for (i = 0; i < strlen(value); i++)
			{
				alpha[i] = value[i];

			}
			alpha[i] = '\0';
		}

	} while (strlen(value) < min || strlen(value) > max);

}

void displayFormattedPhone(const char* phNum)
{
	int i = 0, found = 0, count = 0;

	if (strlen(phNum) == 10)
	{
		for (i = 0; i < 10; i++)
		{
			if (phNum[i] >= '0' && phNum[i] <= '9')
			{
				found += 1;
			}
		}
		if (found == 10)
		{
			printf("(");
			for (i = 0; i < strlen(phNum); i++)
			{
				if (count == 3)
				{
					printf(")");
					printf("%c", phNum[i]);
				}
				else if (count == 6)
				{
					printf("-");
					printf("%c", phNum[i]);
				}
				else
				{
					printf("%c", phNum[i]);
				}
				count++;
			}
		}
		else
		{
			printf("(___)___-____");
		}
	}
	else
	{
		printf("(___)___-____");
	}



}