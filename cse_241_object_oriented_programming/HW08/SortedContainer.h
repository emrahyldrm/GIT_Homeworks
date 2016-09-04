/*
EMRAH YILDIRIM 111044056
*/

#ifndef SORTED_CONTAINER_H
#define SORTED_CONTAINER_H

#include<iostream>
#include"Container.cpp"

using namespace std;

namespace HW08
{
	template<class T>
	class SortedContainer : public Container<T>
	{
	public:
		SortedContainer();
		virtual ~SortedContainer();


		virtual int size() const { return this->cont.size(); }
		virtual int capacity() const { return this->cont.capacity(); }
		virtual void empty() { this->cont.clear(); } //delete all elements

		virtual bool add(const T& element) throw (bad_alloc); //add element throw exc
		virtual void remove(int index); //remove element throw exc
		virtual bool search(const T& element) const; //search element, throw exc
		virtual int  find(const T& element) const;
		virtual const T& first() throw(int);	//return first element
		virtual const T& next() throw(int);	//returns the next element of the Container since the last
										//call to the function next. If function
										//first is called before this function, it returns the second element.

		void sort();
	};

}
#endif
