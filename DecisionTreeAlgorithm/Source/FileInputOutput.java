/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package id3final;

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
    public static final String PATH_TO_DATA_FILE = "data.csv";
    private static FileInputOutput instance = null;
    public static FileInputOutput getInstance() {
      if(instance == null) {
         instance = new FileInputOutput();
      }
      return instance;
   }
    public List<List<Attribute>> getRecords()
    {
        
        ID3 id3 = ID3.getInstance();
        AttributeList al = AttributeList.getInstance();
        List<List<Attribute>> records = new ArrayList<List<Attribute>>();
        List<List<Attribute>> test = new ArrayList<List<Attribute>>();
        int dataCount=0, testDataCount=0;
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
                
	        String A = st.nextToken();
	        String B = st.nextToken();
		String C = st.nextToken();
		String D = st.nextToken();
	        String E = st.nextToken();
                String F = st.nextToken();
                String G = st.nextToken();
                String H = st.nextToken();
                String I = st.nextToken();
                String J = st.nextToken();
                if(dataCount<546)
                {
                records.add(new ArrayList<Attribute>());
                records.get(dataCount).add(new Attribute(A, "A", 0));
                records.get(dataCount).add(new Attribute(B, "B", 1));
                records.get(dataCount).add(new Attribute(C, "C", 2));
                records.get(dataCount).add(new Attribute(D, "D", 3));
                records.get(dataCount).add(new Attribute(E, "E", 4));
                records.get(dataCount).add(new Attribute(F, "F", 5));
                records.get(dataCount).add(new Attribute(G, "G", 6));
                records.get(dataCount).add(new Attribute(H, "H", 7));
                records.get(dataCount).add(new Attribute(I, "I", 8));
                records.get(dataCount).add(new Attribute(J, "J", 9));
                }
                else
                {
                    test.add(new ArrayList<Attribute>());
                    test.get(testDataCount).add(new Attribute(A, "A", 0));
                    test.get(testDataCount).add(new Attribute(B, "B", 1));
                    test.get(testDataCount).add(new Attribute(C, "C", 2));
                    test.get(testDataCount).add(new Attribute(D, "D", 3));
                    test.get(testDataCount).add(new Attribute(E, "E", 4));
                    test.get(testDataCount).add(new Attribute(F, "F", 5));
                    test.get(testDataCount).add(new Attribute(G, "G", 6));
                    test.get(testDataCount).add(new Attribute(H, "H", 7));
                    test.get(testDataCount).add(new Attribute(I, "I", 8));
                    test.get(testDataCount).add(new Attribute(J, "J", 9));
                    testDataCount++;
                }
                dataCount++;
                
            }
            id3.setDataSize(dataCount);
            id3.setTestDataSize(testDataCount);
            al.setRecords(records);
            al.setTest(test);
        }
        catch (FileNotFoundException ex) {
            Logger.getLogger(FileInputOutput.class.getName()).log(Level.SEVERE, null, ex);
        }
        catch (IOException e) { 
           System.out.println("Uh oh, got an IOException error: " + e.getMessage()); 
        }

        return records;
    }
}
