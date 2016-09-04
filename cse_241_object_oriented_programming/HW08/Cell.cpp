/*
EMRAH YILDIRIM 111044056
*/

#include "Cell.h"


namespace HW06
{
	int Cell::takeCoor(void)
	{
		int coor;

		cin >> coor;

		return coor;
	}


	void Cell::printCell(void)	const
	{
		cout << getX() << "." << getY() << " ";
	}


	inline int  Cell::getX(void)	const
	{
		return x;
	}


	inline int  Cell::getY(void)	const
	{
		return y;
	}


	inline void Cell::setX(const int& cX)
	{
		x = cX;
	}


	inline void Cell::setY(const int& cY)
	{
		x = cY;
	}


	void Cell::setCell(const int& cX, const int& cY)
	{
		x = cX;
		y = cY;
	}



	bool Cell::operator < (const Cell& other)	const
	{

		if (getX() < other.getX())
			return true;
		else
		if ((getX() == other.getX()) && getY() < other.getY())
			return true;
		else
			return false;
	}


	bool Cell::operator > (const Cell& other)	const
	{
		if (getX() > other.getX())
			return true;
		else
		if ((getX() == other.getX()) && getY() > other.getY())
			return true;
		else
			return false;
	}


	bool Cell::operator >= (const Cell& other)	const
	{
		if (*this > other || *this == other)
			return true;

		else
			return false;


	}



	bool Cell::operator <= (const Cell& other)	const
	{
		if (*this < other || *this == other)
			return true;

		else
			return false;


	}


	bool Cell::operator == (const Cell& other)	const
	{
		if (x == other.x && y == other.y)
			return true;
		else
			return false;
	}



	bool Cell::operator != (const Cell& other)	const
	{
		if (x != other.x || y != other.y)
			return true;
		else
			return false;
	}

	
	Cell Cell::operator ++(int ignore)
	{
		Cell temp=*this;
		
		x++; y++;
		
		return temp;
	}


	Cell& Cell::operator ++(void)
	{
		x++; y++;
		
		return *this;
	}
	
	
	Cell Cell::operator --(int ignore)
	{
		Cell temp=*this;
		
		x--; y--;
		
		return temp;
	}


	Cell& Cell::operator --(void)
	{
		x--; y--;
		
		return *this;
	}
	
	
	
	ostream& operator << (ostream& out, const Cell& cell)
	{
		out << cell.x << "." << cell.y << endl;

		return out;
	}


	istream& operator >> (istream& inp, Cell& cell)
	{
		inp >> cell.x >> cell.y;

		if (cell.x >= 0 && cell.y >= 0)
			return inp;
		else
		{
			cout << "wrong cell coordinates\n";
			exit(1);
		}
	}

}