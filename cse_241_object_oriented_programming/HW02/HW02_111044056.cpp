/*##########################################################################*
*HW02_111044056.cpp															*
*Emrah YILDIRIM 															*
*																			*
*****************************************************************************
*																			*
* -------------------------------TANIM--------------------------------------*
* Fonksiyon pointer ý kullanarak dizideki n. elemanýn adresini bulma		*
* 																			*
*****************************************************************************
*****************************************************************************
* ----------------------------CALISMA SEKLI---------------------------------*
* fonksiyona gonderilen arrayle birlikte karsilastirma arrayi de gonderilir	*
* fonksiyon daha sonra bu arrayi sýralar									*
* sýralanmýs olan arrayde(temp) n. terim bulunur							*
* bulunan terimin ana arraydeki(base) yeri bulunur ve adresi return edilir	*
*###########################################################################*/


/*##########################################################################*/
/*						libraries and Constant Macros						*/
/*##########################################################################*/

#include<iostream>
#include<cstdlib>
#include<cstring>

using namespace std;

#define SIZE		10
#define NAME_SIZE	50
#define ID_SIZE		12



/*##########################################################################*/
/*								CLASSES										*/
/*##########################################################################*/


class DayOfYear
{
public:
	int day, month, year;
};

class Person
{
public:
	char name[NAME_SIZE], surname[NAME_SIZE];
	char ID[ID_SIZE];
};

/*##########################################################################*/
/*							FUNCTIONS										*/
/*##########################################################################*/

const void * return_nth (const void * base, size_t num, size_t size, int nth,
					int (* comparator) (const void *, const void *));

// integerlar arasi kontrol saðlar kucukten buyuge sýralamada kullanilir
// ilkArguman > ikinciArguman isleminin sonucunu return eder.					
int intComp(const void * num1, const void * num2);

// karakterler arasi alfabetik a-z siralamada kullanilir 
// ilkArguman > ikinciArguman isleminin sonucunu return eder.
int charComp(const void *ch1, const void *ch2);

// double lar arasi kontrol saðlar kucukten buyuge sýralamada kullanilir
// ilkArguman > ikinciArguman isleminin sonucunu return eder.
int doubleComp(const void *d1, const void *d2);

// DayOfYear objeleri arasinda gune gore siralama saglar
// kucukten buyuge siralamada kullanilir
// ilkArguman > ikinciArguman isleminin sonucunu return eder.
int dayComp(const void * DOY1, const void *DOY2);

// Person objeleri arasinda isme gore siralama saglar
// a-z siralamada kullanilir
// strcmp(ilkAd, ikinciAd) isleminin sonucunu return eder.
int nameComp(const void *person1, const void *person2);


// girilen 2 adresten baslayarak size kadarlik hafiza alanýný..
//..birbiri ile degistirir
void swap(char *mem1, char *mem2, size_t size);

// source dizisini dest dizisine kopyalar
// num >> dizilerin eleman sayilari
// size >> dizinin her elemaninin kapladigi hafiza alani(byte cinsinden)
void copyArr(void *dest, const void *source, size_t num, size_t size);

// base dizisinde search dizisini arar
// bulduðunda base deki adresini return eder
// num >> dizilerin eleman sayilari
// size >> dizinin her elemaninin kapladigi hafiza alani(byte cinsinden)
const void * search(const void *base, const char *search, size_t num, size_t size);

// dest ve search dizisinin ayni olup olmadigini kontrol eder
// size >> dizinin her elemaninin kapladigi hafiza alani(byte cinsinden)
int isEqual(const char *base, const char *search, size_t size);



/*##########################################################################*/
/*								MAIN Function								*/
/*##########################################################################*/
 
