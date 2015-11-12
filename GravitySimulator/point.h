/***********************************************************************
 * Header File:
 *    Point : The representation of a position on the screen
 * Author:
 *    Br. Helfrich & Samuel Hibbard
 * Summary:
 *    Everything we need to know about a location on the screen, including
 *    the location and the bounds.
 ************************************************************************/


#ifndef POINT_H
#define POINT_H

#include <iostream>

/*********************************************
 * POINT
 * A single position.  
 *********************************************/
class Position
{
public:
   // constructors
   Position() : x(0.0), y(0.0), dead(false), wrap(false), percentage(false), checkNum(false) {}
   Position(bool check, bool percentage) : x(0.0), y(0.0), dead(false), wrap(false),
    percentage(percentage), checkNum(check) {}
   Position(float x, float y, bool percentage, bool check);
   Position(float x, float y);
   Position(const Position & point) { *this = point; wrap = false; }

   // getters
   float getX()       const { return (percentage) ? x / xMax : x; }
   float getY()       const { return (percentage) ? y / yMax : y; }
   bool  getCheck()   const { return checkNum;       }
   bool  isDead()     const { return dead;           }
   float getXMin()    const { return xMin;           }
   float getXMax()    const { return xMax;           }
   float getYMin()    const { return yMin;           }
   float getYMax()    const { return yMax;           }
   //I put this into the point class.
   bool  getWrap()    const { return wrap;           }

   // setters
   void setX(float x);
   void setY(float y);
   void setPercent(bool p)  { percentage = p;        }
   void addX(float dx)      { setX(getX() + dx);     }
   void addY(float dy)      { setY(getY() + dy);     }
   void setCheck(bool f)    { checkNum = f;          }
   const Position & operator = (const Position & rhs);
   //I added this function.
   void setWrap(bool w)            { wrap = w;         }
   void setPoint(float x, float y) { setX(x); setY(y); }
   //This is where it was changed.
   //wrap around!
   void wrapAround();
   void addXY(float x, float y);

private:
   float x;           // horizontal position
   float y;           // vertical position
   bool  checkNum;    // do bounds checking
   bool  dead;        // have we exceed our bounds?
   static float xMin; // minimum extent of the x position
   static float xMax; // maximum extent of the x position
   static float yMin; // minimum extent of the y position
   static float yMax; // maximum extent of the y position
   bool wrap;         // do we wrap around? Added this variable also!
   bool percentage;   // Do we want the return value of x and y to be a percentage to the window size?
};

// stream I/O useful for debugging
std::ostream & operator << (std::ostream & out, const Position & pt);
std::istream & operator >> (std::istream & in,        Position & pt);

#define deg2rad(value) ((M_PI / 180) * (value))

#endif // POINT_H
