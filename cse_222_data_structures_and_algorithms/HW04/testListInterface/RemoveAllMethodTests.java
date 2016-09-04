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
public class RemoveAllMethodTests {
    
    public RemoveAllMethodTests() {
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
    public void removeAllMethodTest1()
    {
        List<Integer> linked = Factory.factory("linked");
        List<Integer> array = Factory.factory("array");
        
        linked.add(55);
        linked.add(25);
        linked.add(55);
        linked.removeAll(array);
        assertNotSame(0, linked.size());          
        System.out.println("after removeAll method  size  equality test, passed\n");       
    }  
    
    @Test
    public void removeAllMethodTest2()
    {
        List<Integer> linked = Factory.factory("linked");
        List<Integer> array = Factory.factory("array");
        
        linked.add(55);
        linked.add(25);
        array.add(55);
        linked.removeAll(array);
        assertNotSame(true, linked.contains(55));             
        System.out.println("after removeAll method  element contains not  equality test, passed\n");     
    }  
    
    
    @Test
    public void removeAllMethodTest3()
    {
        List<Integer> linked = Factory.factory("linked");
        List<Integer> array = Factory.factory("linked");
        
        linked.add(55);
        linked.add(25);
        array.add(12);
        linked.removeAll(array);
        assertEquals(true, linked.contains(55));   
        System.out.println("after removeAll method  element contains equality test, passed\n");     

    }      
    
    @Test
    public void removeAllMethodTest4()
    {
        List<Integer> linked = Factory.factory("linked");
        List<Integer> array = null;
        
        try
        {
            linked.add(55);
            linked.add(25);
            array.add(55);
            linked.removeAll(array);
        }
        catch(Exception e)
        {
            if(!(e instanceof NullPointerException))
                fail();
        }
            System.out.println("NullPointerException has been caught, passed\n");             
   }       
    
}
