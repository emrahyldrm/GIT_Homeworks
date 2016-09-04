/*
EMRAH YILDIRIM 111044056
*/

#ifndef SORTED_SET_H
#define SORTED_SET_H

#include"SortedContainer.cpp"

using namespace std;

namespace HW08
{
	//derived from SortedContainer<T>
	template<class T>
	class SortedSetContainer : public SortedContainer<T>
	{
	public:
		SortedSetContainer();
		virtual ~SortedSetContainer();

		virtual bool add(const T& element) throw (bad_alloc); //add element throw bad_alloc
		
	};
}

#endif
