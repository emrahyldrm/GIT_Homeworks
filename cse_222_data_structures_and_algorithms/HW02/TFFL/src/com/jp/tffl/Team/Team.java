/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.jp.tffl.Team;

import Exceptions.BadAlloc;
import java.io.Serializable;
import java.util.Arrays;
import java.util.Comparator;
import java.util.Objects;

/**
 *
 * @author Jason
 */
public class Team implements Cloneable,Serializable,Comparable<Team>,Comparator<Team>
{
    protected String name;
    protected int year;
    protected String [] players;
    protected String presidentID;
    protected String vicePresidentID;
    protected String coachID;
    protected int game=0;
    protected int win=0;
    protected int lose=0;
    protected int draw=0;
    protected int goalsFor=0;
    protected int goalsAgainst=0;
    protected int score=0;
    protected int size;
    protected int capacity;

    public Team() 
    {
        super();
        this.name = "no-name";
        this.year = 0;
        this.size=0;
        this.capacity = 20;
        this.players = new String[capacity];
        this.score = 0;
        
    }
    

    public Team(String line) throws BadAlloc
    {
        if(line.length() < 5)
            throw new BadAlloc();
        
        String [] parts = line.split(";");
        
        this.name = parts[0];
        this.year = new Integer(parts[1]);
        this.presidentID = parts[2];
        this.vicePresidentID = parts[3];
        this.coachID = parts[4];
        this.size=0;
        this.capacity = 20;
        this.players = new String[capacity];

    }
    
    
    
    public String getName()
    {
        return name;
    }
    
    
    public int getYear()
    {
        return year;
    }
    
    
    public String getPresident() throws CloneNotSupportedException
    {
        return this.presidentID;
    }
    
    
    public String getVicePresidentId() throws CloneNotSupportedException
    {
        return this.vicePresidentID;
    }
    
    
    public String getCoachID() throws CloneNotSupportedException
    {
        return this.coachID;
    }
    
    public String [] getPlayers()
    {
        return this.players;
    }
    

    public int size()
    {
        return size;
    }
    
    
    public int capacity()
    {
        return capacity;
    }
    
    
    public int getScore()
    {
        return score;
    }
    
    
    public void setName(String newName)
    {
        this.name = newName;
    }
    
    
    public void setYear(int newYear)
    {
        this.year = newYear;
    }
    
    
    public void setPresident(String newPerson) throws CloneNotSupportedException
    {
        this.presidentID = newPerson;
    }
    
    
    public void setVicePresident(String newPerson) throws CloneNotSupportedException
    {
        this.vicePresidentID = newPerson;    
    }
    
    
    public void setCoachID (String newPerson) throws CloneNotSupportedException
    {
        this.coachID = newPerson;
    }
    
    public void setScore(int newScore)
    {
        this.score = newScore;
    }
    
    
    public boolean exist(String player)
    {
        if(player == null) return false;
        
        for (int i = 0; i < this.size; i++)
            if(this.players[i].equals(player))
                return true;
  
        return false;
    }
    
    
    
    public void addPlayer(String player)
    {
        if(this.exist(player))
            return;
        
        this.players[size] = player;
        this.size++;
    }
    
    
    
    public void removePlayer(int index)
    {   
        for (int i = index; i < this.size-1; i++) 
            this.players[i] = this.players[i+1];
        
        this.size--;
    }
    
    
    public void removePlayer(String player)
    {
        for (int i = 0; i < this.size; i++) 
            if(this.players[i].equals(player))
            {
                this.removePlayer(i);
                break;
            }
        
    }
    
    
    @Override
    public Object clone() throws CloneNotSupportedException
    {
        Team team = (Team) super.clone();

        for (int i = 0; i < this.size; i++) 
            team.players[i] = this.players[i];
        
       return team;    
    }
    
    
    @Override
    public boolean equals(Object other)
    {
        if(other == null)   return false;
        if(!(other instanceof Team))    return false;
        
        Team team = (Team) other;
        
        for (int i = 0; i < this.size; i++) {
            if(!(this.players[i].equals(team.players[i])) )
                return false;
        }
        return (this.capacity == team.capacity && this.coachID.equals(team.coachID) 
                && this.name.equals(team.name) &&  this.presidentID.equals(team.presidentID)
                && this.score == team.score && this.size == team.size && 
                this.vicePresidentID.equals(team.vicePresidentID) && this.year == team.year);
        
        
    }

    @Override
    public int hashCode() {
        int hash = 7;
        hash = 47 * hash + Objects.hashCode(this.name);
        hash = 47 * hash + this.year;
        hash = 47 * hash + Arrays.deepHashCode(this.players);
        hash = 47 * hash + Objects.hashCode(this.presidentID);
        hash = 47 * hash + Objects.hashCode(this.vicePresidentID);
        hash = 47 * hash + Objects.hashCode(this.coachID);
        hash = 47 * hash + this.score;
        hash = 47 * hash + this.size;
        hash = 47 * hash + this.capacity;
        return hash;
    }
    
    
    
    @Override
    public String toString()
    {
        String players = new String();
        
        for (int i = 0; i < this.size; i++) {
            players += this.players[i]+"\n";
        }
        
        return String.format("Name: " + this.name + "\nYear: " + this.year + "\nPresident: " +
                             this.presidentID + "\nVice President: " + 
                             this.vicePresidentID + "\nCoach: " + this.coachID + "\nScore: " + this.score + "\n" + players + "\n\n" );    
    }

    @Override
    public int compareTo(Team o)
    {
        return new Integer(o.score).compareTo(this.score);
    }

    @Override
    public int compare(Team o1, Team o2) 
    {
        return new Integer(o1.score).compareTo(o2.score);
    }

    /**
     * @return the game
     */
    public int getGame() {
        return game;
    }

    /**
     * @param game the game to set
     */
    public void setGame(int game) {
        this.game = game;
    }

    /**
     * @return the win
     */
    public int getWin() {
        return win;
    }

    /**
     * @param win the win to set
     */
    public void setWin(int win) {
        this.win = win;
    }

    /**
     * @return the lose
     */
    public int getLose() {
        return lose;
    }

    /**
     * @param lose the lose to set
     */
    public void setLose(int lose) {
        this.lose = lose;
    }

    /**
     * @return the draw
     */
    public int getDraw() {
        return draw;
    }

    /**
     * @param draw the draw to set
     */
    public void setDraw(int draw) {
        this.draw = draw;
    }
    
    
    public void win(int gfor, int against)
    {
        this.game++;
        this.score += 3;
        this.win++;
        this.goalsFor += gfor;
        this.goalsAgainst += against;
    }
    
    public void draw(int gfor, int against)
    {        
        this.game++;
        this.score += 1;
        this.draw++;  
        this.goalsFor += gfor;
        this.goalsAgainst += against;
    }
    
    public void lose(int gfor, int against)
    {
        this.game++;
        this.lose++; 
        this.goalsFor += gfor;
        this.goalsAgainst += against;
    }

    /**
     * @return the goalsFor
     */
    public int getGoalsFor() {
        return goalsFor;
    }

    /**
     * @param goalsFor the goalsFor to set
     */
    public void setGoalsFor(int goalsFor) {
        this.goalsFor = goalsFor;
    }

    /**
     * @return the goalsAgainst
     */
    public int getGoalsAgainst() {
        return goalsAgainst;
    }

    /**
     * @param goalsAgainst the goalsAgainst to set
     */
    public void setGoalsAgainst(int goalsAgainst) {
        this.goalsAgainst = goalsAgainst;
    }
}
