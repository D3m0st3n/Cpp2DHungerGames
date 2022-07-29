#include <iostream>
#include <vector>
#include "Vector2D.h"
#include "Rectangle.h"
#include "Wall.h"
#include "Entrance.h"

Entrance::Entrance(const Vector2d<double>& c1, const Vector2d<double>& c2, const Vector2d<double>& c3, const Vector2d<double>& c4, const bool& isFake,  Wall* wall) : Rectangle(c1, c2, c3, c4), isFake(isFake) {
    this->wall = wall;
}
Entrance::Entrance(const Vector2d<double>& p, const double& length, const double& width, const bool& isFake,  Wall* wall) : Rectangle(p, length, width), isFake(isFake) {
    this->wall = wall;
}

bool Entrance::IsFake() const{ return isFake;}