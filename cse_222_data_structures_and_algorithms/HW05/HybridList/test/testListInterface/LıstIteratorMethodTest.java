/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package testListInterface;

import hybridListOthers.Factory;
import java.util.ConcurrentModificationException;
import java.util.ListIterator;
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
public class LıstIteratorMethodTest {
    
    public LıstIteratorMethodTest() {
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
        List<Integer> linked = Factory.factory("linked");
        ListIterator<Integer> iter = linked.listIterator();
        
        assertNotSame(null, iter);         
        System.out.println("listIterator method  not null equality test, passed\n");       
    }
    
    
    @Test
    public void listIteratorMethodTest2()
    {
        List<Integer> linked = Factory.factory("linked");
        ListIterator<Integer> iter = linked.listIterator();
        
        linked.add(5);
        linked.add(52);
        linked.add(33);
        linked.add(3);
        
        assertNotSame(false, iter.hasNext());        
        System.out.println("listIterator method  before adding hasnext test, passed\n");       
    }
    
    
    @Test
    public void listIteratorMethodTest3()
    {
        List<Integer> linked = Factory.factory("linked");
        
        linked.add(5);
        linked.add(52);
        linked.add(33);
        linked.add(3);
        ListIterator<Integer> iter = linked.listIterator();

        int a = iter.next();
        assertEquals(5, a);        
        System.out.println("listIterator method  after  adding next test, passed\n");          
    }
    
    @Test
    public void listIteratorMethodTest4()
    {
        List<Integer> linked = Factory.factory("linked");
        ListIterator<Integer> iter = linked.listIterator();
        try
        {
            linked.add(5);
            linked.add(52);
            linked.add(33);
            linked.add(3);


            int a = iter.next();
        }catch(Exception e)
        {
            if(!(e instanceof ConcurrentModificationException))
                    fail();
        }
            System.out.println("ConcurrentModificationExp has been caught, passed\n");             
}
    
}

