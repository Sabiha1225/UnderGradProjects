#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include "bitmap_image.hpp"
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<GL/glut.h>
#include "CameraHeader.h"
#define pi (double)2*acos((double)0)
#define RayHit 1
#define RayMiss 0
#define RayInside -1
#define THRESHOLD		0.01
int DEPTH=0;
Camera cam12;

int viewPlaneX = 0, viewPlaneY = 0;
bool rayTraceDoing = false;
double strengthOfLight = 1.0;
double amountOfLight = 1.0;
int sizeOfBlock = 1;
float arrayImage[512][512][3];

int Sphere = 1;
int Plane = 2;

int numberOfObject;

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

int fileObject=0;
int lightObject=0;
double colorArray[10][3];
double coefficientArray[10][4];
double shineArray[10];
int typeArray[10];
double centerArray[10][3];
double radiusArray[10];
double lightCenter[10][3];
struct point
{
	double x,y,z;
};



class Ray
{
private:
	Vector rayOrigin;	
	Vector rayDirection;
public:
	Ray(Vector ori, Vector dir)
	{
		rayDirection = dir;
		rayOrigin = ori;
	}
	Ray()
	{
		rayOrigin = FVector(0,0,0);
		rayDirection = FVector(0,0,0);
	}
	void setRayOrigin(Vector ori)
	{
		rayOrigin = ori;
	}
	void setRayDirection(Vector dir)
	{
		rayDirection = dir;
	}
	Vector getRayOrigin(void)
	{
		return rayOrigin;
	}
	Vector getRayDirection(void)
	{
		return rayDirection;
	}

};
class PropertyOfMaterial {
private:
	double shininess;
	double ambient, diffuse, specular,reflection, refraction, rIndex; 
	Vector color;
public:
	PropertyOfMaterial(double shi, double am, double di, double spec, double reflec, double refrac, Vector col)
	{
	    rIndex = 0;
		color = col;
		specular = spec;
		reflection = reflec;
		ambient = am;
		diffuse = di;
		shininess = shi;
		refraction = refrac;
	}
	PropertyOfMaterial()
	{	
		shininess = 0;
		ambient = 0;
		diffuse = 0;
		specular = 0;
		reflection = 0;
		refraction = 0;
		rIndex = 0;
		color = FVector(0,0,0);
	}
	void setShinines(double shi)
	{
		shininess = shi;
	}
	void setAmbient(double am)
	{
		ambient = am;
	}
	void setDiffuse(double di)
	{
		diffuse = di;
	}
	void setSpecular(double spec)
	{
		specular = spec;
	}
	void setReflection(double reflec)
	{
		reflection = reflec;
	}
	void setRefraction(double refrac)
	{
		refraction = refrac;
	}
	void setColor(Vector col)
	{
		color = col;
	}
	double getDiffuse(void)
	{
		return diffuse;
	}
	double getSpecular(void)
	{
		return specular;
	}
	double getShinines(void)
	{
		return shininess;
	}
	double getAmbient(void)
	{
		return ambient;
	}
	double getReflection(void)
	{
		return reflection;
	}
	void setRIndex(double ri)
	{
		rIndex = ri;
	}
	double getRIndex(void)
	{
		return rIndex;
	}
	double getRefraction(void)
	{
		return refraction;
	}	
	Vector getColor(void)
	{
		return color;
	}
};
class OBJECT
{

private:
	PropertyOfMaterial pMaterial;
	int type;
	bool light;
	char* name;
public:
	OBJECT()
	{		
		light = false;
		name = 0;
	}
	void setPropertyOfMaterial(PropertyOfMaterial pMat)
	{
		pMaterial = pMat;
	}
	virtual int getType(void)
	{
		return type;
	}
	void setType(int t)
	{
		type = t;
	}
    PropertyOfMaterial* getPropertyOfMaterial(void)
	{
		return &pMaterial;
	}
	void setLight(bool l)
	{
		light = l;
	}
	virtual bool getLight(void)
	{
		return light;
	}
	void setName(char* n)
	{
		int len = strlen( n ) + 1;
		delete name;        
        name = new char[len];        
		strcpy(name, n);
	}
	virtual int getIntersectionPoint(double& dist, Ray& ray)=0;
	char* getName(void)
	{
		return name;
	}
	virtual Vector getNormalVector( Vector& position )=0;
};
class SPHERE: public OBJECT 
{
private:
	Vector center;
	double radius;
public:
	SPHERE(double r, Vector cent)
	{		
		radius = r;
		center = cent;
	}
	void setCenter(Vector cent)
	{
		center = cent;
	}
	double getRadius(void)
	{
		return radius;
	}
	int getIntersectionPoint(double& dist, Ray& ray)
    {		
		Vector temp = subVector(ray.getRayOrigin(),center);   
		double b = dotProduct(temp, ray.getRayDirection());	
		b = -b;
		double c = dotProduct(temp, temp) - (radius*radius);
		double determinant = (b*b) - c;
		int returnValue = RayMiss;

        if (determinant > 0)
        {
            determinant = sqrt(determinant);            
			double tera1 = b - determinant;
			double tera2 = b + determinant;
			if (tera2 > 0)
            {
                if (tera1 < 0)
                {
                    if (tera2 < dist)
                    {
                        dist = tera2;
						returnValue = RayInside;
                    }
                }
                else
                {
                    if (tera1 < dist)
                    {
                        dist = tera1;
						returnValue = RayHit;
                    }
                }
            }
        }
        return returnValue;
    }
	Vector getCenter(void)
	{
		return center;
	}
	void setRadius(double r)
	{
		radius = r;
	}
	Vector getNormalVector( Vector& position )
    {
		double r = 1.0/ radius;

		return constantProduct(r, subVector(position , center));
    }
	int getType(void)
	{
		return Sphere;
	}

};
class PLANE:public OBJECT
{
private:
	Vector a;
	Vector normal;
public:
	double lengthOfSide;
	PLANE()
	{
		normal = FVector(0,0,0);
		a = FVector(0,0,0);
	}
	PLANE(Vector a1, Vector n)
	{
		a = a1;
		normal = n;
	}
	Vector getNormal(void)
	{
		return normal;
	}
	Vector getA(void)
	{
		return a;
	}
	void setNormal(Vector n)
	{
		normal = n;
	}
	void setA(Vector a1)
	{
		a = a1;
	}
	int getIntersectionPoint(double& dist,  Ray& ray)
    {
		lengthOfSide = 30;
		Vector hello;
		double denominator = dotProduct(ray.getRayDirection(), normal);
        if (denominator != 0)
        {
			Vector test = subVector(a, ray.getRayOrigin());
			double test1 = dotProduct(test, normal)/denominator; 
            if (test1 > 0)
            {
				hello = addVector( ray.getRayOrigin(),  constantProduct(test1, ray.getRayDirection()));
				if(hello.x >= a.x-1 && hello.x<=(a.x+lengthOfSide) && hello.y>=a.y-1 && hello.y<=(a.y+lengthOfSide) && hello.z>=a.z-1 && hello.z<=a.z+lengthOfSide)
                {
                    if (test1 < dist)
                    {
                        dist = test1;
						
						return RayHit;
                    }
                }           

            }
        }
		return RayMiss;
    }
	int getType(void)
	{
		return Plane;
	}
	Vector getNormalVector( Vector& position )
	{
		return normal;
	}
};

