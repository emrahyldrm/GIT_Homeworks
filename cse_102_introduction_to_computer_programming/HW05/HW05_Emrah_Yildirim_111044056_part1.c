/*##########################################################################*
*HW05_111044056_part1.c														*
*---------------------------------------------------------------------------*
*Emrah YILDIRIM tarafýndan 26.03.2014 tarihinde yazýldý						*
*																			*
* TANIM>>																	*
* Yatirim hesabi takip ve islem yapma programi								*
* kullanici 3 adet yatirim elemani ile alim satim yapabilir					*
*																			*
* YAPILABILECEK ISLEMLER													*
* Transaction: ayni anda iki urun arasinda kurlarina gore takas yapma		*
* Buy : hsaptaki lira miktarina gore baska bir eleman satin alma			*
* Sell: hesaptaki eleman mþktarlarina gore satis yapip tl olarak odeme alma	*
* Input: hesaptaki her hangi bir elemana bakiye ekleme(para yatýrma)		*
* Output: hesaptaki her hangi bir elemani eksiltme(pra cekme)				*
* Report To File: o anki hesap ozetini dosyaya yazma						*
* Report To Console: o anki hesap ozetini ekrana yazma						*
*																			*
* GIRDILER:																	*
* Kur degerleri, baslangic hesap bakiyeleri									*
*																			*
* CIKTILAR																	*
* hesap hareketleri, alim satimlar											*

*###########################################################################*/

#include<stdio.h>

#define DIFFERENCE 32 /* buyuk harf ve kucuk harf arasindaki ascii
					   * karsiligi farký A ve a arasindaki 97-65 gibi.
					   */

/*menu de kullanilan kodlar*/
typedef enum
{
	Transact='T', Buying='B', Selling='S', Inp='I', Outp='O',
	Report2File='F', Report2Cnsle='P', EXIT='E'
} 	operations_t;

typedef enum
{
	TL='L', Gold='G', Dolar='D', Fund ='F'
}	elements_t;


/*##########################################################################*/
/*							Function Prototypes								*/
/*##########################################################################*/

/*ana menu*/
void menu(void);
/*filedan kur degeri okuma fonksiyonu*/
void getPrices(FILE *, double *, double *, double *);
/*dosyadan baslangic eleman miktarlarini okuma fonksiyonu*/
void getInitials(FILE *, int *,int *, int *, int *);
/*o anki degerleri dosyaya yazma fonksiyonu*/
void saveReport(FILE *, int , int, int , int);
/*satilan elemana karsilik baska eleman alma fonksiyonu*/
int  transaction(int *, int *I, int *, double);
/*transaction fonksiyonuna yardýmcý fonksiyon(secenek belirler)*/
void transSelect(int *, int *, int *, int *, int *, int *, double, double, double);
/*o anki degerleri ekrana basma fonksiyonu*/
void report2Console(int , int , int , int);
/*her hangi bir elemandan eksiltme fonksiyonu*/
void output(int *, int *, int *, int *);
/*herhangi bir elemandan artýrma fonksiyonu*/
void input(int *,int *, int *, int *);
/*eleman alimi yapma fonksiyonu*/
void buy(int *, int *, int *, int *, double, double, double);
/*eleman satisi yapma fonksiyonu*/
void sell(int *, int *, int *, int *, double, double, double);

/*##########################################################################*/
/*								MAIN Function								*/
/*##########################################################################*/

