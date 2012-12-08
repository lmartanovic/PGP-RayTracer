/******************************************************************************
* PGP Project - Ray Tracer with Adaptive Subsampling - Vector.cpp             *
*******************************************************************************
* Contents                                                                    *
* --------                                                                    *
* - Sphere - Basic geometry primitive - sphere.                               *
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
#include "Sphere.h"
#include <cmath>

//! Basic constructor
Sphere::Sphere()
: c(0.0,0.0,0.0),
  r(1.0)
{}

//! Primary constructor
Sphere::Sphere(const Vector& center, double radius)
: c(center),
  r(radius)
{}

//! Intersection with given ray
int Sphere::intersect(Ray& ray, double& t)
{
  //solve the quadratic equasion given by sphere and ray equasion
  Vector dist = ray.getOrigin() - c;
  double B = -dot(dist, ray.getDirection());
  double D = B*B - dot(dist, dist) + r*r;
  int ret = MISS;
  //if there is no real solution (discriminant < 0) - no intersection exists
  if(D > 0.0) //compute intersection points
  {
    D = sqrtf(D);
    double t0 = B - D;
    double t1 = B + D;
    //if the first ip is in front
    if(t1 > 0.0)
    {
      if(t0 < 0.0)
      {
        if(t1 < t)
        {
          t = t1;
          ret = INPRIM;
        }
      }else{
        if(t0 < t)
        {
          t = t0;
          ret = HIT;
        }
      }
    }
  }
  return ret;
}

//! Normal at given intersection point
Vector Sphere::getNormal(const Vector& poi)
{
  //compute vector from center to intersection point
  Vector normal = c-poi;
  //normalize it
  normal.normalize();
  return normal;
}
