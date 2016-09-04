/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package hybridListOthers;

import hybridList.HybridList;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.ListIterator;

/**
 *
 * @author Jason
 */
public class HybridListMain
{
    public static void main(String [] args)
    {
        HybridList<String> list = new HybridList<String>();
        LinkedList<String> list2 = new LinkedList<String>();
        for (int i = 0; i < 16; i++)
         list.add(""+i);


        for (int i = 0; i < 3; i++)
         list2.add(""+i);
       list.display();
        
        ListIterator<String> iter = list.listIterator();
        
        for (int i = 0; iter.hasNext(); i++)
        {
            System.out.println(iter.next());
        }


        System.out.println("\nremoved index " + list.remove(12));
        System.out.println("\nadded 12 " + list.add(""+12));
        System.out.println("\nremoved index " + list.remove(6));
        System.out.println("\n");
        for (int i = 0; i < list.size(); i++)
        {
            System.out.println(list.get(i));
        }
        
        list.display();
        
    }
}
