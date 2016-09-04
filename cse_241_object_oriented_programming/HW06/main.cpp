#include<iostream>
#include"Cell.h"
#include"CellVector.h"
#include"Cell2DVector.h"
#include"GameOfLife.h"

using namespace std;
using namespace HW06;
int main()
{

	GameOfLife game1, game2, game3, game4, game5;
	GameOfLife temp;
	
	game1.readFile("map1.txt");
	game2.readFile("map2.txt");
	game3.readFile("map3.txt");
	game4.readFile("map4.txt");
	game5.readFile("map5.txt");

	
	cout << "game1++ 3 times\n";
	game1++;
	cout << game1 << endl;
	game1++;
	cout << game1 << endl;
	game1++;
	cout << game1 << endl;
	
	cout << "------------------------------\n";
	cout << "game2++ 3 times\n";
	game2++;
	cout << game2 << endl;
	game2++;
	cout << game2 << endl;
	game2++;
	cout << "------------------------------\n";

	cout << "game1\n" << game1;
	cout << "game2\n" << game2;
	cout << "game1 += game2\n";
	game1 += game2;
	cout << game1;
	cout << "------------------------------\n";
	cout << "game-- 3 times\n\n";
	cout << game1 << endl;
	game1--;
	cout << game1 << endl;
	game1--;
	cout << game1 << endl;
	game1--;
	cout << game1 << endl;
	cout << "------------------------------\n";

	cout << "temp = game4  - Cell(1,1)\n";
	cout << game4 << endl;
	temp = game4 - Cell(1, 1);
	cout << temp << endl;
	cout << "temp = game4  + Cell(1,1)\n";
	temp = game4 + Cell(1, 1);
	cout << temp << endl;

	cout << "------------------------------\n";


	cout << "game5[1][5] and game5[0][4]\n";
	cout << game5 << endl;
	cout << game5[1][5];
	cout << game5[0][4] << endl;

	cout << "------------------------------\n";

	cout << "game5(1,5) and game5(0,4)\n";
	cout << game5 << endl;
	cout << game5(1, 5);
	cout << game5(0, 4) << endl;


	
	game1.write2File("map1Last.txt");
	game2.write2File("map2Last.txt");
	game3.write2File("map3Last.txt");
	game4.write2File("map4Last.txt");
	game5.write2File("map5Last.txt");

	cout << "------------------------------\n"
	<< "------------------------------\n\n";
	
	getchar(); //terminal beklemesi icin
	return 0;
}
