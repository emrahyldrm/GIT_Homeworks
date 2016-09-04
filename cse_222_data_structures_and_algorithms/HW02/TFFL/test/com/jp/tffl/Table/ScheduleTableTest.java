/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.jp.tffl.Table;

import com.jp.tffl.TeamOperations.Schedule2Team;
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
public class ScheduleTableTest {
    
    public ScheduleTableTest() {
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
     * Test of addSchedule method, of class ScheduleTable.
     */
    @Test
    public void testAddSchedule() throws Exception {
        System.out.println("addSchedule");
        Schedule2Team schedule = new Schedule2Team();
        ScheduleTable instance = new ScheduleTable();
        instance.addSchedule(schedule);
        assertEquals(1, instance.size);
    }

    /**
     * Test of removeSchedule method, of class ScheduleTable.
     */
    @Test
    public void testRemoveSchedule() throws CloneNotSupportedException {
        System.out.println("removeSchedule");
        int index = 0;
        ScheduleTable instance = new ScheduleTable();
        Schedule2Team schedule = new Schedule2Team();
        instance.addSchedule(schedule);
        instance.removeSchedule(index);
        assertEquals(0, instance.size);
    }

    /**
     * Test of removeAll method, of class ScheduleTable.
     */
    @Test
    public void testRemoveAll() {
        System.out.println("removeAll");
        ScheduleTable instance = new ScheduleTable();
        instance.removeAll();
        assertEquals(0, instance.size);

    }
    
}
