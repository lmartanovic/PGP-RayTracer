/******************************************************************************
* PGP Project - Ray Tracer with Adaptive Subsampling - Vector.h               *
*******************************************************************************
* Contents                                                                    *
* --------                                                                    *
* - Material - class representing object material properties for Phong        *
*              lighting model.                                                *
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
#include "Material.h"

Material::Material() {}

//! Ambient color component accessor
Color& Material::getAmbientColor()
{
  return ambientColor;
}
//! Diffuse color component accessor
Color& Material::getDiffuseColor()
{
  return diffuseColor;
}
//! Specular color component accessor
Color& Material::getSpecularColor()
{
  return specularColor;
}
//! Reflectance value accessor
double Material::getReflectance()
{
  return reflectance;
}
//! Refractance value accessor
double Material::getRefractance()
{
  return refractance;
}
//! Shininess intensity accessor
double Material::getShininess()
{
  return shininess;
}
//! Ambient color component setter
void Material::setAmbientColor(const Color& col)
{
  ambientColor = col;
}
//! Diffuse color component setter
void Material::setDiffuseColor(const Color& col)
{
  diffuseColor = col;
}
//! Specular color component setter
void Material::setSpecularColor(const Color& col)
{
  specularColor = col;
}
//! Reflectance factor setter
void Material::setReflectance(double refl)
{
  reflectance = refl;
}
//! Refractance factor setter
void Material::setRefractance(double refr)
{
  refractance = refr;
}
//!Shininess intensity setter
void Material::setShininess(double shin)
{
  shininess = shin;
}