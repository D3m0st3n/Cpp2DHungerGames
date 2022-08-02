#ifndef RECTANGLE_H 
#define RECTANGLE_H

#include <vector>

#include "Vector2D.h"

class Rectangle{


    private:

    protected:
    Vector2d<double> coord[4];

    public:
    //Constructor
    /**
     * @brief Construct a new rectangle object using 4 points
     * 
     * @param c1 point one
     * @param c2 point two
     * @param c3 point three
     * @param c4 point four
     */
    Rectangle(const Vector2d<double>& c1, const Vector2d<double>& c2, const Vector2d<double>& c3, const Vector2d<double>& c4);

    // TODO : ADD ORIENTATION PARAMETER TO CREATE TILTED RECT
    /**
     * @brief Construct a new rectangle object using a starting point, a length and a width
     * 
     * @param p a starting point
     * @param length length of the rectangle
     * @param width width of the rectangle
     */
    Rectangle(const Vector2d<double>& p, const double& length, const double& width);

    //Getters
    /**
     * @brief Get the Coord object
     * 
     * @return std::vector< Vector2d<double> > vector of coordinates
     */
    // std::vector< Vector2d<double> > GetCoord_();

    /**
     * @brief Get the coordinates of the rectangle
     * 
     * @return Vector2d<double> vector of coordinates
     */
    std::vector<Vector2d<double> > GetCoord() const;

    /**
     * @brief Get the number of sides of rectangles
     * 
     * @return int number of sides
     */
    int GetNbSides() const;

    /**
     * @brief Get the Length object
     * 
     * @return double length EuclNorm(c2 - c1)
     */
    double GetLength() const;

    /**
     * @brief Get the Width object
     * 
     * @return double width EuclNorm(c4 - c1)
     */
    double GetWidth() const;

    /**
     * @brief Get the normalized length vector
     * 
     * @return Vector2d<double> coord2 - coord1
     */
    Vector2d<double> GetLengthVec() const;

    /**
     * @brief Get the normalized width vector
     * 
     * @return Vector2d<double> coord4 - coord1
     */
    Vector2d<double> GetWidthVec() const;

    /**
     * @brief Get the rectangle center
     * 
     * @return Vector2d<double> center coordinate
     */
    Vector2d<double> GetCenter() const;

    /**
     * @brief Point in Bounding Box
     * 
     * @param point 
     * @return true if point in boudning box
     * @return false if point not in bounding box
     */
    bool PointInBB(const Vector2d<double>& point);
    bool PointInBB(const double& x, const double& y);
   
    /**
     * @brief If point in BB, tell if point is inside rectangle using WNA
     * Winding number algorithm in two directions to see if a point is inside or not
     * 
     * @param point 
     * @return true if point is in rectangle
     * @return false if point not in rectangle
     */
    bool PointIsInside(const Vector2d<double>& point);
    bool PointIsInside(const double& x, const double& y);
};

#endif