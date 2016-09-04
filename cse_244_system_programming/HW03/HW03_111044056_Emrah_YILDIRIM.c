/*******************************************************************************************************/
/*																									   */
/*										Emrah YILDIRIM 111044056									   */
/*																									   */
/*  Verilen bir klasorde , tum alt dosya ve klasorleri tarayarak farklı kelime sayisini bulan program  */
/*  USAGE : ./newWordCount dirName																	   */
/*																									   */
/*******************************************************************************************************/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <errno.h>

#define FILE_COUNTER	0
#define FILE_FINDER		1

typedef struct 
{
	char w[50];
	int count;
}word;



/*******************************************************************************************************/
/*										FUNCTION PROTOTYPES											   */
/*******************************************************************************************************/

//kelime eger arrayde yoksa onu ekler ve count u bir artırır
int findAndAdd(word * words, int *size, char *target);

//aldigi kelimenin o arrayde olup olmadigina bakar
int isExist(word * words, int size, char *target);

//aldigi adresi free eder
void freeMem(char **ppChAlloc, int iSize);


// bir dosyadaki en uzun satirin boyutunu bulur ve return eder, FILE pointer alir
int findLongestLine(FILE *pfFile);

// bir kelime alir string olarak ve bizim kelime tanimimiza uygun olup olmadigini kontrol eder
// uygunsa 1 degilse 0 return eder
int checkChar(char *chpWord, int size);

// bir satirdaki toplam kelime sayisini bulur ve return eder, string alir
int wordNum4Line(const char *line, int size);

// bir satirdaki toplam kelime sayisini bulur ve return eder, string alir, bunları arraye kaydeder
int wordNum4LineAndAdd(const char *line, int size, word *words, int *wordsize);


// bir dosyadaki kelime sayisini bulur ve return eder, dosya yolu alir kelimeleri return eder
int findWordNumber(const char *pChFileName);


void getWords(const char *pChFileName, int *wordsize, word *words);



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

//aldigi birinci arraye 2. arryin kelimelerini ekler kelime zaten varsa count artırması yapar
void mergeAllWords(word *allWords, word* currentWords, int *allSize, int currentSize);

int wrapper(char * mainDir);


//pipe file descriptors
int fd[2];



/*******************************************************************************************************/
/*											MAIN FUNCTION											   */
/*******************************************************************************************************/
int main( int argc, char **argv)
{

	// 2 arguman olmali kesinlikle
	if(argc != 2)
	{
		fprintf(stderr, "\nTOO FEW OR TOO MANY ARGUMENTS\n");
		fprintf(stderr, "USAGE: ./newWordCount mainFolderName\n");
		fprintf(stderr, "EXAMPLE: ./newWordCount myMainFolder\n\n");
		exit(0);
	}
	else
	{
		//klasorun acilip acilmama kontrolu
		DIR *pdrDir = opendir(argv[1]);
		if(pdrDir == NULL)
		{
			fprintf(stderr, "\n\"%s\" DOES NOT EXIST\n", argv[1]);
			fprintf(stderr, "USAGE: ./newWordCount mainFolderName\n");
			fprintf(stderr, "EXAMPLE: ./newWordCount myMainFolder\n\n");
		//	closedir(pdrDir);
			exit(0);
		}
		else
			closedir(pdrDir);
	}

	wrapper(argv[1]);

	return 0;
}


/*******************************************************************************************************/
/*										FUNCTION DEFINITIONS										   */
/*******************************************************************************************************/

int wrapper(char * mainDir)
{
	int size=0, i, j;
	int file=0, folder=0,allsize=0, total = 0;

	char **files = findAllFilesWrapper(mainDir, &file, &folder);
	word *all = (word*)(calloc(file * 200, sizeof(word)));

	FILE * outFile = fopen("log.txt", "w");

	pid_t pid;


	for (i = 0; i < file; ++i)
	{
		if(pipe(fd) == -1)
		{
			perror("Pipe Error !!");
			freeMem(files, file);
			free(all);
			fclose(outFile);

			exit(-1);
		}
		pid = fork();

		if(pid == -1)
		{
			perror("Fork Error !!");
			freeMem(files, file);
			free(all);
			fclose(outFile);
			exit(-1);
		}
		else if(pid == 0)
		{
			int size = 0;
			word * words = (word*)(calloc(findWordNumber(files[i]), sizeof(word)));

			getWords(files[i], &size, words);

			//printf("child %d\n", size);
		//	printf("child %d  parent %d\n", getpid(), getppid());
			close(fd[0]);

			write(fd[1], &size, sizeof(int));
			write(fd[1], words, sizeof(word) * size);

			free(words);
			freeMem(files, file);
			free(all);
			fclose(outFile);

			close(fd[1]);
			exit(0);
		}
		else
		{
			int temp = 0;			

			close(fd[1]);
			read(fd[0], &temp, sizeof(int));
			word *words = (word *)(calloc(temp, sizeof(word)));
			read(fd[0], words, sizeof(word) * temp);

			mergeAllWords(all, words, &allsize, temp);
		//	printf("parent %s\n", words[0].w);
			close(fd[0]);
			free(words);

			
		}



	}

	fprintf(outFile, "%d different word found in %d file(s) and %d folder(s)\n\n\n", allsize , file, folder);	

	for (i = 0; i < allsize; ++i)
	{
		fprintf(outFile, 	"%d     %s\n",  all[i].count, all[i].w);

	}


	fclose(outFile);
	free(all);
	freeMem(files, file);



}



