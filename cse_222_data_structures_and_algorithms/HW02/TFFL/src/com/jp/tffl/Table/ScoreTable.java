/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.jp.tffl.Table;

import com.jp.tffl.TeamOperations.Score2Team;
import com.jp.tffl.TeamOperations.TeamOperations;

/**
 *
 * @author Jason
 */
public class ScoreTable extends Table
{
    protected Score2Team [] teamScores;
    protected int weekNumber;
    
    
    
    private void realloc()
    {
        this.capacity = this.capacity + 20;
        Score2Team [] temp = this.teamScores;
        
        this.teamScores = new Score2Team[this.capacity];
        
        for (int i = 0; i < this.size; i++)
            this.teamScores[i] = temp[i];
       
    }
        
    public ScoreTable()
    {
        super();
        this.teamScores = new Score2Team[this.capacity];    
    }
    
    
    public void addScore(Score2Team newScore) throws CloneNotSupportedException
    {
        if(this.size == this.capacity)
            this.realloc();
        
        if(this.exist(newScore) || newScore == null)
            return;
        
        this.teamScores[size] = (Score2Team) newScore;
        this.size++;
    }
    
    
    public void removeScore(int index) throws ArrayIndexOutOfBoundsException
    {        
        if(index > this.size) 
            throw new ArrayIndexOutOfBoundsException();
        
        for (int i = index; i < size-1; i++) 
            this.teamScores[i] = this.teamScores[i+1];
        
        this.size--;
    }

       public void removeAll()
    {
        this.teamScores = null;
        this.size = 0;
        this.teamScores = new Score2Team[this.capacity];
    
    }
       public Score2Team get(int i) throws CloneNotSupportedException
       {
           return (Score2Team)this.teamScores[i];
       }
    
    public boolean exist(TeamOperations member) throws CloneNotSupportedException
    {
        if(member == null)  return false;
        if(!(member instanceof Score2Team)) return false;
        
        Score2Team search = (Score2Team)member;
        
        for (int i = 0; i < size; i++)
            if(this.teamScores[i].equals(search))
                return true;
        
        return false;
    }
    
    
    @Override
    public Object clone() throws CloneNotSupportedException
    {
        ScoreTable table = (ScoreTable) super.clone();        
        table.teamScores = (Score2Team[])this.teamScores.clone();
        for (int i = 0; i < this.size(); i++)
            table.teamScores[i] = (Score2Team) this.teamScores[i];
        
        return table;
    }

    @Override
    public String [] printTable()
    {
        String [] str = new String[this.size];
        
        for (int i = 0; i < this.size; i++) 
           str[i]= (this.teamScores[i].toString());
        
        return str;
    }

    /**
     * @return the weekNumber
     */
    @Override
    public int getWeekNumber() {
        return weekNumber;
    }

    /**
     * @param weekNumber the weekNumber to set
     */
    @Override
    public void setWeekNumber(int weekNumber) {
        this.weekNumber = weekNumber;
    }
}
