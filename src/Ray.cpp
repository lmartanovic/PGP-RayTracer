/******************************************************************************
* PGP Project - Ray Tracer with Adaptive Subsampling - Vector.cpp             *
*******************************************************************************
* Contents                                                                    *
* --------                                                                    *
* - Ray - class representing a ray cast into the scene.                       *
*                                                                             *
*******************************************************************************
* Author                                                                      *
* ------                                                                      *
* Lukáš Martanovič (xmarta00@stud.fit.vutbr.cz)                               *
*                                                                             *
* 27.10.2012                                                                  *
*                                                                             *
*******************************************************************************
* This software is not copyrighted.                                           *
*                                                                             *
* This source code is offered for use in the public domain.                   *
* You may use, modify or distribute it freely.                                *
*                                                                             *
******************************************************************************/
#include "Ray.h"

//! Basic constructor
Ray::Ray()
: origin(0.0, 0.0, 0.0),
  direction(0.0, 0.0, 0.0)
{}

//! Primary constructor
Ray::Ray(const Vector& m_origin, const Vector& m_direction)
: origin(m_origin),
  direction(m_direction)
{}

//! Point of origin accessor
Vector Ray::getOrigin()
{
  return origin;
}

//! Direction vector accessor
Vector Ray::getDirection()
{
  return direction;
}

//! Point of origin setter
void Ray::setOrigin(const Vector& n_orig)
{
  origin = n_orig;
}

//! Direction vector setter
void Ray::setDirection(const Vector& n_dir)
{
  direction = n_dir;
}
