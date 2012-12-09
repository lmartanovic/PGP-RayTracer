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
#include "Matrix.h"

//! Constructor
Matrix::Matrix()
{
  //construct identity matrix
  cell[1] = cell[2] = cell[3] = cell[4] = cell[6] = cell[7] =
  cell[8] = cell[9] = cell[11] = cell[12] = cell[13] = cell[14] = 0;
  //diagonal 1
  cell[0] = cell[5] = cell[10] = cell[15] = 1;
}

//! Destructor
Matrix::~Matrix()
{
  //dtor
}

//! Matrix inversion
void Matrix::invert()
{
  //auxiliary helper matrix
  Matrix t;

  double tx = -cell[3];
  double ty = -cell[7];
  double tz = -cell[11];
  //invert into helper matrix top 3x3
  for(int h = 0; h < 3; h++)
  {
    for(int v = 0; v < 3; v++)
    {
      t.cell[h + v * 4] = cell[v + h * 4];
    }
  }
  //copy back
  for(int i = 0; i < 11; i++)
    cell[i] = t.cell[i];
  //rightmost column
  cell[3] = tx * cell[0] + ty * cell[1] + tz * cell[2];
  cell[7] = tx * cell[4] + ty * cell[5] + tz * cell[6];
  cell[11] = tx * cell[8] + ty * cell[9] + tz * cell[10];
}

//! Vector transformation
Vector Matrix::transform(Vector & v)
{
  double x  = cell[0] * v.x + cell[1] * v.y + cell[2] * v.z + cell[3];
	double y  = cell[4] * v.x + cell[5] * v.y + cell[6] * v.z + cell[7];
	double z  = cell[8] * v.x + cell[9] * v.y + cell[10] * v.z + cell[11];
  return Vector(x, y, z);
}
