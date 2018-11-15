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
public class Cluster {
    private int id;
    private Point mean;
    private List<Point> memeberPoints;
    
    public Cluster()
    {
        id = 0;
        mean = new Point();
        memeberPoints = new ArrayList<Point>();
    }

    public void setId(int id) {
        this.id = id;
    }

    public void setMean(Point mean) {
        this.mean = mean;
    }

    public void setMemeberPoints(List<Point> memeberPoints) {
        this.memeberPoints = memeberPoints;
    }

    public int getId() {
        return id;
    }

    public Point getMean() {
        return mean;
    }

    public List<Point> getMemeberPoints() {
        return memeberPoints;
    }
    
}
