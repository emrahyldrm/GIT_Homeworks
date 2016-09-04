/*##########################################################################*
*HW08_111044056.c															*
*Emrah YILDIRIM tarafýndan 29.04.2014 tarihinde yazýldý						*
*																			*
*****************************************************************************
*																			*
* -------------------------------TANIM--------------------------------------*
* PART1>> dizideki  artan dizi sayýyý bulan fonksiyon ve driver kod			*
* PART2>> verilen sayýsý tersten ve duzden yazan fonksiyon ve driver kod	*
* PART3>> [f(x,y) = f(x-1, y) + 2*f(x, y-1) + x+ y ] yi bulan fonksiyon..	*
* 		  ve driver kodu													*
* PART4>> verilen txt dosyasindaki arraydeki 0 larla olusmus en uzun..		*
*		  yolu bulan fonskiyon ve driver kodu								*
* BONUS>> part3 teki fonksiyonu soncunu iterative olarak bulan fonskiyon	*
*																			*	
****************************************************************************
*-------------------------------DOSYALAR------------------------------------*
* INPUT >> Map.txt:  basllangictaki taslarin yerleri						*
*																			*
*****************************************************************************
*																			*
*###########################################################################*/


/*##########################################################################*/
/*						libraries and Constant Macros						*/
/*##########################################################################*/

#include<stdio.h>
#include<string.h>


#define MAX_ROW 	20
#define MAX_COLUMN 	20
#define MAX_Y		100
#define TRUE		1
#define FALSE   	0



/*##########################################################################*/
/*							Function Prototypes								*/
/*##########################################################################*/
/*artan altdizi sayisini bulan foksiyon*/
int getNumOfIncreasingSubSeq(int arr[], int size);

/*alinan sayinin tersini basan fonksiyon*/
int printNumberReversed(int number);
/*alinan sayiyi duzden basan fonskiyon*/
int printNumber(int number);

/*[f(x,y) = f(x-1, y) + 2*f(x, y-1) + x+ y ] yi bulan fonksiyon, recursive*/
int evalF(int x, int y);

/*findLongestPathRec in wrapper fonksiyonu*/
void findLongestPath(char map[][MAX_COLUMN], char route[][MAX_COLUMN], 
						int *routeLen, char longestRoute[][MAX_COLUMN], 
						int *longestRouteLen, int mapRowC,
						int mapColC);

/*dosyadan harita okumasi yapan fonksiyon*/						
void getData(char map[][MAX_COLUMN], int *mapRowC, int *mapColC);

/*verilen arrayi ekrana basan fonksiyon*/
void printTable(char map[][MAX_COLUMN], int mapRowC);


/*map teki en uzun yolu bulan fonksiyon*/
void findLongestPathRec(char map[][MAX_COLUMN], int mapRowC,
						int mapColC, char route[][MAX_COLUMN], 
						int *routeLen, char longestRoute[][MAX_COLUMN], 
						int *longestRouteLen, int yPos, int xPos);

/*verilen arrayi noktalarla dolduran fonksiyon*/						
void fillWithPoints(char map[][MAX_COLUMN], int mapRowC, int mapColC);

/*verilen 1. arrayi 2.ye koyalayan fonksiyon*/
void copyArrays(char route[][MAX_COLUMN], char longestRoute[][MAX_COLUMN], 
				int mapRowC);

/*[f(x,y) = f(x-1, y) + 2*f(x, y-1) + x+ y ] yi bulan fonksiyon, iterative*/
int getEvalFIteretive(int evalF[][MAX_Y], int x, int y);

/*##########################################################################*/
/*								MAIN Function								*/
/*##########################################################################*/

