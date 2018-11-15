/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package adaboost;

import java.util.ArrayList;
import java.util.List;
import java.util.Random;

/**
 *
 * @author Administrator
 */
public class AdaBoost {

    public static int randomVary = 130;
    public static int dataSize = 0;
    public static int testDataSize = 0;
    public static int noOfAttributes = 10;
    public static List<List<Attribute>> records;
    public static List<List<Attribute>> test;
    public static int K = 10;
    public static double threshold = 0.5;
    private static AdaBoost instance = null;
    public static AdaBoost getInstance() {
      if(instance == null) {
         instance = new AdaBoost();
      }
      return instance;
    }
    public static void main(String[] args) {
        Attribute att;
        AttributeList al = AttributeList.getInstance();
        FileInputOutput file = FileInputOutput.getInstance();
        records = new ArrayList<List<Attribute>>();
        test = new ArrayList<List<Attribute>>();
        double threshold1 = 1.0;
        double error=0.0;
        
        file.getRecords();
        records = al.getRecords();
        test = al.getTest();
        
        List<Tree> treeList = new ArrayList<Tree>();
        double [] beta = new double[K];
        
        probWraperInitialization();
        subProbWraperInitialization();
        
        List<WeightInfo> probabilityWraper1 = al.getProbabilityWraper();
        List<WeightInfo> subProbabilityWraper1 = al.getSubProbabilityWraper();
        List<List<Attribute>> subsetOfRecords = al.getSubsetOfRecords();
        for(int i=0; i<K; ++i)
        {
            Tree t1 = new Tree();
            t1.createTree(al.getSubsetOfRecords());
            t1.printTree();
            System.out.println("%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%");
        
            error = calculateError(); 
            System.out.println(error);
            if(error >threshold1)
            {
                break;
            }
            treeList.add(t1);
            beta[i] = error/(1-error);
            weightRecalculate(beta[i]);
            updateMainProbabilityWraper();
            updateSubProWraper();
            updateProbability();
        }
        
        List<Attribute> list = new ArrayList<Attribute>();
        int counter = 0;
        for(int i=0; i<test.size(); ++i)
        {
            System.out.println("#####################################################################");
            double [] classLabel = new double[3];
            classLabel[0] = 0.0;
            classLabel[1] = 0.0;
            classLabel[2] = 0.0;
            
            list =  test.get(i);
            att = list.get(9);
            System.out.println(att.value);
            
            for(int j=0; j<treeList.size(); ++j)
            {
                //System.out.println("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^"+"TreeID: "+j+"^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^");
                treeList.get(j).traverseTree(list);
                if(treeList.get(j).foundFalse==1)
                {
                    classLabel[0] += Math.log(1.0/beta[j]);
                    //System.out.println("Found but false");
                }
                if(treeList.get(j).foundTrue==1)
                {
                    classLabel[1] += Math.log(1.0/beta[j]);
                    //System.out.println("Found but true");
                }
                if(treeList.get(j).foundOther==1)
                {
                    classLabel[2] += Math.log(1.0/beta[j]);
                    //System.out.println("Found but 77");
                }
                if(treeList.get(j).notFound==1)
                {
                    classLabel[2] += Math.log(1.0/beta[j]);
                    //System.out.println("Not Found");
                }
            }
            double max=0;
            int index=0;
            for(int g=0; g<3; ++g)
            {
                if(classLabel[g]>max)
                {
                    max = classLabel[g];
                    index = g;
                }
            }
            System.out.println(index);
            if(Integer.parseInt(att.value) == index)
                counter++;
        }
        System.out.println("::::::::::::::::::::::::::::"+counter+"::::::::::::::::::::::::::::::::::::::::::::");
        System.out.println("Accuracy:  "+(counter*100.0)/test.size());
    }
    
    public static void updateProbability()
    {
        AttributeList al = AttributeList.getInstance();
        double sum=0.0;
        for(int i=0; i<al.getSubProbabilityWraper().size(); ++i)
        {
            sum += al.getSubProbabilityWraper().get(i).weight;
        }
        
        for(int i=0; i<al.getSubProbabilityWraper().size(); ++i)
        {
            al.getSubProbabilityWraper().get(i).probability = al.getSubProbabilityWraper().get(i).weight/sum;
            al.getProbabilityWraper().get(al.getSubProbabilityWraper().get(i).recordID).probability = al.getSubProbabilityWraper().get(i).weight/sum;
        }
        al.setSubProbWeight(sum);
    }
    
    public static void updateMainProbabilityWraper()
    {
        AttributeList al = AttributeList.getInstance();
        for(int i=0; i<al.getSubProbabilityWraper().size(); ++i)
        {
            int index = al.getSubProbabilityWraper().get(i).recordID;
            al.getProbabilityWraper().get(index).found = al.getSubProbabilityWraper().get(i).found;
            al.getProbabilityWraper().get(index).probability = al.getSubProbabilityWraper().get(i).probability;
            al.getProbabilityWraper().get(index).weight = al.getSubProbabilityWraper().get(i).weight;
        }
    }
    
    public static void weightRecalculate(double beta)
    {
        AttributeList al = AttributeList.getInstance();
        for(int i=0; i<al.getSubProbabilityWraper().size(); ++i)
        {
            if(al.getSubProbabilityWraper().get(i).found == 1)
            {
                double w = al.getSubProbabilityWraper().get(i).weight;
                al.getSubProbabilityWraper().get(i).weight = w*beta;
            }
        }
    }
    
