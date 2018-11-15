
package adaboost;

/**
 *
 * @author Administrator
 */
public class Attribute {
    String value;
    String attributeName;
    String label;
    int attributeID;

    public Attribute(String value, String attributeName, int attributeID) {
        this.value = value;
        this.attributeName = attributeName;
        this.attributeID = attributeID;
    }
    public Attribute(String value, String attributeName, String label,int attributeID) {
        this.value = value;
        this.attributeName = attributeName;
        this.attributeID = attributeID;
        this.label = label;
    }

    Attribute() {
        value = null;
        attributeName = null;
        attributeID = -1;
        label = null;
    }

    public void setValue(String value) {
        this.value = value;
    }

    public void setAttributeName(String attributeName) {
        this.attributeName = attributeName;
    }

    public void setAttributeID(int attributeID) {
        this.attributeID = attributeID;
    }

    public void setLabel(String label) {
        this.label = label;
    }

    public String getValue() {
        return value;
    }

    public String getAttributeName() {
        return attributeName;
    }

    public int getAttributeID() {
        return attributeID;
    }

    public String getLabel() {
        return label;
    }
    
}
