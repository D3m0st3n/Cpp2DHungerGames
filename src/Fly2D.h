#ifndef FLY2D_H
#define FLY2D_H

#include <iostream>

#include "Vector2D.h"
#include "Arena2D.h"

class Simulation2D;

class Fly2D {

    friend class Simulation2D;

    // 2D agent navigating inside the arena
    private:

    int room;
    // x, y position
    Vector2d<double> r;
    // velocity of agent
    Vector2d<double> v;
    // Velocity of preference
    Vector2d<double> v_pref;
    // Acceleration
    Vector2d<double> a;
    // orientation of agent
    double angle;
    // Cognition range
    double rcog;
    // index of agent in the simulation
    int index;
    // Time on food
    double timeonfood;
    // Access to arena
    Arena2D* arena;
    // Acces to simulation
    // Simulation2D* simulation;
    // Or provide to cvelocity table directly?
    // Forces applioed on agent, from ref paper
    Vector2d<double> Fint, Fres, Ffric, Fnoise; 
    // Point of aim
    Vector2d<double> aim;



    public:
    /**
     * @brief Construct a new Fly2D agent
     * 
     * @param position Vector2D starting position
     * @param index index of agent in list
     * @param arena arena in which agent is in
     */
    Fly2D(const Vector2d<double>& position, const int& index, Arena2D* arena = nullptr);

    /**
     * @brief Construct a new Fly2D
     * 
     * @param x x position
     * @param y y position
     * @param index index of agent in list
     * @param arena arena in which agent is in
     */
    Fly2D(const double& x, const double& y, const int& index, Arena2D* arena = nullptr);

    /**
     * @brief Construct a new Fly2D
     * 
     * @param room starting room, center of the room
     * @param index index of agent in list
     * @param arena arena in which agent is in
     */
    Fly2D(const int& room, const int& index, Arena2D* arena = nullptr);

    /**
     * @brief Get room of agent
     * 
     * @return int room
     */
    int GetRoom() const;

    /**
     * @brief Get the agent's position
     * 
     * @return Vector2d<double> position
     */
    Vector2d<double> GetPosition() const;

    /**
     * @brief Get the agent's velocity
     * 
     * @return Vector2d<double> velocity vector
     */
    Vector2d<double> GetVelocity() const;

    /**
     * @brief Get agent's prefered velocity
     * 
     * @return Vector2d<double> preferred velocity
     */
    Vector2d<double> GetVelocitypref() const;

    /**
     * @brief Get repsonse force, response to environment 
     * 
     * @return Vector2d<double> 
     */
    Vector2d<double> GetFres() const;

    /**
     * @brief Get agent's aim
     * 
     * @return Vector2d<double> aim
     */
    Vector2d<double> GetAim() const;

    /**
     * @brief Get the Angle object
     * 
     * @return double 
     */
    double GetAngle() const;

    /**
     * @brief Get the arena in which the fly
     * 
     * @return Arena2D* 
     */
    Arena2D* GetArena();

    /**
     * @brief Get the time spent on food by the agent
     * When the agent is in the same room as the food, time on food increases
     * 
     * @return double timeonfood
     */
    double GetTimeOnFood() const; 

    /**
     * @brief Set aiming point
     * 
     * @param point point of aim
     */
    void SetAim(const Vector2d<double>& point);
    
    /**
     * @brief Set aiming point
     * 
     * @param x coordinate
     * @param y coordinate
     */
    void SetAim(const double& x, const double& y);

    /**
     * @brief Update agent, updates each component of the agent
     * 
     * @param dt timestep
     */
    void Update(const double& dt);

    /**
     * @brief Update agent's angle
     * 
     */
    void UpdateAngle();

    /**
     * @brief Update forces
     * 
     */
    void UpdateForces();

    /**
     * @brief Updates response force
     * 
     */
    void UpdateFres();

    /**
     * @brief Updates interaction force
     * 
     */
    void UpdateFint();

    /**
     * @brief Updates friction force 
     * 
     */
    void UpdateFfric();

    /**
     * @brief Updates noise force
     * 
     */
    void UpdateFnoise();

    /**
     * @brief Updates room index 
     * 
     */
    void UpdateRoom();

    /**
     * @brief Updates preferred velocity
     * 
     * @param dt timestep
     */
    void UpdateVpref(const double& dt);
    /**
     * @brief Updates velocity
     * 
     * @param dt timestep 
     */
    void UpdateV(const double& dt);

    /**
     * @brief Updates position
     * 
     * @param dt timestep
     */
    void UpdatePosition(const double& dt);

    /**
     * @brief Updates time on food
     * 
     * @param dt timestep
     */
    void UpdateTimeOmFood(const double& dt);

    /**
     * @brief Generate new aiming point for the agent
     * 
     */
    void GenerateNewAim();

    /**
     * @brief Updates aiming point
     * 
     * @param dt timestep 
     */
    void UpdateAim(const double& dt);

};

#endif