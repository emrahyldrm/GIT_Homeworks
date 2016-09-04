/**
 * @author 111044056 Emrah YILDIRIM
 * HW09 Cell class file
 * Cell.java from HW09
 */



public class Cell implements Cloneable
{
	private int x;
	private int y;
	
	/**
	 * No Paramater Constructor 
	 * 
	 */
	Cell() {y = x = -1;}
	
	
	/**
	 * Constructor 
	 *
	 * @param nX  integer for x
	 * @param nY  integer for y
	 */
	Cell(int nX, int nY) { setX(nX); setY(nY);}
	
	/**
	 * getter for member x 
	 * no parameter
	 */
	
	/**
	 * getter for member x
	 * no parameter
	 * @return member x
	 */
	public int getX()	{return x;}
	
	/**
	 * getter for member y
	 * no parameter
	 * @return member y
	 */
	public int getY()	{return y;}
	

	/**
	 * setter for member x
	 * @param nX set member x with nX
	 */
	public void setX(int nX)	{x = nX;}
	
	
	/**
	 * setter for member y
	 * @param nY set member y with nY
	 */
	public void setY(int nY)	{y = nY;}
	
	
	/**
	 * set the cell
	 * @param nX set member x with nX
	 * @param nY set member y with nY
	 */
	public void setCell(int nX, int nY)  { setX(nX); setY(nY);}
		
	
	/**
	 * string formatter
	 * @return String
	 */
	public String toString()
	{
		return String.format("%d - %d", x, y);
		
	}
	
	
	/**
	 * clone the object cell
	 * @return super.clone()
	 */
	public Cell clone()
	{
		try {
			return (Cell) super.clone();
		} 
		catch (CloneNotSupportedException e) {
			e.printStackTrace();
			return this;
		}		
	}
	

}
