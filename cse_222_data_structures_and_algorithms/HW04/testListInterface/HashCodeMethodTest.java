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
public class HashCodeMethodTest {
    
    public HashCodeMethodTest() {
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
    public void testHasCode1()
    {
        List<Integer> linked = Factory.factory("linked");
        List<Integer> array = Factory.factory("array");
        
        assertEquals(linked.hashCode(), array.hashCode());
        System.out.println("hashcode method equality test, passed\n");                      
    }
    
    
    @Test
    public void testHasCode2()
    {
        List<Integer> linked = Factory.factory("linked");
        List<Integer> array = Factory.factory("array");
        array.add(1);
        assertNotSame(linked.hashCode(), array.hashCode());
        System.out.println("hashcode method not equality test, passed\n");
    }
    
    @Test
    public void testHasCode3()
    {
        List<Integer> linked = Factory.factory("linked");
        List<Integer> linked2 = Factory.factory("linked");
        linked.add(1);
        assertNotSame(linked.hashCode(), linked2.hashCode());
        System.out.println("hashcode method not equality between different lists test, passed\n");
    }    
    
      

}
