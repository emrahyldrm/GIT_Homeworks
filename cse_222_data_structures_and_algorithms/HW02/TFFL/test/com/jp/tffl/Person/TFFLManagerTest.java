/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.jp.tffl.Person;

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
public class TFFLManagerTest {
    
    public TFFLManagerTest() {
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
     * Test of equals method, of class TFFLManager.
     */
    @Test
    public void testEquals() {
        System.out.println("equals");
        Object other = null;
        TFFLManager instance = new TFFLManager();
        boolean expResult = false;
        boolean result = instance.equals(other);
        assertEquals(expResult, result);
    }

    /**
     * Test of toString method, of class TFFLManager.
     */
    @Test
    public void testToString() {
        System.out.println("toString");
        TFFLManager instance = new TFFLManager();
        String expResult = "ID: "+ instance.getID() + "\n" + "Name: " + instance.getName() + "\n" + "Birt Date: " + instance.getBirthDate() +
                             "\n" + "Adress: " + instance.getAdress() + "\n" + "Type: " + instance.getType() + "\n" ;
        String result = instance.toString();
        assertEquals(expResult, result);
    }

    /**
     * Test of clone method, of class TFFLManager.
     */
    @Test
    public void testClone() throws Exception {
        System.out.println("clone");
        TFFLManager instance = new TFFLManager();
        Object expResult = new TFFLManager();
        Object result = instance.clone();
        assertEquals(expResult, result);
    }

    /**
     * Test of hashCode method, of class TFFLManager.
     */
    @Test
    public void testHashCode() {
        System.out.println("hashCode");
        TFFLManager instance = new TFFLManager();
        int expResult = 7;
        int result = instance.hashCode();
        assertEquals(expResult, result);
    }
    
}
