#ifndef CELL_VECTOR_H
#define CELL_VECTOR_H

#include<iostream>
#include<cstdlib>
#include<cstdio>
#include"Cell.h"

using namespace std;
//using namespace HW06;

namespace HW06
{
	class CellVector
	{
	public:
	//constructros
		CellVector();
		CellVector(int wsize);
		CellVector(const CellVector& other); //copy constructor
		~CellVector();		//destructor

		void push_back(const Cell& cell);

		void pop_back();
		int size(void)	const { return sizeV; }
		int capacity(void)	 const { return capacityV; }
		void erase(int index);

		friend ostream& operator << (ostream& out, const CellVector& cellVector);

		CellVector& operator =(const CellVector& other);
		const Cell& operator [](int index) const; // r-value
		Cell& operator[](int index);		//l-value

	private:
		Cell *vector;
		int sizeV, capacityV;
	};


	ostream& operator << (ostream& out, const CellVector& cellVector);


}








#endif