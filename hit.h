#ifndef HIT_H_
#define HIT_H_

#include <cfloat>
#include "ray.h"
#include "vecmath/vecmath.h"

class Material;

class Hit {
    public:
        Hit() {
            material = NULL;
            t = FLT_MAX;
            hasTex = false;
        }

        Hit(float _t, Material *m, const Vector3f& n) {
            t = _t;
            material = m;
            normal = n;
            hasTex = false;
        }

        // copy constructor
        Hit(const Hit& hit) {
            t = hit.t;
            material = hit.material;
            normal = hit.normal;
            hasTex = hit.hasTex;
        }

        ~Hit() {}

        float getT() const { return t; }

        Material* getMaterial() const { return material; }

        const Vector3f& getNormal() const { return normal; }

        void set(float _t, Material *m, const Vector3f& n) {
            t = _t;
            material = m;
            normal = n;
        }

        void setTexCoord(const Vector2f& coord) {
            texCoord = coord;
            hasTex = true;
        }

        bool hasTex;
        Vector2f texCoord;

    private:
        float t;
        Material *material;
        Vector3f normal;
};

#endif
