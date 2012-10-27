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
#ifndef RAY_H
#define RAY_H

#include "Vector.h"

//! A Ray intersecting with scene geometry
class Ray
{
public:
  //! Basic constructor
  Ray();
  //! Primary constructor
  /*!
    \param m_origin - point of origin
    \param m_direction - ray direction vector
  */
  Ray(const Vector& m_origin, const Vector& m_direction);

  //! Origin point accessor
  Vector getOrigin();
  //! Direction vector accessor
  Vector getDirection();
  //! Point of origin setter
  void setOrigin(const Vector& n_orig);
  //! Direction vector setter
  void setDirection(const Vector& n_dir);

private:
  Vector origin;    /*!< Point of origin */
  Vector direction; /*!< Direction vector */
};

#endif // RAY_H
