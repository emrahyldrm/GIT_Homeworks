/*##########################################################################*/
/*HW02_111044056_part3.c													*/
/*--------------------------------------------------------------------------*/
/*Coded by Emrah YILDIRIM on February 30, 2014								*/
/*																			*/
/*Description																*/
/*																			*/
/*Boolean Algebra Calculator with Console Interface							*/
/*Inputs:																	*/
/*x, y and z variables that takes from user via console						*/
/*User will not give value only for Test Mode								*/
/*																			*/
/*Output:																	*/
/*Result of the processes on console										*/
/*																			*/
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



void CalcFinish(void);		/*writing finishing info*/
int  TakeValue(void);		/*taking value for anything*/
void WriteMainMenu(void);
void WriteSubMenuX(void);
void WriteSubMenuY(void);
void TestMonotone(void);	/*test function with monotone laws*/
int FirstRuleTst(int, int, int, int);
int SecondRuleTst(int, int, int, int);
int ThirdRuleTst(int, int, int);
int ForthRuleTst(int, int, int);
int FifthRuleTst(int, int, int, int);
int SixthRuleTst(int, int);
int SeventhRuleTst(int, int);
int EightRuleTst(int, int);
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
	
	int selection,
		x, y;
	
	/*END_OF_VARIABLES*/
	
	
	/*if enter a wrong selection number(1 2 ... 7), user will return start*/
	do
	{
		WriteMainMenu();
		selection = TakeValue();
		
		if (selection < 1 || selection > 7)
			printf("\a\a");
	}
	while (selection < 1 || selection > 7);

	/*when selection is different from 7, the program is not close itself*/
	while (selection != 7)
	{
		/*the program will continue according to the selection*/
		switch (selection)
		{
			case 1: /*Conjunction Mode*/
				{
					printf("Your Selection is Conjunction Mode\n\n");
					WriteSubMenuX();
					x = TakeValue();	
					WriteSubMenuY();
					y = TakeValue();
					printf("\nThe Result of Conjunction ");
					/*calling the conjuction calculating function*/
					printf("\" %d and %d \" = %d\n", x, y, Conj(x, y) );
					CalcFinish();
				}
					break;
					
			case 2: /*Disjunction Mode*/
				{
					printf("Your Selection is Disjunction Mode\n\n");
					WriteSubMenuX();
					x = TakeValue();
					WriteSubMenuY();
					y = TakeValue();
					printf("\nThe Result of Disjunction ");
					/*calling the disjuction calculating function*/
					printf("\" %d and %d \" = %d\n\n", x, y, Disj(x, y) );
					CalcFinish();
				}
					break;
			
			case 3: /*Negation Mode*/
				{
					printf("Your Selection is Negation Mode\n\n");
					WriteSubMenuX();
					x = TakeValue();
					printf("\nThe Result of Negation ");
					/*calling the negation calculating function*/
					printf("\" %d \" = %d\n\n", x, Not(x) );
					CalcFinish();
				}	
					break;
				
				
			case 4: /*Material Implication Mode*/
				{
					printf("Your Selection is Material Implication Mode\n\n");
					WriteSubMenuX();
					x = TakeValue();
					WriteSubMenuY();
					y = TakeValue();
					/*calling the material implication calculating function*/
					printf("\nThe Result of Material Implication ");
					printf("\" %d and %d \" = %d\n\n", x, y, Mate(x, y) );
					CalcFinish();
				}
					break;
			
			case 5: /*Exclusive Or Mode*/
				{
					printf("Your Selection is Exclusive Or Mode\n\n");
					WriteSubMenuX();
					x = TakeValue();
					WriteSubMenuY();
					y = TakeValue();
					printf("\nThe Result of Exclusive Or ");
					printf("\" %d and %d \" = %d\n\n", x, y, Excl(x, y) );
					CalcFinish();
				}
					break;
			
			case 6: /*Calculator Test Mode*/
				{
					
					printf("\nThe Result of Test the Calculator");
					printf("with Monotone Laws\n\n");
					printf("Calculate for each possibility\n");
					TestMonotone();
					CalcFinish();
					break;
				}
			case 7: /*EXIT*/
				{	
					return 0;
				}	
			default:
					break;				
		}	
	
	/*after the calculating, the program return main menu until user enter "7"*/
	/*if enter a wrong selection number(1 2 ... 7), user will return start*/
			do
			{				
				WriteMainMenu();
				selection = TakeValue();
				if (selection < 1 || selection > 7)
				printf("\a\a");
			}
			while (selection < 1 || selection > 7);
	
	}
	
	/*system("pause");*/
	return 0;
	
	/*END_OF_MAIN*/
}


