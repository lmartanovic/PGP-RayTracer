/******************************************************************************
* PGP Project - Ray Tracer with Adaptive Subsampling - Vector.h               *
*******************************************************************************
* Contents                                                                    *
* --------                                                                    *
* - Light - class representing a basic point light.                           *
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
#include "Light.h"

//! Basic constructor
Light::Light()
: position(0.0, 0.0, 0.0),
  diffuseColor(1.0, 1.0, 1.0),
  specularColor(1.0, 1.0, 1.0)
{}

//! Light position accessor
Vector& Light::getPosition()
{
  return position;
}

//! Diffuse color component accessor
Color& Light::getDiffuseColor()
{
  return diffuseColor;
}

//! Specular color component accessor
Color& Light::getSpecularColor()
{
  return specularColor;
}

//! Light position setter
void Light::setPosition(const Vector& pos)
{
  position = pos;
}

//! Diffuse color component setter
void Light::setDiffuseColor(const Color& col)
{
  diffuseColor = col;
}

//! Specular color component setter
void Light::setSpecularColor(const Color& col)
{
  specularColor = col;
}
