package backpropagation;

import java.util.ArrayList;
import java.util.List;

/**
 *
 * @author Administrator
 */
public class Network {
    
    private int inputNeuron, outputNeuron, noOfHiddenLayer;
    private int[] hiddenNeuron= new int[]{3,4,3};
    //private double[] weight = new double[]{.1,.8,.4,.6,.3,.9};
    private double[] inputValues;
    private int noOfLayers=3;
    private List<Layer> layers;
    private static Network instance = null;
    //private int count;
    private double learningRate= .5;
    private double target;
    private double targetClass;
    private double[] targates;
    private int noOfIteration=4000;
    private int totalMissClassification;
    public static Network getInstance() {
      if(instance == null) {
         instance = new Network();
      }
      return instance;
    }
    public Network() {
        this.inputNeuron = 0;
        this.outputNeuron = 0;
        this.noOfHiddenLayer = 0;
        this.layers = new ArrayList<Layer>();
    }

    public Network(int inputNeuron, int outputNeuron, int noOfHiddenLayer, int[] hiddenNeuron) {
        this.inputNeuron = inputNeuron;
        this.outputNeuron = outputNeuron;
        this.noOfHiddenLayer = noOfHiddenLayer;
        this.hiddenNeuron = hiddenNeuron;
        this.layers = new ArrayList<Layer>();
    }

    public void setInputNeuron(int inputNeuron) {
        this.inputNeuron = inputNeuron;
    }

    public void setOutputNeuron(int outputNeuron) {
        this.outputNeuron = outputNeuron;
    }

    public void setNoOfHiddenLayer(int noOfHiddenLayer) {
        this.noOfHiddenLayer = noOfHiddenLayer;
    }

    public void setHiddenNeuron(int[] hiddenNeuron) {
        this.hiddenNeuron = hiddenNeuron;
    }
    
    public void setNoOfLayers(int noOfLayers) {
        this.noOfLayers = noOfLayers;
    }

    /*public void setWeight(double[] weight) {
        this.weight = weight;
    }*/

    public void setInputValues(double[] inputValues) {
        this.inputValues = inputValues;
    }

    /*public double[] getWeight() {
        return weight;
    }*/

    public double[] getInputValues() {
        return inputValues;
    }
    
    public int getInputNeuron() {
        return inputNeuron;
    }

    public int getOutputNeuron() {
        return outputNeuron;
    }

    public int getNoOfHiddenLayer() {
        return noOfHiddenLayer;
    }

    public int[] getHiddenNeuron() {
        return hiddenNeuron;
    }
    
    public int getNoOfLayers() {
        return noOfLayers;
    }
    
    public double sigmoidFunction(double Net)
    {
        return 1/(1+Math.exp(-Net));
    }
    
    public double getRandomWeight()
    {
        return -1+2*Math.random();
    }
    
    public void createNetwork()
    {
        int beforeNodeCount=0;
        //count = 0;
        for(int i=0; i<noOfLayers; ++i)
        {
            Layer l = new Layer();
            l.setNoOfNodes(hiddenNeuron[i]);
            List<Node> n = new ArrayList<Node>();
            for(int j=0; j<hiddenNeuron[i]; ++j)
            {
                Node child = new Node();
                child.setId(j);
                /*if(i==0)
                {
                    child.setInput(inputValues[j]);
                }*/
                if(i>0)
                {
                    child.setNoOfInputWeight(beforeNodeCount);
                    double[] w = new double[beforeNodeCount];
                    for(int k=0; k<beforeNodeCount; ++k)
                    {
                        w[k] = getRandomWeight();
                        //count++;
                    }
                    child.setInputWeight(w);
                }
                n.add(child);
            }
            l.setNodes(n);
            beforeNodeCount = hiddenNeuron[i];
            layers.add(l);
        }
    }
    
    public void printNetwork()
    {
        for(int i=0; i<noOfLayers; ++i)
        {
            Layer l = layers.get(i);
            System.out.println(l.getNoOfNodes());
            List<Node> n = new ArrayList<Node>();
            n = l.getNodes();
            for(int j=0; j<n.size(); ++j)
            {
                Node child = n.get(j);
                System.out.println(child.getId()+"  "+child.getInput()+"  "+child.getNoOfInputWeight()+"  "+child.getOutput()+"  "+child.getSigOutput()+"  "+child.getError());
                if(i>0)
                {
                    double[] w = child.getInputWeight();
                    for(int k=0; k<w.length; ++k)
                    {
                        System.out.print(w[k]+"   ");
                    }
                    System.out.println();
                }
            }
        }
    }
    
    public void perceptron()
    {
        for(int i=0; i<noOfLayers; ++i)
        {
            //Layer l = layers.get(i);
            //List<Node> n = l.getNodes();
            if(i==0)
            {
                for(int j=0; j<layers.get(i).getNoOfNodes(); ++j)
                {
                    //Node child = n.get(j);
                    //child.setInput(inputValues[j]);
                    layers.get(i).nodes.get(j).setInput(inputValues[j]);
                    layers.get(i).nodes.get(j).setOutput(inputValues[j]);
                    layers.get(i).nodes.get(j).setSigOutput(inputValues[j]);
                }
            }
            else if(i>0)
            {
                //Layer beforeLayer = layers.get(i-1);
                //List<Node> beforeNode = beforeLayer.getNodes();
                for(int j=0; j<layers.get(i).getNoOfNodes(); ++j)
                {
                    //Node child1 = n.get(j);
                    //double[] weight = child1.getInputWeight();
                    double[] weight = layers.get(i).nodes.get(j).getInputWeight();
                    double output=0;
                    for(int k=0; k<weight.length; ++k)
                    {
                        output += weight[k]*layers.get(i-1).nodes.get(k).getSigOutput();
                    }
                    layers.get(i).nodes.get(j).setOutput(output);
                    double sigOutput = sigmoidFunction(output);
                    layers.get(i).nodes.get(j).setSigOutput(sigOutput);
                }
            }
        }
        //System.out.println(targates[0]+"  "+targates[1]+"  "+targates[2]);
    }
    
