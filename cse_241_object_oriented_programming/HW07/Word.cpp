/* Emrah YILDIRIM
	111044056 
		HW07
*/

#include "Word.h"

namespace HW07
{
	ostream& operator << (ostream& out, const Word& word)
	{
		out << word.tWord<<" : " << word.lines<<endl;

		return out;
	}

	Word Word::operator+(const Word& other)
	{
		Word temp = *this;
		if (temp.tWord == other.tWord)
			temp.lines = temp.lines + other.lines;
		
		return temp;
	}

	bool Word::operator ==(const Word& other)const
	{
		if (tWord == other.tWord && lines == other.lines)
			return true;
		else
			return false;
	}

	bool Word::operator !=(const Word& other)const
	{
		if (tWord != other.tWord || lines != other.lines)
			return true;
		else
			return false;
	}
}