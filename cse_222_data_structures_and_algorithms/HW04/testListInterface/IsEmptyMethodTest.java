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
public class IsEmptyMethodTest {
    
    public IsEmptyMethodTest() {
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
    public void isEmptyMethodTest1()
    {
        List<Integer> linked = Factory.factory("linked");
        List<Integer> array = Factory.factory("array");
        
        linked.add(34);
        array.add(54);
        
        assertEquals(array.isEmpty(), linked.isEmpty()); 
        System.out.println("isEmpty method equality between two lists test, passed\n");       
    }
    
    @Test
    public void isEmptyMethodTest2()
    {
        List<Integer> linked = Factory.factory("linked");
        List<Integer> array = Factory.factory("array");
        
        linked.add(34);
        assertNotSame(array.isEmpty(), linked.isEmpty());   
        System.out.println("isEmpty method not equality between two lists test, passed\n");    
    }


    @Test
    public void isEmptyMethodTest3()
    {
        List<Integer> linked = Factory.factory("linked");
        
        linked.add(34);
        assertEquals(false, linked.isEmpty());   
        System.out.println("isEmpty method not equality test, passed\n");     
    }
    
    @Test
    public void isEmptyMethodTest4()
    {
        List<Integer> linked = Factory.factory("linked");
        
        assertEquals(true, linked.isEmpty());    
        System.out.println("isEmpty method equality test, passed\n");            
    }

}
