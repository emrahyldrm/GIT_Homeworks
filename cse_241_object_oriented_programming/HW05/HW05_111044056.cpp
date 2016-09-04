/**********************************************************/
// Emrah YILDIRIM 111044056
// HW05_111044056.cpp


#include"HW05_111044056.h"


int Cell::takeCoor(void)
{
	int coor;
	
	cin >> coor;
	
	return coor;
}


void Cell::printCell(void)	const
{
	cout << getX() << "." << getY() <<" ";
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



void Cell::operator = (vector<Cell>& right)
{
	cout <<"assign\n";
	*this = right[0];
}




bool Cell::operator < (const Cell& other)	const
{

	if(getX() < other.getX())
		return true;
	else
	if( (getX() == other.getX()) && getY() < other.getY())
		return true;
	else
		return false;
}


bool Cell::operator > (const Cell& other)	const
{
	if(getX() > other.getX())
		return true;
	else
	if( (getX() == other.getX()) && getY() > other.getY())
		return true;
	else
		return false;
}


bool Cell::operator >= (const Cell& other)	const
{
	if(*this > other || *this == other)
		return true;
	
	else
		return false;


}



bool Cell::operator <= (const Cell& other)	const
{
	if(*this < other ||  *this == other)
		return true;
	
	else
		return false;


}


bool Cell::operator == (const Cell& other)	const
{
	if(x == other.x && y == other.y)
		return true;
	else 
		return false;
}



bool Cell::operator != (const Cell& other)	const
{
	if(x != other.x || y != other.y)
		return true;
	else 
		return false;
}



ostream& operator << (ostream& out, const Cell& cell)
{
	out << cell.x <<"." <<cell.y<<endl;
	
	return out;
}


istream& operator >> (istream& inp, Cell& cell)
{	
	inp >> cell.x >> cell.y;
	
	if(cell.x >=0 && cell.y >= 0) 
		return inp;
	else
	{
		cout <<"wrong cell coordinates\n";
		exit(1);
	}
}

/*****************************************************************************/



int GameOfLife::numOfAlive = 0;



void GameOfLife::setRow(const int& row)
{
	if(row >= 0 || row == -1000)
		sizeRow = row;
	else
	{
		cout << "wrong row index\n";
		
		exit(1);
	}
}




void GameOfLife::setCol(const int& col)
{
	if(col >= 0 || col == -1000)
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
				
		}
	
		fscanf(map, "%c", &trash);
	}	
	
	syncVectors();
	
	numOfAlive += livingsReal.size();
	fclose(map);
	
}



