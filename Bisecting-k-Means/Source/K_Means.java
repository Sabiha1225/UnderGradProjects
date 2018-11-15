/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package bisecting_k_means;

import java.util.ArrayList;
import java.util.List;
import java.util.Random;

/**
 *
 * @author Administrator
 */
public class K_Means {
    
    private int noOfIteration=100;
    Random random = new Random();
    
    private static K_Means instance = null;
    public static K_Means getInstance() {
      if(instance == null) {
         instance = new K_Means();
      }
      return instance;
    }
    Data data = Data.getInstance();
    //List<Point> allPoints = data.getPointList();
    List<Point> allPoints;
    void initializeDataPoints(List<Point> points)
    {
        allPoints = points;
    }
    void printDataPoints()
    {
        for(int j=0; j<allPoints.size(); ++j)
        {
                System.out.println(allPoints.get(j).id+"       "+allPoints.get(j).x+"          "+allPoints.get(j).y);
        }
    }
    void initializeClusterList()
    {
        List<Cluster> clusterList = new ArrayList<Cluster>();
        List<Point> kRandomPoints = getRandomCentroid();
        for(int i=0; i<data.K; ++i)
        {
            Cluster cl = new Cluster();
            cl.setId(i+1);
            cl.setMean(kRandomPoints.get(i));
            clusterList.add(cl);
        }
        data.setClusterList(clusterList);
    }
    
    List<Point> getRandomCentroid()
    {
        List<Point> kRandomPoints = new ArrayList<Point>();
        //boolean[] alreadyChosen = new boolean[data.getPointCounts()];
        boolean[] alreadyChosen = new boolean[allPoints.size()];
        //int size = data.getPointCounts();
        int size = allPoints.size();
        
        for (int i = 0; i < data.K; i++) {
            int index = -1, r = random.nextInt(size--) + 1;
            for (int j = 0; j < r; j++) {
                index++;
                while (alreadyChosen[index])
                    index++;
            }
            kRandomPoints.add(allPoints.get(index));
            alreadyChosen[index] = true;
        }
        return kRandomPoints;
    }
    
    double getEuclideanDistance(Point p1, Point p2)
    {
        return ((p1.x-p2.x)*(p1.x-p2.x)) + ((p1.y-p2.y)*(p1.y-p2.y));
    }
    
    void runAlgorithm()
    {
        int loopCounter = 0;
        
        //Step 1
        initializeClusterList();
        
        while(true)
        {
            //Step 2
            clearMemberPointsOfCluster();
            //for(int i=0; i<data.getPointCounts(); ++i)
            for(int i=0; i<allPoints.size(); ++i)
            {
                double min = Double.MAX_VALUE;
                int clusterIndex=0;
                for(int j=0; j<data.K; ++j)
                {
                    double euclideanDistance = getEuclideanDistance(allPoints.get(i), data.getClusterList().get(j).getMean());
                    if(min>euclideanDistance)
                    {
                        min = euclideanDistance;
                        clusterIndex = j;
                    }
                }
                data.getClusterList().get(clusterIndex).getMemeberPoints().add(allPoints.get(i));
                allPoints.get(i).clusterID = clusterIndex;
            }
            
            //Step 3
            reCalculateCentreOfClusters();
            
            //Step 4
            
            int counter = 0;
            //for(int i=0; i<data.getPointCounts(); ++i)
            for(int i=0; i<allPoints.size(); ++i)
            {
                double min = Double.MAX_VALUE;
                int clusterIndex=0;
                for(int j=0; j<data.K; ++j)
                {
                    double euclideanDistance = getEuclideanDistance(allPoints.get(i), data.getClusterList().get(j).getMean());
                    if(min>euclideanDistance)
                    {
                        min = euclideanDistance;
                        clusterIndex = j;
                    }
                }
            
                if(allPoints.get(i).clusterID != clusterIndex)
                    counter++;
            }
            if(counter == 0)
                break;
            loopCounter++;
        }
        System.out.println(loopCounter);
    }
    
    void clearMemberPointsOfCluster()
    {
        for(int i=0; i<data.getClusterList().size(); ++i)
        {
            if(!data.getClusterList().get(i).getMemeberPoints().isEmpty())
            {
                data.getClusterList().get(i).getMemeberPoints().clear();
            }
        }
    }
    void reCalculateCentreOfClusters()
    {
        for(int i=0; i<data.K; ++i)
        {
            List<Point> pList = data.getClusterList().get(i).getMemeberPoints();
            double newX=0.0, newY=0.0;
            for(int j=0; j<pList.size(); ++j)
            {
                newX += pList.get(j).x ;
                newY += pList.get(j).y ;
            }
            Point p = new Point();
            p.x = newX / pList.size();
            p.y = newY / pList.size();
            data.getClusterList().get(i).setMean(p);
            //data.getClusterList().get(i).getMemeberPoints().clear();
        }
    }
}
