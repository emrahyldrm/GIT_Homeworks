/* Emrah YILDIRIM
	111044056 
		HW07
*/

#include "DocumentIndex.h"

namespace HW07
{
	DocumentIndex::DocumentIndex(string& fileName)
	{
		ifstream input;
		string  line, word;
		char *token, lineC[1000];
		int lineNum = 0;
		input.open(fileName.c_str());


		if (input.fail())
		{
			cerr << "File does not exist\n";
			exit(1);
		}


		while (!input.eof())
		{
			getline(input, line, '\n');
			lineNum++;
			if (line.size() > 2)
			{
				strcpy(lineC, line.c_str());
				token = strtok(lineC, " ");
				while (NULL != token)
				{
					word = token;
					cleanPunct(word);
					toLowerAll(word);
					
					if(word.size() > 2)
						allWords.push_back(Word(word, lineNum));
					
					token = strtok(NULL, " ");					
				
				}
			}
			
		}
		allWords.sort();
		input.close();
	}


	DocumentIndex::DocumentIndex(const char* fileName)
	{
	
		ifstream input;
		string  line, word;
		char *token, lineC[1000];
		int lineNum = 0;
		input.open(fileName);


		if (input.fail())
		{
			cerr << "File does not exist\n";
			exit(1);
		}


		while (!input.eof())
		{
			getline(input, line, '\n');
			lineNum++;
			if (line.size() > 2)
			{
				strcpy(lineC, line.c_str());
				token = strtok(lineC, " ");
				while (NULL != token)
				{
					word = token;
					cleanPunct(word);
					toLowerAll(word);
					
					if(word.size() > 2)
						allWords.push_back(Word(word, lineNum));
					
					token = strtok(NULL, " ");					
				
				}
			}
			
		}
		allWords.sort();
		input.close();
	}


	// tum harfleri kucuk harfe cevirir
	void DocumentIndex::toLowerAll(string& word)
	{
		for (int i = 0; i < word.size(); ++i)
			if (isupper(word[i]))
				word[i] = tolower(word[i]);
	}


	//kelimedeki tum punct karakterleri siler
	void DocumentIndex::cleanPunct(string& word)
	{
		if (ispunct(word[word.size()-1]))
			word.erase(word.end()-1);

		for(int i=0; i < word.size(); ++i)
			if (ispunct(word[i]))
				word.erase(word.begin() + i);
	}



	const Ivector& DocumentIndex::operator[] (const string& word)
	{
		int index = allWords.findLoc(word);
		

		return allWords[index].getLines();
	}

	
	const WordVector DocumentIndex::operator[] (int index)
	{
		int size = allWords.size();
		WordVector temp;
		for (int i = 0; i < size; ++i)
			if (allWords[i].onLine(index))
				temp.push_back(allWords[i]);

		
		if(temp.size() != 0)
			return temp;
		else
			temp.push_back(Word("NOT-EXIST", 0));
		return temp;
	}


	DocumentIndex DocumentIndex::operator +(const DocumentIndex& other)
	{
		DocumentIndex temp = other;

		for (int i = 0; i < allWords.size(); ++i)
		{
			if (temp.allWords.exist(allWords[i]))
			{
				int index = temp.allWords.findLoc(allWords[i]);
				temp.allWords[index] = temp.allWords[index] + allWords[i];
			}
			else
				temp.allWords.push_back(allWords[i]);

		}

		temp.allWords.sort();
		return temp;
	}

	void DocumentIndex::operator +=(const DocumentIndex& other)
	{
		

		for (int i = 0; i < other.allWords.size(); ++i)
		{
			if (allWords.exist(other.allWords[i]))
			{
				int index = allWords.findLoc(other.allWords[i]);
				allWords[index] = allWords[index] + other.allWords[i];
			}
			else
				allWords.push_back(other.allWords[i]);

		}

		allWords.sort();
		
	}


	ostream& operator <<(ostream& out, const DocumentIndex& document)
	{
		out << document.allWords;

		return out;
	
	}
	
	// konsoldan okuma yapar ve satirlara gore ayirir
	istream& operator >>(istream& inp, DocumentIndex& document)
	{
		string  line, word;
		char *token, lineC[1000];
		int lineNum = 0;
		
		cout << "You can write until enter double newline\n\n";
		
		while(true)
		{
			getline(inp, line, '\n');
			if(line.empty())
				break;
			lineNum++;
			if (line.size() > 2)
			{
				strcpy(lineC, line.c_str());
				token = strtok(lineC, " ");
				while (NULL != token)
				{
					word = token;									
					document.cleanPunct(word);
					document.toLowerAll(word);
					if(word.size() > 2)
						document.allWords.push_back(Word(word, lineNum));
					
					token = strtok(NULL, " ");					
				}
			}
		}
	
		document.allWords.sort();
		return inp;
	}
	
}