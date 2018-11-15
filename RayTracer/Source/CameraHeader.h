#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<GL/glut.h>

struct Vector {
	double x,y,z;
};
struct Point1 {
	double x,y,z;
};
Point1 setPoint(double x1, double y1, double z1);
Vector FVector(double x1, double y1, double z1);
Vector crossProduct(Vector u1, Vector v1);
Vector addVector(Vector u1, Vector v1);
Vector subVector(Vector u1, Vector v1);
Vector multVector(Vector u1, Vector v1);
double dotProduct(Vector v1, Vector u1);
double getVectorLength(Vector v1);
Vector normalizeVector(Vector v1);
Vector constantProduct(double value1, Vector u1);
Vector negateVector(Vector u1);
class Camera
{
private:
public:
	void setModelviewMatrix(void);
	double viewAngle,   aspectRatio,   farDistance,   nearDistance,   height,   width;
	int row, col;
	Point1 eye;	
	Vector u,v,n;
	Camera();
	void yaw(double angle1);
	void pitch(double angle1); 
	void slide(double delU,   double delV,   double delN); 
	void setShape(double vAng,  double asp,  double nearD,     double farD);
	void set(double xEye, double yEye, double zEye, double xLook, double yLook, double zLook, double xUp, double yUp, double zUp);
	void roll(double angle1); 
};


