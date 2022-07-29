#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <iostream>
#include <tuple>
#include <cmath>
#include <cfloat>
#include <climits>

/*The Vector2d class is an object consisting of simply an x and
  y value. Certain operators are overloaded to make it easier
  for vector math to be performed.*/
template<class T> 
class Vector2d {
public:
    /*The x and y values are public to give easier access for
      outside funtions. Accessors and mutators are not really
      necessary*/
    T x;
    T y;

    //Constructor assigns the inputs to x and y.
    Vector2d(): x(T(0)), y(T(0)) {}
    Vector2d(const T& vx, const T& vy): x(vx), y(vy) {}
    Vector2d(const Vector2d& v): x(v.x), y(v.y) {}

    /*The following operators simply return Vector2ds that
      have operations performed on the relative (x, y) values*/
    Vector2d& operator+=(const Vector2d& v) { x += v.x; y += v.y; return *this; }
    Vector2d& operator-=(const Vector2d& v) { x -= v.x; y -= v.y; return *this; }
    Vector2d& operator*=(const Vector2d& v) { x *= v.x; y *= v.y; return *this; }
    Vector2d& operator/=(const Vector2d& v) { x /= v.x; y /= v.y; return *this; }

    //Check if the Vectors have the same values (uses pairwise comparison of `std::tuple` on the x,y values of L and R.
    friend bool operator==(const Vector2d& L, const Vector2d& R) { return L.x == R.x && L.y == R.y;}//return std::tie(L.x, L.y) == std::tie(R.x, R.y);  }
    friend bool operator!=(const Vector2d& L, const Vector2d& R) { return !(L == R); }

    //Negate both the x and y values.
    Vector2d operator-() const { return Vector2d(-x, -y); }

    //Apply scalar operations.
    Vector2d& operator*=(const T&  s) { x *= s; y *= s; return *this; }
    Vector2d& operator/=(const T& s) { x /= s; y /= s; return *this; }
};

template<class T> Vector2d<T> operator+(const Vector2d<T>& L, const Vector2d<T>& R) { return Vector2d<T>(L) += R; }
template<class T> Vector2d<T> operator-(const Vector2d<T>& L, const Vector2d<T>& R) { return Vector2d<T>(L) -= R; }
template<class T> Vector2d<T> operator*(const Vector2d<T>& L, const Vector2d<T>& R) { return Vector2d<T>(L) *= R; }
template<class T> Vector2d<T> operator/(const Vector2d<T>& L, const Vector2d<T>& R) { return Vector2d<T>(L) /= R; }

template<class T> Vector2d<T> operator*(const T& s, const Vector2d<T>& v) { return Vector2d<T>(v) *= s; }
template<class T> Vector2d<T> operator*(const Vector2d<T>& v, const T& s) { return Vector2d<T>(v) *= s; }
template<class T> Vector2d<T> operator/(const T& s, const Vector2d<T>& v) { return Vector2d<T>(v) /= s; }
template<class T> Vector2d<T> operator/(const Vector2d<T>& v, const T& s) { return Vector2d<T>(v) /= s; }

//Product functions
template<class T> T DotProduct(const Vector2d<T>& a, const Vector2d<T>& b) {return ((a.x * b.x) + (a.y * b.y));};
template<class T> T CrossProduct(const Vector2d<T>& a, const Vector2d<T>& b) {return ((a.x * b.y) - (a.y * b.x));};

//Returns the length of the vector from the origin.
template<class T> T EuclideanNorm(const Vector2d<T>& v) {return sqrt((v.x * v.x) + (v.y * v.y));};

//Return the unit vector of the input
template<class T> Vector2d<T> Normal(const Vector2d<T>& v) {float magnitude = EuclideanNorm(v); return Vector2d<T>(v.x / magnitude, v.y / magnitude);};

//Return a vector perpendicular to the left.
template<class T> Vector2d<T> Perpendicular(const Vector2d<T>& v) {return Vector2d<T>(v.y, -v.x);};

//Return true if two line segments intersect.
template<class T> bool Intersect(const Vector2d<T>& aa, const Vector2d<T>& ab, const Vector2d<T>& ba, const Vector2d<T>& bb) {
  
  Vector2d<T> p = aa;
  Vector2d<T> r = ab - aa;
  Vector2d<T> q = ba;
  Vector2d<T> s = bb - ba;

  T t = CrossProduct((q - p), s) / CrossProduct(r, s);
  T u = CrossProduct((q - p), r) / CrossProduct(r, s);

  return (0.0 <= t && t <= 1.0) &&
          (0.0 <= u && u <= 1.0);
};

//Return the point where two lines intersect.
template<class T> Vector2d<T> GetIntersect(const Vector2d<T>& aa, const Vector2d<T>& ab, const Vector2d<T>& ba, const Vector2d<T>& bb) {

  float pX = (aa.x*ab.y - aa.y*ab.x)*(ba.x - bb.x) - (ba.x*bb.y - ba.y*bb.x)*(aa.x - ab.x);
  float pY = (aa.x*ab.y - aa.y*ab.x)*(ba.y - bb.y) - (ba.x*bb.y - ba.y*bb.x)*(aa.y - ab.y);
  float denominator = (aa.x - ab.x)*(ba.y - bb.y) - (aa.y - ab.y)*(ba.x - bb.x);

  return Vector2d<T>(pX / denominator, pY / denominator);
};

//Enable vector to be passed to a ostream
template<class T> std::ostream& operator<<(std::ostream& s, const Vector2d<T>& v){ return s << "(" << v.x << ", " << v.y << ")";}

// Indicate if two vectors are colinear
template<class T> bool Colinear(const Vector2d<T>& aa, const Vector2d<T>& ab, const Vector2d<T>& ba, const Vector2d<T>& bb){
  Vector2d<T> r = ab - aa;
  Vector2d<T> s = bb - ba;

  T v = CrossProduct(r, s); 

  return v == 0.0;
};

// Indicate if two vector are colienear and aligned
template<class T> bool Aligned(const Vector2d<T>& aa, const Vector2d<T>& ab, const Vector2d<T>& ba, const Vector2d<T>& bb){
  Vector2d<T> p = ba - aa;
  Vector2d<T> r = ab - aa;
  Vector2d<T> q = bb - ab;
  Vector2d<T> s = bb - ba;

  if(Colinear(aa, ab, ba, bb)){
    T t = CrossProduct(p, q);

    return t == 0;
  }

  else{
    return false;
  }
};

// Indicate if a point is aligned on vector
template<class T> bool PointAligned(const Vector2d<T>& aa, const Vector2d<T>& ab, const Vector2d<T>& c){
  Vector2d<T> p = ab - aa;
  Vector2d<T> r = ab - c;
  Vector2d<T> q = aa - c;
   
  T t = CrossProduct(p, r);
  T u = CrossProduct(p, q);

  return (t == 0.0) && (u == 0.0);
};

// Indicate if a point is on a segment
template<class T> bool PointOnSegment(const Vector2d<T>& aa, const Vector2d<T>& ab, const Vector2d<T>& c){
  if(PointAligned(aa, ab, c)){
    return (c.x >= std::fmin(aa.x, ab.x) && c.x <= std::fmax(aa.x, ab.y)) && (c.y >= std::fmin(aa.y, ab.y) && c.y <= std::fmax(aa.y, ab.y));
  }
  else{
    return false;
  }
};

#endif