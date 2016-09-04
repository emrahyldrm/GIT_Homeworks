/*---------syncrohyzationServer.c----------------*/
/*--SYSTEM PROGRAMMING MIDTERM PROJECT-----------*/
/*Author:Emrah YILDIRIM--------------------------*/
/*111044056                  --------------------*/
/*Date:15/04/2014 			 --------------------*/
/*---------------MATHSERVER----------------------*/

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

#define WAIT_TIME			30
#define FIFO_NAME_SIZE 		255
#define OP_NAME_SIZE 		255
#define PIPE_NAME_SIZE		255
#define RESULT_SIZE			255
#define MAX_PARAM			12
#define MAX_CLIENT			255
#define MAIN_LOG_FILE		"syncServerLog.log"


char strMainFifoName[FIFO_NAME_SIZE];
char strOps[MAX_CLIENT][OP_NAME_SIZE];
int iMathServerCount=0;
long int clients[MAX_CLIENT];

char strOldFifo[FIFO_NAME_SIZE];

char strMathServerName[FIFO_NAME_SIZE];
FILE *fpMainLog;
pid_t pMainPid;

int iAlarmFlag = 0;


void serverSigHandle(int signalNo);
void mathServerSigHandle(int signalNo);
void alarmHandler(int signalNo);
void mathServerExSigHandle(int signalNo);


int isException(char *result);


char * operation1(double a, double b, double c); 
char * operation2(double a, double b);
char * operation3(double a, double b, double c); 
char * operation4(double a, double b, double c, double d);

int  makeOperation(char * strOpName, char *strOpResult, double *dParams, int iParamSize);



