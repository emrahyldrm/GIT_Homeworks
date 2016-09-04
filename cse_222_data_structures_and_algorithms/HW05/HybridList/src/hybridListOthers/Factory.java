/**
 * Emrah YILDIRIM 111044056
 * Test List Interface Homework
 */


/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package hybridListOthers;

import hybridList.HybridList;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;

/**
 *
 * @author Emrah YILDIRIM 111044056
 */
public class Factory
{
    /**
     * if string is not array, hybrid or linked method will return HybridList
     * @param listType the list type that required
     * @return expected list
     */
    public static List<Integer> factory(String listType)
    {
        String type = listType.toLowerCase();
        switch(type)
        {
            case "array":
                        return new ArrayList<Integer>();
             
            case "linked":
                        return new LinkedList<Integer>();
             
            case "hybrid":
                        return new HybridList<Integer>();
                
            default:
                    return new HybridList<Integer>();
        }
    } 
}
