#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<GL/glut.h>
#include "CameraHeader.h"
#define pi 3.14159265
#define NULL_VECTOR FVector(0.0,0.0,0.0)
#define SQR(x) (x*x)
Vector FVector(double x1,  double y1,  double z1)
{
	Vector tmp;
	tmp.x = x1;	
	tmp.y = y1;
	tmp.z = z1;
	return tmp;
}
Point1 setPoint(double x1, double y1, double z1)
{	
	Point1 tmp;	
	tmp.x = x1;
	tmp.y = y1;
	tmp.z = z1;
	return tmp;
}
Vector crossProduct(Vector u1,    Vector v1)
{
	Vector resVector;	
	resVector.x = ((u1.y)*(v1.z)) - ((u1.z)*(v1.y));
	resVector.y = ((u1.z)*(v1.x)) - ((u1.x)*(v1.z));
	resVector.z = ((u1.x)*(v1.y)) - ((u1.y)*(v1.x));
	return resVector;
}
Vector addVector(Vector u1, Vector v1)
{
	Vector resVector;
	resVector.x = u1.x + v1.x;
	resVector.y = u1.y + v1.y;
	resVector.z = u1.z + v1.z;
	return resVector;
}
Vector subVector(Vector u1, Vector v1)
{
	Vector resVector;
	resVector.x = u1.x - v1.x;
	resVector.y = u1.y - v1.y;
	resVector.z = u1.z - v1.z;
	return resVector;
}
Vector multVector(Vector u1, Vector v1)
{
	Vector resVector;
	resVector.x = u1.x * v1.x;
	resVector.y = u1.y * v1.y;
	resVector.z = u1.z * v1.z;	
	return resVector;
}
double getVectorLength(Vector v)
{
	return sqrt(SQR(v.x)+SQR(v.y)+SQR(v.z));
}
Vector constantProduct(double value1, Vector u1)
{
	Vector resVector;
	resVector.x = u1.x * value1;
	resVector.y = u1.y * value1;
	resVector.z = u1.z * value1;
	return resVector;
}
double dotProduct(Vector v, Vector u)
{
	return ((v.x*u.x)+(v.y*u.y)+(v.z*u.z));
}
Vector negateVector(Vector u)
{
	Vector resVector;
	resVector.x = -u.x;
	resVector.y = -u.y;
	resVector.z = -u.z;	
	return resVector;
}
Vector normalizeVector(Vector v)
{
	Vector res;
	double l = getVectorLength(v);
	if (l == 0.0) return NULL_VECTOR;
	res.x = v.x / l;
	res.y = v.y / l;
	res.z = v.z / l;
	return res;
}
Camera::Camera()
{
	eye = setPoint(0.0,0.0, 0.0);	
	u = FVector(0.0,0.0, 0.0);
	v = FVector(0.0,0.0, 0.0);
	n = FVector(0.0,0.0, 0.0);
}
void Camera::setModelviewMatrix(void)
{	
	float m[16];	
	Vector eVec = FVector(eye.x, eye.y, eye.z);
	m[0] = u.x; m[4] = u.y; m[8] = u.z; m[12] = -dotProduct(eVec, u);
	m[1] = v.x; m[5] = v.y; m[9] = v.z; m[13] = -dotProduct(eVec,v);
	m[2] = n.x; m[6] = n.y; m[10] = n.z; m[14] = -dotProduct(eVec,n);
	m[3] = 0; m[7] = 0; m[11] = 0; m[15] = 1.0;
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(m); 
}
void Camera::setShape(double vAng, double asp, double nearD, double farD)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	aspectRatio = asp;
	farDistance = farD;
	viewAngle = vAng;
	nearDistance = nearD;    
	double t = 2.0 * 180;
	height = tan(pi * viewAngle/t) * nearDistance;
	width = height * aspectRatio;
	gluPerspective(vAng, asp, nearD, farD);
}
void Camera::set(double xEye, double yEye, double zEye, double xLook, double yLook, double zLook, double xUp, double yUp, double zUp)
{
	
	eye=setPoint(xEye, yEye, zEye); 	
	n=FVector(eye.x - xLook, eye.y - yLook, eye.z - zLook); 
	Vector up = FVector(xUp, yUp, zUp);
	u=crossProduct(up,n); 
	n=normalizeVector(n); u=normalizeVector(u); 
	v=crossProduct(n,u); 
	setModelviewMatrix(); 
}
void Camera::roll(double angle)
{
	double cs1 = cos((3.14159265/180) * angle);
	double sn1 = sin((3.14159265/180) * angle);	
	Vector t = FVector(u.x, u.y, u.z); 
	u = FVector((cs1*t.x) - (sn1*v.x), (cs1*t.y) - (sn1*v.y), (cs1*t.z) - (sn1*v.z));
	v = FVector((sn1*t.x) + (cs1*v.x), (sn1*t.y) + (cs1*v.y), (sn1*t.z) + (cs1*v.z));
	setModelviewMatrix();
}
void Camera::pitch(double angle)
{
	double cs1 = cos((3.14159265/180) * angle);
	double sn1 = sin((3.14159265/180) * angle);
	Vector t = FVector(n.x,   n.y,    n.z);
	n = FVector((cs1*t.x) - (sn1*v.x),   (cs1*t.y) - (sn1*v.y),   (cs1*t.z) - (sn1*v.z));	
	v = FVector((sn1*t.x) + (cs1*v.x),   (sn1*t.y) + (cs1*v.y),    (sn1*t.z) + (cs1*v.z));
	setModelviewMatrix();
}
void Camera::slide(double delU, double delV, double delN)
{
	eye.x += ((delU * u.x) + (delV * v.x) + (delN * n.x));
	eye.y += ((delU * u.y) + (delV * v.y) + (delN * n.y));
	eye.z += ((delU * u.z) + (delV * v.z) + (delN * n.z));
	setModelviewMatrix();
}
void Camera::yaw(double angle)
{	
	double cs1 = cos((3.14159265/180) * angle);
	double sn1 = sin((3.14159265/180) * angle);		
	Vector t = FVector(n.x, n.y, n.z);
	n = FVector((cs1*t.x)  +  (sn1*u.x)  , (cs1*t.y)  +  (sn1*u.y) , (cs1*t.z)  +  (sn1*u.z));
	u = FVector(-(sn1*t.x) + (cs1*u.x)    , -(sn1*t.y) + (cs1*u.y)  , -(sn1*t.z) + (cs1*u.z));
	setModelviewMatrix();
}

