/******************************************************************************
* PGP Project - Ray Tracer with Adaptive Subsampling - Vector.cpp             *
*******************************************************************************
* Contents                                                                    *
* --------                                                                    *
* - Plane - Basic geometry primitive - plane.                               *
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

#ifndef PLANE_H
#define PLANE_H

#include "Shape.h"

class Plane : public Shape
{
public:
  //! Basic constructor
  Plane();
  //! Priamry constructor
  /*!
    \param n - plane normal
    \param distFromOrigin - distance from origin
  */
  Plane(const Vector& n, double distFromOrigin);

  //! Intersection with given ray
  int intersect(Ray& ray, double& t);
  //! Normal accessor
  Vector getNormal(const Vector& poi);

private:
  Vector normal;  /*!< Plane normal */
  double d;       /*!< Distance from origin */
};

#endif // PLANE_H
