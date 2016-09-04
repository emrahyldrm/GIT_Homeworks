/* Emrah YILDIRIM
	111044056 
		HW07
*/

#include<iostream>
#include"DocumentIndex.h"

using namespace std;
using namespace HW07;


int main()
{
	string name = "text.txt";
	DocumentIndex doc(name);
	DocumentIndex doc2("text2.txt");
	DocumentIndex doc3("text3.txt");
	DocumentIndex doc4;
	
	ofstream out, out2, out3, out4;
	ifstream inp;

	out.open("indexed.txt");
	out2.open("indexed2.txt");
	out3.open("indexed3.txt");
	out4.open("indexed4.txt");


	cout << "THE WORDS ARE ON 45. LINE IN text.txt\n\n" 
		 << doc[45];
		 
	cout << "------------------------------------\n\n";
	cout <<"THE LINE INCLUDE >functions< IN text.txt\n\n"
		 << doc["functions"];
	
	cout << "------------------------------------\n\n";
	
	cout << "THE WORDS ARE ON 45. LINE IN text2.txt\n\n" 
		 << doc2[45];
		 
	cout << "------------------------------------\n\n";
	cout <<"THE LINE INCLUDE >int< IN text2.txt\n\n"
		 << doc2["int"];
	
	cout << "------------------------------------\n\n";
	
	
	cout << "DOC4 = DOC  +  DOC2 AND THE WORDS ARE ON 45  (text.txt + text2.txt)\n\n";
	doc4 = doc + doc2;
	cout << doc4[45];
	cout << "------------------------------------\n\n";
	
	
	cout << "DOC2 += DOC AND THE WORDS ARE ON 45  (text.txt + text2.txt)\n\n";
	doc2 += doc;
	cout << doc2[45];
	cout << "------------------------------------\n\n";
	
	
	
	cout << "INDEXED WORDS WERE WRITTEN TO THE OUTPUT FILES\n\n";
	out << doc;
	out2 << doc2;
	out3 << doc3;
	out4 << doc4;
	cout << "------------------------------------\n\n";
	
	
	
	out.close();
	out2.close();
	out3.close();
	out4.close();

	return 0;
}