package com.jp.tffl.Person;

import java.util.Comparator;
import java.util.Objects;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author Jason
 */
public class Player extends PersonClass implements Comparable<Player>, Comparator<Player>
{
    protected String team;
    protected int goalCounter;
    
    
    /**
     * default constructor
     * team="no-team"
     */
    public Player ()
    {
        super();               
        this.team = "no-team";
    }
    
    public Player(String line)
    {
         if(line.length() <  5)
            return;
       
        String [] parts = line.split(";");
        this.ID = parts[0];
        this.name = parts[1];
        this.birthDate = parts[2];
        this.adress = parts[3];
        this.team = parts[4];
    }
    
    /**
     * get team name
     * @return team name
     */
    public String getTeam()
    {
        return this.team;
    }
    
    
    /**
     * setting up team name
     * @param newTeam 
     */
    public void setTeam(String newTeam)
    {
        team = newTeam;
    }
    
    public int getGoal()
    {
        return this.goalCounter;
    }
    public void goal()
    {
        this.goalCounter++;
    }
    
    /**
     * check equality
     * @param other
     * @return 
     */
    @Override 
    public boolean equals(Object other)
    {
        if(other==null) return false;
        if(!(other instanceof Player)) return false;
        
        Player player = (Player) other;
        
        return (this.name.equals(player.name) && this.ID.equals(player.ID) && 
                this.birthDate.equals(player.birthDate) && this.adress.equals(player.adress)
                && this.team.equals(player.team));
    }

    
    
    
    
    @Override
    public int hashCode() {
        int hash = 3;
        hash = 29 * hash + Objects.hashCode(this.team);
        return hash;
    }

    
    
    @Override
    public Object clone() throws CloneNotSupportedException
    {
        return super.clone();
    }
    
  
    @Override
    public String toString()
    {
         return String.format("ID: "+ this.ID + "\n" + "Name: " + this.name + "\n" + "Birt Date: " + this.birthDate +
                             "\n" + "Adress: " + this.adress + "\n" + "Team: " + this.team + "\n" + "\n" );
    }

    @Override
    public int compareTo(Player o) 
    {
        return new Integer(o.goalCounter).compareTo(this.goalCounter);
    }

    @Override
    public int compare(Player o1, Player o2) 
    {
        return new Integer(o1.goalCounter).compareTo(o2.goalCounter);
    }
}
