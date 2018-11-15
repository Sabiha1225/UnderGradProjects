#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include <windows.h> 
#include<GL/glut.h>
#include "CameraHeader_12_12_1992.h"

#define pi (double)2*acos((double)0)

Camera_12_12_1992 cam_12_12_1992;

double cameraHeight;
double cameraAngle;
int drawgrid;
int drawaxes;
double angle;
double sizeCube;
float radius;
int slices=30,stacks=30;
double sizeSphere,size=50;
double radiCylinder,heightCylinder;
GLuint texid1, baseCyl, baseCylDisk, baseSquareDisk, baseCylUpper, middlePillar, middleSquare1, middleCone;
GLuint middleUpPillar, middleFrontSquare1, middleFrontSquare2, middleFrontSquare3, middleSquare2, middleSquare3;
GLuint middleSquare4, topTriangle1, topOutSquare1, topOutSquare2, road1, road2, road3, road4, road5, road6,grill, sideUpperBar;
GLuint sideUpperBar1, window1, window2, window3, window4, window5, road7, baseCyl1;

int num_texture = -1;

GLfloat diffusePoint[] = {0, 0, 0, 0.0};
GLfloat lightDir[] = {100.0, 100.0, 100.0, 0.0};


struct point
{
	double x,y,z;
};

int LoadBitmap(char *filename)
{
    int i, j=0;
    FILE *l_file;
    unsigned char *l_texture;

    BITMAPFILEHEADER fileheader;
    BITMAPINFOHEADER infoheader;
    RGBTRIPLE rgb;

    num_texture++;

    if( (l_file = fopen(filename, "rb"))==NULL) return (-1);

    fread(&fileheader, sizeof(fileheader), 1, l_file);

    fseek(l_file, sizeof(fileheader), SEEK_SET);
    fread(&infoheader, sizeof(infoheader), 1, l_file);

    l_texture = (byte *) malloc(infoheader.biWidth * infoheader.biHeight * 4);
    memset(l_texture, 0, infoheader.biWidth * infoheader.biHeight * 4);

 for (i=0; i < infoheader.biWidth*infoheader.biHeight; i++)
    {
            fread(&rgb, sizeof(rgb), 1, l_file);

            l_texture[j+0] = rgb.rgbtRed;
            l_texture[j+1] = rgb.rgbtGreen;
            l_texture[j+2] = rgb.rgbtBlue;
            l_texture[j+3] = 255;
            j += 4;
    }
    fclose(l_file);

    glBindTexture(GL_TEXTURE_2D, num_texture);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);

// glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexImage2D(GL_TEXTURE_2D, 0, 4, infoheader.biWidth, infoheader.biHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, l_texture);
     gluBuild2DMipmaps(GL_TEXTURE_2D, 4, infoheader.biWidth, infoheader.biHeight, GL_RGBA, GL_UNSIGNED_BYTE, l_texture);

    free(l_texture);

    return (num_texture);

}
void func(void)
{

	texid1 = LoadBitmap("IMAGE/water.bmp");   /*here bkg1.bmp is the bitmap image to be used as texture, texid is global varible declared to uniquely  identify this particular image*/
    baseCyl = LoadBitmap("IMAGE/baseCyl.bmp");
	baseCylDisk = LoadBitmap("IMAGE/baseCylDisk.bmp");
	baseSquareDisk = LoadBitmap("IMAGE/baseSquareDisk.bmp");
	baseCylUpper = LoadBitmap("IMAGE/baseCylUpper.bmp");
	middlePillar = LoadBitmap("IMAGE/middlePillar.bmp");
	middleSquare1 = LoadBitmap("IMAGE/middleSquare1.bmp");
	middleCone = LoadBitmap("IMAGE/middleCone.bmp");
	middleUpPillar = LoadBitmap("IMAGE/middleUpPillar.bmp");
	middleFrontSquare1 = LoadBitmap("IMAGE/middleFrontSquare1.bmp");
	middleFrontSquare2 = LoadBitmap("IMAGE/middleFrontSquare2.bmp");
	middleFrontSquare3 = LoadBitmap("IMAGE/middleFrontSquare3.bmp");
	middleSquare2 = LoadBitmap("IMAGE/middleSquare2.bmp");
	middleSquare3 = LoadBitmap("IMAGE/middleSquare3.bmp");
	middleSquare4 = LoadBitmap("IMAGE/middleSquare4.bmp");
	topTriangle1 = LoadBitmap("IMAGE/topTriangle1.bmp");
	topOutSquare1 = LoadBitmap("IMAGE/topOutSquare1.bmp");
	topOutSquare2 = LoadBitmap("IMAGE/topOutSquare2.bmp");
	road1 = LoadBitmap("IMAGE/road1.bmp");
	road2 = LoadBitmap("IMAGE/road2.bmp");
	road3 = LoadBitmap("IMAGE/road3.bmp");
	road4 = LoadBitmap("IMAGE/road4.bmp");
	road5 = LoadBitmap("IMAGE/road5.bmp");
	road6 = LoadBitmap("IMAGE/road6.bmp");
	grill = LoadBitmap("IMAGE/grill.bmp");
	sideUpperBar = LoadBitmap("IMAGE/sideUpperBar.bmp");
	sideUpperBar1 = LoadBitmap("IMAGE/sideUpperBar1.bmp");
	window1 = LoadBitmap("IMAGE/window1.bmp");
	window2 = LoadBitmap("IMAGE/window2.bmp");
	window3 = LoadBitmap("IMAGE/window3.bmp");
	window4 = LoadBitmap("IMAGE/window4.bmp");
	window5 = LoadBitmap("IMAGE/window5.bmp");
	road7 = LoadBitmap("IMAGE/road7.bmp");
	baseCyl1 = LoadBitmap("IMAGE/baseCyl1.bmp");
}

void drawAxes()
{
	if(drawaxes==1)
	{
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_LINES);{
			glVertex3f( 100,0,0);
			glVertex3f(-100,0,0);
			glVertex3f(0,-100,0);
			glVertex3f(0, 100,0);
			glVertex3f(0,0, 100);
			glVertex3f(0,0,-100);
		}glEnd();
	}
}


void drawGrid()
{
	int i;
	if(drawgrid==1)
	{
		glColor3f(0.6, 0.6, 0.6);	//grey
		glBegin(GL_LINES);{
			for(i=-8;i<=8;i++){

				if(i==0)
					continue;	//SKIP the MAIN axes

				//lines parallel to Y-axis
				glVertex3f(i*10, -90, 0);
				glVertex3f(i*10,  90, 0);

				//lines parallel to X-axis
				glVertex3f(-90, i*10, 0);
				glVertex3f( 90, i*10, 0);
			}
		}glEnd();
	}
}


void drawSquare(float a)
{
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);{
		glVertex3f( a, a, 25);
		glVertex3f( a, -a, 25);
		glVertex3f(-a, -a, 25);
		glVertex3f(-a, a, 25);
	}glEnd();
	
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);{
		glVertex3f( a, a, -25);
		glVertex3f( a,-a, -25);
		glVertex3f(-a,-a, -25);
		glVertex3f(-a, a, -25);
	}glEnd();
	
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);{
		glVertex3f( 25, a, -a);
		glVertex3f( 25, -a, -a);
		glVertex3f( 25, -a, a);
		glVertex3f( 25, a, a);
	}glEnd();

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);{
		glVertex3f( -a, 25, -a);
		glVertex3f( a, 25, -a);
		glVertex3f( a, 25, a);
		glVertex3f(-a, 25, a);
	}glEnd();
	
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);{
		glVertex3f( -25, -a, -a);
		glVertex3f( -25, a, -a);
		glVertex3f( -25, a, a);
		glVertex3f( -25, -a, a);
	}glEnd();
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);{
		glVertex3f( a, -25, -a);
		glVertex3f( -a, -25, -a);
		glVertex3f( -a, -25, a);
		glVertex3f( a, -25, a);
	}glEnd();
	
}

void drawsphere(float radius,int slices,int stacks)
{
	struct point points[100][100];
	int i,j;
	double h,r;
	for(i=0;i<=stacks;i++)
	{
		h=radius*sin(((double)i/(double)stacks)*(pi/2));	
		r=sqrt(radius*radius-h*h);
		for(j=0;j<=slices;j++)
		{
			points[i][j].x=r*cos(((double)j/(double)slices)*2*pi);
			points[i][j].y=r*sin(((double)j/(double)slices)*2*pi);
			points[i][j].z=h;
		}
		
	}
	for(i=0;i<stacks;i++)
	{
		for(j=0;j<slices;j++)
		{
			glColor3f((double)i/(double)stacks,(double)i/(double)stacks,(double)i/(double)stacks);
			glBegin(GL_QUADS);{
				glVertex3f(points[i][j].x,points[i][j].y,points[i][j].z);
				glVertex3f(points[i][j+1].x,points[i][j+1].y,points[i][j+1].z);
				glVertex3f(points[i+1][j+1].x,points[i+1][j+1].y,points[i+1][j+1].z);
				glVertex3f(points[i+1][j].x,points[i+1][j].y,points[i+1][j].z);
				
			}glEnd();
		}
		
	}
}

void drawFloor()
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,texid1);
	glNormal3f(1.0,0.0,0.0);
	glBegin(GL_POLYGON);			
		glTexCoord2f(0,0); glVertex3f(150, 0,-150);
		glTexCoord2f(0,1); glVertex3f(150, 0,150);
		glTexCoord2f(20,1); glVertex3f(-150, 0,150);
		glTexCoord2f(20,0); glVertex3f(-150, 0,-150);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}


