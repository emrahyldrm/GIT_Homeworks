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
public class EqualsMethodTest {
    
    public EqualsMethodTest() {
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
    public void equalsTest1()
    {
        List<Integer> linked = Factory.factory("linked");
        List<Integer> array = Factory.factory("array");
        
        assertEquals(true, linked.equals(array));
        System.out.println("Two empty collections equality test(true), passed\n");             
    }
    
    
    
    @Test
    public void equalsTest2()
    {
        List<Integer> linked = Factory.factory("linked");
        List<Integer> array = Factory.factory("array");
        
        array.add(34);
        assertEquals(false, linked.equals(array));
        System.out.println("Two empty collections equality test(false), passed\n");             
    }
    
    
    
    @Test
    public void equalsTest3()
    {
        List<Integer> linked = Factory.factory("linked");
        List<Integer> array = Factory.factory("array");
        
        array.add(34);
        linked.add(34);
        assertEquals(true, linked.equals(array));
        System.out.println("Two not empty collections equality test(true), passed\n");              
    }
    
    
    @Test
    public void equalsTest4()
    {
        List<Integer> linked = Factory.factory("linked");
        List<Integer> array = Factory.factory("array");
        
        array.add(34);
        linked.add(34);
        assertEquals(true, linked.equals(array) && array.equals(linked));
        System.out.println("Two not empty collections equality test(true), passed\n");                      
    }
    
    
    @Test
    public void equalsTest5()
    {
        List<Integer> linked = Factory.factory("linked");
        List<Integer> array = Factory.factory("array");
        
        array.add(34);
        linked.add(34);
        linked.remove(new Integer(34));
        assertEquals(false, linked.equals(array) && array.equals(linked));
        System.out.println("After add and remove equality test(true), passed\n");                              
    }
}