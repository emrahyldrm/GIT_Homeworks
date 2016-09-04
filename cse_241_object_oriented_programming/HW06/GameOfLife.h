#ifndef GAME_OF_LIFE_H
#define GAME_OF_LIFE_H

#include"Cell.h"
#include"CellVector.h"
#include"Cell2DVector.h"
#include<iostream>
#include<cstdlib>
#include<cstdio>
 
//using namespace HW06;

namespace HW06
{
	class GameOfLife
	{
	public:
		//constructor
		GameOfLife(const int row = -1000, const int col = -1000) :
			sizeRow(row), sizeCol(col)
		{
			if (row < 0 && row != -1000 && col < 0 && col != 1000)
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
		static int getNumOfAlive() { return numOfAlive; } //tum canli hucrelerin sayisini dondurur


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

		CellVector operator [](int index);



		friend ostream& operator <<(ostream& out, const GameOfLife& game);

	private:
		CellVector livingsReal;	//degisim yapilan vektor
		CellVector livingsControl;	//kontrol vektoru
		Cell2DVector allGames;
		int sizeRow, sizeCol;
		static int numOfAlive;


	};

	GameOfLife operator +(const Cell& cell, const GameOfLife& game);
	ostream& operator <<(ostream& out, const GameOfLife& game);


}

#endif