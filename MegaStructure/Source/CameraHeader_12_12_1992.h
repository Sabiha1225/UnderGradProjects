#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<GL/glut.h>

struct Point1_12_12_1992 {
	double x,y,z;
};

struct Vector_12_12_1992 {
	double x,y,z;
};
Point1_12_12_1992 setPoint_12_12(double x, double y, double z);
Vector_12_12_1992 FVector_12_12(double x, double y, double z);
Vector_12_12_1992 crossProduct_12_12(Vector_12_12_1992 u, Vector_12_12_1992 v);
double dotProduct_12_12(Vector_12_12_1992 v, Vector_12_12_1992 u);
double getVectorLength_12_12(Vector_12_12_1992 v);
Vector_12_12_1992 normalizeVector_12_12(Vector_12_12_1992 v);

class Camera_12_12_1992
{
private:
	
	Point1_12_12_1992 eye_12;
	Vector_12_12_1992 u_12,v_12,n_12;
	//double viewAngle, aspect, nearDist, farDist;	
	void setModelviewMatrix_12_12(void);
public:
	Camera_12_12_1992(); // default constructor
	void set_12_12(double xEye, double yEye, double zEye, double xLook, double yLook, double zLook, double xUp, double yUp, double zUp); // like gluLookAt()
	void setShape_12_12(double vAng, double asp, double nearD, double farD);
	void slide_12_12(double delU, double delV, double delN); // slide it
	void yaw_12_12(double angle); // yaw it
	void pitch_12_12(double angle); // increase pitch
	void roll_12_12(double angle); // roll it
};


