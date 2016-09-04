/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.jp.tffl.Team;

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
public class TeamTest {
    
    public TeamTest() {
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
     * Test of getName method, of class Team.
     */
    @Test
    public void testGetName() {
        System.out.println("getName");
        Team instance = new Team();
        String expResult = "no-name";
        String result = instance.getName();
        assertEquals(expResult, result);
    }

    /**
     * Test of getYear method, of class Team.
     */
    @Test
    public void testGetYear() {
        System.out.println("getYear");
        Team instance = new Team();
        int expResult = 0;
        int result = instance.getYear();
        assertEquals(expResult, result);
    }

    /**
     * Test of getPresident method, of class Team.
     */
    @Test
    public void testGetPresident() throws Exception {
        System.out.println("getPresident");
        Team instance = new Team();
        String expResult = null;
        String result = instance.getPresident();
        assertEquals(expResult, result);
    }

    /**
     * Test of getVicePresidentId method, of class Team.
     */
    @Test
    public void testGetVicePresidentId() throws Exception {
        System.out.println("getVicePresidentId");
        Team instance = new Team();
        String expResult = null;
        String result = instance.getVicePresidentId();
        assertEquals(expResult, result);
    }

    /**
     * Test of getCoachID method, of class Team.
     */
    @Test
    public void testGetCoachID() throws Exception {
        System.out.println("getCoachID");
        Team instance = new Team();
        String expResult = null;
        String result = instance.getCoachID();
        assertEquals(expResult, result);
    }

    /**
     * Test of getPlayers method, of class Team.
     */
    @Test
    public void testGetPlayers() {
        System.out.println("getPlayers");
        Team instance = new Team();
        String[] expResult = new String[instance.capacity];
        String[] result = instance.getPlayers();
        assertArrayEquals(expResult, result);
    }

    /**
     * Test of size method, of class Team.
     */
    @Test
    public void testSize() {
        System.out.println("size");
        Team instance = new Team();
        int expResult = 0;
        int result = instance.size();
        assertEquals(expResult, result);
    }

    /**
     * Test of capacity method, of class Team.
     */
    @Test
    public void testCapacity() {
        System.out.println("capacity");
        Team instance = new Team();
        int expResult = 20;
        int result = instance.capacity();
        assertEquals(expResult, result);
    }

    /**
     * Test of getScore method, of class Team.
     */
    @Test
    public void testGetScore() {
        System.out.println("getScore");
        Team instance = new Team();
        int expResult = 0;
        int result = instance.getScore();
        assertEquals(expResult, result);
    }



    /**
     * Test of setPresident method, of class Team.
     */
    @Test
    public void testSetPresident() throws Exception {
        System.out.println("setPresident");
        String newPerson = "";
        Team instance = new Team();
        instance.setPresident(newPerson);
        assertEquals(instance.getPresident(), "");
    }

    /**
     * Test of setVicePresident method, of class Team.
     */
    @Test
    public void testSetVicePresident() throws Exception {
        System.out.println("setVicePresident");
        String newPerson = "";
        Team instance = new Team();
        instance.setVicePresident(newPerson);
        assertEquals(instance.getVicePresidentId(), "");

    }

    /**
     * Test of setCoachID method, of class Team.
     */
    @Test
    public void testSetCoachID() throws Exception {
        System.out.println("setCoachID");
        String newPerson = "";
        Team instance = new Team();
        instance.setCoachID(newPerson);        
        assertEquals(instance.getCoachID(), "");

    }

    /**
     * Test of setScore method, of class Team.
     */
    @Test
    public void testSetScore() {
        System.out.println("setScore");
        int newScore = 0;
        Team instance = new Team();
        instance.setScore(newScore);
        assertEquals(instance.getScore(), 0);
    }

    /**
     * Test of exist method, of class Team.
     */
    @Test
    public void testExist() {
        System.out.println("exist");
        String player = "";
        Team instance = new Team();
        boolean expResult = false;
        boolean result = instance.exist(player);
        assertEquals(expResult, result);
    }

    /**
     * Test of addPlayer method, of class Team.
     */
    @Test
    public void testAddPlayer() {
        System.out.println("addPlayer");
        String player = "";
        Team instance = new Team();
        instance.addPlayer(player);
        boolean expected = true;
        assertEquals(instance.exist(player), expected);
    }

    /**
     * Test of removePlayer method, of class Team.
     */
    @Test
    public void testRemovePlayer_int() {
        System.out.println("removePlayer");
        int index = 0;
        Team instance = new Team();
        instance.addPlayer("add");
        int size = instance.size();
        instance.removePlayer(index);
        assertEquals(instance.size(), size-1);
    }

    /**
     * Test of removePlayer method, of class Team.
     */
    @Test
    public void testRemovePlayer_String() {
        System.out.println("removePlayer");
        String player = "";
        Team instance = new Team();
        instance.addPlayer(player);
        boolean before = instance.exist(player);
        instance.removePlayer(player);
        boolean after = instance.exist(player);

        assertEquals(before, !after);
    }


    /**
     * Test of equals method, of class Team.
     */
    @Test
    public void testEquals() {
        System.out.println("equals");
        Object other = null;
        Team instance = new Team();
        boolean expResult = false;
        boolean result = instance.equals(other);
        assertEquals(expResult, result);
    }


    /**
     * Test of toString method, of class Team.
     */
    @Test
    public void testToString() {
        System.out.println("toString");
        Team instance = new Team();
        String players = new String();
        
        for (int i = 0; i < instance.size; i++)
            players += instance.players[i]+"\n";
            
        String expResult = "Name: " + instance.name + "\nYear: " + instance.year + "\nPresident: " +
                             instance.presidentID + "\nVice President: " + 
                             instance.vicePresidentID + "\nCoach: " + instance.coachID + "\nScore: " + instance.score + "\n" + instance.players + "\n\n";    
        String result = instance.toString();
        assertEquals(expResult, result);
    }

    /**
     * Test of compareTo method, of class Team.
     */
    @Test
    public void testCompareTo() {
        System.out.println("compareTo");
        Team o = new Team();
        Team instance = new Team();
        int expResult = 0;
        int result = instance.compareTo(o);
        assertEquals(expResult, result);
    }

    /**
     * Test of compare method, of class Team.
     */
    @Test
    public void testCompare() {
        System.out.println("compare");
        Team o1 = new Team();
        Team o2 = new Team();
        Team instance = new Team();
        int expResult = 0;
        int result = instance.compare(o1, o2);
        assertEquals(expResult, result);
    }

    /**
     * Test of getGame method, of class Team.
     */
    @Test
    public void testGetGame() {
        System.out.println("getGame");
        Team instance = new Team();
        int expResult = 0;
        int result = instance.getGame();
        assertEquals(expResult, result);
    }



    /**
     * Test of getWin method, of class Team.
     */
    @Test
    public void testGetWin() {
        System.out.println("getWin");
        Team instance = new Team();
        int expResult = 0;
        int result = instance.getWin();
        assertEquals(expResult, result);
    }

    /**
     * Test of setWin method, of class Team.
     */
    @Test
    public void testSetWin() {
        System.out.println("setWin");
        int win = 0;
        Team instance = new Team();
        instance.setWin(win);
    }

    /**
     * Test of getLose method, of class Team.
     */
    @Test
    public void testGetLose() {
        System.out.println("getLose");
        Team instance = new Team();
        int expResult = 0;
        int result = instance.getLose();
        assertEquals(expResult, result);
    }
    /**
     * Test of setLose method, of class Team.
     */
    @Test
    public void testSetLose() {
        System.out.println("setLose");
        int lose = 0;
        Team instance = new Team();
        instance.setLose(lose);
    }

    /**
     * Test of getDraw method, of class Team.
     */
    @Test
    public void testGetDraw() {
        System.out.println("getDraw");
        Team instance = new Team();
        int expResult = 0;
        int result = instance.getDraw();
        assertEquals(expResult, result);
    }

    /**
     * Test of setDraw method, of class Team.
     */
    @Test
    public void testSetDraw() {
        System.out.println("setDraw");
        int draw = 0;
        Team instance = new Team();
        instance.setDraw(draw);
    }

    /**
     * Test of win method, of class Team.
     */
    @Test
    public void testWin() {
        System.out.println("win");
        int gfor = 0;
        int against = 0;
        Team instance = new Team();
        instance.win(gfor, against);
    }

    /**
     * Test of draw method, of class Team.
     */
    @Test
    public void testDraw() {
        System.out.println("draw");
        int gfor = 0;
        int against = 0;
        Team instance = new Team();
        instance.draw(gfor, against);
    }

    /**
     * Test of lose method, of class Team.
     */
    @Test
    public void testLose() {
        System.out.println("lose");
        int gfor = 0;
        int against = 0;
        Team instance = new Team();
        instance.lose(gfor, against);
    }

    /**
     * Test of getGoalsFor method, of class Team.
     */
    @Test
    public void testGetGoalsFor() {
        System.out.println("getGoalsFor");
        Team instance = new Team();
        int expResult = 0;
        int result = instance.getGoalsFor();
        assertEquals(expResult, result);
    }

    /**
     * Test of setGoalsFor method, of class Team.
     */
    @Test
    public void testSetGoalsFor() {
        System.out.println("setGoalsFor");
        int goalsFor = 0;
        Team instance = new Team();
        instance.setGoalsFor(goalsFor);
    }

    /**
     * Test of getGoalsAgainst method, of class Team.
     */
    @Test
    public void testGetGoalsAgainst() {
        System.out.println("getGoalsAgainst");
        Team instance = new Team();
        int expResult = 0;
        int result = instance.getGoalsAgainst();
        assertEquals(expResult, result);
    }

    /**
     * Test of setGoalsAgainst method, of class Team.
     */
    @Test
    public void testSetGoalsAgainst() {
        System.out.println("setGoalsAgainst");
        int goalsAgainst = 0;
        Team instance = new Team();
        instance.setGoalsAgainst(goalsAgainst);
    }
    
}
