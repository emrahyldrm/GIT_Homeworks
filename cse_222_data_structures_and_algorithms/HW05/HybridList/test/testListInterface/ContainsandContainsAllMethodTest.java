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
public class ContainsandContainsAllMethodTest {
    
     
    public ContainsandContainsAllMethodTest() {
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
    public void containsTest1()
    {

        List<Integer> linked = Factory.factory("linked");
        List<Integer> hybrid = Factory.factory("hybrid");
        
        linked.add(53);
        linked.add(540);
        hybrid.addAll(linked);
        
        assertEquals(true, hybrid.contains(53));
        System.out.println("Contains search element test, passed\n");
        
    }
    
    @Test
    public void containsTest2()
    {
        List<Integer> linked = Factory.factory("linked");
        List<Integer> hybrid = Factory.factory("hybrid");
        
        linked.add(53);
        linked.add(540);
        hybrid.addAll(linked);
        
        assertEquals(false, hybrid.contains(null));
        System.out.println("Contains search null element test(false), passed\n");
        
    }
    
    
    @Test
    public void containsTest3()
    {
        List<Integer> linked = null;
        List<Integer> hybrid = null;
        try
        {
        linked.add(53);
        linked.add(540);
        hybrid.addAll(linked);
        }
        catch(NullPointerException e)
        {
            System.out.println("Contains search null pointer test, passed\n");
        }
    }
    
    @Test
    public void containsAllTest1()
    {
        List<Integer> linked = Factory.factory("linked");
        List<Integer> hybrid = Factory.factory("hybrid");
        
        linked.add(34);
        linked.add(45);
        hybrid.add(44);
        
        assertEquals(false, hybrid.containsAll(linked));
        System.out.println("ContainsAll search other collection elemets test(false), passed\n");     
    }
    
    
        @Test
    public void containsAllTest2()
    {
        List<Integer> linked = Factory.factory("linked");
        List<Integer> hybrid = Factory.factory("hybrid");
        
        linked.add(34);
        linked.add(45);
        hybrid.addAll(linked);
        
        assertEquals(true, hybrid.containsAll(linked));
        System.out.println("ContainsAll search other collection elemets test(true), passed\n");          
    }
}
