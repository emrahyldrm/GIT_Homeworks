/*##########################################################################*/
/*HW03_111044056_main.cpp													*/
/*--------------------------------------------------------------------------*/
/*Emrah YILDIRIM 111044056													*/
/*																			*/
/*##########################################################################*/


#include<iostream>
#include"HW03_111044056.h"

using namespace std;



/*##########################################################################*/
/*									MAIN									*/
/*##########################################################################*/

int main()
{
    Vect3D vect1(1.5, 1.7, 5.4), vect2(2.0, 3.5, 4.0), v;
	

	cout <<"TEST WITH CALL BY VALUE\n\n";
	cout << "Values of vectors before call by value process\n"
		 << "\n1.vector:";
		 vect1.printVector();
		 
	cout << "\n2.vector:";
		 vect2.printVector();
	cout <<endl;
		 
	cout << "\n----------------------------------------\n";	
	
	testCallByValue(vect1, vect2);
	
	cout << "\n----------------------------------------\n";
	cout << "\n----------------------------------------\n";
	
	cout << "Values of vectors after call by vales process\n"
		 << "\n1.vector:";
		 vect1.printVector();
		 
	cout << "\n2.vector:";
		 vect2.printVector();
	cout <<endl;
	cout << "\n----------------------------------------\n";
	cout << "\n----------------------------------------\n";
	cout << "\n----------------------------------------\n";
	cout << "\n----------------------------------------\n";
	
	cout <<"TEST WITH CALL BY REFERENCE\n\n";
	
	cout << "Values of vectors before call by reference process\n"
		 << "\n1.vector:";
		 vect1.printVector();
		 
	cout << "\n2.vector:";
		 vect2.printVector();
	cout <<endl;
	
	cout << "\n----------------------------------------\n";
	
	testCallByReference(vect1, vect2);
	
	cout << "\n----------------------------------------\n";
	cout << "\n----------------------------------------\n";
	
	cout << "Values of vectors after call by reference process\n"
		 << "\n1.vector:";
		 vect1.printVector();
		 
	cout << "\n2.vector:";
		 vect2.printVector();
	cout <<endl;
	
	cout << "----------------------------------------\n";
	
	return 0;
}
