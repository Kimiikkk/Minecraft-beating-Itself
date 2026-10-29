#pragma once
#include <cmath>
struct Vec3 { double x=0,y=0,z=0; };
inline double dist2(const Vec3&a,const Vec3&b){double x=a.x-b.x,y=a.y-b.y,z=a.z-b.z;return x*x+y*y+z*z;}
inline double dist(const Vec3&a,const Vec3&b){return std::sqrt(dist2(a,b));}
