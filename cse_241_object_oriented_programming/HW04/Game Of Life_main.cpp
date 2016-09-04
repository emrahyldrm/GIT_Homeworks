/**********************************************************/
// Emrah YILDIRIM 111044056
// HW04_111044056_main.cpp


#include<iostream>
#include<cstdlib>
#include<cstring>
#include"file.h"

using namespace std;



int main()
{
	GameOfLife game1, game2, game3, game4, game5;
	
	
	
	game1.readFile("map1.txt");
	game2.readFile("map2.txt");
	game3.readFile("map3.txt");
	game4.readFile("map4.txt");
	game5.readFile("map5.txt");
	
	cout<< "Number of alive cells : " 
		<< GameOfLife::getNumOfAlive()<<endl;
	cout << "3 STEP FOR MAP1\n";
	game1.play();
	game1.play();
	game1.play();
	
	cout<< "Number of alive cells : " 
		<< GameOfLife::getNumOfAlive()<<endl;
	
	cout << "3 STEP FOR MAP2\n";
	game2.play();
	game2.play();
	game2.play();
	
	cout<< "Number of alive cells : " 
		<< GameOfLife::getNumOfAlive()<<endl;
	
	cout << "3 STEP FOR MAP3\n";
	game3.play();
	game3.play();
	game3.play();
	
	cout<< "Number of alive cells : " 
		<< GameOfLife::getNumOfAlive()<<endl;
	
	cout << "3 STEP FOR MAP4\n";
	game4.play();
	game4.play();
	game4.play();
	
	cout<< "Number of alive cells : " 
		<< GameOfLife::getNumOfAlive()<<endl;
	
	cout << "3 STEP FOR MAP5\n";
	game5.play();
	game5.play();
	game5.play();
	
	
	cout<< "Number of alive cells : " 
		<< GameOfLife::getNumOfAlive()<<endl;
	
	game1.write2File("map1Last.txt");
	game2.write2File("map2Last.txt");
	game3.write2File("map3Last.txt");
	game4.write2File("map4Last.txt");
	game5.write2File("map5Last.txt");
	
	cout<<"------------------------------\n"
		<<"------------------------------\n\n";

	cout<<"Merge Game2 to Game1 and go ahead\n\n";
		
	game1.mergeGames(game2);
	game1.play();
	game1.play();
	game1.play();
		
		
	cout<< "Number of alive cells : " 
		<< GameOfLife::getNumOfAlive()<<endl;
		
	game1.write2File("merge1-2.txt");
		
	cout<<"Merge Game4 to Game3 and go ahead\n\n";
		
	game3.mergeGames(game4);
	game3.play();
	game3.play();
	game3.play();
		
	cout<< "Number of alive cells : " 
		<< GameOfLife::getNumOfAlive()<<endl;	
		
	game3.write2File("merge3-4.txt");
		
		
	getchar(); //terminal beklemesi icin
	return 0;
}
