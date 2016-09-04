package com.jp.tffl.Person;

import java.io.FileWriter;


/**
 *
 * @author Jason
 */
public class TFFLManager extends Manager
{
    
    
    public TFFLManager()
    {
        super();
    }
    
    public TFFLManager(String line)
    {
        if(line.length() <  5)
            return;
       
        String [] parts = line.split(";");
        this.ID = parts[0];
        this.name = parts[1];
        this.birthDate = parts[2];
        this.adress = parts[3];
        this.type = parts[4];
        
        

    }
    /**
     * check equality
     * @param other
     * @return 
     */
    @Override
    public boolean equals(Object other)
    {
        if(other == null) return false;
        if(!(other instanceof TFFLManager)) return false;
        
        TFFLManager manager = (TFFLManager) other;
        
        return (this.ID.equals(manager.ID) && this.name.equals(manager.name) && 
                this.birthDate.equals(manager.birthDate) && this.adress.equals(manager.adress)
                && this.type.equals(manager.type));
    }
    
    
    @Override
    public String toString()
    {
        return super.toString();
    }
    
    
    @Override
    public Object clone() throws CloneNotSupportedException
    {
        return super.clone();
    }

    @Override
    public int hashCode() {
        int hash = 7;
        return hash;
    }
}

