/****************************************************************************/
/* 				Emrah YILDIRIM 111044056									*/
/*																			*/ 																			
/*				Conway'in Hayat Oyunu										*/
/*																			*/
/*																			*/
/****************************************************************************/



#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<cstring>


using namespace std;



// Kullanılacak dosyanın adını uzantısı ile birlikte kullanıcıdan alır
// fonksiyon çağrılırken argüman olarak string geçirilmelidir

void takeName(char *inpFile);


///////////////////////////////////////////////////////////////////////////////


// oyunun kaç adım devam edeceği sayısını kullanıcıdan alır
// fonksiyon argüman olarak int referans gönderilmelidir

void takeStep(int& stepNum);


///////////////////////////////////////////////////////////////////////////////


// oyun haritasının ölçülerini dosyadan okur
// okunan ilk değer satır ikinci değer sütun sayısıdır
// argüman olarak satır ve sütun sayıları için..
//.. 2 int pointer ve file pointer geçirilmelidir

void takeSize(FILE *mapFile, int *row, int *col);

///////////////////////////////////////////////////////////////////////////////


// dosyadan haritayı okur memory de ayrılmış olan alana yazar
// argüman olarak file pointer, dinamik memory pointerı..
// .. ve satır ve sütun sayıları fonksiyona verilmelidir

void takeMap(FILE *mapFile, char **table, int row, int col);

///////////////////////////////////////////////////////////////////////////////


// Ölüm yasam olaylarının kontrol edileceği allocate edlimiş hafızayı
// doldurmaya yarayan fonksiyon
// source tan aldığını dest in 1x1 indislerinden başyarak tam ortasına yazar	



void fillRealArr(char **tableDest, char **tableSource, int row, int col);

///////////////////////////////////////////////////////////////////////////////





void fillEdges(char **table, int row, int col);

///////////////////////////////////////////////////////////////////////////////


// array e yazılmış haritaları ekrana yazar
// fonksiyona yazılacak array ve ölçüleri argüman..
// .. olarak verilmelidir

void printTable(char **table, int row, int col);

///////////////////////////////////////////////////////////////////////////////


// her bir hücre için yaşama ve ölüm fonksiyonlarını kontrol eder
// bunu yaparken controlLive fonksiyonundan gelen sonuca göre davranır
// argüman olarak geçici ve gerçek haritalara ek olarak satır ve sütun..
// .. sayılarını da alır

void controlEachCell(char **tableReal, char **tableTemp, int row, int col);

///////////////////////////////////////////////////////////////////////////////


// tek bir hücrenin yaşama ve ölüm durumunu kontrol ederek..
// .. bunun bilgisini return eder.
// argüman olarak kontrolün yapıldığı harita ve kontrolün..
// .. yapılacağı hücrenin koordinatlarını alır
// bu işlemi countLiveNB fonksiyonu kullanarak yapar
// 
// yaşayan bir hücre için sonuç yaşamaya devam etmesi yönünde ise 1
// aksi halde 0 return eder
//
// ölü bir hücrenin canlanması durumunda 3 aksi halde 0 return eder

int controlLive(char **table, int currentRow, int currentCol);

///////////////////////////////////////////////////////////////////////////////



// argüman olarak satır sütun indisleri verilen hücrenin ..
// .. etrafındaki canlı hücre sayısını hesaplar..
// .. ve bu toplamı return eder.

int countLiveNB(char **table, int currentRow, int currentCol);

///////////////////////////////////////////////////////////////////////////////



// 2 harita arası eşitleme yapar
// ilk harita kaynak, ikinci harita hedef haritadır

void syncTables(char **tableSource, char **tableDest, int row, int col);

///////////////////////////////////////////////////////////////////////////////


// haritada herhangi bir canlı hücre kalıp kalmadığını kontrol eder

int isAllDead(char **table, int row, int col);

///////////////////////////////////////////////////////////////////////////////

// fonskiyona argüman olarak ölçüleriykle birlikte verilen diziyi
// string olarak ayrıca adı verilen dosyaya yazar

