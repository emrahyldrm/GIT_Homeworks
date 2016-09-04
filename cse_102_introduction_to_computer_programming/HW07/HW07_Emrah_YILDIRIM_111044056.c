/*##########################################################################*
*HW07_111044056.c															*
*Emrah YILDIRIM tarafýndan 23.04.2014 tarihinde yazýldý						*
*																			*
*****************************************************************************
*																			*
* -------------------------------TANIM--------------------------------------*
* GYTE versiyon dama oyunu													*
* oyunun normal damadan farki konulmus engeller ve king olunca macin bitmesi*
* 																			*
*****************************************************************************
*-------------------------------DOSYALAR------------------------------------*
* INPUT >> Initial.txt:  basllangictaki taslarin yerleri					*
*		   Commands.txt: batch mode icin komut dosyasi(MAX 250 komut)		*
* OUTPUT>> anyName.txt: istenilen isimde oyunun son halinin kayit dosyasi	*
*		   anyName.log: istenilen isimde komutlarin kaydedilebildigi dosya	*
*																			*
*****************************************************************************
* ----------------------------CALISMA SEKLI---------------------------------*
* oyun kisa bir aciklama ve isimlerin alinmasi ile baslar					*
* oyunun galibi var mý diye konrol edilir, galip varsa bitirilir			*
* galibiyet kosullari king olmak ya da karsi tarafin tasinin olmamasidir	*
* galibiyet yopksa 1. oyuncu komutunu girer								*
* girilen komutun formati kontrol edilir yanlissa yeni komut istenir		*
* komut formati dogru ise devam edilir ve komutun mantiksal olarak..		*
*.. dogrulugu kontrol edilir. mantiksal birsorun yoksa komut gerceklenir	*
* komut yapildiktan sonra galbiyet kontrolu yapilir							*
* galip yoksa ayni islemler 2. oyuncu icinde yapilir.Dongu boyle devam eder *
*###########################################################################*/



 /***************************************************************************
 * KOMUT ALINIRKEN HARFLERIN BUYUK YA DA KUCUK OLMASI SORUN CIKARMASIN DIYE *
 * AYRICA TUM HARFLER BUYUK HARFE CEVRILMISTIR, BOYLECE HARF DUYARLILIGI    *
 * HATALARININ ONUNE GECILMISTIR											*
 ***************************************************************************/
 
 
 

/*##########################################################################*/
/*						libraries and Constant Macros						*/
/*##########################################################################*/

#include<stdio.h>
#include<string.h>
#include<ctype.h>

#define MAX_ROW 			25	/*maksimum satir sayisi		*/
#define COLUMN_SIZE 		8	/*maximum sutun sayisi		*/
#define MAX_LOG_SIZE		25	/*maximum komut uzunlugu	*/
#define MAX_LOG_ROW 		250 /*maximum komut sayisi		*/
#define MAX_PIECE_COL 		2	
#define MAX_PIECE_ROW		20 	/*max tas koordinati sayisi	*/
#define FILE_NAME_SIZE		50	/*max dosya adi uzunlugu	*/
#define PLAYER_NAME_SIZE	50	/*max oyuncu adi uzunlugu	*/
#define FIRST				1	/*birinci oyuncu*/
#define SECOND				2	/*ikinci oyuncu*/
#define QUIT				101 /*cikis belirteci*/
#define TRUE 				1	
#define FALSE 				0
#define ERROR				-1



/*hareket secenekleri*/
typedef enum
{
	UP, LEFT, RIGHT
}direction_t;



/*##########################################################################*/
/*							Function Prototypes								*/
/*##########################################################################*/

int playGame(char initFileName[]);
int getInitState( FILE *initFile, int table[][COLUMN_SIZE], int *rowC);
int makeMove(int table[][COLUMN_SIZE], int rowC, int playerNo, int *coorY,
			 int *coorX, direction_t direction);
			 
void getPieces(int table[][COLUMN_SIZE], int rowC, int pieces1[][MAX_PIECE_COL], 
			   int *rowCP1, int pieces2[][MAX_PIECE_COL], int *rowCP2);
		
void printGame(int arr[][COLUMN_SIZE], int rowC);
void getOppositeView(int tableIn[][COLUMN_SIZE],  int rowC,
					 int tableReversed[][COLUMN_SIZE]);
					 			 
void printPieces(int pieces[][MAX_PIECE_COL], int rowC);			   
int isBlocked(int table[][COLUMN_SIZE], int rowC, int playerNo, int coorY, int coorX);
int isTerminated(int table[][COLUMN_SIZE], int rowC);			  
void saveGame(char fileName[], int table[][COLUMN_SIZE], int rowC);
void saveLog(char fileName[], char logs[MAX_LOG_ROW][MAX_LOG_SIZE], int rowC);


void save1Log(char log[], char allLogs[][MAX_LOG_SIZE], int *numLogs);
int  takeAndControlCommand(char command[MAX_LOG_SIZE], int playerNo, 
						   char firstPlayer[], char secondPlayer[], 
						   FILE *commandFilePtr );
						   
void takeNames(char firstPlayer[], char secondPlayer[]);
void toUpperAll(char strIn[]);
int ownPiece(int table[][COLUMN_SIZE], int rowC, int playerNo, int coorY, int coorX);
int anyObstacle(int table[][COLUMN_SIZE], int rowC, int playerNo, int coorY,
				int coorX, direction_t direction);
				
int anyOverFlow(int playerNo, int coorX, direction_t direction);
				
int itIsEnemy(int table[][COLUMN_SIZE], int rowC, int playerNo, int coorY,
			  int coorX, direction_t direction);
			  
void offerDraw(int playerNo, char firstPlayer[], char secondPlayer[]);
void printCommandTypes(void);
int answerDraw(char offer[]);
int checkOtherMove(int table[][COLUMN_SIZE], int rowC, int playerNo, int coorY,
				   int coorX);
				   
