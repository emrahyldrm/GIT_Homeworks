#include<stdio.h>

int drawTree(int, int, int, char);
int drawTriangleWithSpace(int, int, char);
int drawRectangleWithSpace(int, int, int, char);


int Part2()
{
	int numberOfTriangles, truckHeight, truckWidth, numberChar;
	char ch, trash;
	
	printf("Please enter\n");
	printf("Number Of Triangles\n");
	scanf("%d", &numberOfTriangles);
	printf("Truck Height\n");
	scanf("%d", &truckHeight);
	printf("Truck WÝdth\n");
	scanf("%d", &truckWidth);
	printf("Character\n\n");
	scanf("%c%c%c", &trash, &ch, &trash);
	
	numberChar = drawTree(numberOfTriangles, truckHeight, truckWidth, ch);
	
	printf("\nnumber char = %d\n", numberChar);



	system("pause");
	return 0;
}


int drawTree(int numberOfTriangles, int truckHeight, int truckWidth, char ch)
{	
	int space, height, width, i, countChar=0;
	
	space = numberOfTriangles;
	height = 2;
	
	for (i=0; i < numberOfTriangles; i++)
	{
		countChar += drawTriangleWithSpace(height, space, ch);
		
		height += 1;
	}
	
	
	space = (((numberOfTriangles * 2) + 1 ) - (truckWidth))/2;
	height = truckHeight;
	width = truckWidth;
	
	drawRectangleWithSpace(height, width, space, ch);
	
	height = truckHeight;
	width = truckWidth;
	
	return countChar + truckHeight * truckWidth;
}

int drawTriangleWithSpace(int height, int space, char ch)
{
	int i, j;
	
	for (i=0; i < height; i++)
	{
		for (j=space*2; j > space; j--)
		{
			printf(" ");
		}
		space-=1;
		
		for (j=0; j<=2*i; j++)
		{
			printf("%c", ch);
		}
		printf("\n");
	}
	
	return height * height;
}

int drawRectangleWithSpace(int height, int width, int space, char ch)
{
	int i, j;
	
	for(i=1; i <= height; i++)
	{
		for (j=1; j <= space; j++)
		{
			printf(" ");
		}
		for (j=1; j <= width; j++)
		{
				printf("%c", ch);
		}
		
		printf("\n");
	}
	
	return height * width;
}




