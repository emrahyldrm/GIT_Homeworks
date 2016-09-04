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
public  abstract class PersonClass implements Person
{
    protected String name;
    protected String birthDate;
    protected String adress;
    protected String ID;
    
     /**
     * default constructor
     * name = "no-name";
     * ID = "no-ID";
     * adress = "non-adress";
     * birthDate = "00.00.0000";
     */
    public PersonClass()
    {       
        this.name = "no-name";
        this.ID = "no-ID";
        this.adress = "non-adress";
        this.birthDate = "00.00.0000";
    }
    
    
    /**
     * 
     * @return ID
     */
    @Override
    public  String getID()
    { 
        return this.ID; 
    }
    
    /**
     * 
     * @return name
     */
    @Override
    public String getName()
    {
        return this.name;
    }
    
    /**
     * 
     * @return birthdate
     */
    @Override
    public String getBirthDate()
    {
        return this.birthDate;
    }
    
    
    /**
     * 
     * @return adress
     */
    @Override
    public String getAdress()
    {
        return this.adress;
    }
    
    
    /**
     * setting up ID
     * @param newID 
     */
    @Override
    public void setID(String newID)
    {
        this.ID = newID;
    }
     
    /**
     * setting up name
     * @param newName 
     */
    @Override
    public void setName(String newName)
    {
        //name = new String(newName);
        this.name = newName;
    }
    
    
    /**
     * setting up birthdate
     * @param newBirthDate 
     */
    @Override
    public void setBirthDate(String newBirthDate)
    {
        this.birthDate = newBirthDate;
    }
    
    /**
     * setting up adress
     * @param newAdress 
     */
    
    @Override
    public void setAdress(String newAdress)
    {
        this.adress = newAdress;
    }
    
    
    /**
     * 
     * @param other
     * @return equality
     */
    @Override 
    public abstract boolean equals(Object other);

    @Override
    public int hashCode() {
        int hash = 7;
        hash = 29 * hash + Objects.hashCode(this.name);
        hash = 29 * hash + Objects.hashCode(this.birthDate);
        hash = 29 * hash + Objects.hashCode(this.adress);
        hash = 29 * hash + Objects.hashCode(this.ID);
        return hash;
    }

    
    
    @Override
    public abstract String toString();
}
