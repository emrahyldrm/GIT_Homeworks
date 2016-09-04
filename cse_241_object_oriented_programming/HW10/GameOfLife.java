/**
 * @author 111044056 Emrah YILDIRIM
 * GameOfLife.java from HW09
 */


import java.awt.Color;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.util.Scanner;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JOptionPane;
import javax.swing.Timer;



public class GameOfLife {
	
	private Cell [] livingsReal;
	private Cell [] livingsControl;	
	private Cell [] backup;
	private static int numOfAlive = 0;
	private int sizeRow=100, sizeCol=100;
	private int counterControl=0, counter=0, backCount=0, capacity=20;
	private int backNOA =0;
	boolean flag = true;

	


	private JFrame frame;
	private JFrame controlFrame;
	private JButton [][] buttons = new JButton[100][100];
	int r=0, c=0;
	
	public GameOfLife() 
	{ 
		livingsReal = new Cell[capacity];
		initialize();
		frame.setVisible(true);
		controlFrame.setVisible(true);
		printBoard();
	}
	
	public GameOfLife(String fileName) 
	{ 
		livingsReal = new Cell[capacity];
		try {
			readFile(fileName);
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		}

		initialize();
		frame.setVisible(true);
		controlFrame.setVisible(true);
		printBoard();

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
		for(int i=0; i < 100; ++i)
			for(int j=0; j < 100; ++j)
				if(isAlive(new Cell(i,j)))
					buttons[i][j].setBackground(Color.green);
				else
					buttons[i][j].setBackground(Color.black);
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
		counter--;
		numOfAlive--;
				
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
		

		for(int i=0; i < sizeRow; ++i)
		{	
			for(int j=0 ; j < sizeCol; ++j)
				bornOrKill(new Cell(i,j));	
		}
		
		sync();
		controlFrame.setTitle("Cell Counter: "+numOfAlive);
		System.out.println(""+counter);
		

		printBoard();
		
	
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
			Cell [] temp = new Cell[capacity+20];
			//Arrays.fill(temp, new Cell(-1,-1));
			for(int i=0; i < counter; ++i)
				temp[i] = livingsReal[i].clone();
			
			capacity += 20;
			livingsReal = temp;
			
			livingsReal[counter] = new Cell(cell.getX(), cell.getY());
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
	
		int cell;
		Scanner map = new Scanner(new File(fileName));
		
		
		int row = map.nextInt();
		int col = map.nextInt();		
		
			
		for(int i=0; i < row; ++i)
		{
			for(int j=0; j < col; ++j)
			{
				cell = map.nextInt();
				if(cell == 1)		
					addElement(new Cell(i, j));
			}
		}	
	
	sync();
	backup = livingsReal.clone();
	backCount = counter;
	backNOA = numOfAlive;
	map.close();
}
	
	
	public void write2File(String fileName) throws FileNotFoundException
	{
		PrintWriter out = new PrintWriter(fileName);
		int row = findMaxRow()+1;
		int col = findMaxCol()+1;
		sync();
		out.print(row+" "+col+"\n");
		for(int i = 0; i < row; ++i)
		{
			for(int j=0; j < col; ++j)
			{
				if(isAlive(new Cell(i,j)))
					out.print(1+" ");
				else
					out.print(0+" ");
			}
			out.print("\n");
		}
				
		out.close();
	}
	
	

	/***************************************************************************************************************/
	