void drawHalfCyllinder(float radius, float height, float clipx, float clipy, float clipz, float d, GLuint texid, GLuint texid1)
{
		//glRotatef(90, 0, 1, 0);
		double coef[4];
		coef[0] = clipx;	//-1.x
		coef[1] = clipy;	//0.y
		coef[2] = clipz;	//0.z
		coef[3] = d;	//10
		glClipPlane(GL_CLIP_PLANE0,coef);
		glEnable(GL_CLIP_PLANE0);{
			GLUquadricObj *qobj;
			qobj = gluNewQuadric();

			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, texid);
			gluQuadricNormals(qobj,GLU_SMOOTH);
            gluQuadricTexture(qobj, GLU_TRUE);
			gluCylinder(qobj, radius, radius, height, slices, stacks); 
			glDisable(GL_TEXTURE_2D);
            //Disk
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, texid1);
			gluQuadricNormals(qobj,GLU_SMOOTH);
            gluQuadricTexture(qobj, GLU_TRUE);
			gluDisk(qobj, 0.0f, radius, slices, 1); 
			glTranslatef(0.0f, 0.0f, height); 
			gluDisk(qobj, 0.0f, radius, slices, 1);
			glDisable(GL_TEXTURE_2D);
		}glDisable(GL_CLIP_PLANE0);
}
void drawHalfCyllinderWithoutBase(float radius, float height, float clipx, float clipy, float clipz, float d, GLuint texid)
{
		//glRotatef(90, 0, 1, 0);
		double coef[4];
		coef[0] = clipx;	//-1.x
		coef[1] = clipy;	//0.y
		coef[2] = clipz;	//0.z
		coef[3] = d;	//10
		glClipPlane(GL_CLIP_PLANE0,coef);
		glEnable(GL_CLIP_PLANE0);{
			GLUquadricObj *qobj;
			qobj = gluNewQuadric();

			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, texid);
			gluQuadricNormals(qobj,GLU_SMOOTH);
            gluQuadricTexture(qobj, GLU_TRUE);
			gluCylinder(qobj, radius, radius, height, slices, stacks); 
			glDisable(GL_TEXTURE_2D);
		}glDisable(GL_CLIP_PLANE0);
}
void drawPlane1(float x1,float y1,float z1,float x2,float y2,float z2,float x3,float y3,float z3,float x4,float y4,float z4,GLuint texid, float tecX, float tecY, float tecX1, float tecY1, float tecX2, float tecY2, float tecX3, float tecY3)
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,texid);
	glNormal3f(1.0,0.0,0.0);
	glBegin(GL_QUADS);			
		//glTexCoord2f(0,0); glVertex3f(x1,y1,z1);
		//glTexCoord2f(0,1); glVertex3f(x2,y2,z2);
		//glTexCoord2f(50,1); glVertex3f(x3,y3,z3);
		//glTexCoord2f(50,0); glVertex3f(x4,y4,z4);
		glTexCoord2f(tecX,tecY); glVertex3f(x1,y1,z1);
		glTexCoord2f(tecX1,tecY1); glVertex3f(x2,y2,z2);
		glTexCoord2f(tecX2,tecY2); glVertex3f(x3,y3,z3);
		glTexCoord2f(tecX3,tecY3); glVertex3f(x4,y4,z4);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}
void drawPlane(float x1,float y1,float z1,float x2,float y2,float z2,float x3,float y3,float z3,float x4,float y4,float z4,GLuint texid)
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,texid);
	glNormal3f(1.0,0.0,0.0);
	glBegin(GL_QUADS);			
		glTexCoord2f(1,0); glVertex3f(x1,y1,z1);
		glTexCoord2f(0,0); glVertex3f(x2,y2,z2);
		glTexCoord2f(0,1); glVertex3f(x3,y3,z3);
		glTexCoord2f(1,1); glVertex3f(x4,y4,z4);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

void drawTriangle(float x1,float y1,float z1,float x2,float y2,float z2,float x3,float y3,float z3,GLuint texid)
{
	//glColor3f(1,1,1);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,texid);
	glNormal3f(1.0,0.0,0.0);
	glBegin(GL_TRIANGLES);			
		/*glTexCoord2f(0,0);*/ glVertex3f(x1,y1,z1);
		/*glTexCoord2f(1,0);*/ glVertex3f(x2,y2,z2);
		/*glTexCoord2f(0,1);*/ glVertex3f(x3,y3,z3);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}
void drawModifiedCircle(float radius, float height, int stacks, int slices, float clipx, float clipy, float clipz, float d, GLuint texid)
{
	double coef[4];
	coef[0] = clipx;	//-1.x
	coef[1] = clipy;	//0.y
	coef[2] = clipz;	//0.z
	coef[3] = d;	//10
	glClipPlane(GL_CLIP_PLANE0,coef);
	glEnable(GL_CLIP_PLANE0);{
			struct point points[100][100];
			int i,j;
			for(i=0;i<stacks;i++)
			{
				for(j=0;j<=slices;j++)
				{
					points[i][j].x=radius*sin(((double)j/(double)slices)*2*pi);
					points[i][j].y=height;
					points[i][j].z=radius*cos(((double)j/(double)slices)*2*pi);
				}
				radius-=2;		
			}
	
			for(i=0;i<stacks;i++)
			{
				for(j=0;j<slices;j++)
				{
					glEnable(GL_TEXTURE_2D);
					glBindTexture(GL_TEXTURE_2D,texid);
					glNormal3f(1.0,0.0,0.0);
					glBegin(GL_QUADS);{
						glTexCoord2f(0,0); glVertex3f(points[i][j].x,points[i][j].y,points[i][j].z);
						glTexCoord2f(1,0); glVertex3f(points[i][j+1].x,points[i][j+1].y,points[i][j+1].z);
						glTexCoord2f(1,1); glVertex3f(points[i+1][j+1].x,points[i+1][j+1].y,points[i+1][j+1].z);
						glTexCoord2f(0,1); glVertex3f(points[i+1][j].x,points[i+1][j].y,points[i+1][j].z);
				
					}glEnd();
					glDisable(GL_TEXTURE_2D);
				}		
			}
	}glDisable(GL_CLIP_PLANE0);
}
void drawBaseCyllinder()
{
	//HalfCyllinder----------------------------------------------------------
	//Radius = 12, Height = 19;
	glPushMatrix();{
		glTranslatef(0 , 0, 10);
		glRotatef(-90, 1, 0, 0);
		drawHalfCyllinder(12, 19, 0, -1, 0, 0, baseCyl, baseCylDisk);
	}glPopMatrix();
	glPushMatrix();{
		glTranslatef(0 , 0, -10);
		glRotatef(-90, 1, 0, 0);
		drawHalfCyllinder(12, 19, 0, 1, 0, 0, baseCyl, baseCylDisk);
	}glPopMatrix();
	//HalfCircle---------------------------------------------------------------
	glPushMatrix();{
		glTranslatef(0 , 0, 10);
		glTranslatef(0 , 19, 0);
		glRotatef(-90, 1, 0, 0);
		drawHalfCyllinderWithoutBase(12, 2, 0, -1, 0, 0, baseCylUpper);
	}glPopMatrix();
	glPushMatrix();{
		glTranslatef(0 , 0, 10);
		glTranslatef(0 , 19, 0);
		glRotatef(-90, 1, 0, 0);
		drawHalfCyllinderWithoutBase(10, 2, 0, -1, 0, 0, baseCylUpper);
	}glPopMatrix();

	glPushMatrix();{
		glTranslatef(0 , 0, -10);
		glTranslatef(0 , 19, 0);
		glRotatef(-90, 1, 0, 0);
		drawHalfCyllinderWithoutBase(12, 2, 0, 1, 0, 0, baseCylUpper);
	}glPopMatrix();
	glPushMatrix();{
		glTranslatef(0 , 0, -10);
		glTranslatef(0 , 19, 0);
		glRotatef(-90, 1, 0, 0);
		drawHalfCyllinderWithoutBase(10, 2, 0, 1, 0, 0, baseCylUpper);
	}glPopMatrix();

	glPushMatrix();{
		glTranslatef(0 , 0, 10);
		drawModifiedCircle(12, 21, 2, slices, 0, 0, 1, 0, baseCylUpper);
	}glPopMatrix();
	glPushMatrix();{
		glTranslatef(0 , 0, -10);
		drawModifiedCircle(12, 21, 2, slices, 0, 0, -1, 0, baseCylUpper);
	}glPopMatrix();

    //BaseSquare---------------------------------------------------------------
	drawPlane(12,0,-10, 12,0,10, 12,19,10, 12,19,-10, baseCyl);
	drawPlane(-12,0,-10, -12,0,10, -12,19,10, -12,19,-10, baseCyl);
	drawPlane(12,19,-10, 12,19,10, -12,19,10, -12,19,-10, baseSquareDisk);
	drawPlane(12,0,-10, 12,0,10, -12,0,10, -12,0,-10, baseCylDisk);

	// back up planes
	drawPlane(5,19+6.3+4,-8, 5,19+6.3+4,8, 5,19+6.3+8.3,8, 5,19+6.3+8.3,-8, middleFrontSquare3);
	drawPlane(-5,19+6.3+4,8, -5,19+6.3+4,-8, -5,19+6.3+8.3,-8, -5,19+6.3+8.3,8, middleFrontSquare3);

	drawPlane(5,19,4, 5,19,8, 5,19+6.3+4,8, 5,19+6.3+4,4, middleFrontSquare1);
	drawPlane(5,19,-8, 5,19,-4, 5,19+6.3+4,-4, 5,19+6.3+4,-8, middleFrontSquare1);
	drawPlane(-5,19,4, -5,19,8, -5,19+6.3+4,8, -5,19+6.3+4,4, middleFrontSquare1);
	drawPlane(-5,19,-8, -5,19,-4, -5,19+6.3+4,-4, -5,19+6.3+4,-8, middleFrontSquare1);
}
void drawCone(float radius, float height, GLuint texid)
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texid);
	//gluQuadricNormals(qobj,GLU_SMOOTH);
    //gluQuadricTexture(qobj, GLU_TRUE);
	glutSolidCone(radius, height, slices, stacks); 
	glDisable(GL_TEXTURE_2D);
}
void drawStencil()
{
	//Front-----------------------------------------------------------------------------------------
	//glClear(GL_DEPTH_BUFFER_BIT);
	glEnable(GL_STENCIL_TEST);
	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
	glDepthMask(GL_FALSE);
	glStencilFunc(GL_ALWAYS, 1, 0xFF);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);  // draw 1s on test fail (always)
 
	// draw stencil pattern
	glStencilMask(0xFF);
	glClear(GL_STENCIL_BUFFER_BIT);  // needs mask=0xFF
	glPushMatrix();{
		glTranslatef(8 , 19+6.3, 0);
		glRotatef(-90, 0, 1, 0);
		drawHalfCyllinder(4, .2, 0, 1, 0, 0, baseCyl, baseCyl);
	}glPopMatrix();

	glPushMatrix();{
		glTranslatef(-7.8 , 19+6.3, 0);
		glRotatef(-90, 0, 1, 0);
		drawHalfCyllinder(4, .2, 0, 1, 0, 0, baseCyl, baseCyl);
	}glPopMatrix();
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	glDepthMask(GL_TRUE);
	glStencilMask(0x00);
	// draw where stencil's value is 0
	glStencilFunc(GL_EQUAL, 0, 0xFF);
	/* (nothing to draw) */
	// draw only where stencil's value is 1
	//glStencilFunc(GL_EQUAL, 1, 0xFF);
	drawPlane(8,19+6.3,-8, 8,19+6.3,8, 8,19+6.3+8.3,8, 8,19+6.3+8.3,-8, middleFrontSquare3);
	drawPlane(-8,19+6.3,8, -8,19+6.3,-8, -8,19+6.3+8.3,-8, -8,19+6.3+8.3,8, middleFrontSquare3);
	glDisable(GL_STENCIL_TEST);
	//glClear(GL_DEPTH_BUFFER_BIT);

}

