/**************************************************************
* Program
*  sim.cpp
* Author:
*  Samuel Hibbard
* Summary:
*  This will define all the methods for the class Simulator
*************************************************************/

#include "sim.h"
#include "uiDraw.h"
using namespace std;

#define EARTH (5.98 * pow(10, 24))
#define MOON  (7.34 * pow(10, 22))
#define JUPITER (1.89813 * pow(10, 27))

// Make the instance null
Simulator * Simulator::sim = NULL;

/********************************
 * Constructor
 *******************************/
Simulator::Simulator()
{
    // Lets create two objects!
    list<Object *> objects;
    
//    objects.push_back(new Planet(200, 0, random(-5, 5), random(-5, 5), 5000, 20, 5));
//    objects.push_back(new Planet(-200, 0, random(-10, 10), random(-10, 10), 500, 10, -10));
//    objects.push_back(new Planet(-75, 0, 0, -1.2, EARTH, 30, 5));
//    objects.push_back(new Planet(75, 0, 0, 1.2, EARTH, 30, 5));
//    objects.push_back(new Planet(0, 80, -2.3, 0, MOON, 10, -10));
//    objects.push_back(new Planet(0, 0, 0, 0, EARTH, 30, 5));
//    objects.push_back(new Planet(0, 0, 0, 0, JUPITER, 50, 0));
//    objects.push_back(new Planet(0, 250, 0.75, 0, EARTH, 8, 0));
//    objects.push_back(new Planet(0, 265, 0.905, 0, MOON, 2, 0));
    
    // Now create the gravity with the objects
    gravity.setObjects(objects);
    gravity.setWrap(true);
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
void Simulator::deleteInstanc()
{
    delete sim;
}

/********************************
 * run
 *  This will run the Simulator
 *******************************/
void Simulator::run()
{
    // First move the objects.
    gravity.move();
    
    // Now draw them.
    gravity.draw();
    return;
}