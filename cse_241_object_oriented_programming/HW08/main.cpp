/*
EMRAH YILDIRIM 111044056
*/

#include<iostream>
#include<vector>
#include"Cell.h"
#include"Container.cpp"
#include"SetContainer.cpp"
#include"SortedContainer.cpp"
#include"SortedSetContainer.cpp"

using namespace std;
using namespace HW08;
using namespace HW06;


template<class T>
int sortedElementCounter(const vector<Container<T>* >& containers)
{
	SortedContainer<T> *temp;
	int total=0;

	for (int i = 0; i < containers.size(); ++i)
		if (NULL != (temp = dynamic_cast<SortedContainer<T> *>(containers[i])))
			total += containers[i]->size();

	return total;
}


int main()
{
	vector<Container<int>* > containers;
	SetContainer<int> set1, set2;
	SortedContainer<int> sorted1, sorted2;
	SortedSetContainer<int> sortedSet1, sortedSet2;
	
	
	vector<Container<Cell>* > containersC;
	SetContainer<Cell> setCell1, setCell2;
	SortedContainer<Cell> sortedCell1, sortedCell2;
	SortedSetContainer<Cell> sortedSetCell1, sortedSetCell2;


	containers.push_back(&set1);
	containers.push_back(&set2);
	containers.push_back(&sorted1);
	containers.push_back(&sorted2);
	containers.push_back(&sortedSet1);
	containers.push_back(&sortedSet2);

	containersC.push_back(&setCell1);
	containersC.push_back(&setCell2);
	containersC.push_back(&sortedCell1);
	containersC.push_back(&sortedCell2);
	containersC.push_back(&sortedSetCell1);
	containersC.push_back(&sortedSetCell2);

	
	
	
	for (int i = 0; i < containers.size(); ++i)
	{
		if (i % 2 == 0)
		{
			containers[i]->add(12);
			containers[i]->add(1);
			containers[i]->add(1);
			containers[i]->add(12);
			containers[i]->add(24);
			containers[i]->add(23);
			containers[i]->add(20);

		}
		else
		{
			containers[i]->add(21);
			containers[i]->add(11);
			containers[i]->add(11);
			containers[i]->add(247);
			containers[i]->add(235);
			containers[i]->add(210);
			containers[i]->add(112);
		}
	}
	

	for (int i = 0; i < containersC.size(); ++i)
	{
		if (i % 2 == 0)
		{
			containersC[i]->add(Cell(12,10));
			containersC[i]->add(Cell(1, 5));
			containersC[i]->add(Cell(1, 5));
			containersC[i]->add(Cell(12, 7));
			containersC[i]->add(Cell(24, 87));
			containersC[i]->add(Cell(23, 45));
			containersC[i]->add(Cell(20, 34));

		}
		else
		{
			containersC[i]->add(Cell(21, 45));
			containersC[i]->add(Cell(11, 11));
			containersC[i]->add(Cell(11, 11));
			containersC[i]->add(Cell(247, 78));
			containersC[i]->add(Cell(235, 45));
			containersC[i]->add(Cell(210, 147));
			containersC[i]->add(Cell(112, 165));
		}
	}
	cout << "Number of sorted Int elements is : "
		 << sortedElementCounter(containers) << endl << endl;


	cout << "Int Containers elements\n";
	for (int i = 0; i < containers.size(); ++i)
	{
		for (int j = 0; j < containers[i]->size(); ++j)
			cout << (*containers[i])[j] << "  ";
		cout << endl <<endl;
	}

	cout << "-------------------------------\n" ;

	cout << "Cell Containers elements\n";
	for (int i = 0; i < containersC.size(); ++i)
	{
		for (int j = 0; j < containersC[i]->size(); ++j)
			cout << (*containersC[i])[j];
		cout << endl << endl;
	}
	cout <<  endl;


	cout << "-------------------------------\n";

	cout <<"int set containers size and 3. element before remove\n"
		 << containers[0]->size()<< "  " <<(*containers[0])[3]<<endl;

	containers[0]->remove(0);
	
	cout << "int set container size and 3. element after remove\n"
		 << containers[0]->size() << "  " << (*containers[0])[3] << endl;

	cout << "-------------------------------\n";

	cout << "\nsorted set cells1 element print with next()\n";
	for (int i = 0; i < containersC[4]->size(); ++i)
		cout << containersC[4]->next();

	cout << containersC[4]->next();
	

	getchar();
	return 0;
}
