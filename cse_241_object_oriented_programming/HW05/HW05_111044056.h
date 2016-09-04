/**********************************************************/
// Emrah YILDIRIM 111044056
// HW05_111044056.h


#ifndef HW05_111044056_H
#define HW05_111044056_H

#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<vector>
#include<iterator>

using namespace std;

class Cell;
class GameOfLife;


class Cell
{
	public:
		Cell(const int cX=-1000, const int cY=-1000) : x(cX), y(cY) { }	//constructor
		
		int takeCoor(void);	//nokta almak istenirse
		
		void printCell(void)	const;
			
		//getters
		inline int  getX(void)	const;
		inline int  getY(void)	const;
		
		//setters
		inline void setX(const int& cX);
		inline void setY(const int& cY);
		void setCell(const int& cX, const int& cY);
		
		//operators
		void operator = (vector<Cell>& right);
		
		bool operator < (const Cell& other)	const;
		bool operator > (const Cell& other)	const;
		bool operator >= (const Cell& other)	const;
		bool operator <= (const Cell& other)	const;
		bool operator == (const Cell& other)	const;
		bool operator != (const Cell& other)	const;
		friend ostream& operator << (ostream& out, const Cell& cell);
		friend istream& operator >> (istream& inp, Cell& cell);
		bool operator [](int b);
	
	private:
		int x, y;

};



class GameOfLife
{
	public:
		//constructor
		GameOfLife(const int row=-1000, const int col=-1000 ) : 
					sizeRow(row), sizeCol(col)
		{
			if(row < 0 && row != -1000 && col < 0 && col != 1000 )
			{
				cout << "wrong col or row index\n";
				
				exit(1);
			}
		
		} 
		
		//dosyadan okuma yapar dosya ismi alýr
		void readFile(const char *fileName);
		
		//board u dosyaya yazar
		void write2File(const char *fileName);
		
		//setters
		void setRow(const int& row);
		void setCol(const int& col);
		
		//getters
		inline int getSizeRow(void)	const;
		inline int getSizeCol(void)	const;
		
		//hucrenin canli olup olmadigini kontrol eder
		bool isAlive(const Cell& cell) const;
		//ne kadar canli komsusu olduguna bakar
		//sayisini dondurur
		int howManyNB(const Cell& cell);
		//dogma ve oldurme islemlerini yapar
		int bornOrKill(const Cell& cell);
		//hucreyi oldurur
		bool killCell(const Cell& cell);

		
		int findMaxRow()const;	//vektordeki en uc satiri bulur
		int findMaxCol()const;	//vektordeki en uc sutunu bulur
		inline void syncVectors();	//vektorleri esitler
		static int getNumOfAlive() { return numOfAlive;} //tum canli hucrelerin sayisini dondurur
		
		
		//operators
		
		GameOfLife operator ++(void);	//prefix
		GameOfLife operator ++(int ignore);	//postfix
		GameOfLife operator --(void);
		GameOfLife operator --(int ignore);
		
		GameOfLife operator +(const Cell& cell) const;
		friend GameOfLife operator +(const Cell& cell, const GameOfLife& game);
		GameOfLife operator -(const Cell& cell)	const;

		GameOfLife operator +(const GameOfLife& game) const;
		GameOfLife operator -(const GameOfLife& game) const;
		
		void operator +=(const GameOfLife other);
		
		Cell operator ()(int row, int col);
		
		vector<Cell> operator [](int index);
		
		
		
		friend ostream& operator <<(ostream& out, const GameOfLife& game);
		
	private:
		vector <Cell> livingsReal;	//degisim yapilan vektor
		vector <Cell> livingsControl;	//kontrol vektoru
		vector <vector <Cell> > allGames;
		int sizeRow, sizeCol;
		static int numOfAlive;


};



GameOfLife operator +(const Cell& cell, const GameOfLife& game);
ostream& operator <<(ostream& out, const GameOfLife& game);


ostream& operator << (ostream& out, const Cell& cell);
istream& operator >> (istream& inp, Cell& cell);
		













#endif