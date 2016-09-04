/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.jp.tffl.TeamOperations;

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
public class Schedule2TeamTest {
    
    public Schedule2TeamTest() {
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
     * Test of equals method, of class Schedule2Team.
     */
    @Test
    public void testEquals() {
        System.out.println("equals");
        Object other = null;
        Schedule2Team instance = new Schedule2Team();
        boolean expResult = false;
        boolean result = instance.equals(other);
        assertEquals(expResult, result);
    }

    /**
     * Test of hashCode method, of class Schedule2Team.
     */
    @Test
    public void testHashCode() {
        System.out.println("hashCode");
        Schedule2Team instance = new Schedule2Team();
        Schedule2Team other = new Schedule2Team();
        int expResult = other.hashCode();
        int result = instance.hashCode();
        assertEquals(expResult, result);
    }



    /**
     * Test of toString method, of class Schedule2Team.
     */
    @Test
    public void testToString() {
        System.out.println("toString");
        Schedule2Team instance = new Schedule2Team();
        String expResult = instance.getTime() + " : " + " " + instance.team1 + " - " + instance.team2 + "\n";
        String result = instance.toString();
        assertEquals(expResult, result);
    }

    /**
     * Test of getTime method, of class Schedule2Team.
     */
    @Test
    public void testGetTime() {
        System.out.println("getTime");
        Schedule2Team instance = new Schedule2Team();
        String expResult = "00.00";
        String result = instance.getTime();
        assertEquals(expResult, result);
    }

    /**
     * Test of setTime method, of class Schedule2Team.
     */
    @Test
    public void testSetTime() {
        System.out.println("setTime");
        String time = "";
        Schedule2Team instance = new Schedule2Team();
        instance.setTime(time);
    }
    
}
