/******************************************************************************
* PGP Project - Ray Tracer with Adaptive Subsampling - Vector.cpp             *
*******************************************************************************
* Contents                                                                    *
* --------                                                                    *
* - Shape - Abstract base class for all geometry.                             *
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

#ifndef SHAPE_H
#define SHAPE_H

#include "Ray.h"
#include "Vector.h"

class Shape
{
public:
  //! Intersection with given ray
  virtual bool intersect(Ray& ray, double& t) = 0;
  //! Normal at given point of intersection computation
  virtual Vector getNormal(const Vector& poi) = 0;
};

#endif // SHAPE_H
