#ifndef FOOD_H
#define FOOD_H

class Arena2D;

class Food{

    public :
    /**
     * @brief Construct a new Food object
     * 
     * @param arena arena object it belongs to
     * @param room position of food in arena
     * @param max_lifetime time spent in each room
     */
    Food(Arena2D* arena, const int& room, const double& max_lifetime);

    Food(Food* food);

    /**
     * @brief Get the room 
     * 
     * @return int room, position of food ion arena
     */
    int GetRoom() const;

    /**
     * @brief Set the room
     * 
     * @param room 
     */
    bool SetRoom(const int& room);

    /**
     * @brief update food
     * Move food everytime it reaches its max_lifetime
     * 
     * @param  dt timestep of simulation
     */
    void Update(const double& dt);
    /**
     * @brief Get the Arena object
     * 
     * @return Arena2D* in which Food is in
     */
    Arena2D* GetArena();

    /**
     * @brief Get the Max Lifetime object
     * 
     * @return double lifetime before switching room
     */
    double GetMaxLifetime() const;

    /**
     * @brief Get the Lifetime object
     * 
     * @return double current time spent in room
     */
    double GetLifetime() const;

    private :
    // Arena
    Arena2D* arena;
    // Location of food in arena
    int room;
    // Max Lifetime
    double max_lifetime;
    // Lifetime
    double lifetime;
    };

#endif