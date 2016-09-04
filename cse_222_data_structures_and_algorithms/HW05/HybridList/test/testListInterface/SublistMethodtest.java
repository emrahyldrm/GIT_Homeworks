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
        List<Integer> hybrid = Factory.factory("hybrid");
        List<Integer> array;
        
        hybrid.add(455);
        hybrid.add(222);
        hybrid.add(12);
        hybrid.add(21);
        hybrid.add(44355);
        hybrid.add(22432);
        
        array = hybrid.subList(2, 5);
      
        assertEquals(hybrid.containsAll(array), true);
        System.out.println("after create sublist containsall test, passed\n");                     

    } 
    
    
    @Test
    public void sublistMethodTest2()
    {
        List<Integer> hybrid = Factory.factory("hybrid");
        List<Integer> array;
        
        try
        {
            array = hybrid.subList(2, 5);
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
        List<Integer> hybrid = null;
        List<Integer> array;
        
        try
        {
            array = hybrid.subList(2, 5);
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
        List<Integer> hybrid = Factory.factory("hybrid");
        List<Integer> array;
        
        hybrid.add(455);
        hybrid.add(222);
        hybrid.add(12);
        hybrid.add(21);
        hybrid.add(44355);
        hybrid.add(22432);
        
        array = hybrid.subList(2, 5);

        assertEquals(array.size(), 3);
        System.out.println("after create sublist size test, passed\n");                     
    } 
        
    
    
}
