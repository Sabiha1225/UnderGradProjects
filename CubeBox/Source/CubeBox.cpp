#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#include<GL/glut.h>


#define pi (double)2*acos((double)0)

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

struct point
{
	double x,y,z;
};


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


void keyboardListener(unsigned char key, int x,int y){
	switch(key){

		case '1':	
			drawgrid=1-drawgrid;
			break;

		default:
			break;
	}
}


void specialKeyListener(int key, int x,int y){
	switch(key){
		case GLUT_KEY_DOWN:		//down arrow key
			cameraHeight -= 3.0;
			break;
		case GLUT_KEY_UP:		// up arrow key
			cameraHeight += 3.0;
			break;

		case GLUT_KEY_RIGHT:
			cameraAngle += 0.03;
			break;
		case GLUT_KEY_LEFT:
			cameraAngle -= 0.03;
			break;

		case GLUT_KEY_PAGE_UP:
			if(radius<25.0)
			{
				sizeSphere = sizeSphere-1.0;
				sizeCube = sizeCube-1.0;
				radiCylinder = radiCylinder+1;
				heightCylinder = heightCylinder-2;
				radius = radius+1.0;
			}
			break;
		case GLUT_KEY_PAGE_DOWN:
			if(radius>0.0)
			{
				sizeSphere = sizeSphere+1.0;
				sizeCube = sizeCube+1.0;
				radiCylinder = radiCylinder-1;
				heightCylinder = heightCylinder+2;
				radius = radius-1.0;
			}
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

	/********************
	/ set-up camera here
	********************/ 
	//load the correct matrix -- MODEL-VIEW matrix
	glMatrixMode(GL_MODELVIEW);

	//initialize the matrix
	glLoadIdentity();

	//now give three info
	//1. where is the camera (viewer)?
	//2. where is the camera looking?
	//3. Which direction is the camera's UP direction?

	//gluLookAt(100,100,100,	0,0,0,	0,0,1);
	gluLookAt(100*cos(cameraAngle), 100*sin(cameraAngle), cameraHeight,		0,0,0,		0,0,1);
	//gluLookAt(0,-1,150,	0,0,0,	0,0,1);
	
	
	//again select MODEL-VIEW
	glMatrixMode(GL_MODELVIEW);


	/****************************
	/ Add your objects from here
	****************************/
	//add objects

	drawAxes();
	drawGrid();
	
	drawSquare(sizeCube);
	glColor3f(0.5, 0.5, 0.5);
	glPushMatrix();{
		//glColor3f(0.3, 0.1, 0.6);
		glTranslatef(heightCylinder/2, heightCylinder/2, -heightCylinder/2);
		double coef[4];
		coef[0] = 1;	//-1.x
		coef[1] = 0;	//0.y
		coef[2] = 0;	//0.z
		coef[3] = 0;	//10
		glClipPlane(GL_CLIP_PLANE0,coef);
		glEnable(GL_CLIP_PLANE0);{
			double coef1[4];
			coef1[0] = 0;	//-1.x
			coef1[1] = 1;	//0.y
			coef1[2] = 0;	//0.z
			coef1[3] = 0;	//10
			glClipPlane(GL_CLIP_PLANE1,coef1);
			glEnable(GL_CLIP_PLANE1);{
				GLUquadricObj *quadratic;
				quadratic = gluNewQuadric();
				gluCylinder(quadratic,radiCylinder,radiCylinder,heightCylinder,slices,stacks);
			}glDisable(GL_CLIP_PLANE1);
		}glDisable(GL_CLIP_PLANE0);
	}glPopMatrix();

	glPushMatrix();{
		//glColor3f(0.3, 0.1, 0.6);
		glTranslatef(heightCylinder/2, -heightCylinder/2, -heightCylinder/2);
		//glColor3f(0.5, 0.5, 0.5);
		double coef2[4];
		coef2[0] = 1;	//-1.x
		coef2[1] = 0;	//0.y
		coef2[2] = 0;	//0.z
		coef2[3] = 0;	//10
		glClipPlane(GL_CLIP_PLANE0,coef2);
		glEnable(GL_CLIP_PLANE0);{
			double coef3[4];
			coef3[0] = 0;	//-1.x
			coef3[1] = -1;	//0.y
			coef3[2] = 0;	//0.z
			coef3[3] = 0;	//10
			glClipPlane(GL_CLIP_PLANE1,coef3);
			glEnable(GL_CLIP_PLANE1);{
				GLUquadricObj *quadratic;
				quadratic = gluNewQuadric();
				gluCylinder(quadratic,radiCylinder,radiCylinder,heightCylinder,slices,stacks);
			}glDisable(GL_CLIP_PLANE1);
		}glDisable(GL_CLIP_PLANE0);
	}glPopMatrix();

	glPushMatrix();{
		//glColor3f(0.5, 0.5, 0.5);
		glTranslatef(-heightCylinder/2, -heightCylinder/2, -heightCylinder/2);
		//glColor3f(0.3, 0.1, 0.6);
		double coef4[4];
		coef4[0] = -1;	//-1.x
		coef4[1] = 0;	//0.y
		coef4[2] = 0;	//0.z
		coef4[3] = 0;	//10
		glClipPlane(GL_CLIP_PLANE0,coef4);
		glEnable(GL_CLIP_PLANE0);{
			double coef5[4];
			coef5[0] = 0;	//-1.x
			coef5[1] = -1;	//0.y
			coef5[2] = 0;	//0.z
			coef5[3] = 0;	//10
			glClipPlane(GL_CLIP_PLANE1,coef5);
			glEnable(GL_CLIP_PLANE1);{
				GLUquadricObj *quadratic;
				quadratic = gluNewQuadric();
				gluCylinder(quadratic,radiCylinder,radiCylinder,heightCylinder,slices,stacks);
			}glDisable(GL_CLIP_PLANE1);
		}glDisable(GL_CLIP_PLANE0);
	}glPopMatrix();

	glPushMatrix();{
		//glColor3f(0.5, 0.5, 0.5);
		glTranslatef(-heightCylinder/2, heightCylinder/2, -heightCylinder/2);
		//glColor3f(0.3, 0.1, 0.6);
		double coef6[4];
		coef6[0] = -1;	//-1.x
		coef6[1] = 0;	//0.y
		coef6[2] = 0;	//0.z
		coef6[3] = 0;	//10
		glClipPlane(GL_CLIP_PLANE0,coef6);
		glEnable(GL_CLIP_PLANE0);{
			double coef7[4];
			coef7[0] = 0;	//-1.x
			coef7[1] = 1;	//0.y
			coef7[2] = 0;	//0.z
			coef7[3] = 0;	//10
			glClipPlane(GL_CLIP_PLANE1,coef7);
			glEnable(GL_CLIP_PLANE1);{
				GLUquadricObj *quadratic;
				quadratic = gluNewQuadric();
				gluCylinder(quadratic,radiCylinder,radiCylinder,heightCylinder,slices,stacks);
			}glDisable(GL_CLIP_PLANE1);
		}glDisable(GL_CLIP_PLANE0);
	}glPopMatrix();
	
//--------------------------------------------------------------------------------
       glPushMatrix();{
		   glTranslatef(-heightCylinder/2, heightCylinder/2, heightCylinder/2);
		//glColor3f(0.6, 0.1, 0.2);
		//glColor3f(0.5, 0.5, 0.5);
		   double coef[4];
		coef[0] = 1;	//-1.x
		coef[1] = 0;	//0.y
		coef[2] = 0;	//0.z
		coef[3] = 0;	//10
		glClipPlane(GL_CLIP_PLANE0,coef);
		glEnable(GL_CLIP_PLANE0);{
			double coef1[4];
			coef1[0] = 0;	//-1.x
			coef1[1] = 1;	//0.y
			coef1[2] = 0;	//0.z
			coef1[3] = 0;	//10
			glClipPlane(GL_CLIP_PLANE1,coef1);
			glEnable(GL_CLIP_PLANE1);{
				
				//glTranslatef(0, 0, 0);
				glRotatef(90,0,1,0);
				GLUquadricObj *quadratic;
				quadratic = gluNewQuadric();
				gluCylinder(quadratic,radiCylinder,radiCylinder,heightCylinder,slices,stacks);
			}glDisable(GL_CLIP_PLANE1);
		}glDisable(GL_CLIP_PLANE0);
	}glPopMatrix();
    glPushMatrix();{
		   glTranslatef(-heightCylinder/2, heightCylinder/2, -heightCylinder/2);
		//glColor3f(0.6, 0.1, 0.2);
		//glColor3f(0.5, 0.5, 0.5);
		double coef[4];
		coef[0] = 1;	//-1.x
		coef[1] = 0;	//0.y
		coef[2] = 0;	//0.z
		coef[3] = 0;	//10
		glClipPlane(GL_CLIP_PLANE0,coef);
		glEnable(GL_CLIP_PLANE0);{
			double coef1[4];
			coef1[0] = 0;	//-1.x
			coef1[1] = 1;	//0.y
			coef1[2] = 0;	//0.z
			coef1[3] = 0;	//10
			glClipPlane(GL_CLIP_PLANE1,coef1);
			glEnable(GL_CLIP_PLANE1);{
				
				//glTranslatef(0, 0, 0);
				glRotatef(90,0,1,0);
				GLUquadricObj *quadratic;
				quadratic = gluNewQuadric();
				gluCylinder(quadratic,radiCylinder,radiCylinder,heightCylinder,slices,stacks);
			}glDisable(GL_CLIP_PLANE1);
		}glDisable(GL_CLIP_PLANE0);
	}glPopMatrix();
//----------------------------------------------------------------------------------
	glPushMatrix();{
		   glTranslatef(-heightCylinder/2, -heightCylinder/2, heightCylinder/2);
		//glColor3f(0.6, 0.1, 0.2);
		//glColor3f(0.5, 0.5, 0.5);
		   double coef[4];
		coef[0] = -1;	//-1.x
		coef[1] = 0;	//0.y
		coef[2] = 0;	//0.z
		coef[3] = 0;	//10
		glClipPlane(GL_CLIP_PLANE0,coef);
		glEnable(GL_CLIP_PLANE0);{
			double coef1[4];
			coef1[0] = 0;	//-1.x
			coef1[1] = 1;	//0.y
			coef1[2] = 0;	//0.z
			coef1[3] = 0;	//10
			glClipPlane(GL_CLIP_PLANE1,coef1);
			glEnable(GL_CLIP_PLANE1);{
				
				//glTranslatef(0, 0, 0);
				glRotatef(-90,1,0,0);
				GLUquadricObj *quadratic;
				quadratic = gluNewQuadric();
				gluCylinder(quadratic,radiCylinder,radiCylinder,heightCylinder,slices,stacks);
			}glDisable(GL_CLIP_PLANE1);
		}glDisable(GL_CLIP_PLANE0);
	}glPopMatrix();
	glPushMatrix();{
		   glTranslatef(-heightCylinder/2, -heightCylinder/2, -heightCylinder/2);
		//glColor3f(0.6, 0.1, 0.2);
		//glColor3f(0.5, 0.5, 0.5);
		   double coef[4];
		coef[0] = -1;	//-1.x
		coef[1] = 0;	//0.y
		coef[2] = 0;	//0.z
		coef[3] = 0;	//10
		glClipPlane(GL_CLIP_PLANE0,coef);
		glEnable(GL_CLIP_PLANE0);{
			double coef1[4];
			coef1[0] = 0;	//-1.x
			coef1[1] = 1;	//0.y
			coef1[2] = 0;	//0.z
			coef1[3] = 0;	//10
			glClipPlane(GL_CLIP_PLANE1,coef1);
			glEnable(GL_CLIP_PLANE1);{
				
				//glTranslatef(0, 0, 0);
				glRotatef(-90,1,0,0);
				GLUquadricObj *quadratic;
				quadratic = gluNewQuadric();
				gluCylinder(quadratic,radiCylinder,radiCylinder,heightCylinder,slices,stacks);
			}glDisable(GL_CLIP_PLANE1);
		}glDisable(GL_CLIP_PLANE0);
	}glPopMatrix();
//--------------------------------------------------------------------
	glPushMatrix();{
		   glTranslatef(heightCylinder/2, -heightCylinder/2, heightCylinder/2);
		//glColor3f(0.6, 0.1, 0.2);
		//glColor3f(0.5, 0.5, 0.5);
		   double coef[4];
		coef[0] = -1;	//-1.x
		coef[1] = 0;	//0.y
		coef[2] = 0;	//0.z
		coef[3] = 0;	//10
		glClipPlane(GL_CLIP_PLANE0,coef);
		glEnable(GL_CLIP_PLANE0);{
			double coef1[4];
			coef1[0] = 0;	//-1.x
			coef1[1] = -1;	//0.y
			coef1[2] = 0;	//0.z
			coef1[3] = 0;	//10
			glClipPlane(GL_CLIP_PLANE1,coef1);
			glEnable(GL_CLIP_PLANE1);{
				
				//glTranslatef(0, 0, 0);
				glRotatef(-90,0,1,0);
				GLUquadricObj *quadratic;
				quadratic = gluNewQuadric();
				gluCylinder(quadratic,radiCylinder,radiCylinder,heightCylinder,slices,stacks);
			}glDisable(GL_CLIP_PLANE1);
		}glDisable(GL_CLIP_PLANE0);
	}glPopMatrix();
	glPushMatrix();{
		   glTranslatef(heightCylinder/2, -heightCylinder/2, -heightCylinder/2);
		//glColor3f(0.6, 0.1, 0.2);
		//glColor3f(0.5, 0.5, 0.5);
		   double coef[4];
		coef[0] = -1;	//-1.x
		coef[1] = 0;	//0.y
		coef[2] = 0;	//0.z
		coef[3] = 0;	//10
		glClipPlane(GL_CLIP_PLANE0,coef);
		glEnable(GL_CLIP_PLANE0);{
			double coef1[4];
			coef1[0] = 0;	//-1.x
			coef1[1] = -1;	//0.y
			coef1[2] = 0;	//0.z
			coef1[3] = 0;	//10
			glClipPlane(GL_CLIP_PLANE1,coef1);
			glEnable(GL_CLIP_PLANE1);{
				
				//glTranslatef(0, 0, 0);
				glRotatef(-90,0,1,0);
				GLUquadricObj *quadratic;
				quadratic = gluNewQuadric();
				gluCylinder(quadratic,radiCylinder,radiCylinder,heightCylinder,slices,stacks);
			}glDisable(GL_CLIP_PLANE1);
		}glDisable(GL_CLIP_PLANE0);
	}glPopMatrix();
//--------------------------------------------------------------------------
	glPushMatrix();{
		   glTranslatef(heightCylinder/2, heightCylinder/2, heightCylinder/2);
		//glColor3f(0.6, 0.1, 0.2);
		//glColor3f(0.5, 0.5, 0.5);
		   double coef[4];
		coef[0] = 1;	//-1.x
		coef[1] = 0;	//0.y
		coef[2] = 0;	//0.z
		coef[3] = 0;	//10
		glClipPlane(GL_CLIP_PLANE0,coef);
		glEnable(GL_CLIP_PLANE0);{
			double coef1[4];
			coef1[0] = 0;	//-1.x
			coef1[1] = -1;	//0.y
			coef1[2] = 0;	//0.z
			coef1[3] = 0;	//10
			glClipPlane(GL_CLIP_PLANE1,coef1);
			glEnable(GL_CLIP_PLANE1);{
				
				//glTranslatef(0, 0, 0);
				glRotatef(90,1,0,0);
				GLUquadricObj *quadratic;
				quadratic = gluNewQuadric();
				gluCylinder(quadratic,radiCylinder,radiCylinder,heightCylinder,slices,stacks);
			}glDisable(GL_CLIP_PLANE1);
		}glDisable(GL_CLIP_PLANE0);
	}glPopMatrix();
	glPushMatrix();{
		   glTranslatef(heightCylinder/2, heightCylinder/2, -heightCylinder/2);
		//glColor3f(0.6, 0.1, 0.2);
		//glColor3f(0.5, 0.5, 0.5);
		   double coef[4];
		coef[0] = 1;	//-1.x
		coef[1] = 0;	//0.y
		coef[2] = 0;	//0.z
		coef[3] = 0;	//10
		glClipPlane(GL_CLIP_PLANE0,coef);
		glEnable(GL_CLIP_PLANE0);{
			double coef1[4];
			coef1[0] = 0;	//-1.x
			coef1[1] = -1;	//0.y
			coef1[2] = 0;	//0.z
			coef1[3] = 0;	//10
			glClipPlane(GL_CLIP_PLANE1,coef1);
			glEnable(GL_CLIP_PLANE1);{
				
				//glTranslatef(0, 0, 0);
				glRotatef(90,1,0,0);
				GLUquadricObj *quadratic;
				quadratic = gluNewQuadric();
				gluCylinder(quadratic,radiCylinder,radiCylinder,heightCylinder,slices,stacks);
			}glDisable(GL_CLIP_PLANE1);
		}glDisable(GL_CLIP_PLANE0);
	}glPopMatrix();
	
    //sphere------------------------------------
	glPushMatrix();{
		glTranslatef(sizeSphere, sizeSphere, sizeSphere);
		//glColor3f(0.6, 0.1, 0.2);
		double coef8[4];
		coef8[0] = 1;	//-1.x
		coef8[1] = 0;	//0.y
		coef8[2] = 0;	//0.z
		coef8[3] = 0;	//10
		glClipPlane(GL_CLIP_PLANE0,coef8);
		glEnable(GL_CLIP_PLANE0);{
			double coef9[4];
			coef9[0] = 0;	//-1.x
			coef9[1] = 1;	//0.y
			coef9[2] = 0;	//0.z
			coef9[3] = 0;	//10
			glClipPlane(GL_CLIP_PLANE1,coef9);
			glEnable(GL_CLIP_PLANE1);{
				//glTranslatef(0, 0, 0);
				//glRotatef(90,0,1,0);
				drawsphere(radius,slices,stacks);
		        //glRotatef(180,1,0,0);
				//drawsphere(20,20,20);
			}glDisable(GL_CLIP_PLANE1);
		}glDisable(GL_CLIP_PLANE0);
	}glPopMatrix();
	
	glPushMatrix();{
		glTranslatef(sizeSphere, -sizeSphere, sizeSphere);
		//glColor3f(0.6, 0.1, 0.2);
		glColor3f(1.0, 1.0, 1.0);
		double coef8[4];
		coef8[0] = 1;	//-1.x
		coef8[1] = 0;	//0.y
		coef8[2] = 0;	//0.z
		coef8[3] = 0;	//10
		glClipPlane(GL_CLIP_PLANE0,coef8);
		glEnable(GL_CLIP_PLANE0);{
			double coef9[4];
			coef9[0] = 0;	//-1.x
			coef9[1] = -1;	//0.y
			coef9[2] = 0;	//0.z
			coef9[3] = 0;	//10
			glClipPlane(GL_CLIP_PLANE1,coef9);
			glEnable(GL_CLIP_PLANE1);{
				//glTranslatef(0, 0, 0);
				//glRotatef(90,0,1,0);
				drawsphere(radius,slices,stacks);
		        //glRotatef(180,1,0,0);
				//drawsphere(20,20,20);
			}glDisable(GL_CLIP_PLANE1);
		}glDisable(GL_CLIP_PLANE0);
	}glPopMatrix();
	
	glPushMatrix();{
		glTranslatef(-sizeSphere, sizeSphere, sizeSphere);
		//glColor3f(0.6, 0.1, 0.2);
		glColor3f(1.0, 1.0, 1.0);
		double coef8[4];
		coef8[0] = -1;	//-1.x
		coef8[1] = 0;	//0.y
		coef8[2] = 0;	//0.z
		coef8[3] = 0;	//10
		glClipPlane(GL_CLIP_PLANE0,coef8);
		glEnable(GL_CLIP_PLANE0);{
			double coef9[4];
			coef9[0] = 0;	//-1.x
			coef9[1] = 1;	//0.y
			coef9[2] = 0;	//0.z
			coef9[3] = 0;	//10
			glClipPlane(GL_CLIP_PLANE1,coef9);
			glEnable(GL_CLIP_PLANE1);{
				//glTranslatef(0, 0, 0);
				//glRotatef(90,0,1,0);
				drawsphere(radius,slices,stacks);
		        //glRotatef(180,1,0,0);
				//drawsphere(20,20,20);
			}glDisable(GL_CLIP_PLANE1);
		}glDisable(GL_CLIP_PLANE0);
	}glPopMatrix();
	glPushMatrix();{
		glTranslatef(-sizeSphere, -sizeSphere, sizeSphere);
		//glColor3f(0.6, 0.1, 0.2);
		glColor3f(1.0, 1.0, 1.0);
		double coef8[4];
		coef8[0] = -1;	//-1.x
		coef8[1] = 0;	//0.y
		coef8[2] = 0;	//0.z
		coef8[3] = 0;	//10
		glClipPlane(GL_CLIP_PLANE0,coef8);
		glEnable(GL_CLIP_PLANE0);{
			double coef9[4];
			coef9[0] = 0;	//-1.x
			coef9[1] = -1;	//0.y
			coef9[2] = 0;	//0.z
			coef9[3] = 0;	//10
			glClipPlane(GL_CLIP_PLANE1,coef9);
			glEnable(GL_CLIP_PLANE1);{
				//glTranslatef(0, 0, 0);
				//glRotatef(90,0,1,0);
				drawsphere(radius,slices,stacks);
		        //glRotatef(180,1,0,0);
				//drawsphere(20,20,20);
			}glDisable(GL_CLIP_PLANE1);
		}glDisable(GL_CLIP_PLANE0);
	}glPopMatrix();
	//---------------------------------------------------------------------
	glPushMatrix();{
		glTranslatef(sizeSphere, sizeSphere, -sizeSphere);
		//glColor3f(0.6, 0.1, 0.2);
		glColor3f(1.0, 1.0, 1.0);
		double coef8[4];
		coef8[0] = 1;	//-1.x
		coef8[1] = 0;	//0.y
		coef8[2] = 0;	//0.z
		coef8[3] = 0;	//10
		glClipPlane(GL_CLIP_PLANE0,coef8);
		glEnable(GL_CLIP_PLANE0);{
			double coef9[4];
			coef9[0] = 0;	//-1.x
			coef9[1] = 1;	//0.y
			coef9[2] = 0;	//0.z
			coef9[3] = 0;	//10
			glClipPlane(GL_CLIP_PLANE1,coef9);
			glEnable(GL_CLIP_PLANE1);{
				//glTranslatef(0, 0, 0);
				//glRotatef(90,0,1,0);
				glRotatef(180,1,0,0);
				drawsphere(radius,slices,stacks);
				//drawsphere(20,20,20);
			}glDisable(GL_CLIP_PLANE1);
		}glDisable(GL_CLIP_PLANE0);
	}glPopMatrix();
	glPushMatrix();{
		glTranslatef(-sizeSphere, sizeSphere, -sizeSphere);
		//glColor3f(0.6, 0.1, 0.2);
		glColor3f(1.0, 1.0, 1.0);
		double coef8[4];
		coef8[0] = -1;	//-1.x
		coef8[1] = 0;	//0.y
		coef8[2] = 0;	//0.z
		coef8[3] = 0;	//10
		glClipPlane(GL_CLIP_PLANE0,coef8);
		glEnable(GL_CLIP_PLANE0);{
			double coef9[4];
			coef9[0] = 0;	//-1.x
			coef9[1] = 1;	//0.y
			coef9[2] = 0;	//0.z
			coef9[3] = 0;	//10
			glClipPlane(GL_CLIP_PLANE1,coef9);
			glEnable(GL_CLIP_PLANE1);{
				//glTranslatef(0, 0, 0);
				//glRotatef(90,0,1,0);
				glRotatef(180,1,0,0);
				drawsphere(radius,slices,stacks);
				//drawsphere(20,20,20);
			}glDisable(GL_CLIP_PLANE1);
		}glDisable(GL_CLIP_PLANE0);
	}glPopMatrix();
	glPushMatrix();{
		glTranslatef(sizeSphere, -sizeSphere, -sizeSphere);
		//glColor3f(0.6, 0.1, 0.2);
		glColor3f(1.0, 1.0, 1.0);
		double coef8[4];
		coef8[0] = 1;	//-1.x
		coef8[1] = 0;	//0.y
		coef8[2] = 0;	//0.z
		coef8[3] = 0;	//10
		glClipPlane(GL_CLIP_PLANE0,coef8);
		glEnable(GL_CLIP_PLANE0);{
			double coef9[4];
			coef9[0] = 0;	//-1.x
			coef9[1] = -1;	//0.y
			coef9[2] = 0;	//0.z
			coef9[3] = 0;	//10
			glClipPlane(GL_CLIP_PLANE1,coef9);
			glEnable(GL_CLIP_PLANE1);{
				//glTranslatef(0, 0, 0);
				//glRotatef(90,0,1,0);
				glRotatef(180,1,0,0);
				drawsphere(radius,slices,stacks);
				//drawsphere(20,20,20);
			}glDisable(GL_CLIP_PLANE1);
		}glDisable(GL_CLIP_PLANE0);
	}glPopMatrix();
	glPushMatrix();{
		glTranslatef(-sizeSphere, -sizeSphere, -sizeSphere);
		//glColor3f(0.6, 0.1, 0.2);
		glColor3f(1.0, 1.0, 1.0);
		double coef8[4];
		coef8[0] = -1;	//-1.x
		coef8[1] = 0;	//0.y
		coef8[2] = 0;	//0.z
		coef8[3] = 0;	//10
		glClipPlane(GL_CLIP_PLANE0,coef8);
		glEnable(GL_CLIP_PLANE0);{
			double coef9[4];
			coef9[0] = 0;	//-1.x
			coef9[1] = -1;	//0.y
			coef9[2] = 0;	//0.z
			coef9[3] = 0;	//10
			glClipPlane(GL_CLIP_PLANE1,coef9);
			glEnable(GL_CLIP_PLANE1);{
				//glTranslatef(0, 0, 0);
				//glRotatef(90,0,1,0);
				glRotatef(180,1,0,0);
				drawsphere(radius,slices,stacks);
				//drawsphere(20,20,20);
			}glDisable(GL_CLIP_PLANE1);
		}glDisable(GL_CLIP_PLANE0);
	}glPopMatrix();
	//ADD this line in the end --- if you use double buffer (i.e. GL_DOUBLE)
	glutSwapBuffers();
}

void animate(){
	angle+=0.05;
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
	//clear the screen
	glClearColor(0,0,0,0);

	/************************
	/ set-up projection here
	************************/
	//load the PROJECTION matrix
	glMatrixMode(GL_PROJECTION);
	
	//initialize the matrix
	glLoadIdentity();

	//give PERSPECTIVE parameters
	gluPerspective(80,	1,	1,	10000.0);
	//field of view in the Y (vertically)
	//aspect ratio that determines the field of view in the X direction (horizontally)
	//near distance
	//far distance
}

int main(int argc, char **argv){
	glutInit(&argc,argv);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);	//Depth, Double buffer, RGB color

	glutCreateWindow("My OpenGL Program");

	init();

	glEnable(GL_DEPTH_TEST);	//enable Depth Testing

	glutDisplayFunc(display);	//display callback function
	glutIdleFunc(animate);		//what you want to do in the idle time (when no drawing is occuring)

	glutKeyboardFunc(keyboardListener);
	glutSpecialFunc(specialKeyListener);
	glutMouseFunc(mouseListener);

	glutMainLoop();		//The main loop of OpenGL

	return 0;
}
