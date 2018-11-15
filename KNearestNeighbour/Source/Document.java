package k_nearest_neighbour;

//package naivebyesclassifierfortext;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

/**
 *
 * @author Administrator
 */
public class Document {
    private int ID;
    private String topic;
    private Map<String, Integer> map;
    private int totalWord;
    
    private int[] hamiltonFeatureVector;
    private int hamiltonCount;
    private List<Neighbor> kNeighbor;
    private String hamiltonOutput;
    
    private int[] euclideanFeatureVector;
    private int euclideanCount;
    private List<Neighbor> kEuclideanNeighbor;
    private String euclideanOutput;
    
    private List<Neighbor> kCosineNeighbor;
    private String cosineOutput;
    
    public Document() {
        this.ID = 0;
        this.topic=null;
        totalWord=0;
        map = new HashMap<String, Integer>();
        kNeighbor =  new ArrayList<Neighbor>();
        kEuclideanNeighbor = new ArrayList<Neighbor>();
    }
    
    public void setID(int ID) {
        this.ID = ID;
    }

    public void setTotalWord(int totalWord) {
        this.totalWord = totalWord;
    }
    
    public void setTopic(String topic) {
        this.topic = topic;
    }

    public void setMap(Map<String, Integer> map) {
        this.map = map;
    }

    public void setHamiltonFeatureVector(int[] hamiltonFeatureVector, int length) {
        //hamiltonFeatureVector = new int[length];
        this.hamiltonFeatureVector = hamiltonFeatureVector;
    }

    public void setHamiltonCount(int hamiltonCount) {
        this.hamiltonCount = hamiltonCount;
    }

    public void setkNeighbor(List<Neighbor> kNeighbor) {
        this.kNeighbor = kNeighbor;
    }

    public void setHamiltonOutput(String hamiltonOutput) {
        this.hamiltonOutput = hamiltonOutput;
    }

    public void setEuclideanFeatureVector(int[] euclideanFeatureVector) {
        this.euclideanFeatureVector = euclideanFeatureVector;
    }

    public void setEuclideanCount(int euclideanCount) {
        this.euclideanCount = euclideanCount;
    }

    public void setkEuclideanNeighbor(List<Neighbor> kEuclideanNeighbor) {
        this.kEuclideanNeighbor = kEuclideanNeighbor;
    }

    public void setEuclideanOutput(String euclideanOutput) {
        this.euclideanOutput = euclideanOutput;
    }

    public void setkCosineNeighbor(List<Neighbor> kCosineNeighbor) {
        this.kCosineNeighbor = kCosineNeighbor;
    }

    public void setCosineOutput(String cosineOutput) {
        this.cosineOutput = cosineOutput;
    }

    public List<Neighbor> getkCosineNeighbor() {
        return kCosineNeighbor;
    }

    public String getCosineOutput() {
        return cosineOutput;
    }
    
    public int[] getEuclideanFeatureVector() {
        return euclideanFeatureVector;
    }

    public int getEuclideanCount() {
        return euclideanCount;
    }

    public List<Neighbor> getkEuclideanNeighbor() {
        return kEuclideanNeighbor;
    }

    public String getEuclideanOutput() {
        return euclideanOutput;
    }
    
    public String getHamiltonOutput() {
        return hamiltonOutput;
    }
    
    public List<Neighbor> getkNeighbor() {
        return kNeighbor;
    }
    
    public int[] getHamiltonFeatureVector() {
        return hamiltonFeatureVector;
    }

    public int getHamiltonCount() {
        return hamiltonCount;
    }
    
    public int getID() {
        return ID;
    }

    public int getTotalWord() {
        return totalWord;
    }
    
    public String getTopic() {
        return topic;
    }

    public Map<String, Integer> getMap() {
        return map;
    }
    
}
