/****************************************************************************
Assignment 1 - Milestone 1
Full Name : Manoj Dhami
Student ID# : 121613202
Email : mdhami7@myseneca.ca
Section : NDD
Authenticity Declaration :
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider.This submitted
piece of work is entirely of my own creation.
* ****************************************************************************
*/


#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
//#include "core.h"

// Clear the standard input buffer
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
		if (value <=0)
		{
			printf("ERROR! Value must be > 0: ");
		}
	} while (value <=0);
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
		clearInputBuffer();
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
	} while (!flag);
	return value;
}

//calculating length of array
int length(const char alpha[])
{
	int len = 0, i = 0;
	
	if (alpha == NULL)
	{
		len = 0;
	}
	else
	{
		for (i = 0; alpha[i] != '\0'; i++)
		{

			len = i;
		}
	}
	
	return len+1;
}

void inputCString(char* alpha, int min, int max)
{
	char value[50] = { "a" };
	int len = 0, i=0;

	do
	{
		
		scanf(" %50[^\n]", value);
		clearInputBuffer();
		len = length(value);
		if (len<min && (min != max))
		{
			printf("ERROR: String length must be between %d and %d chars: ", min, max);
		}
		else if ((len<min || len>max) && min == max)
		{
			printf("ERROR: String length must be exactly %d chars: ",

				min);
		}
		else if (len>max && (min != max))
		{
			printf("ERROR: String length must be no more than %d chars: ",

				max);
		}
		else
		{
			for (i = 0; i < len; i++)
			{
				alpha[i] = value[i];

			}
			alpha[i] = '\0';
		}

	} while (len < min || len > max);
	
}

void displayFormattedPhone(const char* phNum)
{
	int len = 0, i = 0, found = 0,  count = 0;


	len = length(phNum);
	if (len == 10)
	{
		for (i = 0; i < 10; i++)
		{
			
				if (phNum[i] == '0' || phNum[i] == '1' || phNum[i] == '2' || phNum[i] == '3' || phNum[i] == '4' || phNum[i] == '5' || phNum[i] == '6' || phNum[i] == '7' || phNum[i] == '8' || phNum[i] == '9')
				{
					found +=1 ;	 
				}
		}
		if (found == 10)
		{
			printf("(");
			for (i = 0; i < len; i++)
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