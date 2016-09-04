#include"GameOfLife.h"

namespace HW06
{
	int GameOfLife::numOfAlive = 0;



	void GameOfLife::setRow(const int& row)
	{
		if (row >= 0 || row == -1000)
			sizeRow = row;
		else
		{
			cout << "wrong row index\n";

			exit(1);
		}
	}




	void GameOfLife::setCol(const int& col)
	{
		if (col >= 0 || col == -1000)
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


		for (int i = 0; i < sizeRow; ++i)
		{
			for (int j = 0; j < sizeCol; ++j)
			{
				fscanf(map, "%c", &cell);

				if (cell == 'X')
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

		for (int i = 0; i < sizeRow; ++i)
		{
			for (int j = 0; j < sizeCol; ++j)
			{
				if (isAlive(Cell(i, j)))
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
		int size = livingsReal.size(), max = 0, num = 0;

		for (int i = 0; i < size; ++i)
		{
			if ((num = livingsReal[i].getX()) > max)
				max = num;
		}
		return max;
	}



	int GameOfLife::findMaxCol()	const
	{
		int size = livingsReal.size(), max = 0, num = 0;

		for (int i = 0; i < size; ++i)
		{
			if ((num = livingsReal[i].getY()) > max)
				max = num;
		}
		return max;
	}



	int GameOfLife::bornOrKill(const Cell& cell)
	{
		int status = howManyNB(cell);


		//canliysa olecek mi diye bakar
		//yoksa da canlanacak mi
		if (isAlive(cell))
		{
			if (status < 2 || status > 3)
				killCell(cell);
		}
		else
		{
			if (status == 3)
			{
				livingsReal.push_back(cell);
				numOfAlive++;
			}
		}
		return 0;
	}




	int GameOfLife::howManyNB(const Cell& cell)
	{
		int counter = 0;
		int currentRow = cell.getX(), currentCol = cell.getY();


		if (isAlive(Cell(currentRow - 1, currentCol - 1)))
			counter++;
		if (isAlive(Cell(currentRow - 1, currentCol)))
			counter++;
		if (isAlive(Cell(currentRow - 1, currentCol + 1)))
			counter++;
		if (isAlive(Cell(currentRow, currentCol - 1)))
			counter++;
		if (isAlive(Cell(currentRow, currentCol + 1)))
			counter++;
		if (isAlive(Cell(currentRow + 1, currentCol - 1)))
			counter++;
		if (isAlive(Cell(currentRow + 1, currentCol)))
			counter++;
		if (isAlive(Cell(currentRow + 1, currentCol + 1)))
			counter++;

		return counter;
	}



	bool GameOfLife::isAlive(const Cell& cell)	const
	{
		int size = livingsControl.size();


		for (int i = 0; i < size; ++i)
		{
			if (livingsControl[i] == cell)
				return true;
		}
		return false;
	}





	bool GameOfLife::killCell(const Cell& cell)
	{
		int size = static_cast<int>(livingsReal.size());
		//oldurme yapilir eleman sayisi  azaltilir

		for (int i = 0; i < size; ++i)
		if (livingsReal[i] == cell)
		{
			livingsReal.erase(i);
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

		if (findMaxRow() >= sizeRow - 1 || findMaxCol() >= sizeCol - 1)
		{
			sizeRow++;
			sizeCol++;
		}

		for (int i = 0; i < sizeRow; ++i)
		{
			for (int j = 0; j < sizeCol; ++j)
				bornOrKill(Cell(i, j));
		}

		syncVectors();
		cout << endl;


		allGames.push_back(livingsReal);

		return *this;
	}


	//
	GameOfLife GameOfLife::operator ++(int ignore)
	{
		GameOfLife temp = *this;
		syncVectors();


		if (findMaxRow() >= sizeRow - 1 || findMaxCol() >= sizeCol - 1)
		{
			sizeRow++;
			sizeCol++;
		}

		for (int i = 0; i < sizeRow; ++i)
		{
			for (int j = 0; j < sizeCol; ++j)
				bornOrKill(Cell(i, j));
		}


		syncVectors();
		cout << endl;
		allGames.push_back(livingsReal);

		return temp;
	}



	//
	GameOfLife GameOfLife::operator +(const Cell& cell) const
	{
		GameOfLife temp = *this;

		if (!temp.isAlive(cell))
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




	GameOfLife GameOfLife::operator +(const GameOfLife& game) const
	{
		GameOfLife temp = game;
		int size = livingsReal.size();
		bool flag = false;

		for (int i = 0; i < size; ++i)
		if (!temp.isAlive(livingsReal[i]))
		{
			temp.livingsReal.push_back(livingsReal[i]);
			flag = true;
		}
		if (flag)
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

		for (int i = 0; i < size; ++i)
		if (temp.isAlive(game.livingsReal[i]))
			temp.killCell(game.livingsReal[i]);

		temp.syncVectors();
		temp.allGames.push_back(temp.livingsReal);

		return temp;
	}



	void GameOfLife::operator +=(const GameOfLife other)
	{
		int otherSize = other.livingsReal.size();
		bool flag = false;

		// hangi objenin board u daha buyukse ona gecilir
		// satir ve sutun ayri ayi kontrol edilir
		if (other.findMaxRow() > findMaxRow())
			setRow(other.getSizeRow());

		if (other.findMaxCol() > findMaxCol())
			setCol(other.getSizeCol());


		for (int i = 0; i < otherSize; ++i)
		{
			if (!isAlive(other.livingsReal[i]))
			{
				livingsReal.push_back(other.livingsReal[i]);
				flag = true;
			}

		}

		if (flag)
		{
			syncVectors();
			allGames.push_back(livingsReal);
		}
	}






	Cell GameOfLife::operator ()(int row, int col)
	{


		if (isAlive(Cell(row, col)))
			return Cell(row, col);
		else
			return Cell(-1000, 1000);
	}






	CellVector GameOfLife::operator [](int index)
	{
		int size = livingsReal.size();
		int counter = 0;
		bool flag = false;
		CellVector rTemp;
		CellVector tempVec(sizeCol);

		for (int i = 0; i < size; ++i)
		if (livingsReal[i].getX() == index)
			rTemp.push_back(livingsReal[i]);

		if (rTemp.size() == 0)
			tempVec.push_back(Cell(-1000, -1000));

		for (int i = 0; i < rTemp.size(); ++i)
		for (int j = 0; j < sizeCol && !flag; ++j)
		if (j == rTemp[i].getY())
			tempVec[j] = rTemp[i];

		return tempVec;
	}







	//prefix (return new variable)
	GameOfLife GameOfLife::operator --(void)
	{
		if (allGames.size() <= 0)
		{
			cout << "There is no movement for undo\n\n";
			return *this;
		}

		allGames.pop_back();
		livingsReal = allGames[allGames.size() - 1];
		syncVectors();

		return *this;
	}





	//postfix (return old variable)
	GameOfLife GameOfLife::operator --(int ignore)
	{
		GameOfLife temp = *this;
		if (allGames.size() <= 0)
		{
			cout << "There is no movement for undo\n\n";
			return temp;
		}

		allGames.pop_back();
		livingsReal = allGames[allGames.size() - 1];
		syncVectors();


		return temp;
	}



	GameOfLife operator +(const Cell& cell, const GameOfLife& game)
	{
		GameOfLife temp = game;

		if (!temp.isAlive(cell))
		{
			temp.livingsReal.push_back(cell);
			temp.syncVectors();
			temp.allGames.push_back(temp.livingsReal);
		}
		return temp;
	}



	ostream& operator <<(ostream& out, const GameOfLife& game)
	{
		for (int i = 0; i <= game.findMaxRow(); ++i)
		{
			for (int j = 0; j <= game.findMaxCol(); ++j)
			{
				if (game.isAlive(Cell(i, j)))
					out << "X";
				else
					out << ".";
			}
			out << endl;
		}

		return out;

	}



}