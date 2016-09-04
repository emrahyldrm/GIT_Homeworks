/*##########################################################################*
*HW06_111044056.c															*
*Emrah YILDIRIM tarafýndan 07.04.2014 tarihinde yazýldý						*
*																			*
*****************************************************************************
*																			*
* -------------------------------TANIM--------------------------------------*
* istenen sayiya gore dosyadaki arraylerden bu sayiyla baslayip biten 		*
* en uzun altdiziyi bulup, baslama ve bitis indislerini 					*
* baska bir dosyaya yazan program											*
*****************************************************************************
*-------------------------------DOSYALAR------------------------------------*
* INPUT >> arrays.txt:  arraylerin okunacagi dosya							*
*		   numbers.txt: arama sayisinin okunacagi dosya						*
* OUTPUT>> longest.txt: en uzun altdizinin baslama ve bitis indisleri		*
*																			*
*****************************************************************************
* ----------------------------CALISMA SEKLI---------------------------------*
* 1> numbers.txt den aranacak sayi okunur									*
* 	1.1 arrays.txt den bastan baslayarak satir okunur ve arraye yazilir		*
* 	1.2 yazilan arrayde varsa sayinin baslama ve bitis indisleri dondurulur	*
*	  	yoksa da default olarak "-1" dondurulur								*
* 	1.3 bu indisler arasi fark bir onceki farktan buyukse yer degistirilir	*
*		ayni sekilde en uzun indis degiskenlerine var olan degerler atanir	*
*	>> alt islemler arrays.txt nin sonuna gelene kadar devam eder			*
* 2> sona gelindiginde elde edilen en buyuk indisler longest.txt ye yazilir	*
* 3> 1 ve 2 numbers.txt nin sonuna kadar devam eder 						*
*###########################################################################*/



#include<stdio.h>
#define MAX_SIZE 100		/*maksimum array buyuklugu*/
#define ERROR_FIRST -1		/*ilk indis icin hata kodu*/
#define ERROR_LAST  -1		/*son indis icin hata kodu*/
#define MIN			-999	/*gecici deger icin min degeri*/
#define CHAR_TO_INT  48		/*int cevriminde ascii koddan cikarilecak deger*/
#define TRUE		 1
#define FALSE		 0

/*##########################################################################*/
/*							Function Prototypes								*/
/*##########################################################################*/

/*aranacak numarayi alan fonskiyon*/
int TakeNumber(FILE *, int *);

/*dosyadan her satiri array olarak okuyacak fonksiyon*/
int ReadArray(int array[], FILE *, int *);

/*her array icin en uzun araligin indisini bulup dondurecek fonksiyon*/
void Longest(const int array[], int, int, int *, int *);

/*array ekrana basma fonskiyonu*/
void Print(int, int, FILE *, int);

/*sonuc yazdirma fonksiyonu*/
void Print2Console(const int arr[], int size);

/*en uzun dizini bulma fonksiyonu*/
void FindLongestLongest(int arr[], int *, FILE *, FILE *, FILE *, int*, int*);


/*##########################################################################*/
/*								MAIN Function								*/
/*##########################################################################*/

int main()
{
	/*START_OF_MAIN*/
	int arr[MAX_SIZE], size, 		 /*doldurulacak array ve buyuklugu*/		
		longestLast, longestFirst;	 /*tumu icin en uzun dizinin indisleri*/

	FILE *arrFilePtr;				 /*array file pointeri*/
	FILE *numberFilePtr;			 /*aranacak sayinin file pointeri*/
	FILE *longestFilePtr;			 /*en uzun indisleri yazdirma fonksiyonu*/

	/*END_OF_VARIABLES*/

	/*file pointerlara atama yapilir dosyalar okumak uzere acilir*/
	arrFilePtr = fopen("arrays.txt", "r");
	numberFilePtr = fopen("numbers.txt", "r");
	longestFilePtr = fopen("longest.txt", "w");
	
	
	/*en uzun altdizi bulma fonksiyonu cagrilir*/
	FindLongestLongest(arr, &size, arrFilePtr, numberFilePtr, 
					   longestFilePtr, &longestFirst, &longestLast);
	
	/*acilmis dosyalar kapatilir*/
	fclose(arrFilePtr);
	fclose(numberFilePtr);
	fclose(longestFilePtr);

	system("pause");
	return 0;
	/*END_OF_MAIN*/
}

