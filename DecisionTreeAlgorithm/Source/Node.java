
package id3final;

import java.util.ArrayList;
import java.util.List;

/**
 *
 * @author Administrator
 */
public class Node {
    private Node parent;
    
    public List<Node> children;
    public int childrenSize;
    private Attribute att;
    private List<List<Attribute>> subRecords = new ArrayList<List<Attribute>>();
    private List<Integer> subAttributeIDList = new ArrayList<Integer>();
    private double maxGain;
    
    public Node(List<List<Attribute>> records, List<Integer> attributeIDList)
    {
        this.parent = null;
        this.children = new ArrayList<Node>();
        this.subRecords = records;
        this.subAttributeIDList = attributeIDList;
        this.att = null;
        this.maxGain=0.0;
        this.childrenSize = 0;
    }
    public Node()
    {
        this.parent = null;
        this.children = new ArrayList<Node>();
        this.subRecords = null;
        this.subAttributeIDList = null;
        this.att = null;
        this.maxGain=0.0;
        this.childrenSize = 0;
    }

    public void setChildrenSize(int childrenSize) {
        this.childrenSize = childrenSize;
    }

    public int getChildrenSize() {
        return childrenSize;
    }

    public void setSubAttributeIDList(List<Integer> subAttributeIDList) {
        this.subAttributeIDList = subAttributeIDList;
    }

    public void setMaxGain(double maxGain) {
        this.maxGain = maxGain;
    }

    public void setParent(Node parent) {
        this.parent = parent;
    }

    public void setChildren(Node children) {
        this.children.add(children);
    }
    public void setChildren1(List<Node> children) {
        this.children=children;
    }

    public void setAtt(Attribute att) {
        this.att = att;
    }

    public void setSubRecords(List<List<Attribute>> subRecords) {
        this.subRecords = subRecords;
    }
    
    public Node getParent() {
        return parent;
    }

    public List<Node> getChildren() {
        return children;
    }

    public Attribute getAtt() {
        return att;
    }

    public List<List<Attribute>> getSubRecords() {
        return subRecords;
    }
    public List<Integer> getSubAttributeIDList() {
        return subAttributeIDList;
    }

    public double getMaxGain() {
        return maxGain;
    }
}