int Player( int table[][COLUMN_SIZE], int rowC, int pieces1[][MAX_PIECE_COL], 
			int pieces2[][MAX_PIECE_COL], int *rowCP1, int *rowCP2, int *coorX, 
			int *coorY, char log[], char allLogs[][MAX_LOG_SIZE],  int *numLogs,
			FILE *commandsFilePtr, int playerNo, char firstPlayer[],
			char secondPlayer[]);

			
			
/*##########################################################################*/
/*								MAIN Function								*/
/*##########################################################################*/

int main(void)

{
	/*START_OF_MAIN*/
	
	char initFileName[FILE_NAME_SIZE] = {"Initial.txt"}; 
		
	/*END_OF_VARIABLES*/
	
	
	playGame(initFileName);

	system("pause");
	return 0;
	/*END_OF_MAIN*/
}



/*##########################################################################*/
/*								FUNCTIONS									*/
/*##########################################################################*/


/*oyunun devamliligini saglayan, bitis durumunu kontrol eden fonksiyon*/
int playGame(char initFileName[])
{

	int rowC, numLogs = 0;	/*oyun sahasi satir sayisi ve komut sayisi*/
	
	int table[MAX_ROW][COLUMN_SIZE];	/*oyun sahasi*/
	int forPrintTable[MAX_ROW][COLUMN_SIZE]; /*oyun sahasinin tersi*/
	
	int pieces1[MAX_PIECE_ROW][MAX_PIECE_COL];	/*1. oyuncunun tas koordinatlari*/
	int pieces2[MAX_PIECE_ROW][MAX_PIECE_COL];	/*2. oyuncunun tas koordinalari*/
	int rowCP1, rowCP2;
	int coorX, coorY;
	
	/*alinan her log ve hepsinin toplandigi ikinci log arrayleri*/
	char log[MAX_LOG_SIZE], 
		 allLogs[MAX_LOG_ROW][MAX_LOG_SIZE];

		 
	char firstPlayer[PLAYER_NAME_SIZE];
	char secondPlayer[PLAYER_NAME_SIZE];
	
	int playerNo = FIRST;
	
	FILE *initialFilePtr;	/*baslangic dosyasi*/
	FILE *commandsFilePtr;	/*komut dosyasi*/


	initialFilePtr = fopen(initFileName, "r");
	commandsFilePtr = fopen("Commands.txt", "r");

	printCommandTypes();
	
	/*tas konumlari alinirken sorun cikarsa hata mesaji basilir*/
	if(getInitState(initialFilePtr, table, &rowC) == ERROR)
	{
		printf("\nThe file is not appropriate for play game or does not exist\n");
		printf("Game is shutting down\n\n");
		return ERROR;
	}
	
	takeNames(firstPlayer, secondPlayer);

	
	while(1)
	{

		printGame(table, rowC);
		
		/*galibiyet kontrolleri*/
		if (isTerminated(table, rowC) == FIRST)
		{
			printf("\n%s is the WINNER\n\n", firstPlayer);
			return 0;
				
		}
		
		if (isTerminated(table, rowC) == SECOND)
		{
			printf("%s is the WINNER\n\n", secondPlayer);
			return 0;
		}
		
		/*1. oyuncu icin hamle baslar, QUIT donerse oyun biter*/
		playerNo = FIRST;
		if( QUIT == Player(table, rowC, pieces1, pieces2, &rowCP1, &rowCP2, &coorX, 
				&coorY, log, allLogs, &numLogs, commandsFilePtr, playerNo,
				firstPlayer, secondPlayer)){
			return 0;
		}	
			
			
		/*galibbiyet kontrolleri*/
		if (isTerminated(table, rowC) == FIRST)
		{
			printf("\n%s is the WINNER\n\n", firstPlayer);
			return 0;
				
		}
		
		if (isTerminated(table, rowC) == SECOND)
		{
			printf("%s is the WINNER\n\n", secondPlayer);
			return 0;
		}
		
		
		/*tersi alinir ve ekrana basilir*/
		getOppositeView(table, rowC, forPrintTable);
		printGame(forPrintTable, rowC);
		
		/*2. oyuncu icin hamle baslar, QUIT donerse oyun biter*/
		playerNo = SECOND;
		if( QUIT == Player(table, rowC, pieces1, pieces2, &rowCP1, &rowCP2, &coorX, 
				&coorY, log, allLogs, &numLogs, commandsFilePtr, playerNo,
				firstPlayer, secondPlayer)){
			return 0;
		}
	}
	
	
	fclose(initialFilePtr);
	fclose(commandsFilePtr);
	
	return 0;
}




/* oyuncu numarasina gore her oyuncunun duzgun bir sekilde hamlesini yaptirir
 * yanlis hamlelerde ya da ayni oyuncunun devam etmesi
 * gereken hamlelerde tekrari saglar*/