/*##########################################################################*/
/*								FUNCTIONS									*/
/*##########################################################################*/

/*tum arraylerdeki en uzun altdiziyi bulan fonksiyon*/
void FindLongestLongest(int arr[], int *size, FILE *arrFilePtr, 
						FILE *numberFilePtr, FILE *longestFilePtr, 
						int *longestFirst, int *longestLast  )
{	
	int searchNum, 					 /*aranacak sayi*/
		endReadArr = 0, endNumbers=0,/*dosyalarin sonunu gosteren degiskenler*/
		temp = MIN,					 /*gecici toplam degiskeni*/
		firstIndex, lastIndex; 		 /*arraydeki en uzun dizinin indisleri*/

	do
	{
		/*aranacak numara alinir ve 
		 *numbers.txt dosya sonu kontrolu endNumbers a atanýr
		 */
		endNumbers = TakeNumber(numberFilePtr, &searchNum);
		
		/*numbers.txt de dosya sonu degilse devam edilir*/
		if(endNumbers != EOF)
		{
			
			do
			{	/*satýr okunur, arraye yazilir 
				 *arrays.txt nin dosya sonu kontrolu icin endReadArr e atanir
				 */
				endReadArr = ReadArray(arr, arrFilePtr, size);
				Print2Console(arr, *size);
				
				
				/*alinan arrayde sayiyi arar ve 
				 *en uzun olanin ilk ve son indislerini degiskenlerine atar
				 */
				Longest(arr, *size, searchNum, &firstIndex, &lastIndex);
				
				/*o anki arrayde bulunan indislerin farký 
				 *eski farktan daha buyukse yeni fark eski farkin yerine yazilir
				 *yeni indislerde eskileri ile degistirilir
				 */
				if(temp < lastIndex - firstIndex)
				{
					temp = lastIndex - firstIndex;
					*longestLast = lastIndex;
					*longestFirst = firstIndex;
				}
			/*arrays.txt nin sonuna gelinene kadar islem devam eder*/
			}while(endReadArr != EOF);
		}	
			
			/*eger numbers.txt nin sonu degilse ve en buyuk dizinin indisleri
			 *-1 e esit degilse indisler longest.txt ye yazdirilir*/
			if(endNumbers != EOF)
			{
				Print(*longestFirst, *longestLast, longestFilePtr, searchNum);
			}
			
			temp = MIN;			/*temp yeni sayi aramasi icin eski haline getirilir*/
			
			/*array.txt dosyasinin basina donulur*/
			fclose(arrFilePtr);
			arrFilePtr = fopen("arrays.txt", "r");
	
	/*numbers.txt nin sonuna kadar islemler devam eder*/
	}while(endNumbers != EOF);


}