int main()
{
	/*START_OF_MAIN*/
	/*part1 variables*/
	int arr[]={1,2,3,4,5,1,1,1,1,1,1,1,1,2,1,0};
	int size = 16;
	int a;
	
	/*part2 variables*/
	int number = 1234560001;
	
	/*part3 variables*/
	int x=4, y=3;
	
	/*part4 varianbles*/
	char map[MAX_ROW][MAX_COLUMN], 
		 route[MAX_ROW][MAX_COLUMN],
		 longestRoute[MAX_ROW][MAX_COLUMN];
		 
	int mapRowC, mapColC,
		routeLen=0, longestRouteLen=-99;
	/*bonus part variables*/
	int evalFunction[100][100];
	int result,
		i, j;
		
	/*END_OF_VARIABLES*/
	
	
	/*PART1*/
	printf("\n<< PART1 >>\n");
	
	for(i=0; i < size; ++i)		/*array ekrana yazilir*/
		printf("%d ", arr[i]);
		
	printf("\nThe count of subsequences is : %d\n\n", getNumOfIncreasingSubSeq
																  (arr, size));
	printf("-------------------------------------------------------------\n\n");
	/**************************************************************************/
	
	
	/*PART2*/
	printf("<< PART2 >>\n");
	printf("Straigth number\t\t\t: ");
	printf("\nSum of each digit of the number : %d\n", printNumber(number));
	
	printf("\nReversed number\t\t\t: ");
	printf("\nSum of each digit of the number : %d\n", printNumberReversed(number));
	printf("\n");
	printf("-------------------------------------------------------------\n\n");
	/**************************************************************************/
	
	
	/*PART3*/
	printf("<< PART3 >>\n");
	printf("Result of F(%d, %d)\t\t: %d\n\n", x, y, evalF(x, y));
	printf("-------------------------------------------------------------\n\n");
	/**************************************************************************/
	
	
	/*PART4*/
	printf("<< PART4 >>\n");	
	printf("-------------------------------------------------------------\n");
	
	getData(map, &mapRowC, &mapColC);
	printTable(map, mapRowC);
	fillWithPoints(route, mapRowC, mapColC);
	fillWithPoints(longestRoute, mapRowC, mapColC);

	findLongestPath(map, route, &routeLen, longestRoute, &longestRouteLen, 
					mapRowC, mapColC);
	printf("\n");
	printTable(longestRoute, mapRowC);	
	printf("\nThe lenght of the longest path is : %d\n\n", longestRouteLen+1);
	printf("-------------------------------------------------------------\n\n");
	/**************************************************************************/
	
	
	/*BONUS*/
	printf("<< BONUS >>\n");
	
	result = getEvalFIteretive(evalFunction, x, y);
	
	/*result 0(array olusmamis) gelmezse array ekrana basilir*/
	if(result != 0)
	{
		for(i=0; i <= x; ++i )
		{	
			for(j=0; j <= y; ++j )
			printf("%2d ", evalFunction[i][j]);
			printf("\n");
		}
	}
	
	printf("\nResult of F(%d, %d)\t\t: %d\n\n", x, y, result);
	printf("-------------------------------------------------------------\n\n");
	/**************************************************************************/
	
	scanf("&d", &a);
	return 0;	
	/*END_OF_MAIN*/
}


/*##########################################################################*/
/*								FUNCTIONS									*/
/*##########################################################################*/


/********************************************************************
*					1. PARTIN FONKSIYONLARI							*
*********************************************************************/



 /*******************************************************************
 * dizideki artan altdizi sayisini bulan fonksiyon					*
 * bir array ve arrayin buyuklugunu alir							*
 * array 1 elemanli ise sonuc 1 0 ise 0 dir							*
 *******************************************************************/
int getNumOfIncreasingSubSeq(int arr[], int size)
{
	int ans=0;

	/*eger bos arrayse altdizi sayisi 0 dir*/
	if(size == 0)
		ans = FALSE;
	
	else
	{	/* array 1 elemanliysa ya da 2. eleman 1.den buyukse ans 1 artirilir
		 * fonskiyon tekrar cagrilir ve return degeri ans ile toplarak ans a atanir*/
		if(size == 1 || arr[1] < arr[0])
		{
			ans = TRUE;
			
			ans += getNumOfIncreasingSubSeq(&arr[1], size-1);			
		}
		
		/*eger 1. ve 2. eleman esitse ans artirilmaz ama fonksiyon tekrar cagrilir*/
		else if(arr[1] == arr[0]){
			ans += getNumOfIncreasingSubSeq(&arr[1], size-1);
		}	
		
		else 
			ans = getNumOfIncreasingSubSeq(&arr[1], size-1);		
	}
	
	return ans;
}


/********************************************************************
*					2. PARTIN FONKSIYONLARI							*
*********************************************************************/


 /*******************************************************************
 * integer bir sayiyi karakter karakter duzden yazar				*
 * bir tane integer sayi alir										*
 * sayinin basamak degerlerini toplamini return eder				*
 *******************************************************************/
