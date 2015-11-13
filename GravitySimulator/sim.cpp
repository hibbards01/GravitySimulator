/**************************************************************
* Program
*  sim.cpp
* Author:
*  Samuel Hibbard
* Summary:
*  This will define all the methods for the class Simulator
*************************************************************/

#include "sim.h"
#include <openGL/gl.h>    // Main OpenGL library
#include <math.h>
using namespace std;

// Set the gravitational constant
double Simulator::gravitationalConstant = .0000000000667;
int Simulator::indexMeters = 0;

// Set some #defines
#define EARTH (5.98 * pow(10, 24))
#define MOON  (7.34 * pow(10, 22))
#define JUPITER (1.89813 * pow(10, 27))
#define deg2rad(value) ((M_PI / 180) * (value))
#define PI 3.14159265
#define rad2deg(value) (value * 180 / PI)

// Make the instance null
Simulator * Simulator::sim = NULL;

/********************************
 * Constructor
 *******************************/
Simulator::Simulator()
{
    // Lets create two objects!
//    list<Object *> objects;
    
//    objects.push_back(new Planet(200, 0, random(-5, 5), random(-5, 5), 5000, 20, 5));
//    objects.push_back(new Planet(-200, 0, random(-10, 10), random(-10, 10), 500, 10, -10));
//    objects.push_back(new Planet(-75, 0, 0, -1.2, EARTH, 30, 5, "Earth1"));
//    objects.push_back(new Planet(75, 0, 0, 1.2, EARTH, 30, 5, "Earth2"));
//    objects.push_back(new Planet(0, 80, -2.3, 0, MOON, 10, -10));
//    objects.push_back(new Planet(0, 0, 0, 0, EARTH, 30, 5));
//    objects.push_back(new Planet(0, 0, 0, 0, JUPITER, 50, 0));
//    objects.push_back(new Planet(0, 250, 0.75, 0, EARTH, 8, 0));
//    objects.push_back(new Planet(0, 265, 0.905, 0, MOON, 2, 0));
    
    // Now create the gravity with the objects
}

/*************************************
 * getInstance
 *  Grab the instance of this class.
 *************************************/
Simulator * Simulator::getInstance()
{
    // Create only one instance of this class
    if (!sim)
    {
        sim = new Simulator();
    }
    
    return sim;
}

/*************************************
 * deleteInstance
 *  When the application exits.
 *************************************/
void Simulator::deleteInstance()
{
    delete sim;
}

/********************************
 * run
 *  This will run the Simulator
 *******************************/
void Simulator::run(bool movingObjects)
{
    // First move the objects.
    // Only move them if running the simulation
    if (!movingObjects)
    {
        move();
    }
    
    // Now draw them.
    draw();
    
    return;
}

/*************************************
 * addObject
 *  This will add the object and make
 *      it looked like it was selected.
 *      Anything that was selected will
 *      not be anymore.
 ************************************/
void Simulator::addObject(Object * object, int id)
{
    // See if this is the first one
    if (id != -1)
    {
        // Then deselect it
        this->grabObject(id)->showHelpers(false);
    }
    
    // Add to the list
    objects.push_back(object);
}

/*************************************
 * clickedObject
 *  This will check if the object
 *      was clicked on. It will fill
 *      the id number with the object
 *      that was clicked on.
 ************************************/
bool Simulator::clickedObject(float x, float y, int & id)
{
    bool clicked = false;
    
    // Now run through all the objects
    for (list<Object *> :: iterator it = objects.begin(); it != objects.end(); ++it)
    {
        if (!clicked)
        {
            // Grab the distance between them
            float xDist = x - (*it)->getPoint().getX();
            float yDist = y - (*it)->getPoint().getY();
            
            float dist = sqrtf((xDist * xDist) + (yDist * yDist));
            
            // Now see if that is within the radius
            if (dist < (*it)->getSize())
            {
                // Make clicked equal true
                clicked = true;
                
                // Take away the helpers for the other object
                if (id != -1)
                {
                    this->grabObject(id)->showHelpers(false);
                }
                
                // Grab the id!
                id = (*it)->getId();
                
                // Show the helpers for it!
                (*it)->showHelpers(true);
            }
        }
    }
    
    return clicked;
}

/***********************************
 * grabObject
 *  This will grab the object that
 *      has the given id.
 **********************************/
Object * Simulator::grabObject(int id)
{
    for (list<Object *> :: iterator it = objects.begin(); it != objects.end(); ++it)
    {
        if (id == (*it)->getId())
        {
            return *it;
        }
    }
    
    return NULL;
}

