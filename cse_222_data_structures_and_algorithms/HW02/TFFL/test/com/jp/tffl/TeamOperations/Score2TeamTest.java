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
public class Score2TeamTest {
    
    public Score2TeamTest() {
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
     * Test of getScore1 method, of class Score2Team.
     */
    @Test
    public void testGetScore1() {
        System.out.println("getScore1");
        Score2Team instance = new Score2Team("",1,"",1,0,"");
        int expResult = 1 ;
        int result = instance.getScore1();
        assertEquals(expResult, result);
    }

    /**
     * Test of getScore2 method, of class Score2Team.
     */
    @Test
    public void testGetScore2() {
        System.out.println("getScore2");
        Score2Team instance = new Score2Team("",12,"",10,0,"");
        int expResult = 10;
        int result = instance.getScore2();
        assertEquals(expResult, result);
    }

    /**
     * Test of setScore1 method, of class Score2Team.
     */
    @Test
    public void testSetScore1() {
        System.out.println("setScore1");
        int newScore = 4;
        Score2Team instance = new Score2Team();
        instance.setScore1(newScore);
    }

    /**
     * Test of setScore2 method, of class Score2Team.
     */
    @Test
    public void testSetScore2() {
        System.out.println("setScore2");
        int newScore = 0;
        Score2Team instance = new Score2Team();
        instance.setScore2(newScore);
    }

    /**
     * Test of equals method, of class Score2Team.
     */
    @Test
    public void testEquals() {
        System.out.println("equals");
        Object member = null;
        Score2Team instance = new Score2Team();
        boolean expResult = false;
        boolean result = instance.equals(member);
        assertEquals(expResult, result);
    }

    /**
     * Test of hashCode method, of class Score2Team.
     */
    @Test
    public void testHashCode() {
        System.out.println("hashCode");
        Score2Team instance = new Score2Team();
        int expResult = 55357;
        int result = instance.hashCode();
        assertEquals(expResult, result);
    }



    /**
     * Test of toString method, of class Score2Team.
     */
    @Test
    public void testToString() {
        System.out.println("toString");
        Score2Team instance = new Score2Team("", 1, "", 1, 1,"");
        String expResult = instance.team1 + ": " + instance.score1 + " <> " + instance.score2 + " :" + instance.team2;
        String result = instance.toString();
        assertEquals(expResult, result);
    }

    /**
     * Test of getTime method, of class Score2Team.
     */
    @Test
    public void testGetTime() {
        System.out.println("getTime");
        Score2Team instance = new Score2Team("", 1, "", 1, 1,"10.00");
        String expResult = "10.00";
        String result = instance.getTime();
        assertEquals(expResult, result);
    }

    /**
     * Test of setTime method, of class Score2Team.
     */
    @Test
    public void testSetTime() {
        System.out.println("setTime");
        String time = "10.11";
        Score2Team instance = new Score2Team();
        instance.setTime(time);
        assertEquals(instance.getTime(), time);
    }
    
}
