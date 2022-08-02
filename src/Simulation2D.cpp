#include "Vector2D.h"
#include "Fly2D.h"
#include "Arena2D.h"
#include "Simulation2D.h"

#include <fstream>
#include <sys/stat.h>
#include <cmath>
#include <string.h>

Simulation2D::Simulation2D(const Vector2d<double>& c, const double& r, int nb_walls, const int& nb_ent, const int& nb_flies, const int& starting_room, const double& maxtime, const double& dt, const bool& datarec, const bool& v)
    : maxtime(maxtime), time(0.0), dt(dt), dataRec(datarec), VERBOSE(v){

    this->arena = new Arena2D(c, r, nb_walls, nb_ent);
    for(int i = 0; i<nb_flies; i++){
        this->flies.push_back(new Fly2D(starting_room, i, this->arena));
    }
    
    if(dataRec){ InitializeFile();}

}

Simulation2D::Simulation2D(const double& c1, const double& c2, const double& r, int nb_walls, const int& nb_ent, const int& nb_flies, const int& starting_room, const double& maxtime, const double& dt, const bool& datarec, const bool& v)
    : maxtime(maxtime), time(0.0), dt(dt), dataRec(datarec), VERBOSE(v){

    this->arena = new Arena2D(c1, c2, r, nb_walls, nb_ent);
    for(int i = 0; i<nb_flies; i++){
        this->flies.push_back(new Fly2D(starting_room, i, this->arena));
    }
    
    if(dataRec){ InitializeFile();}

    
}

Simulation2D::Simulation2D(Arena2D* arena, const int& nb_flies, const int& starting_room, const double& maxtime, const double& dt, const bool& datarec, const bool& v)
     : maxtime(maxtime), time(0.0), dt(dt), dataRec(datarec), VERBOSE(v){
    this->arena = arena;
    for(int i = 0; i<nb_flies; i++){
        this->flies.push_back(new Fly2D(starting_room, i, this->arena));
    }
    
    if(dataRec){ InitializeFile();}
    
}

Simulation2D::~Simulation2D(){
    std::cout<<"Total Running Time : "<<time<<"\n";
    for(int i=0; i < this->flies.size(); i++) delete(this->flies[i]);
    // Delete arena
    // TODO : Comprehensive deletion of arena if created using NEW command
    // delete arena;

    if(dataRec){ this->CloseFile();}

}

Vector2d<double> Simulation2D::GetArenaCenter() const{ return (*arena).GetCenter();}

double Simulation2D::GetArenaRadius() const{ return (*arena).GetRadius();}

void Simulation2D::Update(double dt){


    // std::cout<<"Update Sim\n";
    if(time < maxtime){
        // Flies update
        for(int i=0; i<this->flies.size(); i++){
            
            flies[i]->Update(dt);

        }
        // Food update
        if(arena->GetFood() != nullptr){
            arena->GetFood()->Update(dt);
        }

        // Data recording
        if(dataRec){
            // Values of variables
            Simfile<< time <<", ";
            for(int i = 0; i < this->GetFlies().size(); i++){
                Simfile<< this->flies[i]->GetPosition().x <<", "<<this->flies[i]->GetPosition().y<<", "<<this->flies[i]->GetRoom()<<", "<<this->flies[i]->GetTimeOnFood();
                if(i < this->flies.size() - 1){ Simfile<<", ";}
            }
            Simfile<<"\n";
        }

        if(VERBOSE) Verbose();

        time += dt;
    }


}

void Simulation2D::Verbose(){
    // TODO : Rework verbose function for all OS
    /* system("clear");

    std::cout<<"%";
    for(int i = 0; i < 10; i++){
        if(i <= floor(time / maxtime * 10)){
            std::cout<<"=";
        }
        if( i > floor(time / maxtime * 10)){
            std::cout<<" ";
        }
    }
    std::cout<<"%   "<<ceil(time / maxtime * 100.0)<<" %";

    std::cout<<"\n\n"; */
}


Arena2D* Simulation2D::GetArena(){ return this->arena;}


std::vector<Fly2D* > Simulation2D::GetFlies() const{ return this->flies;}

double Simulation2D::GetTime() const{ return time;}
    
double Simulation2D::Getdt() const{ return dt;}

double Simulation2D::GetMaxTime() const{return maxtime;}

bool Simulation2D::IsRunning() const{ return time < maxtime;}

void Simulation2D::InitializeFile(){
    // filename
    std::string directory("SimData/");
    std::string filename("SimData_");
    std::string number("000");
    std::string ext(".csv");

    // Check if datafile already exists
    for(int i = 0; i < 1000; i++){
        // Initialize file number
        if(i < 10){ number = "00" + std::to_string(i);}
        if(i >= 10 && i < 100 ){ number = "0" + std::to_string(i);}
        if(i >= 100){ number = std::to_string(i);}
        // Check existence of datafile
        if(!fileExists(directory + filename + number + ext)){
            break;
        }
    }

    // Initialize datafile
    Simfile.open(directory + filename + number + ext);
    Simfile << "time, ";
    for(int i = 0; i < this->flies.size(); i++){
        std::string nb = std::to_string(i);
        Simfile << "fly"<<i<<".x "<<", "<<"fly"<<i<<".y"<<", "<<"fly"<<i<<".room"<<", "<<"fly"<<i<<".TOF";
        if(i < this->flies.size() - 1){ Simfile<<", ";}
    }
    Simfile << "\n";

    WriteConfig(number);
}

void Simulation2D::WriteConfig(const std::string& number){
    // filename 
    std::string directory("SimConfig/");
    std::string filename("SimConfig_");
    std::string ext(".csv");

    // Initialize datafile
    Configfile.open(directory + filename + number + ext);
    Configfile << "time, timestep, flies, rooms, entrances, radius, center.x, center.y, food, food shifting \n";
    Configfile << maxtime <<", "<< dt <<", "<<flies.size();
    if(arena != nullptr){ Configfile<<", "<<arena->GetNbWalls()<<", "<<arena->GetWalls()[0].GetNbEnts()<<", "<<GetArenaRadius()<<", "<<GetArenaCenter().x<<", "<<GetArenaCenter().y;}
    else{ Configfile<<", "<<0<<", "<<0<<", "<<0<<", "<<0<<", "<<0;}
    
    if(arena != nullptr && arena->GetFood() != nullptr){ Configfile<<", "<<"yes"<<", "<<arena->GetFood()->GetMaxLifetime()<<"\n";}
    else{ Configfile<<", "<<"no"<<", "<<0;}

    Configfile<<"\n";

}

void Simulation2D::CloseFile(){
    if(Simfile.is_open()){ Simfile.close();}
    if(Configfile.is_open()){ Configfile.close();}
};

bool fileExists(const std::string& filename){
    struct stat buf;
    if (stat(filename.c_str(), &buf) != -1)
    {
        return true;
    }
    return false;
}

