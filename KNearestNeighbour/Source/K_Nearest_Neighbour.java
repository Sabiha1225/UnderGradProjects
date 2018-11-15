/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package k_nearest_neighbour;

import java.util.List;
import java.util.Map;

/**
 *
 * @author Administrator
 */
public class K_Nearest_Neighbour {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        FileInputOutput f = FileInputOutput.getInstance();
        f.getData();
        Data data = Data.getInstance();
        Functions funct = Functions.getInstance();
        int counter;
        List<Document> list;
        //funct.createHamiltonFeatureVectorForTrainingData();
        /*
        funct.createHamiltonFeatureVectorForTestingData();
        funct.getHamiltonDistance();
        counter = 0;
        list = data.getTestDocList()
        for(int i= 0; i<list.size(); ++i)
        {
            Document doc1 = list.get(i);
            int id = doc1.getID();
            String topic = doc1.getTopic();
            //Map<String, Integer> map = doc.getMap();
            System.out.println(id+"  "+topic);
            System.out.println(doc1.getHamiltonOutput());
            if(topic.equals(doc1.getHamiltonOutput()))
                counter++;
            //System.out.println("Hamilton Count:   "+doc.getHamiltonCount()+"    Total Word Count:   "+doc.getMap().size());
            List<Neighbor> kNeighbor = doc1.getkNeighbor();
            for(int k=0; k<kNeighbor.size(); ++k)
            {
                System.out.println(kNeighbor.get(k).hamiltonDistance+"     "+kNeighbor.get(k).doc.getTopic()+"   "+kNeighbor.get(k).doc.getID());
            }
            
            System.out.println();
            System.out.println("---------------------------------------------------------------------------------------------");
            System.out.println("---------------------------------------------------------------------------------------------");
        }
        System.out.println(counter);
        System.out.println("Accuracy:  "+(counter*100)/list.size());
        */
        /*
        //Euclidean Distance
        funct.getEuclideanDistance();
        //list.clear();
        list = data.getTestDocList();
        counter=0;
        for(int i= 0; i<list.size(); ++i)
        {
            Document doc1 = list.get(i);
            int id = doc1.getID();
            String topic = doc1.getTopic();
            //Map<String, Integer> map = doc.getMap();
            System.out.println(id+"  "+topic);
            System.out.println(doc1.getEuclideanOutput());
            if(topic.equals(doc1.getEuclideanOutput()))
                counter++;
            //System.out.println("Hamilton Count:   "+doc.getHamiltonCount()+"    Total Word Count:   "+doc.getMap().size());
            List<Neighbor> kNeighbor = doc1.getkEuclideanNeighbor();
            for(int k=0; k<kNeighbor.size(); ++k)
            {
                System.out.println(kNeighbor.get(k).euclideanDistance+"     "+kNeighbor.get(k).doc.getTopic()+"   "+kNeighbor.get(k).doc.getID());
            }
            
            System.out.println();
            System.out.println("---------------------------------------------------------------------------------------------");
            System.out.println("---------------------------------------------------------------------------------------------");
        }
        System.out.println(counter);
        System.out.println((counter*100)/list.size());
        */ 
         
        // Cosine-Similarities
        funct.generateIDF();
        funct.getCosineSimilarities();
        
        list = data.getTestDocList();
        counter=0;
        for(int i= 0; i<list.size(); ++i)
        {
            Document doc1 = list.get(i);
            int id = doc1.getID();
            String topic = doc1.getTopic();
            //Map<String, Integer> map = doc.getMap();
            System.out.println(id+"  "+topic);
            System.out.println(doc1.getCosineOutput());
            if(topic.equals(doc1.getCosineOutput()))
                counter++;
            //System.out.println("Hamilton Count:   "+doc.getHamiltonCount()+"    Total Word Count:   "+doc.getMap().size());
            List<Neighbor> kNeighbor = doc1.getkCosineNeighbor();
            for(int k=0; k<kNeighbor.size(); ++k)
            {
                System.out.println(kNeighbor.get(k).cosineSimilarity+"     "+kNeighbor.get(k).doc.getTopic()+"   "+kNeighbor.get(k).doc.getID());
            }
            
            System.out.println();
            System.out.println("---------------------------------------------------------------------------------------------");
            System.out.println("---------------------------------------------------------------------------------------------");
        }
        System.out.println(counter);
        System.out.println((counter*100)/data.getTestDocCount());
        
    }
}
