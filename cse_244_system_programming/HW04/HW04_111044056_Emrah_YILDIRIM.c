/*******************************************************************************************************/
/*																									   */
/*										Emrah YILDIRIM 111044056									   */
/*																									   */
/*  Verilen bir klasorde bulunan, tum alt dosya ve klasorleri tarayarak kelime sayisini thread 		   */
/*	kullanarakbulan program  																			*/
/*  USAGE : ./wordcount dirName																		   */
/*																									   */
/*******************************************************************************************************/


#include <time.h>
#include <math.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <setjmp.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <dirent.h>
#include <pthread.h>

#define FILE_COUNTER	0
#define FILE_FINDER		1


/*******************************************************************************************************/
/*										FUNCTION PROTOTYPES											   */
/*******************************************************************************************************/


// bir dosyadaki kelime sayisini bulur ve return eder, dosya yolu alir
int findWordNumber(const char *pChFileName);

// bir dosyadaki en uzun satirin boyutunu bulur ve return eder, FILE pointer alir
int findLongestLine(FILE *pfFile);

// bir kelime alir string olarak ve bizim kelime tanimimiza uygun olup olmadigini kontrol eder
// uygunsa 1 degilse 0 return eder
int checkChar(char *chpWord, int size);

// bir satirdaki toplam kelime sayisini bulur ve return eder, string alir
int wordNum4Line(const char *line, int size);

//verilen klasordeki dosyalari bulur
//dir : klasor yoludur
//allFiles: istege gore dosya adlarinin yazilacagi string arrayidir
//iNumOfFiles: tum dosyalarin sayisidir
//iForWhat: fonksiyonun yapacagi isi belirtir(1 ise bulur ve dosya yollarini stringe atar, 0 ise sadece sayim yapar)
//index: string arrayinin o anki indeksidir
int findAllFiles(char *pChDir, char **ppChAllFiles, int *iNumOfFiles, int iForWhat, int *iIndex, int *iNumOfFolders);


//findAllFiles fonksiyonuna gerekli argümanlar sağlar
// dosya adlarinin bulundugu string dizisinin pointer ini return eder
char ** findAllFilesWrapper(char *pChDir, int *iNumOfFiles, int *iNumOfFolders);

//aldigi adresi free eder
void freeMem(void **ppChAlloc, int iSize);
//ana fonksiyondur
int findAndPrintAllThings(char *pdrMainDir);
int getTotalWordNumber();

//thread in yapacagi fonksiyon
//dosya yolu alir
void *process(void *args);

//toplam kelime sayisi icin global degisken 
int totalWordNumber = 0;





/*******************************************************************************************************/
/*											MAIN FUNCTION											   */
/*******************************************************************************************************/


int main(int argc, char **argv)
{
	// 2 arguman olmali kesinlikle
	if(argc != 2)
	{
		fprintf(stderr, "\nTOO FEW OR TOO MANY ARGUMENTS\n");
		fprintf(stderr, "USAGE: ./wordcount mainFolderName\n");
		fprintf(stderr, "EXAMPLE: ./wordcount myMainFolder\n\n");
		exit(0);
	}
	else
	{
		//klasorun acilip acilmama kontrolu
		DIR *pdrDir = opendir(argv[1]);
		if(pdrDir == NULL)
		{
			fprintf(stderr, "\n\"%s\" DOES NOT EXIST\n", argv[1]);
			fprintf(stderr, "USAGE: ./wordcount mainFolderName\n");
			fprintf(stderr, "EXAMPLE: ./wordcount myMainFolder\n\n");
			closedir(pdrDir);
			exit(0);
		}
		else
			closedir(pdrDir);
	}

	// baslat
	int iFileNumber=0, iFolderNumber=0;
	char **pChtemp =findAllFilesWrapper(argv[1] ,&iFileNumber, &iFolderNumber);
	freeMem((void **)pChtemp, iFileNumber);

	system("clear");
	findAndPrintAllThings(argv[1]);

	printf("--------------------------------------------------------------------------------------------\n");
	printf("\n\"%d\" subfolder(s) and \"%d\" file(s) has been found\n", iFolderNumber, iFileNumber);
	printf("\"%d\" word has found ind \"%d\" file(s)\n\n", totalWordNumber, iFileNumber);

	return 0;
}




