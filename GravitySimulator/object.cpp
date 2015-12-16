/***************************************************
* Program:
*   object.h
* Author:
*   Samuel Hibbard
* Summary:
*   This will define the object methods.
***************************************************/

#include "object.h"
#include "uiDraw.h"
using namespace std;

/***********************************************************
 ************************* Object **************************
 **********************************************************/

/*********************************
 * move
 *  This will add the vector to the
 *      point.
 ********************************/
void Object::move()
{
    // Move the object
    vector.changePosition();
    return;
}

/*********************************
 * enableWrapping
 *  Enable wrapping.
 ********************************/
void Object::enableWrapping(bool enable)
{
    vector.setWrap(enable);
}

/*********************************
 * showBracketsForArrow
 *  Show the vector that is selected.
 ********************************/
void Object::showBracketsForVector(int id)
{
    bracketsForArrow = id;
}

/***********************************************************
 ************************* Planet **************************
 **********************************************************/

/*********************************
 * draw
 *  Draw the planet.
 ********************************/
void Planet::draw()
{
    // Rotate the planet
//    getVector().rotate(rotationSpeed);
    
    // Draw the planet!
    drawCircle(getPoint(), drawRadius, 20, rotationSpeed);
    
    // Show the brackets if needed
    if (brackets)
    {
        drawBrackets(getPoint(), drawRadius);
    }
    
    // Also the arrows if there are vectors
    if (arrows)
    {
        getVector().drawArrows(getBracketsForArrow());
    }
    
    return;
}

/***********************************************************
 ************************** Ship ***************************
 **********************************************************/

/*********************************
 * draw
 *  Draw the ship.
 ********************************/
void Ship::draw()
{
    // Draw the ship!
    drawShip(getPoint(), 0);
    return;
}

