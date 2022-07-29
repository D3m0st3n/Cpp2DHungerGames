#ifndef SIMULATION2D_H
#define SIMULATION2D_H

#include <iostream>
#include <fstream>

#include "Vector2D.h"
#include "Fly2D.h"
#include "Arena2D.h"

class Simulation2D {

    public:

    //Constructor
        /**
         * @brief Construct a new Simulation2D object
         * 
         * @param c center position
         * @param r radius
         * @param nb_walls number of walls/rooms 
         * @param nb_ent number of entrances in each wall
         * @param nb_flies number of flies in the arena
         * @param starting_room starting room of the flies
         * @param maxtime maximum running time
         * @param dt timestep
         * @param datarec indicates if simulation records data
         */
        Simulation2D(const Vector2d<double>& c, const double& r, int nb_walls = 0, const int& nb_ent = 2, const int& nb_flies = 0, const int& starting_room = 0, const double& maxtime = 1000.0, const double& dt = 0.1, const bool& datarec = 0);

        /**
         * @brief Construct a new Simulation2D object
         * 
         * @param c1 x center coordinate
         * @param c2 y center coordinate
         * @param r radius
         * @param nb_walls number of walls/rooms 
         * @param nb_ent number of entrances in each wall
         * @param nb_flies number of flies in the arena
         * @param starting_room starting room of the flies
         * @param maxtime maximum running time
         * @param dt timestep
         * @param datarec indicates if simulation records data
         */
        Simulation2D(const double& c1, const double& c2, const double& r, int nb_walls = 0, const int& nb_ent = 2, const int& nb_flies = 0, const int& starting_room = 0, const double& maxtime = 1000.0, const double& dt = 0.1, const bool& datarec = 0);

        /**
         * @brief Construct a new Simulation2D object
         * 
         * @param arena arena object
         * @param nb_flies number of flies in the arena
         * @param starting_room starting room of the flies
         * @param maxtime maximum running time
         * @param dt timestep
         * @param datarec indicates if simulation records data
         */
        Simulation2D(Arena2D* arena, const int& nb_flies = 0, const int& starting_room = 0, const double& maxtime = 1000.0, const double& dt = 0.1, const bool& datarec = 0);

        //Destructor
        /**
         * @brief Destroy the Simulation 2D object
         * Specially all associated pointers
         */
        ~Simulation2D();

        /**
         * @brief Get the Arena Center 
         * 
         * @return Vector2d<double> center of arena
         */
        Vector2d<double> GetArenaCenter() const;

        /**
         * @brief Get the Arena Radius 
         * 
         * @return double arena radius
         */
        double GetArenaRadius() const;

        /**
         * @brief Update one step of the simulation
         * 
         * @param dt timestep
         */
        void Update(double dt);

        /**
         * @brief Get arena of simulation
         * 
         * @return Arena2D* 
         */
        Arena2D* GetArena();

        /**
         * @brief Get the fly vector
         * 
         * @return std::vector<Fly2D* > 
         */
        std::vector<Fly2D* > GetFlies() const;

        /**
         * @brief Get time of simulation
         * 
         * @return double 
         */
        double GetTime() const;

        /**
         * @brief Get timestep of simulation
         * 
         * @return double 
         */
        double Getdt() const;

        /**
         * @brief Get maximum running time of simulation
         * 
         * @return double 
         */
        double GetMaxTime() const;

        /**
         * @brief Check if simulation is running
         * 
         * @return true simulation is running
         * @return false simulation has ended
         */
        bool IsRunning() const;


    private:
    
        Arena2D* arena;
        std::vector<Fly2D*> flies;
        double maxtime;
        double time;
        double dt;
        bool dataRec;
        std::ofstream Simfile;
        std::ofstream Configfile;

        /**
         * @brief print advancement of simulation
         * 
         */
        void Verbose();

        /**
         * @brief Open and start datafiles for data recording and config file
         * 
         */
        void InitializeFile();

        /**
         * @brief Open and write simulation configuration
         * 
         * @param number number in filename
         */
        void WriteConfig(const std::string& number);

        /**
         * @brief Close already open file
         * 
         */
        void CloseFile();



};

/**
 * @brief Check if file already exists
 * Utility function
 * 
 * @param filename 
 * @return true file with name "filename" exists
 * @return false no matching file found
 */
bool fileExists(const std::string& filename);

#endif