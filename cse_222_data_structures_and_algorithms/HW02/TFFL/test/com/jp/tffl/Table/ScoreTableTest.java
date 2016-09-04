/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.jp.tffl.Table;

import com.jp.tffl.TeamOperations.Schedule2Team;
import com.jp.tffl.TeamOperations.Score2Team;
import com.jp.tffl.TeamOperations.TeamOperations;
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
public class ScoreTableTest {
    
    public ScoreTableTest() {
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
     * Test of addScore method, of class ScoreTable.
     */
    @Test
    public void testAddScore() throws Exception {
        System.out.println("addScore");
        Score2Team newScore = new Score2Team("no", 0, "no", 0, 0, "00.00");
        ScoreTable instance = new ScoreTable();
        instance.addScore(newScore);
        assertEquals(0, instance.getWeekNumber());
    }

    /**
     * Test of removeScore method, of class ScoreTable.
     */
    @Test
    public void testRemoveScore() throws CloneNotSupportedException {
        System.out.println("removeScore");
        int index = 0;
        ScoreTable instance = new ScoreTable();
        instance.addScore(new Score2Team());
        instance.removeScore(0);
        assertEquals(0, instance.size());
    }




    /**
     * Test of getWeekNumber method, of class ScoreTable.
     */
    @Test
    public void testGetWeekNumber() {
        System.out.println("getWeekNumber");
        ScoreTable instance = new ScoreTable();
        int expResult = 0;
        int result = instance.getWeekNumber();
        assertEquals(expResult, result);
    }

    /**
     * Test of setWeekNumber method, of class ScoreTable.
     */
    @Test
    public void testSetWeekNumber() {
        System.out.println("setWeekNumber");
        int weekNumber = 0;
        ScoreTable instance = new ScoreTable();
        instance.setWeekNumber(weekNumber); 
        int result = instance.getWeekNumber();
        assertEquals(0, result);
        
    }
    
}
