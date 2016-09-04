/*******************************************************************************************************/
/*																									   */
/*										Emrah YILDIRIM 111044056									   */
/*																									   */
/*  Verilen bir klasorde , tum alt dosya ve klasorleri tarayarak farklı kelime sayisini bulan program  */
/*	Her dosya icin thread her klasor icin process olusturularak										   */
/*  USAGE : ./newWordCount dirName																	   */
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
#include <sys/ipc.h>
#include <dirent.h>
#include <pthread.h>
#include <semaphore.h>
#include <setjmp.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <sys/shm.h>



#define FILE_COUNTER	0
#define FILE_FINDER		1

#define PERMS (mode_t)(S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)
#define FLAGS O_CREAT | O_EXCL


typedef struct 
{
	char w[50];
	int count;
}word;

typedef struct 
{
	char name[2000];
	long int sec;
	long int usec;
}folder_t;


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

void timeArrange(char * path, long int sec, long int usec);

int wrapper(char * mainDir);

void sort(char **array, int size);

void getPath(char *source, char *dest);

void fillFolders(char **files, int size);

int folderExist(char * name);



/********************************************************************************************************/

word *all;
folder_t *folders;
int allFolderSize=1;
FILE * outFile;
int file=0, folder=0, total = 0;
char **files;
int *allsize;
int REC = 0;
//pthread_mutex_t mut;
sem_t mut; //semaphore
int shmid1, shmid2, shmid3; //shared memory ids
key_t key1, key2, key3; //shared memory keys


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

//   mut = sem_open ("sem", O_CREAT | O_EXCL, 0644, FLAGS);


    key1 = 2155845;
    key2 = 1587452;
    key3 = 1245874;


	wrapper(argv[1]);

		if (shmctl(shmid1, IPC_RMID, NULL) == -1)
			perror("[main-error]Failed to remove memory segment");
		if (shmctl(shmid2, IPC_RMID, NULL) == -1)
	perror("[main-error]Failed to remove memory segment");
		if (shmctl(shmid3, IPC_RMID, NULL) == -1)
	perror("[main-error]Failed to remove memory segment");
	sem_destroy(&mut);
	return 0;
}


void * process(void * args)
{
	struct timeval startTime, finishTime, diffTime;
	

	int size = 0;
	char *fileName = (char*)(args);
 

	gettimeofday(&startTime, NULL);

	word * words = (word*)(calloc(findWordNumber(fileName), sizeof(word)));
	getWords(fileName, &size, words);

// printf("in thread %d\n",size );

	gettimeofday(&finishTime, NULL);
	mergeAllWords(all, words, allsize, size);

	fprintf(outFile, "%ld tid found %d different words in %s\n", (long)(pthread_self()), size, fileName);
	fprintf(stdout, "%ld tid found %d different words in %s\n", (long)(pthread_self()), size, fileName);
	
	timersub(&finishTime, &startTime, &diffTime); //zamanı hesapla


	timeArrange(fileName, (long int)diffTime.tv_sec , (long int)diffTime.tv_usec);
   


	free(words);

}


//zamani kaydeder
void timeArrange(char * path, long int sec, long int usec)
{
	int i, index;

	for (i = 0; i < allFolderSize; ++i)
	{
		if(strncmp(path, folders[i].name, strlen(folders[i].name)) == 0 )
		{
			folders[i].sec += sec;
			folders[i].usec += usec;
		}
	}

}

//klasor kontrolu yapar
int folderExist(char * name)
{	
	int i;
	for (i = 0; i < allFolderSize; ++i)
	{
		if(strcmp(name, folders[i].name) == 0)
		{			
			return 0;
		}
	}
	return 1;

}
/*******************************************************************************************************/
/*										FUNCTION DEFINITIONS										   */
/*******************************************************************************************************/