int Player( int table[][COLUMN_SIZE], int rowC, int pieces1[][MAX_PIECE_COL], 
			int pieces2[][MAX_PIECE_COL], int *rowCP1, int *rowCP2, int *coorX, 
			int *coorY, char log[], char allLogs[][MAX_LOG_SIZE],  int *numLogs,
			FILE *commandsFilePtr, int playerNo, char firstPlayer[],
			char secondPlayer[])
{	

	int forPrintTable[MAX_ROW][COLUMN_SIZE];
	int cont = TRUE;					/*ayni oyuncunun devam etmesi icin flag*/
	int passFlag = FALSE;				/*PASS komutu kontrol flagi*/
	int drawFlag = FALSE;				/*ACCEPT DRAW komutu kontrol flagi*/
	char temp[MAX_LOG_SIZE];			/*gecici komut tutma arrayi*/
	int retMov;							/*makeMove return degeri*/
	direction_t direction;				/*hamle yonu*/

	/*devamlilik flagi(cont) TRUE iken ayni oyuncuda kalinir*/
	while(cont == TRUE)
	{		
		cont = FALSE;

	/*komut dosyadan okunurken error gelirse fonksiyonda cikilir (EOF vs.)*/
		if (takeAndControlCommand(log, playerNo, firstPlayer, secondPlayer, 
								  commandsFilePtr) == ERROR){
			return QUIT;
		}
		
		save1Log(log, allLogs, numLogs);
		
		/*komut parcalara ayrilir, komutun uydugu yere gore islemler yapilir*/
		strcpy(temp,strtok(log,"_"));
		
		if(strcmp(temp, "M") == 0)
		{			
			
			strcpy(temp, strtok(NULL,"_"));
			
			if (strlen(temp) == 1){
				*coorY = temp[0] - 48;
			}
			if (strlen(temp) == 2){
				*coorY = (temp[0] - 48)*10 + (temp[1] - 48);
			}
				
			strcpy(temp, strtok(NULL,"_"));
			*coorX = temp[0] - 48;
			
			strcpy(temp, strtok(NULL,"_"));
			if(strcmp(temp,"UP") == 0){
				direction = UP;
			}
			if(strcmp(temp,"RIGHT") == 0){
				direction = RIGHT;
			}
			if(strcmp(temp,"LEFT") == 0){
				direction = LEFT;
			}

			/* makeMove dan FALSE return edilmesi tasin yenildigini isaret eder
			 * FALSE gelmisse ve checkOtherMove da TRUE ise 
			 * oyuncuya ne yapacag sorulur
			 */
			if((retMov = makeMove(table, rowC, playerNo, coorY, coorX, direction)) == FALSE &&
			    checkOtherMove(table, rowC, playerNo, *coorY, *coorX) == TRUE)
			{
				cont = TRUE;
				passFlag = TRUE;	/*passFlag TRUE yapilir artik oyuncu P komutu girebilir*/
				printf(">>There is a piece of enemy that you can move\n\n");
				
				if(playerNo == FIRST){
					printGame(table, rowC);
				}
				else
				{
					getOppositeView(table, rowC, forPrintTable);
					printGame(forPrintTable, rowC);
				}
			}
			/*makeMove dan ERROR return edilirse hamlenin yapilamadigi soylenir*/
			else if(retMov == ERROR)
			{
				printf("You do not make this move, TRY AGAIN !!\n\n");
				cont = TRUE;
			}	
		
			
		}
		
		/* pass komutu kontrolu yapilir 
		 * eger passFlagi etkin degilse komut yapilamaz
		 */
		if(strcmp(temp, "P") == 0)
		{
			
			if(passFlag == TRUE){
				return 0;
			}
			else
			{
				printf("You do not enter PASS command\n\n");
				cont = TRUE;
			}
		}
	
		/*oyunun o anki durumu kaydedilir*/
		if(strcmp(temp, "SG") == 0)
		{
			cont = TRUE;
			strcpy(temp, strtok(NULL,"_"));
			
			saveGame(temp, table, rowC);
			printf("GAME SAVED to \"%s\"\n\n", temp);
			
		}
		
		/*loglarin dosyaya kaydi yapilir*/
		if(strcmp(temp, "SL") == 0)
		{
			cont = TRUE;
			strcpy(temp, strtok(NULL,"_"));
			
			saveLog(temp, allLogs, *numLogs);
			printf("Game Logs has been saved to \"%s\"\n\n", temp);
			
		
		}

		/*taslarin yeri gosterilir*/
		if(strcmp(temp, "SP") == 0)
		{
			if(playerNo == FIRST)
			{			
				getPieces(table, rowC, pieces1, rowCP1, pieces2, rowCP2);
				printPieces(pieces1, *rowCP1);
				cont = TRUE;
			}
			else
			{			
				getPieces(table, rowC, pieces1, rowCP1, pieces2, rowCP2);
				printPieces(pieces2, *rowCP2);
				cont = TRUE;
			}
		}
		
		/*oyunda  cekilen varsa oyun bitirilir*/
		if(strcmp(temp, "R") == 0)
		{
			if(playerNo == FIRST)
			{
				printf("\n%s resigned from the game\n", firstPlayer);
				printf("%s is the WINNER\n", secondPlayer);
			}
			else
			{
				printf("\n%s resigned from the game\n", secondPlayer);
				printf("%s is the WINNER\n", firstPlayer);
			}	
			printf("GAME OVER !! \n\n");
			return QUIT;
		}
		
		
		/* beraberlik teklifi olmadan(drawFlag FALSE)
		 * bu komut girlirse hata mesaji basilir
		 */	
		if(strcmp(temp,"AD") == 0 && drawFlag == FALSE)
		{
			printf("There is no OFFER\nYou can not enter Accept Draw code \n\n");
			cont = TRUE;
		}
		
		/*berberlik teklifi*/
		if(strcmp(temp, "OD") == 0)
		{
			offerDraw(playerNo, firstPlayer, secondPlayer);
			
			if(playerNo == FIRST)
				playerNo = SECOND;
			
			else
				playerNo = FIRST;
			
			if (takeAndControlCommand(log, playerNo, firstPlayer, secondPlayer, 
				commandsFilePtr) == ERROR){
				return QUIT;
			}
			
			if(playerNo == FIRST)
				playerNo = SECOND;
			else
				playerNo = FIRST;
			
			
			if(answerDraw(log) == TRUE)
			{
				printf("The offer was accepted\n");
				printf("The match has no winner\nGAME OVER\n");
				return QUIT;
			}
			else if(answerDraw(log) == FALSE)
			{
				printf("Your offer was NOT accepted\n\n");
				cont = TRUE;
			}
			else
			{
				if(playerNo == FIRST)
					playerNo = SECOND;
				else
					playerNo = FIRST;
			
				
				printf("You entered wrong offer answer\n");
				printf("ENTER AGAIN !! \n\n");
				
				if (takeAndControlCommand(log, playerNo, firstPlayer, 
					secondPlayer, commandsFilePtr) == ERROR){
					return QUIT;
				}
				
				drawFlag = TRUE;
				cont = TRUE;
				
				if(playerNo == FIRST)
					playerNo = SECOND;
				else
					playerNo = FIRST;
			
			}
		}
		
	}
	return 0;
}


