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
public class PlayerTest {
    
    public PlayerTest() {
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
     * Test of getTeam method, of class Player.
     */
    @Test
    public void testGetTeam() {
        System.out.println("getTeam");
        Player instance = new Player();
        String expResult = "no-team";
        String result = instance.getTeam();
        assertEquals(expResult, result);
    }

    /**
     * Test of setTeam method, of class Player.
     */
    @Test
    public void testSetTeam() {
        System.out.println("setTeam");
        String newTeam = "";
        Player instance = new Player();
        instance.setTeam(newTeam);
        assertEquals("", instance.getTeam());
    }

    /**
     * Test of equals method, of class Player.
     */
    @Test
    public void testEquals() {
        System.out.println("equals");
        Object other = null;
        Player instance = new Player();
        boolean expResult = false;
        boolean result = instance.equals(other);
        assertEquals(expResult, result);
    }

    /**
     * Test of hashCode method, of class Player.
     */
    @Test
    public void testHashCode() {
        System.out.println("hashCode");
        Player instance = new Player();
        int expResult = 2064107328;
        int result = instance.hashCode();
        assertEquals(expResult, result);
    }

    /**
     * Test of clone method, of class Player.
     */
    @Test
    public void testClone() throws Exception {
        System.out.println("clone");
        Player instance = new Player();
        Object expResult = new  Player();
        Object result = instance.clone();
    }

    /**
     * Test of toString method, of class Player.
     */
    @Test
    public void testToString() {
        System.out.println("toString");
        Player instance = new Player();
        String expResult = "ID: "+ instance.getID() + "\n" + "Name: " + instance.getName() + "\n" + "Birt Date: " + instance.getBirthDate() +
                             "\n" + "Adress: " + instance.getAdress() + "\n" + "Team: " + instance.getTeam() + "\n" + "\n";
        String result = instance.toString();
    }
    
}
