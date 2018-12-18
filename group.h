#ifndef GROUP_H_
#define GROUP_H_

#include <iostream>

#include "object3d.h"
#include "ray.h"
#include "hit.h"

class Group : public Object3D {
    public:
        Group() {}
        Group(int numObjects) {
            this->numObjects = numObjects;
            group = new Object3D*[numObjects]; 
        }
        ~Group() {
            for (int i=0; i<numObjects; i++) {
                delete(group[i]);
            }
            delete(group);
        }
        int getGroupSize() { return numObjects; }
        void addObject(int index, Object3D *object) {
            group[index] = object;
        }

        virtual bool intersect(const Ray& ray, Hit& hit, float tMin) const {
            bool isHit = false;
            for (int i=0; i<numObjects; i++) {
                if (group[i]->intersect(ray, hit, tMin)) {
                    isHit = true;
                }
            }

            return isHit;
        }
    private:
        int numObjects;
        Object3D **group;
};

#endif
