/*
EMRAH YILDIRIM 111044056
*/

#ifndef CELL_H
#define CELL_H

#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<vector>


using namespace std;

namespace HW06
{
	class Cell
	{
	public:
		Cell(const int cX = -1000, const int cY = -1000) : x(cX), y(cY) { }	//constructor

		int takeCoor(void);	//nokta almak istenirse

		void printCell(void)	const;

		//getters
		int  getX(void)	const;
		int  getY(void)	const;

		//setters
		inline void setX(const int& cX);
		inline void setY(const int& cY);
		void setCell(const int& cX, const int& cY);

		//operators
		//void operator = (vector<Cell>& right);

		bool operator < (const Cell& other)	const;
		bool operator > (const Cell& other)	const;

		bool operator >= (const Cell& other) const;
		bool operator <= (const Cell& other) const;

		bool operator == (const Cell& other) const;
		bool operator != (const Cell& other) const;

		Cell  operator ++(int ignore);
		Cell& operator ++(void);

		Cell  operator --(int ignore);
		Cell& operator --(void);

		friend ostream& operator << (ostream& out, const Cell& cell);
		friend istream& operator >> (istream& inp, Cell& cell);

	private:
		int x, y;

	};

	ostream& operator << (ostream& out, const Cell& cell);
	istream& operator >> (istream& inp, Cell& cell);

}
#endif