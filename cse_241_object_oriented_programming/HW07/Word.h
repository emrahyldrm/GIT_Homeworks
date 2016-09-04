/* Emrah YILDIRIM
	111044056 
		HW07
*/

#ifndef Word_H
#define Word_H

#include<iostream>
#include<string>
#include"Ivector.h"

using namespace std;

namespace HW07
{
	class Word
	{
	public:
		Word() {}
		Word(const string& other, int index) { tWord = other; lines.push_back(index); }
		Word(const string& other){ tWord = other; }
		
		// big tree does not necessary

		const string& getWord(void) const { return tWord; }
		const Ivector& getLines(void) const { return lines; }

		void setWord(const string& other, int index) { tWord = other; lines.push_back(index); }
		void addLine(int line) { lines.push_back(line); }
		bool onLine(int index) { return lines.exist(index); }
		int lineNum()	const  { return lines.size(); }
		//void deleteLine(int line) {lines.erase}

		Word operator +(const Word& other);
		
		bool operator ==(const Word& other)const;
		bool operator !=(const Word& other)const; 
		bool operator >(const Word& other) const { return tWord > other.tWord; }
		bool operator <(const Word& other) const { return tWord < other.tWord; }
		friend 	ostream& operator << (ostream& out, const Word& word);
	private:
		string tWord;
		Ivector lines;

	};


	ostream& operator << (ostream& out, const Word& word);



}
#endif