	private void initialize()
	{
		frame = new JFrame();
		controlFrame = new JFrame("Command Window");
		
		frame.setLayout(new GridLayout(100,100));
		controlFrame.setLayout(new GridLayout(1,5));
/***************************************/
		JButton oneStep = new JButton("One Step");
		oneStep.addActionListener(new ActionListener()
		{
			public void actionPerformed(ActionEvent e) 
			{
				if(counter>0)
					play();
				else
					JOptionPane.showMessageDialog(controlFrame, "There is No Cell");
			}
		});
		controlFrame.add(oneStep);
/*************************************************************************************************/
		
		
		JButton startStop = new JButton("Start - Stop");
		Timer timer = new Timer(100, new ActionListener()
		{		    
		    public void actionPerformed(ActionEvent cont) 
		    {
		    	if(counter == 0)
		    	{
		    		JOptionPane.showMessageDialog(frame, "There is no cell !!");
		    		startStop.doClick();
		    	}
		    	else
		    		play();
		    }
		});
		
		ActionListener press = new ActionListener()
		{
			public void actionPerformed(ActionEvent e)
			{
				if(flag)
				{
					timer.start();
					flag = false;
					startStop.setText("STOP");
				}
				else
				{
					timer.stop();
					flag = true;
					startStop.setText("START");
					
				}
			}
			
		};
	
		
		startStop.addActionListener(press);
		controlFrame.add(startStop);
		
		
		
		
/*************************************************************************************************/
		
		JButton reset = new JButton("Reset");
		reset.addActionListener(new ActionListener()
		{
			public void actionPerformed(ActionEvent reset)
			{
				
				if(counter == 0)
					JOptionPane.showMessageDialog(controlFrame, "There is No Cell");
				else
				{
					livingsReal = backup.clone();
					counter = backCount;
					numOfAlive = backNOA;
					controlFrame.setTitle("Cell Counter: "+numOfAlive);
	
					sync();
					printBoard();
				}
			}
			
		});
		controlFrame.add(reset);
		
		
/*************************************************************************************************/

		JButton load = new JButton("Load");
		load.addActionListener(new ActionListener()
		{
			public void actionPerformed(ActionEvent load)
			{
				livingsReal = new Cell[capacity];
				counter = 0;
				numOfAlive=0;
				sync();
				String fileName = JOptionPane.showInputDialog(controlFrame, "Enter the File Name");
				File file = new File(fileName);
				if(!file.exists())
					JOptionPane.showMessageDialog(controlFrame, "File does Not Exist");
				
				try {
					readFile(fileName);
				} catch (FileNotFoundException e) {
					e.printStackTrace();
				}
				printBoard();
				controlFrame.setTitle("Cell Counter: "+numOfAlive);

				System.out.println(fileName);				
			}
		});
		
		controlFrame.add(load);
		
		
/*************************************************************************************************/

		JButton save = new JButton("Save");
		
		
		save.addActionListener(new ActionListener()
		{
			public void actionPerformed(ActionEvent e)
			{
				String file = JOptionPane.showInputDialog(controlFrame,"Enter the File Name");
				try {
					write2File(file);
				} catch (FileNotFoundException e1) {
					e1.printStackTrace();
				}
			}
			
		});
		
		controlFrame.add(save);
/*************************************************************************************************/

		for( r=0; r < 100; ++r)
			for(c=0; c < 100; ++c)
			{
				buttons[r][c] = new JButton(r+" "+c);
				buttons[r][c].setBackground(Color.black);
				
				buttons[r][c].addActionListener(new ActionListener() {
					public void actionPerformed(ActionEvent arg0)
					{
						JButton cButton = (JButton) arg0.getSource();
						
						if(cButton.getBackground() == Color.black)
						{
							cButton.setBackground(Color.green);
							String str = cButton.getText();
							String [] parts = str.split(" ");
							
							int x = Integer.parseInt(parts[0]);
							int y = Integer.parseInt(parts[1]);
							if(!isAlive(new Cell(x,y)) )
								addElement(new Cell(x,y));
							
							System.out.println(""+counter);
							controlFrame.setTitle("Cell Counter: "+numOfAlive);
							sync();

						}
						else
						{
							cButton.setBackground(Color.black);
							String str = cButton.getText();
							String [] parts = str.split(" ");
							
							int x = Integer.parseInt(parts[0]);
							int y = Integer.parseInt(parts[1]);
							if(isAlive(new Cell(x,y)) )
								killCell(new Cell(x, y));
							
							System.out.println(""+counter);
							controlFrame.setTitle("Cell Counter: "+numOfAlive);
							sync();

						}
					}

				});
				frame.add(buttons[r][c]);
			}
		
		frame.setTitle("Game Of Life");
		
		controlFrame.setBounds(125, 900, 600, 150);
		controlFrame.setResizable(false);
		controlFrame.setAlwaysOnTop(true);
		controlFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setBounds(0, 0, 900, 900);
		frame.setAlwaysOnTop(true);
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	}
	

}