int printNumber(int number)
{
	int endDigit, temp=0;

	/*son basamak bulunur*/
	endDigit = number % 10;
	
	/*sayi 1 basamak azaltilir*/
	number = (number - endDigit) / 10;
	
	/*eger bolme islemi sonrasi sayi 0 degilse fonksiyon cagrilir temp e atanir*/
	if(number != 0)
		temp = printNumber(number);
	
	/*ilk basamak yazilir*/
	printf("%d", endDigit);
	
	/*temp ile toplanarak toplam bulunur*/
	endDigit += temp;
	return endDigit;
}

 /*******************************************************************
 * integer bir sayiyi karakter karakter tersten yazar				*
 * bir tane integer sayi alir										*
 * sayinin basamak degerlerini toplamini return eder				*
 *******************************************************************/
int printNumberReversed(int number)
{
	int endDigit, temp=0;
	
	/*son basamak bulunur*/
	endDigit = number % 10;
	
	/*sayi 1 basamak azaltilir*/
	number = (number - endDigit) / 10;
	
	/*son basamak yazilir*/
	printf("%d", endDigit);
	
	/*eger bolme islemi sonrasi sayi 0 degilse fonksiyon cagrilir temp e atanir*/
	if(number != 0)
		temp = printNumberReversed(number);
	
	
	/*temp ile toplanarak toplam bulunur*/
	endDigit += temp;
	return endDigit;
}


/********************************************************************
*					3. PARTIN FONKSIYONLARI							*
********************************************************************/

 /*******************************************************************
 * [f(x,y) = f(x-1, y) + 2*f(x, y-1) + x+ y ] yi bulur				*
 * 2 tane integer alir >> x ve y									*
 * sonucu return eder												*
 *******************************************************************/
int evalF(int x, int y)
{
	int ans;
	
	/*eger x ve ya y 0 ve 0dan kucukse cevap 0 dir*/
	if(x <= 0 || y <= 0)
		ans = 0;
	
	/*degilse foknsiyon tekrar cagirilir ve ans e atanir*/
	else
	{
		ans = evalF(x-1, y) + (2 * evalF(x, y-1)) + (x + y);	
	}

	return ans;
}


/********************************************************************
*					4. PARTIN FONKSIYONLARI							*
*********************************************************************/

void findLongestPath(char map[][MAX_COLUMN], char route[][MAX_COLUMN], 
						int *routeLen, char longestRoute[][MAX_COLUMN], 
						int *longestRouteLen, int mapRowC,
						int mapColC)
{
	int yPos, xPos=0;	
	
	yPos = mapRowC-1;
	findLongestPathRec(map, mapRowC, mapColC, route, routeLen, longestRoute,
					   longestRouteLen, yPos, xPos);
}

 /*******************************************************************
 * Map.txt den string olarak okuma yapar..							*
 * string arraye yazar												*
 *******************************************************************/
void getData(char map[][MAX_COLUMN], int *mapRowC, int *mapColC)
{
	int i=0,
		lenght;
	size_t len;
	char *endPtr;
	FILE *mapFilePtr;



	mapFilePtr = fopen("Map.txt", "r");

	do
	{
		endPtr = fgets(map[i], MAX_ROW, mapFilePtr);

		if(endPtr != NULL)
		{
			len = strlen(map[i]);
			lenght= (int)len; 

			if(map[i][lenght-1] == '\n')
			{
				map[i][lenght-1] = '\0';
			}
			i++;
		}

	}while(endPtr != NULL);


	*mapRowC = i;
	*mapColC = (int)len;

	fclose(mapFilePtr);
}

 /*******************************************************************
 * aldigi arrayi ekrana basar										*
 * bir array ve arrayin buyuklugunu alir							*
 *******************************************************************/
void printTable(char map[][MAX_COLUMN], int mapRowC)
{	
	int i;
	
	for(i=0; i < mapRowC; ++i)
		printf("%s\n", map[i]);
}

 /*******************************************************************
 * aldigi arrayi noktalarla doldurur								*
 * bir array ve arrayin sutun satir sayisini alir					*
 *******************************************************************/
void fillWithPoints(char map[][MAX_COLUMN], int mapRowC, int mapColC)
{
	int i, j;
	
	for(i=0; i < mapRowC; ++i)
	{	
		for(j=0; j < mapColC; ++j)
		{
			map[i][j] = '.';
		}
		map[i][mapColC] = '\0';
	}
}


 /*******************************************************************
 * ilk string arrayi ikinci string arraye kopyalar					*
 * 2 array ve arraylerin satir sayisini alir						*
 *******************************************************************/
