#ifndef SPHERE_H_
#define SPHERE_H_

#include <cmath>
#include <iostream>

#include "object3d.h"

class Sphere : public Object3D {
    public:
        Sphere() {
            material = NULL;
        }

        Sphere(Vector3f center, float radius, Material* material): Object3D(material) {
            this->center = center;
            this->radius = radius;
            this->material = material;
        }
        
        ~Sphere() {}
        
        virtual bool intersect(const Ray& ray, Hit& hit, float tMin) const {
            bool isHit = false;

            Vector3f oc = ray.getOrigin() - center;
            float a = 1;
            float b = Vector3f::dot(oc, ray.getDirection());
            float c = Vector3f::dot(oc, oc) - radius*radius;
        
            float discriminant = b*b - a*c;
            if (discriminant > 0) {
                float temp = -b - sqrt(discriminant);
                if (temp > tMin && temp < hit.getT()) {
                    Vector3f normal = ray.pointAtParameter(temp) - center;
                    hit.set(temp, material, normal);
                    isHit = true;
                }
                temp = -b + sqrt(discriminant);
                if (temp > tMin && temp < hit.getT()) {
                    Vector3f normal = ray.pointAtParameter(temp) - center;
                    hit.set(temp, material, normal);
                    isHit = true;
                }
            }
        
            return isHit;
        }
    private:
        Vector3f center;
        float radius;
        Material *material;
};

#endif
