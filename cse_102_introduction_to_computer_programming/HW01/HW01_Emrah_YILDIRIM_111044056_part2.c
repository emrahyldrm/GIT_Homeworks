/*##############################################################*/
/*HW01_111044056_part2.c										*/
/*--------------------------------------------------------------*/
/*Coded by Emrah YILDIRIM on February 21, 2014					*/
/*																*/
/*Description													*/
/*This program calculates 3 students' average age				*/
/*Inputs:														*/
/*3 student numbers and birth years								*/
/*Current year define by macros									*/
/*Output:														*/
/*Result of the average calculation								*/
/*##############################################################*/

#include<stdio.h>
#define CURRENT_YEAR 2014


int main(void)
{
	/*START_OF_MAIN*/
	int num1, num2, num3,		/*Student numbers*/
		year1, year2, year3,	/*Birth years*/
		age1, age2, age3;		/*Current ages*/

	double average;				/*Average of ages*/
	
	FILE *birthYrsPtr;			/*file pointer for birth years file*/
	FILE *averageYrsPtr;		/*file pointers for average years file*/
	
	/*END_OF_VARIABLES*/
	
	/*Open the input and output text files*/
	birthYrsPtr   = fopen("BirthYears.txt", "r");
	averageYrsPtr = fopen("AverageAges.txt", "w");
	
	/*Take the student numbers and birth years from input text file*/
	fscanf(birthYrsPtr, "%d", &num1);
	fscanf(birthYrsPtr, "%d", &year1);
	fscanf(birthYrsPtr, "%d", &num2);
	fscanf(birthYrsPtr, "%d", &year2);
	fscanf(birthYrsPtr, "%d", &num3);
	fscanf(birthYrsPtr, "%d", &year3);
	
	/*Calculate the current ages and their averages*/
	age1 = CURRENT_YEAR - year1;
	age2 = CURRENT_YEAR - year2;
	age3 = CURRENT_YEAR - year3;
	
	average =(age1 + age2 + age3) / 3;

	/*Write the result to console and the output file*/
	fprintf(averageYrsPtr, "%.2f", average);
	printf("The student whose number %d age is %d\n", num1, age1);
	printf("The student whose number %d age is %d\n", num2, age2);
	printf("The student whose number %d age is %d\n", num3, age3);
	printf("The students ages' average is %.2f\n", average);

	/*Close the opened files*/
	fclose(birthYrsPtr);
	fclose(averageYrsPtr);
	system("pause");
	return 0;
	
	/*END_OF_MAIN*/
}