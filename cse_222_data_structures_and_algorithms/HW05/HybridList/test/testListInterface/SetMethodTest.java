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
public class SetMethodTest {
    
    public SetMethodTest() {
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
    public void setMethodTest1()
    {
        List<Integer> hybrid = Factory.factory("hybrid");
        List<Integer> array = Factory.factory("hybrid");
        
        hybrid.add(455);
        hybrid.set(0, 222);

        int a= hybrid.get(0);
        assertEquals(222, a);      
        System.out.println("after set method  elements equality test, passed\n");                     
    }      
    
    @Test
    public void setMethodTest2()
    {
        List<Integer> hybrid = Factory.factory("hybrid");
        List<Integer> array = Factory.factory("hybrid");
        
        try
        {
            hybrid.set(0, 222);
        }
        catch(Exception e)
        {
            if(!(e instanceof IndexOutOfBoundsException))
                fail();
        }
        System.out.println("Indexoutofboundsexp has been caught, passed\n");                     
    }      
    @Test
    public void setMethodTest3()
    {
        List<Integer> hybrid = Factory.factory("hybrid");
        List<Integer> array = Factory.factory("hybrid");
        
        hybrid.add(455);
        hybrid.set(0, 222);

        assertEquals(true, hybrid.contains(222)); 
        System.out.println("after set method  elements contains test, passed\n");                     

    } 
    
    
    @Test
    public void setMethodTest4()
    {
        List<Integer> hybrid = Factory.factory("hybrid");
        List<Integer> array = Factory.factory("hybrid");
        
        hybrid.add(455);
        hybrid.set(0, 222);

        assertEquals(false, hybrid.contains(455));        
        System.out.println("after set method  elements not contain test, passed\n");                     

    } 
            
}
