 // A domain for inventory using  singly linkedlist.

#include <stdio.h>
#include <stdlib.h>
#include "mytools.h"

#define SIZE_OF_ITEM_NAME 40
#define SIZE_OF_ITEM_ID 15

void printResponse(int result);
int addItem();
int showAllItems();
int updateItemPrice();
int deleteItem();
int isItemIdFound();

struct inventory
{
	char itemId[SIZE_OF_ITEM_ID];
	char itemName[SIZE_OF_ITEM_NAME];
	int itemPrice;
	char status;
	struct inventory *nextItem;
};

struct inventory *head = NULL;
struct inventory *last = NULL;
struct inventory *temp = NULL;
struct inventory *newItem = NULL;

void main()
{
	int userChoice, result, userResponse = 1;
	do
	{
		printf("1. Add an Item\n2. Show All Items\n3. Update Item Price\n4. Delete an Item\n5. Exit\nEnter an Option: ");
		scanf("%d", &userChoice);
		switch (userChoice)
		{
			case 1: result = addItem();
					printResponse(result);
					break;
			case 2: result = showAllItems();
					printResponse(result);
					break;
			case 3: result = updateItemPrice();
					printResponse(result);
					break;
			case 4: result = deleteItem();
					printResponse(result);
					break;
			case 5: userResponse = 0;
					break;
		}
	} while(userResponse);	
}

int addItem()
{
	newItem = (struct inventory*) malloc (sizeof(struct inventory));
	getchar();
	printf("Enter item id: ");
	fgets(newItem -> itemId, SIZE_OF_ITEM_ID, stdin);
	removeNewLine(newItem -> itemId);
	printf("Enter item name: ");
	fgets(newItem -> itemName, SIZE_OF_ITEM_NAME, stdin);
	removeNewLine(newItem -> itemName);
	printf("Enter item price: ");
	scanf("%d", &newItem -> itemPrice);
	newItem -> status = 'I';
	if (head == NULL)
	{
		head = last = newItem;
	}
	else
	{
		last -> nextItem = newItem;
		newItem -> next = NULL;
		last = newItem;
	}
	return 1;
}

void printResponse(int result)
{
	if (result)
	{
		printf("Request processed successfully!\n");
	}
	else
	{
		printf("Failed in processing the request!\n");
	}
}

int showAllItems()
{
	int positionTheText = 10;
	if (head == NULL)
	{
		printf("Inventory is empty!\n");
		return 0;
	}
	printf("%*s %*s %*s %*s\n", SIZE_OF_ITEM_ID, "Item Id", SIZE_OF_ITEM_NAME, "Item Name",positionTheText, "ItemPrice", positionTheText, "Status");
	for (temp = head; temp != NULL; temp = temp -> nextItem)
	{
		printf("%*s %*s %*d ", SIZE_OF_ITEM_ID, temp -> itemId, SIZE_OF_ITEM_NAME, temp -> itemName, positionTheText, temp -> itemPrice);	
		if (temp -> status == 'I')
		{
			printf("In Stock\n");
		}
		else
		{
			printf("Out Of Stock\n");
		}
	}
	return 1;
}

int updateItemPrice()
{
	int itemFound = isItemIdFound();
	if (itemFound)
	{
		printf("Enter new price of the item: ");
		scanf("%d", &temp -> itemPrice);
		return 1;
	}
	return 0;
}

int deleteItem()
{
	int itemFound = isItemIdFound();
	if (itemFound)
	{
		temp -> status = 'O';
		return 1;
	}
	return 0;		
}

int isItemIdFound()
{
	char itemId[SIZE_OF_ITEM_ID];
	getchar();
	printf("Enter item id: ");
	fgets(itemId, SIZE_OF_ITEM_ID, stdin);
	removeNewLine(itemId);
	for (temp = head; temp != NULL ; temp = temp -> nextItem)
	{
		if (strcmp(temp -> itemId, itemId) == 0)
		{
				return 1;
		}
	}
	printf("Item id not found!\n");
	return 0;
}
