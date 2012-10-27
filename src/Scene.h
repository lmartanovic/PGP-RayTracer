/******************************************************************************
* PGP Project - Ray Tracer with Adaptive Subsampling - Vector.h               *
*******************************************************************************
* Contents                                                                    *
* --------                                                                    *
* - Scene - Very basic scene representation - list of all objects and lights. *
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
#ifndef SCENE_H
#define SCENE_H

#include <vector>

#include "Color.h"
#include "Light.h"
#include "Object.h"

class Scene
{
public:
  Scene();
  //! Adding active ligth into scene
  void addLight(Light l);
  //! Adding renderable object into scene
  void addObject(Object o);
  //! Get list of all lights
  std::vector<Light>& getLights();
  //! Get list of all renderable objects
  std::vector<Object>& getObjects();
  //! Get number of all renderable objects
  unsigned int getObjectCount();
  //! Get number of all light sources
  unsigned int getLightCount();
  //! Get the scene background color
  Color& getBackgroundColor();
  //! Background color setter
  void setBackgroundColor(const Color& col);
private:
  std::vector<Light> lights;    /*!< List of all primary light sources */
  std::vector<Object> objects;  /*!< List of all renderable obects */
  Color backgroundColor;        /*! Default background color */
};

#endif // SCENE_H