/*##########################################################################*/
/*								FUNCTIONS									*/
/*##########################################################################*/

/*writing description and selections for calculator*/
void WriteMainMenu (void)
{
	printf("Please Select Calculator Mode\n\n");
	printf("Press \"1\" and \"Enter\" for Conjunction Mode\n");
	printf("Press \"2\" and \"Enter\" for Disjunction Mode\n");
	printf("Press \"3\" and \"Enter\" for Negation Mode\n");
	printf("Press \"4\" and \"Enter\" for Material Implication Mode\n");
	printf("Press \"5\" and \"Enter\" for Exclusive Or Mode\n");
	printf("Press \"6\" and \"Enter\" for Calculator Test Mode with Monotone Laws Mode\n");
	printf("Press \"7\" and \"Enter\" for EXIT\n");
	printf("\n>>");
}

/*writing description for taking x */
void WriteSubMenuX (void)
{
	printf("Enter a integer \"X\"");
	printf("\n>> ");
}

/*writing description for taking y */
void WriteSubMenuY (void)
{
	printf("Enter a integer \"Y\"");
	printf("\n>> ");
}

/*writing finished message and draw line*/
void CalcFinish(void)
{
	printf("The calculating is finished..\n\n");
	printf("-----------------------------------------\n\n");
}
/*taking value from user via console for any process*/
int TakeValue (void)
{	
	int variable;

	scanf("%d", &variable);
	printf("\n");
	
	return variable;
}

/*--------------------------------------------------------------------------*/

/*associativity of disjunction rule*/
int FirstRuleTst(int x, int y, int z, int count)
{
	
	if ( Disj(x, Disj(y, z)) == Disj(Disj(x, y), z) )
	{
		printf("TRUE for x=%d, y=%d, z=%d \n", x, y, z);
		count = count + 1;
	}
	else
		printf("FALSE for x=%d, y=%d, z=%d \n", x, y, z);
	
	return count;
}

/*associativity of conjunction rule*/
int SecondRuleTst(int x, int y, int z, int count)
{
	
	if ( Conj(x, Conj(y, z)) == Conj(Conj(x, y), z) )
	{
		printf("TRUE for x=%d, y=%d, z=%d \n", x, y, z);
		count = count + 1;
	}
	else
		printf("FALSE for x=%d, y=%d, z=%d \n", x, y, z);
	
	return count;
}

/*commutativity of disjunction rule*/
int ThirdRuleTst(int x, int y, int count)
{
	
	if ( Disj(x, y) == Disj(y, x) )
	{
		printf("TRUE for x=%d, y=%d \n", x, y);
		count = count + 1;
	}
	else
		printf("FALSE for x=%d, y=%d \n", x, y);
	
	return count;
}

/*commutativity of conjunction rule*/
int ForthRuleTst(int x, int y, int count)
{
	
	if ( Conj(x, y) == Conj(y, x) )
	{
		printf("TRUE for x=%d, y=%d \n", x, y);
		count = count + 1;
	}
		
	else
		printf("FALSE for x=%d, y=%d \n", x, y);
		
	return count;
}

