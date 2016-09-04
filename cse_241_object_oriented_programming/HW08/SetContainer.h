/*
EMRAH YILDIRIM 111044056
*/

#ifndef SET_CONTAINER_H
#define SET_CONTAINER_H

#include<iostream>
#include"Container.cpp"
using namespace std;

namespace HW08
{
	//derived from Container<T> class
	template<class T>
	class SetContainer : public Container<T>
	{
	public:
		SetContainer();
		virtual ~SetContainer();

		virtual int size() const { return this->cont.size(); }
		virtual int capacity() const { return this->cont.capacity(); }
		virtual void empty() { this->cont.clear(); } //delete all elements

		virtual bool add(const T& element) throw (bad_alloc); //add element throw exc
		virtual void remove(int index) throw(int); //remove element throw exc
		virtual bool search(const T& element) const; //search element
		virtual int  find(const T& element) const;
		virtual const T& first() throw(int);	//return first throw -1
		virtual const T& next() throw(int);	//returns the next element of the Container since the last throw -1
										//call to the function next. If function
										//first is called before this function, it returns the second element.
	};
}

#endif
