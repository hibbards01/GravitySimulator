/*************************************************************
* Program:
*   objects.h
* Author:
*   Samuel Hibbard
* Summary:
*   This will contain the class Objects. Also it will include
*     all the other classes that inherit from Objects.
*************************************************************/

#include "vector.h"
#include <string>

static int identifier = 1;

/**********************************
 * Objects
 *  This will contain all the base
 *    variables for all the objects
 *********************************/
class Object
{
public:
    //
    // Constructors
    //
    Object() : vector(), mass(0.0) {}
    Object(float x, float y, float dx, float dy, double m, std::string n) : vector(x, y, dx, dy),
    mass(m), name(n)
    {
        id = identifier++;
    }
    
    //
    // Methods
    //
    virtual void move();         // Virtual function
    virtual void draw() = 0;     // Pure virtual function
    void addVectors(Vector & v); // Add two vectors together
    
    //
    // Getters
    //
    Vector getVector()   const { return vector;            }
    float getMass()      const { return mass;              }
    Position getPoint()  const { return vector.getPoint(); }
    Vector & getVector()       { return vector;            }
    int getId()          const { return id;                }
    
    //
    // Setters
    //
    void setVector(Vector & v) { vector = v;           }
    void setMass(float m)      { mass = m;             }
    void setWrap(bool wrap)    { vector.setWrap(wrap); }
private:
    Vector vector;    // This will allow the object to move!
    double mass;      // This will hold the mass of the object!
    int id;           // This will help identify it!
    std::string name; // This is the name of the object.
};

/*********************************
 * Planet
 *  This will hold the values for
 *      for a given planet.
 ********************************/
class Planet : public Object
{
public:
    //
    // Constructors
    //
    Planet() : Object(), radius(0), rotationSpeed(0) {}
    Planet(float x, float y, float dx, float dy, double m, int r, int s, std::string n) : radius(r), Object(x, y, dx, dy, m, n), rotationSpeed(s) {}
    
    //
    // Methods
    //
    void draw();
    void rotate();
    
    //
    // Setters
    //
    void setRotationSpeed(int s) { rotationSpeed = s; }
private:
    int radius;        // This is the radius of the planet.
    int rotationSpeed; // This will rotate the planet.
};

/*********************************
 * Ship
 *  This will hold the values for
 *      for a given ship.
 ********************************/
class Ship : public Object
{
public:
    //
    // Constructors
    //
    Ship(float x, float y, float dx, float dy, double m, int r, std::string n) : Object(x, y, dx, dy, m, n) {}
    
    //
    // Methods
    //
    void draw();
private:
};
