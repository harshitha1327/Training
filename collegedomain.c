 // College domain using CRUD operations.

#include <stdio.h>
#include <string.h>
#include "mytools.h"
#define FILE_NAME "studentDetails.dat"
#define SIZE_OF_STUDENT_ID 15
#define SIZE_OF_STUDENT_NAME 30

struct studentDetails 
{
	char studentId[SIZE_OF_STUDENT_ID];
 	char studentName[SIZE_OF_STUDENT_NAME];
 	int studentAge;
 	char status;
} student;

void addStudent();
void showAllStudents();
void addDetails(FILE*, struct studentDetails*);
void updateStudentAge();
void seekBack(FILE*);
FILE* checkId();
void removeStudent();

const int sizeofStudent = sizeof(student);

void main()
{
 	int userOption, exitControl = 1;
 	do
 	{
	 	printf("1. Add Student\n2. Show All Students\n3. Update Student Details\n4. Remove Student\n5. Exit\nEnter an option: ");
	 	scanf("%d", &userOption);
	 	switch (userOption)
	 	{
	 	   case 1:	addStudent();
	 	   	     	break;
	 	   case 2: 	showAllStudents();
	 	   	    	break;
	 	   case 3: 	updateStudentAge();
	 	           	break;
	 	   case 4: 	removeStudent();
	 	           	break;
	 	   case 5: 	exitControl = 0; 
	 	          	break;
	 	   default: printf("Enter valid option!\n");    
	 	}
	} while (exitControl == 1);
}

void addStudent()
{
 	printf("Enter the following details to add a student.\n");
   printf("Enter student id: ");
   scanf("%s", student.studentId);
   printf("Enter student name: ");
 	getchar();
 	fgets(student.studentName, SIZE_OF_STUDENT_NAME, stdin);
   removeNewLine(student.studentName);
   printf("Enter student age: ");
   scanf("%d", &student.studentAge);
   student.status = 'Y';
   FILE *fpStudents = fopen(FILE_NAME, "ab"); 
   addDetails(fpStudents, &student);
   fclose(fpStudents);
}

void addDetails(FILE *fpStudents, struct studentDetails *student)
{
 	fwrite(student, sizeofStudent, 1, fpStudents);
}

void showAllStudents()
{
 	FILE *fpStudents = fopen(FILE_NAME, "rb");
 	printf("%15s %30s %15s %6s\n", "Student Id", "Student Name", "Student Age", "Status");
 	while (fread(&student, sizeofStudent, 1, fpStudents) == 1)
 	{
 		printf("%15s %30s %15d %6c\n", student.studentId, student.studentName, student.studentAge, student.status);
 	}
 	fclose(fpStudents);
}

void updateStudentAge()
{
 	FILE *fpStudents = checkId();
 	if (fpStudents == NULL)
 	{
 		return;
 	}
 	else
 	{
 	   seekBack(fpStudents);
 		printf("Enter the new age: ");
 		scanf("%d", &student.studentAge);
 		addDetails(fpStudents, &student);
 	}
 	fclose(fpStudents);
}

FILE* checkId()
{
	char studentId[SIZE_OF_STUDENT_ID];
 	printf("Enter student id: ");
 	scanf("%s", studentId);
 	FILE *fpStudents = fopen(FILE_NAME, "rb+");
 	while(fread(&student, sizeofStudent, 1, fpStudents) == 1)
 	{
 		if(strcmp(studentId, student.studentId) == 0)
 		{
 			return fpStudents;
 		}
 	}
 	fclose(fpStudents);
 	printf("Id not exists!\n");
 	return NULL;
}

void seekBack(FILE *fpStudents)
{
 	fseek(fpStudents, -1L * sizeofStudent, SEEK_CUR);
}

void removeStudent()
{
 	FILE *fpStudents = checkId();
 	if (fpStudents == NULL)
 	{
 		return;
 	}
 	else
 	{
 		seekBack(fpStudents);
 		student.status = 'N';
 		addDetails(fpStudents, &student);
 	}
 	fclose(fpStudents);
}