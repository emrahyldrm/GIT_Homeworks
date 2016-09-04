/**
 * @author 111044056 Emrah YILDIRIM
 * GameOfLife.java from HW09
 */

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Arrays;
import java.util.Scanner;

public class GameOfLife {
	
	private Cell [] livingsReal;
	private Cell [] livingsControl;	
	private static int numOfAlive = 0;
	private int sizeRow=0, sizeCol=0;
	private int counterControl=0, counter=0, capacity=20;
	
	GameOfLife() 
	{ 
		livingsReal = new Cell[capacity];	
	}
	
	/**
	 * find how many cells in all games
	 * @return all cells number
	 */
	public static int getAllObjNum(){ return numOfAlive; }
	
	/**
	 * @return row size
	 */
	public int getRowSize() { return sizeRow; }
	
	/**
	 * @return all column size
	 */
	public int getColSize() { return sizeCol; }
	
	/**
	 * @param row number
	 */
	public void setRow( int row){ sizeRow = row; }
	
	/**
	 * @param col cloumn number
	 */
	public void setCol( int col) { sizeCol = col; }
	
		
	/**
	 * find max row number in game
	 * @return max row number
	 */
	public int findMaxRow()
	{
		int max=0, num=0;
		
		for(int i=0; i < counter; ++i)
		{
			if((num=livingsReal[i].getX()) > max)
				max=num;
		}
		return max;
	}
	
	
	/**
	 * find max column number in game
	 * @return column row number
	 */
	public int findMaxCol()
	{
		int max=0, num=0;
		
		for(int i=0; i < counter; ++i)
		{
			if((num=livingsReal[i].getY()) > max)
				max=num;
		}
		return max;
	}
	
	
	
	/**
	 * find the cell if is alive
	 * @param cell cell object for control
	 * @return is alive or not 
	 */
	public boolean isAlive(Cell cell)
	{
		
		for(int i=0; i < counterControl; ++i)
		{
			if(livingsControl[i].getX() == cell.getX() &&
			   livingsControl[i].getY() == cell.getY())
				return true;
		}		
		return false;
	}

	
	/**
	 * print the board on screen
	 */
	public void printBoard()
	{
		int startRow=0, startCol=0;
		
		for(int i = 0; i < sizeCol; ++i)
			if(isAlive(new Cell(-1, i)))
			{
				startRow = -1;
				break;
			}
				
		for(int i = 0; i < sizeRow; ++i)
			if(isAlive(new Cell(i, -1)))
			{
				startCol = -1;
				break;
			}
				
		for(int i=startRow; i < sizeRow; ++i)
		{	
			for(int j=startCol; j < sizeCol; ++j)
			{
				if(isAlive(new Cell(i,j)))
					System.out.printf("X");
				else
					System.out.printf(".");
			}
			System.out.printf("\n");
		}
		System.out.printf("\n");
	}

	

	/**
	 * do life job for each cell parameter
	 * @param cell cell object for life job
	 */
	public void bornOrKill(Cell cell)
	{
		int status = howManyNB(cell);
		
		//canliysa olecek mi diye bakar
		//yoksa da canlanacak mi
		if(isAlive(cell))
		{	
			if(status < 2 || status > 3)
				killCell(cell);
		}
		else
		{
			if(status == 3)
				addElement(cell);

		}
	}

	
	/**
	 * count neighbor number
	 * @param cell cell object for counting
	 * @return neighbor count
	 */
	public int howManyNB(Cell cell)
	{
		int countNB=0;
 		int currentRow = cell.getX(), currentCol = cell.getY();
		
		
		if(isAlive(new Cell(currentRow-1, currentCol-1)))
			countNB++;
		if(isAlive(new Cell(currentRow-1, currentCol)))
			countNB++;
		if(isAlive(new Cell(currentRow-1, currentCol+1)))
			countNB++;
		if(isAlive(new Cell(currentRow, currentCol-1)))
			countNB++;
		if(isAlive(new Cell(currentRow, currentCol+1)))
			countNB++;
		if(isAlive(new Cell(currentRow+1, currentCol-1)))
			countNB++;
		if(isAlive(new Cell(currentRow+1, currentCol)))
			countNB++;
		if(isAlive(new Cell(currentRow+1, currentCol+1)))
			countNB++;
		
		//System.out.printf("%d %b\n", countNB, isAlive(new Cell(currentRow+1, currentCol+1)));
		return countNB;
	}

	

