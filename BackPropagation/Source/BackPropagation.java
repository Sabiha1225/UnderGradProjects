/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package backpropagation;

import java.util.Scanner;

/**
 *
 * @author Administrator
 */
public class BackPropagation {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        Data data = Data.getInstance();
        FileInputOutput f = FileInputOutput.getInstance();
        f.getData();
        Network nt = Network.getInstance();
        int inputNeuron, outputNeuron, noOfHiddenLayer;
        int[] hiddenNeuron = new int[3];
        Scanner in = new Scanner(System.in);
        //System.out.print("Enter No Of Neurons In Input Layer: ");
        //inputNeuron = in.nextInt();
        //System.out.print("Enter No Of Neurons In Output Layer: ");
        //outputNeuron = in.nextInt();
        //System.out.print("Enter No Of Hidden Layers: ");
        //noOfHiddenLayer = in.nextInt();
        //hiddenNeuron = new int[noOfHiddenLayer];
        //System.out.println(inputNeuron+"  "+outputNeuron+"  "+noOfHiddenLayer);
        /*for(int i=0; i<3; ++i)
        {
            hiddenNeuron[i] = in.nextInt();
            //System.out.print(hiddenNeuron[i]+"  ");
        }*/
        nt.createNetwork();
        nt.printNetwork();
        System.out.println("-------------------------------------------");
        nt.trainNetwork();
        nt.printNetwork();
        System.out.println("-------------------------------------------");
        nt.testNetwork();
    }
}
