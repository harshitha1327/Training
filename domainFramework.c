 // A Domain which is suitable to create any basic domain.

#include <stdio.h>
#include "mytools.h"
#define SIZE_OF_STRING 30

const char *DETAILS_FILE = "details.dat";
const char *MENU_FILE = "menu.cfg";
const char *FIELD_NAMES_FILE = "fieldNames.cfg";
FILE *fpDetails, *fpFieldNames, *fpMenus;
char *fieldName, *fieldValue;

void printMenu();
int create();
int showAll();
int update();
int delete();
void openFieldsFile();
void closeFile(FILE*);
void printResponse(int);

void main()
{
	int userResponse, requestStatus;
	printMenu();
	do
	{
		printf("Enter your option: ");
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
	char *menuOption;
	int menuCounter = 1;
	fpMenus = fopen(MENU_FILE, "r");
	while (fgets(menuOption, SIZE_OF_STRING, fpMenus))
	{
		removeNewLine(menuOption);
		printf("%d. %s", menuCounter,menuOption);
		menuCounter++;
	}
	closeFile(fpMenus);
}

int create()
{
	// char *fieldName, *fieldValue;
	// fpfieldNames = fopen(FIELD_NAMES_FILE, "r");
	openFieldsFile();
	while (fgets(fieldName, SIZE_OF_STRING, fpFieldNames))
	{
		removeNewLine(fieldName);
		printf("Enter %s: ",fieldName);
		fgets(fieldValue, SIZE_OF_STRING, stdin);
		removeNewLine(fieldValue);
		fputs(fieldValue, fpDetails);
	}
	closeFile(fpFieldNames);
	return 1;
}

int showAll()
{
	int fieldCount = 0;
	int presentPosition;
	openFieldsFile();
	while (fgets(fieldName, SIZE_OF_STRING, fpFieldNames))
	{
		fieldCount++;
		removeNewLine(fieldName);
		printf("%*s", SIZE_OF_STRING, fieldName);
	}
	printf("\n");
	fpDetails = fopen(DETAILS_FILE, "r");
	while (fread(&presentPosition, 1, 1, fpDetails) != EOF)
	{
		for (int fieldCounter = 1; fieldCounter <= fieldCount ; fieldCounter++)
		{
			fgets(fieldValue, SIZE_OF_STRING, fpDetails);
			printf("%*s", SIZE_OF_STRING, fieldValue);
		}	
		printf("\n");
	}
	closeFile(fpFieldNames);
	closeFile(fpDetails);
	return 1;
}

void openFieldsFile()
{
	fpFieldNames = fopen(FIELD_NAMES_FILE, "r");
}

void closeFile(FILE* fp)
{
	fclose(fp);
	fp = NULL ;
}

int update()
{
	fpDetails = fopen()
}

int delete()
{

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