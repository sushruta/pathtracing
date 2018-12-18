#include <iostream>
#include <cfloat>
#include <cmath>
#include <cstdlib>

#include "sphere.h"
#include "vecmath/vecmath.h"
#include "ray.h"
#include "sphere.h"
#include "group.h"
#include "camera.h"
#include "material.h"

using namespace std;

const int MAX_DEPTH = 4;
const int NUM_SAMPLES = 256;
const float T_MIN = 0.001;

Vector3f color(const Ray& ray, Object3D *world, int depth) {
    Hit hit;
    if (world->intersect(ray, hit, T_MIN)) {
        Vector3f attentuation;
        if (depth < MAX_DEPTH) {
            Ray scattered = (hit.getMaterial())->scatter(ray, hit, attentuation);
            return attentuation * color(scattered, world, depth + 1);
        } else {
            return Vector3f(0, 0, 0);
        }
    }
    Vector3f unitDirection = ray.getDirection();
    float t = 0.5 * (unitDirection.y() + 1);
    return (1 - t) * Vector3f(1, 1, 1) + t * Vector3f(0.5, 0.7, 1.0);
}

Group* generateWorld() {
    int n = 500;
    Object3D **list = new Object3D*[n+1];
    list[0] =  new Sphere(Vector3f(0,-1000,0), 1000, new Lambertian(Vector3f(0.5, 0.5, 0.5)));

    int i = 1;
    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            float choose_mat = drand48();
            Vector3f center(a+0.9*drand48(),0.2,b+0.9*drand48()); 
            if ((center - Vector3f(4,0.2,0)).abs() > 0.9) {
                if (choose_mat < 0.75) {  // diffuse
                    list[i++] = new Sphere(center, 0.2, new Lambertian(Vector3f(drand48()*drand48(), drand48()*drand48(), drand48()*drand48())));
                } else if (choose_mat < 0.9) { // metal
                    list[i++] = new Sphere(center, 0.2,
                            new Metal(Vector3f(0.5*(1 + drand48()), 0.5*(1 + drand48()), 0.5*(1 + drand48()))));
                } else { // dielectric
                    list[i++] = new Sphere(center, 0.2, new Dielectric(1.5));
                }
            }
        }
    }

    list[i++] = new Sphere(Vector3f(0, 1, 0), 1.0, new Dielectric(1.5));
    list[i++] = new Sphere(Vector3f(-4, 1, 0), 1.0, new Lambertian(Vector3f(0.4, 0.2, 0.1)));
    list[i++] = new Sphere(Vector3f(4, 1, 0), 1.0, new Metal(Vector3f(0.7, 0.6, 0.5)));

    Group *world = new Group(i);
    for (int j=0; j<i; j++) {
        world->addObject(j, list[j]);
    }
    return world;
}

int main() {
    int nx = 1280;
    int ny = 720;
    float as = (nx * 1.0) / (ny * 1.0);
    cout << "P3" << endl << nx << " " << ny << endl << "255" << endl;

    PerspectiveCamera *camera = new PerspectiveCamera(
        Vector3f(13, 2, 3),
        Vector3f(0, 0, 0),
        Vector3f(0, 1, 0),
        20
    );
    
/**
    Material *mat1 = new Lambertian(Vector3f(0.8, 0.3, 0.3));
    Material *mat2 = new Lambertian(Vector3f(0.8, 0.8, 0.0));
    Material *mat3 = new Metal(Vector3f(0.8, 0.6, 0.2));
    Material *mat4 = new Metal(Vector3f(0.8, 0.8, 0.8));
    
    Sphere *sphere1 = new Sphere(Vector3f(0, 0, -1), 0.5, mat1);
    Sphere *sphere2 = new Sphere(Vector3f(0, -100.5, -1), 100, mat2);
    Sphere *sphere3 = new Sphere(Vector3f(1, 0, -1), 0.5, mat3);
    Sphere *sphere4 = new Sphere(Vector3f(-1, 0, -1), 0.5, mat4);

    Group *world = new Group(4);
    world->addObject(0, sphere1);
    world->addObject(1, sphere2);
    world->addObject(2, sphere3);
    world->addObject(3, sphere4);
**/

    Group *world = generateWorld();
    for (int j = ny - 1; j >= 0; j--) {
        for (int i = 0; i < nx; i++) {
            Vector3f totalColor = Vector3f::ZERO;
            for (int c=0; c<NUM_SAMPLES; c++) {
                float u = as * (2.0 * (float(i + drand48()) / float(nx)) - 1.0);
                float v = 2.0 * (float(j + drand48()) / float(ny)) - 1.0;

                Ray ray = camera->generateRay(Vector2f(u, v));

                totalColor += color(ray, world, 0);
            }
            Vector3f col = totalColor / NUM_SAMPLES;

            // do some gamma correction before writing to image
            int ir = int(255.99 * sqrt(col[0]));
            int ig = int(255.99 * sqrt(col[1]));
            int ib = int(255.99 * sqrt(col[2]));

            cout << ir << " " << ig << " " << ib << endl;
        }
    }

    return 0;
}
