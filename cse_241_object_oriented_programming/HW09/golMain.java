/** 
 * @author 111044056 Emrah YILDIRIM
 * golMain.java from HW09
 */

import java.io.FileNotFoundException;


public class golMain {
	public static void main(String args[]) throws FileNotFoundException
	{		
		GameOfLife game1 = new GameOfLife();
		GameOfLife game2 = new GameOfLife();
		GameOfLife game3 = new GameOfLife();
		GameOfLife game4 = new GameOfLife();
		GameOfLife game5 = new GameOfLife();

		game1.readFile("map1.txt");
		game2.readFile("map2.txt");
		game3.readFile("map3.txt");
		game4.readFile("map4.txt");
		game5.readFile("map5.txt");
		
		System.out.printf("all cells number\n");
		System.out.println(GameOfLife.getAllObjNum());
		game3.printBoard();
		
		
		System.out.printf("game1++ 3 times\n");
		game1.printBoard();
		game1.play();
		game1.play();
		game1.play();
		
		
		System.out.printf("------------------------------\n");
		System.out.printf("game2++ 3 times\n");
		game2.play();
		game2.play();
		game2.play();

		System.out.printf("------------------------------\n");
		
		System.out.printf("game3++ 3 times\n");
		game3.play();
		game3.play();
		game3.play();
		
		
		System.out.printf("------------------------------\n");
		System.out.printf("game4++ 3 times\n");
		game4.play();
		game4.play();
		game4.play();

		System.out.printf("------------------------------\n");
		
		System.out.printf("------------------------------\n");
		System.out.printf("game5++ 3 times\n");
		game5.play();
		game5.play();
		game5.play();

		System.out.printf("------------------------------\n");
		
		System.out.print("game1\n");
		game1.printBoard();
		System.out.print("game2\n");
		game2.printBoard();
		System.out.print("game1 merge with game2\n");
		
		game1.mergeGames(game2);
		System.out.print("game1 as merged with game2\n");
		game1.printBoard();
		System.out.printf("------------------------------\n");
		

		System.out.print("game4\n");
		game4.printBoard();
		System.out.print("game3\n");
		game3.printBoard();
		System.out.print("game4 merge with game3\n");
		
		game4.mergeGames(game3);
		System.out.print("game4 as merged with game3\n");
		game4.printBoard();
		System.out.printf("------------------------------\n");
		
		System.out.printf("all cells number\n");
		System.out.println(GameOfLife.getAllObjNum());
		
	}

}
