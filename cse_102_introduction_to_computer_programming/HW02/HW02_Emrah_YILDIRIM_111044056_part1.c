/*##########################################################################*/
/*HW02_111044056_part1.c													*/
/*--------------------------------------------------------------------------*/
/*Coded by Emrah YILDIRIM on March 03, 2014									*/
/*																			*/
/*Description																*/
/*																			*/
/*Boolean algebra calculator												*/
/*Inputs:																	*/
/*x and y variables that takes from user via console						*/
/*																			*/
/*Output:																	*/
/*Result of the function													*/
/*##########################################################################*/


/*##########################################################################*/
/*									Includes								*/
/*##########################################################################*/

#include<stdio.h>

#define TRUE  1
#define FALSE 0

/*##########################################################################*/
/*							Function Prototypes								*/
/*##########################################################################*/

int Conj(int, int);			/*Conjunction function*/
int Disj(int, int);			/*Disjunction function*/
int Not(int);				/*Negation function*/
int Mate(int, int);			/*Material implication function*/
int Excl(int, int);			/*Exclusive Or function*/


/*##########################################################################*/
/*								MAIN Function								*/
/*##########################################################################*/

int main(void)
{
	/*START_OF_MAIN*/
	
	int x, y;
	
	/*END_OF_VARIABLES*/
	
	
	printf("Enter x and y \n");
	scanf("%d %d", &x, &y);
	
	printf("The Result for  %d and %d\n\n", x, y);
	
	printf("Conjunction  >> %d  \n", Conj(x, y));
	printf("Disjunction  >> %d  \n", Disj(x, y));
	printf("negation     >> %d  \n", Not(x));
	printf("Mate impl    >> %d  \n", Mate(x, y));
	printf("Exclusive or >>	%d  \n", Excl(x, y));
	
	
	return 0;
	
	/*END_OF_MAIN*/
}

/*##########################################################################*/
/*								FUNCTIONS									*/
/*##########################################################################*/

int Conj(int x, int y)		/*Conjunction function*/
{

	int result;

	if (x==y)				/*check x equal y*/
	{
		if(x==1)			/*check x is equal 1*/
			result = TRUE;	
		else
			result = FALSE;
	}
	else
		result = FALSE;
		
	return result;
}


int Disj(int x, int y)		/*Disjunction function*/
{
	int result;
	
	if(x==y)				/*check x equal y*/
	{
		if(x==0)			/*check x equal 0*/
			result = FALSE;	
		else
			result = TRUE;
	}
	else
		result = TRUE;
		
	return result;
}


int Not(int x)				/*Negation function*/
{
	int result;
	
	if (x==1)				/*check x equal 1*/
		result = FALSE;
	else
		result = TRUE;
	
	return result;
}


int Mate (int x, int y)			/*Material implication function*/
{	
	int result;
								/*do Not process first with x*/
	result = Disj(Not(x), y);	/*do Disjunction process with..*/
								/*..return value of Not process and y*/
	
	return result;
}


int Excl (int x, int y)				/*Exclusive Or function*/
{
	int result;
	/*do Disj process with x and y, */
	/*after Not process with result of Conjunction process with x and y */	
	
	result = Conj(Disj(x, y), Not(Conj(x, y)));
	
	return result;
}