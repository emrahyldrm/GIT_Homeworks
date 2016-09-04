/*
EMRAH YILDIRIM 111044056
*/

#ifndef SET_CONTAINER_CPP
#define SET_CONTAINER_CPP

#include "SetContainer.h"


namespace HW08
{

	template<class T>
	SetContainer<T>::SetContainer() : Container<T>()//call Container<T> constructor
	{ /*bilerek bos birakildi*/ }

	template<class T>
	SetContainer<T>::~SetContainer()
	{ /*bilerek bos birakildi*/	}



	//eklenecek eleman var mi diye kontrol edilir
	// varsa ekleme yapilmaz false return edilir
	template<class T>
	bool SetContainer<T>::add(const T& element) throw (bad_alloc)
	{
		if (search(element))
			return false;

		this->cont.push_back(element);
		return true;
	}


	//eger silinmesi istenen index alanin disi ise
	//index throw edilir
	template<class T>
	void SetContainer<T>::remove(int index) throw(int)
	{
		if (index >= this->cont.size())
			throw index;
		else
			this->cont.erase(this->cont.begin() + index);
	}


	//aranan elemen varsa true yoksa false return edilir
	template<class T>
	bool SetContainer<T>::search(const T& element) const
	{
		for (int i = 0; i < this->cont.size(); ++i)
			if (this->cont[i] == element)
				return true;

		return false;
	}


	//girilen elementin imdeksinireturn eder
	//girilen elementin var oldugu bilinmelidir
	template<class T>
	int SetContainer<T>::find(const T& element) const
	{
		for (int i = 0; i < this->cont.size(); ++i)
		if (this->cont[i] == element)
			return i;
	}


	//return first element
	//eger elemen yoksa -1 throw eder
	template<class T>
	const T& SetContainer<T>::first() throw(int)
	{
		if (this->cont.size() == 0)
			throw - 1;

		return this->cont[0];
	}


	//return first element
	//eger elemen yoksa -1 throw eder
	template<class T>
	const T& SetContainer<T>::next() throw(int)
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
