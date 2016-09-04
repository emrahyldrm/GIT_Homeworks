package com.jp.tffl.TeamOperations;

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
public class Schedule2Team extends TeamOperations
{
    protected String time;
    
    
    public Schedule2Team()
    {
        super();
        time = "00.00";
    }
    
    public Schedule2Team(String t1, String t2, int week, String tm)
    {
        super(t1, t2, week);
        this.time = tm;
    }
    
    
    @Override
    public boolean equals(Object other)
    {
        if(other==null)  return false;
        if(!(other instanceof Schedule2Team)) return false;
        
        Schedule2Team schedule = (Schedule2Team) other;
        return (super.equals(schedule) && this.getTime().equals(schedule.getTime()));
    }

    @Override
    public int hashCode() {
        int hash = 7;
        hash = 31 * hash + Objects.hashCode(this.getTime());
        return hash;
    }

    

    
    @Override
    public String toString() 
    {
        return String.format(getTime() + " : " + " " + this.team1 + " - " + team2 + "\n");
    }

    /**
     * @return the time
     */
    public String getTime() {
        return time;
    }

    /**
     * @param time the time to set
     */
    public void setTime(String time) {
        this.time = time;
    }
    
    
  
}
