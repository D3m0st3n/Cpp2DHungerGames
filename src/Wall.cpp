#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include "Vector2D.h"
#include "Rectangle.h"
#include "Wall.h"
#include "Entrance.h"
#include "Arena2D.h"

Wall::Wall(const Vector2d<double>& c1, const Vector2d<double>& c2, const Vector2d<double>& c3, const Vector2d<double>& c4, int nb_ent, Arena2D* arena) : Rectangle(c1, c2, c3, c4) {
    this->BuildEntrances(nb_ent, 0.1 * this->GetLength());
    this->arena = arena;

}

Wall::Wall(const Vector2d<double>& p, const double& length, const double& width, int nb_ent, Arena2D* arena) : Rectangle(p, length, width) {
    this->BuildEntrances(nb_ent, 0.1 * this->GetLength());
    this->arena = arena;

}

void Wall::BuildEntrances(const int& nb_ent, const double& length_e){
    // RNG initialization
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_real_distribution<double> Uniform(0.1 * GetLength(), 0.9 * GetLength());
    // Tries to place entrances until they do not superpose
    do
    {   
        bool add_flag = true;
        Vector2d<double> c1, c2, c3, c4;

        c1 = this->coord[0] + this->GetLengthVec() * Uniform(gen);
        c2 = c1 + this->GetLengthVec() * length_e;
        c3 = c2 + this->GetWidthVec() * this->GetWidth();
        c4 = c1 + this->GetWidthVec() * this->GetWidth();
        bool isFake = false;

        if(ents.size() > 0){

            isFake = true;

            for(int i=0; i<ents.size();i++){
                if(EuclideanNorm(ents[i].GetCoord()[0] - c1) < 1.1 * length_e){
                    add_flag = false;
                }
            }
        }
        if(add_flag){ this->ents.push_back(Entrance(c1, c2, c3, c4, isFake, this));}
    } while (ents.size() < nb_ent);

    std::cout << "Entrances built, nb ents : "<< this->GetNbEnts()<<"\n";

}

std::vector<Entrance> Wall::GetEntrances() const{ return this->ents;}

int Wall::GetNbEnts() const{ return this->ents.size();}
