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
#include "Object.h"

//! Basic constructor
Object::Object()
: shape(NULL),
  material()
{}

//! Primary constructor
Object::Object(Shape& sh, Material& mat)
: shape(&sh),
  material(mat)
{}

//! Geometry accessor
Shape* Object::getShape()
{
  return shape;
}

//! Material accessor
Material& Object::getMaterial()
{
  return material;
}

//! Geometry setter
void Object::setShape(Shape& sh)
{
  shape = &sh;
}

//! Material setter
void Object::setMaterial(Material& mat)
{
  material = mat;
}