/*******************************************************************************************************/
/*										FUNCTION DEFINITIONS										   */
/*******************************************************************************************************/

int findAndPrintAllThings(char *pdrMainDir)
{
	struct timeval startTime, finishTime, diffTime;

	gettimeofday(&startTime, NULL);
	char **pPChFiles;
	int iNumOfFiles=0, iNumOfFolders=0;
	int i;

	// dosya isimlerini al
	pPChFiles = findAllFilesWrapper(pdrMainDir ,&iNumOfFiles, &iNumOfFolders);
	pthread_t tid[iNumOfFiles];

	printf("\n------------------------------------- FILEs AND Thread IDs ---------------------------------------\n");
	//her file icin thread olustur be id lerini kaydet
	for(i=0; i < iNumOfFiles; ++i)
	{
		pthread_create(&tid[i], NULL, process, pPChFiles[i]);
	}

	//olusturulan her thread i bekle
	for(i=0; i < iNumOfFiles; ++i)
	{
		pthread_join(tid[i], NULL);
	}

	gettimeofday(&finishTime, NULL);
	timersub(&finishTime, &startTime, &diffTime);

	fprintf(stderr,"--------------------------------------------------------------------------------------------\n");
	fprintf(stderr, "Time elapsed: %ld.%06ld\n", (long int)diffTime.tv_sec, (long int)diffTime.tv_usec);
	freeMem((void **)pPChFiles, iNumOfFiles);
	return 0;
}

/*******************************************************************************************************/

//thread e yaptirilicak fonksiyon
void *process(void *args)
{
	int iCurrentNumber=0;
	char *file = (char*)(args); // arguman olarak gelen dosay adini karakter ptr ye cast et

	// dosyadan kelime sayisi bulan fonksiyonu cagir
	iCurrentNumber = findWordNumber(file);
	totalWordNumber += iCurrentNumber;

	fprintf(stderr, "ThreadID: %5ld  --  %d word in %-41s\n", (long)pthread_self(),iCurrentNumber, file);
}


char ** findAllFilesWrapper(char *pChDir, int *iNumOfFiles, int *iNumOfFolders)
{
	char **ppChAllFiles;
	int iIndex=0;
	int i,j,k;

	//dosya sayisini bul
	findAllFiles(pChDir, NULL, iNumOfFiles, FILE_COUNTER, &iIndex, iNumOfFolders );
	//dosya sayisina gore yer alma
	ppChAllFiles = (char **)(malloc(*iNumOfFiles * sizeof(char *)));
	for(i = 0; i < *iNumOfFiles; ++i)
		ppChAllFiles[i] = (char *)(malloc(2000 * sizeof(char)));

	//dosya isimlerini al stringe kaydet
	*iNumOfFiles = 0;
	*iNumOfFolders = 0;
	findAllFiles(pChDir, ppChAllFiles, iNumOfFiles,FILE_FINDER, &iIndex, iNumOfFolders );

	//dosya isimlerini return et
	return ppChAllFiles;
}


/*******************************************************************************************************/
int findAllFiles(char *pChDir, char **ppChAllFiles, int *iNumOfFiles, int iForWhat, int *iIndex, int *iNumOfFolders)
{
	DIR *pdrMainDir;	
	struct dirent *pDrntCurrentFile;
	char *pChCurrentFilePath = (char *)(malloc(2000 * sizeof(char)));


	// ana klasor acilma kontrol
	if((pdrMainDir = opendir(pChDir)) != NULL)
	{
		//acilabilir dosya var mi kontrol et
		while((pDrntCurrentFile = readdir(pdrMainDir)) != NULL)
		{
			if(pDrntCurrentFile->d_type == DT_REG) //regular dosya kontrolu
			{
				//dosya adini path e donustur
				sprintf(pChCurrentFilePath, "%s/%s", pChDir,pDrntCurrentFile->d_name);
				if(iForWhat) // kayit isteniyorsa stringe at
				{
					strcpy(ppChAllFiles[*iIndex], pChCurrentFilePath);
					(*iIndex)++;
				}
				
				(*iNumOfFiles)++;
			}
			else if(pDrntCurrentFile->d_type == DT_DIR) //directory kontrolu
			{
				// ozel durumlari kontrol et
				if(strcmp(pDrntCurrentFile->d_name, ".") && strcmp(pDrntCurrentFile->d_name, ".."))
				{
					//dosya adini path e donustur
					sprintf(pChCurrentFilePath, "%s/%s", pChDir,pDrntCurrentFile->d_name);
					(*iNumOfFolders)++;
					//yeni bir directory oldugu icin recursion cagri yap
					findAllFiles(pChCurrentFilePath, ppChAllFiles, iNumOfFiles, iForWhat, iIndex, iNumOfFolders);
				}
			}
		}
	}
	else //dosya acilmadi ise hata ver ve cik
	{
		fprintf(stderr, "%s could not open\n", pChDir);
		free(pChCurrentFilePath);

		exit(0);
	}
	closedir(pdrMainDir);
	free(pChCurrentFilePath);
	return 0;
}






