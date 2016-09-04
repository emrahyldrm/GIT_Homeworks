package com.jp.tffl.TeamOperations;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author Jason
 */
public class Score2Team extends TeamOperations
{
    protected int score1;
    protected int score2;
    protected String time;
    
    
    
    public Score2Team()
    {
        super();
        this.score1 = this.score2 = -1;
    }
    
    public Score2Team(String t1, int s1, String t2, int s2, int week, String ntime)
    {
        super(t1, t2, week);
        this.score1 = s1;
        this.score2 = s2;
        this.time = ntime;

    }
    /**
     * get firts team's score
     * @return 
     */
    public int getScore1()
    {
        return this.score1;
    }
    
    
     /**
     * get second team's score
     * @return 
     */
    public int getScore2()
    {
        return this.score2;
    }
    
    
    /**
     * set first team'score
     * @param newScore 
     */
    public void setScore1(int newScore)
    {
        this.score1 = newScore;
    }
    
    
    /**
     * set first team'score
     * @param newScore 
     */
    public void setScore2(int newScore)
    {
        this.score2 = newScore;
    }
   
    
    
    
    @Override
    public boolean equals(Object member)
    {
        if(member ==null) return false;
        if(!(member instanceof Score2Team)) return false;
                
        Score2Team other = (Score2Team) member;
        return (super.equals(other) && this.score1 == other.score1 && this.score2 == other.score2);
    }

    @Override
    public int hashCode() {
        int hash = 7;
        hash = 89 * hash + this.score1;
        hash = 89 * hash + this.score2;
        return hash;
    }

    
    @Override
    public String toString()
    {
        return String.format(this.team1 + ": " + this.score1 + " <> " + this.score2 + " :" + this.team2);
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
