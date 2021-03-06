#ifndef VECTOR_3F_H
#define VECTOR_3F_H

#include <cmath>

class Vector2f;

class Vector3f {
    public:
        static const Vector3f ZERO;
        static const Vector3f UP;
        static const Vector3f RIGHT;
        static const Vector3f FORWARD;

        Vector3f(float f = 0.0f);
        Vector3f(float x, float y, float z);
        Vector3f(float x, const Vector2f& yz);
        Vector3f(const Vector2f& xy, float z);

        // copy constructor
        Vector3f(const Vector3f& rv);

        // assignment operator
        Vector3f& operator = (const Vector3f& rv);

        // return the ith element
        const float& operator[] (int i) const;
        float& operator[] (int i);

        float& x();
        float& y();
        float& z();

        float x() const;
        float y() const;
        float z() const;

        Vector2f xy() const;
        Vector2f yz() const;
        Vector2f xz() const;

        Vector3f xyz() const;
        Vector3f yzx() const;
        Vector3f zxy() const;
        
        float abs() const;
        float absSquared() const;
        void normalize();
        Vector3f normalized() const;

        void negate();
        Vector3f negated() const;

        Vector2f homogenized() const;

        // utility methods
        operator const float* () const; // type conversion for openGL
        operator float* ();
        void print() const;

        Vector3f& operator += (const Vector3f& v);
        Vector3f& operator -= (const Vector3f& v);
        Vector3f& operator *= (float f);

        static float dot(const Vector3f& v0, const Vector3f& v1);

        static Vector3f cross(const Vector3f& v0, const Vector3f& v1);

        static Vector3f lerp(const Vector3f& v0, const Vector3f& v1, float alpha);

    private:
        float m_elements[3];
};

// component wise operators
Vector3f operator + (const Vector3f& v0, const Vector3f& v1);
Vector3f operator - (const Vector3f& v0, const Vector3f& v1);
Vector3f operator * (const Vector3f& v0, const Vector3f& v1);
Vector3f operator / (const Vector3f& v0, const Vector3f& v1);

// unary negation
Vector3f operator - (const Vector3f& v);

// multiply by scalar
Vector3f operator * (float f, const Vector3f& v);
Vector3f operator * (const Vector3f& v, float f);
Vector3f operator / (const Vector3f& v, float f);

bool operator == (const Vector3f& v0, const Vector3f& v1);
bool operator != (const Vector3f& v0, const Vector3f& v1);

#endif
