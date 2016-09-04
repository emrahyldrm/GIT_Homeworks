/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package hybridList;

import java.util.ArrayList;
import java.util.Collection;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;
import java.util.ListIterator;
import java.util.NoSuchElementException;

/**
 *
 * @author Emrah YILDIRIM 111044056
 * @param <E> generic class type
 */
public class HybridList< E > implements List<E>
{
    private LinkedList< ArrayList<E> > parent = new LinkedList< ArrayList<E> >();
    //private int size=0;

    @Override
    public int size() 
    {
        int total=0;
        for (int i = 0; i < parent.size(); i++)
        {
            total += parent.get(i).size();
        }
        return total;
    }

    @Override
    /**
     * 
     */
    public boolean isEmpty() 
    {
        return 0 == this.size();
    }

    @Override
    public boolean contains(Object o) 
    {
        for (int i = 0; i < parent.size(); i++)
            if(parent.get(i).contains(o))
                return true;
        return false;
    }

    @Override
    public Iterator<E> iterator() 
    {
        return this.listIterator();
    }

    @Override
    public Object[] toArray()
    {
        int index = 0;
        
        Object [] array = new Object[this.size()];
        for (int i = 0; i < parent.size(); i++) 
            for (int j = 0; j < parent.get(i).size(); j++)
            {
               array[index] = parent.get(i).get(j);
               index++;
            }
        return array;
    }

    //not completed
    @Override
    public <T> T[] toArray(T[] a)
    {
        ArrayList<T> array = new ArrayList<T>();
        for (int i = 0; i < parent.size(); i++) 
            for (int j = 0; j < parent.get(i).size(); j++)
               array.add((T) parent.get(i).get(j));
        
        return array.toArray(a);

    }

    @Override
    public boolean add(E e) 
    {
        this.add(this.size(), e);
        return true;
    }

    @Override
    public boolean remove(Object o) 
    {
        if(!this.contains(o))
            return false;
        this.remove(this.indexOf(o));        
        
        return true;
    }

    @Override
    public boolean containsAll(Collection<?> c)
    {
        Iterator<E> iter = (Iterator<E>)c.iterator();
        while(iter.hasNext())
            if(!this.contains(iter.next()))
                return false;        
        return true;
    }

    @Override
    public boolean addAll(Collection<? extends E> c)
    {
        return this.addAll(this.size(), c);
    }

    @Override
    public boolean addAll(int index, Collection<? extends E> c) 
    {
        Iterator<E> iter = (Iterator<E>)c.iterator();
        for(int i = index; iter.hasNext(); ++i)
            this.add(i, iter.next());
        
        return true;
    }

    @Override
    public boolean removeAll(Collection<?> c) 
    {
        if(!this.containsAll(c))
            return false;
        Iterator<E> iter = (Iterator<E>) c.iterator();
        
        while(iter.hasNext())
            this.remove(iter.next());
        
        return true;
    }

    @Override
    public boolean retainAll(Collection<?> c) 
    {        
        this.clear();        
        this.addAll((Collection<E>)c);
    
        return true;
    }

    @Override
    public void clear() 
    {
        parent.clear();
    }

    @Override
    public E get(int index)
    {
        int currIndex = 0;

        if(index < 0 || index >= this.size())
            throw new IndexOutOfBoundsException();
  
        for (int i = 0; i < parent.size(); i++)
            for (int j = 0; j < parent.get(i).size(); j++) 
            {
                if(currIndex == index)
                    return parent.get(i).get(j);
                currIndex++;
            }
        return null;
    }
    
    
    @Override
    public E set(int index, E element)
    {
        int currIndex = 0;
        if(index < 0 || index > this.size())
            throw new IndexOutOfBoundsException();
        for (int i = 0; i < parent.size(); i++)
            for (int j = 0; j < parent.get(i).size(); j++) 
            {
                if(currIndex == index)
                    return parent.get(i).set(j, element);
                currIndex++;
            }
        
        return null;
    }


    @Override
    public void add(int index, E element)
    {
        if(index < 0 || index > this.size())
            throw new IndexOutOfBoundsException();
        
        
        if(index == 0 && this.isEmpty())
        {
            parent.add(new ArrayList<E>());
            parent.get(0).add(element);
        }
        else if(this.size() == index && index % 5 == 0)
        {
            parent.add(new ArrayList<E>());
            parent.get(index / 5).add(element);
            //this.set(this.size() - 1, element); //bullshit
        }
        else if(this.size() == index && index % 5 != 0)
        {
            parent.get(index / 5).add(element);
        }
        else
        {
            for (int i = this.size(); i > index; i--)
            {             
                if(i == this.size() && i % 5 == 0)
                {
                    this.parent.add(new ArrayList<E>());
                    this.parent.get(i/5).add(this.get(i-1));
                }
                else if(i == this.size() && i % 5 != 0)
                    this.parent.get(i/5).add(this.get(i-1));
                else
                    this.set(i, this.get(i-1));
            }
            this.set(index, element);

        }       
    }