int wrapper(char * mainDir)
{
	int size=0, i, j;

	files = findAllFilesWrapper(mainDir, &file, &folder);
	if(folder = 0) folder = 1;
//	all = (word*)(calloc(file * 200, sizeof(word)));
//	folders = (folder_t *)(calloc(file, sizeof(folder_t)));


	freeMem(files, file);
	REC = 1;



//shared memory olustur
  	if ((shmid1 = shmget (key1, sizeof(word)*file*200, 0644 | IPC_CREAT)) == -1) 
  	{
	   perror("shmget: shmget failed");
	   exit(1); }
	else
	{
	 //  fprintf(stderr, "shmget: shmget returned %d\n", shmid1);
//	   all = (word*)shmat(shmid1, NULL, 0);

  	}


  	if ((shmid2 = shmget (key2, sizeof(folder_t)*file, 0644 | IPC_CREAT)) == -1) 
  	{
	   perror("shmget: shmget failed"); exit(1); }
	else
	{
	  // fprintf(stderr, "shmget: shmget returned %d\n", shmid2);
	   folders = (folder_t*)shmat(shmid2, NULL, 0);
	   strcpy(folders[0].name, mainDir);
  	}

  	if ((shmid3 = shmget (key3, sizeof(int), 0644 | IPC_CREAT)) == -1) 
  	{
	   perror("shmget: shmget failed"); exit(1); }
	else
	{
	  // fprintf(stderr, "shmget: shmget returned %d\n", shmid2);
  	}



	file=0;
	folder=0;
	files = findAllFilesWrapper(mainDir, &file, &folder);
	shmdt(folders); //attach

	outFile = fopen("log.txt", "w");
	fprintf(outFile, "Started\n");


	pid_t pids[allFolderSize];
	for(i=0; i < allFolderSize; ++i)
	{
		
		pid_t pid = fork();
		pids[i] = pid;
		if(pid == 0)
		{
		 	if ( sem_init(&mut, 0, 1) )
	   		{
		        printf("\n mutex init failed\n");
		        return 1;
	    	}

			sem_wait(&mut);
			folders = (folder_t*)shmat(shmid2, NULL, 0);
			all = (word *)(shmat(shmid1, NULL, 0));
			allsize = (int *)(shmat(shmid3, NULL, 0));

			
			pthread_t childTids[file]; //check
			int j,tindex=0;
			for(j=0; j < file; ++j)
			{

				if(strncmp(files[j], folders[i].name, strlen(folders[i].name)) == 0)
				{
					pthread_create(&childTids[tindex++], NULL, process, files[j]);
					
				}
			}

			for(j=0; j < tindex; ++j)
			{
				pthread_join(childTids[j], NULL);
			}
			


			freeMem(files, file);
			fclose(outFile);
			sem_post(&mut);
			sem_destroy(&mut);
	
			shmdt(all);
			shmdt(allsize);
			shmdt(folders);
			exit(0);
		}
		else if(pid == -1)
		{                                                
			perror("fork error");
			exit(-1);
		}
	}


	//wait for all child process
	for (i = 0; i < allFolderSize; ++i)
	{
		waitpid(pids[i], NULL, 0);
	}

		
	folders = (folder_t*)shmat(shmid2, NULL, 0);
	all = (word *)(shmat(shmid1, NULL, 0));
	allsize = (int *)(shmat(shmid3, NULL, 0));




//bilgi yazimlari
	fprintf(stdout, "\nPID number for each folder\n");
	fprintf(outFile, "\nPID number for each folder\n");
	for (i = 0; i < allFolderSize; ++i)
	{
		printf("%s %06ld\n",  folders[i].name, (long int)pids[i]);
		fprintf(outFile, "%s %06ld\n",  folders[i].name, (long int)pids[i]);

	}




	fprintf(outFile, "\n\n%d different word found in %d file(s) and %d folder(s)\n\n\n", *allsize , file, folder);	
	printf("\n\n%d different word found in %d file(s) and %d folder(s)\n\n\n",  *allsize , file, folder);	

	for (i = 0; i < *allsize; ++i)
	{
		fprintf(outFile, 	"%d     %s\n",  all[i].count, all[i].w);
		printf("%d     %s\n",  all[i].count, all[i].w);

	}

	fprintf(stdout, "\nELAPSED TIMES FOR EACH FOLDER\n");
	fprintf(outFile, "\n\nELAPSED TIMES FOR EACH FOLDER\n");
	for (i = 0; i < allFolderSize; ++i)
	{
		printf("%s %ld.%06ld\n",  folders[i].name, (long int)folders[i].sec, (long int)folders[i].usec);
		fprintf(outFile, "%s %ld.%06ld\n",  folders[i].name, (long int)folders[i].sec, (long int)folders[i].usec);

	}






	shmdt(allsize);
	shmdt(folders);
	shmdt(all);
	freeMem(files, file);
	fclose(outFile);



}



