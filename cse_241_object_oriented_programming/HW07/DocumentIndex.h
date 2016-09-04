#ifndef DOCUMENT_INDEX_H
#define DOCUMENT_INDEX_H

#include<iostream>
/* Emrah YILDIRIM
	111044056 
		HW07
*/

#include<string>
#include<fstream>
#include"WordVector.h"
#include<cstdlib>
#include<cstring>
using namespace std;

namespace HW07
{
	class DocumentIndex
	{
	public:
		DocumentIndex() {}
		DocumentIndex(string& fileName);
		DocumentIndex(const char* fileName);

		/***BIG TREE DOES NOT NECESSARY*****/
	
		void readFile(ifstream& file);
	
		const Ivector& operator[] (const string& word);
		const WordVector operator[] (int index);
	
		DocumentIndex operator +(const DocumentIndex& other);
		void operator +=(const DocumentIndex& other);
		friend ostream& operator <<(ostream& out, const DocumentIndex& document);
		friend istream& operator >>(istream& inp, DocumentIndex& document);

	private:
		void toLowerAll(string& word);
		void cleanPunct(string& word);
		WordVector allWords;
	};


	ostream& operator <<(ostream& out, const DocumentIndex& document);
	istream& operator >>(istream& inp, DocumentIndex& document);
}

#endif