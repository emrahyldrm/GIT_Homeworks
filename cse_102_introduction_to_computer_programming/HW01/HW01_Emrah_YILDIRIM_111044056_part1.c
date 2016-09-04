/*##############################################################*/
/*HW01_111044056_part1.c										*/
/*--------------------------------------------------------------*/
/*Coded by Emrah YILDIRIM on February 21, 2014					*/
/*																*/
/*Description													*/
/*																*/
/*This program evaluates a mathematical function				*/
/*Inputs:														*/
/*a and b variables that takes from user via input file			*/
/*c and d variables that define by macros						*/
/*Output:														*/
/*Result of the function										*/
/*##############################################################*/


#include<stdio.h>  
#include<math.h>

#define C 5
#define D 8

int main(void)
{	
	/*START_OF_MAIN*/
	int a,b;
	
	double operation1, operation2, operation3, 	/*parts of function*/
		   result;								/*function's result*/
		
	FILE *variablesPtr;			/*file pointer for variables a and b*/
	FILE *resultPtr;			/*file pointer for result*/
	
	/*END_OF_VARIABLES*/
	
	
	/*Open and assign the input and output text files*/
	variablesPtr = fopen("Variables.txt", "r");
	resultPtr	 = fopen("Result.txt", "w");
	
	/*Take the values from input text file*/
	fscanf(variablesPtr, "%d", &a);
	fscanf(variablesPtr, "%d", &b);
	
	/*Make the evaluation*/
	operation1 = pow( (double)((a + b) / (b + 1.0)), 3.8);
	operation2 = pow( log( (double)D) / log(3.0)  + (13.0 / 7.0), (0.5) );
	operation3 = pow( (double) (a + (double)D / (double)C) , (1.0 / 3.0) );
	
	result = operation1 + operation2 + operation3;
			 
	/*Write the result to console and output file*/
	fprintf(resultPtr, "%f", result);
	printf("The result of this function is %f\n\n", result);
	
	
	/*Close the opened files*/
	fclose(variablesPtr);
	fclose(resultPtr);
	
	
	return 0;
	
	/*END_OF_MAIN*/
}