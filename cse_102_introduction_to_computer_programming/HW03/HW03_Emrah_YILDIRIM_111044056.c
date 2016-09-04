/*##########################################################################*/
/*HW03_111044056.c															*/
/*--------------------------------------------------------------------------*/
/*Emrah YILDIRIM tarafýnda 11.03.2014 tarihinde yazýlmýþtýr					*/
/*																			*/
/* PART 1 TANIM >>															*/
/* Taylor serisi yardýmýyla sinus degeri hesaplayan program					*/
/*																			*/
/* Girdiler kullanýcýný isteðine göre dosya ya da konsoldan okunabilir		*/
/* Girdiler:																*/
/* x : sinusun alýnacak deðer. (radyan alýnýp dereceye çevrilecek)			*/
/* n : taylor açýlýmýnýn terim sayýsý										*/
/* 																			*/
/* Çýktýlar:																*/
/* girilen acinin sinus degeri												*/
/*--------------------------------------------------------------------------*/
/* PART 2 TANIM >>															*/
/* Girilen degerlere gore agac cizme										*/
/* 																			*/
/* Girdiler:																*/
/* numberOfTriangle :ucgen sayisi(sifirdan kucuk olmayacak)					*/
/* truckHight : govde yuksekligi											*/
/* truckWidtg : govde genisligi												*/
/* 																			*/
/* Çýktýlar:																*/
/* agac sekli ve basilan karakter sayisi									*/
/*##########################################################################*/


/*##########################################################################*/
/*									Includes								*/
/*##########################################################################*/

#include<stdio.h>

#define PI 3.14

/*##########################################################################*/
/*							Function Prototypes								*/
/*##########################################################################*/

int Part1(void);
int Part2(void);

double CalcSinus(int, int); 						/*Sinus fonksiyonu*/
int TakeFromFile(FILE *srcInput);					/*dosyadan okuma*/
int Factorial(int);									/*faktoriyel hesabý*/
double AngleToRadian(int);							/*radyana cevirme*/
double PowRadianX(double, int);						/*x in kuvvetlerini alma*/
int PowOne(int);									/*-1 in kuvvetlerini alma*/

int DrawTree(int, int, int, char);					/*agac cizme*/
int DrawTriangleWithSpace(int, int, char);			/*3gen cizme*/
int DrawRectangleWithSpace(int, int, int, char); 	/*dortgen cizme*/
/*##########################################################################*/
/*								MAIN Function								*/
/*##########################################################################*/
int main(void)
{
	/*START_OF_MAIN*/

	
	/*END_OF_VARIABLES*/

	Part2();	
	Part1();

	
	system("pause");
	return 0;
	
	/*END_OF_MAIN*/
}

/*##########################################################################*/
/*								FUNCTIONS									*/
/*##########################################################################*/

/*PART 2*/


int Part2()
{
	int numberOfTriangles, truckHeight, truckWidth, 
		numberChar;
		
	char ch, trash; /*enter i es geçmek icin trash e atadik*/
	
	
	/*kullanicidan degerleri ve karakteri istiyoruz*/
	printf("\nPlease enter\n");
	printf("Number Of Triangles\n");
	scanf("%d", &numberOfTriangles);
	printf("Truck Height\n");
	scanf("%d", &truckHeight);
	printf("Truck Width\n");
	scanf("%d", &truckWidth);
	printf("Character\n\n");
	scanf("%c%c%c", &trash, &ch, &trash);
	
	
	/*3gen sayisi 0 dan kucukse ya da govde genisligi cift ise..*/
	/*..programý sonlandiriyoruz*/
	if (numberOfTriangles < 0 || truckWidth % 2 == 0)
		return -1;
	
	/*fonskiyonun donus degerini(basilan karakter sayisi)  degiskene atadik*/
	numberChar = DrawTree(numberOfTriangles, truckHeight, truckWidth, ch);
	
	printf("\nnumber char = %d\n", numberChar);

	
	return 0;
}

/*agac cizme fonksiyonu*/
int DrawTree(int numberOfTriangles, int truckHeight, int truckWidth, char ch)
{	

	int space, height, width, i, countChar=0;
	
	/*boslugu 3gen sayisi ile iliskili hale getirdik*/
	space = numberOfTriangles;
	height = 2;
	
	for (i=0; i < numberOfTriangles; i++)
	{	
		/*fonksiyonun cagirdik, donus degerini degiskene atadik*/
		countChar += DrawTriangleWithSpace(height, space, ch);
		
		height += 1; /*ucgenin buyumesi icin her seferinde height i artýrdýk*/
	}
	
	/*matematiksel iliskilendirmeler yapýldý*/
	space = (((numberOfTriangles * 2) + 1 ) - (truckWidth))/2;
	height = truckHeight;
	width = truckWidth;
	
	/*dikdortgen cizme fonksiyonu cagrilir*/
	DrawRectangleWithSpace(height, width, space, ch);
	
	/*return degeri olarak toplam basilan karakter sayisi donduruldu*/
	return countChar + truckHeight * truckWidth;
}

