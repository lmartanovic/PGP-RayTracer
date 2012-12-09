/******************************************************************************
* PGP Project - Ray Tracer with Adaptive Subsampling - Vector.h               *
*******************************************************************************
* Contents                                                                    *
* --------                                                                    *
* - Matrix - class representing a 4x4 matrix.                                 *
*                                                                             *
*******************************************************************************
* Author                                                                      *
* ------                                                                      *
* Lukáš Martanovič (xmarta00@stud.fit.vutbr.cz)                               *
*                                                                             *
* 09.12.2012                                                                  *
*                                                                             *
*******************************************************************************
* This software is not copyrighted.                                           *
*                                                                             *
* This source code is offered for use in the public domain.                   *
* You may use, modify or distribute it freely.                                *
*                                                                             *
******************************************************************************/

#ifndef MATRIX_H
#define MATRIX_H

#include "Vector.h"

class Matrix
{
public:
  //! Constructor
  Matrix();
  //! Destructor
  virtual ~Matrix();

  //! Matrix inversion
  void invert();
  //! Vector transformation
  /*!
    @param v - Vector to be transformed
  */
  Vector transform(Vector & v);

  double cell[16];  /*!< Matrix cells. */
};

#endif // MATRIX_H
