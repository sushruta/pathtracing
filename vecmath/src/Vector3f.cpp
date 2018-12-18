#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>

#include "Vector2f.h"
#include "Vector3f.h"

const Vector3f Vector3f::ZERO = Vector3f(0.0f, 0.0f, 0.0f);

const Vector3f Vector3f::UP = Vector3f(0.0f, 1.0f, 0.0f);

const Vector3f Vector3f::RIGHT = Vector3f(1.0f, 0.0f, 0.0f);

const Vector3f Vector3f::FORWARD = Vector3f(0.0f, 0.0f, -1.0f);

Vector3f::Vector3f(float f) {
    m_elements[0] = f;
    m_elements[1] = f;
    m_elements[2] = f;
}

Vector3f::Vector3f(float x, float y, float z) {
    m_elements[0] = x;
    m_elements[1] = y;
    m_elements[2] = z;
}

Vector3f::Vector3f(const Vector2f& xy, float z) {
    m_elements[0] = xy.x();
    m_elements[1] = xy.y();
    m_elements[2] = z;
}

Vector3f::Vector3f(float x, const Vector2f& yz) {
    m_elements[0] = x;
    m_elements[1] = yz.x();
    m_elements[2] = yz.y();
}

Vector3f::Vector3f(const Vector3f& rv) {
    m_elements[0] = rv[0];
    m_elements[1] = rv[1];
    m_elements[2] = rv[2];
}

Vector3f& Vector3f::operator = (const Vector3f& rv) {
    if (this != &rv) {
        m_elements[0] = rv[0];
        m_elements[1] = rv[1];
        m_elements[2] = rv[2];
    }

    return *this;
}

const float& Vector3f::operator [] (int i) const {
    return m_elements[i];
}

float& Vector3f::operator [] (int i) {
    return m_elements[i];
}

float& Vector3f::x() { return m_elements[0]; }

float& Vector3f::y() { return m_elements[1]; }

float& Vector3f::z() { return m_elements[2]; }

float Vector3f::x() const { return m_elements[0]; }

float Vector3f::y() const { return m_elements[1]; }

float Vector3f::z() const { return m_elements[2]; }

Vector2f Vector3f::xy() const { return Vector2f(m_elements[0], m_elements[1]); }
Vector2f Vector3f::yz() const { return Vector2f(m_elements[1], m_elements[2]); }
Vector2f Vector3f::xz() const { return Vector2f(m_elements[0], m_elements[2]); }

Vector3f Vector3f::xyz() const { return Vector3f(m_elements[0], m_elements[1], m_elements[2]); }
Vector3f Vector3f::yzx() const { return Vector3f(m_elements[1], m_elements[2], m_elements[0]); }
Vector3f Vector3f::zxy() const { return Vector3f(m_elements[2], m_elements[0], m_elements[1]); }

float Vector3f::abs() const { return sqrt(absSquared()); }

float Vector3f::absSquared() const {
    return m_elements[0] * m_elements[0] + m_elements[1] * m_elements[1] + m_elements[2] * m_elements[2];
}

void Vector3f::normalize() {
    float norm = abs();
    m_elements[0] /= norm;
    m_elements[1] /= norm;
    m_elements[2] /= norm;
}

Vector3f Vector3f::normalized() const {
    float norm = abs();
    return Vector3f(m_elements[0] / norm, m_elements[1] / norm, m_elements[2] / norm);
}

void Vector3f::negate() {
    m_elements[0] = -m_elements[0];
    m_elements[1] = -m_elements[1];
    m_elements[2] = -m_elements[2];
}

Vector3f Vector3f::negated() const {
    return Vector3f(-m_elements[0], -m_elements[1], -m_elements[2]);
}

Vector3f::operator const float* () const { return m_elements; }

Vector3f::operator float* () { return m_elements; }

void Vector3f::print() const { printf("< %.4f, %.4f, %.4f >\n", m_elements[0], m_elements[1], m_elements[2]); }

Vector3f& Vector3f::operator += (const Vector3f& v) {
    m_elements[0] += v.x();
    m_elements[1] += v.y();
    m_elements[2] += v.z();
    return *this;
}

Vector3f& Vector3f::operator -= (const Vector3f& v) {
    m_elements[0] -= v.x();
    m_elements[1] -= v.y();
    m_elements[2] -= v.z();
    return *this;
}

Vector3f& Vector3f::operator *= (float f) {
    m_elements[0] *= f;
    m_elements[1] *= f;
    m_elements[2] *= f;
    return *this;
}

float Vector3f::dot(const Vector3f& v0, const Vector3f& v1) {
    return v0[0] * v1[0] + v0[1] * v1[1] + v0[2] * v1[2];
}

Vector3f Vector3f::cross(const Vector3f& v0, const Vector3f& v1) {
    return Vector3f
        (
            v0.y() * v1.z() - v0.z() * v1.y(),
            v0.z() * v1.x() - v0.x() * v1.z(),
            v0.x() * v1.y() - v0.y() * v1.x()
        );
}

Vector3f Vector3f::lerp(const Vector3f& v0, const Vector3f& v1, float alpha) {
    return alpha * (v1 - v0) + v0;
}

// operator overloading

Vector3f operator + (const Vector3f& v0, const Vector3f& v1) {
    return Vector3f(v0.x() + v1.x(), v0.y() + v1.y(), v0.z() + v1.z());
}

Vector3f operator - (const Vector3f& v0, const Vector3f& v1) {
    return Vector3f(v0.x() - v1.x(), v0.y() - v1.y(), v0.z() - v1.z());
}

Vector3f operator * (const Vector3f& v0, const Vector3f& v1) {
    return Vector3f(v0.x() * v1.x(), v0.y() * v1.y(), v0.z() * v1.z());
}

Vector3f operator - (const Vector3f& v) {
    return Vector3f(-v.x(), -v.y(), -v.z());
}

Vector3f operator * (float f, const Vector3f& v) {
    return Vector3f(f * v.x(), f * v.y(), f * v.z());
}

Vector3f operator * (const Vector3f& v, float f) {
    return f * v;
}

Vector3f operator / (const Vector3f& v, float f) {
    return Vector3f(v.x() / f, v.y() / f, v.z() / f);
}

bool operator == (const Vector3f& v0, const Vector3f& v1) {
    return (v0.x() == v1.x() && v0.y() == v1.y() && v0.z() == v1.z());
}

bool operator != (const Vector3f& v0, const Vector3f& v1) {
    return !(v0 == v1);
}
