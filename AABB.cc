#include <iostream>
#include <algorithm>

#include "AABB.h"



AABB::AABB(int _top, int _left, int _bottom, int _right):
    top(float(_top)), left(float(_left)),
    bottom(float(_bottom)), right(float(_right))
    //creates a box in a coordinate system
{}

float AABB::get_top()
{
    return top;
}

float AABB::get_left()
{
    return left;
}

float AABB::get_bottom()
{
    return bottom;
}

float AABB::get_right()
{
    return right;
}
  
bool AABB::contain ( int x, int y)
//checks if x,y is a coordinate in box
{
    return left <=  x  && x <= right && top <= y && y <= bottom;
}

bool AABB::contain ( struct pt_cord pt )
//checks if pt in box
{
    return contain( pt.x, pt.y );
}

bool AABB::intersect (AABB boxb)
//checks if box overlaps boxb
{
    return (( boxb.get_top() <= get_bottom() &&
	      boxb.get_bottom() >= top) &&
	    ( boxb.get_left() <= get_right() &&
	      boxb.get_right() >= get_left() ));
}

  
AABB AABB::min_bounding_box(AABB boxa)
{
    //creates a box surrounding both boxes given (one being this and the other being boxa)
   
    float max_top{std::min(boxa.get_top(), get_top())};
    float max_left{std::min(boxa.get_left(), get_left())};
    float max_bot{std::max(boxa.get_bottom(), get_bottom())};
    float max_right{std::max(boxa.get_right(), get_right())};

    return AABB(max_top, max_left, max_bot, max_right);
}
  
bool AABB::may_collide( AABB from, AABB to )
{
    //checks if AABB from will collide with this when moving to AABB to
    return intersect(from.min_bounding_box(to));
}
  
bool AABB::collision_point(AABB from, AABB to, pt_cord& where)
{
    //checks where AABB from will collide with this when moving to AABB to
    if (!may_collide(from, to))
    {
	return false;
    }
    int dx{to.right - from.right};
    int dy{to.bottom - from.bottom};
    int maxi{std::max(abs(dx), abs(dy))}; //MAXIMUM
    float xstep{float(dx) / float(maxi)};
    float ystep{float(dy) / float(maxi)};

    for(int i = 0; i <  maxi; i++)
    {
	from.top += ystep;
	from.left += xstep;
	from.bottom += ystep;
	from.right += xstep;
	if(intersect(from))
	{
	    where.y = from.top;
	    where.x = from.left;
	    return true;
	}	
    }
    return false;
}
