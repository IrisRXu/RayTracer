//
// Created by Iris Xu on 8/9/23.
//

#ifndef RAYTRACER0_SPHERE_H
#define RAYTRACER0_SPHERE_H
#include "Vector.h"

struct Material{

};

struct Sphere{
    Vector center;
    double radius;
    Vector color;

    Sphere(Vector& c, double r, Vector& color) : center(c), radius(r), color(color){}
};

#endif //RAYTRACER0_SPHERE_H
