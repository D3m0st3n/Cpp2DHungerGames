#ifndef ENTRANCE_H
#define ENTRANCE_H

#include "Vector2D.h"
#include "Rectangle.h"

// Forward declaration of interdependent class
class Wall;

class Entrance : public Rectangle{

    private:

    Wall* wall;
    bool isFake; 

    public:
    
    /**
     * @brief Construct a new Entrance object
     * 
     * @param c1 point one
     * @param c2 point two
     * @param c3 point three
     * @param c4 point four
     * @param isFake indicate if entrance is fake or not
     * @param wall pointer to associated wall
     */
    Entrance(const Vector2d<double>& c1, const Vector2d<double>& c2, const Vector2d<double>& c3, const Vector2d<double>& c4, const bool& isFake = false,  Wall* wall = nullptr);


    /**
     * @brief Construct a new Entrance object
     * 
     * @param p a starting point
     * @param length length of the rectangle
     * @param width width of the rectangle
     * @param isFake indicate if entrance is fake or not
     * @param wall pointer to associated wall
     */
    Entrance(const Vector2d<double>& p, const double& length, const double& width, const bool& isFake = false, Wall* wall = nullptr);

    /**
     * @brief return if entrance is real or not
     * 
     * @return true real entrance
     * @return false fake entrance
     */
    bool IsFake() const;

};


#endif