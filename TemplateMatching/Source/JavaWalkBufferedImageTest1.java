package templatematching;

import java.awt.Component;
import java.awt.Graphics2D;
import java.awt.image.BufferedImage;
import java.awt.image.BufferedImageOp;
import java.awt.image.ConvolveOp;
import java.awt.image.Kernel;
import java.io.File;
import java.io.IOException;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.imageio.ImageIO;
import javax.swing.JFrame;
 
public class JavaWalkBufferedImageTest1 extends Component {
    private static int[][][] refArray;
    private static int[][][] tempArray;
    private static int refW, refH, tempW, tempH;
    private static int bestRow, bestCol;
    private static double minDist;
 
    public static void main(String[] foo) {
        HierarchicalSearch();
        new JavaWalkBufferedImageTest1();
        //templateMatchingCorrelation();
        //templateMatchingLogarithm();
        
        showImage("logarithm.jpg", refH, refW, refArray, bestRow, bestCol, tempH, tempW);
    }
 
    public static void printPixelARGB(int pixel , int j, int i) {
        int alpha = (pixel >> 24) & 0xff;
        int red = (pixel >> 16) & 0xff;
        int green = (pixel >> 8) & 0xff;
        int blue = (pixel) & 0xff;
        refArray[i][j][0] = red;
        refArray[i][j][1] = green;
        refArray[i][j][2] = blue;
        //System.out.println("argb: " + alpha + ", " + red + ", " + green + ", " + blue);
    }
  
    public static void printPixelARGB1(int pixel , int j, int i) {
        int alpha = (pixel >> 24) & 0xff;
        int red = (pixel >> 16) & 0xff;
        int green = (pixel >> 8) & 0xff;
        int blue = (pixel) & 0xff;
        tempArray[i][j][0] = red;
        tempArray[i][j][1] = green;
        tempArray[i][j][2] = blue;
        //System.out.println("argb: " + alpha + ", " + red + ", " + green + ", " + blue);
    }
 
    private static void marchThroughImage(BufferedImage image, BufferedImage image1) {
        refW = image.getWidth();
        refH = image.getHeight();
        refArray = new int[refH][refW][3];
        System.out.println("width, height: " + refW + ", " + refH);
        for (int i = 0; i < refH; i++) {
            for (int j = 0; j < refW; j++) {
              //System.out.println("x,y: " + j + ", " + i);
                int pixel = image.getRGB(j, i);
                printPixelARGB(pixel, j, i);
               //System.out.println("");
            }
        }
      
        tempW = image1.getWidth();
        tempH = image1.getHeight();
        tempArray = new int[tempH][tempW][3];
        System.out.println();
        System.out.println("*******************************************************************");
        System.out.println("width, height: " + tempW + ", " + tempH);
        for (int i = 0; i < tempH; i++) {
            for (int j = 0; j < tempW; j++) {
                //System.out.println("x,y: " + j + ", " + i);
                int pixel = image1.getRGB(j, i);
                printPixelARGB1(pixel, j, i);
                //System.out.println("");
            }
        }
    }
 
    public JavaWalkBufferedImageTest1() {
        try {
            // get the BufferedImage, using the ImageIO class
            //BufferedImage image = ImageIO.read(this.getClass().getResource("images.jpg"));
            //BufferedImage image1 = ImageIO.read(this.getClass().getResource("images1.jpg"));
        
            //Reverse Procedure
            //Level2
            BufferedImage image = ImageIO.read(this.getClass().getResource("logarithm_level2.jpg"));
            BufferedImage image1 = ImageIO.read(this.getClass().getResource("logarithm1_level2.jpg"));        
            marchThroughImage(image, image1);
            templateMatchingCorrelation();
            
            //Level 1
            image = ImageIO.read(this.getClass().getResource("logarithm_level1.jpg"));
            image1 = ImageIO.read(this.getClass().getResource("logarithm1_level1.jpg"));        
            marchThroughImage(image, image1);
            int centerX = (int) Math.ceil((refH*1.0)/2); 
            int centerY = (int) Math.ceil((refW*1.0)/2);
            templateMatchingLogarithm(centerX+(2*bestRow), centerY+(2*bestCol));
            
            image = ImageIO.read(this.getClass().getResource("logarithm.jpg"));
            image1 = ImageIO.read(this.getClass().getResource("logarithm1.jpg"));        
            marchThroughImage(image, image1);
            centerX = (int) Math.ceil((refH*1.0)/2); 
            centerY = (int) Math.ceil((refW*1.0)/2);
            templateMatchingLogarithm(centerX+(2*bestRow), centerY+(2*bestCol));
        /*
        for(int i=0; i<refH; ++i)
        {
            for(int j=0; j<refW; ++j)
            {
                System.out.println(refArray[i][j][0]+"    "+refArray[i][j][1]+"     "+refArray[i][j][2]);
            }
        }
      
        System.out.println();
        System.out.println();
        System.out.println("************************************************************************************************************************************************");
      
        for(int i=0; i<tempH; ++i)
        {
            for(int j=0; j<tempW; ++j)
            {
                System.out.println(tempArray[i][j][0]+"    "+tempArray[i][j][1]+"     "+tempArray[i][j][2]);
            }
        }*/
      
      
        } catch (IOException e) {
        System.err.println(e.getMessage());
        }
    }
  