    public static double calculateError()
    {
        double error = 0.0;
        AttributeList al = AttributeList.getInstance();
        for(int i=0; i<al.getSubProbabilityWraper().size(); ++i)
        {
            if(al.getSubProbabilityWraper().get(i).found == 0)
            {
                error += al.getSubProbabilityWraper().get(i).probability;
            }
        }
        return error;
    }
    
    public static void probWraperInitialization()
    {
        AttributeList al = AttributeList.getInstance();
        List<WeightInfo> probabilityWraper = new ArrayList<WeightInfo>();
        double probWeight=0, subProbWeight=0;
        for(int i=0; i<records.size(); ++i)
        {
            WeightInfo wi = new WeightInfo();
            
            wi.recordID = i;
            wi.weight = 1.0/records.size();
            wi.probability = 0.0;
            wi.found = 0;
            wi.trainingListPresent = 0;
            if(i<al.wraperSize)
                probWeight += wi.weight;
            
            probabilityWraper.add(wi);
        }
        al.setProbabilityWraper(probabilityWraper);
        al.setProbWeight(probWeight);
    }
    
    public static void subProbWraperInitialization()
    {
        Random random = new Random();
        AttributeList al = AttributeList.getInstance();
        List<List<Attribute>> records = al.getRecords();
        
        List<WeightInfo> subProbabilityWraper = new ArrayList<WeightInfo>();
        List<Attribute> list = new ArrayList<Attribute>();
        List<List<Attribute>> subsetOfRecords = new ArrayList<List<Attribute>>();
        
        double probWeight=0, subProbWeight=0;
        int size = records.size();
        for (int i = 0; i < al.wraperSize; i++) {
            int index = -1, r = random.nextInt(size--) + 1;
            for(int j=0; j<r; ++j)
            {
                index++;
                while(al.getProbabilityWraper().get(index).trainingListPresent==1)
                {
                    index++;
                }
            }
            list = records.get(index);
            subsetOfRecords.add(new ArrayList<Attribute>());
            subsetOfRecords.get(i).addAll(list);
            
            WeightInfo wi = al.getProbabilityWraper().get(index);
            wi.trainingListPresent = 1;
            al.getProbabilityWraper().get(index).trainingListPresent = 1;
            wi.probability = wi.weight/al.probWeight;
            al.getProbabilityWraper().get(index).probability = wi.probability;
            
            subProbWeight += wi.weight;
            
            subProbabilityWraper.add(wi);
        }
        al.setSubProbWeight(subProbWeight);
        al.setSubProbabilityWraper(subProbabilityWraper);
        al.setSubsetOfRecords(subsetOfRecords);
        getEmptyList();
    }
    public static void getEmptyList()
    {
        AttributeList al = AttributeList.getInstance();
        List<WeightInfo> emptyList = new ArrayList<WeightInfo>();
        for(int i=0; i<al.getProbabilityWraper().size(); ++i)
        {
            if(al.getProbabilityWraper().get(i).trainingListPresent == 0)
            {
                WeightInfo w = al.getProbabilityWraper().get(i);
                emptyList.add(w);
            }
        }
        al.setEmptyList(emptyList);
    }
    public static void updateSubProWraper()
    {
        AttributeList al = AttributeList.getInstance();
        List<WeightInfo> probabilityWraper1 = al.getProbabilityWraper();
        List<WeightInfo> subProbabilityWraper1 = al.getSubProbabilityWraper();
        List<List<Attribute>> records = al.getRecords();
        List<WeightInfo> emptyList = al.getEmptyList();
        
        int[] changeProbIndex = new int[randomVary];
        
        Random random1 = new Random();
        Random random2 = new Random();
        int size1 = subProbabilityWraper1.size();
        int size2 = emptyList.size();
        
        for(int i=0; i<randomVary; ++i)
        {
            int r = random1.nextInt(size1);
            changeProbIndex[i] = al.getSubProbabilityWraper().get(r).recordID;
            al.getSubProbabilityWraper().remove(r);
            al.getSubsetOfRecords().remove(r);
            
            int index = -1, r1 = random2.nextInt(size2--) + 1;
            for(int j=0; j<r1; ++j)
            {
                index++;
                while(emptyList.get(index).trainingListPresent==1)
                {
                    index++;
                }
            }
            WeightInfo wi = emptyList.get(index);
            emptyList.get(index).trainingListPresent = 1;
            wi.trainingListPresent = 1;
            al.getProbabilityWraper().get(emptyList.get(index).recordID).trainingListPresent = 1;
            al.getSubProbabilityWraper().add(wi);
            List<Attribute> list = new ArrayList<Attribute>();
            list = al.getRecords().get(emptyList.get(index).recordID);
            int s = al.getSubsetOfRecords().size();
            al.getSubsetOfRecords().add(new ArrayList<Attribute>());
            al.getSubsetOfRecords().get(s).addAll(list);
        }
        
        for(int i=0; i<randomVary; ++i)
        {
            al.getProbabilityWraper().get(changeProbIndex[i]).trainingListPresent = 0;
        }
        getEmptyList();
    }
    
    
}
