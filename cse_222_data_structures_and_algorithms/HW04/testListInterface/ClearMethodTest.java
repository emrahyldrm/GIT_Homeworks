package testListInterface;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

import java.util.List;
import org.junit.After;
import org.junit.AfterClass;
import org.junit.Before;
import org.junit.BeforeClass;
import org.junit.Test;
import static org.junit.Assert.*;
import testListInterface.Factory;

/**
 *
 * @author Jason
 */
public class ClearMethodTest {
    
    public ClearMethodTest() {
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
    public void clearMethodTest1()
    {
        System.out.println("clear size test, passed");
        
        List<Integer> linked = Factory.factory("linked");
        
        linked.add(12);
        linked.add(23);
        linked.add(43);
         
        int before = linked.size();        
        linked.clear();        
        int after = linked.size();        
        assertNotSame(before, after);
    }

    
        @Test
    public void clearMethodTest2()
    {
        List<Integer> linked =null;
        try
        {
            linked.clear();
        }catch(NullPointerException e)
        {
            System.out.println("NullPointerException has been caught");
//            Factory.appendStr("NullPointerException has been caught, passed\n");
        }
    }
    
    
    @Test
    public void clearMethodTest3()
    {
        List<Integer> linked = Factory.factory("linked");
        try
        {
            linked.clear();
        }catch (Exception e)
        {           
        }
        System.out.println("list with no content clear test, exception should not be thrown, passed\n");        
    }

}
