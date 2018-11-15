
package adaboost;

import java.util.ArrayList;
import java.util.List;
import java.util.Map;

/**
 *
 * @author Administrator
 */
public class Tree {
    Node root;
    AttributeList al=AttributeList.getInstance();
    String [] attrName;
    Entropy et = Entropy.getInstance();
    public int foundFalse;
    public int foundTrue;
    public int foundOther;
    public int notFound;
    public int truePositive=0;
    public int trueNegative=0;
    public int falsePositive=0;
    public int falseNegative=0;
    public double maxGain;
    
    List<WeightInfo> subProbabilityWraper;
    /*private static Tree instance = null;
    public static Tree getInstance() {
      if(instance == null) {
         instance = new Tree();
      }
      return instance;
   }*/
    public Tree()
    {
    }
    public void createTree(List<List<Attribute>> records)
    {
        int depth=0;
        attrName = al.getAttributeList();
        root = decisionTreeLearning(records,al.getAttributeIDList(), null, depth);
    }
    public Node decisionTreeLearning(List<List<Attribute>> records, List<Integer> attributeIDList, Node parentNode, int depth) 
    {
        Attribute at = new Attribute();
        Node test = new Node(records, attributeIDList);
        test.setParent(parentNode);
        
        if(positiveCheck(records) && (parentNode != null))
        {
            at.setLabel("1");
            test.setAtt(at);
            for(int i=0; i<subProbabilityWraper.size(); ++i)
            {
                subProbabilityWraper.get(i).found = 1;
                for(int j=0; j<al.subProbabilityWraper.size(); ++j)
                {
                    if(subProbabilityWraper.get(i).recordID == al.subProbabilityWraper.get(j).recordID)
                        al.subProbabilityWraper.get(j).found = 1;
                }
            }
            return test;
        }
        if(negativeCheck(records) && (parentNode != null))
        {
            at.setLabel("0");
            test.setAtt(at);
            for(int i=0; i<subProbabilityWraper.size(); ++i)
            {
                subProbabilityWraper.get(i).found = 1;
                for(int j=0; j<al.subProbabilityWraper.size(); ++j)
                {
                    if(subProbabilityWraper.get(i).recordID == al.subProbabilityWraper.get(j).recordID)
                        al.subProbabilityWraper.get(j).found = 1;
                }
            }
            return test;
        }
        if(isEmptyAttributeList(attributeIDList)|| isEmptyRecords(records))
        {
            at.setLabel("77");
            test.setAtt(at);
            return test;
        }
        if(depth==1)
        {
            at.setLabel("1000");
            test.setAtt(at);
            return test;
        }
        int bestAttributeId = bestAttribute(records, attributeIDList);
        at.setAttributeName(attrName[bestAttributeId]);
        at.setAttributeID(bestAttributeId);
        test.setAtt(at);
        test.setMaxGain(maxGain);
        System.out.println("Root-- Max Gain: "+test.getMaxGain()+" Attribute Name: "+at.getAttributeName()+" Value: "+at.getValue());
        System.out.println("Root-- list: "+test.getSubAttributeIDList());
        Map<String, List<String>> map = al.getMap();
        List<String> valueList = map.get(attrName[bestAttributeId]);
        List<Node> rootChildren = new ArrayList<Node>();
        
        test.childrenSize = valueList.size();
        List<List<Attribute>> subRecords=null;
        List<Integer> subAttIDList = null;
        for(int i=0; i<valueList.size(); ++i)
        {
            Attribute child = new Attribute();
            String s = valueList.get(i);
            Node vola1 = new Node();
            
            vola1.setParent(test);
            child.setAttributeName(attrName[bestAttributeId]);
            child.setAttributeID(bestAttributeId);
            child.setValue(s);
            subRecords = getSubsetOfRecords(records, s, bestAttributeId);
            
            vola1.setSubRecords(subRecords);
            if(subRecords.isEmpty())
            {
                child.setLabel("77");
                vola1.setAtt(child);
                
            }
            else
            {
                
                vola1.setAtt(child);
                subAttIDList = getSubsetOfAttributes(attributeIDList, bestAttributeId);
                
                vola1.setSubAttributeIDList(subAttIDList);
                
                System.out.println("Children-- Max Gain: "+vola1.getMaxGain()+" Attribute Name: "+child.getAttributeName()+" Value: "+child.getValue());
                System.out.println("Children-- list: "+vola1.getSubAttributeIDList());
                List<Node> rootChildrenChildren = new ArrayList<Node>();
                Node vola2;
                
                vola2 = decisionTreeLearning(subRecords, subAttIDList, vola1, depth+1);
                vola1.setChildrenSize(1);
                rootChildrenChildren.add(vola2);
                vola1.setChildren1(rootChildrenChildren);
                rootChildren.add(vola1);
                //test.children[i].childrenSize=1;
                Attribute child1 = new Attribute();
                child1 = vola2.getAtt();
                
                System.out.println("ChildrenChildren-- Max Gain: "+vola2.getMaxGain()+" Attribute Name: "+child1.getAttributeName()+" Value: "+child1.getValue()+" Label: "+child1.getLabel());
                System.out.println("ChildrenChildren-- list: "+vola2.getSubAttributeIDList());
            }
        }
        test.setChildren1(rootChildren);
        return test;
    }

    public boolean positiveCheck(List<List<Attribute>> records)
    {
        int size = records.size();
        int posCount=0;
        for(int i=0; i<records.size(); ++i)
        {
            if(records.get(i).get(9).getValue().equals("1"))
                posCount++;
        }
        if(posCount==size)
            return true;
        else
            return false;
    }