int main(int argc, char **argv)
{
	if(argc != 2 || argv[1][0] != '-')
	{ 
		printf("Illegal command entry\n");
		printf("USAGE: ./syncrohyzationServer -fifoName\n");
		exit(0);
	}


	pMainPid = getpid();


	fpMainLog = fopen(MAIN_LOG_FILE, "a");
	fprintf(fpMainLog, "\n");

	struct tm *cTime;
	int iFifoDesc;
	signal(SIGINT, serverSigHandle);
	pid_t pid;
	pid_t pClientPid, pOldClientPid = 0;


	strcpy(strMainFifoName, &argv[1][1]);

	system("clear");

	mkfifo(strMainFifoName, 0666);

	printf("waiting for a client\n");
	
	if((iFifoDesc = open(strMainFifoName, O_RDONLY)) == -1)
	{
		printf("main server fifo can not opened\n");
		fprintf(fpMainLog, "main server fifo can not opened\n");

		exit(0);
	}
	char strOpName[OP_NAME_SIZE];






	while(1)
	{
		time_t current = time(NULL);
		cTime = localtime(&current);
		if(	read(iFifoDesc, strOpName, OP_NAME_SIZE) != 0)
		{
			read(iFifoDesc, &pClientPid, sizeof(pid_t));
			clients[iMathServerCount] = pClientPid;

			printf("%d. client [%ld]has connected for %s time: %d  %d  %d\n", 1+iMathServerCount, (long)pClientPid, strOpName, cTime->tm_hour, cTime->tm_min, cTime->tm_sec);
			fprintf(fpMainLog, "%d. client [%ld]has connected for %s time: %d  %d  %d\n", 1+iMathServerCount, (long)pClientPid, strOpName, cTime->tm_hour, cTime->tm_min, cTime->tm_sec);

			strcpy(strOps[iMathServerCount], strOpName);
			int fd[2];
			if(pipe(fd) == -1)
			{
				perror("Pipe Error !!");
				exit(0);
			}
			pid = fork();

			if(pid == -1)
			{
				perror("Fork Error !!");
				exit(0);
			}
			else if(pid == 0) //server //child
			{
				signal(SIGINT, mathServerSigHandle);
				signal(SIGALRM, alarmHandler);
				signal(SIGTSTP, mathServerExSigHandle);
				char mathServerFifo[FIFO_NAME_SIZE];
				int writeDesc, readDesc;
				double dAParams[12];
				int iParamSize=0;
				int iWait=0;
				int i;
				double dCurrentWait=0;
				char strOpResult[RESULT_SIZE]; 
				strOpResult[0] = '\0';

				sprintf(mathServerFifo, "fifo-%d", iMathServerCount);
				strcpy(strMathServerName, mathServerFifo);
				mkfifo(mathServerFifo,0666);
				close(fd[0]);
				write(fd[1], mathServerFifo, FIFO_NAME_SIZE);
				close(fd[1]);

				pid_t mypid = getpid();
				if((writeDesc = open(mathServerFifo, O_WRONLY)) == -1)
				{
					printf("math server fifo can not opened\n");
					fprintf(fpMainLog, "math server fifo can not opened\n");

					exit(0);
				}
				write(writeDesc, &mypid, sizeof(pid_t));
				close(writeDesc);
				alarm(WAIT_TIME);
				
				if((readDesc = open(mathServerFifo, O_RDONLY)) == -1)
				{
					printf("math server fifo can not opened\n");
					fprintf(fpMainLog, "math server fifo can not opened\n");

					exit(0);
				}
//				printf("i am child and op is %s\n", strOps[iMathServerCount]);
				int clientPid;
				while( read(readDesc, &clientPid, sizeof(int))== 0)
				{
					printf("waiting for reading\n");
					sleep(0.1);

				}
				printf("Server waiting for any client\n");
				read(readDesc, &iParamSize, sizeof(int));
				read(readDesc, dAParams, sizeof(double) * MAX_PARAM);
				read(readDesc, &iWait, sizeof(int));
				close(readDesc);

				printf("[%ld] math server will wait %d second(s)\n", (long)getpid(), iWait );
				fprintf(fpMainLog, "[%ld] math server will wait %d second(s)\n", (long)getpid(), iWait );
				for (i = 0; i < iWait; ++i)
				{	
					sleep(1);
					dCurrentWait+=1.0;
					if(dCurrentWait == WAIT_TIME-1)
					{
						kill(clientPid, SIGINT);
						kill(getpid(), SIGINT);

					}
//					printf("%d\n", i+1 );
//					fprintf(fpMainLog, "%d\n", i+1 );
				}
				printf("Operation calculating \n");
				fprintf(fpMainLog, "Operation calculating \n");
				if(makeOperation(strOps[iMathServerCount], strOpResult, dAParams, iParamSize) == 1)
				{
					kill(clientPid, SIGTSTP);
					kill(getpid(), SIGTSTP);
				}
				else
				{
					printf("Successfull op\n");
					fprintf(fpMainLog, "Successfull op\n");
				}
				
				printf("result \n%s\n", strOpResult);
				fprintf(fpMainLog, "results for  \n%s\n%s\n", strOpName, strOpResult);


				if((writeDesc = open(mathServerFifo, O_WRONLY)) == -1)
				{
					printf("math server fifo can not opened\n");
					fprintf(fpMainLog, "math server fifo can not opened\n");

					exit(0);
				}
				write(writeDesc, strOpResult, sizeof(char) * RESULT_SIZE);
				printf("Operation calculated and result has sent\n");
				fprintf(fpMainLog, "Operation calculated and result has sent\n");

				unlink(mathServerFifo);
				close(writeDesc);
				fclose(fpMainLog);
				exit(0);
			}
			else
			{
				char mathServerFifo[FIFO_NAME_SIZE];
				close(fd[1]);
				read(fd[0], mathServerFifo, FIFO_NAME_SIZE);
				iMathServerCount++;
				int mainFifo;
				if((mainFifo = open(strMainFifoName, O_WRONLY)) == -1)
				{
					printf("main server fifo can not opened\n");
					fprintf(fpMainLog, "main fifo can not opened\n");

					exit(0);
				}
				write(mainFifo, mathServerFifo, FIFO_NAME_SIZE);
				//waitpid(pid, NULL, WNOHANG);
			}
		}
		sleep(1);
	}

	
	close(iFifoDesc);
	fclose(fpMainLog);
	return 0;
}




void serverSigHandle(int signalNo)
{
	int i;

	for (i = 0; i < iMathServerCount; ++i)
	{
		kill(clients[i], SIGINT);
	}
	unlink(strMainFifoName);
    printf("\nCTRL-C has caught syncServer shutting down properly\n");
    fprintf(fpMainLog, "CTRL-C has caught syncServer shutting down properly\n");
    fclose(fpMainLog);
    exit(signalNo);
}


void mathServerSigHandle(int signalNo)
{
	unlink(strMathServerName);

    printf("\nCTRL-C has caught math server [%ld] shutting down properly\n", (long)getpid());
    fprintf(fpMainLog, "\nCTRL-C has caught math server [%ld] shutting down properly\n", (long)getpid());
	fclose(fpMainLog);    
    exit(signalNo);
}

void mathServerExSigHandle(int signalNo)
{
	unlink(strMathServerName);

    printf("\nException occur math server [%ld] shutting down properly\n", (long)getpid());
    fprintf(fpMainLog, "\nException occur math server [%ld] shutting down properly\n", (long)getpid());
	fclose(fpMainLog);  
    exit(signalNo);
}


