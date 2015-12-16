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

#define rad2deg(value) ((180 / M_PI) * (value))

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
    this->names = v.names;
    
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
    // Add to dx and dy
    addDxDy(mag, angle);
    
    // Add them to the maps
    this->angles[id] = angle;
    this->mags[id] = mag;
    this->names[id] = name;
    
    return;
}

/*********************************
 * deleteVector
 *  Delete from the vector.
 ********************************/
void Vector::deleteVector(int id)
{
    // Delete from the dx and dy
    minusDxDy(id);
    
    // Erase from the maps
    mags.erase(id);
    angles.erase(id);
    
    return;
}

/*********************************
 * addDxDy
 *  This will add to the dx and dy.
 *********************************/
void Vector::addDxDy(float mag, float angle)
{
    // Calculate x and y
    float a = deg2rad(angle);
    float x = mag * cos(a);
    float y = mag * sin(a);
    
    // Now add the x and y to the values dx and dy
    dx += x;
    dy += y;
}

/*********************************
 * minusDxDy
 *  This will minus to the dx and dy.
 *********************************/
void Vector::minusDxDy(int id)
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
}

/*********************************
 * setMag
 *********************************/
void Vector::setMag(int id, float mag)
{
    // Minus the dx and dy
    minusDxDy(id);
    
    // Now add to it again
    addDxDy(mag, angles[id]);
    
    // Set the value
    mags[id] = mag;
}

/*********************************
 * setAngle
 *********************************/
void Vector::setAngle(int id, int angle)
{
    // Minus dx and dy
    minusDxDy(id);
    
    // Add it again
    addDxDy(mags[id], angle);
    
    // Set the value
    angles[id] = angle;
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

/********************************
 * combineVectors
 *  This will combine the vectors
 *      if the game is passed and
 *      that they don't reset the 
 *      values.
 *******************************/
void Vector::combineVectors()
{
    // Loop through all the vectors
    // and combine them. Use the first key as the id
    if (!names.empty())
    {
        map<int, string> :: iterator it = names.begin();
        
        int id = it->first;
        string newName = it->second;
        
        // Grab all the names and combine them
        // Only do this if the size is greater
        if (names.size() > 1)
        {
            // Iterate once
            ++it;
            
            for (; it != names.end(); ++it)
            {
                newName = newName + "&" + it->second;
            }
        }
        
        // Clear all the lists
        names.clear();
        mags.clear();
        angles.clear();
        
        // Now save it
        names[id] = newName;
        
        // Also save the new angle and magnitude
        float degrees = rad2deg(atan(dy / dx));
        
        // Adjust the angle
        if ((dy < 0 && dx < 0) || (dy > 0 && dx < 0))
        {
            degrees += 180;
        }
        else if (dy < 0 && dx > 0)
        {
            degrees += 360;
        }
        
        angles[id] = degrees;
        mags[id] = sqrt((dx * dx) + (dy * dy));
    }
}