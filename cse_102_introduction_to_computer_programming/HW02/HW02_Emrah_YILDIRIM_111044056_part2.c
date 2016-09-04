/*##########################################################################*/
/*HW02_111044056_part2.c													*/
/*--------------------------------------------------------------------------*/
/*Coded by Emrah YILDIRIM on March 03, 2014									*/
/*																			*/
/*Description																*/
/*																			*/
/*Boolean Algebra Calculator Test Program with Monotone Laws				*/
/*Inputs:																	*/
/*x, y and z. Define in testMonotone Function								*/
/*																			*/
/*Output:																	*/
/*Calculator verification for each possibility in text file					*/
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

void testMonotone(void);		/*test function with montone laws*/
int FirstRuleTst(int, int, int, int, FILE *resultsPtr);
int SecondRuleTst(int, int, int, int, FILE *resultsPtr);
int ThirdRuleTst(int, int, int, FILE *resultsPtr);
int ForthRuleTst(int, int, int, FILE *resultsPtr);
int FifthRuleTst(int, int, int, int, FILE *resultsPtr);
int SixthRuleTst(int, int, FILE *resultsPtr);
int SeventhRuleTst(int, int, FILE *resultsPtr);
int EighthRuleTst(int, int, FILE *resultsPtr);
int Conj(int, int);			/*Conjunction function*/
int Disj(int, int);			/*Disjunction function*/

/*##########################################################################*/
/*								MAIN Function								*/
/*##########################################################################*/


int main(void)
{
	/*START_OF_MAIN*/
	
	
	/*END_OF_VARIABLES*/

	
	/*test function calling*/
	testMonotone();


	return 0;
	
	/*END_OF_MAIN*/
}





/*##########################################################################*/
/*								FUNCTIONS									*/
/*##########################################################################*/


