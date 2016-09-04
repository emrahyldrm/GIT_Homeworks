package testListInterface;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;
import org.junit.After;
import org.junit.AfterClass;
import org.junit.Before;
import org.junit.BeforeClass;
import org.junit.Test;
import static org.junit.Assert.*;
import testListInterface.Factory;
import java.lang.System.*;
/**
 *
 * @author Jason
 */
public class AddAllMethodTest {
    
    public AddAllMethodTest() {
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
    public void addAllTest1()
    {
        System.out.print("Add All method test other collection");
        List<Integer> linked = Factory.factory("linked");
        List<Integer> array = Factory.factory("array");
        
        linked.add((45));
        linked.add((451));
        linked.add((452));
        linked.add((425));
        
        array.addAll(linked);
        array.add(1234);
        
        int expectedSize = array.size();
        assertEquals(linked.size()+1, expectedSize);
    }
    
    
    @Test
    public void addAllTest2()
    {
        System.out.print("Add All method test other collection");
        List<Integer> linked = Factory.factory("linked");
        List<Integer> array = Factory.factory("array");
        
        array.add((45));
        array.add((451));
        array.add((452));
        array.add((425));
        
        linked.addAll(array);
        linked.add(1234);
        
        int expectedSize = linked.size();
        assertEquals(array.size()+1, expectedSize);
    }
    
    
    @Test
    public void addAllTest3()
    {
        List<Integer> array = null;
        
        try
        {
            array.add(54);
        }catch (NullPointerException e)
        {
            System.out.println("Null Poınter exception has been caught");
        }
    }
    
    
    @Test
    public void addAllTest4()
    {
        List<Integer> linked = Factory.factory("linked");
        List<Integer> array = Factory.factory("array");
        array.add(23);
        array.add(45);
        array.add(5656);
        
        try
        {
            linked.addAll(5, array);
        }
        catch(IndexOutOfBoundsException e)
        {
            System.out.println("IndexoutOfBound exp has been caught");
        }
    }
    
    
    @Test
    public void addAllTest5()
    {        
        System.out.print("Add All method test other collection element equality test");
        List<Integer> linked = Factory.factory("linked");
        List<Integer> array = Factory.factory("array");
        
        array.add((45));
        array.add((451));
        array.add((452));
        array.add((425));
        
        linked.addAll(array);
        linked.add(1234);
        
        int expected = linked.get(0);
        assertEquals(45, expected);
    }
}
