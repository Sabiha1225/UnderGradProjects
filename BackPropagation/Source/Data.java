package backpropagation;

/**
 *
 * @author Administrator
 */
public class Data {
    private static Data instance = null;
    public static Data getInstance() {
      if(instance == null) {
         instance = new Data();
      }
      return instance;
    }
    
    private double[][] test;
    private double[][] train;
    private int size = 300;
    private int noOfAttribute;
    private int noOfClass;
    private int noOfData;
    private int noOfTestData;

    public Data() { 
        test = new double[size][4];
        train = new double[size][4];
    }   

    public void setTest(double[][] test) {
        this.test = test;
    }

    public void setTrain(double[][] train) {
        this.train = train;
    }
    
    public void setNoOfAttribute(int noOfAttribute) {
        this.noOfAttribute = noOfAttribute;
    }

    public void setNoOfClass(int noOfClass) {
        this.noOfClass = noOfClass;
    }

    public void setNoOfData(int noOfData) {
        this.noOfData = noOfData;
    }
    
    public void setNoOfTestData(int noOfTestData) {
        this.noOfTestData = noOfTestData;
    }
    
    public double[][] getTest() {
        return test;
    }

    public double[][] getTrain() {
        return train;
    }
    
    public int getNoOfAttribute() {
        return noOfAttribute;
    }

    public int getNoOfClass() {
        return noOfClass;
    }

    public int getNoOfData() {
        return noOfData;
    }
    
    public int getNoOfTestData() {
        return noOfTestData;
    }
    
}
