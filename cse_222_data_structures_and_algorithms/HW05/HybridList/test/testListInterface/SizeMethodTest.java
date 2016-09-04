/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package testListInterface;

import hybridListOthers.Factory;
import java.util.List;
import org.junit.After;
import org.junit.AfterClass;
import org.junit.Before;
import org.junit.BeforeClass;
import org.junit.Test;
import static org.junit.Assert.*;

/**
 *
 * @author Jason
 */
public class SizeMethodTest {
    
    public SizeMethodTest() {
    }
    
    @BeforeClass
    public static void setUpClass() {
    }
    
    @AfterClass
    public static void tearDownClass() {
    }
    
    @Before
    public void setUp() {
    }
    
    @After
    public void tearDown() {
    }

    @Test
    public void sizeMethodTest1()
    {
        List<Integer> hybrid = Factory.factory("hybrid");
        
        hybrid.add(55);
        hybrid.add(56);

        assertEquals(hybrid.size(),2);
        System.out.println("size method equality test after adding , passed\n");                     

    }
    
    @Test
    public void sizeMethodTest2()
    {
        List<Integer> hybrid = Factory.factory("hybrid");
        List<Integer> array = Factory.factory("array");
        
        hybrid.add(55);
        hybrid.add(56);
        array.add(550);
        array.add(55);
        
        assertEquals(hybrid.size(), array.size());
        System.out.println("size method equality test between 2 lists after adding , passed\n");   
    }
    
    
    @Test
    public void sizeMethodTest3()
    {
        List<Integer> hybrid = Factory.factory("hybrid");
        assertEquals(hybrid.size(),0);
        System.out.println("size method equality  0 test without adding , passed\n");   
    }
        
    @Test
    public void sizeMethodTest4()
    {
        List<Integer> hybrid = Factory.factory("hybrid");        
        hybrid.add(55);
        hybrid.add(56);
        hybrid.remove(1);
        
        assertEquals(hybrid.size(), 1);
        System.out.println("size method equality test after add and remove , passed\n");   
        
    }    
    
    
    @Test
    public void sizeMethodTest5()
    {
        List<Integer> hybrid = null;
        try
        {
            int a = hybrid.size();
        }catch(Exception e)
        {
            if(!(e instanceof NullPointerException))
                    fail();
        }
        System.out.println("NullPointerException has been caught, passed\n"); 
    }        
}
