/*
EMRAH YILDIRIM 111044056
*/

#ifndef CONTAINER_CPP
#define CONTAINER_CPP

#include "Container.h"


namespace HW08
{
	//constructor cagrilma sayisini 0 yapar
	template<class T>
	Container<T>::Container() : callNum(0)
	{
	}

	template<class T>
	Container<T>::~Container()
	{/*bilerek bos birakildi*/}



	//derived class in add i cagrilacak sekilde addAll yazildi
	//boylece sinifin ekleme karakteristigine uyum saglandi
	template<class T>
	void Container<T>::addAll(const Container<T>& other)
	{
		for (int i = 0; i < other.size(); ++i)
			add(other.cont[i]);
	}



	//parametre olarak Container<T> tipinde arguman alinir
	//parametrede olan elemanlar uzerinde calisilan objede..
	//..var mi diye kontrol edilir
	//varsa find() fonksiyonu ile indeksi bulunur ve o konumdaki
	//erase edilir
	template<class T>
	void Container<T>::removeAll(const Container<T>& other)
	{
		for (int i = 0; i < other.size(); ++i)
			if (search(other.cont[i]))
				cont.erase(cont.begin() + find(other.cont[i]));
	}


	//kullanilan vector const olarak return edilir
	template<class T>
	const vector<T>& Container<T>::toVector() const
	{
		return this->cont;
	}



	template<class T>
	const T& Container<T>::operator[](int index) const
	{
		return this->cont[index];
	}

	template<class T>
	T& Container<T>::operator[](int index)
	{
		return this->cont[index];
	}


	template<class T>
	bool Container<T>::operator==(const Container<T>& other)
	{
		return this->cont == other.cont;
	}


	template<class T>
	bool Container<T>::operator!=(const Container<T>& other)
	{
		return this->cont != other.cont;
	}


	//normalde shallow copy calisir ancak
	//callNum i kopyalamayi istemedigimiz icin overload ettik
	template<class T>
	Container<T>& Container<T>::operator=(const Container<T>& other)
	{
		this->cont = other.cont;
		return *this;
	}
}

#endif