int main()
{
	/*START_OF_MAIN*/
	
	int liraA, dolarA, goldA, fundA;	/*her elemanin miktarý*/
	int amoOSI, amoOBI, amount;			/*transaction icin parametreler*/
	double dolarP, goldP, fundP;		/*elemanlarin kur degerleri*/
	char selection;						/*secim degiskeni*/
	
	FILE *priceFile, *initFile, 
		 *reportFile;					/*kur, baslangic ve rapor dosyalari*/
		 
	/*END_OF_VARIABLES*/
	
	priceFile = fopen("Rates.txt", "r"); 		/*kur dosyasi atamasi*/
	initFile = fopen("Initials.txt", "r");		/*baslangic dosyasi atamasi*/
	reportFile = fopen("Portfolio.txt", "w");	/*rapor dosyasi atamasi*/
	

	
	/*baslangic degerleri "Initials.txt" dosyasindan alinir*/
	getInitials(initFile, &liraA, &dolarA, &goldA, &fundA);
	
	
	
	do{
	
	/*elemenlarin tl bazinda kuru "Rates.txt" den alinir alinir*/
	getPrices(priceFile, &dolarP, &goldP, &fundP);
	
	/*ana menu ekrana basilir*/
	menu();
	
	/*daha sonra kullanicini secim yapmasi beklenir*/
	scanf(" %c", &selection);
	
	/*mevcut secimlerden birini yapana kadar secim yapmasi beklenir*/
	while(selection != 'T' && selection != 'B' && selection != 'S' &&
		  selection != 'I' && selection != 'O' &&	selection != 'F' &&
		  selection != 'P' && selection != 'E' && selection != 't' &&
		  selection != 'b' && selection != 's' && selection != 'i' &&
		  selection != 'o' && selection != 'f' && selection != 'p' && 
		  selection != 'e')
	{
		printf("YOU ENTERED WRONG SELECTION !!! \n");
		printf("Try Again..\n>>");
		scanf(" %c", &selection);
	}

	/*yapilan secime gore operasyonlar gerceklersitirilir*/
	switch(selection)
	{
		case Transact 	  :
		case Transact +
			 DIFFERENCE   :	
							/* transection fonksiyonunun kullanildigi yardimci
							 * deger alma fonksiyonu cagrilir*/
							transSelect(&amoOSI, &amoOBI, &amount, &dolarA,
										&goldA, &fundA, dolarP, goldP, fundP);
							/*amount -1 olmus islem yapilmamis*/
							if (amount == -1)
								printf("\nYour operation was no performed\n");
							break;
		
		/*satin alma islemine gecilir*/
		case Buying		  :
		case Buying +
			 DIFFERENCE   : 
							/*satin alma fonksiyonu cagrilir*/
							buy(&liraA, &dolarA, &goldA, &fundA, dolarP, goldP,
								fundP);
			 				break;
							
		case Selling	  :
		case Selling +
			 DIFFERENCE	  : 
							/*satis yapma fonksiyonu cagrilir*/
							sell(&liraA, &dolarA, &goldA, &fundA, dolarP, goldP,
								 fundP);
							break;
							
		case Inp		  :
		case Inp +
			 DIFFERENCE   : 
							/*elemanlarda artirim yapma fonksiyonu cagrilir*/
							input(&liraA, &dolarA, &goldA, &fundA);
							break;
		
		case Outp 	  :
		case Outp +
			 DIFFERENCE	  :	
							/*elemanlarda azaltma yapma fonksiyonu cagrilir*/
							output(&liraA, &dolarA, &goldA, &fundA);
							break;
							
		
		case Report2File  :
		case Report2File +
			 DIFFERENCE	  : 
							/*dosyaya raporlama fonksiyonu cagrilir*/
							saveReport(reportFile,liraA, dolarA, goldA, fundA);
							printf("All amounts printf to the file. \n\n");
							break;
							
		
		case Report2Cnsle :
		case Report2Cnsle +
			 DIFFERENCE	  :	
							/*degerleri konsola yazan fonksiyon cagrilir*/
							report2Console(liraA, dolarA, goldA, fundA);
							break;
		
		case EXIT		  :
		case EXIT +
			 DIFFERENCE   : 
							/*program kapatilir*/
							printf("Program is shutting down..\n");
							break;
							
		default			  :
							break;
	}
	}while(selection != 'E' && selection != 'e');
	/*ana menu cikis istenene kadar ekranda kalir program kapamaz*/
	
	/*acilmis dosyalar kapatilir*/
	fclose(priceFile);
	fclose(initFile);
	fclose(reportFile);
	
	return 0;
	
	/*END_OF_MAIN*/
}

/*##########################################################################*/
/*								FUNCTIONS									*/
/*##########################################################################*/


