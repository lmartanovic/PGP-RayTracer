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
#include "Vector.h"
#include "Object.h"
#include "Ray.h"
#include "Sphere.h"
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
  Sphere s1(Vector(0.0, 0.5, 1.0), 1.0);
  Sphere s2(Vector(-2, -1.5, 1.0), 1.0);
  Sphere s3(Vector(1, 1.5, 0.5), 0.75);

  Material mat1;
  mat1.setDiffuseColor(Color(1.0, 0.0, 0.0));
  Material mat2;
  mat2.setDiffuseColor(Color(0.0, 1.0, 0.0));
  Material mat3;
  mat3.setDiffuseColor(Color(0.0, 0.0, 1.0));

  Object sp1;
  sp1.setShape(s1);
  sp1.setMaterial(mat1);
  Object sp2;
  sp2.setShape(s2);
  sp2.setMaterial(mat2);
  Object sp3;
  sp3.setShape(s3);
  sp3.setMaterial(mat3);
  Object* intersected = NULL;

  Vector light(-1.0, -1.0, -1.0);

  vector<Object> scene;
  scene.push_back(sp1);
  scene.push_back(sp2);
  scene.push_back(sp3);

  for(int y = 0; y < SCR_HEIGHT; y++)
  {
    m_SX = m_WX1;
    for(int x = 0; x < SCR_WIDTH; x++)
    {
      Vector dir = Vector(m_SX, m_SY, 0.0) - cameraPos;
      dir.normalize();
      Ray r = Ray(cameraPos, dir);
      double t = -1;
      intersected = NULL;
      //get nearest intersecting object
      for(vector<Object>::iterator i = scene.begin(); i != scene.end(); i++)
      {
        if((*i).getShape()->intersect(r, t))
        {
          intersected = &(*i);
        }
      }
      //compute color
      if(intersected == NULL) image.setPixel(x,y,sf::Color(0,0,0));
      else{
        Vector PoI = r.getOrigin() + r.getDirection()*t;
        Vector L = PoI - light;
        L.normalize();
        Vector N = intersected->getShape()->getNormal(PoI);
        double dd = dot(N,L);
        if(dd > 0)
        {
          double factor = 255*dd;
          Color cc = intersected->getMaterial().getDiffuseColor();
          sf::Color col(cc.r*factor, cc.g*factor,cc.b*factor);
          image.setPixel(x,y, col);
        }
      }
      m_SX += m_DX;
    }
    m_SY += m_DY;
  }
  image.saveToFile("result.png");
  return 0;
}
