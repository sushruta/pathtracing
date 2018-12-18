#ifndef MATERIAL_H_
#define MATERIAL_H_

#include <cassert>

#include "ray.h"
#include "hit.h"

/**
class Material {
    public:
        Material(const Vector3f& dColor, const Vector3f& sColor = Vector3f::ZERO, float s = 0) {
            diffuseColor = dColor;
            specularColor = sColor;
            shininess = s;
        }
        virtual ~Material() {}
    private:
        Vector3f diffuseColor;
        Vector3f specularColor;
        float shininess;
};
**/

class Material {
    public:
        virtual Ray scatter(
            const Ray& in,
            const Hit& hit,
            Vector3f& attentuation
        ) = 0;
};

class Lambertian : public Material {
    public:
        Lambertian(const Vector3f& a) {
            this->albedo = a;
        }

        virtual Ray scatter(
            const Ray& in,
            const Hit& hit,
            Vector3f& attentuation
        ) {
            Vector3f pt = in.pointAtParameter(hit.getT());
            Vector3f target = pt + hit.getNormal().normalized() + randPtUnitSphere();
            attentuation = albedo;
            return Ray(pt, (target - pt).normalized());
        }
    private:
        Vector3f albedo;

        Vector3f randPtUnitSphere() {
            Vector3f p;
            do {
                p = 2 * Vector3f(drand48(), drand48(), drand48()) - Vector3f(1, 1, 1);
            } while (p.absSquared() <= 1);
            return p;
        }
};

class Metal : public Material {
    public:
        Metal(const Vector3f& a) {
            this->albedo = a;
        }

        virtual Ray scatter(
            const Ray& in,
            const Hit& hit,
            Vector3f& attenuation
        ) {
            Vector3f pt = in.pointAtParameter(hit.getT());
            Vector3f reflected = reflect(in.getDirection().normalized(), hit.getNormal().normalized());
            attenuation = albedo;
            return Ray(pt, reflected.normalized());
        }

    private:
        Vector3f albedo;
        Vector3f reflect(const Vector3f& v, const Vector3f n) const {
            return v - 2 * Vector3f::dot(v, n) * n;
        }
};

class Dielectric : public Material {
    public:
        Dielectric(float ri) {
            refractiveIdx = ri;
        }
        virtual Ray scatter(const Ray& in, const Hit& hit, Vector3f& attenuation) {
            
            Vector3f normalizedInDirection = in.getDirection().normalized();
            Vector3f normalizedHitNormal = hit.getNormal().normalized();

             Vector3f outwardNormal;
             Vector3f reflected = reflect(normalizedInDirection, normalizedHitNormal);
             float niOverNt;
             attenuation = Vector3f(1.0, 1.0, 1.0);
             Vector3f refracted;
             float reflectProb;
             float cosine;
             
             if (Vector3f::dot(normalizedInDirection, normalizedHitNormal) > 0) {
                  outwardNormal = normalizedHitNormal.negated();
                  niOverNt = refractiveIdx;
                  cosine = Vector3f::dot(normalizedInDirection, normalizedHitNormal);
                  cosine = sqrt(1 - refractiveIdx * refractiveIdx * (1 - cosine * cosine));
             }
             else {
                  outwardNormal = normalizedHitNormal;
                  niOverNt = 1.0 / refractiveIdx;
                  cosine = -1 * Vector3f::dot(normalizedInDirection, normalizedHitNormal);
             }

             if (refract(normalizedInDirection, outwardNormal, niOverNt, refracted))
                reflectProb = schlick(cosine, refractiveIdx);
             else
                reflectProb = 1.0;

             if (drand48() < reflectProb)
                return Ray(in.pointAtParameter(hit.getT()), reflected);
             return Ray(in.pointAtParameter(hit.getT()), refracted);
        }

    private:
        float refractiveIdx;
        
        Vector3f reflect(const Vector3f& v, const Vector3f n) const { return v - 2 * Vector3f::dot(v, n) * n; }
        
        float schlick(float cosine, float refractiveIdx) {
            float r0 = (1 - refractiveIdx) / (1 + refractiveIdx);
            float r0Times2 = r0 * r0;
            return r0Times2 + (1 - r0Times2) * pow((1 - cosine), 5);
        }

        bool refract(const Vector3f& v, const Vector3f& n, float niOverNt, Vector3f& refracted) {
            Vector3f uv = v.normalized();
            float dt = Vector3f::dot(uv, n);
            float discriminant = 1.0 - niOverNt * niOverNt * (1 - dt * dt);
            if (discriminant > 0) {
                refracted = niOverNt * (uv - n * dt) - n * sqrt(discriminant);
                return true;
            }
            return false;
        }
};

#endif
