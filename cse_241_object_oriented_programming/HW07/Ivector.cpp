/* Emrah YILDIRIM
	111044056 
		HW07
*/

#include "Ivector.h"

namespace HW07
{
	//
	Ivector::Ivector() : sizeV(0), capacityV(10)
	{
		nums = new int[capacityV];
	}


	//
	Ivector::Ivector(int wcapacity) : sizeV(0), capacityV(wcapacity)
	{
		nums = new int[capacityV];
	}


	//
	Ivector::Ivector(const Ivector& other) : sizeV(other.sizeV), capacityV(other.capacityV)
	{
		nums = new int[capacityV];

		for (int i = 0; i < other.sizeV; ++i)
			nums[i] = other.nums[i];

	}


	//
	Ivector::~Ivector()
	{
		delete[] nums;
		nums = NULL;
	}


	//sayinin varligini kontrol eder
	bool Ivector::exist(int num)	const
	{
		for (int i = 0; i < sizeV; ++i)
		if (num == nums[i])
			return true;

		return false; 
	}


	//
	bool Ivector::push_back(int num)
	{
		if (exist(num))
			return false;

		if ((capacityV - sizeV) > 0)
		{
			nums[sizeV] = num;
			sizeV++;
			return true;
		}
		else
		{
			Ivector temp(*this);

			delete[] nums;

			capacityV += 10;
			nums = new int[capacityV];

			for (int i = 0; i < temp.sizeV; ++i)
				nums[i] = temp.nums[i];

			nums[sizeV] = num;
			sizeV++;
			return true;
		}

	}


	//
	bool Ivector::pop_back(void)
	{
		if (sizeV > 0)
			sizeV--;
		else
			return false;

		return true;
	}


	//
	bool Ivector::erase(int index)
	{
		if (sizeV > 0)
		{
			Ivector temp(*this);			

			delete[] nums;
			nums = new int[capacityV];

			for (int i = 0, j = 0; i < sizeV; ++i)
			{
				if (i != index)
				{
					nums[j] = temp.nums[i];
					j++;
				}
			}
			sizeV--;

			return true;
		}
		else
			return false;
	}



	void Ivector::sort(void)
	{
		int temp;

		for (int i = 0; i < sizeV; ++i)
		for (int j = 0; j < sizeV; ++j)
		if (nums[i] < nums[j])
		{
			temp = nums[i];
			nums[i] = nums[j];
			nums[j] = temp;
		}

	}


	const Ivector Ivector::operator+(const Ivector& other)
	{
		Ivector temp = *this;

		for (int i = 0; i < other.size(); ++i)
			if (!temp.exist(other[i]))
				temp.push_back(other[i]);
		
		temp.sort();
		return temp;
	}


	//
	const Ivector& Ivector::operator=(const Ivector& other)
	{
		if (this == &other)
			return *this;
		else
		{
			sizeV = other.sizeV;
			capacityV = other.capacityV;
			delete[] nums;

			nums = new int[capacityV];

			for (int i = 0; i < other.sizeV; ++i)
				nums[i] = other.nums[i];

			return *this;
		}
	}


	//
	bool Ivector::operator ==(const Ivector& other) const
	{
		if (sizeV == other.sizeV && capacityV == other.capacityV)
		{

			for (int i = 0; i < sizeV; ++i)
			if (nums[i] != other.nums[i])
				return false;
		}
		else
			return false;

		return true;
	}

	bool Ivector::operator !=(const Ivector& other) const
	{
		if (sizeV != other.sizeV || capacityV != other.capacityV)
			return true;
		else
		{
			for (int i = 0; i < sizeV; ++i)
				if (nums[i] != other.nums[i])
					return true;
		}

		return false;
	}



	//
	ostream& operator << (ostream& out, const Ivector& vector)
	{
		for (int i = 0; i < vector.sizeV; ++i)
			out << vector.nums[i] << " ";
		
		out << endl;

		return out;
	
	}
































}