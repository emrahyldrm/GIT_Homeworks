/*----------------clientX.c----------------------*/
/*--SYSTEM PROGRAMMING MIDTERM PROJECT-----------*/
/*Author:Emrah YILDIRIM--------------------------*/
/*111044056                 ---------------------*/
/*Date:15/04/2014 			---------------------*/
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


char strMathServer[FIFO_NAME_SIZE];
pid_t pMathServerPid;
FILE* fpLog;


void sigHandle(int signalNo);	
int isOp(const char *op);
int minusControl(char **argv, int argc);

void sigHandle(int signalNo);
void pipeSignalHandle(int signalNo);
void mathServerExSigHandle(int signalNo);


void  printResult(char * strOpName, char *strOpResult, double *dParams, int iParamSize);


int main(int argc, char **argv)
{
	signal(SIGINT, sigHandle);
	signal(SIGPIPE, pipeSignalHandle);
	signal(SIGTSTP, mathServerExSigHandle);

	pid_t pPid;
	pPid = getpid();
	char cAlogFile[FIFO_NAME_SIZE];
	sprintf(cAlogFile, "client-%d", pPid);
	fpLog = fopen(cAlogFile, "w");


	char strFifo[FIFO_NAME_SIZE];
	int iWait;
	char strOpName[OP_NAME_SIZE];
	double dParams[MAX_PARAM];
	int i;
	int iParamSize=0;
	char strOpResult[RESULT_SIZE];
	struct tm *cTime;
	int fifoReadDesc, fifoWriteDesc;

	char clientName[FIFO_NAME_SIZE];	

	system("clear");

	/*******************************************************************************************************/
	//Check paramaters
	if(argc < 6)
	{
		printf("missing argument(s)\n");
		printf("USAGE: ./clientX -fifoName -waitTime -operationName -param1 -param2 ..\n");

		fprintf(fpLog, "missing argument(s)\n");
		fprintf(fpLog, "USAGE: ./clientX -fifoName -waitTime -operationName -param1 -param2 ..\n");
		fclose(fpLog);
		return 0;
	}
	else if(minusControl(argv, argc) == 0)
	{
		printf("Illegal command entry\n");
		printf("USAGE: ./clientX -fifoName -waitTime -operationName -param1 -param2 ..\n");
		
		fprintf(fpLog, "Illegal command entry\n");
		fprintf(fpLog, "USAGE: ./clientX -fifoName -waitTime -operationName -param1 -param2 ..\n");
		fclose(fpLog);
		exit(0);
	}
	else
	{
		strcpy(strFifo, &argv[1][1]);
		iWait = atoi(&argv[2][1]);
		if(iWait < 0)
		{
			printf("Illegal wait time (negative)\n");
			fprintf(fpLog, "Illegal wait time (negative)\n");
			fclose(fpLog);
			exit(0);
		}
		strcpy(strOpName, &argv[3][1]);
		if(isOp(strOpName) == 0)
		{
			printf("Illegal operation name (operation1 - operation2 - operation3 - operation4)\n");
			fprintf(fpLog, "Illegal operation name (operation1 - operation2 - operation3 - operation4)\n");
			fclose(fpLog);
			exit(0);
		}
		for (i = 0; i < argc - 4; ++i)
		{
			dParams[i] = atof(&argv[i+4][1]);
			iParamSize++;
		}
		if((i % 3 != 0 && strcmp(strOpName, "operation1") == 0) || (i%3 != 0 && strcmp(strOpName, "operation3")==0) ||
		   (i % 2 != 0 && strcmp(strOpName, "operation2") == 0) || (i%4 != 0 && strcmp(strOpName, "operation4") == 0))
		{
			printf("Missing parameter(s)\n");
			fprintf(fpLog, "Missing parameter(s)\n");
			fclose(fpLog);
			exit(0);
		}


	}

	/*******************************************************************************************************/

/*	printf("%s\n%d\n%s\n",strFifo, iWait, strOpName );
	for (i = 0; i < argc - 4; ++i)
	{
		printf("%.2lf\n", dParams[i]);
	}*/
	


	if((fifoWriteDesc = open(strFifo, O_WRONLY)) == -1)
	{
		printf("fifo can not opened\n");
		fprintf(fpLog, "fifo can not opened\n");
		
		fclose(fpLog);
		exit(0);
	}
	write(fifoWriteDesc, strOpName, OP_NAME_SIZE);
	write(fifoWriteDesc, &pPid, sizeof(pid_t) );
	close(fifoWriteDesc);

	if((fifoReadDesc = open(strFifo, O_RDONLY)) == -1)
	{
		printf("fifo can not opened\n");
		fprintf(fpLog, "fifo can not opened\n");
		fclose(fpLog);
		exit(0);
	}

	usleep(500);
	read(fifoReadDesc, strMathServer, FIFO_NAME_SIZE);
	close(fifoReadDesc);

	printf("taken fifo name is %s %d\n", strMathServer, getpid());
	fprintf(fpLog, "taken fifo name is %s   %d\n", strMathServer, pPid);
	

	sleep(0.5);
	int mathServerReadDesc = open(strMathServer, O_RDONLY);
	read(mathServerReadDesc, &pMathServerPid, sizeof(pid_t));
	close(mathServerReadDesc);

	int mathServerWriteDesc = open(strMathServer, O_WRONLY);
	if(mathServerWriteDesc == -1)
	{
		printf("fifo can not opened\n");
		fprintf(fpLog, "fifo can not opened\n");
		fclose(fpLog);
		exit(0);
	}

	//kontrol
	//sleep(iWait);
	write(mathServerWriteDesc, &pPid, sizeof(int));
	write(mathServerWriteDesc, &iParamSize, sizeof(int));
	write(mathServerWriteDesc, dParams, sizeof(double) * MAX_PARAM);
	write(mathServerWriteDesc, &iWait, sizeof(int));
	close(mathServerWriteDesc);

//	printf("(%.2lfx) + (%.2lf) / (%.2lfx) + (%.2lf))", dParams[0], dParams[1], dParams[2], dParams[3]);

	sleep(1);
	mathServerReadDesc = open(strMathServer, O_RDONLY);
	if(mathServerReadDesc == -1)
	{
		printf("fifo can not opened\n");
		fprintf(fpLog, "fifo can not opened\n");
		fclose(fpLog);
		exit(0);
	}
	int size;
	while( (size =read(mathServerReadDesc, strOpResult, RESULT_SIZE)) == 0)
	{
		sleep(0.01);
	}
	close(mathServerReadDesc);

	printf("\n-------------RESULTS-------------\n\n");
	printf("%s", strOpResult);
	printf("\n---------------------------------\n\n");

	fprintf(fpLog, "\n-------------RESULTS-------------\n\n");
	fprintf(fpLog, "I am client with %d pid and i asked for %s from math server\n", pPid, strOpName);
	fprintf(fpLog, "The results for ");
	for (i = 0; i < iParamSize; ++i)
	{
		fprintf(fpLog, " %.2lf", dParams[i]);
	}

	fprintf(fpLog, "\n\n%s", strOpResult);
	fprintf(fpLog, "\n---------------------------------\n\n");



	fclose(fpLog);
	return 0;
}

