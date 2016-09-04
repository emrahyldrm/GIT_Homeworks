/*
EMRAH YILDIRIM 111044056
*/

#ifndef SORTED_CONTAINER_CPP
#define SORTED_CONTAINER_CPP

#include "SortedContainer.h"

namespace HW08
{
	template<class T>
	SortedContainer<T>::SortedContainer() : Container<T>() //call COntainer<T> constructor
	{ /*bilerek bos birakildi*/ }

	template<class T>
	SortedContainer<T>::~SortedContainer()
	{ /*bilerek bos birakildi*/ }


	//hic bir kontrol olmadan ekleme yapilir7
	//ardindan elemanlar siralanir
	template<class T>
	bool SortedContainer<T>::add(const T& element) throw (bad_alloc)
	{
		this->cont.push_back(element);
		sort();
		return true;
	}

	//bubble sort
	template<class T>
	void SortedContainer<T>::sort()
	{
		T temp;
		int size = this->cont.size();

		for (int i = 0; i < size; ++i)
		for (int j = 0; j < size; ++j)
		if (this->cont[i] < this->cont[j])
		{
			temp = this->cont[i];
			this->cont[i] = this->cont[j];
			this->cont[j] = temp;
		}
	}


	//eger silinmesi istenen index alanin disi ise
	//index throw edilir
	template<class T>
	void SortedContainer<T>::remove(int index)
	{
		if (index >= this->cont.size())
			throw index;
		else
			this->cont.erase(this->cont.begin() + index);
	}

	//aranan elemen varsa true yoksa false return edilir
	template<class T>
	bool SortedContainer<T>::search(const T& element) const
	{
		for (int i = 0; i < this->cont.size(); ++i)
		if (this->cont[i] == element)
			return true;

		return false;
	}


	//girilen elementin imdeksinireturn eder
	//girilen elementin var oldugu bilinmelidir
	template<class T>
	int SortedContainer<T>::find(const T& element) const
	{
		for (int i = 0; i < this->cont.size(); ++i)
		if (this->cont[i] == element)
			return i;
	}


	//return first element
	//eger elemen yoksa -1 throw eder
	template<class T>
	const T& SortedContainer<T>::first() throw(int)
	{
		if (this->cont.size() == 0)
			throw - 1;

		return this->cont[0];
	}


	//return first element
	//eger elemen yoksa -1 throw eder
	template<class T>
	const T& SortedContainer<T>::next() throw(int)
	{
		if (this->callNum > this->cont.size() || this->cont.size() == 0)
			throw - 1;
		if (this->callNum == this->cont.size())
			this->callNum = 0;

		this->callNum++;
		return this->cont[this->callNum - 1];
	}
}

#endif