/***********************************
 * moveObject
 *  This will move the object if being
 *      dragged by the user.
 **********************************/
void Simulator::moveObject(float x, float y, int id)
{
    // Find the object to move
    this->grabObject(id)->getVector().setPosition(x, y);
}

/******************************
 * setWrap
 *  This will make the objects
 *      wrap.
 *****************************/
void Simulator::setWrap(bool wrap)
{
    // See if we will enable wrapping.
    if (wrap)
    {
        // Loop through all the objects and set to true
        for (list<Object *> :: iterator i = objects.begin(); i != objects.end(); ++i)
        {
            (*i)->setWrap(wrap);
        }
    }
    
    return;
}

/****************************************
 * cacluateAcceleration
 *  This will first calulate the force for
 *      all the objects and then calculate
 *      the acceleration those objects
 *      have on each other.
 ***************************************/
void Simulator::calculateAccerlation()
{
    // First calculate the force between each of the objects
    for (list<Object *> :: iterator obj1 = objects.begin(); obj1 != objects.end(); ++obj1)
    {
        // Make the secound for loop start one before the other object
        list<Object *> :: iterator obj2 = obj1;
        ++obj2;
        for (; obj2 != objects.end(); ++obj2)
        {
            // Find the displacement between the objects
            double xDistance = (*obj2)->getPoint().getX() - (*obj1)->getPoint().getX();
            double yDistance = (*obj2)->getPoint().getY() - (*obj1)->getPoint().getY();
            double d =  sqrt((xDistance * xDistance) + (yDistance * yDistance)) * METERS4;
            
            // Hurry and find their angle
            // This is in radians
            double angle = atan2(yDistance, xDistance);
            
            //            cout << "angle = " << angle << endl;
            //            cout << "mass = " << (*obj1)->getMass() << endl;
            //            cout << "Calculating\n";
            //            cout << xDistance << endl;
            //            cout << yDistance << endl;
            //            cout << rad2deg(angle) << endl;
            //            cout << "ending\n";
            //            cout << "Displacement = " << d << endl;
            
            
            // Now calculate the Force between the objects
            //       G * m1 * m2    G = Gravitational Constant N * m^2 / kg^2
            // F  = -------------   d = Distance in meters
            //           d^2        m1, m2 = kg
            double f = (gravitationalConstant * (*obj1)->getMass() * (*obj2)->getMass()) / (d * d);
            
            //            cout << "force = " << f << endl;
            
            // Now find the acceleration they have towards each other
            //      F
            // a = ---
            //      m
            double a1 = (f / (*obj1)->getMass()) / METERS4;
            double a2 = (f / (*obj2)->getMass()) / METERS4;
            
            //            cout << "a1 = " << a1 << endl;
            //            cout << "a2 = " << a2 << endl;
            
            // Now convert it back to dx and dy
            // Do the first object
            (*obj1)->getVector().addVectors(a1 * cos(angle), a1 * sin(angle));
            
            //            float dx = a1 * cos(angle);
            //            float dy = a1 * sin(angle);
            
            //            cout << "dx = " << dx << endl
            //            << "dy = " << dy << endl;
            
            // Check if we need to minus or plus 180 for the secound object
            if (angle < 0)
            {
                angle = PI + angle;
            }
            else
            {
                angle = angle - PI;
            }
            
            // Finally add the vectors
            (*obj2)->getVector().addVectors(a2 * cos(angle), a2 * sin(angle));
            
            //            dx = a2 * cos(angle);
            //            dy = a2 * sin(angle);
            //            cout << "dx1 = " << dx << endl
            //            << "dy1 = " << dy << endl;
        }
    }
    
    return;
}

/****************************
 * move
 *  This will first run all
 *      the calculations of
 *      the objects and will
 *      then move them.
 ***************************/
void Simulator::move()
{
    // Calculate gravity!
    calculateAccerlation();
    
    // Loop through all the objects and move them!
    for (list<Object *> :: iterator i = objects.begin(); i != objects.end(); ++i)
    {
        (*i)->move();
    }
    
    return;
}

/****************************
 * draw
 *  This will then draw the
 *      objects.
 ***************************/
void Simulator::draw()
{
    // Loop through all the objects
    for (list<Object *> :: iterator i = objects.begin(); i != objects.end(); ++i)
    {
        (*i)->draw();
    }
    
    return;
}