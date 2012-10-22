/******************************************************************************
* PGP Project - Ray Tracer with Adaptive Subsampling - Vector.h               *
*******************************************************************************
* Contents                                                                    *
* --------                                                                    *
* - Vector - class representing a three-dimensional vector.                   *
*                                                                             *
*******************************************************************************
* Author                                                                      *
* ------                                                                      *
* Lukáš Martanovič (xmarta00@stud.fit.vutbr.cz)                               *
*                                                                             *
* 22.10.2012                                                                  *
*                                                                             *
*******************************************************************************
* This software is not copyrighted.                                           *
*                                                                             *
* This source code is offered for use in the public domain.                   *
* You may use, modify or distribute it freely.                                *
*                                                                             *
******************************************************************************/

#ifndef VECTOR_H
#define VECTOR_H
//std lib
#include <iostream> //ostream

//! Three-dimensional vector
class Vector
{
public:
    //! Basic constructor
    Vector();
    //! Primary constructor
    /*!
      \param xx - x dimension
      \param yy - y dimension
      \param zz - z dimension
    */
    Vector(double xx, double yy, double zz);
    //! Computes length of the vector
    double length();
    //! Normalizes the vector (unit length)
    Vector& normalize();

    Vector& operator+=(const Vector& v);
    Vector& operator-=(const Vector& v);
    Vector& operator*=(double k);
    Vector& operator*=(const Vector& v);
    double x;   /*!< X dimension */
    double y;   /*!< Y dimension */
    double z;   /*!< Z dimension */
};

//! Vector addition operator
inline Vector operator+(const Vector& a, const Vector& b)
{
  return Vector(a.x + b.x, a.y + b.y, a.z + b.z);
}

//! Vector subtraction operator
inline Vector operator-(const Vector& a, const Vector& b)
{
  return Vector(a.x - b.x, a.y - b.y, a.z - b.z);
}

//! Vector-vector multiplication operator
inline Vector operator*(const Vector& a, const Vector& b)
{
  return Vector(a.x*b.x, a.y*b.y, a.z*b.z);
}

//! Vector-scalar multiplication operator
inline Vector operator*(const Vector& a, double k)
{
  return Vector(a.x*k, a.y*k, a.z*k);
}

//! Scalar-vector multiplication operator
inline Vector operator*(double k, const Vector& a)
{
  return Vector(a.x*k, a.y*k, a.z*k);
}

//! Vector dot product
inline double dot(const Vector& a, const Vector& b)
{
  return a.x*b.x + a.y*b.y + a.z*b.z;
}

//! Vector cross product
inline Vector cross(const Vector& a, const Vector& b)
{
  return Vector(a.y*b.z - a.z*b.y,
                a.z*b.x - a.x*b.z,
                a.x*b.y - a.y*b.x);
}

//! Print-out (debugging purposes only)
inline std::ostream& operator<<(std::ostream& stream, const Vector& v)
{
  stream << v.x << ", ";
  stream << v.y << ", ";
  stream << v.z;
  return stream;
}

#endif // VECTOR_H
