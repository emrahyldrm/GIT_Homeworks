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
import hybridListOthers.Factory;
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
        List<Integer> hybrid = Factory.factory("hybrid");
        
        linked.add((45));
        linked.add((451));
        linked.add((452));
        linked.add((425));
        
        hybrid.addAll(linked);
        hybrid.add(1234);
        
        int expectedSize = hybrid.size();
        assertEquals(linked.size()+1, expectedSize);
    }
    
    
    @Test
    public void addAllTest2()
    {
        System.out.print("Add All method test other collection");
        List<Integer> linked = Factory.factory("linked");
        List<Integer> hybrid = Factory.factory("hybrid");
        
        hybrid.add((45));
        hybrid.add((451));
        hybrid.add((452));
        hybrid.add((425));
        
        linked.addAll(hybrid);
        linked.add(1234);
        
        int expectedSize = linked.size();
        assertEquals(hybrid.size()+1, expectedSize);
    }
    
    
    @Test
    public void addAllTest3()
    {
        List<Integer> hybrid = null;
        
        try
        {
            hybrid.add(54);
        }catch (NullPointerException e)
        {
            System.out.println("Null Poınter exception has been caught");
        }
    }
    
    
    @Test
    public void addAllTest4()
    {
        List<Integer> linked = Factory.factory("linked");
        List<Integer> hybrid = Factory.factory("hybrid");
        hybrid.add(23);
        hybrid.add(45);
        hybrid.add(5656);
        
        try
        {
            linked.addAll(5, hybrid);
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
        List<Integer> hybrid = Factory.factory("hybrid");
        
        hybrid.add((45));
        hybrid.add((451));
        hybrid.add((452));
        hybrid.add((425));
        
        linked.addAll(hybrid);
        linked.add(1234);
        
        int expected = linked.get(0);
        assertEquals(45, expected);
    }
}
