 // Railway domain using CRUD operations.

#include <stdio.h>
#include <string.h>
#include "mytools.h"
#include "global.c"
// #define FILE_NAME "passangerDetails.dat"
// #define SIZE_OF_PASSANGER_NAME 30
// #define SIZE_OF_PNRNUMBER 15

struct passangerDetails
{
  char PNRNumber[SIZE_OF_PNR_NUMBER];
  char passangerName[SIZE_OF_PASSANGER_NAME];
  int passangerAge;
  char bookingStatus;
}passanger;
 
void bookTicket();
void showPassangersList();
void writeIntoPassangers(struct passangerDetails*, FILE*);
void updatePassangerDetails();
void seekBack(FILE*);
FILE* checkPassangerPNR();
void cancelTicket();

// const int sizeOfPassangerDetails = sizeof(passanger);

void main()
{
  int userOption, exitControl = 0;
  do
  {
    drawLine();
    printf("1. Book a Ticket\n2. Show Passangers List\n3. Update Passanger Details\n4. Cancel a Ticket\n5. Exit\nEnter your option: ");
    scanf("%d", &userOption);
    switch (userOption)
    {
      case 1: bookTicket();
              break;
      case 2: showPassangersList();
              break;
      case 3: updatePassangerDetails();
              break;
      case 4: cancelTicket();
              break;
      case 5: exitControl = 1;
              break;
      default: printf("Enter valid option!\n");         
    }
  } while (exitControl == 0);
}

void bookTicket()
{
 	printf("Enter the following details to book a ticket!\n");
 	printf("Enter PNR number: ");
 	scanf("%s", passanger.PNRNumber);
  printf("Enter passanger name: ");
  getchar();
  fgets(passanger.passangerName, SIZE_OF_PASSANGER_NAME, stdin);
  removeNewLine(passanger.passangerName);
 	printf("Enter passanger age: ");
 	scanf("%d", &passanger.passangerAge);
 	passanger.bookingStatus = 'A';
 	FILE *fpPassangers = fopen(FILE_NAME, "ab");
 	writeIntoPassangers(&passanger, fpPassangers);
 	fclose(fpPassangers);
}

void writeIntoPassangers(struct passangerDetails *passanger, FILE *fpPassangers)
{
 	fwrite(passanger, sizeOfPassangerDetails, 1, fpPassangers);
}

void showPassangersList()
{
  FILE *fpPassangers = fopen(FILE_NAME, "rb");
  printf("%15s %30s %20s %s\n", "PNR Number", "Passanger Name", "Passanger Name", "Booking Status");
  while (fread(&passanger, sizeOfPassangerDetails, 1, fpPassangers) == 1)
  {
    printf("%15s %30s %20d %4c\n", passanger.PNRNumber, passanger.passangerName, passanger.passangerAge, passanger.bookingStatus);
  }
  fclose(fpPassangers);
}

void updatePassangerDetails()
{
 	FILE *fpPassangers = checkPassangerPNR();
 	if (fpPassangers == NULL)
 	{
 		return;
 	}
 	seekBack(fpPassangers);
 	printf("Enter the age: ");
 	scanf("%d", &passanger.passangerAge);
 	writeIntoPassangers(&passanger, fpPassangers);	
 	fclose(fpPassangers);
}

void seekBack(FILE *fpPassangers)
{
 	fseek(fpPassangers, -1L * sizeOfPassangerDetails, SEEK_CUR);
}
 
FILE* checkPassangerPNR()
{
 	char PNRNumber[SIZE_OF_PNR_NUMBER];
  printf("Enter PNR number: ");
  scanf("%s", PNRNumber);
 	FILE *fpPassangers = fopen(FILE_NAME, "rb+");
 	while (fread(&passanger, sizeOfPassangerDetails, 1, fpPassangers) == 1)
 	{
 		if(strcmp(passanger.PNRNumber, PNRNumber) == 0)
 		{
 			return fpPassangers;
 		}
 	}
 	printf("PNR number not exists!\n");
 	return NULL;
} 

void cancelTicket()
{
	FILE *fpPassangers = checkPassangerPNR();
	if (fpPassangers == NULL)
 	{
 		return;
 	}
  seekBack(fpPassangers);
 	passanger.bookingStatus = 'C';
 	writeIntoPassangers(&passanger, fpPassangers);
 	fclose(fpPassangers);
}