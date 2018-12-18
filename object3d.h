#ifndef OBJECT3D_H_
#define OBJECT3D_H_

#include "ray.h"
#include "hit.h"
#include "material.h"

class Object3D {
    public:
        Object3D() { material = NULL; }
        virtual ~Object3D() {}
        
        Object3D(Material *material) { this->material = material; }

        virtual bool intersect(const Ray& ray, Hit& hit, float tMin) const = 0;

        char *type;
    protected:
        Material *material;
};

#endif
