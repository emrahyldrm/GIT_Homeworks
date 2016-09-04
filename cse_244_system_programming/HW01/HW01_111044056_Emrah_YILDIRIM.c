/*-----------------HW01_111044056_Emrah_YILDIRIM.c-------------------*/
/*LESSON: SYSTEM PROGRAMMING HOMEWORK 1:MORE OR LESS-----------------*/
/*DATE  : 11/03/2015-------------------------------------------------*/
/*AUTHOR: Emrah YILDIRIM---------------------------------------------*/
/*USAGE: ./exe inputfile lineNumber (enter)--------------------------*/
/*********************************************************************/

#include <stdio.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <string.h>
#include <malloc.h>
#include <errno.h>


/**
 * get terminal column number
 */
int getCol();


/**
 * get terminal row number
 */
int getRow();


/**
 * restore terminal
 */
void restoreTerm(void);


/**
 * take command without press enter
 */
void withoutEnter(void);


/**
 * make arrangements for take command
 */
void makeArrangements();


/**
 * get number of character in file
 * param: FILE * file pointer
 */
int calcSize(FILE *file);


/**
 * get all character from the file
 * param FILE * pflInput: file pointer
 * param char * pcText  : allocated memory pointer
 * param int iSize: return value of calcSize() (number of characters)
 */
void readFile(FILE *file, char *pcText, int iSize);


/**
 * termios struct for arrange terminal
 */
static struct termios oldt;



int main (int argc, char **argv)
{	
	/* VARIABLES */
	FILE *pflInput;
	int iLineNumber=0;
	char *pcText;
	int i, j;
	int iEnd=0, iStart=0, iBufferEnd;
	int iSize=0;
	double iPercentage=0.0;
	char cCh, cSelection='\0';

	/*check main function arguments, filename, print error if necessary*/
	if(argc != 3)
	{
		fprintf(stderr,"USAGE : %s file_name line_number\n", argv[0]);
		return 101;
	}
	else if(NULL == (pflInput = fopen(argv[1], "r")))
	{
		fprintf(stderr,"\"%s\" %s\n", argv[1], strerror(errno));
		return 102;
	}


	makeArrangements();

	iLineNumber = atoi(argv[2]);
	iSize = calcSize(pflInput);
	pcText = (char*)(malloc(iSize));

	readFile(pflInput, pcText, iSize);

	/* first printing*/
	system("clear");
	for (i = 0; i < getCol() * iLineNumber; ++i)
	{
		printf("%c", pcText[i]);	
		iEnd++;
		iBufferEnd++;
	}
	iPercentage = (double)iEnd*(100/(double)iSize);
	printf("\n%%%d:",  (int)iPercentage);
	
    
    while (1)
     {
        cSelection = getchar();
    	if(iPercentage < 100.0)
	    switch(cSelection)
        {
        	case 'd':
        	case 'D':        
        			/* check buffer end*/
        	       	if(iEnd >= iBufferEnd)
			       		break;
    				system("clear");
        			iStart += getCol(); /*change buffer start value*/
        			iEnd += getCol();	/*change current buffer end value*/

        			for (i = 0; i < getCol()*iLineNumber+iStart; ++i)
			        {
							printf("%c", pcText[i]);
			        }		
			        /* calculate and print percentage*/
		        	iPercentage = (double)iEnd*(100/(double)iSize);
					printf("\n%%%d:",  (int)iPercentage);
    			
					break;

         			
        	case 'U':
        	case 'u':	
        			/* check buffer start*/
        			if(iStart != 0)	
        			{
        				system("clear");
	        			iStart -= getCol();	/*change buffer start value*/
						iEnd -= getCol();	/*change current buffer end value*/
	        			

	        			for (i = 0; i < getCol()*iLineNumber+iStart; ++i)
				        {
								printf("%c", pcText[i]);
				        }	
				       	// calculate and print percentage	
			        	iPercentage = (double)iEnd*(100/(double)iSize);
						printf("\n%%%d:",  (int)iPercentage);
        			}   

					break;				        


        	case '\n':
    				system("clear");        				
    				iStart += getCol();	/*change buffer start value*/
    				iEnd += getCol();	/* change current buffer end value*/
    				iBufferEnd += getCol();	//change buffer end value
    				for (i = 0; i < iLineNumber*getCol() + iStart; ++i)
					{
						/*check end of file*/
						if(i > iSize)
						{
							printf("\n(%s) (END)\n", argv[1]);
							fclose(pflInput);
							free(pcText);
							return 0;							
						}					
						printf("%c", pcText[i]);	
					}
					/* calculate and print percentage	*/
					iPercentage = (double)iEnd*(100/(double)iSize);
					printf("\n%%%d:",  (int)iPercentage);
    				break;


		  	case 27:
    			    system("clear");        				
    				iStart += getCol()*iLineNumber;	/*change buffer start value*/
       				iEnd += getCol() * iLineNumber;	/* change current buffer end value*/
       				iBufferEnd += getCol() * iLineNumber; //change buffer end value*/

    				for (i = 0; i < iLineNumber*getCol() + iStart; ++i)
					{
						/*check end of file*/
						if(i > iSize)
						{
							printf("\n(%s) (END)\n", argv[1]);
							fclose(pflInput);
							free(pcText);
							return 0;							
						}
						printf("%c", pcText[i]);
					}
					/* calculate and print percentage	*/
					iPercentage = (double)iEnd*(100/(double)iSize);
					printf("\n%%%d:",  (int)iPercentage);
					break;


          	case 'q':
          	case 'Q':
          			free(pcText);
					fclose(pflInput);
          			printf("\nQUIT\n");
        			return 0;

       	}
    	else
    	{
			free(pcText);
			fclose(pflInput);
			return 0;
    	}

    }

	free(pcText);
	fclose(pflInput);
	return 0;
}







/*****************************************************************************
*							FUNCTIONS DEFINITIONS							 *
*****************************************************************************/

/**
 * get all character from the file
 * param FILE * pflInput: file pointer
 * param char * pcText  : allocated memory pointer
 * param int iSize: return value of calcSize() (number of characters)
 */
void readFile(FILE *file, char *pcText, int iSize)
{
	int i=0;
	char cCh;
	for (i = 0; i < iSize; )
	{
		fscanf(file, "%c", &cCh);
		if(cCh != '\n')
		{
			pcText[i] = cCh;
			i++;
		}
	}
}



/**
 * get number of character in file
 * param: FILE * file pointer
 */
int calcSize(FILE *file)
{
	int counter = 0;
	char cCh;

	while(EOF != fscanf(file, "%c", &cCh))
	{
		if(cCh != '\n')
			counter++;
		//printf("%c", cCh);
	}
	rewind(file);
	return counter;

}




/**
 * make arrangements for take command
 */
void makeArrangements()
{
	withoutEnter();
}


/**
 * get terminal row number
 * reference : from the web
 */
int getRow()
{
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return w.ws_row;
}


/**
 * get terminal column number
 * reference : from the web
 */
int getCol()
{
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return w.ws_col;
}


/**
 * restore terminal
 * reference : from the web
 */
void restoreTerm(void)
{
    tcsetattr(0, TCSANOW, &oldt); 
}


/**
 * take command without press enter
 *
 * reference : from the web
 */
void withoutEnter(void)
{
    struct termios newt;

    tcgetattr(0, &oldt);  
    newt = oldt;  
    newt.c_lflag &= ~(ICANON | ECHO);  
    tcsetattr(0, TCSANOW, &newt);  
    atexit(restoreTerm);
}


