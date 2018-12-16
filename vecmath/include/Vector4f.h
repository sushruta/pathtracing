#ifndef VECTOR_4F_H
#define VECTOR_4F_H

#include <cmath>

class Vector2f;
class Vector3f;

class Vector4f {
    public:
        Vector4f(float f = 0.0f);
        Vector4f(float x, float y, float z, float w);
        Vector4f(float buffer[4]);

        Vector4f(const Vector2f& xy, float z, float w);
        Vector4f(float x, const Vector2f& yz, float w);
        Vector4f(float x, float y, const Vector2f& zw);
        Vector4f(const Vector2f& xy, const Vector2f& zw);

        Vector4f(const Vector3f& xyz, float w);
        Vector4f(float x, const Vector3f& yzw);

        // copy constructor
        Vector4f(const Vector4f& rv);

        // assignment operator
        Vector4f& operator = (const Vector4f& rv);

        // return the ith element
        const float& operator[] (int i) const;
        float& operator[] (int i);

        float& x();
        float& y();
        float& z();
        float& w();

        float x() const;
        float y() const;
        float z() const;
        float w() const;

        Vector2f xy() const;
        Vector2f yz() const;
        Vector2f zw() const;
        Vector2f wx() const;

        Vector3f xyz() const;
        Vector3f yzw() const;
        Vector3f zwx() const;
        Vector3f wxy() const;

        Vector3f xyw() const;
        Vector3f yzx() const;
        Vector3f zwy() const;
        Vector3f wxz() const;
        
        float abs() const;
        float absSquared() const;
        void normalize();
        Vector4f normalized() const;

        void negate();
        Vector4f negated() const;

        void homogenize();
        Vector4f homogenized() const;

        // utility methods
        operator const float* () const; // type conversion for openGL
        operator float* ();
        void print() const;

        Vector4f& operator += (const Vector4f& v);
        Vector4f& operator -= (const Vector4f& v);
        Vector4f& operator *= (float f);

        static float dot(const Vector4f& v0, const Vector4f& v1);

        static Vector4f lerp(const Vector4f& v0, const Vector4f& v1, float alpha);

    private:
        float m_elements[4];
};

// component wise operators
Vector4f operator + (const Vector4f& v0, const Vector4f& v1);
Vector4f operator - (const Vector4f& v0, const Vector4f& v1);
Vector4f operator * (const Vector4f& v0, const Vector4f& v1);
Vector4f operator / (const Vector4f& v0, const Vector4f& v1);

// unary negation
Vector4f operator - (const Vector4f& v);

// multiply by scalar
Vector4f operator * (float f, const Vector4f& v);
Vector4f operator * (const Vector4f& v, float f);
Vector4f operator / (const Vector4f& v, float f);

bool operator == (const Vector4f& v0, const Vector4f& v1);
bool operator != (const Vector4f& v0, const Vector4f& v1);

#endif
