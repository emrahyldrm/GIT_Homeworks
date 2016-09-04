/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package testListInterface;

import hybridListOthers.Factory;
import java.util.ConcurrentModificationException;
import java.util.Iterator;
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
public class IteratorMethodTest {
    
    public IteratorMethodTest() {
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
    public void iteratorMethodTest1()
    {
        List<Integer> hybrid = Factory.factory("hybrid");
        Iterator<Integer> iter = hybrid.iterator();
        
        assertNotSame(null, iter);   
        System.out.println("iterator method  not null equality test, passed\n");             
    }
    
    
    @Test
    public void iteratorMethodTest2()
    {
        List<Integer> hybrid = Factory.factory("linked");
        Iterator<Integer> iter = hybrid.iterator();
        
        hybrid.add(5);
        hybrid.add(52);
        hybrid.add(33);
        hybrid.add(3);
        

        assertNotSame(false, iter.hasNext());        
        System.out.println("iterator method  before adding equality test, passed\n");             
    }
    
    
    @Test
    public void iteratorMethodTest3()
    {
        List<Integer> hybrid = Factory.factory("hybrid");
        
        hybrid.add(5);
        hybrid.add(52);
        hybrid.add(33);
        hybrid.add(3);
        Iterator<Integer> iter = hybrid.iterator();

        int a = iter.next();
        assertEquals(5, a);  
        System.out.println("iterator method  after adding equality test, passed\n");                     
    }
    
    @Test
    public void iteratorMethodTest4()
    {
        List<Integer> hybrid = Factory.factory("linked");
        Iterator<Integer> iter = hybrid.iterator();
        try
        {
            hybrid.add(5);
            hybrid.add(52);
            hybrid.add(33);
            hybrid.add(3);


            int a = iter.next();
        }catch(Exception e)
        {
            System.out.println("asad"  + e.toString());
            if(!(e instanceof ConcurrentModificationException))
                    fail();
        }
        System.out.println("ConcurrentModificationExp has been caught, passed\n");             

    }
}
