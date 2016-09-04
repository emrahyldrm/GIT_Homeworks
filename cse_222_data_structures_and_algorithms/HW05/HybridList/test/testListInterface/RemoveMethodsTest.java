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
        List<Integer> hybrid = Factory.factory("hybrid");
        
        hybrid.add(55);
        hybrid.add(25);
        hybrid.add(55);
        System.out.println(hybrid.size());
        hybrid.remove(2);
        System.out.println(hybrid.size());
        assertEquals(0, hybrid.lastIndexOf(55));
        System.out.println("after remove method  index  equality test, passed\n");       
        
    }    

    @Test
    public void removeMethodTest2()
    {
        List<Integer> hybrid = Factory.factory("hybrid");
        
        hybrid.add(55);
        hybrid.add(25);
        hybrid.add(55);
        hybrid.remove(2);
        assertNotSame(2, hybrid.lastIndexOf(55));
        System.out.println("after remove method  size  equality test, passed\n");       
       
    }  

       
    @Test
    public void removeMethodTest3()
    {
        List<Integer> hybrid = Factory.factory("hybrid");
        List<Integer> array = null;
        
        try
        {
            hybrid.add(55);
            hybrid.add(25);
            array.add(55);
            hybrid.remove(array);
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
        List<Integer> hybrid = Factory.factory("hybrid");
        List<Integer> array = Factory.factory("hybrid");
        
        hybrid.add(55);
        hybrid.add(25);
        hybrid.remove(0);
        assertEquals(false, hybrid.contains(55));   
        System.out.println("after remove method  element contains not equality test, passed\n");     

    }      
    

}
