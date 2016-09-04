/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package testListInterface;

import hybridListOthers.Factory;
import java.util.ConcurrentModificationException;
import java.util.List;
import java.util.ListIterator;
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
public class ListIteratorWithIndexMethodTest {
    
    public ListIteratorWithIndexMethodTest() {
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
    public void listIteratorMethodTest1()
    {
        List<Integer> hybrid = Factory.factory("hybrid");
        ListIterator<Integer> iter = hybrid.listIterator(0);
        
        assertNotSame(null, iter);         
        System.out.println("listIterator method  not null equality test, passed\n");        
    }
    
    
    @Test
    public void listIteratorMethodTest2()
    {
        List<Integer> hybrid = Factory.factory("hybrid");
        ListIterator<Integer> iter = hybrid.listIterator(0);
       
        hybrid.add(5);
        hybrid.add(52);
        hybrid.add(33);
        hybrid.add(3);
    

        assertNotSame(false, iter.hasNext());          
        System.out.println("listIterator method  before adding hasnext test, passed\n");      
    }
    
    
    @Test
    public void listIteratorMethodTest3()
    {
        List<Integer> hybrid = Factory.factory("hybrid");
        
        hybrid.add(5);
        hybrid.add(52);
        hybrid.add(33);
        hybrid.add(3);
        ListIterator<Integer> iter = hybrid.listIterator(2);

        int a = iter.next();
        assertEquals(33, a);    
        System.out.println("listIterator method  after  adding next test, passed\n");        
    }
    
    @Test
    public void listIteratorMethodTest4()
    {
        List<Integer> hybrid = Factory.factory("hybrid");

        try
        {
            hybrid.add(5);
            hybrid.add(52);
            hybrid.add(33);
            hybrid.add(3);

        ListIterator<Integer> iter = hybrid.listIterator(9);
            int a = iter.next();
        }catch(Exception e)
        {
            if(!(e instanceof IndexOutOfBoundsException))
                    fail();
        }
            System.out.println("ConcurrentModificationExp has been caught, passed\n");             
 }
    
    
    
 
}