void drawFourPlane(float x1,float y1,float z1,float x2,float y2,float z2,float x3,float y3,float z3,float x4,float y4,float z4,float x5,float y5,float z5,float x6,float y6,float z6,float x7,float y7,float z7,float x8,float y8,float z8, GLuint texid1, GLuint texid2, GLuint texid3, GLuint texid4, GLuint texid5)
{
	drawPlane(x1, y1, z1, x2, y2, z2, x3, y3, z3, x4, y4, z4, texid1); //up
	drawPlane(x5, y5, z5, x6, y6, z6, x7, y7, z7, x8, y8, z8, texid2); //down
	drawPlane(x4, y4, z4, x3, y3, z3, x7, y7, z7, x8, y8, z8, texid3); //top
	drawPlane(x5, y5, z5, x1, y1, z1, x4, y4, z4, x8, y8, z8, texid4); //right
	drawPlane(x2, y2, z2, x6, y6, z6, x7, y7, z7, x3, y3, z3, texid5); //left
}
void drawFourPlane1(float x1,float y1,float z1,float x2,float y2,float z2,float x3,float y3,float z3,float x4,float y4,float z4,float x5,float y5,float z5,float x6,float y6,float z6,float x7,float y7,float z7,float x8,float y8,float z8, GLuint texid1, GLuint texid2, GLuint texid3, GLuint texid4, GLuint texid5, float tecX, float tecY, float tecX1, float tecY1, float tecX2, float tecY2, float tecX3, float tecY3)
{
	drawPlane(x1, y1, z1, x2, y2, z2, x3, y3, z3, x4, y4, z4, texid1); //up
	drawPlane(x5, y5, z5, x6, y6, z6, x7, y7, z7, x8, y8, z8, texid2); //down
	drawPlane(x4, y4, z4, x3, y3, z3, x7, y7, z7, x8, y8, z8, texid3); //top
	drawPlane1(x5, y5, z5, x1, y1, z1, x4, y4, z4, x8, y8, z8, texid4, tecX, tecY, tecX1, tecY1, tecX2, tecY2, tecX3, tecY3); //right
	drawPlane1(x2, y2, z2, x6, y6, z6, x7, y7, z7, x3, y3, z3, texid5, tecX, tecY, tecX1, tecY1, tecX2, tecY2, tecX3, tecY3); //left
}
void drawFourPlane2(float x1,float y1,float z1,float x2,float y2,float z2,float x3,float y3,float z3,float x4,float y4,float z4,float x5,float y5,float z5,float x6,float y6,float z6,float x7,float y7,float z7,float x8,float y8,float z8, GLuint texid1, GLuint texid2, GLuint texid3, GLuint texid4, GLuint texid5, float tecX, float tecY, float tecX1, float tecY1, float tecX2, float tecY2, float tecX3, float tecY3)
{
	drawPlane1(x1, y1, z1, x2, y2, z2, x3, y3, z3, x4, y4, z4, texid1, tecX, tecY, tecX1, tecY1, tecX2, tecY2, tecX3, tecY3); //up
	drawPlane(x5, y5, z5, x6, y6, z6, x7, y7, z7, x8, y8, z8, texid2); //down
	drawPlane(x4, y4, z4, x3, y3, z3, x7, y7, z7, x8, y8, z8, texid3); //top
	drawPlane(x5, y5, z5, x1, y1, z1, x4, y4, z4, x8, y8, z8, texid4); //right
	drawPlane(x2, y2, z2, x6, y6, z6, x7, y7, z7, x3, y3, z3, texid5); //left
}

void drawMiddleBody()
{
	glPushMatrix();{
		glTranslatef(8 , 19, 8);
		glRotatef(-90, 1, 0, 0);
		drawHalfCyllinderWithoutBase(2, 38, 0, 0, 0, 0, middlePillar);
	}glPopMatrix();
	glPushMatrix();{
		glTranslatef(-8 , 19, 8);
		glRotatef(-90, 1, 0, 0);
		drawHalfCyllinderWithoutBase(2, 38, 0, 0, 0, 0, middlePillar);
	}glPopMatrix();
	glPushMatrix();{
		glTranslatef(-8 , 19, -8);
		glRotatef(-90, 1, 0, 0);
		drawHalfCyllinderWithoutBase(2, 38, 0, 0, 0, 0, middlePillar);
	}glPopMatrix();
	glPushMatrix();{
		glTranslatef(8 , 19, -8);
		glRotatef(-90, 1, 0, 0);
		drawHalfCyllinderWithoutBase(2, 38, 0, 0, 0, 0, middlePillar);
	}glPopMatrix();
//-----------------------------------------------------------------------------------
	drawPlane(8,19,8, -8,19,8, -8,38+19,8, 8,38+19,8, middleSquare1);
	drawPlane(-8,19,-8, 8,19,-8, 8,38+19,-8, -8,38+19,-8, middleSquare1);
    //front hollow square
	drawPlane(8,19,4, 8,19,8, 8,19+6.3,8, 8,19+6.3,4, middleFrontSquare1);
	drawPlane(8,19,-8, 8,19,-4, 8,19+6.3,-4, 8,19+6.3,-8, middleFrontSquare1);
	drawPlane(-8,19,4, -8,19,8, -8,19+6.3,8, -8,19+6.3,4, middleFrontSquare1);
	drawPlane(-8,19,-8, -8,19,-4, -8,19+6.3,-4, -8,19+6.3,-8, middleFrontSquare1);
    //side hollow square
	drawPlane(-8,19,4, 8,19,4, 8,19+6.3,4, -8,19+6.3,4, middleFrontSquare2);
	drawPlane(-8,19,-4, 8,19,-4, 8,19+6.3,-4, -8,19+6.3,-4, middleFrontSquare2);
    //hollow cyllinder
	glPushMatrix();{
		glTranslatef(8 , 19+6.3, 0);
		glRotatef(-90, 0, 1, 0);
		drawHalfCyllinderWithoutBase(4, 16, 0, 1, 0, 0, middleFrontSquare2);
	}glPopMatrix();
	//hollow upper square
	drawPlane(8,19+6.3+8.3,-8, 8,19+6.3+8.3,8, 8,19+6.3+8.3+23.4,8, 8,19+6.3+8.3+23.4,-8, middleSquare2);
	drawPlane(-8,19+6.3+8.3,8, -8,19+6.3+8.3,-8, -8,19+6.3+8.3+23.4,-8, -8,19+6.3+8.3+23.4,8, middleSquare2);
    //Upper square
	drawPlane(8, 19+38 ,8, -8, 19+38 ,8, -8, 19+38+12 ,8, 8, 19+38+12 ,8, middleSquare3);
	drawPlane(-8, 19+38 ,-8, 8, 19+38 ,-8, 8, 19+38+12 ,-8, -8, 19+38+12 ,-8, middleSquare3);
	drawPlane(8, 19+38 ,-8, 8, 19+38 ,8, 8, 19+38+12 ,8, 8, 19+38+12 ,-8, middleSquare3);
	drawPlane(-8, 19+38 ,8, -8, 19+38 ,-8, -8, 19+38+12 ,-8, -8, 19+38+12 ,8, middleSquare3);
	//top square
	drawPlane(8, 19+38+12 ,-8, 8, 19+38+12 ,8, -8, 19+38+12 ,8, -8, 19+38+12 ,-8, middleSquare4);

//-----------------------------------------------------------------------------------
	// Middle Cone
	glPushMatrix();{
		glTranslatef(8, 38+20, 8);
		glRotatef(90,1,0,0);
		drawCone(2.5, 7, middleCone);
	}glPopMatrix();
	glPushMatrix();{
		glTranslatef(-8, 38+20, 8);
		glRotatef(90,1,0,0);
		drawCone(2.5, 7, middleCone);
	}glPopMatrix();
	glPushMatrix();{
		glTranslatef(-8, 38+20, -8);
		glRotatef(90,1,0,0);
		drawCone(2.5, 7, middleCone);
	}glPopMatrix();
	glPushMatrix();{
		glTranslatef(8, 38+20, -8);
		glRotatef(90,1,0,0);
		drawCone(2.5, 7, middleCone);
	}glPopMatrix();
	//--------------------------------------------------------------------------------------
	//Upper Cyllinder-----------------------------------------------------------------------
	glPushMatrix();{
		glTranslatef(8 , 38+20, 8);
		glRotatef(-90, 1, 0, 0);
		drawHalfCyllinderWithoutBase(2.5, 16, 0, 0, 0, 0, middleUpPillar);
	}glPopMatrix();
	glPushMatrix();{
		glTranslatef(-8 , 38+20, 8);
		glRotatef(-90, 1, 0, 0);
		drawHalfCyllinderWithoutBase(2.5, 16, 0, 0, 0, 0, middleUpPillar);
	}glPopMatrix();
	glPushMatrix();{
		glTranslatef(-8 , 38+20, -8);
		glRotatef(-90, 1, 0, 0);
		drawHalfCyllinderWithoutBase(2.5, 16, 0, 0, 0, 0, middleUpPillar);
	}glPopMatrix();
	glPushMatrix();{
		glTranslatef(8 , 38+20, -8);
		glRotatef(-90, 1, 0, 0);
		drawHalfCyllinderWithoutBase(2.5, 16, 0, 0, 0, 0, middleUpPillar);
	}glPopMatrix();

	//siide long bar
	drawFourPlane1(-50, 58+8,10, -50, 58+8, 6, -10, 58+8, 6, -10, 58+8, 10, -50, 58+4, 10, -50, 58+4, 6, -10, 58+4, 6, -10, 58+4, 10,sideUpperBar1,sideUpperBar1,sideUpperBar1,sideUpperBar,sideUpperBar, 0,0,0,1,3,1,3,0);
	//drawPlane1(-50, 58+4, 10, -50, 58+8,10,  -10, 58+8, 10, -10, 58+4, 10, sideUpperBar, 0,0,0,1,2,1,2,0);
	glPushMatrix();{
		glTranslatef(0 , 0, -16);
		drawFourPlane1(-50, 58+8,10, -50, 58+8, 6, -10, 58+8, 6, -10, 58+8, 10, -50, 58+4, 10, -50, 58+4, 6, -10, 58+4, 6, -10, 58+4, 10,sideUpperBar1,sideUpperBar1,sideUpperBar1,sideUpperBar,sideUpperBar, 0,0,0,1,3,1,3,0);
	}glPopMatrix();
	
	//------------------------------------------------------------------
	//Draw UP Cone------------------------------------------------------
	glPushMatrix();{
		glTranslatef(8, 38+20+16, 8);
		glRotatef(-90,1,0,0);
		drawCone(2.5, 10, middleCone);
	}glPopMatrix();
	glPushMatrix();{
		glTranslatef(-8, 38+20+16, 8);
		glRotatef(-90,1,0,0);
		drawCone(2.5, 10, middleCone);
	}glPopMatrix();
	glPushMatrix();{
		glTranslatef(-8, 38+20+16, -8);
		glRotatef(-90,1,0,0);
		drawCone(2.5, 10, middleCone);
	}glPopMatrix();
	glPushMatrix();{
		glTranslatef(8, 38+20+16, -8);
		glRotatef(-90,1,0,0);
		drawCone(2.5, 10, middleCone);
	}glPopMatrix();

}

