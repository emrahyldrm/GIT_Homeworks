/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.jp.tffl.Table;

import com.jp.tffl.Team.Team;
import com.jp.tffl.TeamOperations.TeamOperations;

/**
 *
 * @author Jason
 */
public class StandingTable extends Table
{
    protected String [] teams;
    protected int [] scores;
    protected int [] wins;
    protected int [] loses;
    protected int [] draws;
    protected int [] goalsFor;
    protected int [] goalsAgainsts;
    
    private void realloc()
    {
        this.capacity = this.capacity + 20;
        String [] temp = this.getTeams();
        
        this.teams = new String[this.capacity];
        
        for (int i = 0; i < this.size; i++)
            this.teams[i] = temp[i];
       
    }
    
    public StandingTable(int week)
    {
        super();
        this.teams = new String[this.capacity];
        this.scores = new int[this.capacity];
        this.wins = new int[this.capacity];
        this.loses = new int[this.capacity];
        this.draws = new int[this.capacity];
        this.goalsFor = new int[this.capacity];
        this.goalsAgainsts = new int[this.capacity];
        this.weekNumber = week;


    }
    

    public void add(String name, int score, int win, int lose, int draw, int gF, int gA)
    {
        this.teams[size] = name;
        this.scores[size] = score;
        this.getWins()[size] = win;
        this.loses[size] = lose;
        this.draws[size] = draw;
        this.goalsFor[size] = gF;
        this.goalsAgainsts[size] = gA;
        this.size++;
    
    }
    
    
    public boolean exist(String member) 
    {
        if(member == null)  return false;        
        for (int i = 0; i < size; i++)
            if(this.getTeams()[i].equals(member))
                return true;
        
        return false;
    }

    
    @Override
    public Object clone() throws CloneNotSupportedException
    {
        return super.clone();
    }
    
    
    @Override
    public String [] printTable() 
    {
        String [] str = new String[this.size];
        
        for (int i = 0; i < this.size(); i++)
            str[i] = (this.getTeams()[i] + "    " + this.weekNumber+ "    " + this.getScores()[i]+"\n");
        
        return str;
    }

    /**
     * @return the teams
     */
    public String[] getTeams() {
        return teams;
    }

    /**
     * @return the scores
     */
    public int[] getScores() {
        return scores;
    }

    /**
     * @return the wins
     */
    public int[] getWins() {
        return wins;
    }

    /**
     * @param wins the wins to set
     */
    public void setWins(int[] wins) {
        this.wins = wins;
    }

    /**
     * @return the loses
     */
    public int[] getLoses() {
        return loses;
    }

    /**
     * @return the draws
     */
    public int[] getDraws() {
        return draws;
    }

    /**
     * @return the goalsFor
     */
    public int[] getGoalsFor() {
        return goalsFor;
    }

    /**
     * @return the goalsAgainsts
     */
    public int[] getGoalsAgainsts() {
        return goalsAgainsts;
    }
    
}
