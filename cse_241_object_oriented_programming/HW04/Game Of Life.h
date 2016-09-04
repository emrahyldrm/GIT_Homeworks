/**********************************************************/
// Emrah YILDIRIM 111044056
// HW04_111044056.h


#ifndef FILE_H
#define FILE_H

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
		Cell(const int cX=-1, const int cY=-1) : x(cX), y(cY) { }	//constructor
		
		int takeCoor(void);	//nokta almak istenirse
		
		void printCell(void)	const;
		
		//getters
		inline int  getX(void)	const;
		inline int  getY(void)	const;
		
		//setters
		inline void setX(const int& cX);
		inline void setY(const int& cY);
		void setCell(const int& cX, const int& cY);
		
	
	private:
		int x, y;

};



class GameOfLife
{
	public:
		//constructor
		GameOfLife(const int row=0, const int col=0) : sizeRow(row), sizeCol(col) {} 
		
		//dosyadan okuma yapar dosya ismi alýr
		void readFile(const char *fileName);
		
		//vektorun tamamýný ekrana yazar
		void printVector(void)	const;
		//board u ekrana yazar
		void printBoard(void);
		//board u dosyaya yazar
		void write2File(const char *fileName);
		
		//setters
		void setRow(const int& row);
		void setCol(const int& col);
		
		//getters
		inline int getSizeRow(void)	const;
		inline int getSizeCol(void)	const;
		
		//hucrenin canli olup olmadigini kontrol eder
		bool isAlive(const Cell& cell);
		//ne kadar canli komsusu olduguna bakar
		//sayisini dondurur
		int howManyNB(const Cell& cell);
		//dogma ve oldurme islemlerini yapar
		int bornOrKill(const Cell& cell);
		//hucreyi oldurur
		bool killCell(const Cell& cell);
		
		//iki oyun objesini birlestirir
		void mergeGames(GameOfLife& other);
		void play(void);
		
		
		//vektordeki en uc satiri bulur
		int findMaxRow();
		//vektordeki en uc sutunu bulur
		int findMaxCol();
		//vektorleri esitler
		void syncVectors();
		//tum canli hucrelerin syisini dondurur
		static int getNumOfAlive() { return numOfAlive;}
		
	private:
		vector <Cell> livingsReal;	//degisim yapilan vektor
		vector <Cell> livingsControl;	//kontrol vektoru
		int sizeRow, sizeCol;
		static int numOfAlive;


};





















#endif