OBJECT** object;

void generateEnvironment(void)
{
	int index=0;
	
	object = new OBJECT*[500];

	for(int i=0; i<fileObject-1; ++i)
	{
		object[index] = new SPHERE(radiusArray[i], FVector(centerArray[i][0], centerArray[i][1], centerArray[i][2]));
	
		object[index]->setName("Sphere");

		object[index]->setPropertyOfMaterial(PropertyOfMaterial(shineArray[i], coefficientArray[i][0], coefficientArray[i][1], coefficientArray[i][2], coefficientArray[i][3], 0.0 ,FVector(colorArray[i][0], colorArray[i][1], colorArray[i][2])));

		index++;
	}


	for(int i=0; i<lightObject; ++i)
	{
		object[index] = new SPHERE(5, FVector(lightCenter[i][0], lightCenter[i][1], lightCenter[i][2]));

		object[index]->setLight(true);

		object[index]->setPropertyOfMaterial(PropertyOfMaterial(0.0, 0.0, 0.0, 0.0, 0.0, 0.0 ,FVector(1.0, 1.0, 1.0)));

		index++;
	}

	double lengthOfSide = radiusArray[fileObject-1];

	object[index] = new PLANE(FVector(0.0, 0.0, 0.0), FVector(0.0, 1.0, 0.0));

	object[index]->setName("Plane");

	object[index]->setPropertyOfMaterial(PropertyOfMaterial(shineArray[fileObject-1], coefficientArray[fileObject-1][0], coefficientArray[fileObject-1][1], coefficientArray[fileObject-1][2], coefficientArray[fileObject-1][3], 0.0 ,FVector(colorArray[fileObject-1][0], colorArray[fileObject-1][1], colorArray[fileObject-1][2])));
    
	index++;

	object[index] = new PLANE(FVector(0.0, lengthOfSide, 0.0), FVector(0.0, -1.0, 0.0));


	object[index]->setName("Plane");


	object[index]->setPropertyOfMaterial(PropertyOfMaterial(shineArray[fileObject-1], coefficientArray[fileObject-1][0], coefficientArray[fileObject-1][1], coefficientArray[fileObject-1][2], coefficientArray[fileObject-1][3], 0.0 ,FVector(colorArray[fileObject-1][0], colorArray[fileObject-1][1], colorArray[fileObject-1][2])));

	index++;


	object[index] = new PLANE(FVector(0.0, 0.0, 0.0), FVector(0.0, 0.0, -1.0));

	object[index]->setName("Plane");


	object[index]->setPropertyOfMaterial(PropertyOfMaterial(shineArray[fileObject-1], coefficientArray[fileObject-1][0], coefficientArray[fileObject-1][1], coefficientArray[fileObject-1][2], coefficientArray[fileObject-1][3], 0.0 ,FVector(colorArray[fileObject-1][0], colorArray[fileObject-1][1], colorArray[fileObject-1][2])));

	index++;

	object[index] = new PLANE(FVector(0.0, 0.0, lengthOfSide), FVector(0.0, 0.0, 1.0));

	object[index]->setName("Plane");


	object[index]->setPropertyOfMaterial(PropertyOfMaterial(shineArray[fileObject-1], coefficientArray[fileObject-1][0], coefficientArray[fileObject-1][1], coefficientArray[fileObject-1][2], coefficientArray[fileObject-1][3], 0.0 ,FVector(colorArray[fileObject-1][0], colorArray[fileObject-1][1], colorArray[fileObject-1][2])));

	index++;


	object[index] = new PLANE(FVector(0.0, 0.0, 0.0), FVector(-1.0, 0.0, 0.0));

	object[index]->setName("Plane");


	object[index]->setPropertyOfMaterial(PropertyOfMaterial(shineArray[fileObject-1], coefficientArray[fileObject-1][0], coefficientArray[fileObject-1][1], coefficientArray[fileObject-1][2], coefficientArray[fileObject-1][3], 0.0 ,FVector(colorArray[fileObject-1][0], colorArray[fileObject-1][1], colorArray[fileObject-1][2])));

	index++;


	object[index] = new PLANE(FVector(lengthOfSide, 0.0, 0.0), FVector(1.0, 0.0, 0.0));

	object[index]->setName("Plane");

	object[index]->setPropertyOfMaterial(PropertyOfMaterial(shineArray[fileObject-1], coefficientArray[fileObject-1][0], coefficientArray[fileObject-1][1], coefficientArray[fileObject-1][2], coefficientArray[fileObject-1][3], 0.0 ,FVector(colorArray[fileObject-1][0], colorArray[fileObject-1][1], colorArray[fileObject-1][2])));

	index++;
    
	//int index=0;

	for(int i=0, p = -4 ; i<10; p++, ++i)
	{
	
		for(int j=0, q = -4; j<10; q++, ++j)
		{
			object[index] = new PLANE(FVector(p*20.0, q*20.0, 0.0), FVector(0.0, 0.0, 1.0));

			object[index]->setName("Plane");

			object[index]->setPropertyOfMaterial(PropertyOfMaterial(3.0, 0.4, 0.2, 0.2, 0.5, 0.0 ,FVector(0.0, 0.0, 0.0)));

			if((i%2==0 && j%2==0) || (i%2!=0 && j%2!=0))
				object[index]->getPropertyOfMaterial()->setColor(FVector(0.0, 0.0, 0.0));
			else if((i%2==0 && j%2!=0) || (i%2!=0 && j%2==0))
				object[index]->getPropertyOfMaterial()->setColor(FVector(1.0, 1.0, 1.0));

			index++;
		}
	}
	
	numberOfObject = index;
}


