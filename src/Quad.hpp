#ifndef QUAD_HPP_INCLUDED
#define QUAD_HPP_INCLUDED



#include "coloring.h"
#include "Coord2D.hpp"

/**
@brief Class to represent a quad in 2 dimensions, like a surface or a window
@note The origin of the quad is at the top left corner, x is horizontal and y vertical
**/
class Quad
{
public:
	Quad(int _x=0, int _y=0, int _width=0, int _height=0): m_x(_x), m_y(_y), m_width(_width), m_height(_height)
	{}
	Quad(const Coord2D& start, const Coord2D& stop): m_x(start.x), m_y(start.y)
	{SetBottomRight(stop, false);}

	void SetTop(int y, bool bKeepHeight)
	{
		if(!bKeepHeight)
			m_height-=y-m_y;

		m_y=y;

		if(m_width<0)
		{
			#ifndef _RELEASE_
			cErr<<"Wrong quad operation => width="<<m_width<<" set to 1"<<std::endl;
			#endif
			m_width=1;
		}
		if(m_height<0)
		{
			#ifndef _RELEASE_
			cErr<<"Wrong quad operation => height="<<m_height<<" set to 1"<<std::endl;
			#endif
			m_height=1;
		}
	}
	void SetBottom(int y, bool bKeepHeight)
	{
		if(!bKeepHeight)
			m_height+=y-m_y;

		if(m_width<0)
		{
			#ifndef _RELEASE_
			cErr<<"Wrong quad operation => width="<<m_width<<" set to 1"<<std::endl;
			#endif
			m_width=1;
		}
		if(m_height<0)
		{
			#ifndef _RELEASE_
			cErr<<"Wrong quad operation => height="<<m_height<<" set to 1"<<std::endl;
			#endif
			m_height=1;
		}
	}
	void SetLeft(int x, bool bKeepWidth)
	{
		if(!bKeepWidth)
			m_width-=x-m_x;

		m_x=x;

		if(m_width<0)
		{
			#ifndef _RELEASE_
			cErr<<"Wrong quad operation => width="<<m_width<<" set to 1"<<std::endl;
			#endif
			m_width=1;
		}
		if(m_height<0)
		{
			#ifndef _RELEASE_
			cErr<<"Wrong quad operation => height="<<m_height<<" set to 1"<<std::endl;
			#endif
			m_height=1;
		}
	}
	void SetRight(int x, bool bKeepWidth)
	{
		if(!bKeepWidth)
			m_width+=x-m_x;

		if(m_width<0)
		{
			#ifndef _RELEASE_
			cErr<<"Wrong quad operation => width="<<m_width<<" set to 1"<<std::endl;
			#endif
			m_width=1;
		}
		if(m_height<0)
		{
			#ifndef _RELEASE_
			cErr<<"Wrong quad operation => height="<<m_height<<" set to 1"<<std::endl;
			#endif
			m_height=1;
		}
	}

	int GetTop()const		{	return m_y;					}
	int GetBottom()const	{	return m_y+m_height;		}
	int GetLeft()const		{	return m_x;					}
	int GetRight()const		{	return m_x+m_width;			}


	void SetTopLeft(const Coord2D& pos, bool bKeepSize)
	{
		if(!bKeepSize)
		{
			m_width-=pos.x - GetLeft();
			m_height-=pos.y - GetTop();
		}
		m_x = pos.x;
		m_y = pos.y;

		if(m_width<0)
		{
			#ifndef _RELEASE_
			cErr<<"Wrong quad operation => width="<<m_width<<" set to 1"<<std::endl;
			#endif
			m_width=1;
		}
		if(m_height<0)
		{
			#ifndef _RELEASE_
			cErr<<"Wrong quad operation => height="<<m_height<<" set to 1"<<std::endl;
			#endif
			m_height=1;
		}
	}
	void SetTopRight(const Coord2D& pos, bool bKeepSize)
	{
		if(!bKeepSize)
		{
			m_height-=pos.y - GetTop();
			m_width+=pos.x - GetRight();
		}
		m_y = pos.y;

		if(m_width<0)
		{
			#ifndef _RELEASE_
			cErr<<"Wrong quad operation => width="<<m_width<<" set to 1"<<std::endl;
			#endif
			m_width=1;
		}
		if(m_height<0)
		{
			#ifndef _RELEASE_
			cErr<<"Wrong quad operation => height="<<m_height<<" set to 1"<<std::endl;
			#endif
			m_height=1;
		}
	}
	void SetBottomLeft(const Coord2D& pos, bool bKeepSize)
	{
		if(!bKeepSize)
		{
			m_width-=pos.x - GetLeft();
			m_height+=pos.y - GetBottom();
		}
		m_x = pos.x;

		if(m_width<0)
		{
			#ifndef _RELEASE_
			cErr<<"Wrong quad operation => width="<<m_width<<" set to 1"<<std::endl;
			#endif
			m_width=1;
		}
		if(m_height<0)
		{
			#ifndef _RELEASE_
			cErr<<"Wrong quad operation => height="<<m_height<<" set to 1"<<std::endl;
			#endif
			m_height=1;
		}
	}
	void SetBottomRight(const Coord2D& pos, bool bKeepSize)
	{
		if(!bKeepSize)
		{
			m_width+=pos.x - GetRight();
			m_height+=pos.y - GetBottom();
		}

		if(m_width<0)
		{
			#ifndef _RELEASE_
			cErr<<"Wrong quad operation => width="<<m_width<<" set to 1"<<std::endl;
			#endif
			m_width=1;
		}
		if(m_height<0)
		{
			#ifndef _RELEASE_
			cErr<<"Wrong quad operation => height="<<m_height<<" set to 1"<<std::endl;
			#endif
			m_height=1;
		}
	}

	Coord2D GetTopLeft()const		{	return Coord2D(m_x, m_y);					}
	Coord2D GetTopRight()const		{	return Coord2D(m_x+m_width, m_y);			}
	Coord2D GetBottomLeft()const	{	return Coord2D(m_x, m_y+m_width);			}
	Coord2D GetBottomRight()const	{	return Coord2D(m_x+m_width, m_y+m_width);	}


	void SetWidth(unsigned int width)	{	m_width=width;		}
	void SetHeight(unsigned int height)	{	m_height=height;	}

	unsigned int GetWidth()const		{	return m_width;		}
	unsigned int GetHeight()const		{	return m_height;	}

	void SetPosition(Coord2D pos)
	{
		m_x = pos.x;
		m_y = pos.y;
	}

	Coord2D GetPosition()const		{	return Coord2D(m_x, m_y);	}


	void PrintBounds()const
	{
		std::cout<<"QuadBounds:"<<"\tL="<<GetLeft()<<"\tR="<<GetTop()<<"\tW="<<GetWidth()<<"\tH="<<GetHeight()<<std::endl;
	}


	int m_x, m_y, m_width, m_height;
};


#endif // QUAD_HPP_INCLUDED