/*transaction fonksiyonuna yardýmcý fonksiyon(secenek belirler)*/
void transSelect(int *amoOSI, int *amoOBI, int *amount, int *dolarA, 
				 int *goldA, int *fundA, double dolarP, double goldP, double fundP)
{
	char subSelect, subSelect2; /*secim degiskenleri*/
	double rate;
	
	
	/*satilacak eleman sorulur*/
	printf("What will you sell??\n");
	printf("[D - d] for Dolar\n");
	printf("[G - g] for Gold\n");
	printf("[F - f] for Investment Fund\n>>");
	
	scanf(" %c", &subSelect);
	while(subSelect != 'D' && subSelect != 'G' && 
		  subSelect != 'F' && subSelect != 'd' && 
		  subSelect != 'g' && subSelect != 'f')
	{
		printf("Entered wrong selection!!!\nTry Again\n>>");
		scanf(" %c", &subSelect);
	}
	
	/*alinacak eleman sorulur*/
	printf("What will you buy instead sold element??\n");
	printf("[D - d] for Dolar\n");
	printf("[G - g] for Gold\n");
	printf("[F - f] for Investment Fund\n>>");
	
	scanf(" %c", &subSelect2);
	while(subSelect2 != 'D' && subSelect2 != 'G' && 
		  subSelect2 != 'F' && subSelect2 != 'd' && 
		  subSelect2 != 'g' && subSelect2 != 'f')
	{
		printf("Entered wrong selection!!!\nTry Again\n>>");
		scanf(" %c", &subSelect2);
	}
	
	/*islemin miktari sorulur*/
	printf("Enter your operation amount\n>>");
	scanf("%d", amount);
	
	
	/* secime gore islemler yapilir.
	 * transaction fonksiyonunda kullanilacak parametrelere uygun degiskenler
	 * atanýr ve transaction fonksiyonu cagrilir
	 */
	switch(subSelect)
	{
		case 'D':
		case 'd':
					
					*amoOSI = *dolarA;
					transaction(amoOSI, amoOBI, amount, rate);
					*dolarA = *amoOSI;
					
					
					break;
		
		case 'G':
		case 'g':
					*amoOSI = *goldA;
					transaction(amoOSI, amoOBI, amount, rate);
					*goldA = *amoOSI;
					break;
	
		case 'F':
		case 'f':
					*amoOSI = *fundA;
					transaction(amoOSI, amoOBI, amount, rate);
					*fundA = *amoOSI;
					break;
		
		default:
					break;
	
	}				

	
	/* secime gore islemler yapilir.
	 * transaction fonksiyonunda kullanilacak parametrelere uygun degiskenler
	 * atanýr ve transaction fonksiyonu cagrilir
	 */
	switch(subSelect2)
	{
		
		case 'D':
		case 'd':
					*amoOBI = *dolarA;
					
					if(subSelect == 'D' || subSelect == 'd')
						rate = dolarP / dolarP;
					
					if(subSelect == 'G' || subSelect == 'g')
						rate = goldP / dolarP;
					
					if(subSelect == 'F' || subSelect == 'f')
						rate = fundP / dolarP;
						
					transaction(amoOSI, amoOBI, amount, rate);
					*dolarA = *amoOBI;
					break;
		
		case 'G':
		case 'g':
					*amoOBI = *goldA;
					
					if(subSelect == 'D' || subSelect == 'd')
						rate = dolarP / goldP;
					
					if(subSelect == 'G' || subSelect == 'g')
						rate = goldP / goldP;
					
					if(subSelect == 'F' || subSelect == 'f')
						rate = fundP / goldP;
					
					
					transaction(amoOSI, amoOBI, amount, rate);
					
					*goldA = *amoOBI;
					
					break;
	
		case 'F':
		case 'f':
					*amoOBI = *fundA;
					
					if(subSelect == 'D' || subSelect == 'd')
						rate = dolarP / fundP;
					
					if(subSelect == 'G' || subSelect == 'g')
						rate = goldP / fundP;
					
					if(subSelect == 'F' || subSelect == 'f')
						rate = fundP / fundP;
					
					transaction(amoOSI, amoOBI, amount, rate);
					*fundA = *amoOBI;
					break;
		
		default:
					break;
	
	}				

	
}

