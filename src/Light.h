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
#ifndef LIGTH_H
#define LIGTH_H

#include "Color.h"
#include "Vector.h"

class Light
{
public:
  //! Basic constructor
  Light();
  //! Light position accessor
  Vector& getPosition();
  //! Diffuse color component accessor
  Color& getDiffuseColor();
  //! Specular color component accessor
  Color& getSpecularColor();
  //! Light position setter
  void setPosition(const Vector& pos);
  //! Diffuse color component setter
  void setDiffuseColor(const Color& col);
  //! Specular color component setter
  void setSpecularColor(const Color& col);

private:
  Vector position;      /*!< Light position */
  Color diffuseColor(); /*!< Diffuse color component */
  Color specularColor();/*!< Specular color component */
};

#endif // LIGTH_H
