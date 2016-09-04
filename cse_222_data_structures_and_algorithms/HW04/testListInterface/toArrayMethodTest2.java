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
public class toArrayMethodTest2 {
    
    public toArrayMethodTest2() {
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
    public void toArrayMethod2Test1()
    {
        List<Integer> linked = Factory.factory("linked");
        Integer [] array = new Integer[20];
        
        try
        {
           linked.add(455);
           linked.add(222);
           linked.add(12);
           linked.add(21);
           linked.add(44355);
           linked.add(22432);

           array = (Integer [])linked.toArray(array);
        }
        catch(Exception e)
        {
           if((e instanceof ClassCastException))
                fail();
        }
        System.out.println("ClassCastException has been caught, passed");

    } 
    
    
    
    @Test
    public void toArrayMethod2Test2()
    {
        List<Integer> linked = Factory.factory("linked");
        Integer [] array = new Integer[20];
        
  
        linked.add(455);
        linked.add(222);
        linked.add(12);
        linked.add(21);
        linked.add(44355);
        linked.add(22432);
        
        array = linked.toArray(array);
        int a = array[0];
        assertEquals(455, a);
        System.out.println("compare new array's element is expected test, passed"); 
    }     
    
    @Test
    public void toArrayMethod2Test3()
    {
        List<Integer> linked = Factory.factory("linked");
        Object [] array = new Object[20];
        
  
        linked.add(455);
        linked.add(222);
        linked.add(12);
        linked.add(21);
        linked.add(44355);
        linked.add(22432);

        int expected=0;
        array = linked.toArray(array);
        for (int i = 0; i < array.length; i++) {
            if(array[i] != null)
                expected++;
        }
        assertEquals(expected, 6);
        System.out.println("compare new array size and to array return value size test, passed"); 
    }     
    
    
    @Test
    public void toArrayMethod2Test4()
    {
        List<Integer> linked = null;
        Integer [] array = new Integer[20];
        
        try
        {
           array = (Integer [])linked.toArray(array);
        }
        catch(Exception e)
        {
           if(!(e instanceof NullPointerException))
                fail();
        }
        System.out.println("NullPointerException has been caught, passed");
    } 
    
    
    
}
