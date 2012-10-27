/******************************************************************************
* PGP Project - Ray Tracer with Adaptive Subsampling - main.cpp               *
*******************************************************************************
* Contents                                                                    *
* --------                                                                    *
* - Program entry point - early debugging                                     *
*                                                                             *
*******************************************************************************
* Author                                                                      *
* ------                                                                      *
* Lukáš Martanovič (xmarta00@stud.fit.vutbr.cz)                               *
*                                                                             *
* 22.10.2012                                                                  *
*                                                                             *
*******************************************************************************
* This software is not copyrighted.                                           *
*                                                                             *
* This source code is offered for use in the public domain.                   *
* You may use, modify or distribute it freely.                                *
*                                                                             *
******************************************************************************/

#include <iostream>
#include <vector>

#include "Color.h"
#include "Light.h"
#include "Object.h"
#include "Plane.h"
#include "Ray.h"
#include "Scene.h"
#include "Sphere.h"
#include "Vector.h"
#include <SFML/Graphics.hpp>

#define SCR_WIDTH 800
#define SCR_HEIGHT 600

using namespace std;

int main()
{
  sf::Image image;
  image.create(SCR_WIDTH, SCR_HEIGHT);

  double m_SX, m_SY;
  double m_WX1 = -4, m_WX2 = 4, m_WY1 = m_SY = 3, m_WY2 = -3;
  double m_DX = (m_WX2 - m_WX1) / SCR_WIDTH;
	double m_DY = (m_WY2 - m_WY1) / SCR_HEIGHT;

  Vector cameraPos(0.0, 0.0, -5.0);
  //scene
  Sphere s1(Vector(1.0, -0.8, 3.0), 2.5);
  Sphere s2(Vector(-5.5, -0.5, 7.0), 2.0);
  Plane p1(Vector(0.0, 1.0, 0.0), Vector(0.0, -4.4, 0.0));

  Material mat1;
  mat1.setDiffuseColor(Color(0.7, 0.7, 0.7));
  mat1.setSpecularColor(Color(0.7, 0.7, 0.7));
  mat1.setShininess(20.0);
  Material mat2;
  mat2.setDiffuseColor(Color(0.7, 0.7, 1.0));
  mat2.setDiffuseIntensity(0.1);
  mat2.setSpecularColor(Color(0.7, 0.7, 0.7));
  mat2.setShininess(20.0);
  Material mat3;
  mat3.setDiffuseColor(Color(0.4, 0.3, 0.3));

  //sphere1
  Object sp1;
  sp1.setShape(s1);
  sp1.setMaterial(mat1);
  //sphere2
  Object sp2;
  sp2.setShape(s2);
  sp2.setMaterial(mat2);
  //plane
  Object sp3;
  sp3.setShape(p1);
  sp3.setMaterial(mat3);
  Object* intersected = NULL;

  Light light1;
  light1.setPosition(Vector(0.0, 5.0, 5.0));
  light1.setDiffuseColor(Color(0.6, 0.6, 0.6));
  Light light2;
  light2.setPosition(Vector(2.0, 5.0, 1.0));
  light1.setDiffuseColor(Color(0.7, 0.7, 0.9));

  Scene scene;
  scene.addObject(sp1);
  scene.addObject(sp2);
  scene.addObject(sp3);
  scene.addLight(light1);
  scene.addLight(light2);

  for(int y = 0; y < SCR_HEIGHT; y++)
  {
    m_SX = m_WX1;
    for(int x = 0; x < SCR_WIDTH; x++)
    {
      Color finalColor;
      Vector dir = Vector(m_SX, m_SY, 0.0) - cameraPos;
      dir.normalize();
      Ray r = Ray(cameraPos, dir);
      double t = -1;
      intersected = NULL;
      //get nearest intersecting object
      vector<Object> objcts = scene.getObjects();
      for(vector<Object>::iterator i = objcts.begin(); i != objcts.end(); i++)
      {
        if((*i).getShape()->intersect(r, t))
        {
          intersected = &(*i);
        }
      }
      //compute color
      if(intersected == NULL)
      {
        finalColor += scene.getBackgroundColor();
      }
      else{
        //add material ambient component
        finalColor += intersected->getMaterial().getAmbientColor();
        //compute intersection point
        Vector PoI = r.getOrigin() + r.getDirection()*t;
        //get normal
        Vector N = intersected->getShape()->getNormal(PoI);

        vector<Light> ls = scene.getLights();
        for(vector<Light>::iterator i = ls.begin(); i != ls.end(); i++)
        {
          //get light vector
          Vector L = PoI - (*i).getPosition();
          L.normalize();
          //compute lightness factor
          double dd = dot(N,L);
          //if any, add lights contribution
          if(dd > 0)
          {
            finalColor += intersected->getMaterial().getDiffuseColor()
                          * intersected->getMaterial().getDiffuseIntensity()
                          * (*i).getDiffuseColor()
                          *dd;
          }
          Vector V = -1*r.getDirection();
          Vector R = L - 2.0*dot(L,N) * N;
          dd = dot(V,R);
          if(dd > 0)
          {
            double spec = powf(dd,intersected->getMaterial().getShininess());
            finalColor += spec * intersected->getMaterial().getSpecularColor();
          }
        }
      }

      sf::Color col(finalColor.r*255,
                    finalColor.g*255,
                    finalColor.b*255);
      image.setPixel(x,y,col);
      m_SX += m_DX;
    }
    m_SY += m_DY;
  }
  image.saveToFile("result.png");
  return 0;
}