void GameOfLife::write2File(const char *fileName)
{
	FILE *outFile;
	
	outFile = fopen(fileName, "w");

	syncVectors();
	
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




int GameOfLife::findMaxRow()	const
{
	int size = livingsReal.size(), max=0, num=0;
	
	for(int i=0; i < size; ++i)
	{
		if((num=livingsReal[i].getX()) > max)
			max=num;
	}
	return max;
}



int GameOfLife::findMaxCol()	const
{
	int size = livingsReal.size(), max=0, num=0;
	
	for(int i=0; i < size; ++i)
	{
		if((num=livingsReal[i].getY()) > max)
			max=num;
	}
	return max;
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



bool GameOfLife::isAlive(const Cell& cell)	const
{
	int size = livingsControl.size();
	
	
	
	for(int i=0; i < size; ++i)
	{
		if(livingsControl[i] == cell)
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
		if(livingsReal[i] == cell)
		{
			point = livingsReal.begin() + i;
			livingsReal.erase(point);
			
			numOfAlive--;
			
			return true;
		}
		
	return false;
}



inline void GameOfLife::syncVectors()
{
	livingsControl = livingsReal;
}



///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
//						OPERATORS


//
GameOfLife GameOfLife::operator ++(void)
{
	GameOfLife temp;
	
	syncVectors();
	
	if( findMaxRow() >= sizeRow-1 || findMaxCol() >= sizeCol-1)
	{
	   sizeRow++;
		sizeCol++;
	}
	
	for(int i=0; i < sizeRow; ++i)
	{	
		for(int j=0; j < sizeCol; ++j)
			bornOrKill(Cell(i,j));	
	}
	
	syncVectors();
	cout <<endl;
	
	
	allGames.push_back(livingsReal);

	return *this;
}


//
GameOfLife GameOfLife::operator ++(int ignore)
{
	GameOfLife temp = *this;
	syncVectors();
	
	if( findMaxRow() >= sizeRow-1 || findMaxCol() >= sizeCol-1)
	{
	   sizeRow++;
		sizeCol++;
	}
	
	for(int i=0; i < sizeRow; ++i)
	{	
		for(int j=0; j < sizeCol; ++j)
			bornOrKill(Cell(i,j));	
	}
	
	syncVectors();
	cout <<endl;
	
	allGames.push_back(livingsReal);	
	
	return temp;
}



//
GameOfLife GameOfLife::operator +(const Cell& cell) const
{
	GameOfLife temp = *this;
	
	if(!temp.isAlive(cell))
	{
		temp.livingsReal.push_back(cell);
		temp.syncVectors();
		temp.allGames.push_back(temp.livingsReal);
	}
	return temp;
}


//
GameOfLife GameOfLife::operator -(const Cell& cell) const
{
	GameOfLife temp = *this;
	
	temp.killCell(cell);
	temp.syncVectors();
	temp.allGames.push_back(temp.livingsReal);
	
	return temp;
}


GameOfLife operator +(const Cell& cell, const GameOfLife& game) 
{
	GameOfLife temp = game;
	
	if(!temp.isAlive(cell))
	{
		temp.livingsReal.push_back(cell);
		temp.syncVectors();
		temp.allGames.push_back(temp.livingsReal);
	}
	return temp;
}


GameOfLife GameOfLife::operator +(const GameOfLife& game) const
{
	GameOfLife temp=game;
	int size = livingsReal.size();
	bool flag =false;
	
	for(int i=0; i < size; ++i)
		if(!temp.isAlive(livingsReal[i]))
		{
			temp.livingsReal.push_back(livingsReal[i]);
			flag=true;
		}
	if(flag)
	{
		temp.syncVectors();
		temp.allGames.push_back(temp.livingsReal);
	}
	
	return temp;
}


//
GameOfLife GameOfLife::operator -(const GameOfLife& game) const
{
	GameOfLife temp = *this;
	int size = game.livingsReal.size();

	for(int i=0; i < size; ++i)
		if(temp.isAlive(game.livingsReal[i]))
			temp.killCell(game.livingsReal[i]);	

	temp.syncVectors();
	temp.allGames.push_back(temp.livingsReal);
	
	return temp;
}



void GameOfLife::operator +=(const GameOfLife other)
{
	int otherSize = other.livingsReal.size();
	bool flag=false;
	
	// hangi objenin board u daha buyukse ona gecilir
	// satir ve sutun ayri ayi kontrol edilir
	if(other.findMaxRow() > findMaxRow())
		setRow(other.getSizeRow());
	
	if(other.findMaxCol() > findMaxCol())
		setCol(other.getSizeCol());
		
	
	for(int i=0; i < otherSize; ++i)
	{
		if(!isAlive(other.livingsReal[i]))
		{
			livingsReal.push_back(other.livingsReal[i]);
			flag = true;
		}
	
	}

	if(flag)
	{
		syncVectors();
		allGames.push_back(livingsReal);
	}
}


//
ostream& operator <<(ostream& out, const GameOfLife& game)
{
	for(int i=0; i <= game.findMaxRow(); ++i)
	{	
		for(int j=0; j <= game.findMaxCol(); ++j)
		{
			if(game.isAlive(Cell(i,j)))
				out<<"X";
			else
				out<<".";
		}
		out<<endl;
	}

	return out;
}




Cell GameOfLife::operator ()(int row, int col)
{
	
	
	if(isAlive(Cell(row,col)))
		return Cell(row, col);
	else
		return Cell(-1000, 1000);
}



vector<Cell> GameOfLife::operator [](int index)
{
	int size=livingsReal.size();
	int counter=0;
	bool flag = false;
	vector<Cell> rTemp;
	vector<Cell> tempVec(sizeCol);
	
	for(int i=0; i < size; ++i)
			if(livingsReal[i].getX() == index)
				rTemp.push_back(livingsReal[i]);
			

	if(rTemp.size() == 0)
		tempVec.push_back(Cell(-1000,-1000));

	for(int i=0; i < rTemp.size(); ++i)
		for(int j=0; j < sizeCol && !flag; ++j)
			if(j == rTemp[i].getY())
				tempVec[j] = rTemp[i];
			
			
	
	return tempVec;
}




//prefix (return new variable)
GameOfLife GameOfLife::operator --(void)
{
	
	cout << allGames.size()<<endl;
	
	allGames.pop_back();
	livingsReal = allGames[allGames.size() - 1];
	syncVectors();
	
	return *this;
}





//postfix (return old variable)
GameOfLife GameOfLife::operator --(int ignore)
{
	GameOfLife temp = *this;
	
	cout << allGames.size()<<endl;
	
	allGames.pop_back();
	livingsReal = allGames[allGames.size() - 1];
	syncVectors();
	

	return temp;
}

