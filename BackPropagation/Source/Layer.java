package backpropagation;

import java.util.ArrayList;
import java.util.List;

/**
 *
 * @author Administrator
 */
public class Layer {
    List<Node> nodes;
    private int noOfNodes;
    
    public Layer(int noOfNodes) {
        this.noOfNodes = noOfNodes;
        nodes = new ArrayList<Node>();
    }
    
    public Layer() {
        this.noOfNodes = 0;
        nodes = new ArrayList<Node>();
    }

    public void setNodes(List<Node> nodes) {
        this.nodes = nodes;
    }

    public void setNoOfNodes(int noOfNodes) {
        this.noOfNodes = noOfNodes;
    }

    public List<Node> getNodes() {
        return nodes;
    }

    public int getNoOfNodes() {
        return noOfNodes;
    }
    
}