    /**
     * display list memory representation
     */
    public void display()
    {
        System.out.println("parent size :"  + parent.size());

        for (int i = 0; i < parent.size(); i++)
            System.out.println("size " + i +" : " + parent.get(i).size());
    }
    
    
    @Override
    public E remove(int index)
    {
        if(index < 0 || index >= this.size())
            throw new IndexOutOfBoundsException();
        E item = null;
        if(index == this.size() - 1)
        {   
            item =  this.parent.get(index/5).remove(this.parent.get(index/5).size() - 1 );
            if(this.parent.get(this.parent.size() - 1).isEmpty())
               this.parent.remove(this.parent.size() - 1);
        }
        else
        {
            item = this.parent.get(index/5).set(index % 5, null);
            
            for (int i = index; i < this.size()-1; i++)
            {
               this.set(i, this.get(i+1));
            }
           this.remove(this.size() - 1);
           
           if(this.parent.get(this.parent.size() - 1).isEmpty())
               this.parent.remove(this.parent.size() - 1);
        }
        return item;
    }

    @Override
    public int indexOf(Object o)
    {        
        int currIndex = 0;

        for (int i = 0; i < parent.size(); i++)
            for (int j = 0; j < parent.get(i).size(); j++) 
            {
                if(o.equals(parent.get(i).get(j)))
                    return currIndex;
                currIndex++;
            }
        return -1;        
    }
    
    
    @Override
    public int lastIndexOf(Object o)
    {        
        int currIndex = this.size()-1;

        for (int i = parent.size()-1; i > -1 ; i--)
            for (int j = parent.get(i).size()-1; j > -1; j--) 
            {
                if(((E)o).equals(parent.get(i).get(j)))
                    return currIndex;
                currIndex--;
            }
        return -1;        
    }
    @Override
    public ListIterator<E> listIterator()
    {       
        return new HybridIterator();
    }
    
    @Override
    public ListIterator<E> listIterator(int index)
    {
        return new HybridIterator(index);
    }

    @Override
    public List<E> subList(int fromIndex, int toIndex)
    {
        if(fromIndex < 0 || toIndex < 0 || toIndex > this.size() || fromIndex > this.size() )
            throw new IndexOutOfBoundsException();
        List list = new LinkedList();
        for (int i = fromIndex; i < toIndex; i++) {
            list.add(this.get(i));
        }
        return list;
    }


    
    
   
    private class HybridIterator implements ListIterator<E>  
    {
        private E lastItemReturned;
        private E nextItem;
        private int index = 0;
        
        private HybridIterator()
        {
            this(0);
        }
        
        private HybridIterator(int i)
        {
            index = i;
            lastItemReturned = null;
            if(HybridList.this.isEmpty())
                nextItem = null;
            else
                nextItem = HybridList.this.get(index);
        }
        
        
        @Override
        public boolean hasNext() 
        {
            return nextItem != null;
        }

        @Override
        public E next() 
        {
            if(!HybridList.this.isEmpty() && nextItem == null)
                return null;
            if(nextItem == null)
                throw new NoSuchElementException();
            
            lastItemReturned = nextItem;
            ++index;
            try
            {
                nextItem = HybridList.this.get(index);
            } catch (IndexOutOfBoundsException e) 
            {
                nextItem = null;
            }
            
            
            return lastItemReturned;
        }

        @Override
        public boolean hasPrevious() 
        {
            return lastItemReturned != null;
        }

        @Override
        public E previous() 
        {
            if(lastItemReturned == null)
                throw new NoSuchElementException();
            
            nextItem = lastItemReturned;
            --index;
            try
            {
                lastItemReturned = HybridList.this.get(index);
            } catch (IndexOutOfBoundsException e) 
            {
                lastItemReturned = null;
            }
            
            
            return nextItem;
        }

        @Override
        public int nextIndex() 
        {
            if(nextItem != null)
                return index + 1;
            else
                return HybridList.this.size();
        }

        @Override
        public int previousIndex() 
        {
            if(lastItemReturned != null)
                return index - 1;
            else
                return -1;
        }

        @Override
        public void remove() 
        {
            if(lastItemReturned == null)
                throw new IllegalStateException();
            
            HybridList.this.remove(lastItemReturned);
        }

        @Override
        public void set(E e)
        {
            if(lastItemReturned == null)
                throw new IllegalStateException();
            HybridList.this.set(index, e);
        }

        @Override
        public void add(E e) 
        {
            HybridList.this.add(index, e);
        }
    } 
}
