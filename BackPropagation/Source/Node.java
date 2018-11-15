package backpropagation;

/**
 *
 * @author Administrator
 */
public class Node {
    
    private int id;
    private int noOfInputWeight;
    private double[] inputWeight;
    private double output;
    private double sigOutput;
    private double input;
    private double error; 

    public Node() {
        this.id = 0;
        this.noOfInputWeight = 0;
        this.output = 0;
        this.sigOutput = 0;
        this.input = 0;
        this.error = 0;
    }
    
    public void setId(int id) {
        this.id = id;
    }

    public void setNoOfInputWeight(int noOfInputWeight) {
        this.noOfInputWeight = noOfInputWeight;
    }

    public void setInputWeight(double[] inputWeight) {
        this.inputWeight = new double[this.noOfInputWeight];
        this.inputWeight = inputWeight;
    }

    public void setIndexedInputWeight(int index, double newWeight) {
        this.inputWeight[index] = newWeight;
    }
    
    public void setOutput(double output) {
        this.output = output;
    }

    public void setSigOutput(double sigOutput) {
        this.sigOutput = sigOutput;
    }
    
    public void setInput(double input) {
        this.input = input;
    }
    
    public void setError(double error) {
        this.error = error;
    }
    
    public int getId() {
        return id;
    }

    public int getNoOfInputWeight() {
        return noOfInputWeight;
    }

    public double[] getInputWeight() {
        return inputWeight;
    }
    public double getIndexedInputWeight(int index)
    {
        return inputWeight[index];
    }
    public double getOutput() {
        return output;
    }

    public double getSigOutput() {
        return sigOutput;
    }
    
    public double getInput() {
        return input;
    }
    
    public double getError() {
        return error;
    }
}