int main()
{
	int arr[SIZE];
	const int *a;
	
	double doubArr[SIZE] = {1.5, 0.5, 0.3, 2.3, 2.7, 0.6, 3.4, 4.0, 10.0, 0.1};
	const double *d;
	
	char cArr[SIZE] = {'b', 'c' , 'a', 'z', 'f', 'e', 'd', 'j', 'm', 'k'};
	const char *c;
	
	DayOfYear DOY[3];
	const DayOfYear *day;
	
	Person  person[2];
	const Person *per;
	
	
	cout << "\n >>TESTED ALL ARRAYS' EACH MEMBERS, SO USED"
		 << "FOR LOOPS WHEN CALLING return_nth \n\n";
	
	cout << "TESTING FOR INTEGERS\n\n"
		 << "First State"<<endl;
	for(int i=0, j=SIZE; i < SIZE; ++i, --j)
		arr[i] = j;

	
	for(int i=0; i < SIZE; ++i)
			cout << arr[i] <<" ";

	cout <<endl;

	for(int i=0; i < SIZE; ++i)
	{
		a = static_cast<const int*>(return_nth (arr, SIZE, sizeof(int), i, intComp));
		
		cout << *a <<" ";
	}

	cout << endl <<endl;
	
	
	cout << "TESTING FOR CHARACHTERS\n\n"
		 << "First State"<<endl;
	for(int i=0; i < SIZE; ++i)
			cout << cArr[i] <<" ";
		
		cout << endl;
		
	for(int i=0; i < SIZE; ++i)
	{
		c = static_cast<const char *>(return_nth (cArr, SIZE, sizeof(char), i, charComp));

		cout << *c <<" ";
	}

	
	cout << endl <<endl;

	
	cout << "TESTING FOR DOUBLES\n\n"
		 << "First State"<<endl;
	
	for(int i=0; i < SIZE; ++i)
		cout << doubArr[i] <<" ";
	
	cout << endl<<endl;
	
	for(int i=0; i < SIZE; ++i)
	{
		d = static_cast<const double *>(return_nth (doubArr, SIZE, sizeof(double), i, doubleComp));

		cout << *d <<" ";
	}
	cout <<endl<<endl;
	
	
	cout << "TESTING FOR PERSONS\n\n"
		 << "First State"<<endl;
	strcpy(person[0].name, "emrah");
	strcpy(person[0].surname, "yildirim");
	strcpy(person[0].ID, "01010101012");
	
	strcpy(person[1].name, "caner");
	strcpy(person[1].surname, "yilmaz");
	strcpy(person[1].ID, "01010101013");
	
	for(int i=0; i < 2; ++i)
		cout << person[i].name <<" ";
		
	cout <<endl<<endl;
	for(int i=0; i < 2; ++i)
	{
		per = static_cast<const Person *>(return_nth (person, 2, sizeof(Person), i, nameComp));

		cout << per->name <<" ";
	}
	cout <<endl<<endl;
	

	cout << "TESTING FOR DAYOFYEARS\n\n"
		 << "First State"<<endl;
	DOY[0].day = 12;
	DOY[0].month = 3;
	DOY[0].year = 2013;
	
	DOY[1].day = 11;
	DOY[1].month = 12;
	DOY[1].year = 12;
	
	DOY[2].day = 5;
	DOY[2].month = 12;
	DOY[2].year = 12;
	
	
	for(int i=0; i < 3; ++i)
		cout << DOY[i].day <<" ";
	
	cout << endl;
	
	for(int i=0; i < 3; ++i)
	{
		day = static_cast<const DayOfYear *>(return_nth (DOY, 3, sizeof(DayOfYear), i, dayComp));

		cout << day->day <<" ";
	}


	cout << endl <<endl;

	return 0;
}


/*##########################################################################*/
/*								FUNCTIONS									*/
/*##########################################################################*/

const void * return_nth (const void * base, size_t num, size_t size, int nth,
					int (* comparator) (const void *, const void *))
{
	char *temp;
	const void *nthBaseAdress;
	
	if(nth > num || nth < 0) 	//nth in dizi alaninda olup olmama kontrolu
		return NULL;
	
	// yeni array icin yer alinir
	temp = static_cast<char *>(malloc(size*num));
	
	// temp arraye base array kopyalanir	
	copyArr(temp, base, num, size);

	// temp array siralanir
	for(int i=0; i < num*size; i+=size)
		for(int j=i; j < num*size; j+=size)
			if(comparator(&temp[i], &temp[j]))
				swap(&temp[i], &temp[j], size);
	
	// n. deger base de aranir
	nthBaseAdress = search(base, &temp[size*nth], num, size);
	free(temp);
	
	return nthBaseAdress;
}