/*satilan elemana karsilik baska eleman alma fonksiyonu*/
int  transaction(int *amoOSI, int *amoOBI, int *amount, double rate) 
{
	
	/*satilan elemanin o anki miktarindan islem miktari cikarilir */
	*amoOSI -= *amount; 
	/*satilan elemanin karsiligi olan elemanin miktari eklenir*/
	*amoOBI += *amount * rate;
	
	/*degerler negatif olursa hata kodu dondurur*/
	/*yetersiz bakiye durumunda*/
	if (*amoOSI < 0 || *amoOBI < 0 || *amount < 0)
		*amount = -1;
	
	/*islem sonunda da islem miktari dondurulur
	 * eger islem yanlis olmussa amount -1 olur(hata kodu) 
	 * basarili bir islem olmussa amount degeri ayni kalir */
	return *amount;
	
}


/*filedan kur degeri okuma fonksiyonu*/
void getPrices(FILE *priceFile, double *dolarP , double *goldP, double *fundP)
{
	double price; 			/*gecici kur atama*/
	int status;				/*eof kontrolu*/
	char element, colon;	/*element kodu ve :*/
	
	
	/*en basta okuma yapilir*/
	fscanf(priceFile, " %c%c ", &element, &colon);
	status = fscanf(priceFile, "%lf", &price);
	
	/*eof degilse eof olana kadar okumaya devam edilir
	 *ve element koduna gore kur miktari o elemana atanir*/
	while(status != EOF)
	{		
		switch(element)
		{
			case 'D':
			case 'd':
						*dolarP = price;
						break;
						
			case 'G':	
			case 'g':
						*goldP = price;
						break;
			
			case 'F':						
			case 'f':
						*fundP = price;
						break;
			default :
						break;
		}
		
		/*okuma devam eder..*/
		fscanf(priceFile, " %c%c ", &element, &colon);
		status = fscanf(priceFile, "%lf", &price);
	
	}
}

/*ana menu*/
void menu(void)
{	
	printf("\n------------------------------------");
	printf("\nPLEASE ENTER YOUR SELECTION \n\n");
	printf("[T - t] for Transaction \n");
	printf("[B - b] for Buying \n");
	printf("[S - s] for Selling \n");
	printf("[I - i] for Input \n");
	printf("[O - o] for Output\n");
	printf("[F - f] for Report to File \n");
	printf("[P - p] for Report to Console \n");
	printf("[E - e] for EXIT !! \n");
	printf("\n>>");
}

/*o anki degerleri ekrana basma fonksiyonu*/
void report2Console(int liraA, int dolarA, int goldA, int fundA)
{


	printf("You Have\n>>\n");
	printf("TL	: %d\n", liraA);
	printf("Dolar	: %d\n", dolarA);
	printf("Gold 	: %d\n", goldA);
	printf("I.Fund 	: %d\n", fundA);
}

/*dosyadan baslangic eleman miktarlarini okuma fonksiyonu*/
void getInitials(FILE *initFile, int *liraA,int *dolarA, int *goldA, int *fundA)
{
	int amount, status;		/*gecici miktar atama ve eof kontrolu*/
	char element, colon;	/*element kodu ve :*/
	
	
	/*en basta okuma yapilir*/
	fscanf(initFile, " %c%c ", &element, &colon);
	status = fscanf(initFile, "%d", &amount);
		
		
	/*eof degilse eof olana kadar okumaya devam edilir
	 *ve element koduna gore kur miktari o elemana atanir*/	
	while(status != EOF)
	{		
		switch(element)
		{
			case 'L':
			case 'l':
						*liraA = amount;
						break;
			
			case 'D':
			case 'd':
						*dolarA = amount;
						break;
						
			case 'G':
			case 'g':
						*goldA = amount;
						break;
			
			case 'F':
			case 'f':
						*fundA = amount;
						break;
			default :
						break;
		}
		
		/*okuma devam eder..*/
		fscanf(initFile, " %c%c ", &element, &colon);
		status = fscanf(initFile, "%d", &amount);
	
	}
}

/*o anki degerleri dosyaya yazma fonksiyonu*/
void saveReport(FILE *reportFile, int amoOLira, int amoODolar, int amoOGold,
				int amoOFund)
{			
		/*degerler file pointerla belirlenmis dosyaya yazilir*/
		fprintf(reportFile, "L: %d\n", amoOLira);
		fprintf(reportFile, "D: %d\n", amoODolar);
		fprintf(reportFile, "G: %d\n", amoOGold);				
		fprintf(reportFile, "F: %d\n", amoOFund);
}	

