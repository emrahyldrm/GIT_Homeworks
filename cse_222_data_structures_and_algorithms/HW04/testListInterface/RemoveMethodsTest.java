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
public class RemoveMethodsTest {
    
    public RemoveMethodsTest() {
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
    public void removeMethodTest1()
    {
        List<Integer> linked = Factory.factory("linked");
        
        linked.add(55);
        linked.add(25);
        linked.add(55);
        linked.remove(2);
        assertEquals(0, linked.lastIndexOf(55));
        System.out.println("after remove method  index  equality test, passed\n");       
        
    }    

    @Test
    public void removeMethodTest2()
    {
        List<Integer> linked = Factory.factory("linked");
        
        linked.add(55);
        linked.add(25);
        linked.add(55);
        linked.remove(2);
        assertNotSame(2, linked.lastIndexOf(55));
        System.out.println("after remove method  size  equality test, passed\n");       
       
    }  

       
    @Test
    public void removeMethodTest3()
    {
        List<Integer> linked = Factory.factory("linked");
        List<Integer> array = null;
        
        try
        {
            linked.add(55);
            linked.add(25);
            array.add(55);
            linked.remove(array);
        }
        catch(Exception e)
        {
            if(!(e instanceof NullPointerException))
                fail();
        }
            System.out.println("NullPointerException has been caught, passed\n");             
   }    

    @Test
    public void removeMethodTest4()
    {
        List<Integer> linked = Factory.factory("linked");
        List<Integer> array = Factory.factory("linked");
        
        linked.add(55);
        linked.add(25);
        linked.remove(0);
        assertEquals(false, linked.contains(55));   
        System.out.println("after remove method  element contains not equality test, passed\n");     

    }      
    

}
