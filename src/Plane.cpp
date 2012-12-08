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

#include "Plane.h"

//! Basic constructor
Plane::Plane()
{
  //ctor
}

//! Primary constructor
Plane::Plane(const Vector& n, double distFromOrigin)
: normal(n),
  d(distFromOrigin)
{
  normal *= -1;
  normal.normalize();
  //d = dot(normal, origin);
}

//! Intersection with given ray
int Plane::intersect(Ray& ray, double& t)
{
  double np = dot(normal, ray.getDirection());
  if(np != 0)
  {
    double t0 = -(d + dot(normal, ray.getOrigin())) / np;

    if(t0 > 0.0)
    {
      if(t0 < t) //this is first tested object or closer then previous
      {
        t = t0;
        return HIT;
      }
    }
  }
  return MISS;
}

//! Normal accessor
Vector Plane::getNormal(const Vector& poi)
{
  return normal;
}
