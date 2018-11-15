#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<GL/glut.h>
#include "CameraHeader_12_12_1992.h"

#define SQR(x) (x*x)
#define NULL_VECTOR FVector_12_12(0.0,0.0,0.0)


double getVectorLength_12_12(Vector_12_12_1992 v)
{
	return sqrt(SQR(v.x)+SQR(v.y)+SQR(v.z));
}

Vector_12_12_1992 FVector_12_12(double x, double y, double z)
{
	Vector_12_12_1992 tmp_12;
	tmp_12.x = x;
	tmp_12.y = y;
	tmp_12.z = z;
	return tmp_12;
}

Point1_12_12_1992 setPoint_12_12(double x, double y, double z)
{
	Point1_12_12_1992 tmp_12;
	tmp_12.x = x;
	tmp_12.y = y;
	tmp_12.z = z;
	return tmp_12;
}

double dotProduct_12_12(Vector_12_12_1992 v, Vector_12_12_1992 u)
{
	return ((v.x*u.x)+(v.y*u.y)+(v.z*u.z));
}

Vector_12_12_1992 crossProduct_12_12(Vector_12_12_1992 u, Vector_12_12_1992 v)
{
	Vector_12_12_1992 resVector_12;
	resVector_12.x = ((u.y)*(v.z)) - ((u.z)*(v.y));
	resVector_12.y = ((u.z)*(v.x)) - ((u.x)*(v.z));
	resVector_12.z = ((u.x)*(v.y)) - ((u.y)*(v.x));

	return resVector_12;
}


Vector_12_12_1992 normalizeVector_12_12(Vector_12_12_1992 v)
{
	Vector_12_12_1992 res_12;
	double l = getVectorLength_12_12(v);
	if (l == 0.0) return NULL_VECTOR;
	res_12.x = v.x / l;
	res_12.y = v.y / l;
	res_12.z = v.z / l;
	return res_12;
}

Camera_12_12_1992::Camera_12_12_1992()
{
	eye_12 = setPoint_12_12(0.0,0.0, 0.0);
	u_12 = FVector_12_12(0.0,0.0, 0.0);
	v_12 = FVector_12_12(0.0,0.0, 0.0);
	n_12 = FVector_12_12(0.0,0.0, 0.0);
}
void Camera_12_12_1992::setModelviewMatrix_12_12(void)
{
	// load modelview matrix with existing camera values
	float m_12[16];
	Vector_12_12_1992 eVec = FVector_12_12(eye_12.x, eye_12.y, eye_12.z); // a vector version of eye
	m_12[0] = u_12.x; m_12[4] = u_12.y; m_12[8] = u_12.z; m_12[12] = -dotProduct_12_12(eVec, u_12);
	m_12[1] = v_12.x; m_12[5] = v_12.y; m_12[9] = v_12.z; m_12[13] = -dotProduct_12_12(eVec,v_12);
	m_12[2] = n_12.x; m_12[6] = n_12.y; m_12[10] = n_12.z; m_12[14] = -dotProduct_12_12(eVec,n_12);
	m_12[3] = 0; m_12[7] = 0; m_12[11] = 0; m_12[15] = 1.0;
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(m_12); // load OpenGL’s modelview matrix
}
void Camera_12_12_1992::set_12_12(double xEye, double yEye, double zEye, double xLook, double yLook, double zLook, double xUp, double yUp, double zUp)
{
	// create a modelview matrix and send it to OpenGL
	eye_12=setPoint_12_12(xEye, yEye, zEye); // store the given eye position
	n_12=FVector_12_12(eye_12.x - xLook, eye_12.y - yLook, eye_12.z - zLook); // make n
	Vector_12_12_1992 up = FVector_12_12(xUp, yUp, zUp);
	u_12=crossProduct_12_12(up,n_12); // make u = up X n
	n_12=normalizeVector_12_12(n_12); 
	u_12=normalizeVector_12_12(u_12); // make them unit length
	v_12=crossProduct_12_12(n_12,u_12); // make v = n X u
	setModelviewMatrix_12_12(); // tell OpenGL
}
void Camera_12_12_1992::setShape_12_12(double vAng, double asp, double nearD, double farD)
{
	glMatrixMode(GL_PROJECTION);
	
	//initialize the matrix
	glLoadIdentity();

	//give PERSPECTIVE parameters
	gluPerspective(vAng, asp, nearD, farD);
}
void Camera_12_12_1992::slide_12_12(double delU_12_14, double delV_12_14, double delN_12_14)
{
	eye_12.x += ((delU_12_14 * u_12.x) + (delV_12_14 * v_12.x) + (delN_12_14 * n_12.x));
	eye_12.y += ((delU_12_14 * u_12.y) + (delV_12_14 * v_12.y) + (delN_12_14 * n_12.y));
	eye_12.z += ((delU_12_14 * u_12.z) + (delV_12_14 * v_12.z) + (delN_12_14 * n_12.z));
	setModelviewMatrix_12_12();
}

void Camera_12_12_1992::yaw_12_12(double angle_12)
{
	// roll the camera through angle degrees
	double sn_12 = sin((3.14159265/180) * angle_12);
	double cs_12 = cos((3.14159265/180) * angle_12);

	Vector_12_12_1992 t = FVector_12_12(n_12.x, n_12.y, n_12.z); // remember old n
	n_12 = FVector_12_12((cs_12*t.x) + (sn_12*u_12.x), (cs_12*t.y) + (sn_12*u_12.y), (cs_12*t.z) + (sn_12*u_12.z));
	u_12 = FVector_12_12(-(sn_12*t.x) + (cs_12*u_12.x), -(sn_12*t.y) + (cs_12*u_12.y), -(sn_12*t.z) + (cs_12*u_12.z));
	setModelviewMatrix_12_12();
}
void Camera_12_12_1992::pitch_12_12(double angle_1200)
{
	// roll the camera through angle degrees
	double sn_1200 = sin((3.14159265/180) * angle_1200);
	double cs_1200 = cos((3.14159265/180) * angle_1200);

	Vector_12_12_1992 t = FVector_12_12(n_12.x, n_12.y, n_12.z); // remember old n
	n_12 = FVector_12_12((cs_1200*t.x) - (sn_1200*v_12.x), (cs_1200*t.y) - (sn_1200*v_12.y), (cs_1200*t.z) - (sn_1200*v_12.z));
	v_12 = FVector_12_12((sn_1200*t.x) + (cs_1200*v_12.x), (sn_1200*t.y) + (cs_1200*v_12.y), (sn_1200*t.z) + (cs_1200*v_12.z));
	setModelviewMatrix_12_12();
}
void Camera_12_12_1992::roll_12_12(double angle_114)
{
	// roll the camera through angle degrees
	double sn_114 = sin((3.14159265/180) * angle_114);
	double cs_114 = cos((3.14159265/180) * angle_114);
	
	Vector_12_12_1992 t = FVector_12_12(u_12.x, u_12.y, u_12.z); // remember old u
	u_12 = FVector_12_12((cs_114*t.x) - (sn_114*v_12.x), (cs_114*t.y) - (sn_114*v_12.y), (cs_114*t.z) - (sn_114*v_12.z));
	v_12 = FVector_12_12((sn_114*t.x) + (cs_114*v_12.x), (sn_114*t.y) + (cs_114*v_12.y), (sn_114*t.z) + (cs_114*v_12.z));
	setModelviewMatrix_12_12();
}


