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

using namespace std;

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

//! Output image setter
void Scene::setOutputImage(const sf::Image& img)
{
  outputImg = img;
}

//! Main raytracing method
Color Scene::trace(Ray & r, double rIndex, int depth)
{
  Color outColor;
  //check if ray intersects with geometry
  double t = -1;
  int ip = MISS;
  Object* intersected = NULL; //intersected object holder
  //get nearest intersecting object
  for(vector<Object>::iterator o = objects.begin(); o != objects.end(); o++)
  {
    if((ip = (*o).getShape()->intersect(r, t)) != MISS)
    {
      intersected = &(*o);
    }
  }
  //get an intersection or store background color
  if(intersected == NULL) outColor += backgroundColor;
  else{
    //add ambient color
    outColor += intersected->getMaterial().getAmbientColor();
    //get intersection point
    Vector PoI = r.getOrigin() + r.getDirection()*t;
    //check if intersection is not occluded from lights
    Vector li, N, R, L, V;
    Ray ri;
    for(vector<Light>::iterator l = lights.begin(); l != lights.end(); l++)
    {
      //get a direction towards the light and set up shadow ray
      li = (*l).getPosition() - PoI;
      li.normalize();
      ri.setOrigin(PoI + li*EPSILON);
      ri.setDirection(li);
      //check if occluded - if not, compute lights color contribution
      if(!inShadow(ri, intersected))
      {
        //compute normal
        N = intersected->getShape()->getNormal(PoI);
        //if there is reflectance - get reflected values
        double reflected = intersected->getMaterial().getReflectance();
        if(reflected > 0.0 && depth < MAX_DEPTH)
        {
          //compute reflected ray
          R = r.getDirection() - 2.0*dot(r.getDirection(),N)*N;
          Ray rr = Ray(PoI + R*EPSILON, R);
          outColor += reflected * intersected->getMaterial().getDiffuseColor()*trace(rr, rIndex, depth+1);
        }
        //compute refracted
        double refracted = intersected->getMaterial().getRefractance();
        if(refracted > 0.0 && depth < MAX_DEPTH)
        {
          //compute refracted ray
          double refIndex = intersected->getMaterial().getRefractionIndex();
          double n = rIndex/refIndex;
          //N *= ip; //if inside the primitive - flip normal
          double cosI = -dot(N, r.getDirection());
          double cosT2 = 1.0 - n*n*(1.0-cosI*cosI);
          if(cosT2 > 0.0)
          {
            //compute refracted ray
            Vector T = (n*r.getDirection()) + (n*cosI - sqrtf(cosT2)) * N;
            Ray refR = Ray(PoI + T*EPSILON, T);
            outColor += refracted * trace(refR, refIndex, depth+1);
          }
          //N *= ip;
        }
        //compute color at this level
        // get light vector
        L = -1*li;
        //lightness level
        double dd = dot(N,L);
        //if any, add diffuse component
        if(dd > 0)
        {
          outColor += intersected->getMaterial().getDiffuseColor()
                        * intersected->getMaterial().getDiffuseIntensity()
                        * (*l).getDiffuseColor()
                        *dd;
        }
        //get View vector
        V = -1*r.getDirection();
        R = L - 2.0*dot(L,N) * N;
        //compute shininess
        dd = dot(V,R);
        //if any, add specular component
        if(dd > 0)
        {
          double spec = powf(dd,intersected->getMaterial().getShininess());
          outColor += spec * intersected->getMaterial().getSpecularColor();
        }
      }
    }//for lights
  }
  return outColor;
}

//! Shadow ray tracing
bool Scene::inShadow(Ray & r, Object* o)
{
  double t = -1;
  //check for intersection with scene geometry
  for(vector<Object>::iterator j = objects.begin(); j != objects.end(); j++)
  {
    if(&(*j) != o)
    if((*j).getShape()->intersect(r, t))
    {
      //stop search
      return true;
    }
  }
  //if no intersection
  return false;
}