	/**
	 * delete the cell that was passed paramater
	 * @param cell object for kill job
	 */
	public void killCell(Cell cell)
	{		
		Cell [] temp = new Cell[capacity];
		int j=0;
		
		for(int i=0; i < counter; ++i)
			if(livingsReal[i].getX() == cell.getX() && livingsReal[i].getY() == cell.getY())
				continue;
			else
			{
				temp[j] = (Cell) livingsReal[i].clone();
				++j;
			}
			
		livingsReal = temp;
		//temp=livingsControl;
		counter--;
		numOfAlive--;
				
	}

	
	
/**
 * merge two games
 * @param other game
 */
	public void mergeGames(GameOfLife other)
	{
		int otherSize = other.counter;
		boolean flag=false;
		
		// hangi objenin board u daha buyukse ona gecilir
		// satir ve sutun ayri ayri kontrol edilir
		if(other.findMaxRow() > findMaxRow())
			setRow(other.getRowSize());
		
		if(other.findMaxCol() > findMaxCol())
			setCol(other.getColSize());
			
		
		for(int i=0; i < otherSize; ++i)
		{
			if(!isAlive(other.livingsReal[i]))
			{
				addElement(other.livingsReal[i]);
				flag = true;
			}
		
		}

		if(flag)
			sync();
		
	}

	
	/**
	 * sync two arrays
	 */
	public void sync()
	{
		livingsControl = livingsReal.clone();
		counterControl = counter;
	}
	

	/**
	 * play the game one step
	 */
	public void play()
	{
		sync();
		
		if( findMaxRow() >= sizeRow-1 || findMaxCol() >= sizeCol-1)
		{
		   sizeRow++;
		   sizeCol++;
		}
		
		for(int i=-1; i < sizeRow; ++i)
		{	
			for(int j=-1 ; j < sizeCol; ++j)
				bornOrKill(new Cell(i,j));	
		}
		
		sync();
		

		printBoard();
		System.out.println("\n");
		
	
	}
	
	/**
	 * add cell parameter to Cell array
	 * @param cell object for adding
	 */
	public void addElement(Cell cell)
	{
		
		if(counter < capacity)
		{
			livingsReal[counter] = new Cell(cell.getX(), cell.getY());
			counter++;
			numOfAlive++;
		}
		else
		{
			capacity *= 2;
			Cell [] temp = new Cell[capacity];
			Arrays.fill(temp, new Cell(-1,-1));
			for(int i=0; i < capacity/2; ++i)
			{
				temp[i].setX(livingsReal[i].getX());
				temp[i].setY(livingsReal[i].getY());
			}
			livingsReal = temp;
			
			livingsReal[counter].setX(cell.getX());
			livingsReal[counter].setY(cell.getY());
			counter++;
			numOfAlive++;
			
		}
	
	}
	
	
	/**
	 * read from file the maps
	 * @param fileName
	 * @throws FileNotFoundException
	 */

	void readFile(String fileName) throws FileNotFoundException
	{
		/*File map = new File(fileName);
		FileReader readFile = new FileReader(map);
		BufferedReader readInteger = new BufferedReader(readFile);
		
		readInteger.read*/
		int cell;
		Scanner map = new Scanner(new File(fileName));
		
		sizeRow = map.nextInt();
		sizeCol = map.nextInt();	
		
			
		for(int i=0; i < sizeRow; ++i)
		{
			for(int j=0; j < sizeCol; ++j)
			{
				cell = map.nextInt();
				if(cell == 1)				
					addElement(new Cell(i, j));
			}
		}	
	
	sync();
	
	
	map.close();
}

	
	
}
