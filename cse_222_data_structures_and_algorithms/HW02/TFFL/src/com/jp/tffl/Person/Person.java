package com.jp.tffl.Person;

import java.io.Serializable;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author Jason
 */
public interface Person extends Cloneable, Serializable
{
    /**
     * 
     * @return ID 
     */
    public String getID();
    
    /**
     * 
     * @return name 
     */
    public String getName();

    /**
     * 
     * @return birthDate
     */
    public String getBirthDate();
    
    /**
     * 
     * @return adress
     */
    public String getAdress();
    
    
    /**
     * set person ID
     * @param newID 
     */
    public void setID(String newID);
    
    /**
     * set person name
     * @param newName 
     */
    public void setName(String newName);
    
    /**
     * set person birth sate
     * @param newBirtDate 
     */
    public void setBirthDate(String newBirtDate);
    
    /**
     * set person adress
     * @param newADress 
     */
    public void setAdress(String newADress);
    
    
    /**
     * 
     * @param other
     * @return equality
     */
    @Override
    public boolean equals(Object other);
    

    @Override
    public String toString();
 
    
    
  }