    public void backPropagation()
    {
        for(int i=noOfLayers-1; i>0; --i)
        {
            if(i == noOfLayers-1)
            {
                calculateOutputError(i);
            }
            else
            {
                calculateHiddenError(i);
            }
            changeWeight(i);
        }
    }
    
    public void calculateOutputError(int layerId)
    {
        for(int i=0; i<layers.get(layerId).getNoOfNodes(); ++i)
        {
            double out = layers.get(layerId).nodes.get(i).getSigOutput();
            layers.get(layerId).nodes.get(i).setError((targates[i]-out)*(1-out)*out);
        }
    }
    public void calculateHiddenError(int layerId)
    {
        for(int i=0; i<layers.get(layerId).getNoOfNodes(); ++i)
        {
            double out = layers.get(layerId).nodes.get(i).getSigOutput();
            double prev=0;
            for(int j=0; j<layers.get(layerId+1).getNoOfNodes(); ++j)
            {
                prev += layers.get(layerId+1).nodes.get(j).getError()*layers.get(layerId+1).nodes.get(j).getIndexedInputWeight(i);
            }
            layers.get(layerId).nodes.get(i).setError(prev*(1-out)*out);
        }
    }
    public void changeWeight(int layerId)
    {
        for(int i=0; i<layers.get(layerId).getNoOfNodes(); ++i)
        {
            for(int j=0; j<layers.get(layerId).nodes.get(i).getNoOfInputWeight(); ++j)
            {
                double out = layers.get(layerId-1).nodes.get(j).getSigOutput();
                double newWeight = layers.get(layerId).nodes.get(i).getIndexedInputWeight(j)+(learningRate*layers.get(layerId).nodes.get(i).getError()*out);
                layers.get(layerId).nodes.get(i).setIndexedInputWeight(j, newWeight);
            }
        }
    }
    
    public void trainNetwork()
    {
        
        Data data = Data.getInstance();
        inputValues = new double[data.getNoOfAttribute()];
        targates = new double[data.getNoOfClass()];
        double[][] train = data.getTrain();
        
        for(int i=0; i<noOfIteration; ++i)
        {
            double totalError1 =0;
            for(int j=0; j<data.getNoOfData(); ++j)
            {
                int k;
                for(k=0; k<data.getNoOfAttribute(); ++k)
                {
                    inputValues[k] = train[j][k];
                }
                targetClass = train[j][k];
                for(int l=0; l<data.getNoOfClass(); ++l)
                {
                    if(l+1 == targetClass)
                    {
                        targates[l] = 1;
                    }
                    else
                    {
                        targates[l] = 0;
                    }
                }
                perceptron();
                
                backPropagation();
                totalError1+=totalError();
                
            }
            System.out.println(totalError1);
            if(totalError1<0.05)
                break;
        }
    }
    public void testNetwork()
    {
        int mismatch=0;
        Data data = Data.getInstance();
        inputValues = new double[data.getNoOfAttribute()];
        targates = new double[data.getNoOfClass()];
        double[][] test = data.getTest();
            for(int j=0; j<data.getNoOfTestData(); ++j)
            {
                int k;
                for(k=0; k<data.getNoOfAttribute(); ++k)
                {
                    inputValues[k] = test[j][k];
                }
                targetClass = test[j][k];
                for(int l=0; l<data.getNoOfClass(); ++l)
                {
                    if(l+1 == targetClass)
                    {
                        targates[l] = 1;
                    }
                    else
                    {
                        targates[l] = 0;
                    }
                }
                perceptron();
                System.out.println(targetClass+"   [ "+targates[0]+" "+targates[1]+" "+targates[2]+" ]");
                System.out.println(layers.get(noOfLayers-1).nodes.get(0).getSigOutput()+"   "+layers.get(noOfLayers-1).nodes.get(1).getSigOutput()+"   "+layers.get(noOfLayers-1).nodes.get(2).getSigOutput());
                for(int i=0; i<targates.length; ++i)
                {
                    if(Math.abs(targates[i] - Math.round(layers.get(noOfLayers-1).nodes.get(i).getSigOutput())) != 0)
                    {
                        mismatch++;
                        break;
                    }
                }
            }
            System.out.println(mismatch);
            System.out.println("Accuracy:  "+((data.getNoOfTestData()-mismatch)*100.0)/data.getNoOfTestData());
    }
    
    public double totalError()
    {
        double error=0;
        for(int i=0; i<layers.get(noOfLayers-1).getNoOfNodes(); ++i)
        {
            if(layers.get(noOfLayers-1).nodes.get(i).getError()<0)
                error += (layers.get(noOfLayers-1).nodes.get(i).getError()*(-1));
            else
                error += layers.get(noOfLayers-1).nodes.get(i).getError();
        }
        return error;
    }
}
