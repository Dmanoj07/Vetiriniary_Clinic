/*
*****************************************************************************
                        Assignment 1 - Milestone 3
Full Name  :Manoj Dhami
Student ID#:121613202
Email      :mdhami7@myseneca.ca
Section    :NDD
Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
*****************************************************************************
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>

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

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display's appointment schedule headers (date-specific or all records)
void displayScheduleTableHeader(const struct Date* date, int isAllRecords)
{
    printf("Clinic Appointments for the Date: ");

    if (isAllRecords)
    {
        printf("<ALL>\n\n");
        printf("Date       Time  Pat.# Name            Phone#\n"
            "---------- ----- ----- --------------- --------------------\n");
    }
    else
    {
        printf("%04d-%02d-%02d\n\n", date->year, date->month, date->day);
        printf("Time  Pat.# Name            Phone#\n"
            "----- ----- --------------- --------------------\n");
    }
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display a single appointment record with patient info. in tabular format
void displayScheduleData(const struct Patient* patient,
    const struct Appointment* appoint,
    int includeDateField)
{
    if (includeDateField)
    {
        printf("%04d-%02d-%02d ", appoint->date.year, appoint->date.month,
            appoint->date.day);
    }
    printf("%02d:%02d %05d %-15s ", appoint->time.hour, appoint->time.min,
        patient->patientNumber, patient->name);

    displayFormattedPhone(patient->phone.number);

    printf(" (%s)\n", patient->phone.description);
}


//////////////////////////////////////
// MENU & ITEM SELECTION FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// main menu (hub) for application
void menuMain(struct ClinicData* data)
{
    int selection = 0;

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
            menuAppointment(data);
            break;
        }
    } while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient Management
void menuPatient(struct Patient patient[], int max)
{
    int selection = 0;

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

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient edit
void menuPatientEdit(struct Patient* patient)
{
    int selection = 0;
    

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


// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Appointment Management
void menuAppointment(struct ClinicData* data)
{
    int selection = 0;

    do {
        printf("Appointment Management\n"
            "==============================\n"
            "1) VIEW   ALL Appointments\n"
            "2) VIEW   Appointments by DATE\n"
            "3) ADD    Appointment\n"
            "4) REMOVE Appointment\n"
            "------------------------------\n"
            "0) Previous menu\n"
            "------------------------------\n"
            "Selection: ");
        selection = inputIntRange(0, 4);
        putchar('\n');
        switch (selection)
        {
        case 1:
           viewAllAppointments(data);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 2:
           viewAppointmentSchedule(data);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 3:
            addAppointment(data->appointments, data->maxAppointments,
                data->patients, data->maxPatient);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 4:
            removeAppointment(data->appointments, data->maxAppointments,
                data->patients, data->maxPatient);  // ToDo: You will need to create this function!
            suspend();
            break;
        }
    } while (selection);
}


// ---------------------------------------------------------------------------
// !!! INSERT/COPY YOUR MS#2 FUNCTION DEFINITIONS BELOW... !!!
// Note: Maintain the same order/sequence as it is listed in the header file
//       Properly organize/categorize any new functions accordingly
// ---------------------------------------------------------------------------


// Display's all patient data in the FMT_FORM | FMT_TABLE format
// (Copy your code from MS#2)
void displayAllPatients(const struct Patient patient[], int max, int fmt)
{
    int i = 0, found = 1;
    if (fmt == FMT_TABLE)
    {
        displayPatientTableHeader();
    }

    for (i = 0; i < max; i++)
    {
        if (patient[i].patientNumber != 0)
        {
            displayPatientData(&patient[i], fmt);
        }
        else
        {
            found = 0;
        }
    }
    if (!found)
    {
        printf("*** No records found ***");
    }
    printf("\n");
}

// Search for a patient record based on patient number or phone number
// (Copy your code from MS#2)
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
// (Copy your code from MS#2)
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
// (Copy your code from MS#2)
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
// (Copy your code from MS#2)
void removePatient(struct Patient patient[], int max)
{
    int patientNo = 0, found = -1, selection = 0;
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
            strcpy(patient[found].name, "");
            strcpy(patient[found].phone.number, "");
            patient[found].patientNumber = 0;
            strcpy(patient[found].phone.description, "");
            printf("Patient record has been removed!\n");
        }
        else
        {
            printf("Operation aborted\n");
        }
    }
    else
    {
        printf("ERROR: Patient record not found!\n");
    }
    putchar('\n');
}

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// Milestone #3 mandatory functions...
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

//sorting
void sortingAppointment(const struct ClinicData* data)
{
    int i = 0, j = 0, minPos = 0;
    struct Appointment tmp = { 0 };
    for (i = 0; i < (data->maxAppointments) - 1 ; i++)
    {
        if (data->appointments[i].patientNo != 0)
        {
            minPos = i;
            for (j = i + 1; j < data->maxAppointments; j++)
            {
                if (data->appointments[j].patientNo != 0)
                {
                    if (data->appointments[j].date.year < data->appointments[minPos].date.year)
                    {
                        minPos = j;
                    }
                    else if (data->appointments[j].date.year == data->appointments[minPos].date.year)
                    {
                        if (data->appointments[j].date.month < data->appointments[minPos].date.month)
                        {
                            minPos = j;
                        }
                        else if (data->appointments[j].date.month == data->appointments[minPos].date.month)
                        {
                            if (data->appointments[j].date.day < data->appointments[minPos].date.day)
                            {
                                minPos = j;
                            }
                            else if (data->appointments[j].date.day == data->appointments[minPos].date.day)
                            {
                                if (data->appointments[j].time.hour < data->appointments[minPos].time.hour)
                                {
                                    minPos = j;
                                }
                                else if (data->appointments[j].time.hour == data->appointments[minPos].time.hour)
                                {
                                    if (data->appointments[j].time.min < data->appointments[minPos].time.min)
                                    {
                                        minPos = j;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        if (minPos != i)
        {
            tmp = data->appointments[minPos];
            data->appointments[minPos] = data->appointments[i];
            data->appointments[i] = tmp;
        }
  
    }
}

void sortingPatient(const struct ClinicData* data)
{
    int i = 0, j = 0;
    struct Patient tmp1[20] = { { 0 } };
    for (i = 0; i < data->maxAppointments; i++)
    {
        if (data->appointments[i].patientNo != 0)
        {
            for (j = 0; j < data->maxPatient; j++)
            {
                if (data->patients[j].patientNumber != 0)
                {
                    if (data->patients[j].patientNumber == data->appointments[i].patientNo)
                    {
                        tmp1[i] = data->patients[j];
                    }
                }
            }
            {
                displayScheduleData(&tmp1[i], &data->appointments[i], 1);
            }
        }


    }
}


// View ALL scheduled appointments
// Todo:

void viewAllAppointments(const struct ClinicData* data)
{
    
    displayScheduleTableHeader(&data->appointments->date, 1);
    sortingAppointment(data);
    sortingPatient(data);
    putchar('\n');
     

}
//Asking user for day

int inputDay(int month, int year)
{
    int day = 0;
    if (month % 2 == 0)
    {
        if (month == 2)
        {
            printf("Day (1-%d)  : ", ((year % 4) ? 28 : 29));
            day = inputIntRange(1, ((year % 4) ? 28 : 29));
        }
        else
        {
            printf("Day (1-30)  : ");
            day = inputIntRange(1, 30);
        }
    }
    else
    {
        printf("Day (1-31)  : ");
        day = inputIntRange(1, 31);
    }
    return day;
}

// View appointment schedule for the user input date
// Todo:
void viewAppointmentSchedule(const struct ClinicData* data)
{
    int yr = 0, mth = 0, day = 0, i = 0, found = 0, j = 0;
    struct Patient tmp1[50] = { {0} };


    printf("Year        : ");
    scanf(" %d", &yr);
    printf("Month (1-12): ");
    mth = inputIntRange(1, 12);
    day = inputDay(mth, yr);
    putchar('\n');
    for ( i = 0; i < data->maxAppointments && found == 0; i++)
    {
        if (data->appointments->patientNo != 0)
        {
            if (data->appointments[i].date.year == yr && data->appointments[i].date.month == mth && data->appointments[i].date.day == day)
            {
                displayScheduleTableHeader(&data->appointments[i].date, 0);
                found = 1;
            }
        }
       
    }
    sortingAppointment(data);
    for ( i = 0; i <data->maxAppointments; i++)
    {
        if (data->appointments[i].date.year == yr) {
            
            for (j = 0; j < data->maxPatient; j++)
            {
                if (data->patients[j].patientNumber !=0)
                {
                    if (data->patients[j].patientNumber == data->appointments[i].patientNo)
                    {
                        tmp1[i] = data->patients[j];
                    }
                }
                
            }
            displayScheduleData(&tmp1[i], &data->appointments[i], 0);
        }     
    }

    putchar('\n');
    
}


// Add an appointment record to the appointment array
// Todo:
void addAppointment( struct Appointment* appointments, int maxApt,  struct Patient* patients, int maxPat)
{
    int i = 0, ptNo= 0, found = 0,j= 0, exits = 0;
    int yr = 0, mth = 0, day = 0, hr = 0, min = 0, empty = 0, index = 0;
    for ( i = 0; i < maxApt && found == 0; i++)
    {
        if (appointments[i].patientNo < 1)
        {
            do
            {
               printf("Patient Number: ");
                ptNo = inputIntRange(1024, 1206);
                exits = 0;
                for ( j = 0; j < maxApt && exits == 0; j++)
                {
                    if (ptNo == appointments[j].patientNo)
                    {
                        exits = 1;
                    };
                }
            } while (exits == 1);
            found = 1;
            index = i;
        }
    }

    do
    {
        empty = 0;
        printf("Year        : ");
        scanf(" %d", &yr);
        printf("Month (1-12): ");
        mth = inputIntRange(1, 12);
        day = inputDay(mth, yr);
        do
        {
            printf("Hour (0-23)  : ");
            hr = inputIntRange(0, 23);
            printf("Minute (0-59): ");
            min = inputIntRange(0, 59);
            if ((hr < START || hr > END) || (min % APPTINT != 0))
            {
                printf("ERROR: Time must be between 10:00 and 14:00 in 30 minute intervals.\n");
                putchar('\n');
            }
            else if (hr == 14 && min != 0)
            {
                printf("ERROR: Time must be between 10:00 and 14:00 in 30 minute intervals.\n");
                putchar('\n');
            }
            
        } while ((hr < START || hr > END) || (min % APPTINT != 0) || (hr == 14 && min != 0));

        // checking in appointment list
        for ( i = 0; i < maxApt && empty == 0; i++)
        {
            if (yr == appointments[i].date.year && mth == appointments[i].date.month && day == appointments[i].date.day && hr == appointments[i].time.hour && min == appointments[i].time.min)
            {
                putchar('\n');
                printf("ERROR: Appointment timeslot is not available!\n");
                empty = 1;
            }
        }  
        putchar('\n');
    } while (empty == 1);

    if (empty == 0)
    {
        appointments[index].date.year = yr;
        appointments[index].date.month = mth;
        appointments[index].date.day = day;
        appointments[index].time.hour = hr;
        appointments[index].time.min = min;
        appointments[index].patientNo = ptNo;
       
        printf("*** Appointment scheduled! ***\n");
    }
    putchar('\n');
}

// Remove an appointment record from the appointment array
// Todo:
void removeAppointment(struct Appointment* appointments, int maxApt, struct Patient* patients, int maxPat)
{
    int patNO = 0, yr = 0, mth = 0, day = 0, i = 0, found = 0, selection = 0, remove=0,j =0;

    printf("Patient Number: ");
    scanf(" %d%*c", &patNO);
    for ( i = 0; i < maxApt && appointments[i].patientNo != 0 && found == 0; i++)
    {
        if (patNO == appointments[i].patientNo)
        {
            found = 1;  
        }  
    }
    if (found == 1)
    {
        printf("Year        : ");
        scanf(" %d", &yr);
        printf("Month (1-12): ");
        mth = inputIntRange(1, 12);
        day = inputDay(mth,yr);
        putchar('\n');
        for ( i = 0; i < maxApt && appointments[i].patientNo !=0 && remove == 0; i++)
        {
            
            if (yr == appointments[i].date.year && mth == appointments[i].date.month && day == appointments[i].date.day && patNO == appointments[i].patientNo)
            {
                found = 0;
                for ( j = 0; j < maxPat && patients[j].patientNumber !=0 && found == 0; j++)
                {
                    
                    if (patNO == patients[j].patientNumber)
                    {
                        
                        displayPatientData(&patients[j], FMT_FORM);
                        found = 1;

                    }
                }
                
                printf("Are you sure you want to remove this appointment (y,n): ");
                selection = inputCharOption("yn") == 'y';
                putchar('\n');
                if (selection)
                {
                    appointments[i].patientNo = 0;    
                    printf("Appointment record has been removed!\n");
                    remove = 1;

                }
                else
                {
                    printf("Operation aborted\n");
                }
            }
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
// (Copy your code from MS#2)
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
// (Copy your code from MS#2)
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
// (Copy your code from MS#2)
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
// (Copy your code from MS#2)
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
// (Copy your code from MS#2)
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
// (Copy your code from MS#2)
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


//////////////////////////////////////
// FILE FUNCTIONS
//////////////////////////////////////

// Import patient data from file into a Patient array (returns # of records read)
/// ToDo:
int importPatients(const char* datafile, struct Patient patients[], int max)
{
    FILE* fp = NULL;
    int numdata = 0;
    fp = fopen(datafile, "r");
    
    if (fp != NULL)
    {
        do
        {
            // taking phone description and if des == TBD reading 3 element else 4.
            fscanf(fp, "%d%*c%[^|]%*c%[^|]%*c%[^\n]%*c", &patients[numdata].patientNumber, patients[numdata].name, patients[numdata].phone.description, patients[numdata].phone.number);

            if (!feof(fp))
            {
                numdata++;
            }
        } while (!feof(fp) && numdata < max);
        fclose(fp);
    }
    return numdata;
}

// Import appointment data from file into an Appointment array (returns # of records read)
// ToDo:
int importAppointments(const char* datafile, struct Appointment appoints[], int max)
{
    FILE* fp = NULL;
    int i = 0, dataread = 0, numdata = 0;
    fp = fopen(datafile, "r");
    if (fp != NULL)
    {
        for (i = 0; i < max && !(feof(fp)); i++)
        {
            dataread = fscanf(fp, "%d%*c%d%*c%d%*c%d%*c%d%*c%d%*c", &appoints[numdata].patientNo, &appoints[numdata].date.year, &appoints[numdata].date.month, &appoints[numdata].date.day, &appoints[numdata].time.hour, &appoints[numdata].time.min);

            if (dataread == 6)
            {
                numdata++;
            }
        }
        fclose(fp);
    }
    return numdata;
}