/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.jp.tffl.FileOperations;

import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectInput;
import java.io.ObjectInputStream;
import java.io.ObjectOutput;
import java.io.ObjectOutputStream;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

/**
 *
 * @author Jason
 */
public class FileOperations 
{

    public static void writeBinary(Object ownObject, String filePath) throws IOException
    {
        File temp = new File(filePath);
        if(temp.isFile())
            temp.delete();
        
        ByteArrayOutputStream bos = new ByteArrayOutputStream();
        ObjectOutput out = null;
        out = new ObjectOutputStream(bos);   
        out.writeObject(ownObject);
        byte[] yourBytes = bos.toByteArray();

        FileOutputStream file = new FileOutputStream(filePath);

        file.write(yourBytes, 0, yourBytes.length);
        file.flush();
        file.close();
        bos.close();
    }
    
    
    
    public static Object readBinary(String filePath) throws FileNotFoundException, IOException, ClassNotFoundException
    {
        File inp = new File(filePath);
        byte [] bytes = new byte[(int)inp.length()];
        FileInputStream fis = new FileInputStream(filePath);
        fis.read(bytes, 0, bytes.length);

        ByteArrayInputStream bis = new ByteArrayInputStream(bytes);
        ObjectInput oi = new ObjectInputStream(bis);
        fis.close();
        bis.close();
        
        return  oi.readObject(); 
        
    }
    
    public static void deleteFolder(String folderPath) throws IOException
    {
        File folder = new File(folderPath);
        if(!folder.isDirectory())
            return;
        File [] files = folder.listFiles();
        
        for (int i = 0; i < files.length; i++) 
            if(files[i].isFile())
                files[i].delete();
        
        Files.deleteIfExists(Paths.get(folderPath));
    
    
    }
    
    public static void deleteFolder(Path folderPath) throws IOException
    {
        FileOperations.deleteFolder(folderPath.normalize().toString());
    
    }
    
}
