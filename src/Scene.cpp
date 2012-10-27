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

#include "Scene.h"

Scene::Scene() {}

//! Adding active ligth into scene
void Scene::addLight(Light l)
{
  lights.push_back(l);
}

//! Adding renderable object into scene
void Scene::addObject(Object o)
{
  objects.push_back(o);
}

//! Get list of all lights
std::vector<Light>& Scene::getLights()
{
  return lights;
}

//! Get list of all renderable objects
std::vector<Object>& Scene::getObjects()
{
  return objects;
}

//! Get number of all renderable objects
unsigned int Scene::getObjectCount()
{
  return objects.size();
}

//! Get number of all light sources
unsigned int Scene::getLightCount()
{
  return lights.size();
}

//! Get the scene background color
Color& Scene::getBackgroundColor()
{
  return backgroundColor;
}

//! Background color setter
void Scene::setBackgroundColor(const Color& col)
{
  backgroundColor = col;
}
