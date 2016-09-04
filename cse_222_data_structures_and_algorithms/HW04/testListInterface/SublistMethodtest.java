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
public class SublistMethodtest {
    
    public SublistMethodtest() {
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
    public void sublistMethodTest1()
    {
        List<Integer> linked = Factory.factory("linked");
        List<Integer> array;
        
        linked.add(455);
        linked.add(222);
        linked.add(12);
        linked.add(21);
        linked.add(44355);
        linked.add(22432);
        
        array = linked.subList(2, 5);
      
        assertEquals(linked.containsAll(array), true);
        System.out.println("after create sublist containsall test, passed\n");                     

    } 
    
    
    @Test
    public void sublistMethodTest2()
    {
        List<Integer> linked = Factory.factory("linked");
        List<Integer> array;
        
        try
        {
            array = linked.subList(2, 5);
        }
        catch(Exception e)
        {
            if(!(e instanceof IndexOutOfBoundsException))
                fail();
        }
        System.out.println("IndexOutOfBoundsException has been caught, passed\n");             

    }  

    
    @Test
    public void sublistMethodTest3()
    {
        List<Integer> linked = null;
        List<Integer> array;
        
        try
        {
            array = linked.subList(2, 5);
        }
        catch(Exception e)
        {
            if(!(e instanceof NullPointerException))
                fail();
        }
        System.out.println("NullPointerException has been caught, passed\n");             

    }  
    
    
    @Test
    public void sublistMethodTest4()
    {
        List<Integer> linked = Factory.factory("linked");
        List<Integer> array;
        
        linked.add(455);
        linked.add(222);
        linked.add(12);
        linked.add(21);
        linked.add(44355);
        linked.add(22432);
        
        array = linked.subList(2, 5);
      
        assertEquals(array.size(), 3);
        System.out.println("after create sublist size test, passed\n");                     
    } 
        
    
    
}
