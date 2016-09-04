package com.jp.tffl.TeamOperations;

import com.jp.tffl.Team.Team;
import java.io.Serializable;
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
public abstract class TeamOperations implements Cloneable,Serializable
{
    protected String team1;
    protected String team2;
    protected int weekNumber;
    
    
    /**
     * default constructor
     */
    public TeamOperations()
    {
        weekNumber = 0;
    }
    
    
    public TeamOperations(String t1, String t2, int week)
    {
        this.team1 = t1;
        this.team2 = t2;
        this.weekNumber = week;
    }
    
    /**
     * get first team
     * @return team 1
     * @throws java.lang.CloneNotSupportedException
     */
    public String getTeam1() throws CloneNotSupportedException
    {
        return this.team1;
    }
    
    
    /**
     * get second team
     * @return team 2
     * @throws java.lang.CloneNotSupportedException
     */
    public String getTeam2() throws CloneNotSupportedException 
    {
        return  this.team2;
    }
    
    
    /**
     * get current week number
     * @return 
     */
    public int getWeekNumber()
    {
        return this.weekNumber;
    }
    
    
    /**
     * set team 1
     * @param newTeam 
     * @throws java.lang.CloneNotSupportedException 
     */
    public void setTeam1(String newTeam) throws CloneNotSupportedException
    {
        this.team1 = newTeam;
    }
    
    
    /**
     * set team 2
     * @param newTeam 
     * @throws java.lang.CloneNotSupportedException 
     */
    public void setTeam2(String newTeam) throws CloneNotSupportedException
    {
        this.team2 = newTeam;
    }
    
    
    /**
     * set current week number
     * @param newNumber 
     */
    public void setWeekNumber(int newNumber)
    {
        this.weekNumber = newNumber;
    }
    
 

    
    @Override
    public boolean equals(Object other)
    {
        if(other == null)   return false;
        if(!(other instanceof TeamOperations)) return false;
        
        TeamOperations teamOp = (TeamOperations) other;
        return (this.team1.equals(teamOp.team1) && this.team2.equals(teamOp.team2) && this.weekNumber == teamOp.weekNumber);
        
    }

    @Override
    public int hashCode() {
        int hash = 7;
        hash = 89 * hash + Objects.hashCode(this.team1);
        hash = 89 * hash + Objects.hashCode(this.team2);
        hash = 89 * hash + this.weekNumber;
        return hash;
    }
    

    
    @Override
    public abstract String toString();
     
}
