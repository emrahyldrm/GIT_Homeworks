package com.jp.tffl.Person;

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
public class TeamManager extends Manager
{
    protected String team;

    /**
     * constructor
     */
    public TeamManager() 
    {
        super();
        team = "no-team";    
    }
    
    
     public TeamManager(String line)
    {
        if(line.length() <  6)
            return;
       
        String [] parts = line.split(";");
        this.ID = parts[0];
        this.name = parts[1];
        this.birthDate = parts[2];
        this.adress = parts[3];
        this.type = parts[4];
        this.team = parts[5];
    }
    
    /**
     * 
     * @return team
     */
    public String getTeam()
    {
        return this.team;
    }
    
    /**
     * set team
     * @param newTeam 
     */
    public void setTeam(String newTeam)
    {
        this.team = newTeam;                
    }

    @Override
    public int hashCode() {
        int hash = 3;
        hash = 73 * hash + Objects.hashCode(this.team);
        return hash;
    }
    
    
    @Override
    public boolean equals(Object other)
    {
        if(other == null)   return false;
        if(!(other instanceof TeamManager)) return false;
        
        TeamManager manager = (TeamManager) other;
        
        
        return (this.ID.equals(manager.ID) && this.name.equals(manager.name) && 
                this.birthDate.equals(manager.birthDate) && this.adress.equals(manager.adress)
                && this.team.equals(manager.team) && this.type.equals(type));
        
        
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
                             "\n" + "Adress: " + this.adress + "\n" + "Team: " + this.team + "\n" +  "Type: " + this.type + "\n" );
    
    }
}
