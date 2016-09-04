/*##########################################################################*/
/*HW04_111044056															*/
/*--------------------------------------------------------------------------*/
/*Emrah YILDIRIM tarafýnda 18.03.2014 tarihinde yazýldý						*/
/* TANIM>>																	*/
/* MARKET STOK TAKIP VE ARAMA PROGRAMI										*/
/*																			*/
/* Kullanýcý isteðine göre þu iþlemleri yapabilir							*/
/* Var olan dosyayý kullanbilir ya da yeni bir tane oluþturabilir			*/
/* Yeni oluþturduðu dosyaya yeni ürünler ekleyebilir						*/
/*																			*/
/* Eðer eski dosyayý kullanmayý seçerse de þu iþlemleri yapabilir			*/
/* >>																		*/
/* 1- Eski dosyaya yeni ürünler ekleme										*/
/* 2- Eski dosyadaki tüm bilgileri okuma ve konsola basma					*/
/* 3- Ürünleri tipine göre arama											*/
/* 4- Ürünleri hem kod hem de tipine göre arama								*/
/* 5- Varolan ürün miktarýna göre listeleme									*/
/*																			*/
/*##########################################################################*/

/*##########################################################################*/
/*									Includes								*/
/*##########################################################################*/
#include<stdio.h>


/*##########################################################################*/
/*							Function Prototypes								*/
/*##########################################################################*/


void Start(void);
int SubMenu(void);
int Selection(void);
int SubSelection(void);
void Write2File(int);
void Search4CodeNType(void);
void Search4Type(void);
void Filter4Quant(void);
void ListAll(void);


/*##########################################################################*/
/*								MAIN Function								*/
/*##########################################################################*/
int main()
{	
	/*START_OF_MAIN*/
	/*END_OF_VARIABLES*/
	
	Start();

	return 0;
	/*END_OF_MAIN*/
}
/*##########################################################################*/
/*								FUNCTIONS									*/
/*##########################################################################*/

/*baþalama fonkdiyonu*/
void Start (void)
{
	int end;
	
	/*selection fonksiyonunda return 6 deðeri alýnana kadar devam eder*/
	/*6 degeri cikis degeridir*/
	
	do
	{	printf("-----------------------------------------------------\n\n");
		printf("What will you do ?? \n");
		
		end = Selection();
	
	}while(end != 6);
	
}


/*program baslangici secimi fonksiyonu*/
int Selection()
{
	int	 selection;
	int  end, stop = 1;
	
	/*eger dogru bir secim yapilmissa select degeri 0 olur ve döngu sona erer*/
	/*aksi takdirde dogru deger girilene kadar secim islemi devam eder*/
	
	do
	{	printf("\nENTER YOUR SELECTION\n\n");
		printf("[1]>>  Use existing file\n");
		printf("[2]>>  Create a new file\n");
		printf("[3]>>  EXIT\n>>");
		
		scanf("%d", &selection);
		
		/*1 secilmisse bir alt menuyu acan fonksiyon cagrilir ve return..*/
		/*.. 6 degeri gonderilerek ustteki fonksiyona isinin bittigi soylenir*/
		if (selection == 1)
		{
			stop = 0;
			end = SubMenu();
			
		}
		
		/*2 secilmisse dosyaya yazdýrma fonksiyonu cagrilir*/
		else if (selection == 2)
		{
			/*degerin 1 olmasý silinip dosyanýn üzerine yazilmasini soyler*/
			Write2File(1);	
			stop = 0;
		}
		
		/*3 secilirse return degeri 6 olur ve cikis verilir*/
		else if (selection == 3)
		{
			printf("Program is shutting down..\n");
			return 6;
		}
		
		/*yanlis secim durumunda uyari verilir ve basa donulur*/
		else
		{
			printf(">> You entered wrong selection !! Try Again..\n");
		}
			
	}while(stop != 0 );
	
	return end;
}


/*Alt menu yazdýrma va alt menu secimi fonksiyonunu cagirma fonksiyonu*/
int SubMenu(void)
{
	printf("\nENTER YOUR SELECTION \n\n");
	printf("[1] -- Enter New Products\n");
	printf("[2] -- List All Records \n");
	printf("[3] -- Search by Type \n");
	printf("[4] -- Search by Type and Code \n");
	printf("[5] -- Filter by Quantitiy \n");
	printf("[6] -- EXIT \n\n>>");
	
	return SubSelection();
}


