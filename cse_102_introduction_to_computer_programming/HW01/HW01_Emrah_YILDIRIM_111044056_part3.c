/*##############################################################*/
/*HW01_111044056_part3.c										*/
/*--------------------------------------------------------------*/
/*Coded by Emrah YILDIRIM on February 21, 2014					*/
/*																*/
/*Description													*/
/*																*/
/*Calculates unit price for the each items that bought			*/
/*Inputs:														*/
/*Item no, item code and total cost from input file 			*/
/*																*/
/*Output:														*/
/*Unit price for each items	(to console and output file)		*/
/*##############################################################*/

#include<stdio.h>
#define LIRA	100



int main()
{	
	/*START_OF_MAIN*/
	
	int	itemNo1, itemNo2,itemNo3,itemNo4,
		amountItem1, amountItem2, amountItem3, amountItem4,
		uPriceAsKurus1, uPriceAsKurus2, uPriceAsKurus3, uPriceAsKurus4,
		tl1, tl2, tl3, tl4,				/*unit prices without odd lot as tl*/
		kurus1, kurus2, kurus3, kurus4; /*odd lots as kurus*/
		
		
	double	totalCost1, totalCost2, totalCost3, totalCost4,
			uPrice1, uPrice2, uPrice3, uPrice4; 	/*unit prices*/
	
	FILE *buysPtr;
	FILE *unitPricesPtr;
	
	
	/*END_OF_VARIABLES*/

	/*Open input and output files*/
	buysPtr		  = fopen("Buys.txt", "r");
	unitPricesPtr = fopen("UnitPrices.txt", "w");
	
	/*Take the purchases information from input file*/
	fscanf(buysPtr, "%d", &itemNo1);
	fscanf(buysPtr, "%d", &amountItem1);
	fscanf(buysPtr, "%lf", &totalCost1);
	
	fscanf(buysPtr, "%d", &itemNo2);
	fscanf(buysPtr, "%d", &amountItem2);
	fscanf(buysPtr, "%lf", &totalCost2);
	
	fscanf(buysPtr, "%d", &itemNo3);
	fscanf(buysPtr, "%d", &amountItem3);
	fscanf(buysPtr, "%lf", &totalCost3);
	
	fscanf(buysPtr, "%d", &itemNo4);
	fscanf(buysPtr, "%d", &amountItem4);
	fscanf(buysPtr, "%lf", &totalCost4);



	/*Calculate each prices(TL Format) for each item*/
	uPrice1 = totalCost1 / amountItem1;
	uPrice2 = (totalCost2 - totalCost1) / amountItem2;
	uPrice3 = (totalCost3 - totalCost2) / amountItem3;
	uPrice4 = (totalCost4 - totalCost3) / amountItem4;

	
	/*Show the each prices as KURUS*/
	uPriceAsKurus1 = (int)(uPrice1 * LIRA);
	uPriceAsKurus2 = (int)(uPrice2 * LIRA);
	uPriceAsKurus3 = (int)(uPrice3 * LIRA);
	uPriceAsKurus4 = (int)(uPrice4 * LIRA);
	
	/*Seperate the costs Tl and KURUS*/
	tl1 = (uPriceAsKurus1 - (uPriceAsKurus1 % 100)) / 100;
	tl2 = (uPriceAsKurus2 - (uPriceAsKurus2 % 100)) / 100;
	tl3 = (uPriceAsKurus3 - (uPriceAsKurus3 % 100)) / 100;
	tl4 = (uPriceAsKurus4 - (uPriceAsKurus4 % 100)) / 100;	
	
	kurus1 = uPriceAsKurus1 % 100;
	kurus2 = uPriceAsKurus2 % 100;
	kurus3 = uPriceAsKurus3 % 100;
	kurus4 = uPriceAsKurus4 % 100;
	
	/*Print the unit prices to console and output files */
	printf("The unit price of the item (%d) is %d TL and %d kurus\n", 
											   itemNo1, tl1, kurus1);	
	printf("The unit price of the item  (%d) is %d TL and %d kurus\n",
												itemNo2, tl2, kurus2);
	printf("The unit price of the item (%d) is %d TL and %d kurus\n",
											   itemNo3, tl3, kurus3);
	printf("The unit price of the item (%d) is %d TL and %d kurus\n", 
											   itemNo4, tl4, kurus4);
	
	fprintf(unitPricesPtr, "%d   %.2f\n", itemNo1, uPrice1);
	fprintf(unitPricesPtr, "%d    %.2f\n",itemNo2, uPrice2);
	fprintf(unitPricesPtr, "%d   %.2f\n", itemNo3, uPrice3);
	fprintf(unitPricesPtr, "%d   %.2f\n", itemNo4, uPrice4);
	
	
	/*Close the input and output files*/
	fclose(buysPtr);
	fclose(unitPricesPtr);

	return 0;
		
	/*END_OF_MAIN*/
}