/***************************************************
* Program:
*   vector.h
* Author:
*   Samuel Hibbard
* Summary:
*   This will hold the vector class.
***************************************************/

#ifndef vector_h
#define vector_h

#include "point.h"
#include <map>
#include <string>
#include <stdexcept>

/***************************
 * Vector
 *  This will help the 
 *      objects to move where
 *      they need to.
 **************************/
class Vector
{
public:
    //
    // Constructor
    //
    Vector() : dx(0.0), dy(0.0), angles(), position(), mags() {}
    Vector(float x, float y, float dx, float dy) : position(x, y), dx(dx), dy(dy), angles(), mags() {}
    Vector(float x, float y, float dx, float dy, float a) : position(x, y), dx(dx), dy(dy), angles(), mags() {}
    Vector(const Vector & v);
    
    //
    // Methods
    //
    void changePosition();                                          // This will change the point
    void addVector(const float mag, const int angle, const int id, const std::string name); // Add another vector
    void addVector(const float x, const float y);                   // Add the dx and dy
    void deleteVector(const int id);                                // Remove a vector
    Vector & operator = (const Vector & v);                         // Assingment operator
    void drawArrows(int id);                                        // Draw the arrows
    bool clicked(float x, float y, int & id);                       // See if any of the arrows was clicked on
//    void rotate(int rotate)                  { angle += rotate; }
    void combineVectors();                                          // This will combine the vectors if runned
                                                                    // not the first time.
    
    //
    // Getters
    //
    float getDx()               const { return dx;           }
    float getDy()               const { return dy;           }
    Position getPoint()         const { return position;     }
    int getAngle(int id) const
    {
        int angle;
        
        try
        {
            angle = angles.at(id);
        }
        catch(const std::out_of_range & oos)
        {
            angle = -1;
        }
        
        return angle;
    }
    float getMag(int id) const
    {
        float mag;
        
        try
        {
            mag = mags.at(id);
        }
        catch (const std::out_of_range & oos)
        {
            mag = -1;
        }
        
        return mag;
    }
    std::string getName(int id) const
    {
        std::string name;
        
        try
        {
            name = names.at(id);
        }
        catch (const std::out_of_range & oos)
        {
            name = "none";
        }
        
        return name;
    }
    
    //
    // Setters
    //
    void setDx(float dx)                 { this->dx = dx;          }
    void setDy(float dy)                 { this->dy = dy;          }
    void setPosition(Position & pt)      { this->position = pt;    }
    void setPosition(float x, float y)
    {
        position.setX(x);
        position.setY(y);
    }
    void setWrap(bool wrap)                        { position.setWrap(wrap); }
    void insertAngle(std::pair<int, int> a)        { angles.insert(a);       }
    void insertMag(std::pair<int, int> m)          { mags.insert(m);         }
    void insertName(std::pair<int, std::string> n) { names.insert(n);        }
    void setMag(int id, float mag);
    void setAngle(int id, int angle);
private:
    float dx;                             // The direction for the object in the x
    float dy;                             // Same thing as dx but for the y
    Position position;                    // The position of the object
    std::map<int, int> angles;            // The angle of the vectors
    std::map<int, float> mags;            // The magnitude of the vector
    std::map<int, std::string> names;     // The names of the vector
    
    void minusDxDy(int id);               // This will minus the dx and dy
    void addDxDy(float mag, float angle); // This will add to dx and dy
};

#endif /* vector_h */