OBJECT* mainRayTracing( Ray& ray, Vector& color, int rayDepth, double ri, double& dist )
{
	if (rayDepth > DEPTH) 
		return 0;
	OBJECT* obj = 0;
    dist = 1000000.0f;
	int rayTracingResult;
	double eta= 1000005.0f;
	Vector hello;
	for ( int i = 0; i < numberOfObject; i++ )
    {
        OBJECT* obj1 = object[i];
        int res;
		res = obj1->getIntersectionPoint(dist, ray);
        if (res)
        {
			obj = obj1;
            rayTracingResult = res; 
        }
    }
    if (!obj)
    {
        color = FVector(0, 0, 0);
        return 0;
    }
	if (obj->getLight())
    { 
    }
    else
    {   
		ray.setRayDirection(normalizeVector(ray.getRayDirection()));   
		hello = addVector( ray.getRayOrigin() , constantProduct(dist, ray.getRayDirection()));
		color = addVector(color, constantProduct(obj->getPropertyOfMaterial()->getAmbient(), obj->getPropertyOfMaterial()->getColor()));
		for ( int j = 0; j < numberOfObject; j++ )
        {
            OBJECT* o = object[j];
			
			if (o->getLight())
            {
                OBJECT* light = o;

                double shade = 1.0f;
				if (light->getType() == 1)
				{
					Vector test = subVector(((SPHERE*)light)->getCenter() , hello);
					double tdist = getVectorLength(test);
					test = constantProduct((1.0f / tdist), test);
					Ray r(addVector( hello , constantProduct(THRESHOLD, test)), test );
					for ( int k = 0; k < numberOfObject; k++ )
					{
						OBJECT* ob = object[k];
						if ((ob != light) && (ob->getIntersectionPoint(tdist, r)))
						{
							shade = 0;
							break;
						}
					}
				}
				Vector test = subVector(((SPHERE*)light)->getCenter() , hello);
				test = normalizeVector(test);
				Vector normal = obj->getNormalVector(hello);
				if (obj->getPropertyOfMaterial()->getDiffuse() > 0)
                {
					double dot = dotProduct( normal, test );
                    if (dot > 0)
                    {
						double diff = dot * obj->getPropertyOfMaterial()->getDiffuse() * shade;						
						color = addVector( color, constantProduct( diff , multVector( obj->getPropertyOfMaterial()->getColor() , light->getPropertyOfMaterial()->getColor())));
                    }
                }

				if (obj->getPropertyOfMaterial()->getSpecular() > 0)
                {
					Vector V = ray.getRayDirection();
					Vector R = subVector (test , constantProduct(2.0 *dotProduct( test, normal ) , normal));
					double dot = dotProduct( V, R );
                    
					if (dot > 0)
                    {
						double shinines = obj->getPropertyOfMaterial()->getShinines();						
						double spec = pow( dot, shinines) * obj->getPropertyOfMaterial()->getSpecular()* shade ;
						color = addVector(color, constantProduct(spec, light->getPropertyOfMaterial()->getColor()));
                    }
                }
            }
        }      
		double refl = obj->getPropertyOfMaterial()->getReflection();
        if (refl > 0.0f)
        {           
			Vector N = obj->getNormalVector(hello);
			Vector R = subVector( ray.getRayDirection() , constantProduct(2.0f *dotProduct( ray.getRayDirection(), N ) , N));
			if (rayDepth < DEPTH)
            {
				Vector color1 = FVector( 0, 0, 0 );
                double dist;
				Ray r(addVector( hello , constantProduct(THRESHOLD, R)) , R );                
				mainRayTracing( r, color1, rayDepth + 1, ri, dist );
				color = addVector(color, constantProduct( refl , multVector( color1 , obj->getPropertyOfMaterial()->getColor())));
            }
        }
    }
    return obj;
}
void drawImage()
{
	bitmap_image picture(cam12.row, cam12.col);
	for(int i=cam12.row-1; i>=0; --i)
	{
		for(int j=cam12.col-1; j>=0; --j)
		{
			picture.set_pixel(i,j, arrayImage[i][j][0], arrayImage[i][j][1], arrayImage[i][j][2]);
		}
	}
	picture.save_image("output.bmp");
}

