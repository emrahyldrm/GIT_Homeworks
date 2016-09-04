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
public class GetMethodTest {
    
    public GetMethodTest() {
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
    public void getMethodTest1()
    {
        List<Integer> linked = Factory.factory("linked");
        List<Integer> hybrid = Factory.factory("hybrid");
        
        hybrid.add(34);
        linked.add(34);
        int a = linked.get(0);
        assertEquals(34, a);
        System.out.println("get method element equality test, passed\n");                      
    }
    
    @Test
    public void getMethodTest2()
    {
        List<Integer> linked = Factory.factory("linked");
        List<Integer> hybrid = Factory.factory("hybrid");
        
        linked.add(345);
        linked.add(34);
        int a = linked.get(0);
        assertNotSame(34, a);
        System.out.println("get method element not equality test, passed\n");
    }
    
    @Test
    public void getMethodTest3()
    {
        List<Integer> linked = Factory.factory("linked");
        List<Integer> hybrid = Factory.factory("hybrid");

        try
        {        
            hybrid.add(34);
            linked.add(34);
            int a = linked.get(14);
        }catch(IndexOutOfBoundsException e)
        {
            System.out.println("IndexOutOfBounds Exp has been caught");
        }
    }

    
    
    
    
}