/*her hangi bir elemandan eksiltme fonksiyonu*/
void output(int *liraA,int *dolarA, int *goldA, int *fundA)
{
	int  amoDec;		/*azaltma miktari*/
	char subSelect;		/*secim degiskeni*/
	
	
	printf("Select element for decreasing\n");
	printf("[L - l] for TL\n");
	printf("[D - d] for Dolar\n");
	printf("[G - g] for Gold\n");
	printf("[F - f] for Investment Fund\n>>");
	
	/*dogru seim girilene kadar secim yapilmasi beklenir*/
	scanf(" %c", &subSelect);
	while(subSelect != 'L' && subSelect != 'D' && subSelect != 'G' && 
		  subSelect != 'F' && subSelect != 'l' && subSelect != 'd' && 
		  subSelect != 'g' && subSelect != 'f')
	{
		printf("Entered wrong selection!!!\nTry Again\n>>");
		scanf(" %c", &subSelect);
	}
	
	/*azaltma miktari sorulur ve deger alinir*/
	printf("Enter the amount of decreasing\n>>");
	scanf("%d", &amoDec);
	
	/*secime gore ilgili elemanin azaltma islemi yapilir*/
	switch(subSelect)
	{
		case TL		   	:
		case TL+
			 DIFFERENCE :	
							if(*liraA >= amoDec)
							{
								*liraA -= amoDec;
								printf("You decrease %d Liras\n", amoDec);
							}	
							break;
						
		case Gold		:
		case Gold +
			 DIFFERENCE :
							if(*goldA >= amoDec)
							{
								*goldA -= amoDec;
								printf("You decrease %d Unit Golds\n", amoDec);
							}
							break;
		
		case Dolar		:
		case Dolar +
			 DIFFERENCE :
							if(*dolarA >= amoDec)
							{
								*dolarA -= amoDec;
								printf("You decrease %d Dolars\n", amoDec);
							}
							break;
		
		case Fund		:
		case Fund +
			 DIFFERENCE	:
							if(*fundA >= amoDec)
							{
								*fundA -= amoDec;
								printf("You decrease %d I. Funds\n", amoDec);
							}
							break;
		
		default			:
							break;
	}
}

/*herhangi bir elemandan artýrma fonksiyonu*/
void input(int *liraA,int *dolarA, int *goldA, int *fundA)
{
	int  amoInc;		/*artirma iktari*/
	char subSelect;		/*secim degiskeni*/
	
	
	printf("Select element for increasing\n");
	printf("[L - l] for TL\n");
	printf("[D - d] for Dolar\n");
	printf("[G - g] for Gold\n");
	printf("[F - f] for Investment Fund\n>>");
	
	/*dogru seim girilene kadar secim yapilmasi beklenir*/
	scanf(" %c", &subSelect);
	while(subSelect != 'L' && subSelect != 'D' && subSelect != 'G' && 
		  subSelect != 'F' && subSelect != 'l' && subSelect != 'd' && 
		  subSelect != 'g' && subSelect != 'f')
	{
		printf("Entered wrong selection!!!\nTry Again\n>>");
		scanf(" %c", &subSelect);
	}
	
	
	/*dogru seim girilene kadar secim yapilmasi beklenir*/
	printf("Enter the amount of increasing\n>>");
	scanf("%d", &amoInc);
	
	
	/*secime gore ilgili elemanin azaltma islemi yapilir*/
	switch(subSelect)
	{
		case TL		   	:
		case TL+
			 DIFFERENCE :
							*liraA += amoInc;
							printf("You increased %d Liras\n", amoInc);
							break;
						
		case Gold		:
		case Gold +
			 DIFFERENCE :
							*goldA += amoInc;
							printf("You increased %d Unit Golds\n", amoInc);
							break;
		
		case Dolar		:
		case Dolar +
			 DIFFERENCE :
							*dolarA += amoInc;
							printf("You increased %d Dolars\n", amoInc);
							break;
		
		case Fund		:
		case Fund +
			 DIFFERENCE	:
							*fundA += amoInc;
							printf("You increased %d I. Funds\n", amoInc);
							break;
		
		default			:
							break;
	}
}