/*distribuvity of disjunction and over conjunction*/
int FifthRuleTst(int x, int y, int z, int count)
{

	if (Conj(x, Disj(y, z)) == Disj( Conj(x, y), Conj(x, z) ))
	{
		printf("TRUE for x=%d, y=%d, z=%d \n", x, y, z);
		count = count + 1;
	}
	
	else
		printf("FALSE for x=%d, y=%d, z=%d \n", x, y, z);
		
	return count;
}

/*identity for disjunction*/
int SixthRuleTst(int x, int count)
{
	
	if (Disj(x, 0) == x)
	{
		printf("TRUE for x=%d \n", x);
		count = count + 1;
	}
	else
		printf("FALSE for x=%d \n", x);
		
	return count;
}

/*identity for conjuntion*/
int SeventhRuleTst(int x, int count)
{
		
	if (Conj(x, 1) == x)
	{
		printf("TRUE for x=%d \n", x);
		count = count + 1;
	}
	else
		printf("FALSE for x=%d \n", x);
	
	return count;
}

/*annihilator for conjunction*/
int EightRuleTst(int x, int count)
{

	if (Conj(x, 0) == 0)
	{
		printf("TRUE for x=%d \n", x);
		count = count + 1;
	}
	else
		printf("FALSE for x=%d \n", x);
	
	return count;
}

/*--------------------------------------------------------------------------*/

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

/*--------------------------------------------------------------------------*/

