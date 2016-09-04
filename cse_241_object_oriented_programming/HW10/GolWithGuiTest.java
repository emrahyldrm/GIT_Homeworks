

public class GolWithGuiTest 
{
	public static void main(String[] args)
	{		

		try 
		{
			System.setProperty("java.util.Arrays.useLegacyMergeSort", "true");
			GameOfLife game = new GameOfLife();		

		}
		catch (Exception e) 
		{
			e.printStackTrace();
		}
		
	}
}