void trace(void)
{
	cam12.row = viewPlaneX;
	cam12.col = viewPlaneY;
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClearColor(0,0,0,0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	gluOrtho2D(0,cam12.col,0,cam12.row); 
    glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING); 
    Ray ray;
	ray.setRayOrigin(FVector(cam12.eye.x, cam12.eye.y, cam12.eye.z));
	double windowWidth = 2*cam12.width/(double)cam12.col;
	double windowHeight = 2*cam12.height/(double)cam12.row;
    double x, y;
	for(int row = 0; row < cam12.row; row += sizeOfBlock)
    {
		for(int col = 0; col < cam12.col; col += sizeOfBlock)
        {
			Vector color = FVector(0,0,0);   
			x = -cam12.width + col * windowWidth;
			y = -cam12.height + row * windowHeight;
			ray.setRayDirection(FVector(-(cam12.nearDistance*cam12.n.x)+(x*cam12.u.x)+(y*cam12.v.x), -(cam12.nearDistance*cam12.n.y)+(x*cam12.u.y)+(y*cam12.v.y), -(cam12.nearDistance*cam12.n.z)+(x*cam12.u.z)+(y*cam12.v.z) ));
			ray.setRayDirection(normalizeVector(ray.getRayDirection()));          
            int a_Depth=1;
			double a_RIndex=1.0 ,a_Dist=10 ;
			mainRayTracing( ray, color,  a_Depth, a_RIndex,  a_Dist );
            glColor3f(color.x,color.y,color.z);
			glRecti(col,row,col+sizeOfBlock, row + sizeOfBlock);
            float r1=color.x*256;
			float g1=color.y*256;
			float b1=color.z*256;
			if(r1>255) r1=255;
			if(g1>255) g1=255;
			if(b1>255) b1=255;
            arrayImage[row][col][0] = r1;
			arrayImage[row][col][1] = g1;
			arrayImage[row][col][2] = b1;
        }
    }
	drawImage();   
}

void fileInput(void)
{
	FILE *fp;
    
	
	char buff [256], buff1 [256], buff2 [256], buff3 [256];
	
	fp = fopen("depth.txt", "r");

	if(fp==NULL)
	{
		printf("Cannot Open File.\n");
	}
	else
	{
	
		fscanf(fp, "%s", buff);


		DEPTH = atoi(buff);
		
		fscanf(fp, "%s", buff);

		viewPlaneX = viewPlaneY = atoi(buff);
		
		fscanf(fp, "%s", buff);

		fileObject = atoi(buff);



		for(int i=0; i<fileObject; ++i)
		{
			fscanf(fp, "%s", buff);
			typeArray[i] = atoi(buff);


			fscanf(fp, "%s %s %s", buff, buff1, buff2);
			centerArray[i][0] = atof(buff);

			centerArray[i][1] = atof(buff1);
			centerArray[i][2] = atof(buff2);

			fscanf(fp, "%s", buff);
			radiusArray[i] = atof(buff);

			fscanf(fp, "%s %s %s", buff, buff1, buff2);

			colorArray[i][0] = atof(buff);

			colorArray[i][1] = atof(buff1);
			colorArray[i][2] = atof(buff2);

			fscanf(fp, "%s %s %s %s", buff, buff1, buff2, buff3);
			coefficientArray[i][0] = atof(buff);


			coefficientArray[i][1] = atof(buff1);
			coefficientArray[i][2] = atof(buff2);

			coefficientArray[i][3] = atof(buff3);

			fscanf(fp, "%s", buff);

			shineArray[i] = atof(buff);
		}
		fscanf(fp, "%s", buff);

		lightObject = atoi(buff);

		for(int i=0; i<lightObject; ++i)
		{
			fscanf(fp, "%s %s %s", buff, buff1, buff2);

			lightCenter[i][0] = atof(buff);
			lightCenter[i][1] = atof(buff1);

			lightCenter[i][2] = atof(buff2);
		}
	}
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
		glColor3f(0.6, 0.6, 0.6);	
		glBegin(GL_LINES);{
			for(i=-8;i<=8;i++){

				if(i==0)
					continue;	

				
				glVertex3f(i*10, -90, 0);
				glVertex3f(i*10,  90, 0);

				
				glVertex3f(-90, i*10, 0);
				glVertex3f( 90, i*10, 0);
			}
		}glEnd();
	}
}


void drawSquare(float a)
{
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_QUADS);{
		glVertex3f( a, a, a);
		glVertex3f( 0, a, a);
		glVertex3f( 0, a, 0);
		glVertex3f( a, a, 0);
	}glEnd();
	
	
	glBegin(GL_QUADS);{
		glVertex3f( a, 0, a);
		glVertex3f( 0, 0, a);
		glVertex3f( 0, 0, 0);
		glVertex3f( a, 0, 0);

	}glEnd();
	
	
	glBegin(GL_QUADS);{
		glVertex3f( a, 0, a);
		glVertex3f( 0, 0, a);
		glVertex3f( 0, a, a);
		glVertex3f( a, a, a);
	}glEnd();

	
	glBegin(GL_QUADS);{
		glVertex3f( 0, 0, a);
		glVertex3f( 0, 0, 0);
		glVertex3f( 0, a, 0);
		glVertex3f( 0, a, a);
	}glEnd();
	
	
	glBegin(GL_QUADS);{
		glVertex3f( 0, 0, 0);
		glVertex3f( a, 0, 0);
		glVertex3f( a, a, 0);
		glVertex3f( 0, a, 0);
	}glEnd();
	

	glBegin(GL_QUADS);{
		glVertex3f( a, 0, 0);
		glVertex3f( a, 0, a);
		glVertex3f( a, a, a);
		glVertex3f( a, a, 0);
	}glEnd();
	
}

void keyboardListener(unsigned char key, int x,int y){
	switch(key){

		case '1':
			cam12.yaw(.8);
			
			break;
	    case '2':
			cam12.yaw(-.8);			
			break;
		case '3':
			cam12.pitch(.8);
			
			break;
		case '4':
			cam12.pitch(-.8);
			
			break;
		case '5':	
			cam12.roll(.8);
			
			break;
		case '6':	
			
			cam12.roll(-.8);
			break;

		default:
			break;
	}
}


