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
        List<Integer> hybrid = Factory.factory("hybrid");
        List<Integer> array = Factory.factory("array");
        
        hybrid.add(55);
        hybrid.add(25);
        hybrid.add(55);
        hybrid.removeAll(array);
        assertNotSame(0, hybrid.size());          
        System.out.println("after removeAll method  size  equality test, passed\n");       
    }  
    
    @Test
    public void removeAllMethodTest2()
    {
        List<Integer> hybrid = Factory.factory("hybrid");
        List<Integer> array = Factory.factory("array");
        
        hybrid.add(55);
        hybrid.add(25);
        array.add(55);
        hybrid.removeAll(array);
        assertNotSame(true, hybrid.contains(55));             
        System.out.println("after removeAll method  element contains not  equality test, passed\n");     
    }  
    
    
    @Test
    public void removeAllMethodTest3()
    {
        List<Integer> hybrid = Factory.factory("hybrid");
        List<Integer> array = Factory.factory("hybrid");
        
        hybrid.add(55);
        hybrid.add(25);
        array.add(12);
        hybrid.removeAll(array);
        assertEquals(true, hybrid.contains(55));   
        System.out.println("after removeAll method  element contains equality test, passed\n");     

    }      
    
    @Test
    public void removeAllMethodTest4()
    {
        List<Integer> hybrid = Factory.factory("hybrid");
        List<Integer> array = null;
        
        try
        {
            hybrid.add(55);
            hybrid.add(25);
            array.add(55);
            hybrid.removeAll(array);
        }
        catch(Exception e)
        {
            if(!(e instanceof NullPointerException))
                fail();
        }
            System.out.println("NullPointerException has been caught, passed\n");             
   }       
    
}
