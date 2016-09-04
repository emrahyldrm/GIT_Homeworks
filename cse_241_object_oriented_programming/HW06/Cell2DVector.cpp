#include "Cell2DVector.h"

namespace HW06
{

	Cell2DVector::Cell2DVector()
	{
		all = new CellVector[5];
		size2D = 0;
		capacity2D = 5;
	}
	
	
	Cell2DVector::Cell2DVector(const Cell2DVector& other)
	{
		size2D = other.size2D;
		capacity2D = other.capacity2D;
		all = new CellVector[capacity2D];

		for (int i = 0; i < size2D; ++i)
			all[i] = other.all[i];
	}


	Cell2DVector::~Cell2DVector()
	{
		//delete[] all;    sorun cikmisti commente aldim
	}


	//yer varsa direk sona eklenir
	//eger yer yoksa backup alinir ardindan yeniedn yer alinir
	//daha sonrasinda restore edilerek eleman sona eklenir
	void Cell2DVector::push_back(const CellVector& vector)
	{
		if ((capacity2D - size2D) > 0)
		{
			all[size2D] = vector;
			size2D++;
		}
		else
		{
			CellVector *temp;
			temp = new CellVector[capacity2D];

			for (int i = 0; i < size2D; ++i)
				temp[i] = all[i];

			capacity2D += 10;
			delete all;
			all = new CellVector[capacity2D];

			for (int i = 0; i < size2D; ++i)
				all[i] = temp[i];

			all[size2D] = vector;
			size2D++;

		}

	}


	//eleman sayisi azaltilir
	//performans kaybi engellenir
	void Cell2DVector::pop_back(void)
	{
	
		size2D--;

	}


	//backup, varolan silinir yerine istenen 
	//indisteki eleman haric tekrar yazilir
	void Cell2DVector::erase(int index)
	{
		CellVector *temp;

		temp = new CellVector[size2D];

		for (int i = 0; i < size2D; ++i)
			temp[i] = all[i];

		delete[] all;
		all = new CellVector[capacity2D];

		for (int i = 0, j=0; i < size2D; ++i)
		if (i != index)
		{
			all[j] = temp[i];
			j++;
		}

		delete[] temp;

	}


	Cell2DVector& Cell2DVector::operator=(const Cell2DVector& other)
	{
		if (this != &other)
		{
			size2D = other.size2D;
			capacity2D = other.capacity2D;

			delete[] all;
			all = new CellVector[capacity2D];

			for (int i = 0; i < size2D; ++i)
				all[i] = other.all[i];
		}
		else
		{
			cout << "same object error\n";
			exit(1);
		}

		return *this;
	}


	CellVector& Cell2DVector::operator[](int index)
	{
		return all[index];
	}


	const CellVector& Cell2DVector::operator[](int index) const
	{
		return all[index];
	}

}