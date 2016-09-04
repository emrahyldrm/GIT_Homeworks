/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.jp.tffl.Table;

import com.jp.tffl.TeamOperations.Schedule2Team;
import com.jp.tffl.TeamOperations.TeamOperations;

/**
 *
 * @author Jason
 */
public class ScheduleTable extends Table
{
    protected Schedule2Team [] teamSchedules;

    
    
    private void realloc()
    {
        this.capacity = this.capacity + 20;
        Schedule2Team [] temp = this.teamSchedules;
        
        this.teamSchedules = new Schedule2Team[this.capacity];
        
        for (int i = 0; i < this.size; i++)
            this.teamSchedules[i] = temp[i];
       
    }
    
    public ScheduleTable() 
    {
        super();
        teamSchedules = new Schedule2Team[this.capacity];
    }
    
    public void addSchedule(Schedule2Team schedule) throws CloneNotSupportedException
    {
        if(this.size == this.capacity)
            this.realloc();
        
        if(schedule == null || this.exist(schedule)) 
            return;
        
        this.teamSchedules[size] = (Schedule2Team) schedule;
        size++;       
    }

    /**
     *
     * @param index
     */
    public void removeSchedule(int index) throws ArrayIndexOutOfBoundsException
    {        
        if(index > this.size) 
            throw new ArrayIndexOutOfBoundsException();
        
        for (int i = index; i < size-1; i++) 
            this.teamSchedules[i] = this.teamSchedules[i+1];
        
        this.size--;
    }
    
    public void removeAll()
    {
        this.teamSchedules = null;
        this.size = 0;
        this.teamSchedules = new Schedule2Team[this.capacity];
    
    }
    
    public boolean exist(TeamOperations member) throws CloneNotSupportedException
    {
        if(!(member instanceof Schedule2Team))  return false;
        
        for (int i = 0; i < this.size; i++)
            if(this.teamSchedules[i].equals(member))
                return true;
        
        
        return false;
    }

    public Schedule2Team get(int i) throws CloneNotSupportedException
    {
        return (Schedule2Team) this.teamSchedules[i];
    
    }
    @Override
    public String [] printTable()
    {
        String [] str = new String[this.size];
        
        for (int i = 0; i < this.size(); i++) {
            str[i] = (this.teamSchedules[i].toString());
        }
        
        return str;
    }
    
    
    @Override
    public Object clone() throws CloneNotSupportedException
    {
        ScheduleTable table = (ScheduleTable) super.clone();
        
        table.teamSchedules = (Schedule2Team[]) this.teamSchedules.clone();
        for (int i = 0; i < this.size; i++)
            table.teamSchedules[i] = (Schedule2Team) this.teamSchedules[i];
            
         return table;             
    }
    
    
    
    
    
    
}
