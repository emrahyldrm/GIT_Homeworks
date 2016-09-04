#ifndef CELL_2D_VECTOR_H
#define CELL_2D_VECTOR_H

#include <iostream>
#include "CellVector.h"

using namespace std;

namespace HW06
{

	class Cell2DVector
	{
	public:
		Cell2DVector();
		Cell2DVector(const Cell2DVector& other);
		~Cell2DVector();

		void push_back(const CellVector& vector);
		void pop_back(void);
		int size(void) const { return size2D; }
		int capacity(void) const { return capacity2D; }
		void erase(int index);

		Cell2DVector& operator =(const Cell2DVector& other);
		CellVector& operator [](int index);
		const CellVector& operator [](int index) const;


	private:
		CellVector *all;
		int size2D, capacity2D;
	};


}


#endif

