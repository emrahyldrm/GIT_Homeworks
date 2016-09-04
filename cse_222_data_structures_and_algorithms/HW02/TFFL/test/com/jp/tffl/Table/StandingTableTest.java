/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.jp.tffl.Table;

import com.jp.tffl.Team.Team;
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
public class StandingTableTest {
    
    public StandingTableTest() {
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
     * Test of add method, of class StandingTable.
     */
    @Test
    public void testAdd() {
        System.out.println("add");
        String name = "";
        int score = 0;
        int win = 0;
        int lose = 0;
        int draw = 0;
        int gF = 0;
        int gA = 0;
        StandingTable instance = new StandingTable(0);
        instance.add(name, score, win, lose, draw, gF, gA);
        assertEquals(lose, instance.loses[0]);
    }

    /**
     * Test of exist method, of class StandingTable.
     */
    @Test
    public void testExist() {
        System.out.println("exist");
        String member = "name";
        StandingTable instance = new StandingTable(0);
        instance.add(member, 0, 0, 0, 0, 0, 0);
        boolean expResult = true;
        boolean result = instance.exist(member);
        assertEquals(expResult, result);
    }


    /**
     * Test of getTeams method, of class StandingTable.
     */
    @Test
    public void testGetTeams() {
        System.out.println("getTeams");
        StandingTable instance = new StandingTable(0);
        String[] expResult = new String[5];
        expResult[0] = "no";
        instance.add("no", 0,0,0,0,0,0);
        String[] result = instance.getTeams();
        assertEquals(expResult[0], result[0]);
    }

    /**
     * Test of getScores method, of class StandingTable.
     */
    @Test
    public void testGetScores() {
        System.out.println("getScores");
        StandingTable instance = new StandingTable(0);
        int[] expResult = new int[5];
        expResult[0] = 0;        
        int[] result = instance.getScores();
        assertEquals(expResult[0], result[0]);
    }

    /**
     * Test of getWins method, of class StandingTable.
     */
    @Test
    public void testGetWins() {
        System.out.println("getWins");
        StandingTable instance = new StandingTable(0);
        int[] expResult = new int[5];
        expResult[0] = 0;
        int[] result = instance.getWins();
        assertEquals(expResult[0], result[0]);
    }

    /**
     * Test of setWins method, of class StandingTable.
     */
    @Test
    public void testSetWins() {
        System.out.println("setWins");
        int[] wins = null;
        StandingTable instance = new StandingTable(0);
        instance.setWins(wins);
    }

    /**
     * Test of getLoses method, of class StandingTable.
     */
    @Test
    public void testGetLoses() {
        System.out.println("getLoses");
        StandingTable instance = new StandingTable(0);
        int[] expResult = new int[5];
        expResult[0] = 0;        
        int[] result = instance.getLoses();
        assertEquals(expResult[0], result[0]);
    }

    /**
     * Test of getDraws method, of class StandingTable.
     */
    @Test
    public void testGetDraws() {
        System.out.println("getDraws");
        StandingTable instance = new StandingTable(0);
        int[] expResult = new int[5];
        expResult[0] = 0;
        int[] result = instance.getDraws();
        assertEquals(expResult[0], result[0]);
    }

    /**
     * Test of getGoalsFor method, of class StandingTable.
     */
    @Test
    public void testGetGoalsFor() {
        System.out.println("getGoalsFor");
        StandingTable instance = new StandingTable(0);
        int[] expResult = new int[5];
        expResult[0] = 0;
        int[] result = instance.getGoalsFor();
        assertEquals(expResult[0], result[0]);
    }

    /**
     * Test of getGoalsAgainsts method, of class StandingTable.
     */
    @Test
    public void testGetGoalsAgainsts() {
        System.out.println("getGoalsAgainsts");
        StandingTable instance = new StandingTable(0);
        int[] expResult = new int[5];
        expResult[0] = 0;
        int[] result = instance.getGoalsAgainsts();
        assertEquals(expResult[0], result[0]);
    }
    
}
