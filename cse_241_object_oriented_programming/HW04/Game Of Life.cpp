/**********************************************************/
// Emrah YILDIRIM 111044056
// HW04_111044056.cpp


#include"file.h"


int Cell::takeCoor(void)
{
	int coor;
	
	cin >> coor;
	
	return coor;
}


void Cell::printCell(void)	const
{
	cout << getX() << "." << getY() <<endl;
}


inline int  Cell::getX(void)	const
{
	return x;
}


inline int  Cell::getY(void)	const
{
	return y;
}


inline void Cell::setX(const int& cX)
{
	x =cX;
}


inline void Cell::setY(const int& cY)
{
	x =cY;
}


void Cell::setCell(const int& cX, const int& cY)
{
	x = cX;
	y = cY;
}


/*****************************************************************************/



int GameOfLife::numOfAlive = 0;



void GameOfLife::setRow(const int& row)
{
	if(row >= 0)
		sizeRow = row;
	else
	{
		cout << "wrong row index\n";
		
		exit(1);
	}
}




void GameOfLife::setCol(const int& col)
{
	if(col >= 0)
		sizeCol = col;
	else
	{
		cout << "wrong column index\n";
		exit(1);
	}
}


inline int GameOfLife::getSizeRow(void) const
{
	return sizeRow;
}

inline int GameOfLife::getSizeCol(void) const
{
	return sizeCol;
}



void GameOfLife::readFile(const char *fileName)
{
	FILE *map;
	char cell, trash;
	
	map = fopen(fileName, "r");
	
	
	
	fscanf(map, "%d%d%c", &sizeRow, &sizeCol, &trash);
	
	
	for(int i=0; i < sizeRow; ++i)
	{
		for(int j=0; j < sizeCol; ++j)
		{
			fscanf(map, "%c", &cell);
			
			if(cell == 'X')
				livingsReal.push_back(Cell(i, j));
				// tek 1 obje oluþturmayý da dene 
				
		}
	
		fscanf(map, "%c", &trash);
	}	
	
	//eleman sayisi artirilir
	numOfAlive += livingsReal.size();
	fclose(map);
	
}



void GameOfLife::write2File(const char *fileName)
{
	FILE *outFile;
	
	outFile = fopen(fileName, "w");

	
	for(int i=0; i < sizeRow; ++i)
	{	
		for(int j=0; j < sizeCol; ++j)
		{
			if(isAlive(Cell(i,j)))
				fprintf(outFile, "X");
			else
				fprintf(outFile, ".");
		}
		fprintf(outFile, "\n");
	}

	fclose(outFile);
}


void GameOfLife::printVector()	const
{
	int size = livingsReal.size();

	for(int i=0; i < size; ++i)
		livingsReal[i].printCell();
		

}



void GameOfLife::printBoard()
{
	for(int i=0; i < sizeRow; ++i)
	{	
		for(int j=0; j < sizeCol; ++j)
		{
			if(isAlive(Cell(i,j)))
				cout<<"X";
			else
				cout<<".";
		}
		cout<<endl;
	}
}


int GameOfLife::findMaxRow()
{
	int size = livingsReal.size(), max=0, num=0;
	
	for(int i=0; i < size; ++i)
	{
		if((num=livingsReal[i].getX()) > max)
			max=num;
	}
	return max;
}



int GameOfLife::findMaxCol()
{
	int size = livingsReal.size(), max=0, num=0;
	
	for(int i=0; i < size; ++i)
	{ 
		if((num=livingsReal[i].getY()) > max)
			max=num;
	}
	return max;
}


void GameOfLife::play(void)
{
	
	syncVectors();
	printBoard();

	for(int i=0; i < sizeRow; ++i)
	{	
		for(int j=0; j < sizeCol; ++j)
			bornOrKill(Cell(i,j));	
	}
	
	if( findMaxRow() >= sizeRow-1 || findMaxCol() >= sizeCol-1)
	{
	   sizeRow++;
		sizeCol++;
	}
	cout <<endl;
	syncVectors();
	

}



int GameOfLife::bornOrKill(const Cell& cell)
{
	int status = howManyNB(cell);
	
	//canliysa olecek mi diye bakar
	//yoksa da canlanacak mi
	if(isAlive(cell))
	{	
		if(status < 2 || status > 3)
			killCell(cell);
	}
	else
	{
		if(status == 3)
		{
			livingsReal.push_back(cell);
			numOfAlive++;
		}
	}

}




int GameOfLife::howManyNB(const Cell& cell)
{
	int counter=0;
	int currentRow = cell.getX(), currentCol = cell.getY();
	
	
	if(isAlive(Cell(currentRow-1, currentCol-1)))
		counter++;
	if(isAlive(Cell(currentRow-1, currentCol)))
		counter++;
	if(isAlive(Cell(currentRow-1, currentCol+1)))
		counter++;
	if(isAlive(Cell(currentRow, currentCol-1)))
		counter++;
	if(isAlive(Cell(currentRow, currentCol+1)))
		counter++;
	if(isAlive(Cell(currentRow+1, currentCol-1)))
		counter++;
	if(isAlive(Cell(currentRow+1, currentCol)))
		counter++;
	if(isAlive(Cell(currentRow+1, currentCol+1)))
		counter++;
	
	return counter;
}



bool GameOfLife::isAlive(const Cell& cell)
{
	int size = livingsControl.size();
	
	
	for(int i=0; i < size; ++i)
	{
		if(livingsControl[i].getX() == cell.getX() &&
		   livingsControl[i].getY() == cell.getY())
			return true;
	}		
	return false;
}





bool GameOfLife::killCell(const Cell& cell)
{
	vector<Cell>::iterator point;
	int size=static_cast<int>(livingsReal.size());
	
	//oldurme yapilir eleman sayisi  azaltilir
	for(int i=0; i < size; ++i)
		if(livingsReal[i].getX() == cell.getX() && livingsReal[i].getY() == cell.getY())
		{
			point = livingsReal.begin() + i;
			livingsReal.erase(point);
			
			numOfAlive--;
			return true;
		}
	return false;
}



void GameOfLife::mergeGames(GameOfLife& other)
{
	int otherSize= other.livingsReal.size();
	
	// hangi objenin board u daha buyukse ona gecilir
	//satir ve sutun ayri ayi kontrol edilir
	if(other.findMaxRow() > findMaxRow())
		setRow(other.getSizeRow());
	
	if(other.findMaxCol() > findMaxCol())
		setCol(other.getSizeCol());
		
	
	for(int i=0; i < otherSize; ++i)
	{
		livingsReal.push_back(other.livingsReal[i]);
	
	}
}



void GameOfLife::syncVectors()
{
	livingsControl = livingsReal;
}

