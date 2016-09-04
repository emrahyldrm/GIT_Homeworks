/*##########################################################################*/
/*HW03_111044056.cpp														*/
/*--------------------------------------------------------------------------*/
/*Emrah YILDIRIM 111044056													*/
/*																			*/
/*##########################################################################*/


#include"HW03_111044056.h"


/*##########################################################################*/
/*							Vect3D Member Functions							*/
/*##########################################################################*/
// kullanicidan nokta alir
// hemen ardindan noktanin atanacagi degiskenin..
// .. setter fonksiyonu cagirilmalidir
double Vect3D::takeDot()
{
	
	cin >> dot;
	
	return dot;
}


// butun vektoru set eder 3 adet double argüman alir
void Vect3D::setVect(const double& dotX, const double& dotY, const double& dotZ)
{
	x = dotX;
	y = dotY;
	z = dotZ;
}


//vektorun buyuklugunu bulur
//parametre almaz double return eder
double Vect3D::evaluateMagnitude() const
{
	return (sqrt(x*x + y*y + z*z));
}


// iki vektor arasi nokta carpimi yapar
// ikinci vektor arguman olarak alinir
// double return eder
double Vect3D::dotProduct(const Vect3D& vect) const
{
	return (x*vect.x + y*vect.y + z*vect.z);
}


// iki vektor arasi vektorel carpim yapar
// ikinci vektor parametre olarak alinir
// Vect3D return eder
Vect3D Vect3D::vectorProduct(const Vect3D& vect)
{
	double d1=0.0, d2=0.0, d3=0.0;
	Vect3D result;
	
	d1 = (y*vect.z - z*vect.y);
	d2 = (x*vect.z - z*vect.x);
	d3 = (x*vect.y - y*vect.x);
	
	result.setVect(d1, d2, d3);
		
	return result;	
}






/*##########################################################################*/
/*								Test Functions								*/
/*##########################################################################*/


void testCallByValue(Vect3D vect1, Vect3D vect2) 
{
	Vect3D result;
	
	
	cout << "Enter the dots for vector1\n"
		 << "first x, after y, last z\n";
	
	vect1.setX(vect1.takeDot());
	vect1.setY(vect1.takeDot());
	vect1.setZ(vect1.takeDot());
	
	
	cout << "Enter the dots for vector2\n"
		 << "first x, after y, last z\n";
	
	
	vect2.setX(vect1.takeDot());
	vect2.setY(vect1.takeDot());
	vect2.setZ(vect1.takeDot());
		 
	cout << "\n----------------------------------------\n";
	
	cout << "1. vector : ("
		 <<vect1.getX()<<"x, "
		 <<vect1.getY()<<"y, "
		 <<vect1.getZ()<<"z)\n";
		
	cout << "2. vector : ("
		 <<vect2.getX()<<"x, "
		 <<vect2.getY()<<"y, "
		 <<vect2.getZ()<<"z)\n";
		
	cout << "Result of dot product between 1 and 2 is: "
		 << vect1.dotProduct(vect2)
		 << endl;
		
	
	result = vect1.vectorProduct(vect2);
	
	cout << "Result of vector product between 1 and 2 is: ";
		 result.printVector();
}





void testCallByReference(Vect3D & vect1, Vect3D & vect2)
{
	Vect3D result;
	
	cout << "Enter the dots for vector1\n"
		 << "first x, after y, last z\n";
	
	vect1.setX(vect1.takeDot());
	vect1.setY(vect1.takeDot());
	vect1.setZ(vect1.takeDot());
	
	
	cout << "Enter the dots for vector2\n"
		 << "first x, after y, last z\n";
	
	
	vect2.setX(vect1.takeDot());
	vect2.setY(vect1.takeDot());
	vect2.setZ(vect1.takeDot());
		 
	cout << "\n----------------------------------------\n";
	

	cout << "1. vector : ("
		 <<vect1.getX()<<"x, "
		 <<vect1.getY()<<"y, "
		 <<vect1.getZ()<<"z)\n";
		
	cout << "2. vector : ("
		 <<vect2.getX()<<"x, "
		 <<vect2.getY()<<"y, "
		 <<vect2.getZ()<<"z)\n";
		 
	cout << "Result of dot product between 1 and 2 is: "
		 << vect1.dotProduct(vect2)
		 << endl;
	
	
	result = vect1.vectorProduct(vect2);
	
	cout << "Result of vector product between 1 and 2 is: ";
		 result.printVector();
}
