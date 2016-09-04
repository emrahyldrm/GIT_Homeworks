/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package testListInterface;

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
public class RetainAllTest {
    
    public RetainAllTest() {
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
    public void retainAllMethodTest1()
    {
        List<Integer> linked = Factory.factory("linked");
        List<Integer> array = Factory.factory("array");
        
        linked.add(55);
        linked.add(25);
        linked.add(55);
        linked.retainAll(array);
        assertEquals(0, linked.size());  
        System.out.println("after retainall method size equality test, passed\n");                     
    }  
    
    @Test
    public void retainAllMethodTest2()
    {
        List<Integer> linked = Factory.factory("linked");
        List<Integer> array = Factory.factory("array");
        
        linked.add(55);
        linked.add(25);
        array.add(55);
        linked.retainAll(array);
        assertNotSame(false, linked.contains(55));       
        System.out.println("after retainall method  elements not equality test, passed\n");                     
    }  
    
    
    @Test
    public void retainAllMethodTest3()
    {
        List<Integer> linked = Factory.factory("linked");
        List<Integer> array = Factory.factory("linked");
        
        linked.add(55);
        linked.add(25);
        array.add(12);
        linked.retainAll(array);
        assertEquals(false, linked.contains(55));   
        System.out.println("after retainall method  elements equality test, passed\n");                     
        
    }      
    
    @Test
    public void retainAllMethodTest4()
    {
        List<Integer> linked = Factory.factory("linked");
        List<Integer> array = null;
        
        try
        {
            linked.add(55);
            linked.add(25);
            array.add(55);
            linked.retainAll(array);
        }
        catch(Exception e)
        {
            if(!(e instanceof NullPointerException))
                fail();
        }
        System.err.println("Nullpointerexp has been caught, passed");
    }       
    
}
