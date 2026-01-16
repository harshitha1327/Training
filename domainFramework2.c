 // The program which can be used by any domain. 

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mytools.h"

#define SIZE_OF_FIELD_VALUE 30
#define SIZE_OF_MENU_OPTION 50
#define SIZE_OF_FIELD_NAME 30

const char *DETAILS_FILE = "details.dat";
const char *MENU_FILE = "menu.cfg";
const char *FIELD_NAMES_FILE = "fieldNames.cfg";

FILE *fpDetails, *fpFieldNames, *fpMenus;
char fieldName[SIZE_OF_FIELD_VALUE];
char fieldValue[SIZE_OF_FIELD_VALUE];
char **fieldNames;
int fieldCount;
int sizeOfChar = sizeof(char);

void printMenu();
int create();
int showAll();
int findSizeOfRecord();
int update();
int delete();
void closeFile(FILE*);
void printResponse(int);
int checkId();
void printValue(char*);
int getFieldCount();
void loadFieldsIntoArray();

void main()
{
	int userResponse, requestStatus;
	loadFieldsIntoArray();
	do
	{
		printMenu();
		scanf("%d", &userResponse);
		switch (userResponse)
		{
			case 1: requestStatus = create();
				    printResponse(requestStatus);
					break;
			case 2: requestStatus = showAll();
				    printResponse(requestStatus);
					break;
			case 3: requestStatus = update();
					printResponse(requestStatus);
					break;
			case 4: requestStatus = delete();
				    printResponse(requestStatus);
					break;
			case 5: break;
			default: printf("Invalid Option! ");
		}
	} while (userResponse != 5);
}

void printMenu()
{
	char menuOption[SIZE_OF_MENU_OPTION];
	fpMenus = fopen(MENU_FILE, "r");
	while (fgets(menuOption, SIZE_OF_MENU_OPTION, fpMenus))
	{
		printf("%s", menuOption);
	}
	closeFile(fpMenus);
}

int create()
{
	char addOneMore;
	fpDetails = fopen(DETAILS_FILE, "ab");
	do
	{
		getchar();
		for (int fieldCounter = 0; fieldCounter < fieldCount; fieldCounter++)
		{
			printf("Enter %s: ", fieldNames[fieldCounter]);
			fgets(fieldValue, SIZE_OF_FIELD_VALUE, stdin);
			removeNewLine(fieldValue);
			fwrite(fieldValue, SIZE_OF_FIELD_VALUE, 1, fpDetails);
		}
		char status = 'A';
		fputc(status, fpDetails);
		printf("Enter 'Y' if you want to add one more: ");
		scanf("%c", &addOneMore);
	} while (addOneMore == 'Y');
	closeFile(fpDetails);
	return 1;
}

int showAll()
{
	int fieldCounter;
	for (fieldCounter = 0; fieldCounter < fieldCount; fieldCounter++)
	{
		printValue(fieldNames[fieldCounter]);
	}
	printValue("Status\n");
	int sizeOfRecord = findSizeOfRecord();
	fpDetails = fopen(DETAILS_FILE, "rb");
	fseek(fpDetails, 1, SEEK_END);
	int sizeOfFile = ftell(fpDetails);
	rewind(fpDetails);
	int numberOfRecords = sizeOfFile / sizeOfRecord; 
	int recordCounter = numberOfRecords;
	while(recordCounter != 0)
	{
		for (fieldCounter = 0; fieldCounter < fieldCount; fieldCounter++)
		{
			fread(fieldValue, SIZE_OF_FIELD_VALUE, 1, fpDetails);
			printValue(fieldValue);
		}
		char status = fgetc(fpDetails);
		if (status == 'A')
		{
			printValue("Active\n");
		}
		else
		{
			printValue("InActive\n");
		}
		recordCounter--;
	}
	return 1;
}

void printValue(char *fieldValue)
{
	printf("%*s", SIZE_OF_FIELD_VALUE, fieldValue);
}

int update()
{
	int isIdExists = checkId();
	if (isIdExists)
	{
		printf("Enter %s: ", fieldNames[fieldCount - 1]);
		fgets(fieldValue, SIZE_OF_FIELD_VALUE, stdin);
		removeNewLine(fieldValue);
		fseek(fpDetails, -1L * (SIZE_OF_FIELD_VALUE + sizeOfChar), SEEK_CUR);
		fwrite(fieldValue, SIZE_OF_FIELD_VALUE, 1, fpDetails);
		closeFile(fpDetails);
	}
	return 1;
}

int checkId()
{
	int sizeOfRecordWithoutStatus = (findSizeOfRecord()) - sizeOfChar;
	char checkingId[SIZE_OF_FIELD_VALUE], recordValueWithoutStatus[sizeOfRecordWithoutStatus];
	char actualId[SIZE_OF_FIELD_VALUE];
	getchar();
	printf("Enter %s: ", fieldNames[0]);
	fgets(checkingId, SIZE_OF_FIELD_VALUE, stdin);
	removeNewLine(checkingId);
	fpDetails = fopen(DETAILS_FILE, "rb+");
	while (fread(recordValueWithoutStatus, sizeOfRecordWithoutStatus, 1, fpDetails))
	{
		char status = fgetc(fpDetails);
		strncpy(actualId, recordValueWithoutStatus, SIZE_OF_FIELD_VALUE);
		if (status == 'A')
		{
			if (strcmp(checkingId, actualId) == 0)
			{
				return 1;
			}
		}
	}
	closeFile(fpDetails);
	printf("Id not found. \n");
	return 0;
}

int delete()
{
	int isIdExists = checkId();
	if (isIdExists)
	{
		fseek(fpDetails, -1L * sizeOfChar, SEEK_CUR);
		char status = 'I';
		fputc(status, fpDetails);
		closeFile(fpDetails);
	}
	return 1;
}

int getFieldCount()
{
	int fieldCount = 0;
	fpFieldNames = fopen(FIELD_NAMES_FILE, "r");
	while (fgets(fieldValue, SIZE_OF_FIELD_NAME, fpFieldNames))
	{
		fieldCount++;
	}	
	closeFile(fpFieldNames);
	return fieldCount;
}

void loadFieldsIntoArray()
{
    fieldCount = getFieldCount();
	fieldNames = (char **) malloc (fieldCount * sizeof(char*));
	fpFieldNames = fopen(FIELD_NAMES_FILE, "r");
		for (int fieldCounter = 0; fieldCounter < fieldCount; fieldCounter++)
		{
			fieldNames[fieldCounter] = (char *) malloc (SIZE_OF_FIELD_NAME);
			fgets(fieldName, SIZE_OF_FIELD_NAME, fpFieldNames);
			removeNewLine(fieldName);
			strcpy(fieldNames[fieldCounter], fieldName);
		}
	closeFile(fpFieldNames);
}

void printResponse(int requestStatus)
{
	if (requestStatus)
	{
		printf("Request processed successfully! \n");
	}
	else
	{
		printf("Failed in processing the request! \n");
	}
}

void closeFile(FILE* fp)
{
	fclose(fp);
	fp = NULL;
}

int findSizeOfRecord()
{
	int sizeOfRecord = (SIZE_OF_FIELD_VALUE * fieldCount) + sizeOfChar;
	return sizeOfRecord;
}