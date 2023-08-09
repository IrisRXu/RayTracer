/* find if the ray hits the object
 * how to reflect light
 * find the color to show for each pixel
 *
 * what's input and output
 * input: sphere, sphere position, light source, camera position
 * output: 2D image
 */


#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <limits>

#include "Vector.h"
#include "Ray.h"
#include "Sphere.h"

using namespace std;


double dot(Vector& a, Vector& b){
    return (a.x*b.x + a.y*b.y + a.z*b.z);
}

ostream& operator<< (ostream& out, Vector& v){
    out<< "(" << v.x << "," << v.y << "," << v.z << ")" << endl;
    return out;
}

struct HitInfo{
    bool didHit = false;
    double distance = 0;
    Vector hitPoint = Vector (0,0,0);
    Vector normal = Vector (0,0,0);
    //Vector pixelColor = Vector (0,0,0);

    HitInfo() {}
};

void hitSphere (Ray ray, Sphere sphere, HitInfo closest){
    Vector oc = ray.origin - sphere.center;
    double a = dot(ray.direction, ray.direction);
    double b = 2.0 * dot(oc, ray.direction);
    double c = dot(oc, oc) - sphere.radius * sphere.radius;
    double discriminant1 = b*b -4*a*c;
    if (discriminant1 < 0){
        return;
    }
    double t = (-b - sqrt(discriminant1))/ (2*a);
    if (t>0 && t < closest.distance){
        closest.didHit = true;
        closest.distance = t;
        closest.hitPoint = ray.origin + (ray.direction * closest.distance);
        closest.normal = (closest.hitPoint - sphere.center).normalize();
    }

    /*
    light = (light).normalize();
    double intensity = dot(hit.normal, light);
    intensity = max(intensity, 0.0);
    hit.pixelColor = sphere.color*intensity;
    */
}

/*
HitInfo findClosest (Ray r, Sphere (&spheres)[2]){
    HitInfo closest = HitInfo();
    closest.distance = numeric_limits<double>::max();
    for (Sphere sphere : spheres){
        HitInfo hit = hitSphere(r, sphere);
        if (hit.didHit && hit.distance < closest.distance){
            closest=hit;
        }
    }
}
*/

HitInfo trace (Ray ray, Sphere (&spheres)[2]){
    HitInfo closest = HitInfo();
    for (Sphere sphere:spheres){
        hitSphere(ray, sphere, closest);
    }
    return closest;
}

int main() {

    const int image_width = 500;
    const int image_height = 500;

    Vector red = Vector (255, 0, 0);
    Vector blue = Vector (0, 0, 255);
    Vector c1 (500,250,200);
    Sphere s1 (c1, 250, red);
    Vector c2 (150,250,200);
    Sphere s2 (c2, 100, blue);

    Sphere spheres[2] = {s1, s2};
    Vector light (0,250,-1000);

    ofstream image;
    image.open("2 spheres.ppm");

    if (image.is_open()){
        image << "P3\n" << image_width << " " << image_width << endl;
        image << "255" << endl;

        for (int j=0; j<image_height; j++ ){
            for (int i=0; i<image_width; i++){
                Vector pixel = Vector (0,0,0);

                Vector d(0,0,1);
                Vector o(j,i,0);

                //Ray r (o, d);

                HitInfo closest = HitInfo();
                closest.distance = numeric_limits<double>::max();
                for (Sphere sphere : spheres){
                    Ray r (o, d);
                    HitInfo hit = hitSphere(r, sphere, light);
                    if (hit.didHit && hit.distance < closest.distance){
                        closest=hit;
                        //
                        Vector d2 = r.direction - (closest.normal * (2.0 * dot(closest.normal, r.direction)));
                        Ray r2 (closest.hitPoint, d2);
                        //r.origin = closest.hitPoint;
                        //r.direction =  r.direction - (closest.normal * (2.0 * dot(closest.normal, r.direction)));

                        HitInfo hit2 = hitSphere(r2, sphere, light);
                        if (hit2.didHit){
                            closest.pixelColor = hit2.pixelColor + closest.pixelColor;
                        }
                    }
                }




                pixel = closest.pixelColor;

                image << (int)pixel.x << " "
                      << (int)pixel.y << " "
                      << (int)pixel.z << endl;
            }
        }
    }
    image.close();

    return 0;
}
//drgf 阴影部分的光
//image format? discrete vs ?
//anti-aliasing
