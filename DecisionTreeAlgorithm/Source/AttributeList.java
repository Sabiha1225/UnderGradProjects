
package id3final;

//import java.util;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

/**
 *
 * @author Administrator
 */
public class AttributeList {
    public String [] attributeList =  {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J"};
    List<Integer> attributeIDList = new ArrayList<Integer>();
    List<List<Attribute>> records;
    List<List<Attribute>> test;
    private static AttributeList instance = null;
          
    public Map<String, List<String>> map = new HashMap<String, List<String>>();
    List<String> list = new ArrayList<String>();
    List<String> list1 = new ArrayList<String>();
    List<String> list2 = new ArrayList<String>();
    List<String> list3 = new ArrayList<String>();
    List<String> list4 = new ArrayList<String>();
    List<String> list5 = new ArrayList<String>();
    List<String> list6 = new ArrayList<String>();
    List<String> list7 = new ArrayList<String>();
    List<String> list8 = new ArrayList<String>();
    List<String> list9 = new ArrayList<String>();
    public AttributeList()
    {
        list.clear();
        for(int i=1; i<=10; ++i)
        {
            list.add(String.valueOf(i));
        }
        map.put("A", list);
        list1.clear();
        for(int i=1; i<=10; ++i)
        {
            list1.add(String.valueOf(i));
        }
        map.put("B", list1);
        list2.clear();
        for(int i=1; i<=10; ++i)
        {
            list2.add(String.valueOf(i));
        }
        map.put("C", list2);
        list3.clear();
        for(int i=1; i<=10; ++i)
        {
            list3.add(String.valueOf(i));
        }
        map.put("D", list3);
        list4.clear();
        for(int i=1; i<=10; ++i)
        {
            list4.add(String.valueOf(i));
        }
        map.put("E", list4);
        list5.clear();
        for(int i=1; i<=10; ++i)
        {
            list5.add(String.valueOf(i));
        }
        map.put("F", list5);
        list6.clear();
        for(int i=1; i<=10; ++i)
        {
            list6.add(String.valueOf(i));
        }
        map.put("G", list6);
        list7.clear();
        for(int i=1; i<=10; ++i)
        {
            list7.add(String.valueOf(i));
        }
        map.put("H", list7);
        list8.clear();
        for(int i=1; i<=8; ++i)
        {
            list8.add(String.valueOf(i));
        }
        list8.add("10");
        map.put("I", list8);
        list9.clear();
        list9.add("0");
        list9.add("1");
        map.put("J", list9);
        
        attributeIDList.add(0);
        attributeIDList.add(1);
        attributeIDList.add(2);
        attributeIDList.add(3);
        attributeIDList.add(4);
        attributeIDList.add(5);
        attributeIDList.add(6);
        attributeIDList.add(7);
        attributeIDList.add(8);
    }
    public static AttributeList getInstance() {
      if(instance == null) {
         instance = new AttributeList();
      }
      return instance;
   }
    public List<List<Attribute>> getRecords() {
        return records;
    }

    public List<List<Attribute>> getTest() {
        return test;
    }

    public void setTest(List<List<Attribute>> test) {
        this.test = test;
    }

    public void setRecords(List<List<Attribute>> records) {
        this.records = records;
    }
    public List<Integer> getAttributeIDList() {
        return attributeIDList;
    }
    public String[] getAttributeList() {
        return attributeList;
    }

    public Map<String, List<String>> getMap() {
        return map;
    }
}