/*eleman alimi yapma fonksiyonu*/
void buy(int *liraA,int *dolarA, int *goldA, int *fundA,
		 double dolarP, double goldP, double fundP)
{
	int amoBuy;			/*alinacak miktar*/
	char subSelect;		/*secim degiskeni*/
	
	
	printf("What will you buy??\n");
	printf("[D - d] for Dolar\n");
	printf("[G - g] for Gold\n");
	printf("[F - f] for Investment Fund\n>>");	

	
	/*dogru secim yapilana kadar beklenir*/
	scanf(" %c", &subSelect);
	while(subSelect != 'L' && subSelect != 'D' && subSelect != 'G' && 
		  subSelect != 'F' && subSelect != 'l' && subSelect != 'd' && 
		  subSelect != 'g' && subSelect != 'f')
	{
		printf("Entered wrong selection!!!\nTry Again\n>>");
		scanf(" %c", &subSelect);
	}
	
	/*satin alma miktari sorulur ve deger alinir*/
	printf("Enter the amount of buying\n>>");
	scanf("%d", &amoBuy);
	
	
	/*secime ve degere gore islemler yapilir*/
	switch(subSelect)
	{
		
		case Gold		:
		case Gold +
			 DIFFERENCE :	if(*liraA >= amoBuy * goldP)
							{
								*goldA += amoBuy;
								*liraA -= (int)(amoBuy * goldP + 0.5);
								printf("You bought %d Unit Golds\n", amoBuy);
							}
							break;
		
		case Dolar		:
		case Dolar +
			 DIFFERENCE :	if(*liraA >= amoBuy * dolarP)
							{
								*dolarA += amoBuy;
								*liraA -= (int)(amoBuy * dolarP + 0.5);
								printf("You bought %d Dolars\n", amoBuy);
							}
							break;
		
		case Fund		:
		case Fund +
			 DIFFERENCE	:	if(*liraA >= amoBuy * fundP)
							{
								*fundA += amoBuy;
								*liraA -= (int)(amoBuy * fundP + 0.5);
								printf("You bought %d I. Funds\n", amoBuy);
							}
							break;
		
		default			:
							break;
	}
}

/*eleman satisi yapma fonksiyonu*/
void sell(int *liraA,int *dolarA, int *goldA, int *fundA,
		 double dolarP, double goldP, double fundP)
{
	int amoSell;		/*satilacak miktar*/
	char subSelect;		/*secim degiskeni*/
	
	printf("What will you sell??\n");
	printf("[D - d] for Dolar\n");
	printf("[G - g] for Gold\n");
	printf("[F - f] for Investment Fund\n>>");	
	
	/*dogru secim yapilana kadar beklenir*/
	scanf(" %c", &subSelect);
	while(subSelect != 'D' && subSelect != 'G' && 
		  subSelect != 'F' && subSelect != 'd' && 
		  subSelect != 'g' && subSelect != 'f')
	{
		printf("Entered wrong selection!!!\nTry Again\n>>");
		scanf(" %c", &subSelect);
	}
	
	/*satilacak miktar sorulur ve deger alinir*/
	printf("Enter the amount of selling\n>>");
	scanf("%d", &amoSell);
	
	
	/*secime gore satis islemi yapilir*/
	switch(subSelect)
	{
		
		case Gold		:
		case Gold +
			 DIFFERENCE :	if(*goldA >= amoSell)
							{
								*goldA -= amoSell;
								*liraA += (int)(amoSell * goldP + 0.5);
								printf("You sold %d Unit Golds.", amoSell);
							}
							
							break;
		
		case Dolar		:
		case Dolar +
			 DIFFERENCE :	if(*dolarA >= amoSell)
							{
								*dolarA -= amoSell;
								*liraA += (int)(amoSell * dolarP + 0.5);
								printf("You sold %d Dolars.", amoSell);
							}
							
							break;
		
		case Fund		:
		case Fund +
			 DIFFERENCE	:	if(*fundA >= amoSell)
							{
								*fundA -= amoSell;
								*liraA += (int)(amoSell * fundP + 0.5);
								printf("You sold %d Investment Funds.", amoSell);
							}
							
							break;
		
		default			:
							break;
	}
}
