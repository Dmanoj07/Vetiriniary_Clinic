#pragma once
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

// Clear the standard input buffer
void clearInputBuffer(void);

// Wait for user to input the "enter" key to continue
void suspend(void);

//funtion prototypes

int inputInt();
int inputIntPositive();
int inputIntRange(int min, int max);
char inputCharOption(const char alpha[]);
void inputCString(char* alpha, int min, int max);
void displayFormattedPhone(const char* phNum);