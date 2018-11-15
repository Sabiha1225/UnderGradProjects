package templatematching;

import java.awt.Canvas;
import java.awt.Color;
import java.awt.Graphics;
import java.awt.image.BufferedImage;
import java.io.IOException;
import java.util.Random;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.imageio.ImageIO;

import javax.swing.JFrame;

public class PixelCanvas extends Canvas {
    private static String imageName;
    private static int row, col, bestRow, bestCol, tempH, tempW;
    private static int[][][] refArray;
    private static final int WIDTH = 400;
    private static final int HEIGHT = 400;
    private static final Random random = new Random();

    @Override
    public void paint(Graphics g) {
        super.paint(g);
        try {
            BufferedImage image = ImageIO.read(this.getClass().getResource(imageName));
            for(int i=0; i<row; ++i)
            {
                for(int j=0; j<col; ++j)
                {
                    g.setColor(new Color(refArray[i][j][0], refArray[i][j][1], refArray[i][j][2]));
                    g.drawLine(i, j, i, j);
                }
            }
            g.setColor(Color.WHITE);
            g.drawRect(bestRow, bestCol, tempH, tempW);
            /*for(int x = 0; x < WIDTH; x++) {
                for(int y = 0; y < HEIGHT; y++) {
                    g.setColor(randomColor());
                    g.drawLine(x, y, x, y);
                }
            }*/
        } catch (IOException ex) {
            Logger.getLogger(PixelCanvas.class.getName()).log(Level.SEVERE, null, ex);
        }
        
    }

    private Color randomColor() {
        return new Color(random.nextInt(256), random.nextInt(256), random.nextInt(256));
    }

    public void draw(String image, int row, int col, int[][][] refArray, int bestR, int bestH, int temH, int temR) {
        imageName = image;
        this.row = row;
        this.col = col;
        this.refArray = refArray;
        this.bestRow = bestH;
        this.bestCol = bestR;
        this.tempH = temH;
        this.tempW = temR;
        
        JFrame frame = new JFrame();

        frame.setSize(WIDTH, HEIGHT);
        frame.add(new PixelCanvas());

        frame.setVisible(true);
    }
}