/***************************************************
* Program:
*   vector.cpp
* Author:
*   Samuel Hibbard
* Summary:
*   This will define the vector methods.
***************************************************/

#include "vector.h"
#include <math.h>
#include "uiDraw.h"
using namespace std;

/*********************************
 * Copy Constructor
 ********************************/
Vector::Vector(const Vector & v)
{
    // Use the assingment operator
    *this = v;
}

/*********************************
 * Operator =
 ********************************/
Vector & Vector::operator = (const Vector & v)
{
    // Assign all the values to this Vector
    this->dx = v.dx;
    this->dy = v.dy;
    this->position = v.position;
    this->angles = v.angles;
    this->mags = v.mags;
    
    // Finally return this
    return *this;
}

/*********************************
 * changePosition
 *  This will add the vector to 
 *      the point.
 ********************************/
void Vector::changePosition()
{
    // Add the vector to the position
    position.addXY(dx, dy);
    return;
}

/*********************************
 * addVectors
 *  This will add the vector to itself.
 ********************************/
void Vector::addVector(const float mag, const int angle, const int id, const string name)
{
    // Calculate x and y
    float a = deg2rad(angle);
    float x = mag * cos(a);
    float y = mag * sin(a);
    
    // Add them to the maps
    this->angles[id] = angle;
    this->mags[id] = mag;
    this->names[id] = name;

    // Now add the x and y to the values dx and dy
    dx += x;
    dy += y;
    
    return;
}

/*********************************
 * deleteVector
 *  Delete from the vector.
 ********************************/
void Vector::deleteVector(int id)
{
    // Grab the mag and angle
    float m = mags[id];
    float a = angles[id];
    
    // Calculate their individual x and y
    float x = m * cos(deg2rad(a));
    float y = m * sin(deg2rad(a));
    
    // Now minus it from dx and dy
    dx -= x;
    dy -= y;
    
    // Erase from the maps
    mags.erase(id);
    angles.erase(id);
    
    return;
}

/*********************************
 * addVectors
 *  This will add the vector to itself
 ********************************/
void Vector::addVector(const float x, const float y)
{
    // Add the vectors!
    this->dx += x;
    this->dy += y;
    
    return;
}

/*********************************
 * clicked
 *  See if the arrow was clicked.
 ********************************/
bool Vector::clicked(float x, float y, int & id)
{
    bool clicked = false;
    
    for (map<int, float> :: iterator it = mags.begin(); it != mags.end(); ++it)
    {
        // Grab the angle
        float angle = angles[it->first];
        
        // Now calculate dx and dy
        float dx = position.getX() + ((it->second * cos(deg2rad(angle))) * 20);
        float dy = position.getY() + ((it->second * sin(deg2rad(angle))) * 20);
        
        // Now calculate the distance
        // Grab the distance between them
        float xDist = x - dx;
        float yDist = y - dy;
        
        float dist = sqrtf((xDist * xDist) + (yDist * yDist));
        
        // Now see if the distance is less then the size
        if (dist < 9.5)
        {
            // Set the id
            id = it->first;
            
            // Now make clicked equal true
            clicked = true;
        }
    }
    
    return clicked;
}

/********************************
 * drawArrows
 *  This will draw the arrows when
 *      the planet is clicked upon.
 *******************************/
void Vector::drawArrows()
{
    // Draw all the arrows
    for (map<int, float> :: iterator it = mags.begin(); it != mags.end(); ++it)
    {
        // Grab the angle
        float angle = angles[it->first];
        
        // Now calculate dx and dy
        float dx = it->second * cos(deg2rad(angle));
        float dy = it->second * sin(deg2rad(angle));
        
        // Now draw it
        drawArrow(position, dx, dy, angle);
    }
}