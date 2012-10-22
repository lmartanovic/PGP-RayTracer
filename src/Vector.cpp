/******************************************************************************
* PGP Project - Ray Tracer with Adaptive Subsampling - Vector.cpp             *
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

#include "Vector.h"
//std lib
#include <cmath>  //sqrt

//! Basic constructor
Vector::Vector()
: x(0), y(0), z(0)  //Initialize to all zeros
{}

//! Primary constructor
Vector::Vector(double xx, double yy, double zz)
: x(xx),
  y(yy),
  z(zz)
{}

//! Computes length of the vector
double Vector::length()
{
  return sqrt(x*x + y*y + z*z);
}

//! Normalizes the vector (unit length)
Vector& Vector::normalize()
{
  double l = length();
  x = x/l;
  y = y/l;
  z = z/l;
  return *this;
}

//addition
Vector& Vector::operator+=(const Vector& v)
{
  x += v.x;
  y += v.y;
  z += v.z;
  return *this;
}

//subtraction
Vector& Vector::operator-=(const Vector& v)
{
  x -= v.x;
  y -= v.y;
  z -= v.z;
  return *this;
}

//scalar multiplication
Vector& Vector::operator*=(double k)
{
  x *= k;
  y *= k;
  z *= k;
  return *this;
}

//vector multiplication
Vector& Vector::operator*=(const Vector& v)
{
  x *= v.x;
  y *= v.y;
  z *= v.z;
  return *this;
}
