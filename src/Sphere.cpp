#include "Sphere.h"
#include <cmath>
#include <iostream>

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
bool Sphere::intersect(Ray& ray, double& t)
{
  //solve the quadratic equasion given by sphere and ray equasion
  Vector dist = ray.getOrigin() - c;
  double B = dot(ray.getDirection(), dist);
  double D = B*B - dot(dist, dist) + r*r;

  //if there is no real solution (discriminant < 0) - no intersection exists
  if(D < 0.0)
  {
    return false;
  }
  //esle compute intersection points
  double t0 = -B - sqrt(D);
  double t1 = -B + sqrt(D);
  bool ret = false;
  //if the first ip is in front
  if(t0 > 0.01)
  {
    if(t < 0.0 || t0 < t) //this is first tested object or closer then previous
    {
      t = t0;
      ret = true;
    }
  }
  //second ip test
  if(t1 > 0.01)
  {
    if(t < 0.0 || t1 < t) //this is first tested object or closer then previous
    {
      t = t1;
      ret = true;
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