void specialKeyListener(int key, int x,int y){
	switch(key){
		case GLUT_KEY_DOWN:		//move backward
			
			cam12.slide(0,0,.8);
			
			break;
		case GLUT_KEY_UP:		//move forward
			
			
			cam12.slide(0,0,-.8);
			
			break;

		case GLUT_KEY_RIGHT:   //move right
			
			
			cam12.slide(.8,0,0);
			
			
			break;
		case GLUT_KEY_LEFT:    //move left
			
			
			cam12.slide(-.8,0,0);
			
			
			
			break;

		case GLUT_KEY_PAGE_UP:  //move upward
			
			
			
			cam12.slide(0,.8,0);
			
			break;
		case GLUT_KEY_PAGE_DOWN:  //move downward
			
			
			cam12.slide(0,-.8,0);
			
			break;

		case GLUT_KEY_INSERT:
			
			
			rayTraceDoing=true;
			
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
			}
			break;

		case GLUT_RIGHT_BUTTON:
			break;

		case GLUT_MIDDLE_BUTTON:
			break;

		default:
			break;
	}
}
void drawFloor()
{
	glColor3f(1.0, 1.0, 1.0 );
	glBegin(GL_QUADS);
    {
        glVertex3f( 15, 0, 15);
        glVertex3f( 0, 0, 15);
        glVertex3f( 0,  0, 0);
        glVertex3f( 15,  0, 0);
    }
    glEnd();

	glColor3f(0.0, 0.0, 0.0 );
	glBegin(GL_QUADS);
    {
        glVertex3f( 30, 0, 15);
        glVertex3f( 15, 0, 15);
        glVertex3f( 15,  0, 0);
        glVertex3f( 30,  0, 0);
    }
    glEnd();
	glColor3f(1.0, 1.0, 1.0 );
	glBegin(GL_QUADS);
    {
        glVertex3f( 45,  0, 15);
        glVertex3f( 30,  0, 15);
        glVertex3f( 30,  0, 0);
        glVertex3f( 45,  0, 0);
    }
    glEnd();
	glColor3f(0.0, 0.0, 0.0 );
	glBegin(GL_QUADS);
    {
        glVertex3f( 60, 0, 15);
        glVertex3f( 45, 0, 15);
        glVertex3f( 45,  0, 0);
        glVertex3f( 60,  0, 0);
    }
    glEnd();

	glColor3f(0.0, 0.0, 0.0 );
	glBegin(GL_QUADS);
    {
        glVertex3f( 0, 0,  15);
        glVertex3f( -15, 0, 15);
        glVertex3f( -15,  0, 0);
        glVertex3f( 0,  0,  0);
    }
    glEnd();
	glColor3f(1.0, 1.0, 1.0 );
	glBegin(GL_QUADS);
    {
        glVertex3f( -15, 0, 15);
        glVertex3f( -30, 0, 15);
        glVertex3f( -30,  0, 0);
        glVertex3f( -15,  0, 0);
    }
    glEnd();
	glColor3f(0.0, 0.0, 0.0 );	
	glBegin(GL_QUADS);
    {
        glVertex3f( -30, 0, 15);
        glVertex3f( -45, 0, 15);
        glVertex3f( -45,  0, 0);
        glVertex3f( -30,  0, 0);
    }
    glEnd();
	glColor3f(1.0, 1.0, 1.0 );
	glBegin(GL_QUADS);
    {
        glVertex3f( -45, 0, 15);
        glVertex3f( -60, 0, 15);
        glVertex3f( -60,  0, 0);
        glVertex3f( -45,  0, 0);
    }
    glEnd();
	glColor3f(0.0, 0.0, 0.0 );
	glBegin(GL_QUADS);
    {
        glVertex3f( 15, 0, 30);
        glVertex3f( 0, 0, 30);
        glVertex3f( 0, 0, 15);
        glVertex3f( 15, 0, 15);
    }
    glEnd();

	glColor3f(1.0, 1.0, 1.0 );
	glBegin(GL_QUADS);
    {
        glVertex3f( 30, 0, 30);
        glVertex3f( 15, 0, 30);
        glVertex3f( 15, 0, 15);
        glVertex3f( 30, 0, 15);
    }
    glEnd();
	glColor3f(0.0, 0.0, 0.0 );
	glBegin(GL_QUADS);
    {
        glVertex3f( 45, 0, 30);
        glVertex3f( 30, 0, 30);
        glVertex3f( 30, 0, 15);
        glVertex3f( 45, 0, 15);
    }
    glEnd();
	glColor3f(1.0, 1.0, 1.0 );
	glBegin(GL_QUADS);
    {
        glVertex3f( 60, 0, 30);
        glVertex3f( 45, 0, 30);
        glVertex3f( 45, 0, 15);
        glVertex3f( 60, 0, 15);
    }
    glEnd();

	glColor3f(1.0, 1.0, 1.0 );
	glBegin(GL_QUADS);
    {
        glVertex3f( 0,  0, 30);
        glVertex3f( -15, 0, 30);
        glVertex3f( -15, 0, 15);
        glVertex3f( 0,  0, 15);
    }
    glEnd();
	glColor3f(0.0, 0.0, 0.0 );
	glBegin(GL_QUADS);
    {
        glVertex3f( -15, 0, 30);
        glVertex3f( -30, 0, 30);
        glVertex3f( -30, 0, 15);
        glVertex3f( -15, 0, 15);
    }
    glEnd();
	glColor3f(1.0, 1.0, 1.0 );	
	glBegin(GL_QUADS);
    {
        glVertex3f( -30, 0, 30);
        glVertex3f( -45, 0, 30);
        glVertex3f( -45, 0, 15);
        glVertex3f( -30, 0, 15);
    }
    glEnd();
	glColor3f(0.0, 0.0, 0.0 );
	glBegin(GL_QUADS);
    {
        glVertex3f( -45, 0, 30);
        glVertex3f( -60, 0, 30);
        glVertex3f( -60, 0, 15);
        glVertex3f( -45, 0, 15);
    }
    glEnd();
	glColor3f(1.0, 1.0, 1.0 );
	glBegin(GL_QUADS);
    {
        glVertex3f( 15, 0, 45);
        glVertex3f( 0, 0, 45);
        glVertex3f( 0, 0, 30);
        glVertex3f( 15, 0, 30);
    }
    glEnd();

	glColor3f(0.0, 0.0, 0.0 );
	glBegin(GL_QUADS);
    {
        glVertex3f( 30, 0, 45);
        glVertex3f( 15, 0, 45);
        glVertex3f( 15, 0, 30);
        glVertex3f( 30, 0, 30);
    }
    glEnd();
	glColor3f(1.0, 1.0, 1.0 );
	glBegin(GL_QUADS);
    {
        glVertex3f( 45, 0, 45);
        glVertex3f( 30, 0, 45);
        glVertex3f( 30, 0, 30);
        glVertex3f( 45, 0, 30);
    }
    glEnd();
	glColor3f(0.0, 0.0, 0.0 );
	glBegin(GL_QUADS);
    {
        glVertex3f( 60, 0, 45);
        glVertex3f( 45, 0, 45);
        glVertex3f( 45, 0, 30);
        glVertex3f( 60, 0, 30);
    }
    glEnd();

	glColor3f(0.0, 0.0, 0.0 );
	glBegin(GL_QUADS);
    {
        glVertex3f( 0,  0, 45);
        glVertex3f( -15, 0, 45);
        glVertex3f( -15, 0, 30);
        glVertex3f( 0,  0, 30);
    }
    glEnd();
	glColor3f(1.0, 1.0, 1.0 );
	glBegin(GL_QUADS);
    {
        glVertex3f( -15, 0, 45);
        glVertex3f( -30, 0, 45);
        glVertex3f( -30, 0, 30);
        glVertex3f( -15, 0, 30);
    }
    glEnd();
	glColor3f(0.0, 0.0, 0.0 );	
	glBegin(GL_QUADS);
    {
        glVertex3f( -30, 0, 45);
        glVertex3f( -45, 0, 45);
        glVertex3f( -45, 0, 30);
        glVertex3f( -30, 0, 30);
    }
    glEnd();
	glColor3f(1.0, 1.0, 1.0 );
	glBegin(GL_QUADS);
    {
        glVertex3f( -45, 0, 45);
        glVertex3f( -60, 0, 45);
        glVertex3f( -60, 0, 30);
        glVertex3f( -45, 0, 30);
    }
    glEnd();
	glColor3f(0.0, 0.0, 0.0 );
	glBegin(GL_QUADS);
    {
        glVertex3f( 15, 0, 60);
        glVertex3f( 0, 0, 60);
        glVertex3f( 0, 0, 45);
        glVertex3f( 15, 0, 45);
    }
    glEnd();

	glColor3f(1.0, 1.0, 1.0 );
	glBegin(GL_QUADS);
    {
        glVertex3f( 30, 0, 60);
        glVertex3f( 15, 0, 60);
        glVertex3f( 15, 0, 45);
        glVertex3f( 30, 0, 45);
    }
    glEnd();
	glColor3f(0.0, 0.0, 0.0 );
	glBegin(GL_QUADS);
    {
        glVertex3f( 45, 0, 60);
        glVertex3f( 30, 0, 60);
        glVertex3f( 30, 0, 45);
        glVertex3f( 45, 0, 45);
    }
    glEnd();
	glColor3f(1.0, 1.0, 1.0 );
	glBegin(GL_QUADS);
    {
        glVertex3f( 60, 0, 60);
        glVertex3f( 45, 0, 60);
        glVertex3f( 45, 0, 45);
        glVertex3f( 60, 0, 45);
    }
    glEnd();

	glColor3f(1.0, 1.0, 1.0 );
	glBegin(GL_QUADS);
    {
        glVertex3f( 0,  0, 60);
        glVertex3f( -15, 0, 60);
        glVertex3f( -15, 0, 45);
        glVertex3f( 0,  0, 45);
    }
    glEnd();
	glColor3f(0.0, 0.0, 0.0 );
	glBegin(GL_QUADS);
    {
        glVertex3f( -15, 0, 60);
        glVertex3f( -30, 0, 60);
        glVertex3f( -30, 0, 45);
        glVertex3f( -15, 0, 45);
    }
    glEnd();
	glColor3f(1.0, 1.0, 1.0 );	
	glBegin(GL_QUADS);
    {
        glVertex3f( -30, 0, 60);
        glVertex3f( -45, 0, 60);
        glVertex3f( -45, 0, 45);
        glVertex3f( -30, 0, 45);
    }
    glEnd();
	glColor3f(0.0, 0.0, 0.0 );
	glBegin(GL_QUADS);
    {
        glVertex3f( -45, 0, 60);
        glVertex3f( -60, 0, 60);
        glVertex3f( -60, 0, 45);
        glVertex3f( -45, 0, 45);
    }
    glEnd();
	glColor3f(0.0, 0.0, 0.0 );
	glBegin(GL_QUADS);
    {
        glVertex3f( 15, 0, 0);
        glVertex3f( 0, 0, 0);
        glVertex3f( 0, 0, -15);
        glVertex3f( 15, 0, -15);
    }
    glEnd();

	glColor3f(1.0, 1.0, 1.0 );
	glBegin(GL_QUADS);
    {
        glVertex3f( 30, 0, 0);
        glVertex3f( 15, 0, 0);
        glVertex3f( 15, 0, -15);
        glVertex3f( 30, 0, -15);
    }
    glEnd();
	glColor3f(0.0, 0.0, 0.0 );
	glBegin(GL_QUADS);
    {
        glVertex3f( 45, 0, 0);
        glVertex3f( 30, 0, 0);
        glVertex3f( 30, 0, -15);
        glVertex3f( 45, 0, -15);
    }
    glEnd();
	glColor3f(1.0, 1.0, 1.0 );
	glBegin(GL_QUADS);
    {
        glVertex3f( 60, 0, 0);
        glVertex3f( 45, 0, 0);
        glVertex3f( 45, 0, -15);
        glVertex3f( 60, 0, -15);
    }
    glEnd();

	glColor3f(1.0, 1.0, 1.0 );
	glBegin(GL_QUADS);
    {
        glVertex3f(  0,  0, 0);
        glVertex3f( -15, 0, 0);
        glVertex3f( -15, 0, -15);
        glVertex3f( 0,  0, -15);
    }
    glEnd();
	glColor3f(0.0, 0.0, 0.0 );
	glBegin(GL_QUADS);
    {
        glVertex3f( -15, 0, 0);
        glVertex3f( -30, 0, 0);
        glVertex3f( -30, 0, -15);
        glVertex3f( -15, 0, -15);
    }
    glEnd();
	glColor3f(1.0, 1.0, 1.0 );	
	glBegin(GL_QUADS);
    {
        glVertex3f( -30, 0, 0);
        glVertex3f( -45, 0, 0);
        glVertex3f( -45, 0, -15);
        glVertex3f( -30, 0, -15);
    }
    glEnd();
	glColor3f(0.0, 0.0, 0.0 );
	glBegin(GL_QUADS);
    {
        glVertex3f( -45, 0, 0);
        glVertex3f( -60, 0, 0);
        glVertex3f( -60, 0, -15);
        glVertex3f( -45, 0, -15);
    }
    glEnd();
	glColor3f(1.0, 1.0, 1.0 );
	glBegin(GL_QUADS);
    {
        glVertex3f( 15, 0, -15);
        glVertex3f( 0, 0, -15);
        glVertex3f( 0, 0, -30);
        glVertex3f( 15, 0, -30);
    }
    glEnd();

	glColor3f(0.0, 0.0, 0.0 );
	glBegin(GL_QUADS);
    {
        glVertex3f( 30, 0, -15);
        glVertex3f( 15, 0, -15);
        glVertex3f( 15, 0, -30);
        glVertex3f( 30, 0, -30);
    }
    glEnd();
	glColor3f(1.0, 1.0, 1.0 );
	glBegin(GL_QUADS);
    {
        glVertex3f( 45, 0, -15);
        glVertex3f( 30, 0, -15);
        glVertex3f( 30, 0, -30);
        glVertex3f( 45, 0, -30);
    }
    glEnd();
	glColor3f(0.0, 0.0, 0.0 );
	glBegin(GL_QUADS);
    {
        glVertex3f( 60, 0, -15);
        glVertex3f( 45, 0, -15);
        glVertex3f( 45, 0, -30);
        glVertex3f( 60, 0, -30);
    }
    glEnd();

	glColor3f(0.0, 0.0, 0.0 );
	glBegin(GL_QUADS);
    {
        glVertex3f( 0,  0, -15);
        glVertex3f( -15, 0, -15);
        glVertex3f( -15, 0, -30);
        glVertex3f( 0,  0, -30);
    }
    glEnd();
	glColor3f(1.0, 1.0, 1.0 );
	glBegin(GL_QUADS);
    {
        glVertex3f(-15, 0, -15);
        glVertex3f(-30, 0, -15);
        glVertex3f(-30, 0, -30);
        glVertex3f(-15, 0, -30);
    }
    glEnd();
	glColor3f(0.0, 0.0, 0.0 );	
	glBegin(GL_QUADS);
    {
        glVertex3f(-30, 0, -15);
        glVertex3f(-45, 0, -15);
        glVertex3f(-45, 0, -30);
        glVertex3f(-30, 0, -30);
    }
    glEnd();
	glColor3f(1.0, 1.0, 1.0 );
	glBegin(GL_QUADS);
    {
        glVertex3f(-45, 0, -15);
        glVertex3f(-60, 0, -15);
        glVertex3f(-60, 0, -30);
        glVertex3f(-45, 0, -30);
    }
    glEnd();
	glColor3f(0.0, 0.0, 0.0 );
	glBegin(GL_QUADS);
    {
        glVertex3f( 15, 0, -30);
        glVertex3f( 0, 0, -30);
        glVertex3f( 0, 0, -45);
        glVertex3f( 15, 0, -45);
    }
    glEnd();

	glColor3f(1.0, 1.0, 1.0 );
	glBegin(GL_QUADS);
    {
        glVertex3f( 30, 0, -30);
        glVertex3f( 15, 0, -30);
        glVertex3f( 15, 0, -45);
        glVertex3f( 30, 0, -45);
    }
    glEnd();
	glColor3f(0.0, 0.0, 0.0 );
	glBegin(GL_QUADS);
    {
        glVertex3f( 45, 0, -30);
        glVertex3f( 30, 0, -30);
        glVertex3f( 30, 0, -45);
        glVertex3f( 45, 0, -45);
    }
    glEnd();
	glColor3f(1.0, 1.0, 1.0 );
	glBegin(GL_QUADS);
    {
        glVertex3f( 60, 0, -30);
        glVertex3f( 45, 0, -30);
        glVertex3f( 45, 0, -45);
        glVertex3f( 60, 0, -45);
    }
    glEnd();

	glColor3f(1.0, 1.0, 1.0 );
	glBegin(GL_QUADS);
    {
        glVertex3f( 0,  0, -30);
        glVertex3f( -15, 0, -30);
        glVertex3f( -15, 0, -45);
        glVertex3f( 0,  0, -45);
    }
    glEnd();
	glColor3f(0.0, 0.0, 0.0 );
	glBegin(GL_QUADS);
    {
        glVertex3f(-15, 0, -30);
        glVertex3f(-30, 0, -30);
        glVertex3f(-30, 0, -45);
        glVertex3f(-15, 0, -45);
    }
    glEnd();
	glColor3f(1.0, 1.0, 1.0 );	
	glBegin(GL_QUADS);
    {
        glVertex3f(-30, 0, -30);
        glVertex3f(-45, 0, -30);
        glVertex3f(-45, 0, -45);
        glVertex3f(-30, 0, -45);
    }
    glEnd();
	glColor3f(0.0, 0.0, 0.0 );
	glBegin(GL_QUADS);
    {
        glVertex3f(-45, 0, -30);
        glVertex3f(-60, 0, -30);
        glVertex3f(-60, 0, -45);
        glVertex3f(-45, 0, -45);
    }
    glEnd();
	glColor3f(1.0, 1.0, 1.0 );
	glBegin(GL_QUADS);
    {
        glVertex3f( 15, 0, -45);
        glVertex3f( 0, 0, -45);
        glVertex3f( 0, 0, -60);
        glVertex3f( 15, 0, -60);
    }
    glEnd();

	glColor3f(0.0, 0.0, 0.0 );
	glBegin(GL_QUADS);
    {
        glVertex3f( 30, 0, -45);
        glVertex3f( 15, 0, -45);
        glVertex3f( 15, 0, -60);
        glVertex3f( 30, 0, -60);
    }
    glEnd();
	glColor3f(1.0, 1.0, 1.0 );
	glBegin(GL_QUADS);
    {
        glVertex3f( 45, 0, -45);
        glVertex3f( 30, 0, -45);
        glVertex3f( 30, 0, -60);
        glVertex3f( 45, 0, -60);
    }
    glEnd();
	glColor3f(0.0, 0.0, 0.0 );
	glBegin(GL_QUADS);
    {
        glVertex3f( 60, 0, -45);
        glVertex3f( 45, 0, -45);
        glVertex3f( 45, 0, -60);
        glVertex3f( 60, 0, -60);
    }
    glEnd();

	glColor3f(0.0, 0.0, 0.0 );
	glBegin(GL_QUADS);
    {
        glVertex3f( 0,  0, -45);
        glVertex3f( -15, 0, -45);
        glVertex3f( -15, 0, -60);
        glVertex3f( 0,  0, -60);
    }
    glEnd();
	glColor3f(1.0, 1.0, 1.0 );
	glBegin(GL_QUADS);
    {
        glVertex3f(-15, 0, -45);
        glVertex3f(-30, 0, -45);
        glVertex3f(-30, 0, -60);
        glVertex3f(-15, 0, -60);
    }
    glEnd();
	glColor3f(0.0, 0.0, 0.0 );	
	glBegin(GL_QUADS);
    {
        glVertex3f(-30, 0, -45);
        glVertex3f(-45, 0, -45);
        glVertex3f(-45, 0, -60);
        glVertex3f(-30, 0, -60);
    }
    glEnd();
	glColor3f(1.0, 1.0, 1.0 );
	glBegin(GL_QUADS);
    {
        glVertex3f(-45, 0, -45);
        glVertex3f(-60, 0, -45);
        glVertex3f(-60, 0, -60);
        glVertex3f(-45, 0, -60);
    }
    glEnd();
}