/*baslangic oyun tahtasini belirtielen dosyada alip ilgili arraye yazar*/
int getInitState(FILE *initFile, int table[][COLUMN_SIZE], int *rowC)
{
	int status, i, j, piece;
	char trash;
	
	/*dosya bossa hata kodu return edilir*/
	if(initFile == 0)
		return ERROR;
	
	/*dosya okunup arraye yazilir*/
	status = fscanf(initFile, "%d%c", &piece, &trash);
	for(i=0; status != EOF ; ++i)
	{
		for(j=0; status != EOF && trash != '\n'; ++j)
		{
			table[i][j] = piece;	
			status = fscanf(initFile, "%d%c", &piece, &trash);
			
			if(trash == '\n')
				table[i][j+1] = piece;
		}
		
		status = fscanf(initFile, "%d%c", &piece, &trash);
	}
		*rowC = i;
		
	/*satir sayisi 4 ten kucuk 25 ten buyuk olamaz
     * aksi halde hata kodu return edilir
	 */
	if (*rowC < 4 || *rowC > 25)
		return ERROR;
	
	
	return *rowC;
}

/*ana arrayin tersini alarak baska bir arraye yazar*/
void getOppositeView(int tableIn[][COLUMN_SIZE],  int rowC, int tableReversed[][COLUMN_SIZE])
{
	int i, j, k, l;
	
	for(i=0, k = rowC-1; i < rowC ; ++i, --k)
	{
		for(j=0, l=COLUMN_SIZE-1
			; j < COLUMN_SIZE
			;++j, --l)
		{
			tableReversed[i][j] = tableIn[k][l];
		}
	}
}


/*o anki oyun tahtasinin durumunu ekrana yazar*/
void printGame(int arr[][COLUMN_SIZE], int rowC)
{
	int i, j;
	
	
	printf("\n\n                                  ");
	printf("      1 2 3 4 5 6 7 8      \n");
	printf("                      ");
	printf("                  ---------------      \n\n");
	
	for(i=0; i < rowC; ++i)
	{	
		if(i > COLUMN_SIZE)
		{
			printf("                      ");
			printf("            %d>   ", i+1);
		}
		
		else
		{	
			printf("                      ");
			printf("             %d>   ", i+1);
		}
		for(j=0; j < COLUMN_SIZE; ++j)
		{

			if(arr[i][j] == 1)
				printf("1 ");	
				
			if(arr[i][j] == 2)
				printf("2 ");	
				
			if(arr[i][j] == -1)
				printf("X ");
			
			if(arr[i][j] == 0)
				printf("- ");
		}
		
		
			printf("  <%d", i+1);
			printf("\n");
		
		
	}
	
	printf("                                 ");
	printf("                             ");
	printf("\n                      ");
	printf("                  ---------------       \n");
	printf("                                 ");
	printf("       1 2 3 4 5 6 7 8\n");
}


/*koordinatlarin bulundugu arrayi ekrana yazar*/
void printPieces(int pieces[][MAX_PIECE_COL], int rowC)
{
	int i, j;
	
	printf("Player's pieces\n");
	
	for(i=0; i < rowC; ++i)
	{
		for(j=0; j < MAX_PIECE_COL; ++j)
		{
			printf("%d ", pieces[i][j]);
		}
		printf("\n");
	}
}

/* her iki oyuncu icin de taslarin koordinatlarini bulur
 * bunlari her oyuncu icin ayri olarak acilmis arraylere yazar*/
void getPieces(int table[][COLUMN_SIZE], int rowC, int pieces1[][MAX_PIECE_COL], 
			   int *rowCP1, int pieces2[][MAX_PIECE_COL], int *rowCP2)
{	
	int i, j, m=0;
	int tableReversed[MAX_ROW][COLUMN_SIZE];	
	
	for(i=0; i < rowC; ++i)
	{
		for(j=0; j < COLUMN_SIZE; ++j)
		{
			if(table[i][j] == 1)
			{
				pieces1[m][0] = i+1;
				pieces1[m][1] = j+1;
				m++;
			}
		}
	}
	*rowCP1 = m;


	getOppositeView(table, rowC, tableReversed);
	m=0;
	for(i=0; i < rowC; ++i)
	{
		for(j=0; j < COLUMN_SIZE; ++j)
		{
			if(tableReversed[i][j] == 2)
			{
				pieces2[m][0] = i+1;
				pieces2[m][1] = j+1;
				m++;
			}
		}
	}
	*rowCP2 = m;
	getOppositeView(tableReversed, rowC, table);

}

/*koordinatlari verilen tasin hareket kabiliyetini sorgular
 * hareket mumkunse FALSE aksi halde TRUE return eder
 */
int isBlocked(int table[][COLUMN_SIZE], int rowC, int playerNo, int coorY, int coorX)
{
	int counter = 0;


	if(anyObstacle(table, rowC, playerNo, coorY,  coorX, UP) == FALSE)
		counter++;
	
	if(anyObstacle(table, rowC, playerNo, coorY,  coorX, LEFT) == FALSE)
		counter++;
	
	if(anyObstacle(table, rowC, playerNo, coorY,  coorX, RIGHT) == FALSE)
		counter++;
	
	if(counter == 0)
		return TRUE;
	else
		return FALSE;

}


/* **************************************************
 * oyunun kazanani olup olmadigini kontrol eder		*
 * eger 1. oyuncu kazanmissa FIRST					*
 * 2. oyuncu kazanmissa SECOND						*
 * oyun devam edecekse de FALSE return eder			*
 *													*
 * input olarak oyun sahasi ve satir sayisi alinir	*
 ****************************************************/
