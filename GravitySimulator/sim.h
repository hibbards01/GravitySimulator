/***************************************************************
* Program:
*   sim.h
* Author:
*   Samuel Hibbard
* Summary:
*   This will hold the class Simulator. This will be designed
*       to be a SingleTon desgin. This will also keep track of
*       the gravity between objects.
***************************************************************/

#ifndef sim_h
#define sim_h

#include <list>
#include "object.h"
#include <string>

#define MILLMETERS 1000000
#define METERS5    100000
#define METERS4    10000
#define KILOMETERS 1000

/**********************************
 * Simulator
 *  This class will be the one that
 *      that will tell the objects
 *      when to do what.
 *********************************/
class Simulator
{
public:
    //
    // Methods
    //
    static Simulator * getInstance();
    static void deleteInstance();
    void run(bool movingObjects);
    void addObject(Object * object, int id);
    void addVector(int objId, float mag, float angle, std::string name, int & id);
    void removeObject(int id);
    void removeVector(int vectorId);
    bool clickedObject(float x, float y, int & id);
    void moveObject(float x, float y, int id);
    Object * grabObject(int id);                        // This will grab the object
    Vector grabVector(int id, Object * &obj);
    
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
    //
    // Constructors
    //
    Simulator();
    Simulator(std::list<Object *> & objects) : objects(objects) {}
    static Simulator * sim; // This creates our singleton.
    
    // Private methods
    void move();
    void draw();
    void calculateAccerlation();         // This will calculate the force for all the objects
    
    // Member variables
    std::list<Object *> objects;         // This will hold all the objects.
    static double gravitationalConstant; // This will hold the gravitational constant
    static int indexMeters;              // This is set by gravity to 1 for METERS4, unless it is changed
};

#endif // sim_h
