/******************************************************************************
* PGP Project - Ray Tracer with Adaptive Subsampling - Vector.h               *
*******************************************************************************
* Contents                                                                    *
* --------                                                                    *
* - Object - class representing complete object with geometry and material    *
*            properties ready to be set into scene and rendered.              *
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
#ifndef OBJECT_H
#define OBJECT_H

#include "Material.h"
#include "Shape.h"

class Object
{
public:
  //! Basic constructor
  Object();
  //! Primary constructor
  /*!
    \param sh - Shape representing object geometry
    \param mat - Object material
  */
  Object(Shape& sh, Material& mat);
  //! Geometry accessor
  Shape* getShape();
  //! Material accessor
  Material& getMaterial();
  //! Geometry setter
  void setShape(Shape& sh);
  //! Material setter
  void setMaterial(Material& mat);

private:
  Shape* shape;       /*!< Object geometry */
  Material material;  /*!< Object material */
};

#endif // OBJECT_H
