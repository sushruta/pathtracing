#ifndef VECTOR_2F_H
#define VECTOR_2F_H

#include <cmath>

class Vector3f;

class Vector2f {
    public:
        static const Vector2f ZERO;
        static const Vector2f UP;
        static const Vector2f RIGHT;

        Vector2f(float f = 0.0f);
        Vector2f(float x, float y);

        // copy constructor
        Vector2f(const Vector2f& rv);

        // assignment operator
        Vector2f& operator = (const Vector2f& rv);

        // return the ith element
        const float& operator[] (int i) const;
        float& operator[] (int i);

        float& x();
        float& y();

        float x() const;
        float y() const;

        Vector2f xy() const;
        Vector2f yx() const;
        Vector2f xx() const;
        Vector2f yy() const;

        // normal -- (-y, x)
        Vector2f normal() const;

        float abs() const;
        float absSquared() const;
        void normalize();
        Vector2f normalized() const;

        void negate();
        Vector2f negated() const;

        // utility methods
        operator const float* () const; // type conversion for openGL
        operator float* ();
        void print() const;

        Vector2f& operator += (const Vector2f& v);
        Vector2f& operator -= (const Vector2f& v);
        Vector2f& operator *= (float f);

        static float dot(const Vector2f& v0, const Vector2f& v1);

        static Vector3f cross(const Vector2f& v0, const Vector2f& v1);

        static Vector2f lerp(const Vector2f& v0, const Vector2f& v1, float alpha);

    private:
        float m_elements[2];
};

// component wise operators
Vector2f operator + (const Vector2f& v0, const Vector2f& v1);
Vector2f operator - (const Vector2f& v0, const Vector2f& v1);
Vector2f operator * (const Vector2f& v0, const Vector2f& v1);
Vector2f operator / (const Vector2f& v0, const Vector2f& v1);

// unary negation
Vector2f operator - (const Vector2f& v);

// multiply by scalar
Vector2f operator * (float f, const Vector2f& v);
Vector2f operator * (const Vector2f& v, float f);
Vector2f operator / (const Vector2f& v, float f);

bool operator == (const Vector2f& v0, const Vector2f& v1);
bool operator != (const Vector2f& v0, const Vector2f& v1);

#endif
