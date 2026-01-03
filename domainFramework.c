 // A domain which is suitable to create any basic domain.

#include <stdio.h>
#include "mytools.h"
#define SIZE_OF_STRING 30

const char *DETAILS_FILE = "details.dat";
const char *MENU_FILE = "menu.cfg";
const char *FIELD_NAMES_FILE = "fieldNames.cfg";
FILE *fpDetails, *fpFieldNames, *fpMenus;
char fieldName[SIZE_OF_STRING], fieldValue[SIZE_OF_STRING], lastFieldName[SIZE_OF_STRING];
int fieldCount;

void printMenu();
int create();
int showAll();
int update();
int delete();
void openFieldsFile();
void closeFile(FILE*);
void printResponse(int);
// char* takeIdFromUser();
int checkId();
void printValue(char*);

void main()
{
	int userResponse, requestStatus;
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
	char menuOption[SIZE_OF_STRING];
	fpMenus = fopen(MENU_FILE, "r");
	while (fgets(menuOption, SIZE_OF_STRING, fpMenus))
	{
		printf("%s", menuOption);
	}
	closeFile(fpMenus);
}

int create()
{
	openFieldsFile();
	fpDetails = fopen(DETAILS_FILE, "ab");
	getchar();
	while (fgets(fieldName, SIZE_OF_STRING, fpFieldNames))
	{
		removeNewLine(fieldName);
		printf("Enter %s: ",fieldName);
		fgets(fieldValue, SIZE_OF_STRING, stdin);
		removeNewLine(fieldValue);
		fwrite(fieldValue, SIZE_OF_STRING, 1, fpDetails);
	}
	char status = 'A';
	fprintf(fpDetails, "%c", status);
	closeFile(fpFieldNames);
	closeFile(fpDetails);
	return 1;
}

int showAll()
{
	fieldCount = 0; 
	int presentPosition;
	char status;
	openFieldsFile();
	while (fgets(fieldName, SIZE_OF_STRING, fpFieldNames))
	{
		fieldCount++;
		removeNewLine(fieldName);
		printf("%*s", SIZE_OF_STRING, fieldName);
	}
	strcpy(lastFieldName, fieldName);
	printValue("Status");
	printf("\n");
	fpDetails = fopen(DETAILS_FILE, "rb");
	char character;
	int sizeOfRecord = SIZE_OF_STRING * fieldCount;
	char record[sizeOfRecord];
	while (fread(fieldValue, SIZE_OF_STRING, 1, fpDetails) == 1)
	{
		// printf("%*s", SIZE_OF_STRING, fieldName);
		printValue(fieldValue);
	    for (int fieldCounter = 2; fieldCounter <= fieldCount; fieldCounter++)
        {
        	fread(fieldValue, SIZE_OF_STRING, 1, fpDetails);
        	printValue(fieldValue);
        }
		fread(&status, 1, 1, fpDetails);
		printValue(&status);
		printf("\n");
		// if (status == 'A')
		// {
		// 	printf("Active\n");
		// }
		// else
		// {
		// 	printf("InActive\n");
		// }
	}
	closeFile(fpFieldNames);
	closeFile(fpDetails);
	return 1;
}

void printValue(char *fieldValue)
{
	printf("%*s", SIZE_OF_STRING, fieldValue);
}

void openFieldsFile()
{
	fpFieldNames = fopen(FIELD_NAMES_FILE, "r");
}

void closeFile(FILE* fp)
{
	fclose(fp);
	fp = NULL;
}

int update()
{  
	// char *id = takeIdFromUser();
	int idExists = checkId();
	char newValue[SIZE_OF_STRING];
	if (idExists)
	{
		fseek(fpDetails, -1L * (SIZE_OF_STRING + 1), SEEK_CUR);
		printf("Enter new %s: ", lastFieldName);
		fgets(newValue, SIZE_OF_STRING, stdin);
		fwrite(newValue, SIZE_OF_STRING, 1, fpDetails);
		closeFile(fpDetails);
		return 1;
	}
	return 0;
}

int delete()
{
	// char *id = takeIdFromUser();
	int idExists = checkId();
	if (idExists)
	{
		fseek(fpDetails, -1L, SEEK_CUR);
		fputc('I', fpDetails);
		closeFile(fpDetails);
		return 1;
	}
	return 0;
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

// char* takeIdFromUser()
// {
	// char id[SIZE_OF_STRING];
	// openFieldsFile();
	// fgets(fieldName, SIZE_OF_STRING, fpFieldNames); // Assuming that first one is always id.
	// closeFile(fpFieldNames);
	// removeNewLine(fieldName);
	// printf("Enter %s: ", fieldName); 
	// fgets(id, SIZE_OF_STRING, stdin);
	// return id;
// }  

int checkId()
{
	char id[SIZE_OF_STRING];
	openFieldsFile();
	fgets(fieldName, SIZE_OF_STRING, fpFieldNames); // Assuming that first one is always id.
	closeFile(fpFieldNames);
	removeNewLine(fieldName);
	getchar();
	printf("Enter %s: ", fieldName); 
	fgets(id, SIZE_OF_STRING, stdin);
	removeNewLine(id);
	// return id;
	int SizeOfRemainingRecord = (SIZE_OF_STRING * (fieldCount - 1)) + 1;
	fpDetails = fopen(DETAILS_FILE, "rb+");
	while (fgets(fieldValue, SIZE_OF_STRING, fpDetails) != NULL)
	{
		printf("%s", fieldValue);
		if (strcmp(fieldValue, id) == 0)
		{
			fseek(fpDetails, SizeOfRemainingRecord, SEEK_CUR);
			return 1;
		}
	}
	return 0;
}