void drawLittleHome()
{
	drawPlane( 3, 69 , 8, -3, 69 , 8, -3, 69+2 , 8,  3, 69+2 , 8, topOutSquare1);
	drawPlane(-3, 69 ,-8,  3, 69 ,-8,  3, 69+2 ,-8, -3, 69+2 ,-8, topOutSquare1);
    drawPlane(-3, 69 , 8, -3, 69 ,-8, -3, 69+2 ,-8, -3, 69+2 , 8, topTriangle1);
	drawPlane( 3, 69 ,-8,  3, 69 , 8,  3, 69+2 , 8,  3, 69+2 ,-8, topTriangle1);
	//------------------------------------------------------------------------------
	drawPlane( 3, 71 , 8, -3, 71 , 8, -4, 72 , 8,  4, 72 , 8, topOutSquare2);
	drawPlane(-3, 71 ,-8,  3, 71 ,-8,  4, 72 ,-8, -4, 72 ,-8, topOutSquare2);
	drawPlane(-3, 71 , 8, -3, 71 ,-8, -4, 72 ,-8, -4, 72 , 8, topTriangle1);
	drawPlane( 3, 71 ,-8,  3, 71 , 8,  4, 72 , 8,  4, 72 ,-8, topTriangle1);
	//------------------------------------------------------------------------------
	drawPlane( 4, 72 , 8, -4, 72 , 8, -2.5, 73.5 , 8,  2.5, 73.5 , 8, topOutSquare1);
	drawPlane(-4, 72 ,-8,  4, 72 ,-8,  2.5, 73.5 ,-8, -2.5, 73.5 ,-8, topOutSquare1);
    drawPlane(-4, 72 , 8, -4, 72 ,-8, -2.5, 73.5 ,-8, -2.5, 73.5 , 8, topTriangle1);
	drawPlane( 4, 72 ,-8,  4, 72 , 8,  2.5, 73.5 , 8,  2.5, 73.5 ,-8, topTriangle1);
	//-------------------------------------------------------------------------------
	drawPlane( 2.5, 73.5 , 8, -2.5, 73.5 , 8, -2.5, 75 , 8,  2.5, 75 , 8, topOutSquare1);
	drawPlane(-2.5, 73.5 ,-8,  2.5, 73.5 ,-8,  2.5, 75 ,-8, -2.5, 75 ,-8, topOutSquare1);
    drawPlane(-2.5, 73.5 , 8, -2.5, 73.5 ,-8, -2.5, 75 ,-8, -2.5, 75 , 8, topTriangle1);
	drawPlane( 2.5, 73.5 ,-8,  2.5, 73.5 , 8,  2.5, 75 , 8,  2.5, 75 ,-8, topTriangle1);
	//--------------------------------------------------------------------------------
	drawPlane( 2.5, 75 , 8, -2.5, 75 , 8, -3, 75.5 , 8,  3, 75.5 , 8, topOutSquare1);
	drawPlane(-2.5, 75 ,-8,  2.5, 75 ,-8,  3, 75.5 ,-8, -3, 75.5 ,-8, topOutSquare1);
    drawPlane(-2.5, 75 , 8, -2.5, 75 ,-8, -3, 75.5 ,-8, -3, 75.5 , 8, topTriangle1);
	drawPlane( 2.5, 75 ,-8,  2.5, 75 , 8,  3, 75.5 , 8,  3, 75.5 ,-8, topTriangle1);
	//---------------------------------------------------------------------------------
	drawPlane( 3, 75.5 , 8, -3, 75.5 , 8, -2, 76.5 , 8,  2, 76.5 , 8, topOutSquare1);
	drawPlane(-3, 75.5 ,-8,  3, 75.5 ,-8,  2, 76.5 ,-8, -2, 76.5 ,-8, topOutSquare1);
    drawPlane(-3, 75.5 , 8, -3, 75.5 ,-8, -2, 76.5 ,-8, -2, 76.5 , 8, topTriangle1);
	drawPlane( 3, 75.5 ,-8,  3, 75.5 , 8,  2, 76.5 , 8,  2, 76.5 ,-8, topTriangle1);
	//---------------------------------------------------------------------------------
	drawPlane( 2, 76.5 , 8, -2, 76.5 , 8, -2, 77.5 , 8,  2, 77.5 , 8, topOutSquare1);
	drawPlane(-2, 76.5 ,-8,  2, 76.5 ,-8,  2, 77.5 ,-8, -2, 77.5 ,-8, topOutSquare1);
    drawPlane(-2, 76.5 , 8, -2, 76.5 ,-8, -2, 77.5 ,-8, -2, 77.5 , 8, topTriangle1);
	drawPlane( 2, 76.5 ,-8,  2, 76.5 , 8,  2, 77.5 , 8,  2, 77.5 ,-8, topTriangle1);
	drawPlane( 2, 77.5 , 8, -2, 77.5 , 8, -2, 77.5 ,-8,  2, 77.5 ,-8, topTriangle1);
	//---------------------------------------------------------------------------------
	drawTriangle( 1.5, 77.5 , 8, -1.5, 77.5 , 8, 0, 81.5 , 8, topOutSquare1);
	drawTriangle(-1.5, 77.5 ,-8,  1.5, 77.5 ,-8, 0, 81.5 ,-8, topOutSquare1);
	drawPlane(-1.5, 77.5 , 8, -1.5, 77.5 ,-8, 0, 81.5 ,-8, 0, 81.5 , 8, topTriangle1);
	drawPlane( 1.5, 77.5 ,-8,  1.5, 77.5 , 8, 0, 81.5 , 8, 0, 81.5 ,-8, topTriangle1);
	//---------------------------------------------------------------------------------
	drawPlane( 2, 77.5 , 7, -2, 77.5 , 7, -2, 79.5 , 7,  2, 79.5 , 7, topOutSquare1);
	drawPlane(-2, 77.5 ,-7,  2, 77.5 ,-7,  2, 79.5 ,-7, -2, 79.5 ,-7, topOutSquare1);
    drawPlane(-2, 77.5 , 7, -2, 77.5 ,-7, -2, 79.5 ,-7, -2, 79.5 , 7, topTriangle1);
	drawPlane( 2, 77.5 ,-7,  2, 77.5 , 7,  2, 79.5 , 7,  2, 79.5 ,-7, topTriangle1);
	drawPlane( 2, 79.5 , 7, -2, 79.5 , 7, -2, 79.5 ,-7,  2, 79.5 ,-7, topTriangle1);
}
void drawTop()
{
	//big triangle------------------------------------------------------------------
	drawPlane( 5.86, 69,  5.86, -5.86, 69,  5.86, -0.5, 69+18,  2,  0.5, 69+18,  2, topTriangle1);
	drawPlane(-5.86, 69, -5.86,  5.86, 69, -5.86,  0.5, 69+18, -2, -0.5, 69+18, -2, topTriangle1);
	drawPlane( 5.86, 69, -5.86,  5.86, 69,  5.86,  0.5, 69+18,  2,  0.5, 69+18, -2, topTriangle1);
	drawPlane(-5.86, 69,  5.86, -5.86, 69, -5.86, -0.5, 69+18, -2, -0.5, 69+18,  2, topTriangle1);
	drawPlane( 0.5,  87, -2,     0.5,  87,  2,    -0.5, 87,     2, -0.5, 87,    -2, topTriangle1);

	//Little home triangles----------------------------------------------------------
	drawLittleHome();
	glPushMatrix();{
		glRotatef(90, 0, 1, 0);
		drawLittleHome();
	}glPopMatrix();

}
void drawRoad()
{
	drawFourPlane2( 12, 19,     10, 12, 19,     -10,  12+88, 19,     -10,  12+88, 19,     10, 12, 18.5, 10, 12, 18.5, -10,  12+88, 18.5, -10,  12+88, 18.5, 10, road7,road1, road1, road1, road1, 0,0,0,1,2,1,2,0);
	drawFourPlane1( 12, 19+1.6, 10, 12, 19+1.6,  8.7, 12+88, 19+1.6,  8.7, 12+88, 19+1.6, 10, 12, 19,   10, 12, 19,    8.7, 12+88, 19,    8.7, 12+88, 19,   10, road3,road3, road3, /*road4*/grill, /*road4*/grill, 0,0,0,1,25,1,25,0);
	glPushMatrix();{
		glTranslatef(0, 0, -18.7);
		drawFourPlane1( 12, 19+1.6, 10, 12, 19+1.6,  8.7, 12+88, 19+1.6,  8.7, 12+88, 19+1.6, 10, 12, 19,   10, 12, 19,    8.7, 12+88, 19,    8.7, 12+88, 19,   10, road3,road3, road3, /*road4*/grill, /*road4*/grill, 0,0,0,1,25,1,25,0);
	}glPopMatrix();

//upper bim 1
	drawFourPlane( 8,  65.6, 10, 8,  65.6,  8.7, 19, 51.6,  8.7, 19, 51.6, 10, 8,  64.6,   10, 8,  64.6,    8.7, 19, 50.6,    8.7, 19, 50.6,   10, road6,road6, road6, road6, road6);
	drawFourPlane( 19, 51.6, 10, 19, 51.6,  8.7, 26, 44.6,  8.7, 26, 44.6, 10, 19, 50.6,   10, 19, 50.6,    8.7, 26, 43.6,    8.7, 26, 43.6,   10, road6,road6, road6, road6, road6);
	drawFourPlane( 26, 44.6, 10, 26, 44.6,  8.7, 33, 38.6,  8.7, 33, 38.6, 10, 26, 43.6,   10, 26, 43.6,    8.7, 33, 37.6,    8.7, 33, 37.6,   10, road6,road6, road6, road6, road6);
	drawFourPlane( 33, 38.6, 10, 33, 38.6,  8.7, 40, 33.6,  8.7, 40, 33.6, 10, 33, 37.6,   10, 33, 37.6,    8.7, 40, 32.6,    8.7, 40, 32.6,   10, road6,road6, road6, road6, road6);
	drawFourPlane( 40, 33.6, 10, 40, 33.6,  8.7, 47, 29.6,  8.7, 47, 29.6, 10, 40, 32.6,   10, 40, 32.6,    8.7, 47, 28.6,    8.7, 47, 28.6,   10, road6,road6, road6, road6, road6);
	drawFourPlane( 47, 29.6, 10, 47, 29.6,  8.7, 54, 25.6,  8.7, 54, 25.6, 10, 47, 28.6,   10, 47, 28.6,    8.7, 54, 24.6,    8.7, 54, 24.6,   10, road6,road6, road6, road6, road6);
	drawFourPlane( 54, 25.6, 10, 54, 25.6,  8.7, 66, 20.6,  8.7, 66, 20.6, 10, 54, 24.6,   10, 54, 24.6,    8.7, 63, 20.6,    8.7, 63, 20.6,   10, road6,road6, road6, road6, road6);

	glPushMatrix();{
		glTranslatef(0, 0, -18.7);
		drawFourPlane( 8,  65.6, 10, 8,  65.6,  8.7, 19, 51.6,  8.7, 19, 51.6, 10, 8,  64.6,   10, 8,  64.6,    8.7, 19, 50.6,    8.7, 19, 50.6,   10, road6,road6, road6, road6, road6);
		drawFourPlane( 19, 51.6, 10, 19, 51.6,  8.7, 26, 44.6,  8.7, 26, 44.6, 10, 19, 50.6,   10, 19, 50.6,    8.7, 26, 43.6,    8.7, 26, 43.6,   10, road6,road6, road6, road6, road6);
		drawFourPlane( 26, 44.6, 10, 26, 44.6,  8.7, 33, 38.6,  8.7, 33, 38.6, 10, 26, 43.6,   10, 26, 43.6,    8.7, 33, 37.6,    8.7, 33, 37.6,   10, road6,road6, road6, road6, road6);
		drawFourPlane( 33, 38.6, 10, 33, 38.6,  8.7, 40, 33.6,  8.7, 40, 33.6, 10, 33, 37.6,   10, 33, 37.6,    8.7, 40, 32.6,    8.7, 40, 32.6,   10, road6,road6, road6, road6, road6);
		drawFourPlane( 40, 33.6, 10, 40, 33.6,  8.7, 47, 29.6,  8.7, 47, 29.6, 10, 40, 32.6,   10, 40, 32.6,    8.7, 47, 28.6,    8.7, 47, 28.6,   10, road6,road6, road6, road6, road6);
		drawFourPlane( 47, 29.6, 10, 47, 29.6,  8.7, 54, 25.6,  8.7, 54, 25.6, 10, 47, 28.6,   10, 47, 28.6,    8.7, 54, 24.6,    8.7, 54, 24.6,   10, road6,road6, road6, road6, road6);
		drawFourPlane( 54, 25.6, 10, 54, 25.6,  8.7, 66, 20.6,  8.7, 66, 20.6, 10, 54, 24.6,   10, 54, 24.6,    8.7, 63, 20.6,    8.7, 63, 20.6,   10, road6,road6, road6, road6, road6);

	}glPopMatrix();

	//upper bim 2
	drawFourPlane( 8,  65.6,     10, 8,  65.6,      8.7, 19, 51.6-5,    8.7, 19, 51.6-5,   10, 8,  64.6,       10, 8,  64.6,        8.7, 19, 50.6-5,      8.7, 19, 50.6-5,     10, road6,road6, road6, road6, road6);
	drawFourPlane( 19, 51.6-5,   10, 19, 51.6-5,    8.7, 26, 44.6-7,    8.7, 26, 44.6-7,   10, 19, 50.6-5,     10, 19, 50.6-5,      8.7, 26, 43.6-7,      8.7, 26, 43.6-7,     10, road6,road6, road6, road6, road6);
	drawFourPlane( 26, 44.6-7,   10, 26, 44.6-7,    8.7, 33, 38.6-6.5,  8.7, 33, 38.6-6.5, 10, 26, 43.6-7,     10, 26, 43.6-7,      8.7, 33, 37.6-6.5,    8.7, 33, 37.6-6.5,   10, road6,road6, road6, road6, road6);
	drawFourPlane( 33, 38.6-6.5, 10, 33, 38.6-6.5,  8.7, 40, 33.6-6.0,  8.7, 40, 33.6-6.0, 10, 33, 37.6-6.5,   10, 33, 37.6-6.5,    8.7, 40, 32.6-6.0,    8.7, 40, 32.6-6.0,   10, road6,road6, road6, road6, road6);
	drawFourPlane( 40, 33.6-6.0, 10, 40, 33.6-6.0,  8.7, 47, 29.6-4.5,  8.7, 47, 29.6-4.5, 10, 40, 32.6-6.0,   10, 40, 32.6-6.0,    8.7, 47, 28.6-4.5,    8.7, 47, 28.6-4.5,   10, road6,road6, road6, road6, road6);
	drawFourPlane( 47, 29.6-4.5, 10, 47, 29.6-4.5,  8.7, 54, 25.6-3.0,  8.7, 54, 25.6-3.0, 10, 47, 28.6-4.5,   10, 47, 28.6-4.5,    8.7, 54, 24.6-3.0,    8.7, 54, 24.6-3.0,   10, road6,road6, road6, road6, road6);
	drawFourPlane( 54, 25.6-3.0, 10, 54, 25.6-3.0,  8.7, 66, 20.6,      8.7, 66, 20.6,     10, 54, 24.6-3.0,   10, 54, 24.6-3.0,    8.7, 63, 20.6,        8.7, 63, 20.6,       10, road6,road6, road6, road6, road6);

	glPushMatrix();{
		glTranslatef(0, 0, -18.7);
		drawFourPlane( 8,  65.6,     10, 8,  65.6,      8.7, 19, 51.6-5,    8.7, 19, 51.6-5,   10, 8,  64.6,       10, 8,  64.6,        8.7, 19, 50.6-5,      8.7, 19, 50.6-5,     10, road6,road6, road6, road6, road6);
	drawFourPlane( 19, 51.6-5,   10, 19, 51.6-5,    8.7, 26, 44.6-7,    8.7, 26, 44.6-7,   10, 19, 50.6-5,     10, 19, 50.6-5,      8.7, 26, 43.6-7,      8.7, 26, 43.6-7,     10, road6,road6, road6, road6, road6);
	drawFourPlane( 26, 44.6-7,   10, 26, 44.6-7,    8.7, 33, 38.6-6.5,  8.7, 33, 38.6-6.5, 10, 26, 43.6-7,     10, 26, 43.6-7,      8.7, 33, 37.6-6.5,    8.7, 33, 37.6-6.5,   10, road6,road6, road6, road6, road6);
	drawFourPlane( 33, 38.6-6.5, 10, 33, 38.6-6.5,  8.7, 40, 33.6-6.0,  8.7, 40, 33.6-6.0, 10, 33, 37.6-6.5,   10, 33, 37.6-6.5,    8.7, 40, 32.6-6.0,    8.7, 40, 32.6-6.0,   10, road6,road6, road6, road6, road6);
	drawFourPlane( 40, 33.6-6.0, 10, 40, 33.6-6.0,  8.7, 47, 29.6-4.5,  8.7, 47, 29.6-4.5, 10, 40, 32.6-6.0,   10, 40, 32.6-6.0,    8.7, 47, 28.6-4.5,    8.7, 47, 28.6-4.5,   10, road6,road6, road6, road6, road6);
	drawFourPlane( 47, 29.6-4.5, 10, 47, 29.6-4.5,  8.7, 54, 25.6-3.0,  8.7, 54, 25.6-3.0, 10, 47, 28.6-4.5,   10, 47, 28.6-4.5,    8.7, 54, 24.6-3.0,    8.7, 54, 24.6-3.0,   10, road6,road6, road6, road6, road6);
	drawFourPlane( 54, 25.6-3.0, 10, 54, 25.6-3.0,  8.7, 66, 20.6,      8.7, 66, 20.6,     10, 54, 24.6-3.0,   10, 54, 24.6-3.0,    8.7, 63, 20.6,        8.7, 63, 20.6,       10, road6,road6, road6, road6, road6);
	}glPopMatrix();

	//vertical bims
	drawFourPlane( 19, 19+1.6, 10, 18, 19+1.6,  10, 18, 19+1.6+31,  10, 19, 19+1.6+30, 10, 19, 19+1.6,   8.7, 18, 19+1.6,    8.7, 18, 19+1.6+31,    8.7, 19, 19+1.6+30,   8.7, road5,road5, road5, road5, road5);
	drawFourPlane( 26, 19+1.6, 10, 25, 19+1.6,  10, 25, 19+1.6+24,  10, 26, 19+1.6+23, 10, 26, 19+1.6,   8.7, 25, 19+1.6,    8.7, 25, 19+1.6+24,    8.7, 26, 19+1.6+23,   8.7, road5,road5, road5, road5, road5);
	drawFourPlane( 33, 19+1.6, 10, 32, 19+1.6,  10, 32, 19+1.6+18,  10, 33, 19+1.6+17, 10, 33, 19+1.6,   8.7, 32, 19+1.6,    8.7, 32, 19+1.6+18,    8.7, 33, 19+1.6+17,   8.7, road5,road5, road5, road5, road5);
	drawFourPlane( 40, 19+1.6, 10, 39, 19+1.6,  10, 39, 19+1.6+13,  10, 40, 19+1.6+12, 10, 40, 19+1.6,   8.7, 39, 19+1.6,    8.7, 39, 19+1.6+13,    8.7, 40, 19+1.6+12,   8.7, road5,road5, road5, road5, road5);
	drawFourPlane( 47, 19+1.6, 10, 46, 19+1.6,  10, 46, 19+1.6+9 ,  10, 47, 19+1.6+8 , 10, 47, 19+1.6,   8.7, 46, 19+1.6,    8.7, 46, 19+1.6+9 ,    8.7, 47, 19+1.6+8 ,   8.7, road5,road5, road5, road5, road5);
	drawFourPlane( 54, 19+1.6, 10, 53, 19+1.6,  10, 53, 19+1.6+5 ,  10, 54, 19+1.6+4 , 10, 54, 19+1.6,   8.7, 53, 19+1.6,    8.7, 53, 19+1.6+5 ,    8.7, 54, 19+1.6+4 ,   8.7, road5,road5, road5, road5, road5);

	glPushMatrix();{
		glTranslatef(0, 0, -18.7);
		drawFourPlane( 19, 19+1.6, 10, 18, 19+1.6,  10, 18, 19+1.6+31,  10, 19, 19+1.6+30, 10, 19, 19+1.6,   8.7, 18, 19+1.6,    8.7, 18, 19+1.6+31,    8.7, 19, 19+1.6+30,   8.7, road5,road5, road5, road5, road5);
		drawFourPlane( 26, 19+1.6, 10, 25, 19+1.6,  10, 25, 19+1.6+24,  10, 26, 19+1.6+23, 10, 26, 19+1.6,   8.7, 25, 19+1.6,    8.7, 25, 19+1.6+24,    8.7, 26, 19+1.6+23,   8.7, road5,road5, road5, road5, road5);
		drawFourPlane( 33, 19+1.6, 10, 32, 19+1.6,  10, 32, 19+1.6+18,  10, 33, 19+1.6+17, 10, 33, 19+1.6,   8.7, 32, 19+1.6,    8.7, 32, 19+1.6+18,    8.7, 33, 19+1.6+17,   8.7, road5,road5, road5, road5, road5);
		drawFourPlane( 40, 19+1.6, 10, 39, 19+1.6,  10, 39, 19+1.6+13,  10, 40, 19+1.6+12, 10, 40, 19+1.6,   8.7, 39, 19+1.6,    8.7, 39, 19+1.6+13,    8.7, 40, 19+1.6+12,   8.7, road5,road5, road5, road5, road5);
		drawFourPlane( 47, 19+1.6, 10, 46, 19+1.6,  10, 46, 19+1.6+9 ,  10, 47, 19+1.6+8 , 10, 47, 19+1.6,   8.7, 46, 19+1.6,    8.7, 46, 19+1.6+9 ,    8.7, 47, 19+1.6+8 ,   8.7, road5,road5, road5, road5, road5);
		drawFourPlane( 54, 19+1.6, 10, 53, 19+1.6,  10, 53, 19+1.6+5 ,  10, 54, 19+1.6+4 , 10, 54, 19+1.6,   8.7, 53, 19+1.6,    8.7, 53, 19+1.6+5 ,    8.7, 54, 19+1.6+4 ,   8.7, road5,road5, road5, road5, road5);
	}glPopMatrix();
    
	//left road--------------------------------------------------------------
	drawFourPlane2( -12, 19,     10, -12, 19,      -10,  -12-33, 19+25,       -10,  -12-33, 19+25,     10, -12, 18.5, 10, -12, 18.5,  -10,  -12-33, 18.5+25,  -10,  -12-33, 18.5+25, 10, road2,road1, road1, road1, road1, 0,0,0,1,2,1,2,0);
	drawFourPlane1( -12, 19+1.6, 10, -12, 19+1.6,  8.7,  -12-33, 19+25+1.6,  8.7,  -12-33, 19+25+1.6, 10, -12, 19,   10, -12, 19,    8.7,  -12-33, 19+25,    8.7,  -12-33, 19+25,   10, road3,road3, road3, /*road4*/grill, /*road4*/grill, 0,0,0,1,25,1,25,0);
	glPushMatrix();{
		glTranslatef(0, 0, -18.7);
		drawFourPlane1( -12, 19+1.6, 10, -12, 19+1.6,  8.7,  -12-33, 19+25+1.6,  8.7,  -12-33, 19+25+1.6, 10, -12, 19,   10, -12, 19,    8.7,  -12-33, 19+25,    8.7,  -12-33, 19+25,   10, road3,road3, road3, /*road4*/grill, /*road4*/grill, 0,0,0,1,25,1,25,0);
	}glPopMatrix();
	
	drawFourPlane( -12,   18.5, 10, -12,   18.5,  8.7,  -12-27, 18.5+20.5,  8.7,  -12-27, 18.5+20.5, 10, -13,   17.5,   10, -13,   17.5,    8.7,  -12-27, 17.5+20.5,    8.7,  -12-27, 17.5+20.5,   10, road3,road3, road3, road3, road3);
	drawFourPlane( -12-3, 13,   10, -12-3, 13,    8.7,  -12-27, 18.5+18.5,  8.7,  -12-27, 18.5+18.5, 10, -12-3, 12,     10, -12-3, 12,      8.7,  -12-27, 17.5+18.5,    8.7,  -12-27, 17.5+18.5,   10, road3,road3, road3, road3, road3);
	drawPlane(-39, 37, 10, -39, 37, 8.7, -39, 39, 8.7, -39, 39, 10, road3);
    drawTriangle(-39, 36, 10,  -39, 39, 10,  -45, 43.5, 10, road3);
	drawTriangle(-39, 36, 8.7, -39, 39, 8.7, -45, 43.5, 8.7, road3);
	drawPlane(-39, 36, 10, -39, 36, 8.7, -45, 43.5, 8.7, -45, 43.5, 10, road3);

    drawFourPlane( -12.7,      18.5,       10, -12.7,      18.5,       8.7,  -12.7-2.8,    13,     8.7,  -12.7-2.8,    13,    10, -11.7,      18.5,        10, -11.7,      18.5,         8.7,  -11.7-3.2,    11.9,       8.7,  -11.7-3.2,    11.9,      10, road3,road3, road3, road3, road3);
	drawFourPlane( -13.0-5,    18.5+4.6,   10, -13.0-5,    18.5+4.6,   8.7,  -12.7-2.8-5,  13+5,   8.7,  -12.7-2.8-5,  13+5,  10, -12.0-5,    18.5+3.6,    10, -12.0-5,    18.5+3.6,     8.7,  -11.7-3.2-5,  11.9+5,     8.7,  -11.7-3.2-5,  11.9+5,    10, road3,road3, road3, road3, road3);
	drawFourPlane( -13.3-10,   18.5+8.3,   10, -13.3-10,   18.5+8.3,   8.7,  -12.7-2.8-10, 13+10,  8.7,  -12.7-2.8-10, 13+10, 10, -12.5-10,   18.5+7.3,    10, -12.5-10,   18.5+7.3,     8.7,  -11.7-3.2-10, 11.9+10,    8.7,  -11.7-3.2-10, 11.9+10,   10, road3,road3, road3, road3, road3);
	drawFourPlane( -13.9-15,   18.5+12.0,  10, -13.9-15,   18.5+12.0,  8.7,  -12.7-2.8-15, 13+15,  8.7,  -12.7-2.8-15, 13+15, 10, -13.1-15,   18.5+11.0,   10, -13.1-15,   18.5+11.0,    8.7,  -11.7-3.2-15, 11.9+15,    8.7,  -11.7-3.2-15, 11.9+15,   10, road3,road3, road3, road3, road3);
	drawFourPlane( -14.5-20,   18.5+16.0,  10, -14.5-20,   18.5+16.0,  8.7,  -12.7-2.8-20, 13+20,  8.7,  -12.7-2.8-20, 13+20, 10, -13.7-20,   18.5+15.5,   10, -13.7-20,   18.5+15.5,    8.7,  -11.7-3.2-20, 11.9+20,    8.7,  -11.7-3.2-20, 11.9+20,   10, road3,road3, road3, road3, road3);

	drawFourPlane( -12.7,      17.5,       10, -12.7,      17.5,       8.7,  -12.7-6.3,      16.3,      8.7,  -12.7-6.3,      16.3,      10, -12.9,      17.0,      10, -12.9,      17.0,         8.7,  -12.7-5.9,      15.7,         8.7,  -12.7-5.9,      15.7,        10, road3,road3, road3, road3, road3);
	drawFourPlane( -13.0-5,    17.5+4.2,   10, -13.0-5,    17.5+4.2,   8.7,  -12.7-6.3-4.5,  16.3+4.8,  8.7,  -12.7-6.3-4.5,  16.3+4.8,  10, -12.9-5,    17.0+4.0,  10, -12.9-5,    17.0+4.0,     8.7,  -12.7-5.9-4.5,  15.7+4.8,     8.7,  -12.7-5.9-4.5,  15.7+4.8,    10, road3,road3, road3, road3, road3);
	drawFourPlane( -13.3-10,   17.5+8.3,   10, -13.3-10,   17.5+8.3,   8.7,  -12.7-6.3-8.5,  16.3+9.0,  8.7,  -12.7-6.3-8.5,  16.3+9.0,  10, -12.9-10.9, 17.0+8.1,  10, -12.9-10.9, 17.0+8.1,     8.7,  -12.7-5.9-8.5,  15.7+9.0,     8.7,  -12.7-5.9-8.5,  15.7+9.0,    10, road3,road3, road3, road3, road3);
	drawFourPlane( -13.9-15,   17.5+12.6,  10, -13.9-15,   17.5+12.6,  8.7,  -12.7-6.3-13.5, 16.3+13.9, 8.7,  -12.7-6.3-13.5, 16.3+13.9, 10, -12.9-15.5, 17.0+12.2, 10, -12.9-15.5, 17.0+12.2,    8.7,  -12.7-5.9-13.5, 15.7+13.8,    8.7,  -12.7-5.9-13.5, 15.7+13.8,   10, road3,road3, road3, road3, road3);
	drawFourPlane( -14.0-20,   17.5+17.5,  10, -14.0-20,   17.5+17.5,  8.7,  -12.7-6.3-19.0, 16.3+19.0, 8.7,  -12.7-6.3-19.0, 16.3+19.0, 10, -12.9-19.5, 17.0+17.0, 10, -12.9-19.5, 17.0+17.0,    8.7,  -12.7-5.9-19.0, 15.7+19.0,    8.7,  -12.7-5.9-19.0, 15.7+19.0,   10, road3,road3, road3, road3, road3);

	glPushMatrix();{
		glTranslatef(0, 0, -18.7);

		drawFourPlane( -12,   18.5, 10, -12,   18.5,  8.7,  -12-27, 18.5+20.5,  8.7,  -12-27, 18.5+20.5, 10, -13,   17.5,   10, -13,   17.5,    8.7,  -12-27, 17.5+20.5,    8.7,  -12-27, 17.5+20.5,   10, road3,road3, road3, road3, road3);
		drawFourPlane( -12-3, 13,   10, -12-3, 13,    8.7,  -12-27, 18.5+18.5,  8.7,  -12-27, 18.5+18.5, 10, -12-3, 12,     10, -12-3, 12,      8.7,  -12-27, 17.5+18.5,    8.7,  -12-27, 17.5+18.5,   10, road3,road3, road3, road3, road3);
		drawPlane(-39, 37, 10, -39, 37, 8.7, -39, 39, 8.7, -39, 39, 10, road3);
		drawTriangle(-39, 36, 10,  -39, 39, 10,  -45, 43.5, 10, road3);
		drawTriangle(-39, 36, 8.7, -39, 39, 8.7, -45, 43.5, 8.7, road3);
		drawPlane(-39, 36, 10, -39, 36, 8.7, -45, 43.5, 8.7, -45, 43.5, 10, road3);

		drawFourPlane( -12.7,      18.5,       10, -12.7,      18.5,       8.7,  -12.7-2.8,    13,     8.7,  -12.7-2.8,    13,    10, -11.7,      18.5,        10, -11.7,      18.5,         8.7,  -11.7-3.2,    11.9,       8.7,  -11.7-3.2,    11.9,      10, road3,road3, road3, road3, road3);
		drawFourPlane( -13.0-5,    18.5+4.6,   10, -13.0-5,    18.5+4.6,   8.7,  -12.7-2.8-5,  13+5,   8.7,  -12.7-2.8-5,  13+5,  10, -12.0-5,    18.5+3.6,    10, -12.0-5,    18.5+3.6,     8.7,  -11.7-3.2-5,  11.9+5,     8.7,  -11.7-3.2-5,  11.9+5,    10, road3,road3, road3, road3, road3);
		drawFourPlane( -13.3-10,   18.5+8.3,   10, -13.3-10,   18.5+8.3,   8.7,  -12.7-2.8-10, 13+10,  8.7,  -12.7-2.8-10, 13+10, 10, -12.5-10,   18.5+7.3,    10, -12.5-10,   18.5+7.3,     8.7,  -11.7-3.2-10, 11.9+10,    8.7,  -11.7-3.2-10, 11.9+10,   10, road3,road3, road3, road3, road3);
		drawFourPlane( -13.9-15,   18.5+12.0,  10, -13.9-15,   18.5+12.0,  8.7,  -12.7-2.8-15, 13+15,  8.7,  -12.7-2.8-15, 13+15, 10, -13.1-15,   18.5+11.0,   10, -13.1-15,   18.5+11.0,    8.7,  -11.7-3.2-15, 11.9+15,    8.7,  -11.7-3.2-15, 11.9+15,   10, road3,road3, road3, road3, road3);
		drawFourPlane( -14.5-20,   18.5+16.0,  10, -14.5-20,   18.5+16.0,  8.7,  -12.7-2.8-20, 13+20,  8.7,  -12.7-2.8-20, 13+20, 10, -13.7-20,   18.5+15.5,   10, -13.7-20,   18.5+15.5,    8.7,  -11.7-3.2-20, 11.9+20,    8.7,  -11.7-3.2-20, 11.9+20,   10, road3,road3, road3, road3, road3);

		drawFourPlane( -12.7,      17.5,       10, -12.7,      17.5,       8.7,  -12.7-6.3,      16.3,      8.7,  -12.7-6.3,      16.3,      10, -12.9,      17.0,      10, -12.9,      17.0,         8.7,  -12.7-5.9,      15.7,         8.7,  -12.7-5.9,      15.7,        10, road3,road3, road3, road3, road3);
		drawFourPlane( -13.0-5,    17.5+4.2,   10, -13.0-5,    17.5+4.2,   8.7,  -12.7-6.3-4.5,  16.3+4.8,  8.7,  -12.7-6.3-4.5,  16.3+4.8,  10, -12.9-5,    17.0+4.0,  10, -12.9-5,    17.0+4.0,     8.7,  -12.7-5.9-4.5,  15.7+4.8,     8.7,  -12.7-5.9-4.5,  15.7+4.8,    10, road3,road3, road3, road3, road3);
		drawFourPlane( -13.3-10,   17.5+8.3,   10, -13.3-10,   17.5+8.3,   8.7,  -12.7-6.3-8.5,  16.3+9.0,  8.7,  -12.7-6.3-8.5,  16.3+9.0,  10, -12.9-10.9, 17.0+8.1,  10, -12.9-10.9, 17.0+8.1,     8.7,  -12.7-5.9-8.5,  15.7+9.0,     8.7,  -12.7-5.9-8.5,  15.7+9.0,    10, road3,road3, road3, road3, road3);
		drawFourPlane( -13.9-15,   17.5+12.6,  10, -13.9-15,   17.5+12.6,  8.7,  -12.7-6.3-13.5, 16.3+13.9, 8.7,  -12.7-6.3-13.5, 16.3+13.9, 10, -12.9-15.5, 17.0+12.2, 10, -12.9-15.5, 17.0+12.2,    8.7,  -12.7-5.9-13.5, 15.7+13.8,    8.7,  -12.7-5.9-13.5, 15.7+13.8,   10, road3,road3, road3, road3, road3);
		drawFourPlane( -14.0-20,   17.5+17.5,  10, -14.0-20,   17.5+17.5,  8.7,  -12.7-6.3-19.0, 16.3+19.0, 8.7,  -12.7-6.3-19.0, 16.3+19.0, 10, -12.9-19.5, 17.0+17.0, 10, -12.9-19.5, 17.0+17.0,    8.7,  -12.7-5.9-19.0, 15.7+19.0,    8.7,  -12.7-5.9-19.0, 15.7+19.0,   10, road3,road3, road3, road3, road3);

	}glPopMatrix();

}
void drawWindow()
{
	glPushMatrix();{
		glTranslatef(0 , 38+19, 8);
		//glRotatef(-90, 1, 0, 0);
		drawPlane(3, 2.5, 1.5, -3, 2.5, 1.5, -3, 6, 1.5, 3, 6, 1.5, window1);
		drawPlane(3, 0, 0, -3, 0, 0, -3, 2.5, 1.5, 3, 2.5, 1.5, window2);
		drawPlane(3, 6, 1.5, -3, 6, 1.5, -3, 6, 0, 3, 6, 0, window3);
		drawPlane(3, 2.5, 0, 3, 2.5, 1.5, 3, 6, 1.5, 3, 6, 0, window3);
		drawPlane(-3, 2.5, 0, -3, 2.5, 1.5, -3, 6, 1.5, -3, 6, 0, window3);
		drawTriangle(3, 2.5, 0, 3, 0, 0, 3, 2.5, 1.5, window3);
		drawTriangle(-3, 2.5, 0, -3, 0, 0, -3, 2.5, 1.5, window3);
	}glPopMatrix();

	glPushMatrix();{
		glTranslatef(8 , 38+19, 0);
		glRotatef(90, 0, 1, 0);
		drawPlane(3, 2.5, 1.5, -3, 2.5, 1.5, -3, 6, 1.5, 3, 6, 1.5, window1);
		drawPlane(3, 0, 0, -3, 0, 0, -3, 2.5, 1.5, 3, 2.5, 1.5, window2);
		drawPlane(3, 6, 1.5, -3, 6, 1.5, -3, 6, 0, 3, 6, 0, window3);
		drawPlane(3, 2.5, 0, 3, 2.5, 1.5, 3, 6, 1.5, 3, 6, 0, window3);
		drawPlane(-3, 2.5, 0, -3, 2.5, 1.5, -3, 6, 1.5, -3, 6, 0, window3);
		drawTriangle(3, 2.5, 0, 3, 0, 0, 3, 2.5, 1.5, window3);
		drawTriangle(-3, 2.5, 0, -3, 0, 0, -3, 2.5, 1.5, window3);
	}glPopMatrix();

	glPushMatrix();{
		glTranslatef(0 , 38+19, -8);
		glRotatef(180, 0, 1, 0);
		drawPlane(3, 2.5, 1.5, -3, 2.5, 1.5, -3, 6, 1.5, 3, 6, 1.5, window1);
		drawPlane(3, 0, 0, -3, 0, 0, -3, 2.5, 1.5, 3, 2.5, 1.5, window2);
		drawPlane(3, 6, 1.5, -3, 6, 1.5, -3, 6, 0, 3, 6, 0, window3);
		drawPlane(3, 2.5, 0, 3, 2.5, 1.5, 3, 6, 1.5, 3, 6, 0, window3);
		drawPlane(-3, 2.5, 0, -3, 2.5, 1.5, -3, 6, 1.5, -3, 6, 0, window3);
		drawTriangle(3, 2.5, 0, 3, 0, 0, 3, 2.5, 1.5, window3);
		drawTriangle(-3, 2.5, 0, -3, 0, 0, -3, 2.5, 1.5, window3);
	}glPopMatrix();

	glPushMatrix();{
		glTranslatef(-8 , 38+19, 0);
		glRotatef(270, 0, 1, 0);
		drawPlane(3, 2.5, 1.5, -3, 2.5, 1.5, -3, 6, 1.5, 3, 6, 1.5, window1);
		drawPlane(3, 0, 0, -3, 0, 0, -3, 2.5, 1.5, 3, 2.5, 1.5, window2);
		drawPlane(3, 6, 1.5, -3, 6, 1.5, -3, 6, 0, 3, 6, 0, window3);
		drawPlane(3, 2.5, 0, 3, 2.5, 1.5, 3, 6, 1.5, 3, 6, 0, window3);
		drawPlane(-3, 2.5, 0, -3, 2.5, 1.5, -3, 6, 1.5, -3, 6, 0, window3);
		drawTriangle(3, 2.5, 0, 3, 0, 0, 3, 2.5, 1.5, window3);
		drawTriangle(-3, 2.5, 0, -3, 0, 0, -3, 2.5, 1.5, window3);
	}glPopMatrix();


}