void alarmHandler(int signalNo)
{
//	unlink(strMathServerName);
	iAlarmFlag = 1;
    printf("\n30 seconds alarm, math server [%ld] shutting down properly\n", (long)getpid());
    fprintf(fpMainLog, "\n30 seconds alarm, math server [%ld] shutting down properly\n", (long)getpid());
    fclose(fpMainLog);
    exit(signalNo);
}

int  makeOperation(char * strOpName, char *strOpResult, double *dParams, int iParamSize)
{
	int i, index;
	char *temp;
	int status = 0;

	if(strcmp(strOpName, "operation1") == 0)
	{
		for (i = 0; i < iParamSize; i+=3)
		{
			temp = operation1(dParams[i], dParams[i+1], dParams[i+2]);
			if(isException(temp) == 1)
			{
				fprintf(fpMainLog, "%s\n", temp);
				return 1;
			}
			strcat(strOpResult, temp);
			free(temp);
//			printf("%s\n", operation1(dParams[i], dParams[i+1], dParams[i+2]) );
		}

	}
	else if(strcmp(strOpName, "operation2") == 0)
	{
		for (i = 0; i < iParamSize; i+=2)
		{
			temp = operation2(dParams[i], dParams[i+1]);
			if(isException(temp) == 1)
			{
				fprintf(fpMainLog, "%s\n", temp);
				return 1;
			}
			strcat(strOpResult, temp);
			free(temp);
//			printf("%s\n", operation1(dParams[i], dParams[i+1], dParams[i+2]) );
		}

	}
	else if(strcmp(strOpName, "operation3") == 0)
	{
		for (i = 0; i < iParamSize; i+=3)
		{
			temp = operation3(dParams[i], dParams[i+1], dParams[i+2]);
			if(isException(temp) == 1)
			{
				fprintf(fpMainLog, "%s\n", temp);
				return 1;
			}		
			strcat(strOpResult, temp);
			free(temp);//			printf("%s\n", operation1(dParams[i], dParams[i+1], dParams[i+2]) );
		}

	}
	else if(strcmp(strOpName, "operation4") == 0)
	{
		for (i = 0; i < iParamSize; i+=4)
		{
			temp = operation4(dParams[i], dParams[i+1], dParams[i+2], dParams[i+3]);
			if(isException(temp) == 1)
			{
				fprintf(fpMainLog, "%s\n", temp);
				return 1;
			}

			strcat(strOpResult, temp);
			free(temp);//			printf("%s\n", operation1(dParams[i], dParams[i+1], dParams[i+2]) );
		}

	}
}


char * operation1(double a, double b, double c) //free
{
	char *strOpResult = (char *)(calloc(sizeof(char), RESULT_SIZE));
	if(c == 0.0)
		sprintf(strOpResult, "Division by zero exception !!\n");
	else
		sprintf(strOpResult, "%.2lf\n", sqrt(a*a + b*b) / fabs(c));

	return strOpResult;
}


char * operation2(double a, double b) //free
{
	char *strOpResult = (char *)(calloc(sizeof(char), RESULT_SIZE));
	if((a+b) < 0.0)
		sprintf(strOpResult, "Sum of parameters is negative !!\n");
	else
		sprintf(strOpResult, "%.2lf\n", sqrt((double)(a+b)));

	return strOpResult;
}


char * operation3(double a, double b, double c) //free
{
	char *strOpResult = (char *)(calloc(sizeof(char), RESULT_SIZE));
	int delta = (b*b - 4*a*c);
	if( delta < 0.0)
		sprintf(strOpResult, "Delta is negative !!\n");
	else
		sprintf(strOpResult, "Root 1: %.2lf -- Root 2: %.2lf", ((-1*b + sqrt(delta)) / 2*a), ((-1*b - sqrt(delta)) / 2*a));

	return strOpResult;
}


char * operation4(double a, double b, double c, double d) //free //not completed
{
	char *strOpResult = (char *)(calloc(sizeof(char), RESULT_SIZE));

	if(c == 0 && -1.0*a == 0)
		sprintf(strOpResult, "Te inverse is undefined\n");
	else
		sprintf(strOpResult, "(%.2lfx) + (%.2lf) / (%.2lfx) + (%.2lf))\n", -1.0*d, b, c, -1.0*a);
	
	return strOpResult;
}


int isException(char *result)
{
	if((strcmp(result,"Division by zero exception !!\n" ) == 0 		||
		strcmp(result,"Sum of parameters is negative !!\n" ) == 0 	||
		strcmp(result,"Delta is negative !!\n" ) == 0 				||
		strcmp(result,"Te inverse is undefined\n") == 0))
		return 1;

	return 0;
	
}