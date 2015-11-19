/*************************************************************
* Program:
*   objects.h
* Author:
*   Samuel Hibbard
* Summary:
*   This will contain the class Objects. Also it will include
*     all the other classes that inherit from Objects.
*************************************************************/

#ifndef objects_h
#define objects_h

#include "vector.h"
#include <string>

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
    virtual void move();                       // Virtual function
    virtual void draw() = 0;                   // Pure virtual function
    void addVectors(Vector & v);               // Add two vectors together
    virtual void showHelpers(bool helper) = 0; // Show the helpers for the object?
    virtual void showVectors(bool vector) = 0; // When to show the vectors
    virtual double getSize() = 0;              // Get the size of the object
    virtual int getDrawSize() = 0;             // Get the draw size of the object
    int addVector(float angle, float mag, std::string name)
    {
        getVector().addVector(mag, angle, identifier, name);
        return identifier++;
    }
    void deleteVector(int id)   { getVector().deleteVector(id); }
    
    //
    // Getters
    //
    Vector getVector()    const { return vector;                }
    float getMass()       const { return mass;                  }
    Position getPoint()   const { return vector.getPoint();     }
    Vector & getVector()        { return vector;                }
    int getId()           const { return id;                    }
    std::string getName() const { return name;                  }

    //
    // Setters
    //
    void setVector(Vector & v) { vector = v;           }
    void setMass(float m)      { mass = m;             }
    void setWrap(bool wrap)    { vector.setWrap(wrap); }
private:
    Vector vector;         // This will allow the object to move!
    double mass;           // This will hold the mass of the object!
    int id;                // This will help identify it!
    std::string name;      // This is the name of the object.
    static int identifier; // This will add a special identifier
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
    Planet() : Object(), radius(0), rotationSpeed(0), brackets(false) {}
    Planet(float x, float y, float dx, float dy, double m, int drawR, double r, int s, std::string n) : radius(r), Object(x, y, dx, dy, m, n), rotationSpeed(s), brackets(true), drawRadius(drawR), arrows(true) {}
    
    //
    // Methods
    //
    void draw();
    void rotate();
    void showHelpers(bool helper) { brackets = helper; }
    void showVectors(bool vector) { arrows = vector;   }
    double getSize()              { return radius;     }
    int getDrawSize()             { return drawRadius; }
    void move()
    {
        // Make sure it can move
        if (!arrows && !brackets)
        {
            getVector().changePosition();
        }
    }
    
    //
    // Setters
    //
    void setRotationSpeed(int s) { rotationSpeed = s; }
private:
    double radius;      // This is the radius of the planet.
    int drawRadius;     // The draw radius for OpenGl.
    int rotationSpeed;  // This will rotate the planet.
    bool brackets;      // Do we draw brackets or not?
    bool arrows;        // Show the vectors?
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
    void showHelpers(bool helper) { brackets = helper; }
    void showVectors(bool vector) { /* Fill this when needed */ }
    double getSize()              { return 0;          }
    int getDrawSize()             { return 0;          }
private:
    bool brackets; // Show the brackets for the ship
};

#endif // objects_h