/*ucgen cizme fonskiyonu*/
int DrawTriangleWithSpace(int height, int space, char ch)
{
	int i, j;
	
	for (i=0; i < height; i++)
	{
		for (j=space*2; j > space; j--)
		{
			printf(" ");
		}
		space-=1;
		
		for (j=0; j<=2*i; j++)
		{
			printf("%c", ch);
		}
		printf("\n");
	}
	
	/*basilan karakter sayisi*/
	return height * height;
}


/*diksortgen cizme fonksiyonu*/
int DrawRectangleWithSpace(int height, int width, int space, char ch)
{
	int i, j;
	
	for(i=1; i <= height; i++)
	{
		for (j=1; j <= space; j++)
		{
			printf(" ");
		}
		for (j=1; j <= width; j++)
		{
				printf("%c", ch);
		}
		
		printf("\n");
	}
	
	/*basilan karakater sayisi*/
	return height * width;
}


/*###########################################################################*/
/*PART 1*/

int Part1(void)
{
	double	result;		/*x in sinus degeri*/
	int angleX, n;
	
	
	char srcSelect, trash; /*veri kaynaðý pointer i */
	
	FILE *srcInput; 	/*kaynak dosya*/
	FILE *outPtr;		/*cikti dosyasý*/
	
	
	/*kaynak dosyasýný aç*/
	srcInput = fopen("Angle.txt", "r");	
	outPtr = fopen("Sinus.txt", "w");
	

	printf("Enter your source selection\n");
	printf("Enter \"C\" or \"c\" for taking from console\n");
	printf("Enter \"F\" or \"f\" for takin from file\n");
	
	scanf("%c%c", &srcSelect, &trash); /*kaynak secimini oku*/
	
	/*kaynak seccimine gore davran*/		
	if (srcSelect == 'C' || srcSelect == 'c')
	{
		printf("Please enter x and term variable n \n");
		scanf("%d%d", &angleX, &n);

	}
	else if (srcSelect == 'F' || srcSelect == 'f')
	{
		angleX = TakeFromFile(srcInput); /*fonskiyonunun dondurdugu degeri ata*/
		n = TakeFromFile(srcInput);		/*donus degerini ata*/
		
	
	}
	else
	{	/*yanlýs secim yapýlmýssa programý kapat*/
		printf("Entered wrong selection. Program is shutting down..\n\n");
		return 0;
	}
	
	/*result a calcsinus un donus degerini ata*/
	result = CalcSinus(n, angleX);
	printf("The Sinus value of %d degree is %.4f\n", angleX,result);
	fprintf(outPtr,"%f", result);

	/*dosyalarý kapa*/
	fclose(srcInput);	
	fclose(outPtr);
	return 0;
}

/*sinus buma fonksiyonu*/
double CalcSinus (int n, int angleX)
{
	double radianX, result=0;
	int counter;
	
	/*dereceden radyana cevir radianX e ata*/
	radianX = AngleToRadian(angleX);

	/*istenen terim sayisina gore dongu ile islem yap*/
	for (counter=0; counter <= n; counter++)
	{	
		/*		(-1)^n * x^(2n+1) / (2n+1)!		*/
		/*her bir islem icin fonskiyonlarini cagir ve islemi yap*/
		result += PowOne(counter) * PowRadianX(radianX, counter) / Factorial(counter);

	}

	return result;
}

/*dereceden radyana cevirme*/
double AngleToRadian(int angleX)
{
	/*radyan = derece * PI / 180*/
	return angleX * PI / 180.0;	
}

/*-1 in terim sayýsýna gore uzerini alma*/
int PowOne(int counter)
{
	int result, i;
	
	result = 1;
	
	for (i= 1; i <= counter; i++)
	{	
		/*terim sayisi tekse - ciftse + olacak*/
		result = -1 * result;
	}
	
	return result;
}


/*radyan degerinin ustunu alma*/
double PowRadianX(double radianX, int counter)
{
	int i, realCounter;
	double powRad=1;
	/*x^(2n+1) olacagi icin counter iona esitliyoruz*/
	realCounter = 2*counter +1;
	
	for(i=1; i <= realCounter; i++ )
	{
		powRad = radianX * powRad;
	
	}

	return powRad;
}

/*faktoriyel hesaplama*/
int Factorial(int counter)
{
	int i, realCounter, fact=1;
	
	realCounter = 2*counter + 1;
	
	for (i=1; i <= realCounter; i++)
	{
		fact = i * fact;
	}

	return fact;
}

int TakeFromFile (FILE *srcInput)
{
	int data;

	/*dosyadan okudugumuz degeri donduruyoruz*/
	fscanf(srcInput,"%d", &data);
	
	return data;
}