    public boolean negativeCheck(List<List<Attribute>> records)
    {
        int size = records.size();
        int negCount=0;
        for(int i=0; i<records.size(); ++i)
        {
            if(records.get(i).get(9).getValue().equals("0"))
                negCount++;
        }
        if(negCount==size)
            return true;
        else
            return false;
    }

    public boolean isEmptyAttributeList(List<Integer> list)
    {
        if(list.isEmpty())
            return true;
        else
            return false;
    }
    public boolean isEmptyRecords(List<List<Attribute>> records)
    {
        if(records.isEmpty())
            return true;
        else
            return false;
    }

    public int bestAttribute(List<List<Attribute>> records, List<Integer> attList)
    {
        double gain=0;
        int attributeID=0, totalRow=0;
        double entropy = et.getEntropy(records);
        totalRow = et.totalCount;
        this. maxGain=0;
        for(int i=0; i<attList.size() ; ++i)
        {
            gain = et.getGain(entropy, totalRow, attList.get(i), records);
            if(gain>maxGain)
            {
                this.maxGain = gain;
                attributeID = attList.get(i);
            }
        }
        return attributeID;
   }

    public List<List<Attribute>> getSubsetOfRecords(List<List<Attribute>> records, String value, int attributeID)
    {
        subProbabilityWraper = new ArrayList<WeightInfo>();
        List<Attribute> list = new ArrayList<Attribute>();
        List<List<Attribute>> subsetOfRecords = new ArrayList<List<Attribute>>();
        int j=0;
        for(int i=0; i<records.size(); ++i)
        {
            if(records.get(i).get(attributeID).getValue().equals(value))
            {
                list = records.get(i);
                subsetOfRecords.add(new ArrayList<Attribute>());
                subsetOfRecords.get(j).addAll(list);
                WeightInfo w = al.subProbabilityWraper.get(i);
                subProbabilityWraper.add(w);
                j++;
                
            }
        }
        return subsetOfRecords;
    }

    public List<Integer> getSubsetOfAttributes(List<Integer> list,int attributeId)
    {
        List<Integer> subSet = new ArrayList<Integer>();
        
        for(int i=0; i<list.size(); ++i)
        {
            if(list.get(i)!=attributeId)
            {
                subSet.add(list.get(i));
            }
        }
        return subSet;
    }

    public void printTree(){
        System.out.println();
        System.out.println();
        System.out.println();
        System.out.println();
        System.out.println("-------------------------------Inside Print----------------------------------------------");
        printDecisionTree(root);
    }

    public void printDecisionTree(Node root)
    {
        Attribute at = new Attribute();
        Attribute child = new Attribute();
        at = root.getAtt();
        System.out.println("Root --- Value: "+at.getValue()+" AttName: "+at.getAttributeName()+" Label: "+at.getLabel()+" Max Gain: "+root.getMaxGain());
        if(at.getLabel()!=null && at.getLabel().equals("0"))
            return;
        if(at.getLabel()!=null && at.getLabel().equals("1"))
            return;
        if(at.getLabel()!=null && at.getLabel().equals("77"))
            return;
        if(at.getLabel()!=null && at.getLabel().equals("1000"))
            return;
        System.out.println(root.getChildrenSize());
        List<Node> list = root.getChildren();
        
        for(int i=0; i<list.size(); ++i)
        {
            Node n = list.get(i);
            child = n.getAtt();
            System.out.println("Children --- Value: "+child.getValue()+" AttName: "+child.getAttributeName()+" Label: "+child.getLabel()+" Max Gain: "+n.getMaxGain());
            List<Node> t = n.getChildren();
            
            printDecisionTree(t.get(0));
        }
    }
    public void traverseTree(List<Attribute> list)
    {
        foundFalse=0;
        foundTrue=0;
        foundOther=0;
        notFound=1;
        traverseTree1(root, list);
        
    }
    public void traverseTree1(Node root, List<Attribute> list)
    {
        Attribute at = new Attribute();
        Attribute child = new Attribute();
        at = root.getAtt();
        //System.out.println("Root --- Value: "+at.getValue()+" AttName: "+at.getAttributeName()+" Label: "+at.getLabel()+" AttributeID: "+at.getAttributeID()+" Max Gain: "+root.getMaxGain());
        if(at.getLabel()!=null && at.getLabel().equals("0"))
        {
            Attribute test = new Attribute();
            test = list.get(9);
            if(test.getValue().equals("0"))
            {
                trueNegative++;
            }
            else if(test.getValue().equals("1"))
            {
                falseNegative++;
            }
            foundFalse = 1;
            notFound=0;
            return;
        }
        if(at.getLabel()!=null && at.getLabel().equals("1"))
        {
            Attribute test = new Attribute();
            test = list.get(9);
            if(test.getValue().equals("0"))
            {
                falsePositive++;
            }
            else if(test.getValue().equals("1"))
            {
                truePositive++;
            }
            foundTrue = 1;
            notFound=0;
            return;
        }
        if(at.getLabel()!=null && at.getLabel().equals("77"))
        {
            foundOther = 1;
            notFound=0;
            return;
        }
        if(at.getLabel()!=null && at.getLabel().equals("1000"))
        {
            notFound=1;
            return;
        }
        List<Node> ch = root.getChildren();
        int attID = at.getAttributeID();
        Attribute atList = list.get(attID);
        //System.out.println(atList.getValue());
        for(int i=0; i<ch.size(); ++i)
        {
            Node n = ch.get(i);
            child = n.getAtt();
            //System.out.println("Children --- Value: "+child.getValue()+" AttName: "+child.getAttributeName()+" Label: "+child.getLabel()+" Max Gain: "+n.getMaxGain());
            if(child.getValue().equals(atList.getValue()))
            {
                
                List<Node> t = n.getChildren();            
                traverseTree1(t.get(0), list);
            }
        }
    }

}
