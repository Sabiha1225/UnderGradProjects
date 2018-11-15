/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package id3final;

/**
 *
 * @author Administrator
 */
import java.util.ArrayList;
import java.util.List;
import java.util.Map;
/**
 *
 * @author Administrator
 */
public class ID3 {

    public static int getTestDataSize() {
        return testDataSize;
    }

    public static void setTestDataSize(int testDataSize) {
        ID3.testDataSize = testDataSize;
    }

    public static void setTest(List<List<Attribute>> test) {
        ID3.test = test;
    }
    public static int dataSize = 0;
    public static int testDataSize = 0;
    public static int noOfAttributes = 10;
    public static List<List<Attribute>> records;
    public static List<List<Attribute>> test;
    private static ID3 instance = null;
    public static ID3 getInstance() {
      if(instance == null) {
         instance = new ID3();
      }
      return instance;
   }
            
    public static void main(String[] args) {
        Attribute att;
        AttributeList al = AttributeList.getInstance();
        FileInputOutput file = FileInputOutput.getInstance();
        records = new ArrayList<List<Attribute>>();
        records = file.getRecords();
        /*for(int i=0; i<records.size(); ++i)
        {
            for(int j=0; j<noOfAttributes ; ++j)
            { 
                att = records.get(i).get(j);
                System.out.print(att.getValue()+ att.attributeName+"      ");
            }
            System.out.println();
        }
        System.out.println("==============================="+dataSize+"===============================================================");
        test= al.getTest();
        for(int i=0; i<test.size(); ++i)
        {
            for(int j=0; j<noOfAttributes ; ++j)
            { 
                att = test.get(i).get(j);
                System.out.print(att.getValue()+ att.attributeName+"      ");
            }
            System.out.println();
        }*/
        System.out.println("==============================="+testDataSize+"===============================================================");
       Tree t = Tree.getInstance();
       t.createTree(records);
       t.printTree();
       List<Attribute> list = new ArrayList<Attribute>();
       test= al.getTest();
       list =  test.get(0);
       for(int i=0; i<noOfAttributes; ++i)
       {
           att = list.get(i);
           System.out.println(att.attributeName+"   "+att.value);
       }
        
       for(int i=0; i<test.size(); ++i)
       {
           list =  test.get(i);
           att = list.get(9);
           System.out.println(att.value);
           t.traverseTree(list);
           if(t.foundFalse==1)
          System.out.println("Found but false");
      if(t.foundTrue==1)
          System.out.println("Found but true");
      if(t.foundOther==1)
          System.out.println("Found but 77");
      if(t.notFound==1)
          System.out.println("Not Found");
       }
       int total =t.truePositive+t.falsePositive+t.trueNegative+t.falseNegative;
       System.out.println(t.truePositive+" "+t.falsePositive+" "+t.trueNegative+" "+t.falseNegative+"  "+total);
       double accuracy = ((t.truePositive+t.trueNegative)*1.0)/total;
       double precesion = (t.truePositive*1.0)/(t.truePositive+t.falsePositive);
       double recall = (t.truePositive*1.0)/(t.truePositive+t.falseNegative);
       double f_measure = 2*(precesion*recall)/(precesion+recall);
       double g_mean = Math.sqrt(precesion*recall);
       System.out.println(""+accuracy+"    "+precesion+"    "+recall+"    "+f_measure+"    "+g_mean);
       //System.out.println(""+accuracy+","+precesion+","+recall+","+f_measure+","+g_mean);
          
    }

    public static void setNoOfAttributes(int noOfAttributes) {
        ID3.noOfAttributes = noOfAttributes;
    }

    public static void setRecords(List<List<Attribute>> records) {
        ID3.records = records;
    }

    public void setDataSize(int dataSize) {
        this.dataSize = dataSize;
    }

    public int getDataSize() {
        return dataSize;
    }
    public static int getNoOfAttributes() {
        return noOfAttributes;
    }

    public static List<List<Attribute>> getRecords() {
        return records;
    }
}