void TestMonotone(void)
{
	int count = 0,	/*variable for count correct results for each function*/
		x, y, z;	/*variable for each probabilities*/
	
	
	/*controlling 1st rule*/
	printf("1ST RULE;\n");
	x=1; y= 1; z=1;
	count = FirstRuleTst(x, y, z, count);
	
	x=1; y= 1; z=0;
	count = FirstRuleTst(x, y, z, count);
	
	x=1; y= 0; z=0;
	count = FirstRuleTst(x, y, z, count);
	
	x=1; y= 0; z=1;
	count = FirstRuleTst(x, y, z, count);
	
	x=0; y= 0; z=1;
	count = FirstRuleTst(x, y, z, count);
	
	x=0; y= 1; z=0;
	count = FirstRuleTst(x, y, z, count);
	
	x=0; y= 1; z=1;
	count = FirstRuleTst(x, y, z, count);
	
	x=0; y= 0; z=0;
	count = FirstRuleTst(x, y, z, count);
	
	/* correctness controlling for each probabilities */
	if  (count == 8)
		printf(">> THE SYSTEM VERIFIES 1ST RULE\n\n");
	else
		printf(">> THE SYSTEM DOES NOT VERIFIES 1ST RULE\n\n");
	count=0;		/*reset the counter for use next test*/
	
	
	/*controlling 2nd rule*/
	printf("2TH RULE;\n");
	x=1; y= 1; z=1;
	count = SecondRuleTst(x, y, z, count);
	
	x=1; y= 1; z=0;
	count = SecondRuleTst(x, y, z, count);
	
	x=1; y= 0; z=0;
	count = SecondRuleTst(x, y, z, count);
	
	x=1; y= 0; z=1;
	count = SecondRuleTst(x, y, z, count);
	
	x=0; y= 0; z=1;
	count = SecondRuleTst(x, y, z, count);
	
	x=0; y= 1; z=0;
	count = SecondRuleTst(x, y, z, count);
	
	x=0; y= 1; z=1;
	count = SecondRuleTst(x, y, z, count);
	
	x=0; y= 0; z=0;
	count = SecondRuleTst(x, y, z, count);
	
	/* correctness controlling for each probabilities */
	if  (count == 8)
		printf(">> THE SYSTEM VERIFIES 2ND RULE\n\n");
	else
		printf(">> THE SYSTEM DOES NOT VERIFIES 2ND RULE\n\n");
	
	count=0;		/*reset the counter for use next test*/		
	
	printf("3RD RULE;\n");
	x=1; y= 1;
	count = ThirdRuleTst(x, y, count);
	
	x=1; y= 0;
	count = ThirdRuleTst(x, y, count);
	
	x=0; y= 1;
	count = ThirdRuleTst(x, y, count);
	
	x=0; y= 0;
	count = ThirdRuleTst(x, y, count);
	
	/* correctness controlling for each probabilities */
	if  (count == 4)
		printf(">> THE SYSTEM VERIFIES 3RD RULE\n\n");
	else
		printf(">> THE SYSTEM DOES NOT VERIFIES 3RD RULE\n\n");
	
	count=0;		/*reset the counter for use next test*/
	
	printf("4TH RULE;\n");
	x=1; y= 1;
	count = ForthRuleTst(x, y, count);
	
	x=1; y= 0;
	count = ForthRuleTst(x, y, count);
	
	x=0; y= 1;
	count = ForthRuleTst(x, y, count);
	
	x=0; y= 0;
	count = ForthRuleTst(x, y, count);
	
	/* correctness controlling for each probabilities */
	if  (count == 4)
		printf(">> THE SYSTEM VERIFIES 4TH RULE\n\n");
	else
		printf(">> THE SYSTEM DOES NOT VERIFIES 4TH RULE\n\n");
	
	count=0;		/*reset the counter for use next test*/
		
	printf("5TH RULE;\n");
	x=1; y=1; z=1;
	count = FifthRuleTst(x, y, z, count);
		
	x=1; y= 1; z=0;
	count = FifthRuleTst(x, y, z, count);
	
	x=1; y= 0; z=0;
	count = FifthRuleTst(x, y, z, count);
	
	x=1; y= 0; z=1;
	count = FifthRuleTst(x, y, z, count);
	
	x=0; y= 0; z=1;
	count = FifthRuleTst(x, y, z, count);
	
	x=0; y= 1; z=0;
	count = FifthRuleTst(x, y, z, count);
	
	x=0; y= 1; z=1;
	count = FifthRuleTst(x, y, z, count);
	
	x=0; y= 0; z=0;
	count = FifthRuleTst(x, y, z, count);
	
	/* correctness controlling for each probabilities */
	if  (count == 8)
		printf(">> THE SYSTEM VERIFIES 5TH RULE\n\n");
	else
		printf(">> THE SYSTEM DOES NOT VERIFIES 5TH RULE\n\n");
	
	count=0;		/*reset the counter for use next test*/


	printf("6TH RULE;\n");
	x=1;
	count = SixthRuleTst(x, count);
	
	x=0;
	count = SixthRuleTst(x, count);
	
	/* correctness controlling for each probabilities */
	if  (count == 2)
		printf(">> THE SYSTEM VERIFIES 6TH RULE\n\n");
	else
		printf(">> THE SYSTEM DOES NOT VERIFIES 6TH RULE\n\n");
		
	count = 0;		/*reset the counter for use next test*/
	
	
	printf("7TH RULE;\n");
	x=1;
	count = SeventhRuleTst(x, count);
	
	x=0;
	count = SeventhRuleTst(x, count);
	
	/* correctness controlling for each probabilities */
	if  (count == 2)
		printf(">> THE SYSTEM VERIFIES 7TH RULE\n\n");
	else
		printf(">> THE SYSTEM DOES NOT VERIFIES 7TH RULE\n\n");
		
	count = 0;		/*reset the counter for use next test*/
	
	
	printf("8TH RULE;\n");
	x=1;
	count = EightRuleTst(x, count);
	x=0;
	count = EightRuleTst(x, count);
	
	/* correctness controlling for each probabilities */
	if  (count == 2)
		printf(">> THE SYSTEM VERIFIES 8TH RULE\n\n");
	else
	{
		printf(">> THE SYSTEM DOES NOT VERIFIES 8TH RULE\n\n");
	}
}