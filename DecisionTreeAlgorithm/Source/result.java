/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package id3final;

/**
 *
 * @author Administrator
 */
/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

import java.io.BufferedReader;
import java.io.DataInputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;
import java.util.StringTokenizer;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author Administrator
 */
public class result {
    public static final String PATH_TO_DATA_FILE = "result1.txt";
    private static FileInputOutput instance = null;
    static double accuracy=0;
    static double precesion=0;
    static double recall=0;
    static double f_measure=0;
    static double g_mean=0;
    static int count=0;
    public static void main(String[] args) {
        BufferedReader reader = null;
	DataInputStream dis = null; 
        try {
            File f = new File(PATH_TO_DATA_FILE);
            FileInputStream fis;
            fis = new FileInputStream(f);
            reader = new BufferedReader(new InputStreamReader(fis));
            String line;
            while ((line = reader.readLine()) != null) {
                StringTokenizer st = new StringTokenizer(line, ",");
                
	        accuracy += Double.valueOf(st.nextToken());
	        precesion += Double.valueOf(st.nextToken());
		recall += Double.valueOf(st.nextToken());
		f_measure += Double.valueOf(st.nextToken());
	        g_mean += Double.valueOf(st.nextToken());
                count++;
                //System.out.println(accuracy+" "+precesion+" "+recall+" "+f_measure+" "+g_mean); 
            }
        }
        catch (FileNotFoundException ex) {
            Logger.getLogger(FileInputOutput.class.getName()).log(Level.SEVERE, null, ex);
        }
        catch (IOException e) { 
           System.out.println("Uh oh, got an IOException error: " + e.getMessage()); 
        }
        System.out.println((accuracy*100)/count+" "+(precesion*100)/count+" "+(recall*100)/count+" "+(f_measure*100)/count+" "+(g_mean*100)/count);
        System.out.println(count);
    }
    
}
