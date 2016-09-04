package testListInterface;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

import java.util.List;
import jdk.nashorn.internal.ir.ContinueNode;
import jdk.nashorn.internal.runtime.regexp.JoniRegExp;
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
public class AddMethodTest {
    
    public AddMethodTest() {
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

    /**
     *
     */
    @Test
    public void testAdd1()
    {
       System.out.println("Test size function, expected size 3 ");
       List<Integer> temp = Factory.factory("array");       
       temp.add(12);
       temp.add(34);
       temp.add(4565);       
       assertEquals(3, temp.size());
       
    }
    
    @Test
    public void testAdd2()
    {
       System.out.println("NULL POINTER EXCEPTION TEST ");
       List<Integer> temp =null;
       try
       {
            System.out.println(temp.get(1).toString());
       }catch (Exception e)
       {
           System.err.println(e.toString());
         if(!(e instanceof NullPointerException))
              fail("Expected exception was NULL POINTER EXCEPTION");
               
       }       
    }
    
    
    @Test
    public void testAdd3()
    {
       System.out.println("Add method elemet equality test");
       List<Integer> temp =Factory.factory("linked");
      
        temp.add(23);
        temp.add(12);    
        
        int expected = temp.get(1);
        assertEquals(12, expected);
    }
    
    
    @Test
    public void testAdd4()
    {
       System.out.println("Add element control ");
       List<Integer> temp =Factory.factory("linked");
      
        temp.add(233);
        temp.add(123); 
        boolean expected = temp.contains(123);
        
        assertEquals(true, expected);
    }
    
    @Test
    public void testAdd5()
    {
       System.out.println("Add function return value test ");
       List<Integer> temp =Factory.factory("array");
       try
       {
       temp.add(12,12);
       }catch(IndexOutOfBoundsException e)
       {
           System.out.println("IndexOutOfBoundException has been caught");
       }
    }
}
