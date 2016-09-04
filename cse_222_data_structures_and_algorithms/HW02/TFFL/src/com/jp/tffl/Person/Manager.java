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
public abstract class Manager extends PersonClass
{
    protected String type;

    /**
     * default constructor
     * name = "no-name";
     * ID = "no-ID";
     * adress = "non-adress";
     * birthDate = "00.00.0000";
     * type = "no-type";
     */
    public Manager()
    {
        this.name = "no-name";
        this.ID = "no-ID";
        this.adress = "non-adress";
        this.birthDate = "00.00.0000";
        this.type = "no-type";
    }
    
    /**
     * president or vice president
     * @return type
     */
    public String getType()
    {
        return this.type;
    }
    
    /**
     * manage type setting
     * president or vice president
     * @param newType 
     */
    public void setType(String newType)
    {
        this.type = newType;
    }    
    
    
    @Override
    
    
    /**
     * ID: ..
     * Name: ..
     * BirthDate: ..
     * Adress: ..
     * Type: ..
     * @return String
     */
    public String toString()
    {
        return String.format("ID: "+ this.ID + "\n" + "Name: " + this.name + "\n" + "Birt Date: " + this.birthDate +
                             "\n" + "Adress: " + this.adress + "\n" + "Type: " + this.type + "\n" );
    }
}
