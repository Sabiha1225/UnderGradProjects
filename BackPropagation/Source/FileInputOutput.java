/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package backpropagation;

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
public class FileInputOutput {
    public static final String PATH_TO_DATA_FILE = "Train.txt";
    public static final String PATH_TO_DATA_FILE1 = "Test.txt";
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
        double[][] test= new double[300][4];
        double[][] train= new double[300][4];
        int dataCount=0, testDataCount=0;
        BufferedReader reader = null;
	DataInputStream dis = null; 
        try {
            File f = new File(PATH_TO_DATA_FILE);
            FileInputStream fis;
            fis = new FileInputStream(f);
            reader = new BufferedReader(new InputStreamReader(fis));
            String line=null;
            line = reader.readLine();
            StringTokenizer st = new StringTokenizer(line, " ");
            String A = st.nextToken();
	    String B = st.nextToken();
            String C = st.nextToken();
            data.setNoOfAttribute(Integer.valueOf(A));
            data.setNoOfClass(Integer.valueOf(B));
            data.setNoOfData(Integer.valueOf(C));
            //System.out.println(A+"  "+B+"  "+C);
            String delims = "[ \\t]+";
            String line1 = null;
            while ((line1 = reader.readLine()) != null) { 
                //System.out.println(line1);
                String[] tokens = line1.split(delims);
                for(int i=1; i<tokens.length; ++i)
                {
                    //String s = tokens[i];
                    double d = Double.parseDouble(tokens[i]);
                    
                    //System.out.print(d+"----------");
                    train[dataCount][i-1] = d;
                }
                dataCount++;
                //System.out.println();
            }
            data.setTrain(train);
            //data.setNoOfData(dataCount);
            f = new File(PATH_TO_DATA_FILE1);
            fis = new FileInputStream(f);
            reader = new BufferedReader(new InputStreamReader(fis));
            line=null;
            //String delims = "[ \\t]+";
            //String line1 = null;
            while ((line = reader.readLine()) != null) { 
                //System.out.println(line1);
                String[] tokens = line.split(delims);
                for(int i=1; i<tokens.length; ++i)
                {
                    //String s = tokens[i];
                    double d = Double.parseDouble(tokens[i]);
                    
                    //System.out.print(d+"----------");
                    test[testDataCount][i-1] = d;
                }
                testDataCount++;
                //System.out.println();
            }
            data.setTest(test);
            data.setNoOfTestData(testDataCount);
        }
        catch (FileNotFoundException ex) {
            Logger.getLogger(FileInputOutput.class.getName()).log(Level.SEVERE, null, ex);
        }
        catch (IOException e) { 
           System.out.println("Uh oh, got an IOException error: " + e.getMessage()); 
        }
    }
}
