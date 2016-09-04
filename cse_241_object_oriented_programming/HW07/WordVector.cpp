/* Emrah YILDIRIM
	111044056 
		HW07
*/

#include "WordVector.h"

namespace HW07
{


	WordVector::WordVector() : sizeV(0), capacityV(100)
	{
		words = new Word[capacityV];
	}


	//
	WordVector::WordVector(int capacity) : sizeV(0), capacityV(capacity)
	{
		words = new Word[capacityV];
	}

	//
	WordVector::WordVector(const WordVector& other) : sizeV(other.sizeV), capacityV(other.capacityV)
	{
		words = new Word[capacityV];

		for (int i = 0; i < sizeV; ++i)
			words[i] = other.words[i];
	}


	//
	WordVector::~WordVector()
	{
		delete[] words;
		words = NULL;
	}

	//word objelerinin tamamý ayný mý kontrol eder
	bool WordVector::allexist(const Word& word) const
	{
		for (int i = 0; i < sizeV; ++i)
		if (word == words[i])
			return true;

		return false;
	}


	// word objelerinin sadece string kýsýmlarini karsilasitirir
	bool WordVector::exist(const Word& word) const
	{
		for (int i = 0; i < sizeV; ++i)
			if (word.getWord() == words[i].getWord())
				return true;

		return false;
	}


	//girilen word objesinin bulunudugu indeksi return eder yoksa -1
	int WordVector::findLoc(const Word& word) const
	{
		for (int i = 0; i < sizeV; ++i)
		if (word.getWord() == words[i].getWord())
			return i;
		return -1;
	}


	
	bool WordVector::push_back(const Word& word)
	{
		if (allexist(word))
			return false;

		if (exist(word))
		{
			int index = findLoc(word);
			words[index].addLine(word.getLines()[0]);
			return true;
		}
		else if ((capacityV - sizeV) > 0)
		{
			words[sizeV] = word;
			sizeV++;
			return true;
		}
		else
		{
			WordVector temp(*this);

			delete[] words;

			capacityV += 10;
			words = new Word[capacityV];

			for (int i = 0; i < temp.sizeV; ++i)
				words[i] = temp.words[i];

			words[sizeV] = word;
			sizeV++;
			return true;
		}
	}



	bool WordVector::pop_back(void)
	{
		if (sizeV > 0)
			sizeV--;
		else
			return false;

		return true;
	}


	bool WordVector::erase(int index)
	{
		if (sizeV > 0)
		{
			WordVector temp(*this);

			delete[] words;
			words = new Word[capacityV];

			for (int i = 0, j = 0; i < sizeV; ++i)
			{
				if (i != index)
				{
					words[j] = temp.words[i];
					j++;
				}
			}
			sizeV--;

			return true;
		}
		else
			return false;
	}

	WordVector& WordVector::operator=(const WordVector& other)
	{
		if (this == &other)
			return *this;
		else
		{
			sizeV = other.sizeV;
			capacityV = other.capacityV;
			delete[] words;

			words = new Word[capacityV];

			for (int i = 0; i < other.sizeV; ++i)
				words[i] = other.words[i];

			return *this;
		}
	}


	bool WordVector::operator ==(const WordVector& other) const
	{
		if (sizeV == other.sizeV && capacityV == other.capacityV)
		{

			for (int i = 0; i < sizeV; ++i)
			if (words[i] != other.words[i])
				return false;
		}
		else
			return false;

		return true;
	}


	bool WordVector::operator !=(const WordVector& other) const
	{
		if (sizeV != other.sizeV || capacityV != other.capacityV)
			return true;
		else
		{
			for (int i = 0; i < sizeV; ++i)
			if (words[i] != other.words[i])
				return true;
		}

		return false;
	}


	void WordVector::sort(void)
	{
		Word temp;

		for (int i = 0; i < sizeV; ++i)
		for (int j = 0; j < sizeV; ++j)
		if (words[i] < words[j])
		{
			temp = words[i];
			words[i] = words[j];
			words[j] = temp;
		}

	
	}


	WordVector WordVector::operator +(const WordVector& other)
	{
		WordVector temp = *this;

	
		for (int i = 0; i < other.sizeV; ++i)
		if (!temp.exist(other[i]))
			temp.push_back(other[i]);
		else
		{
			for (int j = 0; j < other[i].lineNum(); ++i)
				temp[temp.findLoc(other[i])].addLine(j);
		}
		
		return temp;
	}





	ostream& operator <<(ostream& out, const WordVector& vector)
	{
		for (int i = 0; i < vector.sizeV; ++i)
			out << vector.words[i];

		//out << endl;

		return out;

	}


}