void write2File(char *outFile, char **table, int row, int col);

///////////////////////////////////////////////////////////////////////////////


// girilen satır ve sütun sayısına göre 2 boyutlu..
// .. char array için hafızada yer açar ve bu yerin..
// .. başlangıç adresini return eder.

char **memAlloc(int row, int col);

///////////////////////////////////////////////////////////////////////////////


void freeMem(char **table, int row);


int main()
{
	const int NAME_SIZE = 50;	
	int stepNum=0;
	int row=0, col=0;
	char inpFile[NAME_SIZE], outFile[NAME_SIZE];
	char **tableReal, **tableTemp, **tableStart;
	FILE *mapFile;
	
	
	cout <<"Enter the file name\n";
	
	//gecerli bir dosya adı girilene kadar isim istenir
	do
	{
		takeName(inpFile);	
		
		if((mapFile = fopen(inpFile, "r")) == NULL)
			cout << "The file does not exist\n"
				 << "TRY AGAIN !!\n";
			 
	}while((mapFile = fopen(inpFile, "r")) == NULL);
	
	cout <<"Enter the step number\n";
	takeStep(stepNum);
	
	// dosyadan board un olculeri okunur
	takeSize(mapFile, &row, &col);
	
	// Kullanılacak 3 array için yer alınır
	tableReal = memAlloc(row+2, col+2);
	tableTemp = memAlloc(row+2, col+2);
	tableStart = memAlloc(row, col);
	
	// dosyadan board okunur ve baslangıc arrayine yazılır
	takeMap(mapFile, tableStart, row, col);
	
	// dosya ile islem yapılamayacaı için kapatılır
	fclose(mapFile);
	
	
	// asıl islem yapılacak arraylerin kenarları doldurulur
	fillEdges(tableReal, row+2, col+2);
	fillEdges(tableTemp, row+2, col+2);
	
	// daha sonra ortalarına board un kendisi yazılır
	fillRealArr(tableReal, tableStart, row, col);
	fillRealArr(tableTemp, tableStart, row, col);
	
	// artık kullnılmayacak olan baslangıc arrayinin hafıazsı free edilir
	freeMem(tableStart, row);
	
	// board lar arası eşitleme işlemi yapılır
	syncTables(tableReal, tableTemp, row+2, col+2);
	
	
	/////////////////////////////////////////////////////////////////////////////
	//	OYUN BASLAR
	
	
	cout << "FIRST STATE\n";
	printTable(tableReal, row+2, col+2);
	cout << "\n\n";
	
	getchar();
	for(int i=0; i < stepNum; ++i)
	{
		cout << "STEP " << i+1	 <<endl;
		controlEachCell(tableReal, tableTemp, row+2, col+2);
		printTable(tableReal, row+2, col+2); cout << endl;
		syncTables(tableReal, tableTemp, row+2, col+2);
		
		if(i != stepNum-1)
			getchar();
	}
	
	
	// kayıt icin dosya adı alınır kaydetme islemi yapılır
	cout << "Please enter file name for saving data (as a txt file)\n";
	cin  >> outFile;
	write2File(outFile, tableReal, row+2, col+2);

	// kullanılan diger hafızalar da free edilir
	freeMem(tableReal, row+2);
	freeMem(tableTemp, row+2);
	
	return 0;
}


/****************************************************************************
 * 																			*
 *				 				FUNCTIONS									*
 * 																			*
 * **************************************************************************/


void takeName(char *inpFile)
{
	cin >> inpFile;
}



void takeStep(int& stepNum)
{
	char step[50];
	
	do
	{
		cin >> step;

		stepNum = atoi(step);
		
		if(stepNum == 0)
			cout << "Entered wrong step number try again.." << endl;
		
	}while(stepNum == 0);
		
}



void takeSize(FILE *mapFile, int *row, int *col)
{
	fscanf(mapFile, "%d %d", row, col);
}


