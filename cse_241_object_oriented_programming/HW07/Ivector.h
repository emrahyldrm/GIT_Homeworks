/* Emrah YILDIRIM
	111044056 
		HW07
*/

#ifndef Ivector_H
#define Ivector_H

#include<iostream>
using namespace std;

namespace HW07
{

	class Ivector
	{
	public:
		Ivector();
		Ivector(int wcapacity);
		Ivector(const Ivector& other);
		~Ivector();

		int size() const	{ return sizeV; }
		int capacity() const	{ return capacityV; }

		bool exist(int num)	const;

		bool push_back(int num);
		bool pop_back(void);
		bool erase(int index);
		//belirli sayý silme fonksiyonu ve index return eden fonksiyon

		void sort(void);
		const Ivector& operator=(const Ivector& other);
		const Ivector operator+(const Ivector& other);
		bool operator ==(const Ivector& other) const;
		bool operator !=(const Ivector& other) const;
		int operator [](int index) const { return nums[index]; }
		int& operator [](int index)	{ return nums[index]; }
		friend ostream& operator << (ostream& out, const Ivector& vector);


	private:
		int *nums;
		int sizeV, capacityV;
	};

	ostream& operator << (ostream& out, const Ivector& vector);

}

#endif