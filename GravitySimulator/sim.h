/***************************************************************
* Program:
*   sim.h
* Author:
*   Samuel Hibbard
* Summary:
*   This will hold the class Simulator. This will be designed
*       to be a SingleTon desgin.
***************************************************************/

#include "gravity.h"
#include <list>

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
    static void deleteInstanc();
    void run();
    void addObject(Object * object)    { gravity.addObject(object);    }
    void removeObject(Object * object) { gravity.removeObject(object); }
    
    //
    // Getters
    //
    Gravity & getGravity() { return gravity; }
private:
    //
    // Constructors
    //
    Simulator();
    Simulator(std::list<Object *> & objects) : gravity(objects) {}
    
    Gravity gravity;        // We need gravity!
    static Simulator * sim; // This creates our singleton.
};