// girilen 2 integer degerin karsilastirmasini yapar
// num1 > num2 return eder
// kucukten buyuge siralamada kullanilir
int intComp(const void * num1, const void * num2)
{
	const int *sNum1, *sNum2;
	
	sNum1 = static_cast<const int *>(num1);
	sNum2 = static_cast<const int *>(num2);
	
	return *sNum1 > *sNum2;
}


// girilen 2 karakteri degerin karsilastirmasini yapar
// karakter1 > karakter2 return eder
// alfabetik a-z siralamada kullanilir
int charComp(const void *ch1, const void * ch2)
{
	const char *sCh1, *sCh2;

	sCh1 = static_cast<const char *>(ch1);
	sCh2 = static_cast<const char *>(ch2);

	return  *sCh1 > *sCh2;
}


// girilen 2 double degerin karsilastirmasini yapar
// d1 > d2 return eder
// kucukten buyuge siralamada kullanilir
int doubleComp(const void *d1, const void *d2)
{
	const double *sD1, *sD2;
	
	sD1 = static_cast<const double *>(d1);
	sD2 = static_cast<const double *>(d2);
	
	
	return *sD1 > *sD2;
}


// girilen 2 DayOfYear objesini gun olarak karsilastirir
// day1 > day2 nin degerini return eder
// kucukten buyuge siralama icin kullanilir
int dayComp(const void * DOY1, const void *DOY2)
{
	const DayOfYear *sDOY1, *sDOY2;
	
	sDOY1 = static_cast<const DayOfYear *>(DOY1);
	sDOY2 = static_cast<const DayOfYear *>(DOY2);
	
	return (*sDOY1).day > sDOY2->day;
}


// girilen 2 Person objesinin isimlerini karsilastirir
// 1. önce geliyorsa 1 aksi halde 0 return eder.
// alfabetik a-z siralamada kullanilir
int nameComp(const void *person1, const void *person2)
{
	const Person *pr1, *pr2; 

	pr1= static_cast<const Person *>(person1);
	pr2= static_cast<const Person *>(person2);

	
	if(strcmp(pr1->name, pr2->name) == 1)
		return 1;
	else 
		return 0;
}
/*##########################################################################*/
/*								General Functions							*/
/*##########################################################################*/

// source u dest e kopyalar
// >> num: eleman sayisi
// >> size: eleman boyutu
void copyArr(void *dest, const void *source, size_t num, size_t size)
{
	char *p1;
	const char *p2;
	
	p1 = static_cast<char*>(dest);
	p2 = static_cast<const char*>(source);
	
	for(int i=0; i < size*num; ++i)
		p1[i] = p2[i];	
}


// girilen 2 adresten baslayarak size kadarlik hafiza alanini..
//..birbiri ile degistirir
// size: takas yapilacak alan boyutu
void swap(char *mem1, char *mem2, size_t size)
{
	char temp;
	
	for(int i=0;  i < size;  ++i, mem1++, mem2++)
	{	temp = *mem1;
		*mem1 = *mem2;
		*mem2 = temp;
	}
}


// search un base in hangi adresinden basladigini bulur
// >> base: ana array
// >> search: aranacak array
// >> num: base arrayinin eleman sayisi
// >> size: karsilastirilacak alan boyutu 
const void * search(const void *base, const char *search, size_t num, size_t size)
{
	const char *source;
	
	source = static_cast<const char *>(base);
	
	for(int i=0; i < num*size; ++i)
		if(source[i] == search[0])
			if((isEqual(&source[i], search, size)))
				return &source[i];
}


// dest ve source adreslerinden baslayarak size byte kadarlýk..
// .. alanin birbirine eþit olup olmadýðýný kontrol eder
// >> base: arama yapilacak array
// >> search: aranacak array
// >> size: karsilastirilacak alan boyutu
int isEqual(const char *base, const char *search, size_t size)
{
	int counter=0;
	
	for(int i=0; i < size; ++i)
		if(base[i] == search[i])
			counter++;
	
	if(counter == size)
		return 1;
	else 
		return 0;
}