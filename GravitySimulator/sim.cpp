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
#include <stdexcept>
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

// Set the identifier
int Object::identifier = 1;

/********************************
 * Constructor
 *******************************/
Simulator::Simulator()
{
    // Lets create two objects!
//    list<Object *> objects;
    
//    objects.push_back(new Planet(200, 0, random(-5, 5), random(-5, 5), 5000, 20, 5));
//    objects.push_back(new Planet(-200, 0, random(-10, 10), random(-10, 10), 500, 10, -10));
//    objects.push_back(new Planet(-75, 0, 0, -1.2, EARTH, 30, 30, 5, "Earth1"));
//    objects.push_back(new Planet(75, 0, 0, 1.2, EARTH, 30, 30, 5, "Earth2"));
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
    // Then deselect all planets
    for (list<Object *> :: iterator it = objects.begin(); it != objects.end(); ++it)
    {
        (*it)->showHelpers(false);
    }
    
    // Add to the list
    objects.push_back(object);
}

/*************************************
 * editObject
 *  This will edit either the vector
 *      or planet.
 ************************************/
void Simulator::editObject(int id, string edit, double newValue)
{
    // Grab the object
    Object * obj = this->grabObject(id);
    
    // If it is null then we need to edit the vector
    if (obj == NULL)
    {
        // What are we editing?
        for (list<Object *> :: iterator it = objects.begin(); it != objects.end(); ++it)
        {
            if ((*it)->getVector().getAngle(id) != -1)
            {
                if (edit == string("radiusOrMag"))
                {
                    (*it)->getVector().setMag(id, newValue);
                }
                else
                {
                    (*it)->getVector().setAngle(id, newValue);
                }
            }
        }
    }
    else
    {
        // What are we editing?
        if (edit == string("radiusOrMag"))
        {
            obj->setSize(newValue);
            obj->setDrawSize(newValue / getMeter());
        }
        else
        {
            obj->setMass(newValue);
        }
    }
}

/*************************************
 * changeVector
 *  This will change the vector to the 
 *      new object.
 ************************************/
void Simulator::changeVector(int id, int newObjId)
{
    Object *obj;
    
    // Grab the current object with the vector
    // Copy it
    Vector v = grabVector(id, obj);
    float mag = v.getMag(id);
    float angle = v.getAngle(id);
    string name = v.getName(id);
    
    // Now delete it
    removeVector(id);
    
    // Now add it to the object
    grabObject(newObjId)->addVector(angle, mag, name, id);
}

/*************************************
 * addVector
 *  This will add a vector to the object
 *      with the objId.
 ************************************/
void Simulator::addVector(int objId, float mag, float angle, string name, int & id)
{
    // Grab the object and add the vector
    id = grabObject(objId)->addVector(angle, mag, name);
}

/*************************************
 * removeVector
 *  This will remove the vector from
 *      the object.
 ************************************/
void Simulator::removeVector(int vectorId)
{
    // Loop through the objects and remove the vector
    for (list<Object *> :: iterator it = objects.begin(); it != objects.end(); ++it)
    {
        if ((*it)->getVector().getAngle(vectorId) != -1)
        {
            (*it)->deleteVector(vectorId);
        }
    }
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
        // See if the arrow was clicked on
        if (!clicked)
        {
            clicked = (*it)->getVector().clicked(x, y, id);
            
            // If true then don't show the brackets
            if (clicked)
            {
                (*it)->showHelpers(false);
            }
        }
       
        // See if object was clicked
        if (!clicked)
        {
            // Grab the distance between them
            float xDist = x - (*it)->getPoint().getX();
            float yDist = y - (*it)->getPoint().getY();
            
            float dist = sqrtf((xDist * xDist) + (yDist * yDist));
            
            // Now see if that is within the radius
            if (dist < (*it)->getDrawSize())
            {
                // Make clicked equal true
                clicked = true;
                
                // Take away the helpers for the other object
                if (id != -1)
                {
                    Object * obj = this->grabObject(id);
                    
                    // See if it is null. If so then it was a vector
                    // that was clicked on. So no need to turn off brackets
                    if (obj != NULL)
                    {
                        obj->showHelpers(false);
                    }
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
 * grabVector
 *  This will grab the vector with
 *      the id.
 ***********************************/
Vector Simulator::grabVector(int id, Object * &obj)
{
    Vector vector;
    for (list<Object *> :: iterator it = objects.begin(); it != objects.end(); ++it)
    {
        // See if we can grab an angle
        int angle = (*it)->getVector().getAngle(id);
        
        if (angle != -1)
        {
            vector = (*it)->getVector();
            obj = *it;
        }
    }
    
    return vector;
}

/***********************************
 * editingVector
 *  This will tell the GravityController
 *      to update the form if it is a
 *      vector
 ***********************************/
bool Simulator::editingVector(int id)
{
    bool isVector = false;
    
    // See if there is a vector
    Object *o;
    Vector v = grabVector(id, o);
    
    // Now see if it is empty
    if (v.getAngle(id) != -1)
    {
        isVector = true;
    }
    
    return isVector;
}

/***********************************
 * moveObject
 *  This will move the object if being
 *      dragged by the user.
 **********************************/
void Simulator::moveObject(float x, float y, int id)
{
    // Find the object to move
    // See if it is a planet
    Object * obj = this->grabObject(id);
    
    // If not then we need to move a vector
    if (obj == NULL)
    {
        for (list<Object *> :: iterator it = objects.begin(); it != objects.end(); ++it)
        {
            int angle = (*it)->getVector().getAngle(id);
            
            // See if we got something
            if (angle != -1)
            {
                // Grab distance of x and y from center point
                float cx = (*it)->getPoint().getX();
                float cy = (*it)->getPoint().getY();
                float xDist = x - cx;
                float yDist = y - cy;
                
                // Now find the newMag
                float newMag = sqrtf((xDist * xDist) + (yDist * yDist)) / 20;
                
                // Find the new angle based off of the x and y
                int newAngle = rad2deg(atan(yDist / xDist));
                
                // See if we need to adjust the angle
                if (x < cx && (y > cy || y < cy))
                {
                    newAngle += 180;
                }
                else if (x > cx && y < cy)
                {
                    newAngle += 360;
                }
                
                // Now save it!
                (*it)->getVector().setAngle(id, newAngle);
                (*it)->getVector().setMag(id, newMag);
            }
        }
    }
    else
    {
        obj->getVector().setPosition(x, y);
    }
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
            double d =  sqrt((xDistance * xDistance) + (yDistance * yDistance)) * getMeter();
            
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
            double a1 = (f / (*obj1)->getMass()) / getMeter();
            double a2 = (f / (*obj2)->getMass()) / getMeter();
            
            //            cout << "a1 = " << a1 << endl;
            //            cout << "a2 = " << a2 << endl;
            
            // Now convert it back to dx and dy
            // Do the first object
            (*obj1)->getVector().addVector(a1 * cos(angle), a1 * sin(angle));
            
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
            (*obj2)->getVector().addVector(a2 * cos(angle), a2 * sin(angle));
            
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