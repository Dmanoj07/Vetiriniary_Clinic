/*
*****************************************************************************
                        Assignment 1 - Milestone 2

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
#include<string.h>

// include the user library "core" so we can use those functions
#include "core.h"
// include the user library "clinic" where the function prototypes are declared
#include "clinic.h"


//////////////////////////////////////
// DISPLAY FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display's the patient table header (table format)
void displayPatientTableHeader(void)
{
    printf("Pat.# Name            Phone#\n"
        "----- --------------- --------------------\n");
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Displays a single patient record in FMT_FORM | FMT_TABLE format
void displayPatientData(const struct Patient* patient, int fmt)
{
    if (fmt == FMT_FORM)
    {
        printf("Name  : %s\n"
            "Number: %05d\n"
            "Phone : ", patient->name, patient->patientNumber);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
    else
    {
        printf("%05d %-15s ", patient->patientNumber,
            patient->name);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
}


//////////////////////////////////////
// MENU & ITEM SELECTION FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// main menu
void menuMain(struct ClinicData* data)
{
    int selection;

    do {
        printf("Veterinary Clinic System\n"
            "=========================\n"
            "1) PATIENT     Management\n"
            "2) APPOINTMENT Management\n"
            "-------------------------\n"
            "0) Exit System\n"
            "-------------------------\n"
            "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');
        switch (selection)
        {
        case 0:
            printf("Are you sure you want to exit? (y|n): ");
            selection = !(inputCharOption("yn") == 'y');
            putchar('\n');
            if (!selection)
            {
                printf("Exiting system... Goodbye.\n\n");
            }
            break;
        case 1:
            menuPatient(data->patients, data->maxPatient);
            break;
        case 2:
            printf("<<< Feature not yet available >>>\n\n");
            break;
        }
    } while (selection);
}
//
//// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
//// Menu: Patient Management
void menuPatient(struct Patient patient[], int max)
{
    int selection;

    do {
        printf("Patient Management\n"
            "=========================\n"
            "1) VIEW   Patient Data\n"
            "2) SEARCH Patients\n"
            "3) ADD    Patient\n"
            "4) EDIT   Patient\n"
            "5) REMOVE Patient\n"
            "-------------------------\n"
            "0) Previous menu\n"
            "-------------------------\n"
            "Selection: ");
        selection = inputIntRange(0, 5);
        putchar('\n');
        switch (selection)
        {
        case 1:
            displayAllPatients(patient, max, FMT_TABLE);
            suspend();
            break;
        case 2:
            searchPatientData(patient, max);
            break;
        case 3:
            addPatient(patient, max);
            suspend();
            break;
        case 4:
            editPatient(patient, max);
            break;
        case 5:
            removePatient(patient, max);
            suspend();
            break;
        }
    } while (selection);
}

//// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
//// Menu: Patient edit
void menuPatientEdit(struct Patient* patient)
{
    int selection;

    do {
        printf("Edit Patient (%05d)\n"
            "=========================\n"
            "1) NAME : %s\n"
            "2) PHONE: ", patient->patientNumber, patient->name);

        displayFormattedPhone(patient->phone.number);

        printf("\n"
            "-------------------------\n"
            "0) Previous menu\n"
            "-------------------------\n"
            "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');

        if (selection == 1)
        {
            printf("Name  : ");
            inputCString(patient->name, 1, NAME_LEN);
            putchar('\n');
            printf("Patient record updated!\n\n");
        }
        else if (selection == 2)
        {
            inputPhoneData(&patient->phone);
            printf("Patient record updated!\n\n");
        }

    } while (selection);
}


// ---------------------------------------------------------------------------
// !!! Put all the remaining function definitions below !!!
// Note: Maintain the same order/sequence as it is listed in the header file
// ---------------------------------------------------------------------------

// Display's all patient data in the FMT_FORM | FMT_TABLE format
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
void displayAllPatients(const struct Patient patient[], int max, int fmt)
{
    int i = 0;
    if (fmt == FMT_TABLE)
    {
        displayPatientTableHeader();
    }
    if (patient[i].patientNumber == 0)
    {
        printf("*** No records found ***");
    }

    for (i = 0; i < max; i++)
    {
        if (patient[i].patientNumber != 0)
        {
            displayPatientData(&patient[i], fmt);
        }
    }
    printf("\n");
}


// Search for a patient record based on patient number or phone number
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
void searchPatientData(const struct Patient patient[], int max)
{
    int selection = 0;
    do
    {
        printf("Search Options\n");
        printf("==========================\n");
        printf("1) By patient number\n"
            "2) By phone number\n");
        printf("..........................\n");
        printf("0) Previous menu\n");
        printf("..........................\n");
        printf("Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');
        switch (selection)
        {
        case 1:
            searchPatientByPatientNumber(patient, max);
            suspend();
            break;

        case 2:
            searchPatientByPhoneNumber(patient, max);
            suspend();
            break;
        }
    } while (selection);

}


// Add a new patient record to the patient array
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
void addPatient(struct Patient patient[], int max)
{
    int arrayIndx = 0, i = 0, patientNo = 0;
    for (i = 0; i < max && arrayIndx == 0; i++)
    {
        if (patient[i].patientNumber == 0)
        {
            arrayIndx = i;
        }

    }
    if (arrayIndx)
    {
        patientNo = nextPatientNumber(patient, max);
        patient[arrayIndx].patientNumber = patientNo;
        inputPatient(&patient[arrayIndx]);
        printf("*** New patient record added ***\n");
        putchar('\n');
    }
    else
    {
        printf("ERROR: Patient listing is FULL!\n");
        putchar('\n');
    }
}

// Edit a patient record from the patient array
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
void editPatient(struct Patient patient[], int max)
{
    int patientNo = 0, found = -1;
    printf("Enter the patient number: ");
    patientNo = inputIntPositive();
    putchar('\n');
    found = findPatientIndexByPatientNum(patientNo, patient, max);
    if (found > -1)
    {
        menuPatientEdit(&patient[found]);
    }
    else
    {
        printf("ERROR: Patient record not found!");
        putchar('\n');

    }
    
}


// Remove a patient record from the patient array
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
void removePatient(struct Patient patient[], int max)
{
    int patientNo = 0, i = 0, found = -1, selection = 0;
    printf("Enter the patient number: ");
    patientNo = inputIntPositive();
    found = findPatientIndexByPatientNum(patientNo, patient, max);
    putchar('\n');
    if (found > -1)
    {
        displayPatientData(&patient[found], FMT_FORM);
        putchar('\n');
        printf("Are you sure you want to remove this patient record? (y/n): ");
        selection = inputCharOption("yn") == 'y';
        if (selection)
        {
            for (i = found; i < max - 1; i++)
            {
                patient[i] = patient[i + 1];
            }
            strcpy(patient[max - 1].name, "");
            strcpy(patient[max - 1].phone.number, "");
            patient[max - 1].patientNumber = 0;
            strcpy(patient[max - 1].phone.description, "");
            printf("Patient record has been removed!\n");
        }
        else
        {
            printf("Operation aborted.\n");
        }
    }
    else
    {
        printf("ERROR: Patient record not found!\n");
    }
    putchar('\n');
}



//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

// Search and display patient record by patient number (form)
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
void searchPatientByPatientNumber(const struct Patient patient[], int max)
{
    int patientNo = 0, found = -1;
    printf("Search by patient number: ");
    patientNo = inputIntPositive();
    found = findPatientIndexByPatientNum(patientNo, patient, max);
    putchar('\n');
    if (found > -1)
    {

        displayPatientData(&patient[found], FMT_FORM);

    }
    else
    {
        printf("*** No records found ***\n");
    }

    putchar('\n');

}

// Search and display patient records by phone number (tabular)
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
void searchPatientByPhoneNumber(const struct Patient patient[], int max)
{
    char phNo[11] = { "0" };
    int found = 0, i = 0;

    printf("Search by phone number: ");
    inputCString(phNo, 10, 10);
    putchar('\n');
    displayPatientTableHeader();

    for (i = 0; i < max; i++)
    {

        if (strcmp(phNo, patient[i].phone.number) == 0)
        {
            displayPatientData(&patient[i], FMT_TABLE);
            found++;

        }
    }
    if (found == 0)
    {
        putchar('\n');
        printf("*** No records found ***\n");
    }
    putchar('\n');
}

// Get the next highest patient number
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
int nextPatientNumber(const struct Patient patient[], int max)
{
    int largestPatientNo = 0, i = 0, nxtPatientNo = 0;
    largestPatientNo = patient[0].patientNumber;
    for (i = 0; i < max; i++)
    {
        if (patient[i].patientNumber > largestPatientNo)
        {
            largestPatientNo = patient[i].patientNumber;
        }
    }
    nxtPatientNo = largestPatientNo + 1;
    return nxtPatientNo;
}

// Find the patient array index by patient number (returns -1 if not found)
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
int findPatientIndexByPatientNum(int patientNumber,
    const struct Patient patient[], int max)
{
    int rcdfound = -1, i = 0;
    for (i = 0; i < max && rcdfound == -1; i++)
    {
        if (patientNumber == patient[i].patientNumber)
        {
            rcdfound = i;
        }
    }
    return rcdfound;
}



//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

// Get user input for a new patient record
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
void inputPatient(struct Patient* patient)
{
    char name[NAME_LEN + 1] = "abc";
    printf("Patient Data Input\n");
    printf("------------------\n");
    printf("Number: 0%d\n", patient->patientNumber);
    printf("Name  : ");
    inputCString(name, 0, NAME_LEN);
    strcpy(patient->name, name);
    printf("\n");
    inputPhoneData(&patient->phone);
}


// Get user input for phone contact information
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
void inputPhoneData(struct Phone* phone)
{
    int selection = 0;
    char contact[11];
    printf("Phone Information\n");
    printf("-----------------\n");
    printf("How will the patient like to be contacted?\n");
    printf("1. Cell\n");
    printf("2. Home\n");
    printf("3. Work\n");
    printf("4. TBD\n");
    printf("Selection: ");
    selection = inputIntRange(1, 4);
    switch (selection)
    {
    case 1:
        putchar('\n');
        strcpy(phone->description, "CELL");
        printf("Contact: %s\n", phone->description);
        printf("Number : ");
        inputCString(contact, 10, 10);
        strcpy(phone->number, contact);
        break;
    case 2:
        putchar('\n');
        strcpy(phone->description, "HOME");
        printf("Contact: %s\n", phone->description);
        printf("Number : ");
        inputCString(contact, 10, 10);
        strcpy(phone->number, contact);
        break;

    case 3:
        putchar('\n');
        strcpy(phone->description, "WORK");
        printf("Contact: %s\n", phone->description);
        printf("Number : ");
        inputCString(contact, 10, 10);
        strcpy(phone->number, contact);
        break;

    case 4:
        strcpy(phone->description, "TBD");
        strcpy(phone->number, "0");
        break;
    }
    putchar('\n');


}