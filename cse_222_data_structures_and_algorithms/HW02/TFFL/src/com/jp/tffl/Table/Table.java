package com.jp.tffl.Table;

import com.jp.tffl.TeamOperations.TeamOperations;
import java.io.Serializable;
import java.util.ArrayList;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author Jason
 */
public abstract class Table implements Cloneable, Serializable
{
    protected  int weekNumber;
    protected int size;
    protected int capacity;

    public Table() 
    {
        this.weekNumber = 0;
        this.size = 0;
        this.capacity = 20;
    }

    
    
    public int size()
    {
        return this.size;
    }
    
    public int capacity()
    {
        return this.capacity;
    }
    
    public int getWeekNumber()
    {
        return this.weekNumber;
    }
    
    
    public void setWeekNumber(int newNumber)
    {
        this.weekNumber = newNumber;
    }
    
    public Object clone() throws CloneNotSupportedException
    {
        return super.clone();
    }
    
    public abstract String [] printTable();
    
}