void drawWindow1()
{
	glPushMatrix();{
		glTranslatef(8 , 38+3, 0);
		glRotatef(90, 0, 1, 0);
		drawPlane(3, 2.5, 1.5, -3, 2.5, 1.5, -3, 6, 1.5, 3, 6, 1.5, window4);
		drawPlane(3, 2.5, 1.5, -3, 2.5, 1.5, -3, 2.5, 0, 3, 2.5, 0, window2); //bottm
		drawPlane(3, 6, 1.5, -3, 6, 1.5, -3, 6, 0, 3, 6, 0, window3); //top
		drawPlane(3, 2.5, 0, 3, 2.5, 1.5, 3, 6, 1.5, 3, 6, 0, window3); //right
		drawPlane(-3, 2.5, 0, -3, 2.5, 1.5, -3, 6, 1.5, -3, 6, 0, window3); //left
		drawTriangle(3, 2.5, 0, 3, 0, 0, 3, 2.5, 1.5, window3); //right
		drawTriangle(-3, 2.5, 0, -3, 0, 0, -3, 2.5, 1.5, window3); //left
		drawPlane(3, 0, 0, 2.5, 0, 0, 2.5, 2.5, 1.5, 3, 2.5, 1.5, window5); //right
		drawPlane(-3, 0, 0, -2.5, 0, 0, -2.5, 2.5, 1.5, -3, 2.5, 1.5, window5); //left
		drawTriangle(2.5, 2.5, 0, 2.5, 0, 0, 2.5, 2.5, 1.5, window3); //right
		drawTriangle(-2.5, 2.5, 0, -2.5, 0, 0, -2.5, 2.5, 1.5, window3); //left

		drawPlane(1.5,  1.0, 0,  1.0, 1.0, 0,  1.0, 2.5, 1.5,  1.5, 2.5, 1.5, window5); //right
		drawPlane(-1.5, 1.0, 0, -1.0, 1.0, 0, -1.0, 2.5, 1.5, -1.5, 2.5, 1.5, window5); //left
		drawTriangle(1.5,  2.5, 0,  1.5, 1.0, 0,  1.5, 2.5, 1.5, window3); //right
		drawTriangle(-1.5, 2.5, 0, -1.5, 1.0, 0, -1.5, 2.5, 1.5, window3); //left
		drawTriangle(1.0,  2.5, 0,  1.0, 1.0, 0,  1.0, 2.5, 1.5, window3); //right
		drawTriangle(-1.0, 2.5, 0, -1.0, 1.0, 0, -1.0, 2.5, 1.5, window3); //left

	}glPopMatrix();

	glPushMatrix();{
		glTranslatef(-8 , 38+3, 0);
		glRotatef(270, 0, 1, 0);
		drawPlane(3, 2.5, 1.5, -3, 2.5, 1.5, -3, 6, 1.5, 3, 6, 1.5, window4);
		drawPlane(3, 2.5, 1.5, -3, 2.5, 1.5, -3, 2.5, 0, 3, 2.5, 0, window2); //bottm
		drawPlane(3, 6, 1.5, -3, 6, 1.5, -3, 6, 0, 3, 6, 0, window3); //top
		drawPlane(3, 2.5, 0, 3, 2.5, 1.5, 3, 6, 1.5, 3, 6, 0, window3); //right
		drawPlane(-3, 2.5, 0, -3, 2.5, 1.5, -3, 6, 1.5, -3, 6, 0, window3); //left
		drawTriangle(3, 2.5, 0, 3, 0, 0, 3, 2.5, 1.5, window3); //right
		drawTriangle(-3, 2.5, 0, -3, 0, 0, -3, 2.5, 1.5, window3); //left
		drawPlane(3, 0, 0, 2.5, 0, 0, 2.5, 2.5, 1.5, 3, 2.5, 1.5, window5); //right
		drawPlane(-3, 0, 0, -2.5, 0, 0, -2.5, 2.5, 1.5, -3, 2.5, 1.5, window5); //left
		drawTriangle(2.5, 2.5, 0, 2.5, 0, 0, 2.5, 2.5, 1.5, window3); //right
		drawTriangle(-2.5, 2.5, 0, -2.5, 0, 0, -2.5, 2.5, 1.5, window3); //left

		drawPlane(1.5,  1.0, 0,  1.0, 1.0, 0,  1.0, 2.5, 1.5,  1.5, 2.5, 1.5, window5); //right
		drawPlane(-1.5, 1.0, 0, -1.0, 1.0, 0, -1.0, 2.5, 1.5, -1.5, 2.5, 1.5, window5); //left
		drawTriangle(1.5,  2.5, 0,  1.5, 1.0, 0,  1.5, 2.5, 1.5, window3); //right
		drawTriangle(-1.5, 2.5, 0, -1.5, 1.0, 0, -1.5, 2.5, 1.5, window3); //left
		drawTriangle(1.0,  2.5, 0,  1.0, 1.0, 0,  1.0, 2.5, 1.5, window3); //right
		drawTriangle(-1.0, 2.5, 0, -1.0, 1.0, 0, -1.0, 2.5, 1.5, window3); //left

	}glPopMatrix();


}

