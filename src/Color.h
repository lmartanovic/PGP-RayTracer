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
#ifndef COLOR_H
#define COLOR_H

class Color
{
public:
  //! Basic constructor
  Color();
  //! Primary constructor
  /*!
    \param rr - red component
    \param gg - green component
    \param bb - blue component
  */
  Color(double rr, double gg, double bb);

  //! In-place constant value multiplication operator
  Color& operator*=(double k);
  //! In place color addition operator
  Color& operator+=(const Color& col);

  double r; /*!< Red component */
  double g; /*!< Green component */
  double b; /*!< Blue component */
};

//! Color addition
inline Color operator+(const Color& c1, const Color& c2)
{
  return Color(c1.r + c2.r, c1.g + c2.g, c1.b + c2.b);
}

//! Color subtraction
inline Color operator-(const Color& c1, const Color& c2)
{
  return Color(c1.r - c2.r, c1.g - c2.g, c1.b - c2.b);
}

//! Color-Color multiplication
inline Color operator*(const Color& c1, const Color& c2)
{
  return Color(c1.r*c2.r, c1.g*c2.g, c1.b*c2.b);
}

//! Color-constant value multiplication - left
inline Color operator*(double k, const Color& c)
{
  return Color(k * c.r, k * c.g, k * c.b);
}

//! Color-constant value multiplication - right
inline Color operator*(const Color& c, double k)
{
  return Color(k * c.r, k * c.g, k * c.b);
}

#endif // COLOR_H
