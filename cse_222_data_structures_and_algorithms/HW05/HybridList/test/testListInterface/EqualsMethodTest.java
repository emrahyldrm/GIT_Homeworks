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


    
    // BU TESTIN ILK HALI HATALI OLDUGUNDAN BU HALINI TEST EDEMEDIM
    
    @Test
    public void equalsTest1()
    {
        List<Integer> linked = Factory.factory("linked");
        List<Integer> hybrid = Factory.factory("hybrid");
        
        assertEquals(true, linked.equals(hybrid));
        System.out.println("Two empty collections equality test(true), passed\n");             
    }
    
    
    
    @Test
    public void equalsTest2()
    {
        List<Integer> linked = Factory.factory("linked");
        List<Integer> hybrid = Factory.factory("hybrid");
        
        hybrid.add(34);
        assertEquals(false, linked.equals(hybrid));
        System.out.println("Two empty collections equality test(false), passed\n");             
    }
    
    
    
    @Test
    public void equalsTest3()
    {
        List<Integer> linked = Factory.factory("linked");
        List<Integer> hybrid = Factory.factory("hybrid");
        
        hybrid.add(34);
        linked.add(34);
        assertEquals(true, linked.equals(hybrid));
        System.out.println("Two not empty collections equality test(true), passed\n");              
    }
    
    
    @Test
    public void equalsTest4()
    {
        List<Integer> linked = Factory.factory("linked");
        List<Integer> hybrid = Factory.factory("hybrid");
        
        hybrid.add(34);
        linked.add(34);
        
        System.err.println("Bu test normalde dogru olarak sonuc verir \n"
                          +"ancak bizim listimizin içeriği farklı olduğu için \n "
                          +"burda doğal olarak yanlış sonuc vermiştir.");

        assertEquals(true, linked.equals(hybrid) && hybrid.equals(linked));
        System.out.println("Two not empty collections equality test(true), passed\n");

    }
    
    
    @Test
    public void equalsTest5()
    {
        List<Integer> linked = Factory.factory("linked");
        List<Integer> hybrid = Factory.factory("hybrid");
        
        hybrid.add(34);
        linked.add(34);
        linked.remove(new Integer(34));
        assertEquals(false, linked.equals(hybrid) && hybrid.equals(linked));
        System.out.println("After add and remove equality test(true), passed\n");                              
    }
}