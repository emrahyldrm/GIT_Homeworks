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
public class LastIndexOfMethodTest {
    
    public LastIndexOfMethodTest() {
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
    public void lastIndexOfMethodTest1()
    {
        List<Integer> hybrid = Factory.factory("hybrid");
        
        hybrid.add(55);
        hybrid.add(25);
        hybrid.add(55);
        assertEquals(2, hybrid.lastIndexOf(55));        
        System.out.println("lastindexof method  equality test, passed\n");             
       
    }
    
    
    @Test
    public void lastIndexOfMethodTest2()
    {
        List<Integer> hybrid = Factory.factory("hybrid");
        List<Integer> array = Factory.factory("array");
        
        hybrid.add(55);
        array.add(25);
        array.add(55);
        assertNotSame(array.lastIndexOf(55), hybrid.lastIndexOf(55));         
        System.out.println("lastindexof method not equality test between two lists, passed\n");       
    }
    
    @Test
    public void lastIndexOfMethodTest3()
    {
        List<Integer> hybrid = Factory.factory("hybrid");
        
        hybrid.add(55);

        assertEquals(hybrid.lastIndexOf(55), hybrid.lastIndexOf(55));        
        System.out.println("lasindexof method  equality test two times on same list, passed\n");        
    }
    
    
    
}
