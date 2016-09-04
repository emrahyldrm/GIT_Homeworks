#include"CellVector.h"

namespace HW06
{

	CellVector::CellVector() : sizeV(0), capacityV(10) 
	{
		vector = new Cell[capacityV];
	}


	CellVector::CellVector(int wsize) : sizeV(wsize), capacityV(wsize + 10)
	{
		vector = new Cell[wsize + 10];
	}


	CellVector::CellVector(const CellVector& other) : sizeV(other.sizeV), capacityV(other.capacityV)
	{
		vector = new Cell[capacityV];

		for (int i = 0; i < capacityV; ++i)
			vector[i] = other[i];
	}

	
	CellVector::~CellVector()
	{
		//delete [] vector;   sorun cikmisti commente aldim
	}
	
	//yer varsa direk sona eklenir
	//eger yer yoksa backup alinir ardindan yeniedn yer alinir
	//daha sonrasinda restore edilerek eleman sona eklenir
	void CellVector::push_back(const Cell& cell)
	{
		if ((capacityV - sizeV) > 0)
		{
			vector[sizeV] = cell;
			sizeV++;
		}
		else
		{
			Cell *temp;
			temp = new Cell[sizeV];

			for (int i = 0; i < sizeV; ++i)
				temp[i] = vector[i];
			delete[] vector;

			capacityV += 10;
			vector = new Cell[capacityV];
			for (int i = 0; i < sizeV; ++i)
				vector[i] = temp[i];
			vector[sizeV] = cell;
			sizeV++;

			delete[] temp;
		}
	}

	//backup, varolan silinir son
	//indisteki eleman haric tekrar yazilir
	void CellVector::pop_back()
	{/*
		Cell *temp;
		temp = new Cell[sizeV];

		for (int i = 0; i < sizeV; ++i)
			temp[i] = vector[i];
		delete[] vector;

		vector = new Cell[capacityV];
		for (int i = 0; i < sizeV - 1; ++i)
			vector[i] = temp[i];*/
		sizeV--;

		//delete[] temp;
	}


	//backup, varolan silinir yerine istenen 
	//indisteki eleman haric tekrar yazilir
	void CellVector::erase(int index)
	{
		
		Cell *temp;
		temp = new Cell[sizeV];
		for (int i = 0; i < sizeV; ++i)
			temp[i] = vector[i];

		delete[] vector;
		vector = new Cell[capacityV];

		for (int i = 0, j = 0; i < sizeV; ++i)
		if (i != index)
		{
			vector[j] = temp[i];
			++j;
		}
		delete[] temp;
		
		sizeV--;
		

	}

	//r-value
	const Cell& CellVector::operator [](int index) const
	{
		return vector[index];
	}

	//l-value
	Cell& CellVector::operator [](int index)
	{
		return vector[index];
	}

	
	CellVector& CellVector::operator =(const CellVector& other)
	{
		if (this == &other)
		{
			cout << "same object error\n";
			exit(1);
		}
		else
		{
			sizeV = other.sizeV;
			capacityV = other.capacityV;
			delete[] vector;
			vector = new Cell[capacityV];

			for (int i = 0; i < capacityV; ++i)
				vector[i] = other[i];
		}
		return *this;
	}




	ostream& operator << (ostream& out, const CellVector& cellVector)
	{
		for (int i = 0; i < cellVector.size(); ++i)
			out << cellVector[i].getX() << "." << cellVector[i].getY() << " " << endl;
		out << endl;

		return out;
	}


}