/*dosyadan array okuma fonksiyonu*/
int ReadArray(int array[], FILE *arrFilePtr, int *size)
{
	int i=0, status,	/*array indisi, fscanf donus degeri*/
		total=0, num;	/*integer cevirmede sayinin tamami ve her basamagi*/
	int flag = FALSE;	/*bosluk belirteci*/
	char a; 			/*okunan karakter*/
	

	/*dosyadan karakter karakter okuma yapilir*/
	status = fscanf(arrFilePtr, "%c", &a);
	
	/*okuma sonucunda new line ve EOF degilse donguye girilir*/
	while(a!='\n' && status != EOF)
	{	
		flag = FALSE;
		
		/*okunan deger integer bir degerse 
		 *ascii kodundan int degere cevrilir 
		 *eski toplama eklenir
		 */
		while(a >= '0' && a <='9')
		{
			{	
				num = a - CHAR_TO_INT;
				total= total * 10 + num;
			}
			
			status = fscanf(arrFilePtr, "%c",&a);
			
			/*integer deger elde edilirse flag TRUE olur*/
			flag = TRUE;			
		}
		
		/*islem bitince int deger arraye yazilir 
		 *total sifirlanir ve indis degeri 1 artirilir
		 *islemin yapilabilmesi icin int deger(flag = TRUE) olmasi gerekir*/
		if(flag == TRUE)
		{
			array[i] = total;
			total=0;
			i++;
		}	
		
		/*son okunan deger new line ya da EOF degilse yeni bir okuma yapilir*/
		if(a!='\n' && status != EOF)
			status = fscanf(arrFilePtr, "%c", &a);		
	}
	
	/*son indisin degeri array buyuklugu olarak atanir*/
	*size = i;
	
	/*dosya sonu bilgisi dondurulur*/
	return status;
}

/*arraydeki en uzun diziyi bulma fonksiyonu*/
void Longest(const int array[], int size, int searchNum, int *firstIndex, int *lastIndex)
{

	int i;	/*indis degeri*/
	
	/*deger bulunamazsa -2 dondurulur*/
	*firstIndex = ERROR_FIRST;
	*lastIndex = ERROR_LAST;

	/*son indeksi bulan dongu, aramaya bastan baslanir son deger bulunur*/
	for(i = 0; i < size; i++)
	{
		/* i indisindeki eleman arama elemanina esitse 
		 * son indeksi gosteren pointer a i degeri atanir
		 */
		if(array[i] == searchNum)
			*lastIndex = i;
	}

	/*ilk indeksi bulan dongu, aramaya sondan baslanir ilk deger bulunur*/
	for(i = size-1; i >= 0; i--)
	{
		/* i indisindeki eleman arama elemanina esitse 
		 * ilk indeksi gosteren pointer a i degeri atanir
		 */
		if(array[i] == searchNum)
			*firstIndex = i;
	}

}


/*dosyadan aranacak sayiyi alan dongu */
int TakeNumber(FILE *numberFilePtr, int *num)
{
	int status;	/*dosya sonu bilgisi*/
	
	/*okuma yapilir*/
	status = fscanf(numberFilePtr, "%d", num);
	
	/*dosya sonu degeri dondurulur*/
	return status;
}

/*sonuc yazdirma fonksiyonu*/
void Print(int longestFirst, int longestLast, FILE *longestFilePtr, int searchNum)
{	

	/*ilk ve son indis degerleri hata kodu -1 e esitse 
	 *ya da ilk ve son indis ayný ise hata kodu yazdirilir
	 */
	if  ((longestLast == ERROR_LAST && longestFirst == ERROR_FIRST) ||
		(longestLast - longestFirst == 1 || longestLast - longestFirst == 0))	   
	{
		fprintf(longestFilePtr, "%d %d\n", ERROR_FIRST, ERROR_LAST);
		printf(">>ERROR : a subsequent for %d was not found !!\n\n",searchNum);
	}
	/*gelen degerler beklenen tipteyse degerler yazdirilir*/
	else
	{
		fprintf(longestFilePtr, "%d %d\n", longestFirst, longestLast);
		printf(">> The Longest Subsequent's Indexes for \"%d\"", searchNum);
		printf(" are %d and %d\n\n", longestFirst, longestLast);
	}
}


/*konsola yazdirma fonksiyonu*/
void Print2Console(const int arr[], int size)
{
	int i=0;	/*yazdirma icin indis degeri*/
	
	/*arrayde eleman varsa yazdirma yapilir*/
	if(size !=0)
	{
		for(i=0; i < size; ++i)
		{
			printf("%d ", arr[i]);
		}
		printf("\n");
	}
}