int isTerminated(int table[][COLUMN_SIZE], int rowC)
{
	int tableReversed[MAX_ROW][COLUMN_SIZE];
	int i, j, counter=0;
	int y, x, blockCount=0, playerNo;
	
	/* 1. oyuncunun herhangi bir tasi king olmus mu diye kontrol edilir
	 * king tas varsa FIRST(1) return edilir
	 */
	for(i=0; i < rowC; ++i)
	{
		for(j=0; j < COLUMN_SIZE; ++j)
		{
			if(table[i][j] == FIRST && i == 0)
				return FIRST;		
		}
	}

	/* 2. oyuncunun herhangi bir tasi king olmus mu diye kontrol edilir
	 * king tas varsa SECOND(2) return edilir
	 */
	for(i=0; i < rowC; ++i)
	{
		for(j=0; j < COLUMN_SIZE; ++j)
		{
			if(table[i][j] == SECOND && i == rowC-1)
				return SECOND;		
		}
	}


	/*1. oyuncunun tasi olup olmadigi kontrol edilir
	 * yoksa rakip oyuncu return edilir
	 */
	for(i=0; i < rowC; ++i)
	{
		for(j=0; j < COLUMN_SIZE; ++j)
		{
			if(table[i][j] == FIRST)
				counter++;
		}
	
	}
	if(counter == 0)
		return SECOND;
	
	
	counter=0;
	
	/*2. oyuncunun tasi olup olmadigi kontrol edilir
	 * yoksa rakip oyuncu return edilir
	 */
	for(i=0; i < rowC; ++i)
	{
		for(j=0; j < COLUMN_SIZE; ++j)
		{
			if(table[i][j] == SECOND)
				counter++;
		}
	
	}
	if(counter == 0)
		return FIRST;
		
	
	/*1. oyuncunun gecerli hamlesi olup olmadigi kontrol edilir*/
	playerNo = FIRST;
	for(y=1; y <= rowC; ++y)
	{
		for(x=1; x <= COLUMN_SIZE; ++x)
		{
			if(table[y-1][x-1] == playerNo)
			{
				if(isBlocked(table, rowC, playerNo, y, x) == FALSE)
					blockCount++;
			}
		}
	}

	if(blockCount == 0)
	{
		return SECOND;
	}
	else
		blockCount = 0;
	
	
	/*2. oyuncunun gecerli hamlesi olup olmadigi kontrol edilir*/	
	getOppositeView(table, rowC, tableReversed);
	
	playerNo = SECOND;
	for(y=1; y <= rowC; ++y)
	{
		for(x=1; x <= COLUMN_SIZE; ++x)
		{
			if( isBlocked(table, rowC, playerNo, y, x)  == FALSE  &&
				tableReversed[y-1][x-1] == playerNo)
				{
					blockCount++;
				}
		}
	}
	
	if(blockCount == 0)
	{
		return FIRST;
	}
	else
		blockCount = 0;

	return FALSE;
		
}	


/* oyunun o anki halini istenilen dosyaya kaydeder
 * dosya ismi, oyun sahasi ve satir sayisi input olarak alinir
 */
void saveGame(char fileName[], int table[][COLUMN_SIZE], int rowC)
{
	int i, j;
	FILE *saveFilePtr;
	
	saveFilePtr = fopen(fileName, "w");
	
	for(i = 0; i < rowC; ++i)
	{
		for(j = 0; j < COLUMN_SIZE; ++j)
		{
			if(j == 7)
				fprintf(saveFilePtr, "%d", table[i][j]);
			else
				fprintf(saveFilePtr, "%d	", table[i][j]);
		
		}
		
		if(i != rowC - 1)
			fprintf(saveFilePtr, "\n");
	}
	
	fclose(saveFilePtr);
}

/* hatali olmayan her logu tum loglarin tutuldugu arraye yazar */
void save1Log(char log[], char allLogs[MAX_LOG_ROW][MAX_LOG_SIZE], int *numLogs)
{
	
	strcpy(allLogs[*numLogs], log);
	*numLogs = *numLogs + 1;
	
}


/* tum loglarin kaydedildigi arrayi istenilen dosyaya basar*/
void saveLog(char fileName[], char logs[MAX_LOG_ROW][MAX_LOG_SIZE], int rowC)
{	
	int i;
	FILE *logPtr;
	
	logPtr = fopen(fileName, "w");
	
	for(i=0; i < rowC; ++i){
		fprintf(logPtr,"%s\n", logs[i]);
	}
	
	fclose(logPtr);

}


/* hamle yapma fonksiyonu
 * eger hamle gecerli bir hamle ise hareketi gerceklestirir
 * aksi halde ERROR return eder
 * yapilan hamle karsi tarafin tasi yenilmeden yapildiysa TRUE
 * tas yenilerek yapildiysa FALSE return edilir */
