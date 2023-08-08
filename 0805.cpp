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

using namespace std;

struct Vector{
    double x,y,z;

    Vector(double x, double y, double z) : x(x), y(y), z(z){}

    Vector operator+ (const Vector& v) {
        return Vector(x+v.x, y+v.y, z+v.z);
    }

    Vector operator-(const Vector& v){
        return Vector(x-v.x, y-v.y, z-v.z);
    }

    Vector operator*(double a){
        return Vector(x*a, y*a, z*a);
    }

    Vector operator/(double a){
        return Vector(x/a, y/a, z/a);
    }

    Vector normalize(){
        double length = sqrt(x*x + y*y + z*z);
        return Vector(x/length, y/length, z/length);
    }
};

double dot(Vector& a, Vector& b){
    return (a.x*b.x + a.y*b.y + a.z*b.z);
}

ostream& operator<< (ostream& out, Vector& v){
    out<< "(" << v.x << "," << v.y << "," << v.z << ")" << endl;
    return out;
}

struct Ray{
    Vector origin;
    Vector direction;

    Ray(Vector& o, Vector& d) : origin(o), direction(d){}
};

struct Sphere{
    Vector center;
    double radius;

    Sphere(Vector& c, double r) : center(c), radius(r){}
};

Vector hitSphere (Ray ray, Sphere sphere, Vector light){
    Vector oc = ray.origin - sphere.center;
    double a = dot(ray.direction, ray.direction);
    double b = 2.0 * dot(oc, ray.direction);
    double c = dot(oc, oc) - sphere.radius *sphere.radius;
    double discriminant = b*b -4*a*c;
    if (discriminant < 0){
        return Vector(0,0,0);
    }
    double t = (-b - sqrt(discriminant))/ (2*a);
    Vector hitPoint = ray.origin + (ray.direction * t);
    Vector normal = (hitPoint - sphere.center).normalize();
    light = (light).normalize();
    double intensity = dot(normal, light);
    intensity = max(intensity, 0.0);
    return Vector(255, 0, 0)*intensity;
}

int main() {

    const int image_width = 100;
    const int image_height = 100;

    Vector black(0,0,0);
    Vector white(255,255,255);
    Vector pink(255, 0, 255);
    Vector pixel(black);

    Vector c (50,50,200);
    Sphere s (c, 20);

    Vector light (100,0,-200);

    ofstream image;
    image.open("sphere_greyscale.ppm");

    if (image.is_open()){
        image << "P3\n" << image_width << " " << image_width << endl;
        image << "255" << endl;

        for (int j=0; j<image_height; j++ ){
            for (int i=0; i<image_width; i++){
                pixel = black;
                //cout << "here";

                Vector d(0,0,1);
                Vector o(j,i,0);

                Ray r (o, d);

                pixel = hitSphere(r, s, light);

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

/*



using color = vec;
using point = vec;

void write_color(std::ostream out, color pixel_color){
    out << pixel_color.x() << " "
        << pixel_color.y() << " "
        << pixel_color.z() << endl;
}

class ray{
    public:
        ray(){}
        ray(point origin, vec& direction): orig(origin), dir(direction){};

        point origin(){
            return orig;
        }

    vec direction(){
            return dir;
        }

        point at(double t){
            return orig + dir*t;
        }
};

// origin: set to 0
// direction: a point on the view plane

bool hit_sphere (point center, double radius, ray r){
    vector oc = r.origin() - center;
    double a = dot(r.direction(), r.direction());
    double b = 2.0 * dot(oc, r.direction());
    double c = dot(oc, oc) - radius *radius;
    double discriminant = b*b -4*a*c;
    return (discriminant >= 0);
}

color ray_color(ray r){
    if (hit_sphere(point (1, 1, 1), 2, r))
        return color (255, 255, 255);
    //figure out where t is
}

*/
