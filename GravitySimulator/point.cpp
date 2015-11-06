/***********************************************************************
 * Source File:
 *    Point : The representation of a position on the screen
 * Author:
 *    Br. Helfrich & Samuel Hibbard
 * Summary:
 *    Everything we need to know about a location on the screen, including
 *    the location and the bounds.
 ************************************************************************/

#include "point.h"
#include <cassert>

/******************************************
 * POINT : CONSTRUCTOR WITH X,Y
 * Initialize the point to the passed position
 *****************************************/
Position::Position(float x, float y) : x(0.0), y(0.0), checkNum(false), dead(false), wrap(false), percentage(false)
{
   setX(x);
   setY(y);
}

/*******************************************
 * CONSTRUCTOR with x, y, percentage
 ******************************************/
Position::Position(float x, float y, bool percentage, bool check)
{
    setX(x);
    setY(y);
    this->percentage = percentage;
    this->checkNum = check;
}

/*******************************************
 * POINT : SET X
 * Set the x position if the value is within range
 *******************************************/
void Position::setX(float x)
{
   assert(xMin < xMax);
    
    //HERE is where I changed it.
   if (getWrap())
   {
      this->x = x;
      wrapAround();
   }
   else if (!checkNum || (x >= xMin && x <= xMax))
      this->x = x;
   else
   {
      dead = true;
   }
}

/********************************************
 * POINT : Assignmenet
 *******************************************/
const Position & Position :: operator = (const Position & rhs)
{
   x        = rhs.x;
   y        = rhs.y;
   checkNum    = rhs.checkNum;
   dead     = rhs.dead;
   percentage = rhs.percentage;

   return *this;
}

/*******************************************
 * POINT : SET Y
 * Set the y position if the value is within range
 *******************************************/
void Position::setY(float y)
{
   assert(yMin < yMax);
    
    //HERE is where I changed it.
   if (getWrap())
   {
      this->y = y;
      wrapAround();
   }
   else if (!checkNum || (y >= yMin && y <= yMax))
      this->y = y;
   else
   {
      dead = true;
   }
}


/******************************************
 * POINT insertion
 *       Display coordinates on the screen
 *****************************************/
std::ostream & operator << (std::ostream & out, const Position & pt)
{
   out << "(" << pt.getX() << ", " << pt.getY() << ")";
   return out;
}

/*******************************************
 * POINT extraction
 *       Prompt for coordinates
 ******************************************/
std::istream & operator >> (std::istream & in, Position & pt)
{
   float x;
   float y;
   in >> x >> y;

   pt.setX(x);
   pt.setY(y);

   return in;
}

/***********************************
 * WRAP
 *      Wrap around the screen!
 *      I created this wrap.
 **********************************/
void Position::wrapAround()
{
    assert(xMin < xMax); //these better be this way!
    assert(yMin < yMax);
    
    if (x > xMax)
    {
        x -= (xMax - xMin);
    }
    if (x < xMin)
    {
        x += (xMax - xMin);
    }
    if (y > yMax)
    {
        y -= (yMax - yMin);
    }
    if (y < yMin)
    {
        y += (yMax - yMin);
    }
    
    assert(x <= xMax);  //everything should be now correct!
    assert(x >= xMin);
    assert(y <= yMax);
    assert(y > yMin);
}

void Position::addXY(float x, float y)
{
    setX(getX() + x);
    setY(getY() + y);
}