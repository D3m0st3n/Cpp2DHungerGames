#include <iostream>
#include "Vector2D.h"
#include "Arena2D.h"
#include "Food.h"

Food::Food(Arena2D* arena, const int& room, const double& max_lifetime) : lifetime(0.0){
    this->arena = arena;
    if(max_lifetime > 0){ this->max_lifetime = max_lifetime;}
    if(room >= 0 && room < this->arena->GetNbWalls()){ this->room = room;}

}

Food::Food(Food* food) : lifetime(0.0){ 
    if(food != nullptr){
        this->max_lifetime = food->GetMaxLifetime();
        this->arena = food->GetArena();
        this->room = food->GetRoom();
    }

}


int Food::GetRoom() const{ return room;}

Arena2D* Food::GetArena(){ return arena;}

double Food::GetMaxLifetime() const{ return max_lifetime;}

double Food::GetLifetime() const{ return lifetime;}



bool Food::SetRoom(const int& room){
    if( room >= 0 && room < arena->GetNbWalls()){
        this->room = room;
        return true;
    }
    return false;

}

void Food::Update(const double& dt){
    double rate = 1;

    if(lifetime < max_lifetime){lifetime += rate * dt;}
    else{ 
        lifetime = 0.0;
        if(room >= arena->GetNbWalls() - 1){
            room = 0;
        }
        else{
            room += 1;
        }

    }

}
