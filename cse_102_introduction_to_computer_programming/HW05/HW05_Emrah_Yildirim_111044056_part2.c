/*##########################################################################*/
/*HW05_111044056_part2.c													*/
/*--------------------------------------------------------------------------*/
/*Emrah YILDIRIM tarafýndan 26.03.2014 tarihinde yazýldý					*/
/*																			*/
/* TANIM>>																	*/
/* Ýstenilen karakterle, 2li ve 4lu ucgen cizme ve ve tekrar ettirme		*/
/*																			*/
/*drawReccurOf2Triangles fonksiyonu icin >>									*/
/* GIRDILER																	*/
/* m : her bir ucgenin yuksekligi											*/
/* n : her ucgen arasindaki bosluk sayisi									*/
/* k : 2li desenin tekrar etme sayisi										*/
/* ch: cizimin yapilacagi karakter											*/
/* e : cizim baslamadan basta birakilacak olan bosluk sayisi				*/
/* 																			*/
/* CIKTI>>																	*/
/* numChar : ekrana basilan karakter sayisi									*/
/*																			*/
/*--------------------------------------------------------------------------*/
/*																			*/
/*drawReccurOf4Triangles fonksiyonu icin >>									*/
/* GIRDILER																	*/
/* rH : dusey eksende yapilacak olan tekrar sayisi							*/
/* vH : yatay eksende yapilacak olan tekrar sayisi							*/
/* 																			*/
/* CIKTI>>																	*/
/* numChar : ekrana basilan karakter sayisi									*/
/*																			*/
/*##########################################################################*/

/*##########################################################################*/
/*									Includes								*/
/*##########################################################################*/
#include<stdio.h>


/*##########################################################################*/
/*							Function Prototypes								*/
/*##########################################################################*/

int drawReccurOf2Triangles(int, int, int, char, int);
int drawReccurOf4Triangles(int, int);


/*##########################################################################*/
/*								MAIN Function								*/
/*##########################################################################*/
int main()
{
	/*START_OF_MAIN*/

	int rH, rV,		/*2. sekil icin yatayda ve dikeyde tekrar parametreleri*/
		m, n, k, e,	/*1. sekil icin cizim paramatreleri*/
		numCh;		/*basilan karakter sayisi*/
	
	char ch;		/*basilacak karakter*/

	/*END_OF_VARIABLES*/
	
	/*verilen direktiflerce, kullanicinin degerler girmesi beklenir*/
	printf("ENTER THE VALUES FOR SAMPLE 1..\n");
	printf("Do not enter negative numbers !!\n");
	
	/*negatif degerler girilmesi durumunda uyarilip, tekrar deger alinir*/
	do{
		printf("Height of pattern..\n>>");
		scanf("%d", &m);
		if(m < 0)
			printf("Negative !! Enter again.\n");
	}while(m < 0);
	
	
	do{
		printf("Number of empty columns of between each triangle..\n>>");
		scanf("%d", &n);
		if(n < 0)
			printf("Negative !! Enter again.\n");
	}while(n < 0);	
	
	do{
		printf("Number of recurrence\n>>");
		scanf("%d", &k);
		if(k < 0)
			printf("Negative !! Enter again.\n");
	}while(k < 0);
		
	printf("The charachter..\n>>");
	scanf(" %c", &ch);
				
	
	do{	
		printf("Number of empty colums before start..\n>>");
		scanf("%d", &e);
		if(e < 0)
			printf("Negative !! Enter again.\n");
	}while(e < 0);
	
	/*alinan parametrelere gore 2li ucgen cizme fonksiyonu cagrilir*/
	numCh = drawReccurOf2Triangles(m, n, k, ch, e);
	
	/*basilan karakter sayisi yazilir*/
	printf("\nThe number of printed charachter for this shape is %d\n", numCh);
	
	/*verilen direktiflerce kullanicinin degerler girmesi beklenir*/
	printf("\nENTER THE VALUES FOR SAMPLE 2..\n");
	printf("Do not enter negative numbers !!\n");
	
	do{
		printf("Horizontal recurrence of the pattern\n>>");
		scanf("%d", &rH);
		if(rH < 0)
			printf("Negative !! Enter again.\n");
	}while(rH < 0);

	do{
		printf("Vertical recurrence of the pattern\n>>");
		scanf("%d", &rV);
		if(rV < 0)
			printf("Negative !! Enter again.\n");
	}while(rV < 0);
	
		
	/*alinan paramatreler gonderilerek 4lu ucgen cizme fonksiyonu cagrilir*/
	numCh = drawReccurOf4Triangles(rH, rV);
	
	printf("\nThe number of printed charachter for this shape is %d", numCh);
	printf("\n\n");
	

	return 0;
	/*END_OF_MAIN*/
}


/*##########################################################################*/
/*								FUNCTIONS									*/
/*##########################################################################*/

/*4lu ucgen cizdirme fonksiyonu*/
int drawReccurOf4Triangles(int rH, int rV)
{
	int i,
		numChar=0;

	for (i=0; i < rV; i++)
	{
		numChar += drawReccurOf2Triangles(3, 2, rH, 'x', 0);
		
		numChar += drawReccurOf2Triangles(3, 2, rH, 'x', 3);
	}	
	
	

	return numChar;	
}


/*2li ucgen cizdirme fonksiyonu*/
int drawReccurOf2Triangles(int m, int n, int k, char c, int e)
{
	int i, j, p,		/*donguler icin sayaclar*/
		inverse=1, 		/*duz ucgeni cizdirmek icin baslangic degeri*/
		straight=2*m-1,	/*ters ucgeni cizdirmek icin baslangic degeri*/
		space=0,		/*ilk ucgenlerin basindaki boslugun baslangic degeri*/
		numChar=0;		/*cizilen karakter sayisi*/
	
	
	/*negatif deger girilmisse -1 dondurulur, fonksiyon kapanir*/
	if ( m < 0 || n < 0 || k < 0 || e < 0 )
		return -1;
		
	
	
	for(j=0; j < m; j++)			/*ucgen yuksekligini ayarlayan dongu*/
	{
		for(i=0; i < e; i++)		/*baslangictaki boslugu ayarlayan dongu*/
		{
			printf(" ");
		}
	
		for(i=0; i < space; i++)	/*ucgen	basindaki boslugu ayarlayan dongu*/
		{
			printf(" ");
		}
		
		for(p=0; p < k; p++)		/*desenin tekrarýný ayarlayan dongu*/
		{
			
			/*ters ucgen satirlarini cizen dongu*/
			for(i=0; i < straight; i++)	
			{
				printf("%c", c);
				numChar += 1;
			}
			
			/*her ucgen satiri arasindaki boslugu ayarlayan dongu*/
			for(i=0; i < n; i++)
			{
				printf(" ");
			}
			
			/*duz ucgen satirlarini cizen dongu*/
			for(i=0; i < inverse; i++)
			{
				printf("%c", c);
				numChar += 1;
			}
			
			/*her ucgen satiri arasindaki boslugu ayarlayan dongu*/
			for(i=0; i < n; i++)
			{
				printf(" ");
			}
			
		}
		
		printf("\n");	/*her bir satir bitince alta gecilir*/
		
		/*sekli olusturmak icin degerlerde artirma ve azaltma yapilir*/
		space += 1;
		straight -=2;
		inverse += 2;
	}
	
	return numChar; /*ekrana basilmis karakter sayisi return degeri olur*/
}


