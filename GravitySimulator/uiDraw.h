#ifndef UI_DRAW_H
#define UI_DRAW_H

#include <string>     // To display text on the screen
#include <cmath>      // for M_PI, sin() and cos()
#include "point.h"    // Where things are drawn
using std::string;

/************************************************************************
 * DRAW DIGIT
 * Draw a single digit in the old school line drawing style.  The
 * size of the glyph is 8x11 or x+(0..7), y+(0..10)
 *************************************************************************/
//void drawDigit(const Position & topLeft, char digit);

/*************************************************************************
 * DRAW NUMBER
 * Display an positive integer on the screen using the 7-segment method
 *************************************************************************/
//void drawNumber(const Position & topLeft, unsigned int number);

/*************************************************************************
 * DRAW TEXT
 * Draw text using a simple bitmap font
 ************************************************************************/
//void drawText(const Position & topLeft, const char * text);

/************************************************************************
 * ROTATE
 * Rotate a given point (point) around a given origin (center) by a given
 * number of degrees (angle).
 *************************************************************************/
void rotate(Position & point, const Position & origin, int rotation);

/************************************************************************
 * DRAW RECTANGLE
 * Draw a rectangle on the screen centered on a given point (center) of
 * a given size (width, height), and at a given orientation (rotation)
 * measured in degrees (0 - 360)
 *************************************************************************/
void drawRect(const Position & center, char width, char height, int rotation);

/************************************************************************
 * DRAW CIRCLE
 * Draw a circle from a given location (center) of a given size (radius).
 *************************************************************************/
void drawCircle(const Position & center, int radius, int points, int rotation);

/******************************************************************
 * drawArrow
 *  This will draw an arrow. This will help indicate the direction
 *      and magnitude of the vector.
 *****************************************************************/
void drawArrow(const Position & center, float dx, float dy, int angle);

/*****************************************************************
 * drawBrackets
 *  This will allow the user to know that the object has been
 *      selected by the user.
 ****************************************************************/
void drawBrackets(const Position & center, int radius);

/************************************************************************
 * DRAW LINE
 * Draw a line on the screen from the beginning to the end.
 *************************************************************************/
void drawLine(const Position & begin, const Position & end);

/************************************************************************
 * DRAW DOT
 * Draw a single point on the screen, 2 pixels by 2 pixels
 *************************************************************************/
void drawDot(const Position & point);

/************************************************************************
 * DRAW Ship
 * Draw the spaceship on the screen
 *************************************************************************/
void drawShip(const Position & point, int rotation);

/******************************************************************
 * RANDOM
 * This function generates a random number.  The user specifies
 * The parameters 
 *    INPUT:   min, max : The number of values (min <= num <= max)
 *    OUTPUT   <return> : Return the integer
 ****************************************************************/
int    random(int    min, int    max);
double random(double min, double max);

//draw text but with color!
//void drawTextColor(const Position & topLeft, const char * text);
void drawCoolShip(const Position & center, int rotation);
void drawBigShip(const Position & center, int rotation);
void drawLesserShip(const Position & center, int rotation);

#endif // UI_DRAW_H