/*alt menu secim yapma fonskiyonu*/
int SubSelection(void)
{
	int selection;
	
	scanf("%d", &selection);
	
	/*selection in degerine gore fonksiyon adi ile tanimli islemler yapilir*/
	switch(selection)
	{
		case 1:
				Write2File(0);
				break;
				
		case 2: 
				ListAll();
				break;

		case 3: 
				Search4Type();
				break;
				
		case 4: 
				Search4CodeNType();
				break;
		
		case 5: 	
				Filter4Quant();
				break;
		
		case 6:
				/*6 girilirse program kapatýlýr*/
				printf("Program is shutting down.. \n");
				break;
				
		default:
				break;
				
	}
	
	return selection;
}


/*dosyaya yazdirma fonksiyonu*/
void Write2File(int create)
{
	FILE *productPtr; /*file pointer*/
	
	int code, buy, sale, quant,
		stop;
	char type, trash, correctness;
	
	/*create degerinin 1 gelmesi dosyanýn silinip yazilmasýný saglar*/
		if(create == 1)
	{	
		productPtr = fopen("products.txt", "w");
		fclose(productPtr);
	}
	
	/*dosyauzerine ekleme yapilmaz üzere "a" komutu ile cagrilir*/
	productPtr = fopen("products.txt", "a");
	
	
	stop = -1;
	code = 0;
	
	printf("Enter the information one by one \n");
	printf("Code - Type - Buying Price - Sale Price - Quantity \n");
	scanf("%d", &code);

	do
	{
		if(code != -1)
		{

			scanf(" %c%d %d %d", &type, &buy, &sale, &quant);
			printf("-------------------------------------------------");
			printf("\nCODES  TYPES	BUYPRCS  SALEPRCS  QUANTITIES\n");
			printf(" %d	 %c	  %d	  %d		%d \n", code, type, buy, sale, quant);
			printf("-------------------------------------------------");
			
			printf("\nAre they true ? Y or N\n\n>>");
			scanf("%c%c", &trash, &correctness);
			
			if (correctness == 'y' || correctness == 'Y' )
			{
				fprintf(productPtr, "\n%d %c %d %d %d", code, type, buy, sale, quant);
				printf("\nThe product information was successfully written to the file\n");
				printf("You can continue..");
				printf("\nIf you want to stop, enter -1 \n>>");
			}
			
			else
			{
				printf("\nEnter again \n");
				printf("If you want to stop, enter -1 \n");
			}
		}
		scanf("%d", &code);
		
	}while(code != stop);

	
	fclose(productPtr);
}


/*dosyanin tamamini listeleme fonksiyonu*/
void ListAll(void)
{
	int code, buy, sale, quant, end;
	char type;
	
	FILE *productPtr;	/*file pointer*/
	
	/*dosya okuma yapmak uzere acilir*/
	productPtr = fopen("products.txt", "r");
	
	printf("\nList of All Records\n\n");
	printf("CODES  TYPES	BUYPRCS  SALEPRCS  QUANTITIES\n\n");
	
	/*end degeri fscanf in dondurdugu degeri alir ve dosya sonu kontrol edilir*/
	end = fscanf(productPtr, "%d %c %d %d %d", &code, &type, &buy, &sale, &quant);
	
	/*dosya sonuna geline kadar dosya taranir*/
	while(end != EOF)
	{
		printf(" %d	 %c	  %d	  %d		%d \n", code, type, buy, sale, quant);	
		
		/*end degeri fscanf in dondurdugu degeri alir vedosya sonu kontrol edilir*/
		end = fscanf(productPtr, "%d %c %d %d %d", &code, &type, &buy, &sale, &quant);
	}
	
	printf("-----------------------------------------------------\n\n");
	
	/*dosya kapatilir*/
	fclose(productPtr);
}