//zamana gore siralama yapar
void sort(char **array, int size)
{
	int i,j;
	char *temp;
	for (i = 0; i < size; ++i)
		for (j = i; j < size; ++j)
			if(strcmp(array[i], array[j]) > 0)
			{
				temp = array[i];
				array[i] = array[j];
				array[j] = temp;
			}
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




//kelimeleri bulur ve arraye yazar
void getWords(const char *pChFileName, int *wordsize, word *words) //free
{
	FILE *pfInput = fopen(pChFileName, "r"); 
	int iMaxLine = findLongestLine(pfInput)+1;
	char *pChLine = (char*) (calloc(iMaxLine , sizeof(char)));

    long begin = ftell(pfInput);
    fseek(pfInput, 0, SEEK_END);

    if (ftell(pfInput) == 0)
    {
    	free(pChLine);
		fclose(pfInput);
        return;
    }

    fseek(pfInput, begin, SEEK_SET);


	*wordsize = 0;
	while((fgets(pChLine, iMaxLine, pfInput)) != NULL)
		wordNum4LineAndAdd(pChLine, iMaxLine, words, wordsize);

	free(pChLine);
	fclose(pfInput);
}
/*******************************************************************************************************/

//her satir icin kelime sayisi bulur
//eger kelime daha once bulunmussa counter++ yapar
//aksi halde ekler
int wordNum4LineAndAdd(const char *line, int size, word *words, int *wordsize)
{
	char *chpWord;
	char chaTemp[size];
	char chaDelim[10] = " \",.;:?\n"; //ayirma bolgelerini tanimla
	int iCounter=0;
	char *save;

	//yedek al
	strcpy(chaTemp, line);

	// yeni bir kelime al ve uygunlugunu kontrol et
	if((chpWord = strtok_r(chaTemp, chaDelim, &save)) != NULL )
		if(checkChar(chpWord, strlen(chpWord)))
		{
			findAndAdd(words, wordsize, chpWord);
			iCounter++; 

		}

	//satir sonuna kadar ayni isleme devam et
	while((chpWord = strtok_r(NULL, chaDelim, &save)) != NULL)
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

//tum kelimelerin bulundugu array e yeni bulunanlari ekler
//eger varsa counterlari toplar
//aksi halde ekleme yapar
void mergeAllWords(word *allWords, word* currentWords, int *allSize, int currentSize)
{
	int i, index;

	for (i = 0; i < currentSize; ++i)
	{
		if((index = isExist(allWords, *allSize, currentWords[i].w)) != -1 )
		{
			allWords[index].count += currentWords[i].count;	

		}
		else
		{

			word temp;
			temp.count = 0;
			strcpy(temp.w, currentWords[i].w);
			temp.count = currentWords[i].count;	
			allWords[*allSize] = temp;
			(*allSize)++;
		}
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
	{
		ppChAllFiles[i] = (char *)(calloc(2000 , sizeof(char)));
	}

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
					if(REC == 1 && folderExist(pChCurrentFilePath)) //klasor adlarini kaydet
					{
						strcpy(folders[allFolderSize++].name, pChCurrentFilePath);
						folders[allFolderSize].sec = 0;
						folders[allFolderSize].usec = 0;
					}

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
