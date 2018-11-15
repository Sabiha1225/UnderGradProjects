/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package k_nearest_neighbour;

/**
 *
 * @author Administrator
 */
public class Neighbor {
    public int hamiltonDistance;
    public double euclideanDistance;
    public double cosineSimilarity;
    public Document doc;

    public Neighbor() {
        hamiltonDistance = 0;
        euclideanDistance=0.0;
        cosineSimilarity = 0.0;
        doc = new Document();
    }
}