int makeMove(int table[][COLUMN_SIZE], int rowC, int playerNo, int *coorY,
			 int *coorX, direction_t direction)
{

	int tableReversed[MAX_ROW][COLUMN_SIZE];
	int status = ERROR;
		
	if(playerNo == FIRST)
	{	
		
		if(anyObstacle(table, rowC, playerNo, *coorY,  *coorX, direction) != FALSE ||
			   anyOverFlow(playerNo,*coorX, direction) != FALSE  ||
			   ownPiece(table, rowC, playerNo, *coorY, *coorX) != TRUE){
			   return ERROR;
			}
			
		switch(direction)
		{
			case UP:
					if(itIsEnemy(table,  rowC, playerNo, *coorY, *coorX, direction) != TRUE)
					{
						table[*coorY-1][*coorX-1] = 0;
						*coorY = *coorY - 1;
						table[*coorY-1][*coorX-1] = 1;
						status = TRUE;
					}
					
					else
					{
						if(table[*coorY-3][*coorX-1] == 0)
						{
							table[*coorY-1][*coorX-1] = 0;
							table[*coorY-2][*coorX-1] = 0;
							*coorY = *coorY - 2;
							table[*coorY-1][*coorX-1] = 1;
							status = FALSE;
						}
						else
							status = ERROR;
					}
					break;
				
			case LEFT:
					if(itIsEnemy(table,  rowC, playerNo, *coorY, *coorX, direction) != TRUE)
					{
						table[*coorY-1][*coorX-1] = 0;
						*coorX = *coorX - 1;
						table[*coorY-1][*coorX-1] = 1;	
						status = TRUE;
					}
					
					else
					{	
						if(table[*coorY-1][*coorX-3] == 0)
						{
							table[*coorY-1][*coorX-1] = 0;
							table[*coorY-1][*coorX-2] = 0;
							*coorX = *coorX - 2;
							table[*coorY-1][*coorX-1] = 1;		
							status = FALSE;
						}
						else
							status = ERROR;
					}
					break;
			
			case RIGHT:
					if(itIsEnemy(table,  rowC, playerNo, *coorY, *coorX, direction) != TRUE)
					{
						table[*coorY-1][*coorX-1] = 0;
						*coorX = *coorX + 1;
						table[*coorY-1][*coorX-1] = 1;
						status = TRUE;
					}
					
					else
					{
						if(table[*coorY-1][*coorX+1] == 0)
						{
							table[*coorY-1][*coorX-1] = 0;
							table[*coorY-1][*coorX] = 0;
							*coorX = *coorX + 2;
							table[*coorY-1][*coorX-1] = 1;	
							status = FALSE;
						}
						else
							status = ERROR;
					}
					break;
			
			default :
						break;
		}
		
	}
	

	if(playerNo == SECOND)
	{
		getOppositeView(table,  rowC,  tableReversed);
		
		if(anyObstacle(table, rowC, playerNo, *coorY,  *coorX, direction) != FALSE ||
			   anyOverFlow(playerNo,*coorX, direction) != FALSE  ||
			   ownPiece(table, rowC, playerNo, *coorY, *coorX) != TRUE){
			   return ERROR;
		}
		
		switch(direction)
		{
			case UP:
					if(itIsEnemy(tableReversed,  rowC, playerNo, *coorY, *coorX,
					   direction) != TRUE)
					{
						tableReversed[*coorY-1][*coorX-1] = 0;
						*coorY = *coorY - 1;
						tableReversed[*coorY-1][*coorX-1] = 2;
						status = TRUE;
					}
					
					else
					{	if(tableReversed[*coorY-3][*coorX-1] == 0)
						{
							tableReversed[*coorY-1][*coorX-1] = 0;
							tableReversed[*coorY-2][*coorX-1] = 0;
							*coorY = *coorY - 2;
							tableReversed[*coorY-1][*coorX-1] = 2;		
							status = FALSE;
						}
						else
							status = ERROR;
					}
					break;
				
			case LEFT:
					if(itIsEnemy(tableReversed,  rowC, playerNo, *coorY, *coorX,
					   direction) != TRUE)
					{
						tableReversed[*coorY-1][*coorX-1] = 0;
						*coorX = *coorX - 1;
						tableReversed[*coorY-1][*coorX-1] = 2;	
						status = TRUE;
					}
					
					else
					{	if(tableReversed[*coorY-1][*coorX-3] == 0)
						{
							tableReversed[*coorY-1][*coorX-1] = 0;
							tableReversed[*coorY-1][*coorX-2] = 0;
							*coorX = *coorX - 2;
							tableReversed[*coorY-1][*coorX-1] = 2;				
							status = FALSE;
						}
						else
							status = ERROR;
					}
					break;
			
			case RIGHT:
					if(itIsEnemy(tableReversed,  rowC, playerNo, *coorY, *coorX,
					   direction) != TRUE)
					{
						tableReversed[*coorY-1][*coorX-1] = 0;
						*coorX = *coorX + 1;
						tableReversed[*coorY-1][*coorX-1] = 2;
						status = TRUE;
					}
					
					else
					{	if(tableReversed[*coorY-1][*coorX+1] == 0)
						{
							tableReversed[*coorY-1][*coorX-1] = 0;
							tableReversed[*coorY-1][*coorX] = 0;
							*coorX = *coorX + 2;
							tableReversed[*coorY-1][*coorX-1] = 2;					
							status = FALSE;
						}
						else
							status = ERROR;
					}
					break;
			
			default :
					break;
		}
		getOppositeView(tableReversed,  rowC,  table);
	}

	
	return status;
}


/*beraberlik onerisi*/
void offerDraw(int playerNo, char firstPlayer[], char secondPlayer[])
{
	if(playerNo == FIRST)
		printf("\n%s offered draw\n", firstPlayer);
	else
		printf("\n%s offered draw\n", secondPlayer);		
		
	printf("Do you want to accept this offer??\n");
	printf("If your answer is YES enter \"AD\"\n");
	printf("If your answer is NO enter \"RD\"\n\n");
}


/* beraberlik onerisinin cevabini kontrol eder
 * kabul edilmisse TRUE aksi halde FALSE return eder*/
int answerDraw(char offer[])
{
	int status;
	if(strcmp(offer, "AD") == 0)
		status = TRUE;
		
	else if(strcmp(offer, "RD") == 0)
		status = FALSE;
	else
		status = ERROR;

	return status;
}



/* Oynamak istenen tas ve oyuncu ayni mi diye kontrol eder
 * eger kendi tasiysa TRUE aksi halde FALSE return eder
 */
int ownPiece(int table[][COLUMN_SIZE], int rowC, int playerNo, int coorY, int coorX)
{
	int tableReversed[MAX_ROW][COLUMN_SIZE];
	int status;
	
	switch(playerNo)
	{	
		case 1:	
				if(table[coorY-1][coorX-1] == playerNo)
					status = TRUE;
				else
					status = FALSE;
					
				break;
				
		case 2:
				getOppositeView(table,  rowC,  tableReversed);
				
				if(tableReversed[coorY-1][coorX-1] == playerNo)
					status = TRUE;
				else
					status = FALSE;
			
				getOppositeView(tableReversed,  rowC,  table);
				break;
	}
	
	return status;
}



/* Oynanmak istenen konumda engel(X ya da kendi tasi) var mi diye kontrol eder
 * engel varsa TRUE yoksa FALSE return eder
 */
