//
// Created by Iris Xu on 8/9/23.
//

#ifndef RAYTRACER0_RAY_H
#define RAYTRACER0_RAY_H
#include "Vector.h"

struct Ray{
    Vector origin;
    Vector direction;

    Ray(Vector& o, Vector& d) : origin(o), direction(d){}
};

#endif //RAYTRACER0_RAY_H