int isOp(const char *op)
{
	if(strcmp(op, "operation1") != 0 && strcmp(op, "operation2") != 0 && 
	   strcmp(op, "operation3") != 0 && strcmp(op, "operation4") != 0)
		return 0;
	else
		return 1;
}

int minusControl(char **argv, int argc)
{
	int i;
	int iCounter=0;

	for (i = 1; i < argc; ++i)
	{
		if(argv[i][0] == '-')
			iCounter++;
	}

	return iCounter == argc-1;
}

void mathServerExSigHandle(int signalNo)
{

	printf("\nException occur, client shutting down\n");
	fprintf(fpLog, "\nException occur, client shutting down\n");
	fclose(fpLog);
    exit(signalNo);
}



void sigHandle(int signalNo)
{
	kill(pMathServerPid, SIGINT);
	printf("\nCTRL-C has caught shutting down\n");
	fprintf(fpLog, "\nCTRL-C has caught shutting down\n");
	fclose(fpLog);
	exit(signalNo);
}

void pipeSignalHandle(int signalNo)
{
	printf("\nServer timeout, client shutting down\n");
	fprintf(fpLog, "\nServer timeout, client shutting down\n");
 	fclose(fpLog);
 	exit(signalNo);
}


void  printResult(char * strOpName, char *strOpResult, double *dParams, int iParamSize)
{
	int i, index;
	char *temp;

	if(strcmp(strOpName, "operation1") == 0)
	{
		printf("(a^2 + b^2 ) / |c|\n");
		printf("For %.2lf %.2lf %.2lf ==> %s\n", dParams[0], dParams[1], dParams[2], strtok(strOpResult, "\n"));
		for (i = 3; i < iParamSize; i+=3)
		{
			printf("For %.2lf %.2lf %.2lf ==> %s\n", dParams[i], dParams[i+1], dParams[i+2], strtok(NULL, "\n"));
//			printf("%s\n", operation1(dParams[i], dParams[i+1], dParams[i+2]) );
		}

	}
	else if(strcmp(strOpName, "operation2") == 0)
	{
		printf("sqrt(a + b)\n");
		printf("For %.2lf %.2lf ==> %s\n", dParams[0], dParams[1], strtok(strOpResult, "\n"));
		for (i = 2; i < iParamSize; i+=2)
		{
			printf("For %.2lf %.2lf ==> %s\n", dParams[i], dParams[i+1], strtok(NULL, "\n"));
//			printf("%s\n", operation1(dParams[i], dParams[i+1], dParams[i+2]) );
		}

	}
	else if(strcmp(strOpName, "operation3") == 0)
	{
		printf("(roots of ax^2 + bx + c)\n");
		printf("For %.2lf %.2lf %.2lf ==> %s\n", dParams[0], dParams[1], dParams[2], strtok(strOpResult, "\n"));
		for (i = 3; i < iParamSize; i+=3)
		{
			printf("For %.2lf %.2lf %.2lf ==> %s\n", dParams[i], dParams[i+1], dParams[i+2], strtok(NULL, "\n"));
//			printf("%s\n", operation1(dParams[i], dParams[i+1], dParams[i+2]) );
		}
	}
	else if(strcmp(strOpName, "operation4") == 0)
	{
		printf("inverse of (ax + b / cx + d)\n");	
		printf("For %.2lf %.2lf %.2lf %.2lf ==> %s\n", dParams[0], dParams[1], dParams[2], dParams[3], strtok(NULL, "\n"));
		for (i = 4; i < iParamSize; i+=4)
		{
			printf("For %.2lf %.2lf %.2lf %.2lf ==> %s\n", dParams[i], dParams[i+1], dParams[i+2], dParams[i+3], strtok(NULL, "\n"));
//			printf("%s\n", operation1(dParams[i], dParams[i+1], dParams[i+2]) );
		}

	}
}