    public static void templateMatchingCorrelation()
    {
        double min = Double.MAX_VALUE;
      
        for(int x=0; x<=(refH-tempH); ++x)
        {
            for(int y=0; y<=(refW-tempW); ++y)
            {
                double sad = 0.0;
              
                for(int i=0; i<tempH; ++i)
                {
                    for(int j=0; j<tempW; ++j)
                    {
                        sad += ( (Math.abs(refArray[x+i][y+j][0]-tempArray[i][j][0])*Math.abs(refArray[x+i][y+j][0]-tempArray[i][j][0])) + (Math.abs(refArray[x+i][y+j][1]-tempArray[i][j][1])*Math.abs(refArray[x+i][y+j][1]-tempArray[i][j][1]))+(Math.abs(refArray[x+i][y+j][2]-tempArray[i][j][2])*Math.abs(refArray[x+i][y+j][2]-tempArray[i][j][2])) );
                    }
                }
                if(sad< min)
                {
                    min = sad;
                    bestRow = x;
                    bestCol = y;
                    minDist = sad;
                }
            }
        }
      
        System.out.println("Row:  "+bestRow+ "   Col:  "+bestCol+"   MinDistance:   "+minDist);
    }
  
    public static void templateMatchingLogarithm()
    {
        int p = refH/2;
        int counter=0;
        //int p =7;
        int k = (int)Math.ceil(Math.log10(p)/Math.log10(2));
        int d = (int) Math.pow(2.0, (double)(k-1));
        //System.out.println(d);
        int[][] pointList = new int[9][2];
        int[][] helper = {{0,0},{1,0},{-1,0},{0,1},{0,-1},{1,1},{-1,1},{1,-1},{-1,-1}};
        int centerX, centerY;
        int tempX=0, tempY=0;
        double max = 0.0;
        double maxDist = 0.0;
        centerX = (int) Math.ceil((refH*1.0)/2); 
        centerY = (int) Math.ceil((refW*1.0)/2);
        System.out.println(d);
        System.out.println(centerX+"          "+centerY);
        while(d>=1)
        {
            for(int i=0; i<9; ++i)
            {
                if((centerX+(helper[i][0]*d))>=0 && (centerX+(helper[i][0]*d))<refH && (centerY+(helper[i][1]*d))>=0 && (centerY+(helper[i][1]*d))<refW)
                {
                    pointList[i][0] = centerX+(helper[i][0]*d);
                    pointList[i][1] = centerY+(helper[i][1]*d);
                }
                else
                {
                    pointList[i][0] = -1;
                    pointList[i][1] = -1;
                }
            }
            if(counter==0)
            {
                for(int s=0; s<9; ++s)
                {
                    double sad = 0.0, sad1=0.0, sad2=0.0;
                    int x = pointList[s][0];
                    int y = pointList[s][1];
              
                    if(x != -1 && y != -1)
                    {
                        for(int i=0; i<tempH; ++i)
                        {
                            for(int j=0; j<tempW; ++j)
                            {
                                if(x+i>=0 && x+i<refH && y+j>=0 && y+j<refW)
                                {
                                    sad1 += ((refArray[x+i][y+j][0]*refArray[x+i][y+j][0]) + (refArray[x+i][y+j][1]*refArray[x+i][y+j][1])+(refArray[x+i][y+j][2]*refArray[x+i][y+j][2]));
                                    sad2 += ( (tempArray[i][j][0]*tempArray[i][j][0]) + (tempArray[i][j][1]*tempArray[i][j][1]) + (tempArray[i][j][2]*tempArray[i][j][2]) );
                          
                                    sad += ( (refArray[x+i][y+j][0]*tempArray[i][j][0]) + (refArray[x+i][y+j][1]*tempArray[i][j][1]) + (refArray[x+i][y+j][2]*tempArray[i][j][2]) );
                                }
                            }
                        }
                    }
                    sad = sad/Math.sqrt(sad1*sad2);
                    if(sad > max)
                    {
                        max = sad;
                        tempX = x;
                        tempY = y;
                        maxDist = sad;
                    }
                }
            }
            else
            {
                for(int s=1; s<9; ++s)
                {
                    double sad = 0.0, sad1=0.0, sad2=0.0;
                    int x = pointList[s][0];
                    int y = pointList[s][1];
              
                    if(x != -1 && y != -1)
                    {
                        for(int i=0; i<tempH; ++i)
                        {
                            for(int j=0; j<tempW; ++j)
                            {
                                if(x+i>=0 && x+i<refH && y+j>=0 && y+j<refW)
                                {
                                    sad1 += ((refArray[x+i][y+j][0]*refArray[x+i][y+j][0]) + (refArray[x+i][y+j][1]*refArray[x+i][y+j][1])+(refArray[x+i][y+j][2]*refArray[x+i][y+j][2]));
                                    sad2 += ( (tempArray[i][j][0]*tempArray[i][j][0]) + (tempArray[i][j][1]*tempArray[i][j][1]) + (tempArray[i][j][2]*tempArray[i][j][2]) );
                          
                                    sad += ( (refArray[x+i][y+j][0]*tempArray[i][j][0]) + (refArray[x+i][y+j][1]*tempArray[i][j][1]) + (refArray[x+i][y+j][2]*tempArray[i][j][2]) );
                                }
                            }
                        }
                    }
                    sad = sad/Math.sqrt(sad1*sad2);
                    if(sad > max)
                    {
                        max = sad;
                        tempX = x;
                        tempY = y;
                        maxDist = sad;
                    }
                }
                
            }
              //if(sad1>0 && sad2>0)
            centerX = tempX;
            centerY = tempY;
            d = d/2;
            System.out.println(tempX+"          "+tempY+"           "+maxDist);
            counter++;
            System.out.println(d);
      }
        bestRow = centerX;
        bestCol = centerY;
  }
    
