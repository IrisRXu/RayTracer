//
// Created by Iris Xu on 8/9/23.
//

#ifndef RAYTRACER0_VECTOR_H
#define RAYTRACER0_VECTOR_H

#include <cmath>

struct Vector {
    double x = 0;
    double y = 0;
    double z = 0;

    //Vector(double=0, double=0, double=0);
    Vector(double x, double y, double z) : x(x), y(y), z(z){}


    Vector operator+ (const Vector& v) {
        return Vector(x+v.x, y+v.y, z+v.z);
    }

    Vector operator-(const Vector& v){
        return Vector(x-v.x, y-v.y, z-v.z);
    }

    Vector operator*(const double a) {
        return {x*a, y*a, z*a};
    }

    Vector operator/(double a){
        return Vector(x/a, y/a, z/a);
    }

    Vector normalize(){
        double length = sqrt(x*x + y*y + z*z);
        return Vector(x/length, y/length, z/length);
    }
};


#endif //RAYTRACER0_VECTOR_H