/*******************************************************************************************************/
int findWordNumber(const char *pChFileName)
{
	FILE *pfInput = fopen(pChFileName, "r"); 
	int iWordCounter;
	int iMaxLine = findLongestLine(pfInput)+1;
	char *pChLine = (char*) (malloc(iMaxLine * sizeof(char)));
	int iTotalWords=0;


    long begin = ftell(pfInput);
    fseek(pfInput, 0, SEEK_END);

    if (ftell(pfInput) == 0)
    {
    	free(pChLine);
		fclose(pfInput);
        return 0;
    }

    fseek(pfInput, begin, SEEK_SET);


	// dosya sonu olana kadar satir satir oku
	// her satiri kelime sayan fonksiyona gonder
	while((fgets(pChLine, iMaxLine, pfInput)) != NULL)
	{
		iTotalWords += wordNum4Line(pChLine, iMaxLine);
	}

	free(pChLine);
	fclose(pfInput);
	return iTotalWords;
}


/*******************************************************************************************************/
int wordNum4Line(const char *line, int size)
{
	char *chpWord;
	char *chaTemp = (char *)(calloc(size, sizeof(char)));
	char chaDelim[10] = " \",.;:?\n"; //ayirma bolgelerini tanimla
	int iCounter=0;
	char *save;

	//yedek al
	strcpy(chaTemp, line);

	// yeni bir kelime al ve uygunlugunu kontrol et
	if((chpWord = strtok_r(chaTemp, chaDelim, &save)) != NULL )
		if(checkChar(chpWord, strlen(chpWord)))
			iCounter++; 

	//satir sonuna kadar ayni isleme devam et
	while((chpWord = strtok_r(NULL, chaDelim, &save)) != NULL)
		if (checkChar(chpWord, strlen(chpWord)))
			iCounter++; 
	
	free(chaTemp);
	// kelime sayisini return et
	return iCounter;
}


/*******************************************************************************************************/
int checkChar(char *chpWord, int size)
{
	int i = 0;

	// saf kelime kontrolu
	for(i = 0; chpWord[i] != '\0'; ++i)
	{
		if( !(chpWord[i] >= 'A' && chpWord[i] <= 'Z') &&
		    !(chpWord[i] >= 'a' && chpWord[i] <= 'z')  )
		    return 0;
	}
				
	return 1;
}


/*******************************************************************************************************/
int findLongestLine(FILE *pfFile)
{
	int counter = 0, max=-1;
	char ch;

	//dosya sonuna kadar satir satir uzunluk kotrolu
	while((fscanf(pfFile, "%c", &ch)) != EOF)
	{
		if(ch != '\n' )
			counter++;
		else
		{
			if(max < counter)
				max = counter;
			counter = 0;
		}

	}

	if(max < counter)
		max = counter;

	//dosyanin basina geri don
	rewind(pfFile);
	return max;
}



int getTotalWordNumber()
{
	FILE *inp = fopen("res", "r");
	int iTotal=0,count=0;

	while(fscanf(inp,"%d", &count) != EOF)
		iTotal += count;

	fclose(inp);
	remove("res");
	return iTotal;
}

/*******************************************************************************************************/

void freeMem(void **ppChAlloc, int iSize)
{
	int i = 0;

	for(i = 0; i < iSize; ++i)
	{
		free(ppChAlloc[i]);
	}
	free(ppChAlloc);

}


/*******************************************************************************************************/