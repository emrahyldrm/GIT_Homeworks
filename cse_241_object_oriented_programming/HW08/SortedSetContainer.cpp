/*
EMRAH YILDIRIM 111044056
*/

#ifndef SORTED_SET_CPP
#define SORTED_SET_CPP
#include "SortedSetContainer.h"

namespace HW08
{
	template<class T>
	SortedSetContainer<T>::SortedSetContainer() : SortedContainer<T>()
	{
	}

	template<class T>
	SortedSetContainer<T>::~SortedSetContainer()
	{
	}


	//eleman var mi diye kontrol edilir varsa false return edilir
	//yoksa ekleme yapilir ardindan da sort yapilir
	template<class T>
	bool SortedSetContainer<T>::add(const T& element) throw (bad_alloc)
	{
		if (this->search(element))
			return false;

		this->cont.push_back(element);
		this->sort();
		return true;
	}

}

#endif