/*test function with monotone laws*/
void testMonotone(void)
{
	int count = 0,		/*variable for count correct results for each function*/
		x, y, z;		/*variable for each probabilities*/
		
	FILE *resultsPtr;	/*result file pointer*/
	
		
	/*open the result file*/
	resultsPtr = fopen("results.txt", "w");
	
	
	/*controlling 1st rule*/
	fprintf(resultsPtr,"1ST RULE;\n");
	x=1; y= 1; z=1;
	count = FirstRuleTst(x, y, z, count, resultsPtr);
	
	x=1; y= 1; z=0;
	count = FirstRuleTst(x, y, z, count, resultsPtr);
	
	x=1; y= 0; z=0;
	count = FirstRuleTst(x, y, z, count, resultsPtr);
	
	x=1; y= 0; z=1;
	count = FirstRuleTst(x, y, z, count, resultsPtr);
	
	x=0; y= 0; z=1;
	count = FirstRuleTst(x, y, z, count, resultsPtr);
	
	x=0; y= 1; z=0;
	count = FirstRuleTst(x, y, z, count, resultsPtr);
	
	x=0; y= 1; z=1;
	count = FirstRuleTst(x, y, z, count, resultsPtr);
	
	x=0; y= 0; z=0;
	count = FirstRuleTst(x, y, z, count, resultsPtr);
	
	/* correctness controlling for each probabilities */
	if  (count == 8)
		fprintf(resultsPtr, ">> THE SYSTEM VERIFIES 1ST RULE\n\n");
	else
		fprintf(resultsPtr, ">> THE SYSTEM DOES NOT VERIFIES 1ST RULE\n\n");
	count=0;		/*reset the counter for use next test*/
	
	
	/*controlling 2nd rule*/
	fprintf(resultsPtr,"2TH RULE;\n");
	x=1; y= 1; z=1;
	count = SecondRuleTst(x, y, z, count, resultsPtr);
	
	x=1; y= 1; z=0;
	count = SecondRuleTst(x, y, z, count, resultsPtr);
	
	x=1; y= 0; z=0;
	count = SecondRuleTst(x, y, z, count, resultsPtr);
	
	x=1; y= 0; z=1;
	count = SecondRuleTst(x, y, z, count, resultsPtr);
	
	x=0; y= 0; z=1;
	count = SecondRuleTst(x, y, z, count, resultsPtr);
	
	x=0; y= 1; z=0;
	count = SecondRuleTst(x, y, z, count, resultsPtr);
	
	x=0; y= 1; z=1;
	count = SecondRuleTst(x, y, z, count, resultsPtr);
	
	x=0; y= 0; z=0;
	count = SecondRuleTst(x, y, z, count, resultsPtr);
	
	/* correctness controlling for each probabilities */
	if  (count == 8)
		fprintf(resultsPtr, ">> THE SYSTEM VERIFIES 2ND RULE\n\n");
	else
		fprintf(resultsPtr, ">> THE SYSTEM DOES NOT VERIFIES 2ND RULE\n\n");
	
	count=0;		/*reset the counter for use next test*/		
	
	fprintf(resultsPtr,"3RD RULE;\n");
	x=1; y= 1;
	count = ThirdRuleTst(x, y, count, resultsPtr);
	
	x=1; y= 0;
	count = ThirdRuleTst(x, y, count, resultsPtr);
	
	x=0; y= 1;
	count = ThirdRuleTst(x, y, count, resultsPtr);
	
	x=0; y= 0;
	count = ThirdRuleTst(x, y, count, resultsPtr);
	
	/* correctness controlling for each probabilities */
	if  (count == 4)
		fprintf(resultsPtr, ">> THE SYSTEM VERIFIES 3RD RULE\n\n");
	else
		fprintf(resultsPtr, ">> THE SYSTEM DOES NOT VERIFIES 3RD RULE\n\n");
	
	count=0;		/*reset the counter for use next test*/
	
	fprintf(resultsPtr,"4TH RULE;\n");
	x=1; y= 1;
	count = ForthRuleTst(x, y, count, resultsPtr);
	
	x=1; y= 0;
	count = ForthRuleTst(x, y, count, resultsPtr);
	
	x=0; y= 1;
	count = ForthRuleTst(x, y, count, resultsPtr);
	
	x=0; y= 0;
	count = ForthRuleTst(x, y, count, resultsPtr);
	
	/* correctness controlling for each probabilities */
	if  (count == 4)
		fprintf(resultsPtr, ">> THE SYSTEM VERIFIES 4TH RULE\n\n");
	else
		fprintf(resultsPtr, ">> THE SYSTEM DOES NOT VERIFIES 4TH RULE\n\n");
	
	count=0;		/*reset the counter for use next test*/
		
	fprintf(resultsPtr,"5TH RULE;\n");
	x=1; y=1; z=1;
	count = FifthRuleTst(x, y, z, count, resultsPtr);
		
	x=1; y= 1; z=0;
	count = FifthRuleTst(x, y, z, count, resultsPtr);
	
	x=1; y= 0; z=0;
	count = FifthRuleTst(x, y, z, count, resultsPtr);
	
	x=1; y= 0; z=1;
	count = FifthRuleTst(x, y, z, count, resultsPtr);
	
	x=0; y= 0; z=1;
	count = FifthRuleTst(x, y, z, count, resultsPtr);
	
	x=0; y= 1; z=0;
	count = FifthRuleTst(x, y, z, count, resultsPtr);
	
	x=0; y= 1; z=1;
	count = FifthRuleTst(x, y, z, count, resultsPtr);
	
	x=0; y= 0; z=0;
	count = FifthRuleTst(x, y, z, count, resultsPtr);
	
	/* correctness controlling for each probabilities */
	if  (count == 8)
		fprintf(resultsPtr, ">> THE SYSTEM VERIFIES 5TH RULE\n\n");
	else
		fprintf(resultsPtr, ">> THE SYSTEM DOES NOT VERIFIES 5TH RULE\n\n");
	
	count=0;		/*reset the counter for use next test*/


	fprintf(resultsPtr,"6TH RULE;\n");
	x=1;
	count = SixthRuleTst(x, count, resultsPtr);
	
	x=0;
	count = SixthRuleTst(x, count, resultsPtr);
	
	/* correctness controlling for each probabilities */
	if  (count == 2)
		fprintf(resultsPtr, ">> THE SYSTEM VERIFIES 6TH RULE\n\n");
	else
		fprintf(resultsPtr, ">> THE SYSTEM DOES NOT VERIFIES 6TH RULE\n\n");
		
	count = 0;		/*reset the counter for use next test*/
	
	
	fprintf(resultsPtr,"7TH RULE;\n");
	x=1;
	count = SeventhRuleTst(x, count, resultsPtr);
	
	x=0;
	count = SeventhRuleTst(x, count, resultsPtr);
	
	/* correctness controlling for each probabilities */
	if  (count == 2)
		fprintf(resultsPtr, ">> THE SYSTEM VERIFIES 7TH RULE\n\n");
	else
		fprintf(resultsPtr, ">> THE SYSTEM DOES NOT VERIFIES 7TH RULE\n\n");
		
	count = 0;		/*reset the counter for use next test*/
	
	
	fprintf(resultsPtr,"8TH RULE;\n");
	x=1;
	count = EighthRuleTst(x, count, resultsPtr);
	x=0;
	count = EighthRuleTst(x, count, resultsPtr);
	
	/* correctness controlling for each probabilities */
	if  (count == 2)
		fprintf(resultsPtr, ">> THE SYSTEM VERIFIES 8TH RULE\n\n");
	else
	{
		fprintf(resultsPtr, ">> THE SYSTEM DOES NOT VERIFIES 8TH RULE\n\n");
	}
	
	/*close the result file*/
	fclose(resultsPtr);
}