void fillEdges(char **table, int row, int col)
{
	for(int i=0; i < col; ++i)
	{
		table[0][i] = '.';
		table[row-1][i] = '.';
	}
	
	for(int i=0; i < row; ++i)
	{
		table[i][0] = '.';
		table[i][col-1] = '.';
	}
	
	
}


void fillRealArr(char **tableDest, char **tableSource, int row, int col)
{
	
	for(int i=1, m=0; i < row+1 && m < row; ++i, ++m)
		for(int j=1, n=0; j < col+1 && n < col; ++j, ++n)
			tableDest[i][j] = tableSource[m][n];	
}



void takeMap(FILE *mapFile, char **table, int row, int col)
{
	char temp[col*2];
	int i=0;
	
	fgets(temp, sizeof(temp), mapFile);
	do
	{
		if(!feof(mapFile) && i!= row)
		{
			fgets(temp, sizeof(temp), mapFile);
			strncpy(table[i], temp, col);
			++i;
		}
			
	}while(!feof(mapFile) && i != row);
}



void printTable(char **table, int row, int col)
{
	for(int i=1; i < row-1; ++i)
	{
		for(int j=1; j < col-1; ++j){
			cout << table[i][j];
			//getchar();
		}
		cout << endl;
	}
}


void controlEachCell(char **tableReal, char **tableTemp, int row, int col)
{
	int liveOrDead= -1;
	
	
	for(int i=1; i < row-1; ++i)
	{
		for(int j=1; j < col-1; ++j) //değiştirilebilir
		{
			liveOrDead = controlLive(tableTemp, i, j);
			
			if(tableTemp[i][j] == 'X' && liveOrDead == 0)				
				tableReal[i][j] = '.';
				//cout <<liveOrDead <<" yeap" <<endl;
			
			if(tableTemp[i][j] == '.' && liveOrDead == 3)
				tableReal[i][j] = 'X';
		}
	}
}


int controlLive(char **table, int currentRow, int currentCol)
{
	int result=-1;
	
	result = countLiveNB(table, currentRow, currentCol);
	
	if(table[currentRow][currentCol] == 'X')
	{	
		if(result == 2 || result == 3)
			return 1;
		else 
			return 0;	
	}
	else
	{
		if(result == 3)
			return 3;
		else
			return 0;
	}
}


int countLiveNB(char **table, int currentRow, int currentCol)
{
	int counter = 0;
	
	if (table[currentRow-1][currentCol-1] == 'X')
		counter++;
	if (table[currentRow-1][currentCol] == 'X')
		counter++;
	if (table[currentRow-1][currentCol+1] == 'X')
		counter++;
	if (table[currentRow][currentCol-1] == 'X')
		counter++;
	if (table[currentRow][currentCol+1] == 'X')
		counter++;
	if (table[currentRow+1][currentCol-1] == 'X')
		counter++;
	if (table[currentRow+1][currentCol] == 'X')
		counter++;
	if (table[currentRow+1][currentCol+1] == 'X')
		counter++;
		
	
	
	return counter;
}




int isAllDead(char **table, int row, int col)
{
	for(int i=0; i < row; ++i)
		for(int j=0; j < col; ++j)
			if(table[i][j] == 'X')
				return 0;
	
	return 1;
}


void write2File(char *outFile, char **table, int row, int col)
{
	FILE *outputFile;
	
	outputFile = fopen(outFile, "w");
	
	for(int i=1; i < row-1; ++i)
		fprintf(outputFile, "%s\n", table[i]);			
	
	fclose(outputFile);
}


void syncTables(char **tableSource, char **tableDest, int row, int col)
{
	for(int i=0; i < row; ++i)
		for(int j=0; j < col; ++j) 
			tableDest[i][j] = tableSource[i][j];
}

char **memAlloc(int row, int col)
{
	char **allocated;
	
	allocated = static_cast<char**>(malloc(sizeof(char *)*row));

	for(int i=0; i < row; ++i)
		allocated[i] = static_cast<char*>(malloc(sizeof(char)*col));
	
	return allocated;
}


void freeMem(char **table, int row)
{
	for(int i=0; i < row; ++i)
		free(table[i]);
	
	free(table);
}