void drawEllipse(float radius, float radius1,int slices,int stacks)
{
	struct point points[100][100];
	int i,j;
	double h,r,t;
	double ratio = 1;
	double x = radius/slices; 
	for(i= 0;i<=stacks;i++)
	{
		h = sin(((double)i/(double)stacks)*(pi/2));	
		r = .8*exp(-(double)(i*i)*.1);
		t= cos(((double)i/(double)stacks)*(pi/2));
		for(j= 0;j<=slices*2;j++)
		{
			points[i][j].x = ((radius) * cos(((double)j/(double)slices)*2*pi)*t*.9);
			points[i][j].y = ((radius) * sin(((double)j/(double)slices)*2*pi)*t*.9);
			points[i][j].z = radius1*h;
		}
	}
	for(i= 0;i<stacks;i++)
	{
		for(j= 0;j<slices*2;j++)
		{
			GLuint texid=baseCyl1;
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D,texid);
			glNormal3f(1.0,0.0,0.0);
			glBegin(GL_QUADS);{
				glTexCoord2f(1,0); glVertex3f(points[i][j].x,points[i][j].y,points[i][j].z);
				glTexCoord2f(0,0); glVertex3f(points[i][j+1].x,points[i][j+1].y,points[i][j+1].z);
				glTexCoord2f(0,1); glVertex3f(points[i+1][j+1].x,points[i+1][j+1].y,points[i+1][j+1].z);
				glTexCoord2f(1,1); glVertex3f(points[i+1][j].x,points[i+1][j].y,points[i+1][j].z);
				
			}glEnd();
		}
		
	}
}
void drawBoat()
{
	double coef[4], coef1[4];
	glPushMatrix();{
		//glTranslatef(0,6,0);
		//glRotatef(90, 1, 0,0);
		coef[0] = 0;	//-1.x
		coef[1] = 1;	//0.y
		coef[2] = 0;	//0.z
		coef[3] = 0;	
		glClipPlane(GL_CLIP_PLANE0,coef);
	    glEnable(GL_CLIP_PLANE0);{
			coef1[0] = 0;	//-1.x
			coef1[1] = 0;	//0.y
			coef1[2] = 0;	//0.z
			coef1[3] = 0;
			glClipPlane(GL_CLIP_PLANE1,coef1);

			glEnable(GL_CLIP_PLANE1);{
				drawEllipse(12, 25, 20,20);
			}glDisable(GL_CLIP_PLANE1);
		}glDisable(GL_CLIP_PLANE0);
	}glPopMatrix();

	glPushMatrix();{
		//glTranslatef(0,6,0);
		glRotatef(180, 0, 1,0);
		coef[0] = 0;	//-1.x
		coef[1] = 1;	//0.y
		coef[2] = 0;	//0.z
		coef[3] = 0;	
		glClipPlane(GL_CLIP_PLANE0,coef);
	    glEnable(GL_CLIP_PLANE0);{
			coef1[0] = 0;	//-1.x
			coef1[1] = 0;	//0.y
			coef1[2] = 0;	//0.z
			coef1[3] = 0;
			glClipPlane(GL_CLIP_PLANE1,coef1);

			glEnable(GL_CLIP_PLANE1);{
				drawEllipse(12, 25, 20,20);
			}glDisable(GL_CLIP_PLANE1);
		}glDisable(GL_CLIP_PLANE0);
	}glPopMatrix();
}
void keyboardListener(unsigned char key, int x,int y){
	switch(key){

		case '1':
			//drawgrid=1-drawgrid;
			cam_12_12_1992.yaw_12_12(.8);
			break;
	    case '2':
			//drawgrid=1-drawgrid;
			cam_12_12_1992.yaw_12_12(-.8);
			break;
		case '3':
			//drawgrid=1-drawgrid;
			cam_12_12_1992.pitch_12_12(.8);
			break;
		case '4':
			//drawgrid=1-drawgrid;
			cam_12_12_1992.pitch_12_12(-.8);
			break;
		case '5':	
			cam_12_12_1992.roll_12_12(.8);
			break;
		case '6':	
			cam_12_12_1992.roll_12_12(-.8);
			break;
		case '7':	
			diffusePoint[0]=0.0;
			diffusePoint[1]=0.0;
			diffusePoint[2]=1.0;
            glLightfv(GL_LIGHT1, GL_DIFFUSE, diffusePoint);
			break;
		case '8':	
			diffusePoint[0]=1.0;
			diffusePoint[1]=1.0;
			diffusePoint[2]=1.0;
            glLightfv(GL_LIGHT1, GL_DIFFUSE, diffusePoint);
			break;
		case '9':	
			angle+=0.3;
			break;
		default:
			break;
	}
}