void display(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0,0,0,0);	//color black
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDisable(GL_DEPTH_TEST);
	glMatrixMode(GL_MODELVIEW);
	cam12.setModelviewMatrix(); 
	cam12.setShape(cam12.viewAngle, cam12.aspectRatio, cam12.nearDistance, cam12.farDistance);
    glPushMatrix();
    {
		drawFloor();	
	}
    glPopMatrix();
	glPushMatrix();
    {
		glTranslatef( 0.0 ,0.0 ,0.0 );	
		glColor3f(1.0, 0.0, 0.0 );
		drawSquare(30);
    }
    glPopMatrix();
    glPushMatrix();
    {
        glTranslatef( 40.0 , 0.0, 20.0);
		glColor3f(0.0, 0.0, 1.0 );
		glutSolidSphere(20.0,30,30);
    }
    glPopMatrix();
    glPushMatrix();
    {
        glTranslatef( -20.0, -10.0, 40.0 );
        glColor3f(0.0, 1.0, 0.0 );
		glutSolidSphere(10.0,30,30);
    }
    glPopMatrix();
    glPushMatrix();
    {
        glTranslatef( 0.0, 30.0 ,15.0 );
		glColor3f(1.0, 1.0, 0.0 );
        glutSolidSphere(15.0,30,30);
    }
    glPopMatrix();
	if(rayTraceDoing)
	{
		trace();
		rayTraceDoing=false;
	}
	glutSwapBuffers();
}