    public static void templateMatchingLogarithm(int centerx, int centery)
    {
        int p = refH/2;
        int counter=0;
        //int p =7;
        int k = (int)Math.ceil(Math.log10(p)/Math.log10(2));
        int d = (int) Math.pow(2.0, (double)(k-1));
        //System.out.println(d);
        int[][] pointList = new int[9][2];
        int[][] helper = {{0,0},{1,0},{-1,0},{0,1},{0,-1},{1,1},{-1,1},{1,-1},{-1,-1}};
        int centerX, centerY;
        int tempX=0, tempY=0;
        double max = 0.0;
        double maxDist = 0.0;
        centerX = (int) Math.ceil((refH*1.0)/2); 
        centerY = (int) Math.ceil((refW*1.0)/2);
        System.out.println(d);
        System.out.println(centerX+"          "+centerY);
        while(d>=1)
        {
            for(int i=0; i<9; ++i)
            {
                if((centerX+(helper[i][0]*d))>=0 && (centerX+(helper[i][0]*d))<refH && (centerY+(helper[i][1]*d))>=0 && (centerY+(helper[i][1]*d))<refW)
                {
                    pointList[i][0] = centerX+(helper[i][0]*d);
                    pointList[i][1] = centerY+(helper[i][1]*d);
                }
                else
                {
                    pointList[i][0] = -1;
                    pointList[i][1] = -1;
                }
            }
            if(counter==0)
            {
                for(int s=0; s<9; ++s)
                {
                    double sad = 0.0, sad1=0.0, sad2=0.0;
                    int x = pointList[s][0];
                    int y = pointList[s][1];
              
                    if(x != -1 && y != -1)
                    {
                        for(int i=0; i<tempH; ++i)
                        {
                            for(int j=0; j<tempW; ++j)
                            {
                                if(x+i>=0 && x+i<refH && y+j>=0 && y+j<refW)
                                {
                                    sad1 += ((refArray[x+i][y+j][0]*refArray[x+i][y+j][0]) + (refArray[x+i][y+j][1]*refArray[x+i][y+j][1])+(refArray[x+i][y+j][2]*refArray[x+i][y+j][2]));
                                    sad2 += ( (tempArray[i][j][0]*tempArray[i][j][0]) + (tempArray[i][j][1]*tempArray[i][j][1]) + (tempArray[i][j][2]*tempArray[i][j][2]) );
                          
                                    sad += ( (refArray[x+i][y+j][0]*tempArray[i][j][0]) + (refArray[x+i][y+j][1]*tempArray[i][j][1]) + (refArray[x+i][y+j][2]*tempArray[i][j][2]) );
                                }
                            }
                        }
                    }
                    sad = sad/Math.sqrt(sad1*sad2);
                    if(sad > max)
                    {
                        max = sad;
                        tempX = x;
                        tempY = y;
                        maxDist = sad;
                    }
                }
            }
            else
            {
                for(int s=1; s<9; ++s)
                {
                    double sad = 0.0, sad1=0.0, sad2=0.0;
                    int x = pointList[s][0];
                    int y = pointList[s][1];
              
                    if(x != -1 && y != -1)
                    {
                        for(int i=0; i<tempH; ++i)
                        {
                            for(int j=0; j<tempW; ++j)
                            {
                                if(x+i>=0 && x+i<refH && y+j>=0 && y+j<refW)
                                {
                                    sad1 += ((refArray[x+i][y+j][0]*refArray[x+i][y+j][0]) + (refArray[x+i][y+j][1]*refArray[x+i][y+j][1])+(refArray[x+i][y+j][2]*refArray[x+i][y+j][2]));
                                    sad2 += ( (tempArray[i][j][0]*tempArray[i][j][0]) + (tempArray[i][j][1]*tempArray[i][j][1]) + (tempArray[i][j][2]*tempArray[i][j][2]) );
                          
                                    sad += ( (refArray[x+i][y+j][0]*tempArray[i][j][0]) + (refArray[x+i][y+j][1]*tempArray[i][j][1]) + (refArray[x+i][y+j][2]*tempArray[i][j][2]) );
                                }
                            }
                        }
                    }
                    sad = sad/Math.sqrt(sad1*sad2);
                    if(sad > max)
                    {
                        max = sad;
                        tempX = x;
                        tempY = y;
                        maxDist = sad;
                    }
                }
                
            }
              //if(sad1>0 && sad2>0)
            centerX = tempX;
            centerY = tempY;
            d = d/2;
            System.out.println(tempX+"          "+tempY+"           "+maxDist);
            counter++;
            System.out.println(d);
      }
        bestRow = centerX;
        bestCol = centerY;
  }
    
