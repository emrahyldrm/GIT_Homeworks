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
public class IndexOfMethodTest {
    
    public IndexOfMethodTest() {
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
    public void indexOfMethodTest1()
    {
        List<Integer> linked = Factory.factory("linked");
        List<Integer> hybrid = Factory.factory("hybrid");
        
        linked.add(34);
        linked.add(54);
        
        assertEquals(1, linked.indexOf(54));
        System.out.println("indexOf method index equality test, passed\n"); 
        
    }
    
    
    @Test
    public void indexOfMethodTest2()
    {
        List<Integer> linked = Factory.factory("linked");
        List<Integer> hybrid = Factory.factory("hybrid");
        
        linked.add(34);
        linked.add(54);
        
        assertNotSame(0, linked.indexOf(54));
        System.out.println("indexOf method index not equality test, passed\n"); 
    }
    
    @Test
    public void indexOfMethodTest3()
    {
        List<Integer> linked = Factory.factory("linked");
        List<Integer> hybrid = Factory.factory("hybrid");
        
        hybrid.add(34);
        linked.add(54);
        
        assertEquals(hybrid.indexOf(34), linked.indexOf(54));
        System.out.println("indexOf method index equality between two lists test, passed\n"); 
    }
    
    
    @Test
    public void indexOfMethodTest4()
    {
        List<Integer> linked = Factory.factory("linked");
        List<Integer> hybrid = Factory.factory("hybrid");
        
        linked.add(34);
        hybrid.add(54);
        
        assertNotSame(hybrid.indexOf(54), linked.indexOf(54));
        System.out.println("indexOf method index not equality between two lists test, passed\n");         
    }
    
    
    @Test
    public void indexOfMethodTest5()
    {
        List<Integer> linked = null;
        try
        {
            linked.indexOf(5);
        }
        catch(NullPointerException e)
        {
            System.err.println("Null pointer exp has been caught");
        } 
           
    }
}
