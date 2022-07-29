#ifndef ARENA2D_H
#define ARENA2D_H

#include "Vector2D.h"
#include "Wall.h"
#include "Food.h"
#include <iostream>

class Arena2D {
    //2D Arena class
    
    public:
    //Array of flies has to be a pointer to declare size

    //Array of walls has to be a pointer to declare size in constructor

    //Constructor
    /**
     * @brief Construct a new Arena 2D object
     * Arena 2D is always a circular arena composed of walls evenly spaced within it.
     * 
     * @param c coordinate of center of the arena
     * @param r radius of the arena
     * @param nb_walls number of walls
     * @param w_width wall width
     */
    Arena2D(const Vector2d<double>& c, const double& r, int nb_walls = 0, const int& nb_ent = 2, const double& w_width = 0);
    /**
     * @brief Construct a new Arena 2D object
     * 
     * @param c1 x coordinate of center
     * @param c2 y coordinate of center
     * @param r radius of the arena
     * @param nb_walls number of walls 
     * @param w_width wall width
     */
    Arena2D(const double& c1, const double& c2, const double& r, int nb_walls = 0, const int& nb_ent = 2, const double& w_width = 0);

    // Destructor for pointers


    // Others
    /**
     * @brief Get the Room From Position object
     * 
     * @param point 
     * @return int room corresponding to position
     */
    int GetRoomFromPosition(const Vector2d<double>& point);
    int GetRoomFromPosition(const double& x, const double& y);

    /**
     * @brief Indicate if move a to b is legal in arena
     * 
     * @param a starting point 
     * @param b ending point
     * @return true move is legal, does not cross wall, not outside arena or going through real entrance to next room
     * @return false outside arena, through wall, going through fake entrance to next room
     */
    bool AllowMove(const Vector2d<double>& a, const Vector2d<double>& b);

    //Getters
    /**
     * @brief Get the Center object
     * 
     * @return Vector2d<double> center coordinates
     */
    Vector2d<double> GetCenter() const;

    /**
     * @brief Get the Radius object
     * 
     * @return double radius
     */
    double GetRadius() const;

    /**
     * @brief Get the number of walls, equivalent to getting the number of rooms
     * 
     * @return int number of walls
     */
    int GetNbWalls() const;
    
    /**
     * @brief Get the list of walls in the arena
     * 
     * @return std::vector<Wall> vector of walls
     */
    std::vector<Wall> GetWalls() const;

    /**
     * @brief Get the vector of room center
     * 
     * @return std::vector<Vector2d<double> > list of room center
     */
    std::vector<Vector2d<double> > GetRoomCenter() const;
    /**
     * @brief Get the center of room based on index
     * 
     * @param room 
     * @return Vector2d<double> room center of interest
     */
    Vector2d<double> GetRoomCenter(const int& room) const;

    /**
     * @brief Get food of arena
     * 
     * @return Food* 
     */
    Food* GetFood();

    /**
     * @brief Get if arena has a food object associated with
     * 
     * @return true it has a food ptr
     * @return false it has not
     */
    bool GetFoodbool() const;


    /**
     * @brief Set the Food object
     * 
     * @param food 
     */
    void SetFood(Food* food);

    /**
     * @brief Set food in room
     * 
     * @param room room 
     * @return true 
     * @return false 
     */
    bool SetFoodRoom(const int& room);

    /**
     * @brief check if position is in same room as food
     * 
     * @param room 
     * @return true position is in same room
     * @return false position is not in same room/ food is nullptr
     */
    bool OnFood(const int& room);
        

    private:
    //Attributes
    //Radius of arena
    double radius;
    //Center coordinates
    Vector2d<double> center;
    //List of walls 
    std::vector<Wall> walls;
    // Lists of angles
    std::vector<double> walls_cos;
    std::vector<double> walls_sin;
    // Food object
    Food* food;

    //Methods
    /**
     * @brief Build evenly spaced number of walls within the arena to create rooms
     * 
     * @param nb_walls number of walls
     * @param w_width wall width
     */
    void BuildWalls(int nb_walls = 0, const int& nb_ent = 2,  const double& w_width = 0);




};

#endif