/*koda ve tipe gore arama fonksiyonu*/
void Search4CodeNType(void)
{
	int code, buy, sale, quant, end,
		searchCode, counter=0;
		
	char type, searchType, trash;
	
	FILE *productPtr; /*file pointer*/
	
	/*dosya okuma yapmak uzre acilir*/
	productPtr = fopen("products.txt", "r");
	
	/*hangi kod ve tipin aranacagi sorulur*/
	printf("Enter code and type for searching\n>>");
	scanf("%d %c", &searchCode, &searchType);
	printf("CODES  TYPES	BUYPRCS  SALEPRCS  QUANTITIES\n");
	
	
	do
	{

		fscanf(productPtr, "%d %c %d %d %d", &code, &type, &buy, &sale, &quant);
		
		/*kod ve tip istenen degerlerse ekrana basilir*/
		if (code == searchCode && type == searchType)
		{
			printf(" %d	 %c	  %d	  %d		%d \n", code, type, buy, sale, quant);
			counter += 1;
		}
		
		end = fscanf(productPtr, "%c", &trash);	
	}
	while(end != EOF);
	
	printf("-----------------------------------------------------\n\n");
	
	/*counter in 0 olmasý aranan dosyanin bulunamadigi anlaminba gelir*/
	if(counter == 0)
	printf("\nThe product that you searched does not exist!\n\n");
	
	fclose(productPtr);

}


/*tipe gore arama fonksiyonu*/
void Search4Type(void)
{


	int code, buy, sale, quant, end, counter=0;
		
	char type, searchType, trash;
	
	FILE *productPtr; /*file pointer*/
	
	/*dosya acilir*/
	productPtr = fopen("products.txt", "r");
	
	/*arama tipi sorulur*/
	printf("Enter type for searching\n>>");
	scanf("%c%c", &trash, &searchType);
	printf("CODES  TYPES	BUYPRCS  SALEPRCS  QUANTITIES\n");
	
	
	do
	{

		fscanf(productPtr, "%d %c %d %d %d", &code, &type, &buy, &sale, &quant);
		
		/*aranan tip okunan tip ile ayniysa ekrana yazilir*/
		if ( type == searchType)
		{
			printf(" %d	 %c	  %d	  %d		%d \n", code, type, buy, sale, quant);
			counter += 1;
		}	
		
		end = fscanf(productPtr, "%c", &trash);	
	}
	while(end != EOF);
	
	printf("-----------------------------------------------------\n\n");
	
	/*counter 0 sa arnan dosya bulunamamis demektir*/
	if(counter == 0)
		printf("\nThe product that you searched does not exist!\n\n");
}


/*stok adedine gore listeleme fonskiyonu*/
void Filter4Quant()
{
	int code, buy, sale, quant, 
		quantFilter, arrange, 
		end, counter;

	char type, trash;

	FILE *productPtr;	/*file pointer*/

	/*dosya acilir*/
	productPtr = fopen("products.txt", "r");
		
	/*arama yapilacak stok adedi sorulur*/
	printf("Enter the Quantity for filtering\n>>");
	scanf("%d", &quantFilter);
	
	/*belirlenen sto adedeinin altinin mi yoksa uzerinin mi*/
	/*aranacagi sorulur*/
	printf("Higher from selection [1]  --  Lower from selection [2] \n>>");
	scanf("%d", &arrange);

	printf("\nCODES  TYPES	BUYPRCS  SALEPRCS  QUANTITIES\n>>");
	
	
	do
	{

		fscanf(productPtr, "%d %c %d %d %d", &code, &type, &buy, &sale, &quant);
		
		/*belirlenen stok adedinin uzerindekiler sorulursa*/
		if (arrange == 1)
		{
			/*belirlenenden az olanlar ekrana basilir*/
			if ( quantFilter <= quant)
			{
				printf(" %d	 %c	  %d	  %d		%d \n", code, type, buy, sale, quant);
				counter += 1;
			}	
		}
		
		/*belirlene stok adedinin alti sorulursa*/
		if (arrange == 2)
		{
			/*belirlenenden fazla olanlar ekrana basilir*/
			if (quantFilter >= quant)
			{
				printf(" %d	 %c	  %d	  %d		%d \n", code, type, buy, sale, quant);
				counter += 1;		
			}
		}
		
		end = fscanf(productPtr, "%c", &trash);	
		
	}
	while(end != EOF);
	
	printf("-----------------------------------------------------\n\n");
	
	/*counter in 0 olmasý aranan nitelikte urun olmadigini gosterir*/
	if(counter == 0)
		printf("\nThe product that you searched does not exist!\n\n");
}
