/******************************************************************************
* PGP Project - Ray Tracer with Adaptive Subsampling - Vector.h               *
*******************************************************************************
* Contents                                                                    *
* --------                                                                    *
* - Material - class representing object material properties for Phong        *
               lighting model.                                                *
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
#ifndef MATERIAL_H
#define MATERIAL_H

#include "Color.h"

class Material
{
public:
  //! constructor
  Material();

  //! Ambient color component accessor
  Color& getAmbientColor();
  //! Diffuse color component accessor
  Color& getDiffuseColor();
  //! Specular color component accessor
  Color& getSpecularColor();
  //! Reflectance value accessor
  double getReflectance();
  //! Refractance value accessor
  double getRefractance();
  //! Shininess intensity accessor
  double getShininess();
  //! Ambient color component setter
  void setAmbientColor(const Color& col);
  //! Diffuse color component setter
  void setDiffuseColor(const Color& col);
  //! Specular color component setter
  void setSpecularColor(const Color& col);
  //! Reflectance factor setter
  void setReflectance(double refl);
  //! Refractance factor setter
  void setRefractance(double refr);
  //!Shininess intensity setter
  void setShininess(double shin);

private:
  Color ambientColor;   /*!< Ambient color component */
  Color diffuseColor;   /*!< Diffuse color component */
  Color specularColor;  /*!< Specular color component */
  double reflectance;   /*!< Reflectance factor 0.0 - 1.0 */
  double refractance;   /*!< Refractance factor */
  double shininess;     /*!< Shininess intensity */
};

#endif // MATERIAL_H
