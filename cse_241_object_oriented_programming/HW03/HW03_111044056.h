/*##########################################################################*/
/*HW03_111044056.h															*/
/*--------------------------------------------------------------------------*/
/*Emrah YILDIRIM 111044056													*/
/*																			*/
/*##########################################################################*/


#include<iostream>
#include<cmath>

#ifndef HW03_111044056_H
#define	HW03_111044056_H

using namespace std;


/*##########################################################################*/
/*						Classes and Function Prototypes						*/
/*##########################################################################*/

class Vect3D
{
	public:
		//constructor
		explicit Vect3D(double cX=0.0, double cY=0.0, double cZ=0.0) : x(cX), y(cY), z(cZ)
		{/*bilerek bos birakildi*/}
		
		
		//input
		double takeDot();
		
		
		// outputs (as inline)
		void printX() const	{ cout << x <<endl; }

		void printY() const	{ cout << y <<endl; }

		void printZ() const	{ cout << z <<endl; }
		
		void printVector() const
		{
			cout << x <<"x " << y <<"y " << z << "z" <<endl; 
		}
			
		
		
		//the getters (as inline)
		double getX() const	{return x;}

		double getY() const	{return y;}

		double getZ() const	{return z;}
		
			
			
			
		//setters (as inline except setVect)
		void setX(const double& dot) {x = dot;}

		void setY(const double& dot) {y = dot;}
		
		void setZ(const double& dot) {z = dot;}

		void setVect(const double& dotX, const double& dotY, const double& dotZ);
		
		
		
		// iki vektor arasi nokta carpimi yapar
		// ikinci vektor arguman olarak alinir
		// double return eder
		double dotProduct(const Vect3D& vect) const;
		
		//vektorun buyuklugunu bulur
		//parametre almaz double return eder
		double evaluateMagnitude() const;
		
		// iki vektor arasi vektorel carpim yapar
		// ikinci vektor parametre olarak alinir
		// Vect3D return eder
		Vect3D vectorProduct(const Vect3D& vect);
		
	
	private:
		double x, y, z; //dots
		double dot;		//temp dot		
};



extern void testCallByValue(Vect3D vect1, Vect3D vect2);
extern void testCallByReference(Vect3D & vect1, Vect3D & vect2);

#endif
