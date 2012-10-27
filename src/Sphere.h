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
#ifndef SPHERE_H
#define SPHERE_H

#include "Ray.h"
#include "Shape.h"

class Sphere : public Shape
{
public:
  //! Basic constructor
  Sphere();
  //! Primary constructor
  /*!
    \param center - Sphere center point
    \param radius - Sphere radius (in world units)
  */
  Sphere(const Vector& center, double radius);
  //! Intersection with given ray
  /*!
    \param ray - Ray to intersect with
    \param t - current closest intersection point of given ray
    Return value is true if ray intersects with sphere and the intersection is
    closer than current t.
  */
  bool intersect(Ray& ray, double& t);
  //! Normal at given point computation
  /*!
    \param poi - Point of intersection at which the normal is needed
  */
  Vector getNormal(const Vector& poi);
protected:
private:
  Vector c; /*!< Center point */
  double r; /*!< Radius */
};

#endif // SPHERE_H
