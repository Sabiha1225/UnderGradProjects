/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package bisecting_k_means;

import java.util.ArrayList;
import java.util.List;

/**
 *
 * @author Administrator
 */
public class Bisecting_K_means {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        FileInputOutput f = FileInputOutput.getInstance();
        f.getData();
        Data data = Data.getInstance();
        data.K = 2;
        K_Means kmeans = K_Means.getInstance();
        List<Point> pointList = data.getPointList();
        kmeans.initializeDataPoints(pointList);
        //kmeans.printDataPoints();
        //System.out.println(data.K);
        
        //System.out.println(data.K);
        kmeans.runAlgorithm();
        
        List<Cluster> clList = data.getClusterList();
        List<Cluster> finalClusterList = new ArrayList<Cluster>();
        for(int i=0; i<clList.size(); ++i)
        {
            finalClusterList.add(clList.get(i));
        }
        data.K = 2;
        while(finalClusterList.size() < data.finalKValue)
        {
            int index = findMaxErrorCluster(finalClusterList);
            data.getClusterList().clear();
            kmeans.initializeDataPoints(finalClusterList.get(index).getMemeberPoints());
            kmeans.runAlgorithm();
            finalClusterList.remove(index);
            for(int j=0; j<data.getClusterList().size(); ++j)
            {
                finalClusterList.add(data.getClusterList().get(j));
            }
        }
        
        if(finalClusterList.size()>data.finalKValue)
        {
            for(int i=0; i<finalClusterList.size()-data.finalKValue; ++i)
            {
                finalClusterList.remove(finalClusterList.size()-1);
            }
        }
        
        for(int i=0; i<finalClusterList.size(); ++i)
        {
            Cluster c = finalClusterList.get(i);
            
            System.out.println(c.getId()+"               "+c.getMean().x+"           "+c.getMean().y);
            List<Point> pList = c.getMemeberPoints();
            for(int j=0; j<pList.size(); ++j)
            {
                System.out.println(pList.get(j).id+"       "+pList.get(j).x+"          "+pList.get(j).y);
            }
            System.out.println("%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%");
        }
        
    }
    
    public static int findMaxErrorCluster(List<Cluster> finalClusterList)
    {
        K_Means kmean = K_Means.getInstance();
        
        double max = 0;
        int index = 0;
        for(int i=0; i<finalClusterList.size(); ++i)
        {
            double sum = 0;
            Point mean = finalClusterList.get(i).getMean();
            List<Point> memeberPoints = finalClusterList.get(i).getMemeberPoints();
            for(int j=0; j<memeberPoints.size(); ++j)
            {
                sum += kmean.getEuclideanDistance(memeberPoints.get(j), mean);
            }
            if(sum>max)
            {
                max = sum;
                index = i;
            }
        }
        return index;
    }
}
