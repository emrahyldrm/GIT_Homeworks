/* Emrah YILDIRIM
	111044056 
		HW07
*/

#ifndef WORD_VECTOR_H
#define WORD_VECTOR_H

#include<iostream>
#include"Word.h"

namespace HW07
{
	class WordVector
	{

	public:
		WordVector();
		WordVector(int capacity);
		WordVector(const WordVector& other);
		~WordVector();

		int size() const	{ return sizeV; }
		int capacity() const	{ return capacityV; }

		bool exist(const Word& word) const;
		bool allexist(const Word& word) const;
		int findLoc(const Word& word) const;
		bool push_back(const Word& word);
		bool pop_back(void);
		bool erase(int index);

		WordVector operator +(const WordVector& other);
		WordVector& operator=(const WordVector& other);
		bool operator ==(const WordVector& other) const;
		bool operator !=(const WordVector& other) const;
		Word operator [](int index) const { return words[index]; }
		Word& operator [](int index)	{ return words[index]; }

		void sort(void);
		friend ostream& operator <<(ostream& out, const WordVector& vector);


	private:
		Word *words;
		int sizeV, capacityV;
	};

	ostream& operator <<(ostream& out, const WordVector& vector);
}


#endif