void specialKeyListener(int key, int x,int y){
	switch(key){
		case GLUT_KEY_DOWN:		//move backward
			cam_12_12_1992.slide_12_12(0,0,.8);
			break;
		case GLUT_KEY_UP:		//move forward
			cam_12_12_1992.slide_12_12(0,0,-.8);
			break;

		case GLUT_KEY_RIGHT:   //move right
			cam_12_12_1992.slide_12_12(.8,0,0);
			break;
		case GLUT_KEY_LEFT:    //move left
			cam_12_12_1992.slide_12_12(-.8,0,0);
			break;

		case GLUT_KEY_PAGE_UP:  //move upward
			cam_12_12_1992.slide_12_12(0,.8,0);
			break;
		case GLUT_KEY_PAGE_DOWN:  //move downward
			cam_12_12_1992.slide_12_12(0,-.8,0);
			break;

		case GLUT_KEY_INSERT:
			break;

		case GLUT_KEY_HOME:
			break;
		case GLUT_KEY_END:
			break;

		default:
			break;
	}
}


void mouseListener(int button, int state, int x, int y){	//x, y is the x-y of the screen (2D)
	switch(button){
		case GLUT_LEFT_BUTTON:
			if(state == GLUT_DOWN){		// 2 times?? in ONE click? -- solution is checking DOWN or UP
				drawaxes=1-drawaxes;	
			}
			break;

		case GLUT_RIGHT_BUTTON:
			//........
			break;

		case GLUT_MIDDLE_BUTTON:
			//........
			break;

		default:
			break;
	}
}