void animate(){
	
	glutPostRedisplay();
}

void init(){
	
	drawgrid=1;
	drawaxes=1;
	cameraHeight=100.0;
	cameraAngle=1.0;
	sizeSphere=15;
	sizeCube=15.0;
	radius = 10;
	radiCylinder=10,heightCylinder=30;
 	rayTraceDoing = false;
	generateEnvironment();
 	glClearColor(0,0,0,0);
    glShadeModel(GL_SMOOTH); // or could be GL_FLAT
    glEnable(GL_NORMALIZE);
}

int main(int argc, char **argv){
	glutInit(&argc,argv);
	fileInput();
	glutInitWindowSize(viewPlaneX, viewPlaneY);
	glutInitWindowPosition(0, 0);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);	
	glutCreateWindow("My OpenGL Program");
	init();
	glEnable(GL_DEPTH_TEST);	
	glViewport(0, 0, viewPlaneX, viewPlaneY);
	cam12.setShape(80.0, 1, 1, 10000.0);
	cam12.set(165.0,70.0,40.0, 0,0.25,0, 0,1,0);
	glutDisplayFunc(display);	
	glutIdleFunc(animate);		
	glutKeyboardFunc(keyboardListener);
	glutSpecialFunc(specialKeyListener);
	glutMouseFunc(mouseListener);
	glutMainLoop();		
	return 0;
}
