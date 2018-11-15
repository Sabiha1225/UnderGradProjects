package bisecting_k_means;

//package naivebyesclassifierfortext;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

/**
 *
 * @author Administrator
 */
public class Data {

    private List<Point> pointList;
    private int pointCounts;
    private List<Cluster> clusterList;
    private List<Cluster> finalClusterList;
    public int K;
    public int finalKValue = 12;
    
    private static Data instance = null;
    public static Data getInstance() {
      if(instance == null) {
         instance = new Data();
      }
      return instance;
    }

    public Data() {
        pointCounts = 0;
        pointList = new ArrayList<Point>();
        clusterList = new ArrayList<Cluster>();
        finalClusterList = new ArrayList<Cluster>();
    }

    public void setPointList(List<Point> pointList) {
        this.pointList = pointList;
    }

    public void setPointCounts(int pointCounts) {
        this.pointCounts = pointCounts;
    }

    public void setClusterList(List<Cluster> clusterList) {
        this.clusterList = clusterList;
    }

    public void setFinalClusterList(List<Cluster> finalClusterList) {
        this.finalClusterList = finalClusterList;
    }

    public List<Cluster> getFinalClusterList() {
        return finalClusterList;
    }
    
    public List<Cluster> getClusterList() {
        return clusterList;
    }
    
    public List<Point> getPointList() {
        return pointList;
    }

    public int getPointCounts() {
        return pointCounts;
    }
    
    
}
