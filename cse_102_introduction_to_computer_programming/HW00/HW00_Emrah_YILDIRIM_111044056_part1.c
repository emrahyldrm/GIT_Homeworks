/*#########################################################################*/
/*HW00_111044056_part1.c												   */
/*-------------------------------------------------------------------------*/
/*Coded by Evren Ciftci on February 2, 2014							   	   */
/*																		   */
/*Description															   */
/*-------------------------------------------------------------------------*/
/*Evaluates a given 2nd degree polynomial								   */
/*Inputs:																   */
/*Coefficients of the poly												   */
/*Number for which the Poly will be evaluated							   */
/*Outputs:																   */
/*Result																   */
/*#########################################################################*/


#include<stdio.h>


int main ()
{
	/*START_OF_MAIN*/
	
	double c1, c2, c3,  /*coefficients of the poly*/
		   x,			/*variable of the poly*/
		   result; 		/*evaluation value*/

	/*END_OF_VARIABLES*/

	/*Get the poly*/
	printf("Enter the coefficients of the poly(from higher to lower order):\n");
	scanf("%lf %lf %lf", &c1, &c2, &c3);

	/*Get the value of the variable*/
	printf("Enter the value of x:\n");
	scanf("%lf", &x);					  
	
	/*Calculate the evaluation value*/
	result = c1*x*x + c2*x + c3;			
	
	/*Print the result*/
	printf("The result is %5.3f\n", result);
	
	
	return 0;
	
	/*END_OF_MAIN*/
}