/*---------------------------------------------------------------------------*/

/*associativity of disjunction rule*/
int FirstRuleTst(int x, int y, int z, int count, FILE *resultsPtr)
{
	
	if ( Disj(x, Disj(y, z)) == Disj(Disj(x, y), z) )
	{
		fprintf(resultsPtr, "TRUE for x=%d, y=%d, z=%d \n", x, y, z);
		count = count + 1;
	}
	else
		fprintf(resultsPtr,"FALSE for x=%d, y=%d, z=%d \n", x, y, z);
	
	return count;
}

/*associativity of conjunction rule*/
int SecondRuleTst(int x, int y, int z, int count, FILE *resultsPtr)
{
	
	if ( Conj(x, Conj(y, z)) == Conj(Conj(x, y), z) )
	{
		fprintf(resultsPtr, "TRUE for x=%d, y=%d, z=%d \n", x, y, z);
		count = count + 1;
	}
	else
		fprintf(resultsPtr,"FALSE for x=%d, y=%d, z=%d \n", x, y, z);
	
	return count;
}

/*commutativity of disjunction rule*/
int ThirdRuleTst(int x, int y, int count, FILE *resultsPtr)
{
	
	if ( Disj(x, y) == Disj(y, x) )
	{
		fprintf(resultsPtr, "TRUE for x=%d, y=%d \n", x, y);
		count = count + 1;
	}
	else
		fprintf(resultsPtr,"FALSE for x=%d, y=%d \n", x, y);
	
	return count;
}










/*commutativity of conjunction rule*/
int ForthRuleTst(int x, int y, int count, FILE *resultsPtr)
{
	
	if ( Conj(x, y) == Conj(y, x) )
	{
		fprintf(resultsPtr, "TRUE for x=%d, y=%d \n", x, y);
		count = count + 1;
	}
		
	else
		fprintf(resultsPtr, "FALSE for x=%d, y=%d \n", x, y);
		
	return count;
}

/*distribuvity of disjunction and over conjunction*/
int FifthRuleTst(int x, int y, int z, int count, FILE *resultsPtr)
{

	if (Conj(x, Disj(y, z)) == Disj( Conj(x, y), Conj(x, z) ))
	{
		fprintf(resultsPtr, "TRUE for x=%d, y=%d, z=%d \n", x, y, z);
		count = count + 1;
	}
	
	else
		fprintf(resultsPtr, "FALSE for x=%d, y=%d, z=%d \n", x, y, z);
		
	return count;
}

/*identity for disjunction*/
int SixthRuleTst(int x, int count, FILE *resultsPtr)
{
	
	if (Disj(x, 0) == x)
	{
		fprintf(resultsPtr, "TRUE for x=%d \n", x);
		count = count + 1;
	}
	else
		fprintf(resultsPtr, "FALSE for x=%d \n", x);
		
	return count;
}

/*identity for conjuntion*/
int SeventhRuleTst(int x, int count, FILE *resultsPtr)
{
		
	if (Conj(x, 1) == x)
	{
		fprintf(resultsPtr, "TRUE for x=%d \n", x);
		count = count + 1;
	}
	else
		fprintf(resultsPtr, "FALSE for x=%d \n", x);
	
	return count;
}






/*annihilator for conjunction*/
int EighthRuleTst(int x, int count, FILE *resultsPtr)
{

	if (Conj(x, 0) == 0)
	{
		fprintf(resultsPtr, "TRUE for x=%d \n", x);
		count = count + 1;
	}
	else
		fprintf(resultsPtr, "FALSE for x=%d \n", x);
	
	return count;
}
/*---------------------------------------------------------------------------*/

int Conj(int x, int y)		/*conjunction function*/
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





int Disj(int x, int y)		/*disjunction function*/
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