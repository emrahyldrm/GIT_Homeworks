/*
EMRAH YILDIRIM 111044056
*/

#ifndef CONTAINER_H
#define CONTAINER_H

#include<vector>

using namespace std;

namespace HW08
{
	template <class T>
	class Container
	{
	public:

		Container();
		virtual ~Container();

		virtual int size() const = 0;
		virtual int capacity() const = 0;
		virtual void empty() = 0; //delete all elements

		virtual bool add(const T& element) throw (bad_alloc)= 0; //add element throw exc
		virtual void remove(int index) = 0; //remove element
		virtual bool search(const T& element) const = 0; //search element
		virtual int  find(const T& element) const = 0; //return element's index
		virtual const T& first() throw(int)  = 0;	//return first element
		virtual const T& next() throw(int) = 0; //returns the next element of the Container

		void addAll(const Container<T>& other);
		void removeAll(const Container<T>& other);
		const vector<T>& toVector() const;

		const T& operator [](int index) const;
		T& operator [](int index);
		bool operator ==(const Container<T>& other);
		bool operator !=(const Container<T>& other);
		Container<T>& operator =(const Container<T>& other);


	protected:
		vector<T> cont;
		int callNum;
	};
}

#endif