void display(){

	//clear the display
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0,0,0,0);	//color black
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	//again select MODEL-VIEW
	glMatrixMode(GL_MODELVIEW);


	/****************************
	/ Add your objects from here
	****************************/
	//add objects

	glPushMatrix();{
		//glRotatef(angle, 0, 0, 1);
		lightDir[0] = 100.0*cos(angle);
		lightDir[1] = 100.0*sin(angle);
		lightDir[2] = 100;
		glLightfv(GL_LIGHT1, GL_POSITION, lightDir);
    }glPopMatrix();

	
//	drawAxes();
	
	
	glPushMatrix();{
		glTranslatef(-50.0, 0, 0);
		glRotatef(180, 0, 1, 0);
		drawStencil();
		//drawAxes();
		//drawGrid();
		//glColor3f(1.0, 1.0, 0.0);
		//drawFloor();
		drawBaseCyllinder();
		drawMiddleBody();
		drawTop();
		drawRoad();
		drawWindow();
		drawWindow1();
		drawBoat();
	}glPopMatrix();

	drawAxes();
	drawGrid();
	drawFloor();

	glPushMatrix();{
		glTranslatef(50.0, 0, 0);
		drawStencil();
		//drawAxes();
		//drawGrid();
		//glColor3f(1.0, 1.0, 0.0);
	
		drawBaseCyllinder();
		drawMiddleBody();
		drawTop();
		drawRoad();
		drawWindow();
		drawWindow1();
		drawBoat();
	}glPopMatrix();

	//ADD this line in the end --- if you use double buffer (i.e. GL_DOUBLE)
	glutSwapBuffers();
}

void animate(){
	//angle+=0.05;
	//codes for any changes in Models, Camera
	glutPostRedisplay();
}

void init(){
	//codes for initialization
	drawgrid=0;
	drawaxes=1;
	cameraHeight=100.0;
	cameraAngle=1.0;
	angle=0;
	//sizeSphere=0;
	sizeSphere=15;
	//sizeCube=0.0;
	sizeCube=15.0;
	//radius = 25;
	radius = 10;
	//radiCylinder=25,heightCylinder=0;
	radiCylinder=10,heightCylinder=30;
	func();
	//clear the screen
	glClearColor(0,0,0,0);

	glShadeModel(GL_SMOOTH);

		//Add global ambient light
    GLfloat lmodel_ambient[] = { 1.0, 1.0, 1.0, 1.0 }; //color of the global ambient light
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);

	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	diffusePoint[0] = 1.0;
	diffusePoint[1] = 1.0;
	diffusePoint[2] = 1.0;
    glLightfv(GL_LIGHT1, GL_DIFFUSE, diffusePoint); //
    glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT1, GL_POSITION, lightDir);

	GLfloat spotLightColour[] = {1.0,0.0,0.0, 1.0}; 
	GLfloat spotLightDir[] = {0.0, 0.0 , 0.0, 1.0 };
	GLfloat diffuseSpot[] = {1, 0, 0, 1.0};
    GLfloat ambientSpot[] = {1, 0, 0, 1.0};
	//glLightfv(GL_LIGHT2, GL_AMBIENT, ambientSpot);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuseSpot);
	
	glLightfv(GL_LIGHT2,GL_SPECULAR,spotLightColour);

	glLightfv(GL_LIGHT2, GL_POSITION, spotLightDir);

	glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 80.0);
    glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 0.0);
	glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, 4.0);
    GLfloat spot_direction[] = { 1.0, 0.0, 0.0};
    glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spot_direction);

    glEnable(GL_NORMALIZE); //Automatically normalize normals needed by the illumination model
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0); //Enable light #0
    glEnable(GL_LIGHT1); //Enable light #1
	glEnable(GL_LIGHT2); //Enable light #2

	//glEnable(GL_COLOR_MATERIAL);
    //glEnable(GL_DEPTH_TEST);


	//glEnable(GL_DEPTH_TEST);
}

int main(int argc, char **argv){
	glutInit(&argc,argv);
	glutInitWindowSize(1500, 1500);
	glutInitWindowPosition(0, 0);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);	//Depth, Double buffer, RGB color

	glutCreateWindow("My OpenGL Program");

	init();

	glEnable(GL_DEPTH_TEST);	//enable Depth Testing

    cam_12_12_1992.set_12_12(80, 20, 90, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    cam_12_12_1992.setShape_12_12(80.0, 1, 1, 10000.0);

	glutDisplayFunc(display);	//display callback function
	glutIdleFunc(animate);		//what you want to do in the idle time (when no drawing is occuring)

	glutKeyboardFunc(keyboardListener);
	glutSpecialFunc(specialKeyListener);
	glutMouseFunc(mouseListener);

	glutMainLoop();		//The main loop of OpenGL

	return 0;
}