int anyObstacle(int table[][COLUMN_SIZE], int rowC, int playerNo, int coorY, 
				int coorX, direction_t direction)
{
	int tableReversed[MAX_ROW][COLUMN_SIZE];
	int status = FALSE;
	
	
	if(playerNo == FIRST)
	{
		switch(direction)
		{
			case UP:
						if(table[coorY-2][coorX-1] == -1 || 
						   table[coorY-2][coorX-1] == playerNo ){
							status = TRUE;
						}
							break;
						
			case LEFT:
						if(table[coorY-1][coorX-2] == -1 ||
						   table[coorY-1][coorX-2] == playerNo){
							status = TRUE;
						}
							break;
						
			case RIGHT:
						if(table[coorY-1][coorX] == -1 ||
						   table[coorY-1][coorX] == playerNo){
							status = TRUE;
						}
							break;
						
			default:
						break;
		}
	}
	
	if(playerNo == SECOND)
	{
		getOppositeView(table,  rowC,  tableReversed);
		switch(direction)
		{
			case UP:
						if(tableReversed[coorY-2][coorX-1] == -1 || 
						   tableReversed[coorY-2][coorX-1] == playerNo){
							status = TRUE;
						}
							break;
						
			case LEFT:
						if(tableReversed[coorY-1][coorX-2] == -1 ||
    					   tableReversed[coorY-1][coorX-2] == playerNo){
							status = TRUE;
						}
							break;
						
			case RIGHT:
						if(tableReversed[coorY-1][coorX] == -1 ||
						   tableReversed[coorY-1][coorX] == playerNo){
							status = TRUE;
						}
							break;
						
			default:
						break;
		}
		
		getOppositeView(tableReversed,  rowC,  table);
	}

	return status;
}


/* oynanacak tasin hamleden sonra 
 * alan disina cikip cikmayacagini kontrol eder
 * cikiyorsa TRUE aksi halde FALSE return eder
 */
int anyOverFlow(int playerNo, int coorX, direction_t direction)
{	

	int status = FALSE;
	
	if(playerNo == FIRST)
	{
		switch(direction)
		{
			
			case LEFT:
						if(coorX == 1)
							status = TRUE;
						break;
			case RIGHT:
						if(coorX == 8)
							status = TRUE;
						break;
			default:
						break;
		}
	}

	else
	{
		switch(direction)
		{
			
			case LEFT:
						if(coorX == 8)
							status = TRUE;
						break;
			case RIGHT:
						if(coorX == 1)
							status = TRUE;
						break;
			default:
						break;
		}
	}

	return status;
}

/* oynanan tasin hamle yaptigi noktada 
 * karsi tarafin tasinin olup olmadigini kontrol eder
 * dusman varsa TRUE aksi halde FALSE return eder
 */
int itIsEnemy(int table[][COLUMN_SIZE], int rowC, int playerNo, int coorY, 
			  int coorX, direction_t direction)
{
	int tableReversed[MAX_ROW][COLUMN_SIZE];
	int status = FALSE;
	
	
	if(playerNo == FIRST)
	{	switch(direction)
		{
			case UP:
						if(table[coorY-2][coorX-1] == SECOND)
							status = TRUE;
							break;
			case LEFT:
						if(table[coorY-1][coorX-2] == SECOND)
							status = TRUE;
							break;
			case RIGHT:
						if(table[coorY-1][coorX] == SECOND)
							status = TRUE;
							break;
			default:
						break;
		}		
	}
	
	if(playerNo == SECOND)
	{
		getOppositeView(table, rowC, tableReversed);
		switch(direction)
		{
			case UP:
						if(table[coorY-2][coorX-1] == FIRST)
							status = TRUE;
							break;
			case LEFT:
						if(table[coorY-1][coorX-2] == FIRST)
							status = TRUE;
							break;
			case RIGHT:
						if(table[coorY-1][coorX] == FIRST)
							status = TRUE;
							break;
			default:
						break;
		}
		getOppositeView(tableReversed, rowC, table);
	}
	
	return status;
}

/* oyuncu bir tas yedikten sonra baska hamle
 * yapabilecegi tas var mi diye kontrol eder
 * varsa TRUE yoksa FAlSE return eder */
int checkOtherMove(int table[][COLUMN_SIZE], int rowC, int playerNo, int coorY, 
				   int coorX)
{
	int tableReversed[MAX_ROW][COLUMN_SIZE];
	int status;
	
	switch(playerNo)
	{
		case FIRST:
				if( table[coorY-1][coorX-2] == SECOND || 
					table[coorY-2][coorX-1] == SECOND ||
					table[coorY-1][coorX] == SECOND )
				{					
					status = TRUE;
				}	
				else
					status = FALSE;
					
				break;
		
		case SECOND:
				getOppositeView(table, rowC, tableReversed);
				
				if( tableReversed[coorY-1][coorX-2] == FIRST ||
					tableReversed[coorY-2][coorX-1] == FIRST ||
					tableReversed[coorY-1][coorX] == FIRST )
				{					
					status = TRUE;
				}	
				else
					status = FALSE;
				
				getOppositeView(tableReversed, rowC, table);
				break;
		
		default:
				break;
	}		
	
	return status;
}

/* oyuncu isimlerini alir */
void takeNames(char firstPlayer[], char secondPlayer[])
{
	printf("Please enter 1st player's names\n");
	scanf("%s", firstPlayer);
	toUpperAll(firstPlayer);
	printf("Please enter 2nd player's names\n");
	scanf("%s", secondPlayer);
	toUpperAll(secondPlayer);
}


/* girilen komutlari tum harflernin buyuk hale getirir */
void toUpperAll(char strIn[])
{	
	int i;
	
	for(i=0; strIn[i] != '\0'; ++i)
	{
		if(islower(strIn[i]))
			strIn[i] = toupper(strIn[i]);
			

	}
}



/* komutlari alan fonskiyon
 * dosyadan ya da konsoldan okuma yapabilir
 * Commands.txt varsa dosyadan yoksa konsoldan komut alir
 * alinan komutlarin yazim olarak dogrulugunu kontrol eder
 * yanlis giris varsa dogru girise kadar tekrar eder */
