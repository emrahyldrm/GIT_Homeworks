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
public class TeamManagerTest {
    
    public TeamManagerTest() {
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
     * Test of getTeam method, of class TeamManager.
     */
    @Test
    public void testGetTeam() {
        System.out.println("getTeam");
        TeamManager instance = new TeamManager();
        String expResult = "no-team";
        String result = instance.getTeam();
        assertEquals(expResult, result);
    }

    /**
     * Test of setTeam method, of class TeamManager.
     */
    @Test
    public void testSetTeam() {
        System.out.println("setTeam");
        String newTeam = "new";
        TeamManager instance = new TeamManager();
        instance.setTeam(newTeam);
        assertEquals("new", instance.getTeam());
    }

    /**
     * Test of hashCode method, of class TeamManager.
     */
    @Test
    public void testHashCode() {
        System.out.println("hashCode");
        TeamManager instance = new TeamManager();
        int expResult = 2064107460;
        int result = instance.hashCode();
        assertEquals(expResult, result);
    }

    /**
     * Test of equals method, of class TeamManager.
     */
    @Test
    public void testEquals() {
        System.out.println("equals");
        Object other = null;
        TeamManager instance = new TeamManager();
        boolean expResult = false;
        boolean result = instance.equals(other);
        assertEquals(expResult, result);
    }

    /**
     * Test of clone method, of class TeamManager.
     */
    @Test
    public void testClone() throws Exception {
        System.out.println("clone");
        TeamManager instance = new TeamManager();
        Object expResult = new TeamManager();
        Object result = instance.clone();
        assertEquals(expResult, result);
    }

    /**
     * Test of toString method, of class TeamManager.
     */
    @Test
    public void testToString() {
        System.out.println("toString");
        TeamManager instance = new TeamManager();
        String expResult = "ID: "+ instance.getID() + "\n" + "Name: " + instance.getName() + "\n" + "Birt Date: " + instance.getBirthDate() +
                             "\n" + "Adress: " + instance.getAdress() + "\n" + "Team: " + instance.getTeam() + "\n" +  "Type: " + instance.getType() + "\n";
        String result = instance.toString();
        assertEquals(expResult, result);
    }
    
}
