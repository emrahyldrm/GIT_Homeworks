/*#########################################################################*/
/*HW00_111044056_part2.c												   */
/*-------------------------------------------------------------------------*/
/*Coded by Emrah YILDIRIM on February 12, 2014						  	   */
/*																		   */
/*Description															   */
/*-------------------------------------------------------------------------*/
/*Take the derivative of given parabola									   */
/*Inputs:																   */
/*Coefficients of the parabola											   */
/*-------------------------------------------------------------------------*/
/*Outputs:																   */
/*Result																   */
/*#########################################################################*/


#include<stdio.h>


int main()
{
	/*START_OF_MAIN*/
	
	double c1, c2, c3;				/*Coefficients of the poly*/
	int    element1, element2;		/*Parts of derivative*/
	
	/*END_OF_VARIABLES*/
	
	/*Get the parabola's coefficients*/
	printf("Enter the coefficients of the parabola (from higher to lower order)\n");
	scanf("%lf %lf %lf", &c1, &c2, &c3);
	
	
	/*Calculate the derivative of the parabola*/
	element1 = c1*2;
	element2 = c2;
	
	/*Print the result*/
	printf("The parabola's derivative is \" %dx+%d \"\n", element1, element2);
	

	return 0;
	
	/*END_OF_MAIN*/	
}