int takeAndControlCommand(char command[MAX_LOG_SIZE], int playerNo, 
						  char firstPlayer[], char secondPlayer[],
						  FILE *commandFilePtr )
{
	int ans = TRUE, i, counter=0;
	char temp[MAX_LOG_SIZE];
	char moveTemp[MAX_LOG_SIZE]; 	/*hamle icin gecici array*/
	char saveTemp[MAX_LOG_SIZE]; 	/*kayit islemi icin gecici array*/
	char ext[MAX_LOG_SIZE];			/*uzanti kontrolu icin gecici array*/
	int lenght;
	
	
	
	
	/*ans degeri FALSE ken islemler devam eder*/
	do{
	
	ans=TRUE;
	counter=0;
	
	/*komut dosyasi yoksa konsoldan komut istenir*/
	if(commandFilePtr == 0)
	{
		printf("------------------------\n");
		if(playerNo == FIRST)
			printf("%s your turn\n", firstPlayer);
		else
			printf("%s your turn\n", secondPlayer);
		
		printf("ENTER YOUR COMMAND \n\n>>");
		scanf("%s", command);
	}
	
	/*komut dosyasi varsa komutlar dosya sonuna kadar alinir*/
	/* dosya sonuna gelince fgets NULL return eder ve islem bitirilir*/
	if(commandFilePtr != 0)
	{
		
		if (fgets(command, MAX_LOG_SIZE, commandFilePtr) == NULL)
		{
			printf("END OF THE COMMENT FILE\n");
			return ERROR;
		}	
		else
		{
			printf("THE COMMAND FROM COMMAND FILE \n\n>>");
			printf("%s\n", command);
		}
	}
	
	/*dosyadan alinan komutun uzunlugu bulunur*/
	lenght = strlen(command);
	
	/*son eleman new line ise NULL a cevrilir*/
	if(command[lenght-1] == '\n')
		command[lenght-1] = '\0';
	
	/*komutun tamami buyuk harfe cevrilir*/
	toUpperAll(command);
	
	/*gecici arraylere kopyalamamlar yapilir*/
	strcpy(temp, command);
	strcpy(moveTemp, command);
	strcpy(saveTemp, command);
	
	/*karakterlere ve stringlere gore kontroller baslar*/
	if(temp[0] != 'M' && temp[0] != 'P' && temp[0] != 'S' && 
	   temp[0] != 'R' && temp[0] != 'O' && temp[0] != 'A'){
		ans = FALSE;
	}
	else
		ans=TRUE;
		
	
	if(temp[0] == 'M' && ans == TRUE)
	{
		for(i=0; temp[i] != '\0'; ++i)
		{
			if(temp[i] == '_')
				counter++;
		}
		
		if(counter == 3)
			ans = TRUE;
		else
		{
			ans = FALSE;
			counter=0;
		}
	}	
	
	if(ans == TRUE)
	strcpy(moveTemp, strtok(moveTemp,"_"));	
	if(strcmp(moveTemp, "M") == 0 && ans == TRUE)
	{	
		strcpy(moveTemp, strtok(NULL,"_"));
		if (strlen(moveTemp) != 1 && strlen(moveTemp) != 2)
			ans = FALSE;

	
		if(ans == TRUE)
			strcpy(moveTemp, strtok(NULL,"_"));
			
		if(strlen(moveTemp) != 1  && ans == TRUE)
			ans = FALSE;
			
		if(ans == TRUE)
			strcpy(moveTemp, strtok(NULL,"_"));
		
		if(strcmp(moveTemp,"UP") != 0 && strcmp(moveTemp,"RIGHT") != 0 &&
		   strcmp(moveTemp,"LEFT") && ans == TRUE){
			ans = FALSE;
		}
	}
	
	if(ans == TRUE && temp[0] == 'P')
	{
		if(strcmp(temp, "P") != 0)
			ans = FALSE;
	}

	if(ans == TRUE && temp[0] == 'R')
	{
		if(strcmp(temp, "R") != 0 && strcmp(temp, "RD") )
			ans = FALSE;
	}
	
	if(ans == TRUE && temp[0] == 'O')
	{
		if(strcmp(temp, "OD") != 0)
			ans = FALSE;
	}	
	
	if(ans == TRUE && temp[0] == 'A')
	{
		if(strcmp(temp, "AD") != 0)
			ans = FALSE;
	}
	
	if(ans == TRUE && temp[0] == 'S')
	{
		if(strcmp(temp, "SP") != 0 && strcmp(strtok(temp,"_"), "SG") != 0 &&
		   strcmp(strtok(temp,"_"), "SL") != 0){
			ans = FALSE;
		}
		
		else if(strcmp(temp, "SP") != 0)
		{
			/*dosya uzantisinin dusgun girildigi kontrol edilir*/
			strtok(saveTemp, ".");
			strcpy(ext, strtok(NULL, "."));
			if(strcmp(ext, "TXT") != 0 && strcmp(ext, "LOG") != 0)
			{
				ans=FALSE;
			}
		}
	}
	
	if(ans == FALSE)
		printf("\nYou entered wrong command, trry again !!\n");
		
	}while(ans == FALSE);

	return TRUE;
}


/* hamle turlerini ekrana yazar */
void printCommandTypes(void)
{	
	
	printf("|========================================================================|\n");
	printf("||									||\n");
	printf("||									||\n");
	printf("||			WELCOME TO GIT  VERSION CHECKERS		||\n");
	printf("||									||\n");
	printf("||									||\n");
	printf("|========================================================================|\n\n");
	
	printf("|========================================================================|\n");
	printf("|| YOU CAN ENTER COMMANDS LIKE FOLLOWING LINES			   	||\n");
	printf("||									||\n");
	printf("|| Making Move	    >> \"M_coorX_coorY_Direction\" like <M_1_3_UP>	||\n");
	printf("|| Saving Game	    >> \"SG_file.txt\" like <SG_initial.txt>		||\n");
	printf("|| Saving Logs	    >> \"SL_file.log\" like <SL_gameLogs.log>		||\n");
	printf("|| Passing	    >> \"P\"						||\n");
	printf("|| See the pieces   >> \"SP\"						||\n");
	printf("|| Resign from game >> \"R\"						||\n");
	printf("|| Offer Draw	    >> \"OD\"						||\n");
	printf("|| Accept Draw Offer>> \"AD\"						||\n");
	printf("|| Reject Draw Offer>> \"RD\"						||\n");
	printf("||									||\n");
	printf("|========================================================================|\n\n");
}










