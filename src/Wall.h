#ifndef WALL_H
#define WALL_H

#include <vector>
#include "Vector2D.h"
#include "Rectangle.h"
#include "Entrance.h"

class Arena2D;

//Object limiting movement within the arena
class Wall : public Rectangle {

    private:
    // List of entrances
    std::vector<Entrance> ents;
    Arena2D* arena;

    /**
     * @brief Create non overlapping entrances on the wall 
     * 
     * @param nb_ent number of entrances
     * @param length_e length of entrances
     */
    void BuildEntrances(const int& nb_ent, const double& length_e);

    public:
    //Constructor
    /**
     * @brief Construct a new Wall object using 4 points
     * 
     * @param c1 point one
     * @param c2 point two
     * @param c3 point three
     * @param c4 point four
     * @param nb_ent number of entrances
     * @param arena 
     */
    Wall(const Vector2d<double>& c1, const Vector2d<double>& c2, const Vector2d<double>& c3, const Vector2d<double>& c4, int nb_ent, Arena2D* arena = nullptr);

    /**
     * @brief Construct a new Wall object using a starting point, a length and a width
     * 
     * @param p a starting point
     * @param length length of the wall
     * @param width width of the wall
     * @param nb_ent number of entrances
     * @param arena
     */
    Wall(const Vector2d<double>& p, const double& length, const double& width, int nb_ent, Arena2D* arena = nullptr);

    /**
     * @brief Get the Entrances 
     * 
     * @return std::vector<Entrance> list of entrances
     */
    std::vector<Entrance> GetEntrances() const;

    /**
     * @brief Get the number of entrances in wall
     * 
     * @return int number of entrances
     */
    int GetNbEnts() const;


};

#endif