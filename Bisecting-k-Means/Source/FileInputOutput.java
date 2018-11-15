package bisecting_k_means;

/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
//package naivebyesclassifierfortext;

import java.io.BufferedReader;
import java.io.DataInputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.StringTokenizer;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author Administrator
 */
public class FileInputOutput {
    public static final String PATH_TO_DATA_FILE = "bisecting.txt";
    
    private static FileInputOutput instance = null;
    public static FileInputOutput getInstance() {
      if(instance == null) {
         instance = new FileInputOutput();
      }
      return instance;
    }
    public void getData()
    {
        Data data = Data.getInstance();
        int pointCount=0;
        List<Point> pointList = new ArrayList<Point>();
        BufferedReader reader = null;
	DataInputStream dis = null; 
        
        try {
            File f = new File(PATH_TO_DATA_FILE);
            FileInputStream fis;
            fis = new FileInputStream(f);
            reader = new BufferedReader(new InputStreamReader(fis));
            String line=null;
            while ((line = reader.readLine()) != null) { 
                Point point = new Point();
                String delims = "[ \\t]+";
                String[] tokens = line.split(delims);
                point.x = Double.valueOf(tokens[0]);
                point.y = Double.valueOf(tokens[1]);
                point.id = pointCount;
                pointCount++;
                pointList.add(point);
            }
            data.setPointCounts(pointCount);
            data.setPointList(pointList);
        }
        catch (FileNotFoundException ex) {
            Logger.getLogger(FileInputOutput.class.getName()).log(Level.SEVERE, null, ex);
        }
        catch (IOException e) { 
           System.out.println("Uh oh, got an IOException error: " + e.getMessage()); 
        }
    }
}
