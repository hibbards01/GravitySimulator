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

#define drawMeter 100

/**********************************
 * SaveOrigin
 *  This will save the original
 *      positions and vectors when
 *      the simulation is run so that
 *      the user can reset it.
 *********************************/
class SaveOrigin
{
public:
    //
    // Constructors
    //
    SaveOrigin() {}
    
    //
    // GETTERS
    //
    Position & getPosition(int id) { return positions[id]; }
    Vector & getVector(int id)     { return vectors[id];   }
    
    //
    // Methods
    //
    void addOrigin(Position pt, Vector & v, int id)
    {
        positions[id] = pt;
        vectors[id] = v;
    }
    void clear()
    {
        positions.clear();
    }
private:
    std::map<int, Position> positions; // This will save all the original positions
    std::map<int, Vector> vectors;    // Save the vector
};


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
    void removeAll()                                            { objects.clear();        }
    bool clickedObject(float x, float y, int & id);
    void moveObject(float x, float y, int id);
    Object * grabObject(int id);                                // This will grab the object
    Vector grabVector(int id, Object * &obj);
    void editObject(int id, std::string edit, double newValue); // Edit the vector or object
    void changeVector(int id, int newObjId);                    // Edit the vector
    bool editingVector(int id);                                 // Are we editing a vector?
    void enableHelpers(bool enable);
    void enableWrapping(bool enable);
    void reset();
    void deselectObjects(int id);
    void selectObject(int id);
    
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
    static double getMeter()     { return meters[indexMeters]; }
    static double getDrawMeter() { return drawMeter;           }
    static void setMeter(int i)  { indexMeters = i;            }
private:
    //
    // Constructors
    //
    Simulator();
    Simulator(std::list<Object *> & objects) : objects(objects), firstTime(true) {}
    static Simulator * sim; // This creates our singleton.
    
    // Private methods
    void move();
    void draw();
    void calculateAccerlation();         // This will calculate the force for all the objects
    
    // Member variables
    std::list<Object *> objects;         // This will hold all the objects.
    static double gravitationalConstant; // This will hold the gravitational constant
    static int indexMeters;              // This is set by gravity to 1 for METERS4, unless it is changed
    static double meters[4];             // This will hold the values of meters that will be used
    bool firstTime;                      // First time running the simulation?
    SaveOrigin origin;                   // Save the original positions, dxs, and dys
};

#endif // sim_h
