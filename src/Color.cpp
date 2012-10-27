/******************************************************************************
* PGP Project - Ray Tracer with Adaptive Subsampling - Vector.h               *
*******************************************************************************
* Contents                                                                    *
* --------                                                                    *
* - Color - class representing a three-component RGB color.                   *
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
#include "Color.h"

//! Basic constructor
Color::Color()
: r(0.0),
  g(0.0),
  b(0.0)
{}

//! Primary constructor
Color::Color(double rr, double gg, double bb)
: r(rr),
  g(gg),
  b(bb)
{}

//! In-place constant value multiplication operator
Color& Color::operator*=(double k)
{
  r *= k;
  g *= k;
  b *= k;
  return *this;
}
