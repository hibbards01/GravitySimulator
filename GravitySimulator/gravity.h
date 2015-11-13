/***************************************************************
* Program:
*   gravity.h
* Author:
*   Samuel Hibbard
* Summary:
*   This will hold the class Gravity.
***************************************************************/

#include "object.h"
#include <list>

#define MILLMETERS 1000000
#define METERS5    100000
#define METERS4    10000
#define KILOMETERS 1000

/************************************
 * Gravity
 *  This will hold all the objects.
 *      It will be the one calculating
 *      what will happen to the given
 *      objects
 ***********************************/
class Gravity
{
public:
    //
    // Constructors
    //
    Gravity() {}
    Gravity(std::list<Object *> & objs);
    
    //
    // Methods
    //
    void move();
    void draw();
    void addObject(Object * obj)    { objects.push_back(obj); }
    void removeObject(Object * obj) { objects.remove(obj);    }
    bool hitObject(int x, int y, int & id);
    
    //
    // Getters
    //
    std::list<Object *> & getObjects() { return objects; }
    
    //
    // Setters
    //
    void setObjects(std::list<Object *> & objs) { objects = objs; }
    void setWrap(bool wrap);
    
    // Static functions
    static double getMeter()
    {
        double meter[4];
        meter[0] = METERS4;
        meter[1] = METERS5;
        meter[2] = MILLMETERS;
        meter[3] = KILOMETERS;
        
        return meter[indexMeters];
    }
    static void setMeter(int i) { indexMeters = i; }
private:
    void calculateAccerlation();         // This will calculate the force for all the objects
    std::list<Object *> objects;         // This will hold all the objects.
    static double gravitationalConstant; // This will hold the gravitational constant
    static int indexMeters;              // This is set by gravity to 1 for METERS4, unless it is changed.
};