    public static void HierarchicalSearch()
    {
        //Level 0 Image, Image1
        
        //Level  1
        // filter Image
        String refImage = "D:/Sabiha/Sabiha1/Level-4Term-2/CSE_474_Pattern_Recognition_Sessional/Offline2/TemplateMatching/src/templatematching/logarithm.jpg";
        String refImage1 = "D:/Sabiha/Sabiha1/Level-4Term-2/CSE_474_Pattern_Recognition_Sessional/Offline2/TemplateMatching/src/templatematching/logarithm_level1.jpg";
        String tempImage = "D:/Sabiha/Sabiha1/Level-4Term-2/CSE_474_Pattern_Recognition_Sessional/Offline2/TemplateMatching/src/templatematching/logarithm1.jpg";
        String tempImage1 = "D:/Sabiha/Sabiha1/Level-4Term-2/CSE_474_Pattern_Recognition_Sessional/Offline2/TemplateMatching/src/templatematching/logarithm1_level1.jpg";
        
        filterImage(refImage, tempImage, refImage1, tempImage1, 2);
        
        //Level 2
        //filter Image
        String refImage2 = "D:/Sabiha/Sabiha1/Level-4Term-2/CSE_474_Pattern_Recognition_Sessional/Offline2/TemplateMatching/src/templatematching/logarithm_level1.jpg";
        String refImage3 = "D:/Sabiha/Sabiha1/Level-4Term-2/CSE_474_Pattern_Recognition_Sessional/Offline2/TemplateMatching/src/templatematching/logarithm_level2.jpg";
        String tempImage2 = "D:/Sabiha/Sabiha1/Level-4Term-2/CSE_474_Pattern_Recognition_Sessional/Offline2/TemplateMatching/src/templatematching/logarithm1_level1.jpg";
        String tempImage3 = "D:/Sabiha/Sabiha1/Level-4Term-2/CSE_474_Pattern_Recognition_Sessional/Offline2/TemplateMatching/src/templatematching/logarithm1_level2.jpg";
        
        filterImage(refImage2, tempImage2, refImage3, tempImage3, 2);
        
        //Reverse Procedure
        //Level 2
    }
    public static void filterImage(String refImage, String tempImage, String refImage1, String tempImage1, int size)
    {
        try {            
            //Reference Image
            File inputFile = new File(refImage);
            BufferedImage inputImage = ImageIO.read(inputFile);
            
            float data[] = { 0.0001111f, 0.0001111f, 0.0001111f, 0.0001111f, 0.0001111f, 0.0001111f, 0.0001111f, 0.0001111f, 0.0001111f };
            Kernel kernel = new Kernel(3, 3, data);	 
            BufferedImageOp op = new ConvolveOp(kernel, ConvolveOp.EDGE_NO_OP,null);	 
            BufferedImage outputImage = op.filter(inputImage, null);
            
            Graphics2D g2d = outputImage.createGraphics();
            g2d.drawImage(inputImage, 0, 0, inputImage.getWidth(), inputImage.getHeight(), null);        
            g2d.dispose();
            
            String formatName = refImage1.substring(refImage1.lastIndexOf(".") + 1);
            ImageIO.write(outputImage, formatName, new File(refImage1));
            
            resize(refImage, refImage1, size, size);
            
            
            //template Image
            inputFile = new File(tempImage);
            inputImage = ImageIO.read(inputFile);
             	 
            outputImage = op.filter(inputImage, null);
            
            g2d = outputImage.createGraphics();
            g2d.drawImage(inputImage, 0, 0, inputImage.getWidth(), inputImage.getHeight(), null);        
            g2d.dispose();
            
            formatName = tempImage1.substring(tempImage1.lastIndexOf(".") + 1);
            ImageIO.write(outputImage, formatName, new File(tempImage1));
            
            resize(tempImage, tempImage1, size, size);
            
        } catch (IOException ex) {
            Logger.getLogger(JavaWalkBufferedImageTest1.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
    public static void resize(String inputImagePath,String outputImagePath,int scaledWidth, int scaledHeight){
        try {
            File inputFile = new File(inputImagePath);        
            BufferedImage inputImage;
            inputImage = ImageIO.read(inputFile);
            BufferedImage outputImage = new BufferedImage(inputImage.getWidth()/scaledWidth, inputImage.getHeight()/scaledHeight, inputImage.getType());
            
            Graphics2D g2d = outputImage.createGraphics();
            g2d.drawImage(inputImage, 0, 0, inputImage.getWidth()/scaledWidth, inputImage.getHeight()/scaledHeight, null);        
            g2d.dispose();
            
            String formatName = outputImagePath.substring(outputImagePath.lastIndexOf(".") + 1);
            ImageIO.write(outputImage, formatName, new File(outputImagePath));
            
        } catch (IOException ex) {
            Logger.getLogger(JavaWalkBufferedImageTest1.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
    
    public static void showImage(String image, int row, int col, int[][][] refArray, int bestRow, int bestCol, int tempH, int tempR)
    {
        PixelCanvas p = new PixelCanvas();
        p.draw(image, row, col, refArray, bestRow, bestCol, tempH, tempR);
    }
 
}