/*******************************************************************************************************/

int findWordNumber(const char *pChFileName) //free
{
	FILE *pfInput = fopen(pChFileName, "r"); 
	int iMaxLine = findLongestLine(pfInput)+1;
	char *pChLine = (char*) (calloc(iMaxLine , sizeof(char)));
	int iTotalWords=0;

	// dosya sonu olana kadar satir satir oku
	// her satiri kelime sayan fonksiyona gonder
	while((fgets(pChLine, iMaxLine, pfInput)) != NULL)
		iTotalWords += wordNum4Line(pChLine, iMaxLine);

	free(pChLine);
	fclose(pfInput);
	return iTotalWords;
}




void getWords(const char *pChFileName, int *wordsize, word *words) //free
{
	FILE *pfInput = fopen(pChFileName, "r"); 
	int iMaxLine = findLongestLine(pfInput)+1;
	char *pChLine = (char*) (calloc(iMaxLine , sizeof(char)));

	*wordsize = 0;
	while((fgets(pChLine, iMaxLine, pfInput)) != NULL)
		wordNum4LineAndAdd(pChLine, iMaxLine, words, wordsize);

	free(pChLine);
	fclose(pfInput);
}
/*******************************************************************************************************/

int wordNum4LineAndAdd(const char *line, int size, word *words, int *wordsize)
{
	char *chpWord;
	char chaTemp[size];
	char chaDelim[10] = " \",.;:?\n"; //ayirma bolgelerini tanimla
	int iCounter=0;

	//yedek al
	strcpy(chaTemp, line);

	// yeni bir kelime al ve uygunlugunu kontrol et
	if((chpWord = strtok(chaTemp, chaDelim)) != NULL )
		if(checkChar(chpWord, strlen(chpWord)))
		{
			findAndAdd(words, wordsize, chpWord);
			iCounter++; 

		}

	//satir sonuna kadar ayni isleme devam et
	while((chpWord = strtok(NULL, chaDelim)) != NULL)
		if (checkChar(chpWord, strlen(chpWord)))
		{
			findAndAdd(words, wordsize, chpWord);
			iCounter++; 

		}

	
	// kelime sayisini return et
	return iCounter;
}




/**********************************************************************************/
/*sayma islemleri*/



int wordNum4Line(const char *line, int size)
{
	char *chpWord;
	char chaTemp[size];
	char chaDelim[10] = " \",.;:?\n"; //ayirma bolgelerini tanimla
	int iCounter=0;

	//yedek al
	strcpy(chaTemp, line);

	// yeni bir kelime al ve uygunlugunu kontrol et
	if((chpWord = strtok(chaTemp, chaDelim)) != NULL )
		if(checkChar(chpWord, strlen(chpWord)))
			iCounter++; 

	//satir sonuna kadar ayni isleme devam et
	while((chpWord = strtok(NULL, chaDelim)) != NULL)
		if (checkChar(chpWord, strlen(chpWord)))
			iCounter++; 
	
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


/*******************************************************************************************************/

void freeMem(char **ppChAlloc, int iSize)
{
	int i = 0;

	for(i = 0; i < iSize; ++i)
	{
		free(ppChAlloc[i]);
	}
	free(ppChAlloc);

}


/*******************************************************************************************************/



//varsa kelime index return eder yoksa -1
int isExist(word * words, int size, char *target)
{
	int i;
	for (i = 0; i < size; ++i)
	{
		if(strcmp(words[i].w, target) == 0)
			return i;
	}

	return -1;
}

/*******************************************************************************************************/

//eger kelime varsa counter artar yoksa en sona ekler ve counter artar
int findAndAdd(word * words, int *size, char *target)
{
	int i = 0, index = -99;



	if((index = isExist(words, *size, target)) != -1 )
	{
		words[index].count++;		
		return index;
	}


	word temp;
	temp.count = 0;
	strcpy(temp.w, target);
	temp.count++;
	words[*size] = temp;
	(*size)++;

	return *size - 1; 

}


/*******************************************************************************************************/

void mergeAllWords(word *allWords, word* currentWords, int *allSize, int currentSize)
{
	int i;

	for (i = 0; i < currentSize; ++i)
	{
		findAndAdd(allWords, allSize, currentWords[i].w);
	}

}


/*******************************************************************************************************/

char ** findAllFilesWrapper(char *pChDir, int *iNumOfFiles, int *iNumOfFolders)
{
	char **ppChAllFiles;
	int iIndex=0;
	int i,j,k;

	//dosya sayisini bul
	findAllFiles(pChDir, NULL, iNumOfFiles, FILE_COUNTER, &iIndex, iNumOfFolders );
	//dosya sayisina gore yer alma
	ppChAllFiles = (char **)(calloc(*iNumOfFiles , sizeof(char *)));
	for(i = 0; i < *iNumOfFiles; ++i)
		ppChAllFiles[i] = (char *)(calloc(2000 , sizeof(char)));

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
	char *pChCurrentFilePath = '\0';
	pChCurrentFilePath = (char *)(calloc(2000 , sizeof(char)));


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
