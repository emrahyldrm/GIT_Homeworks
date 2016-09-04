/**********************************************************/
// Emrah YILDIRIM 111044056
// HW05_111044056_main.cpp


#include<iostream>
#include<cstdlib>
#include<cstring>
#include"HW05_111044056.h"

using namespace std;



int main()
{
	GameOfLife game1, game2, game3, game4, game5;
	Cell cell;
	
	
	game1.readFile("map1.txt");
	game2.readFile("map2.txt");
	game3.readFile("map3.txt");
	game4.readFile("map4.txt");
	game5.readFile("map5.txt");
	

	cout << "game1++ 3 times\n";
	game1++;
	cout << game1<<endl;
	game1++;
	cout << game1<<endl;
	game1++;
	cout << game1<<endl;
	
	cout<<"------------------------------\n";
	cout << "game2++ 3 times\n";
	game2++;
	cout << game2<<endl;
	game2++;
	cout << game2<<endl;
	game2++;
	cout<<"------------------------------\n";
	
	cout <<"game1\n"<<game1;
	cout <<"game2\n"<<game2;
	cout <<"game1 += game2\n";
	game1 += game2;
	cout << game1;
	cout<<"------------------------------\n";
	cout <<"game-- 3 times\n\n";
	game1--;
	cout << game1<<endl;
	game1--;
	cout << game1<<endl;
	game1--;
	cout << game1<<endl;
	cout<<"------------------------------\n";
	
	cout<<"game4 = game4  - Cell(1,1)\n"; 
	cout << game4<<endl;
	game4 = game4 - Cell(1,1);
	cout << game4<<endl;
	cout<<"game4 = game4  + Cell(1,1)\n";
	game4 = game4 + Cell(1,1);
	cout << game4<<endl;

	cout<<"------------------------------\n";

		
	cout <<"game5[1][5] and game5[0][4]\n";
	cout << game5<<endl;
	cout << game5[1][5];
	cout << game5[0][4]<<endl;

	cout<<"------------------------------\n";
	
	cout <<"game5(1,5) and game5(0,4)\n";
	cout << game5<<endl;
	cout << game5(1,5);
	cout << game5(0,4)<<endl;
	
	
	
	game1.write2File("map1Last.txt");
	game2.write2File("map2Last.txt");
	game3.write2File("map3Last.txt");
	game4.write2File("map4Last.txt");
	game5.write2File("map5Last.txt");
	
	cout<<"------------------------------\n"
		<<"------------------------------\n\n";
	
	getchar(); //terminal beklemesi icin
	return 0;
}
