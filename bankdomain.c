 // To read, save and show the account details.

#include <stdio.h>
#include "mytools.h"
#define FILE_NAME "accountDetails.dat"
#define SIZE_OF_NAME 30
#define SIZE_OF_ACCOUNT_NUMBER 15

struct accountDetails
{
   char accountNumber[SIZE_OF_ACCOUNT_NUMBER];
   char customerName[SIZE_OF_NAME];
   int accountBalance;
   char status;
} customer;

const int sizeOfCustomer = sizeof(customer);

void openAccount();
void showAllAccounts();
void deposit();
void withdraw();
void writeIntoAccounts(struct accountDetails*, FILE*);
void closeAccount();
FILE* seekPointerBack(FILE*);
FILE* checkAccountNumber();

void main()
{
 	int option, exitControl = 0;
 	do
 	{
 		printf("1. Open an Account\n2. Show All Accounts\n3. Deposit\n4. Withdraw\n5. Close an Account\n6. Exit\nEnter an option: ");
 		scanf("%d", &option);
 		switch (option)
 		{
 			case 1: openAccount();
 				     break;
 			case 2: showAllAccounts();
 					  break;
         case 3: deposit();
                 break;
         case 4: withdraw();
                 break;       
         case 5: closeAccount();
                 break;
  			case 6: exitControl = 1;
 				     break;
 			default: printf("Enter valid option!\n");
 		}

 	} while (exitControl == 0);
}

void openAccount()
{
   printf("Enter the following account details to open an account.\n");
 	printf("Enter account number: ");
 	scanf("%s", customer.accountNumber);
   printf("Enter customer name: ");
   getchar();
   fgets(customer.customerName, SIZE_OF_NAME, stdin);
   removeNewLine(customer.customerName);
 	printf("Enter account balance: ");
 	scanf("%d", &customer.accountBalance);
   customer.status = 'A';
   FILE *fpAccounts = fopen(FILE_NAME, "ab");
   writeIntoAccounts(&customer, fpAccounts);
 	fclose(fpAccounts);
}

void showAllAccounts()
{
   FILE *fpAccounts = fopen(FILE_NAME, "r");
   printf("%15s %30s %15s %s\n", "Account Number", "Customer Name", "Account Balance", "Status");
   while (fread(&customer, sizeOfCustomer, 1, fpAccounts) == 1)
   {
      printf("%15s %30s %15d %4c\n", customer.accountNumber, customer.customerName, customer.accountBalance, customer.status);
   }
   fclose(fpAccounts);
}

void withdraw()
{
   int withdrawAmount;
   FILE* fpAccounts = checkAccountNumber();
   if(fpAccounts == NULL)
   {
      return;
   }
   printf("Enter your withdraw amount: ");
   scanf("%d", &withdrawAmount);
   customer.accountBalance -= withdrawAmount;
   fpAccounts = seekPointerBack(fpAccounts);
   writeIntoAccounts(&customer, fpAccounts);
   fclose(fpAccounts); 
} 

void deposit()
{
   int depositAmount; 
   FILE *fpAccounts = checkAccountNumber();
   if(fpAccounts == NULL)
   {
      return;
   }
   printf("Enter your deposit amount: ");
   scanf("%d", &depositAmount);
   customer.accountBalance += depositAmount;
   fpAccounts = seekPointerBack(fpAccounts);
   writeIntoAccounts(&customer, fpAccounts);
   fclose(fpAccounts);    
} 

void closeAccount()
{

   FILE *fpAccounts = checkAccountNumber();
   if (fpAccounts == NULL)
   {
      return;
   }
   else
   {
      customer.status = 'C';
   }
   fpAccounts = seekPointerBack(fpAccounts);
   writeIntoAccounts(&customer, fpAccounts);
   fclose(fpAccounts);
}
 
void writeIntoAccounts(struct accountDetails* customer, FILE *fpAccounts)
{
   fwrite(customer, sizeOfCustomer, 1, fpAccounts); 
}

FILE* checkAccountNumber()
{
   char accountNumber[SIZE_OF_ACCOUNT_NUMBER];
   printf("Enter your account number: ");
   scanf("%s", accountNumber);
   FILE *fpAccounts = fopen(FILE_NAME, "rb+");
   while (fread(&customer, sizeOfCustomer, 1, fpAccounts) == 1)
   {
      if (strcmp(accountNumber, customer.accountNumber) == 0)
      {
         return fpAccounts;
      }
   }
   fclose(fpAccounts);
   printf("Account number not found!\n");
   return NULL;   
}

FILE* seekPointerBack(FILE *fpAccounts)
{
   fseek(fpAccounts, -1L * sizeOfCustomer, SEEK_CUR);
   return fpAccounts;
}
