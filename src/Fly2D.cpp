#include <iostream>
#include <random>
// #include <RVO.h>
// #include "../lib/RVO2/src/RVO.h"
#include "Vector2D.h"
#include "Fly2D.h"

using namespace std;

Fly2D::Fly2D(const Vector2d<double>& position, const int& index, Arena2D* arena ) : r(position), v(Vector2d<double>(0,0)), v_pref(Vector2d<double>(0,0)), a(Vector2d<double>(0,0)), angle(0.0), index(index), arena(arena), room(arena->GetRoomFromPosition(position))
    , Fint(Vector2d<double>(0,0)), Ffric(Vector2d<double>(0,0)), Fres(Vector2d<double>(0,0)), Fnoise(Vector2d<double>(0,0)), rcog(100.0), timeonfood(0.0){

    this->GenerateNewAim();
    }

Fly2D::Fly2D(const double& x, const double& y, const int& index, Arena2D* arena) : r(Vector2d<double>(x, y)), v(Vector2d<double>(0,0)), v_pref(Vector2d<double>(0,0)), a(Vector2d<double>(0,0)), angle(0.0), index(index), arena(arena), room(arena->GetRoomFromPosition(x, y))
    , Fint(Vector2d<double>(0,0)), Ffric(Vector2d<double>(0,0)), Fres(Vector2d<double>(0,0)), Fnoise(Vector2d<double>(0,0)), rcog(100.0), timeonfood(0.0){

    this->GenerateNewAim();
    }

Fly2D::Fly2D(const int& room, const int& index, Arena2D* arena) : v(Vector2d<double>(0,0)), v_pref(Vector2d<double>(0,0)), a(Vector2d<double>(0,0)), angle(0.0), index(index), arena(arena)
    , Fint(Vector2d<double>(0,0)), Ffric(Vector2d<double>(0,0)), Fres(Vector2d<double>(0,0)), Fnoise(Vector2d<double>(0,0)), rcog(100.0), timeonfood(0.0){
    
    if(this->arena != nullptr && room < this->arena->GetNbWalls() && room >= 0){
        r = this->arena->GetRoomCenter(room);
        this->room = room;
    }
    this->GenerateNewAim();
}


int Fly2D::GetRoom() const{ return this->room;}


double Fly2D::GetAngle() const{ return this->angle;}

Vector2d<double> Fly2D::GetPosition() const{ return this->r;}

Vector2d<double> Fly2D::GetVelocity() const{ return this->v;}

Vector2d<double> Fly2D::GetVelocitypref() const{ return this->v_pref;}

Vector2d<double> Fly2D::GetFres() const{ return this->Fres;}

Vector2d<double> Fly2D::GetAim() const{ return this->aim;}

void Fly2D::SetAim(const Vector2d<double>& point){ this->aim = point;}

void Fly2D::SetAim(const double& x, const double& y){ this->aim = Vector2d<double>(x, y);}


void Fly2D::GenerateNewAim(){
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::normal_distribution<double> Gauss(0.0, 50.0); //or rcog/2
    std::uniform_real_distribution<double> Uniform(-rcog,rcog);
    Vector2d<double> dr;
    if(arena->OnFood(room)){ aim = arena->GetRoomCenter(room);}
    else{
        do{
            double x(Uniform(gen));
            double y(Uniform(gen));
            dr = Vector2d<double>(x, y);
        } while (EuclideanNorm((r + dr) - arena->GetCenter()) > arena->GetRadius() && EuclideanNorm(dr) < rcog);
        this->aim = r + dr;
    }
}

void Fly2D::UpdateAim(const double& dt){
    // std::cout<<"Aim distance "<<index<<" "<<EuclideanNorm(r -aim)<<" "<<EuclideanNorm(v) * dt<<" "<<EuclideanNorm(v)<<"\n\n\n";

    if(EuclideanNorm(r - aim) <= EuclideanNorm(v_pref) * dt * 2.5|| EuclideanNorm(r - aim) > rcog){
        // std::cout<<"Close to aim, change aim\n\n\n";
        this->GenerateNewAim();

    }
}

void Fly2D::Update(const double& dt){
    // Update reponse to environment
    this->UpdateFres();
    // Update preferred velocity
    this->UpdateVpref(dt);
    // Update velocity
    this->UpdateV(dt);
    // Update angle
    this->UpdateAngle();
    // Update position
    this->UpdatePosition(dt);
    // Update aim
    this->UpdateAim(dt);
    // Update room of fly
    this->UpdateRoom();
    // Update time of food
    this->UpdateTimeOmFood(dt);
}

void Fly2D::UpdateAngle(){
    if(this->v != Vector2d<double>(0.0, 0.0)){
        // std::cout<<"Update Angle "<<this->angle * 180 / M_PI;
        Vector2d<double> orient(this->r + this->v);
        Vector2d<double> uvec(1.0, 0.0);
        uvec+= this->r;

        this->angle = atan2(this->v.y, this->v.x);
        // std::cout<<" "<<this->angle * 180 / M_PI<<"\n";
    }

}

void Fly2D::UpdateFres(){
    // std::cout<<"Update Fres "<<index<<" "<<r<<" "<<aim<<" "<<EuclideanNorm(v)<<"\n";
    Vector2d<double> rie(aim - r);
    // Fres = Xres * H(rcog - |rie|) * (se * rie/|rie| * R(n, theta) - (1 - se) * rie / |rie|)
    if(arena->OnFood(room)){ 
        double rcog_ = 1000.0;
        Fres = 10.0 * std::max(0.0, (rcog_ - EuclideanNorm(rie)) / fabs(rcog_ - EuclideanNorm(rie))) * (rie/EuclideanNorm(rie)); 
    }
    else{
        Fres = 100 * std::max(0.0, (rcog - EuclideanNorm(rie)) / fabs(rcog - EuclideanNorm(rie))) * (rie/EuclideanNorm(rie));
    }
}

void Fly2D::UpdateVpref(const double& dt){
    v_pref = v + Fres * dt;
    // If v_pref norm exceeds max observed fly speed
    // if(EuclideanNorm(v_pref) > 25) v_pref *= 25 / EuclideanNorm(v_pref);
}

void Fly2D::UpdateV(const double& dt){
    v = v_pref;
    // If v_pref norm exceeds max observed fly speed
    if(EuclideanNorm(v) > 25) v *= 25 / EuclideanNorm(v);
}

void Fly2D::UpdatePosition(const double& dt){
    Vector2d<double> new_r (r + v * dt);
    if(arena->AllowMove(r, new_r)){ r = new_r;}
    else if(arena->OnFood(room)){ GenerateNewAim();}
    else{GenerateNewAim();}
}

void Fly2D::UpdateRoom(){ room = arena->GetRoomFromPosition(r);}


double Fly2D::GetTimeOnFood() const { return timeonfood;} 

void Fly2D::UpdateTimeOmFood(const double& dt){
    if(arena->OnFood(room)){ timeonfood+= dt;}}