void copyArrays(char route[][MAX_COLUMN], char longestRoute[][MAX_COLUMN],
				int mapRowC)
{
	int i;
	
	for(i=0; i < mapRowC; ++i)
	{
		strcpy(longestRoute[i], route[i]);
	
	}

}


 /*******************************************************************
 * arraydeki(map) 0 larla olusmus en uzun yolu bulur				*
 * 3 array(map, route, longest) arraylerin satir sutun sayisini..	*
 * o anki yolun ve en uzun yolun uzunlugunu tutan 2 pointer..		*
 * o anki pozisyonlari alir											* 
 *******************************************************************/
void findLongestPathRec(char map[][MAX_COLUMN],  int mapRowC,
						int mapColC, char route[][MAX_COLUMN], 
						int *routeLen, char longestRoute[][MAX_COLUMN], 
						int *longestRouteLen, int yPos, int xPos)
{
		
		/*yukarý*/					   
		if(map[yPos-1][xPos] == '0' && route[yPos-1][xPos] != 'X')
		{
			if(map[yPos][xPos] == '0')
			{
				route[yPos][xPos] = 'X';
				*routeLen+=1;
			}
			findLongestPathRec(map, mapRowC, mapColC, route, routeLen,
							   longestRoute, longestRouteLen, yPos-1, xPos);
			
			if(*routeLen < *longestRouteLen)
			{
				route[yPos-1][xPos] = '.';
				if(*routeLen > 1)
					*routeLen -= 1;
			}

		}
		
		/*sag*/
		if(map[yPos][xPos+1] == '0' && route[yPos][xPos+1] != 'X')
		{
			if(map[yPos][xPos] == '0')
			{
				route[yPos][xPos] = 'X';
				*routeLen+=1;
			}
			findLongestPathRec(map, mapRowC, mapColC, route, routeLen, 
							   longestRoute, longestRouteLen, yPos, xPos+1);
							   
			if(*routeLen < *longestRouteLen)
			{
				route[yPos][xPos+1] = '.';
				if(*routeLen > 1)
					*routeLen -= 1;
			}
			

		}
		
		/*sol*/	
		if(map[yPos][xPos-1] == '0' && route[yPos][xPos-1] != 'X')
		{
			if(map[yPos][xPos] == '0')
			{
				route[yPos][xPos] = 'X';
				*routeLen+=1;
			}
			findLongestPathRec(map, mapRowC, mapColC, route, routeLen, 
							   longestRoute, longestRouteLen, yPos, xPos-1);		
						   
			if(*routeLen < *longestRouteLen)
			{
				route[yPos][xPos-1] = '.';
				if(*routeLen > 1)
					*routeLen -= 1;
			}
		}
		
		if(map[yPos][xPos] == '0')
			{
				route[yPos][xPos] = 'X';
				*routeLen+=1;
			}
				   
				   
		
		if(*routeLen > *longestRouteLen)
		{
			
			*longestRouteLen = *routeLen;
			copyArrays(route, longestRoute, mapRowC);
			*routeLen = 0;
			
		}



}


/********************************************************************
*					BONUS PARTIN FONKSIYONLARI						*
*********************************************************************/

 /*******************************************************************
 * ilk string arrayi ikinci string arraye kopyalar					*
 * 2 array ve arraylerin satir sayisini alir						*
 *******************************************************************/
int getEvalFIteretive(int evalF[][MAX_Y], int x, int y)
{
	
	int i=0, j=0;
	
	/*sayi 0 yada 0 dan buyukse islem yapilir, degilse cevap 0 olur*/
	if (x >= 0 && y >= 0)
	{
		/* x ve y ye kadar her deger icin sonuc bulunur
		 * her hangi 1 eleman 0 sa cevap 0 olur ve bu ilgili dizi indisine atanir
		 * degilse de daha once hesaplanmis indislerdeki degerlerle yeni deger 
		 * bulunur*/
		for(i=0; i <= x; ++i )
		{
			for(j=0; j <= y; ++j)
			{
				if(i <= 0 || j <= 0)
					evalF[i][j] = 0;
				else
					evalF[i][j] = evalF[i-1][j] + 2 * evalF[i][j-1] + i + j;
			}
		}
		
	}
	else
		evalF[x][y] = 0;
		
	
	/*son eleman return edilir*/
	return evalF[x][y];

}
