
package adaboost;

import java.util.ArrayList;
import java.util.List;
import java.util.Map;

/**
 *
 * @author Administrator
 */
public class Entropy {
    public int posCount, negCount, totalCount;
    public double entropy, gain;
    private static Entropy instance = null;
    AttributeList at = AttributeList.getInstance();
    public static Entropy getInstance() {
      if(instance == null) {
         instance = new Entropy();
      }
      return instance;
   }
    public double getEntropy(List<List<Attribute>> records)
    {
        entropy = 0;
        posCount=0; negCount=0; totalCount=0;
        for(int i=0; i<records.size(); ++i)
        {
            if(records.get(i).get(9).getValue().equals("0"))
                negCount++;
            else if(records.get(i).get(9).getValue().equals("1"))
                posCount++;
        }
        totalCount = posCount+negCount;
        if(posCount==totalCount)
        {
            entropy = -(((posCount*1.0)/totalCount)*(Math.log((posCount*1.0)/totalCount)/Math.log(2)));
        }
        else if(negCount==totalCount)
        {
            entropy = -(((negCount*1.0)/totalCount)*(Math.log((negCount*1.0)/totalCount)/Math.log(2)));
        }
        else
        {
            entropy = -(((posCount*1.0)/totalCount)*(Math.log((posCount*1.0)/totalCount)/Math.log(2)))-(((negCount*1.0)/totalCount)*(Math.log((negCount*1.0)/totalCount)/Math.log(2)));
        }
        return entropy;
    }
    public double getGain(double entropy, int totalRow, int attributeID, List<List<Attribute>> records)
    {
        gain=entropy;
        double et=0;
        int posCount, negCount, totalCount;
        //Map<String, List<String>> map = at.getMap();
        //String []  attributeList = at.getAttributeList();
        String s = at.attributeList[attributeID];
        List<String> list = new ArrayList<String>();
        list=at.map.get(s);
        for(int i=0; i<list.size() ; ++i)
        {
            String value = list.get(i);
            posCount=negCount=totalCount=0;
            for(int j=0; j<records.size(); ++j)
            {
                if(records.get(j).get(attributeID).getValue().equals(value) && records.get(j).get(9).getValue().equals("0"))
                    negCount++;
                else if(records.get(j).get(attributeID).getValue().equals(value) && records.get(j).get(9).getValue().equals("1"))
                    posCount++;
            }
            totalCount = posCount+negCount;
            if(posCount==totalCount || negCount==totalCount || totalCount==0)
            {
                et = 0;
            }
            else
            {
                et = -(((posCount*1.0)/totalCount)*(Math.log((posCount*1.0)/totalCount)/Math.log(2)))-(((negCount*1.0)/totalCount)*(Math.log((negCount*1.0)/totalCount)/Math.log(2)));
            }
            gain += -((totalCount*1.0)/totalRow)*(et);
        }
        return gain;
    }
}
