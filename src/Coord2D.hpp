#ifndef COORD2D_HPP_INCLUDED
#define COORD2D_HPP_INCLUDED

/**
@brief 2D coordinates
**/
class Coord2D
{
public:
	Coord2D():Coord2D(0,0){}
	Coord2D(int _x, int _y){x=_x; y=_y;}
	Coord2D(const Coord2D& other) : x(other.x), y(other.y){}


	Coord2D& operator=(const Coord2D &other){x=other.x; y=other.y; return *this;}

	Coord2D operator+(const Coord2D& other){return Coord2D(this->x+other.x, this->y+other.y);}
	void operator+=(const Coord2D& other){this->x+=other.x; this->y+=other.y;;}

	Coord2D operator-(const Coord2D& other){return Coord2D(this->x-other.x, this->y-other.y);}
	void operator-=(const Coord2D& other){this->x-=other.x; this->y-=other.y;}

	Coord2D operator*(const int& other){return Coord2D(this->x*other, this->y*other);}
	void operator*=(const int& other){this->x*=other; this->y*=other;}

	Coord2D operator/(const int& other){return (*this)*(1/other);}
	void operator/=(const int& other){(*this)*=(1/other);}


	int x;
	int y;
};

#endif // COORD2D_HPP_INCLUDED
