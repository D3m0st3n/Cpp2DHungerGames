#include <iostream>
#include <vector>
#include "Vector2D.h"
#include "Rectangle.h"

Rectangle::Rectangle(const Vector2d<double>& c1, const Vector2d<double>& c2, const Vector2d<double>& c3, const Vector2d<double>& c4) {
    this->coord[0] = c1;
    this->coord[1] = c2;
    this->coord[2] = c3;
    this->coord[3] = c4;

}

Rectangle::Rectangle(const Vector2d<double>& p, const double& length, const double& width) {
    this->coord[0] = p;
    this->coord[1] = Vector2d<double>(p.x + length, p.y);
    this->coord[2] = Vector2d<double>(p.x + length, p.y + width);
    this->coord[3] = Vector2d<double>(p.x, p.y + width);

}

std::vector<Vector2d<double> > Rectangle::GetCoord() const{
    std::vector<Vector2d<double> > coord;
    coord.push_back(this->coord[0]);
    coord.push_back(this->coord[1]);
    coord.push_back(this->coord[2]);
    coord.push_back(this->coord[3]);
    return  coord;
}

int Rectangle::GetNbSides() const{ return 4;}

double Rectangle::GetLength() const{ return EuclideanNorm(this->coord[1] - this->coord[0]);}

double Rectangle::GetWidth() const{ return EuclideanNorm(this->coord[3] - this->coord[0]);}

Vector2d<double> Rectangle::GetLengthVec() const{ return (this->coord[1] - this->coord[0]) / this->GetLength();}

Vector2d<double> Rectangle::GetWidthVec() const{ return (this->coord[3] - this->coord[0]) / this->GetWidth();}

Vector2d<double> Rectangle::GetCenter() const{ return (this->coord[0] + this->coord[2]) / 2.0;}

bool Rectangle::PointInBB(const Vector2d<double>& point){
    return (point.x >= std::min(std::min(this->coord[0].x, this->coord[1].x), std::min(this->coord[2].x, this->coord[3].x)) 
                    && point.x <= std::max(std::max(this->coord[0].x, this->coord[1].x), std::max(this->coord[2].x, this->coord[3].x))) 
        && (point.y >= std::min(std::min(this->coord[0].y, this->coord[1].y), std::min(this->coord[2].y, this->coord[3].y)) 
                    && point.y <= std::max(std::max(this->coord[0].y, this->coord[1].y), std::max(this->coord[2].y, this->coord[3].y)));
}

bool Rectangle::PointInBB(const double& x, const double& y){
    return this->PointInBB(Vector2d<double>(x, y));
}

bool Rectangle::PointIsInside(const Vector2d<double>& point) {
    // See Winding Number Algorithm for reference
    // Point in Bouding Box
    if(this->PointInBB(point)){
                
        // Check nb sides crossed in two directions to validate if point is inside
        int count_i = 0;
        int count_j = 0;


        for(int i = 0; i<this->GetNbSides(); i++){
            if(i + 1 == this->GetNbSides()){
                if(Intersect(point, point+Vector2d<double>(10000.0, 0.0), this->coord[0], this->coord[i])){
                    count_i++;
                }
                if(Intersect(point, point+Vector2d<double>(0.0, 10000.0), this->coord[0], this->coord[i])){
                    count_j++;
                }
            }
            else{
                if(Intersect(point, point+Vector2d<double>(10000.0, 0.0), this->coord[i], this->coord[i+1])){
                    count_i++;
                }
                if(Intersect(point, point+Vector2d<double>(0.0, 10000.0), this->coord[i], this->coord[i+1])){
                    count_j++;
                }
            }

        }
                
        if(count_i % 2 == 0 || count_j % 2 == 0){
            return false;
        }
        
        else{
            return true;
        }
    }
    else{
        return false;
    }
}

bool Rectangle::PointIsInside(const double& x, const double& y){
    return this->PointIsInside(Vector2d<double>(x, y));
}

