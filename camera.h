#ifndef CAMERA_H_
#define CAMERA_H_

#include "ray.h"

#define _USE_MATH_DEFINES
#include <cmath>
#include <cfloat>

class Camera {
    public:
        virtual Ray generateRay(const Vector2f& pt) const = 0;
        virtual float getTMin() const = 0;
        virtual ~Camera() {}

    protected:
        Vector3f eye;
        Vector3f direction;
        Vector3f up;
        Vector3f horizontal;
};

class PerspectiveCamera : public Camera {
    public:
        PerspectiveCamera(
            const Vector3f& eye,
            const Vector3f& lookAt,
            const Vector3f& up,
            float angle
        ) {
            this->eye = eye;
            Vector3f w = lookAt - eye;
            Vector3f u = Vector3f::cross(w, up);
            Vector3f v = Vector3f::cross(u, w);

            this->direction = w.normalized();
            this->horizontal = u.normalized();
            this->up = v.normalized();

            this->angle = angle;
            this->distanceToScreen = 1.0 / tanf(degreeToRadians(angle) / 2);
        }

        virtual float getTMin() const {
            return 0;
        }

        virtual Ray generateRay(const Vector2f& pt) const {
            Vector3f dir = this->distanceToScreen * this->direction + pt[0] * this->horizontal + pt[1] * this->up;
            return Ray(eye, dir.normalized());
        }
    private:
        float angle;
        float distanceToScreen;
        float degreeToRadians(float angle) { return (3.1415926 * angle) / 180.0; }
};

/**
class DofCamera : public Camera {
    public:
        DofCamera(
            const Vector3f& eye,
            const Vector3f& lookAt,
            const Vector3f& up,
            float angle,
            float aperture,
            float distanceToFocus
        ) {
            this->eye = eye;
            Vector3f w = lookAt - eye;
            Vector3f u = Vector3f::cross(w, up);
            Vector3f v = Vector3f::cross(u, w);

            this->direction = w.normalized();
            this->horizontal = u.normalized();
            this->up = v.normalized();

            lensRadius = aperture / 2.0;

            this->angle = angle;
            this->distanceToScreen = 1.0 / tanf(degreeToRadians(angle) / 2);
        }

        virtual float getTMin() const {
            return 0;
        }

        virtual Ray generateRay(const Vector2f& pt) const {
            Vector3f dir = this->distanceToScreen * this->direction + pt[0] * this->horizontal + pt[1] * this->up;
            Vector2f rnd = randomUnitDisk() * lensRadius;
            Vector3f offset = this->horizontal * rnd.x() + this->up * rnd.y();
            return Ray((eye - offset), (dir - eye - offset).normalized());
        }
    private:
        float angle;
        float lensRadius;
        float distanceToScreen;

        float degreeToRadians(float angle) { return (3.1415926 * angle) / 180.0; }
        Vector2f randomUnitDisk() {
            Vector2f p;
            do {
                p = 2.0 * Vector2f(drand48(), drand48()) - Vector2f(1, 1);
            } while (p.absSquared() <= 1);
            return p;
        }
};
**/

#endif
