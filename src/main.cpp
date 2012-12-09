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
#include "Matrix.h"
#include "Object.h"
#include "Plane.h"
#include "Ray.h"
#include "Scene.h"
#include "Sphere.h"
#include "Vector.h"
#include <SFML/Graphics.hpp>

#define SCR_WIDTH 800
#define SCR_HEIGHT 600
#define AS_DELTA 32

using namespace std;

//globals originally from main
//position to look at
Vector targetPos(0.0,0.0,0.0);
Vector desiredPos(0.0, 0.0, -3.0);
//camera position
Vector cameraPos(0.0, 0.0, -5.0);
//projection plane corners
Vector C0 = Vector(4.0, -3.0, 0.0);
Vector C1 = Vector(-4.0, -3.0, 0.0);
Vector C2 = Vector(4.0, 3.0, 0.0);
Vector C3 = Vector(-4.0, 3.0, 0.0);
Vector m_DX, m_DY, screenPos;
Scene scene;

//bilinear color interpolation
void interpolateColor(Color** image, Sample* corners, int x, int y, int xx, int yy)
{
  double xkoef1;
  double xkoef2;
  double ykoef1;
  double ykoef2;
  Color R1, R2;
  for(int y0 = y; y0 <= yy; y0++)
  {
    for(int x0 = x; x0 <= xx; x0++)
    {
      xkoef1=((double)xx - (double)x0)/((double)xx - (double)x);
      xkoef2=((double)x0 - (double)x)/((double)xx - (double)x);
      ykoef1=((double)yy - (double)y0)/((double)yy - (double)y);
      ykoef2=((double)y0 - (double)y)/((double)yy - (double)y);
      R1.r = xkoef1*corners[0].c.r + xkoef2*corners[1].c.r;
      R1.g = xkoef1*corners[0].c.g + xkoef2*corners[1].c.g;
      R1.b = xkoef1*corners[0].c.b + xkoef2*corners[1].c.b;

      R2.r = xkoef1*corners[2].c.r + xkoef2*corners[3].c.r;
      R2.g = xkoef1*corners[2].c.g + xkoef2*corners[3].c.g;
      R2.b = xkoef1*corners[2].c.b + xkoef2*corners[3].c.b;

      image[y0][x0].r = ykoef1*R1.r + ykoef2*R2.r;
      image[y0][x0].g = ykoef1*R1.g + ykoef2*R2.g;
      image[y0][x0].b = ykoef1*R1.b + ykoef2*R2.b;
    }
  }
}

//check if corner samples are similar
bool cornersGoodEnough(Sample* corners)
{
  //did we hit the same object?
  if((corners[0].o != corners[3].o) ||
    (corners[1].o != corners[2].o) ||
    (corners[0].o != corners[1].o))
  {
    return false;
  }

  //is shadowing the same?
  if((corners[0].l != corners[3].l) ||
    (corners[1].l != corners[2].l) ||
    (corners[0].l != corners[1].l))
  {
    return false;
  }

  //are diffuse intensities similar?
  if(((corners[0].di - corners[3].di) > 0.05) ||
    ((corners[1].di - corners[2].di) > 0.05) ||
    ((corners[0].di - corners[1].di) > 0.05))
  {
    return false;
  }
  //are specular intensities similar?
  if(((corners[0].si - corners[3].si) > 0.05) ||
    ((corners[1].si - corners[2].si) > 0.05) ||
    ((corners[0].si - corners[1].si) > 0.05))
  {
    return false;
  }

  return true;
}

//adaptive subsampling
void sample(Color** image, int sampleDelta, int tx, int ty, int bx, int by)
{
  static const Color outColor = Color(1.0, 1.0, 1.0);
  //on single pixel level just store the color
  int xOffset = sampleDelta;
  int yOffset = sampleDelta;

  int depth = 0;
  Vector dir;
  Ray r;
  Sample corners[4];

  for(int y = ty; y < by; y += sampleDelta)
  {
    for(int x = tx; x < bx; x += sampleDelta)
    {
      //edges
      if(x+sampleDelta >= SCR_WIDTH)
        xOffset = SCR_WIDTH - x - 1;
      if(y+sampleDelta >= SCR_HEIGHT)
        yOffset = SCR_HEIGHT - y - 1;
      //color checked samples
      /*image[y][x] = outColor;
      image[y][x+xOffset] = outColor;
      image[y+yOffset][x] = outColor;
      image[y+yOffset][x+xOffset] = outColor;*/
      //cast actual rays
      //0
      screenPos = C0 + (double)y*m_DY + (double)x*m_DX;
      dir = screenPos - cameraPos;
      dir.normalize();
      r = Ray(cameraPos, dir);
      corners[0] = scene.trace(r, REFRACTION_INDEX_AIR, depth);
      //1
      screenPos = C0 + (double)y*m_DY + (double)(x+xOffset)*m_DX;
      dir = screenPos - cameraPos;
      dir.normalize();
      r = Ray(cameraPos, dir);
      corners[1] = scene.trace(r, REFRACTION_INDEX_AIR, depth);
      //2
      screenPos = C0 + (double)(y+yOffset)*m_DY + (double)x*m_DX;
      dir = screenPos - cameraPos;
      dir.normalize();
      r = Ray(cameraPos, dir);
      corners[2] = scene.trace(r, REFRACTION_INDEX_AIR, depth);
      //3
      screenPos = C0 + (double)(y+yOffset)*m_DY + (double)(x+xOffset)*m_DX;
      dir = screenPos - cameraPos;
      dir.normalize();
      r = Ray(cameraPos, dir);
      corners[3] = scene.trace(r, REFRACTION_INDEX_AIR, depth);

      //if the lowest level - store values
      if(sampleDelta == 1)
      {
        image[y][x] = corners[0].c;
        image[y][x+xOffset] = corners[1].c;
        image[y+yOffset][x] = corners[2].c;
        image[y+yOffset][x+xOffset] = corners[3].c;
        return;
      }

      //if there are amjor differences - perform finer sampling
      if(!cornersGoodEnough(corners) && sampleDelta != 1)
      {
        sample(image, sampleDelta/2, x, y, x+xOffset, y+yOffset);
      }else{//else interpolate color
        interpolateColor(image, corners, x, y, x+xOffset, y+yOffset);
      }
    }
  }
}

//=============================================================================
// MAIN
//=============================================================================
int main(int argc, char* argv[])
{
  bool as = true;
  sf::Image image;
  image.create(SCR_WIDTH, SCR_HEIGHT);

  //z-axis
  Vector zAxis = targetPos - cameraPos;
  zAxis.normalize();
  //up vector
  Vector up = Vector(0.0, 1.0, 0.0);
  //x-axis - prependicular to z and up
  Vector xAxis = cross(zAxis, up);
  //y-axis - perpendicular to z and x
  Vector yAxis = cross(zAxis, xAxis);
  //transformation matrix
  Matrix M;   //identity
  //fill top left 3x3
  M.cell[0] = xAxis.x, M.cell[1] = xAxis.y, M.cell[2] = xAxis.z;
	M.cell[4] = yAxis.x, M.cell[5] = yAxis.y, M.cell[6] = yAxis.z;
	M.cell[8] = zAxis.x, M.cell[9] = zAxis.y, M.cell[10] = zAxis.z;
	//invert
	M.invert();
	//fill rightmost column
	M.cell[3] = desiredPos.x, M.cell[7] = desiredPos.y, M.cell[11] = desiredPos.z;
	//transform camera and projection plane
  cameraPos = M.transform(cameraPos);
  C0 = M.transform(C0);
  C1 = M.transform(C1);
  C2 = M.transform(C2);
  C3 = M.transform(C3);
  m_DX = (C1 - C0) * (1.0/SCR_WIDTH);
  m_DY = (C3 - C1) * (1.0/SCR_HEIGHT);
//  screenPos;

  //create scene geometry
  Sphere s1(Vector(3.5, -0.8, 3.0), 2.5);
  Sphere s2(Vector(-5.5, -0.5, 7.0), 2.0);
  Plane p1(Vector(0.0, 1.0, 0.0), -4.4);
  Plane p2(Vector(1.0, 0.0, 0.0), -15.0);
  Plane p3(Vector(-1.0, 0.0, 0.0), -15.0);
  Plane p4(Vector(0.0, 0.0, -1.0), -15.0);
  Plane p5(Vector(0.0, 0.0, 1.0), -15.0);
  Plane p6(Vector(0.0, -1.0, 0.0), -10.0);

  //create materials
  Material mat1;
  mat1.setDiffuseColor(Color(0.7, 0.7, 0.7));
  mat1.setSpecularColor(Color(0.7, 0.7, 0.7));
  mat1.setShininess(20.0);
  mat1.setReflectance(0.0);
  mat1.setRefractance(1.0);
  mat1.setRefractionIndex(REFRACTION_INDEX_GLASS);
  Material mat2;
  mat2.setDiffuseColor(Color(0.7, 0.7, 1.0));
  mat2.setDiffuseIntensity(0.1);
  mat2.setSpecularColor(Color(0.7, 0.7, 0.7));
  mat2.setShininess(20.0);
  mat2.setReflectance(1.0);

  Material mat3;
  mat3.setDiffuseColor(Color(0.4, 0.3, 0.3));
  //mat3.setAmbientColor(Color(0.1, 0.0, 0.0));

  Material mat4;
  mat4.setDiffuseColor(Color(0.0, 1.0, 0.0));
  mat4.setSpecularColor(Color(0.5, 1.0, 0.5));
  mat4.setShininess(25.0);

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
  //side planes
  Object sp4;
  sp4.setShape(p2);
  sp4.setMaterial(mat3);
  Object sp5;
  sp5.setShape(p3);
  sp5.setMaterial(mat3);
  //back plane
  Object sp6;
  sp6.setShape(p4);
  sp6.setMaterial(mat3);
  //front plane
  Object sp7;
  sp7.setShape(p5);
  sp7.setMaterial(mat3);
  //topl plane
  Object sp8;
  sp8.setShape(p6);
  sp8.setMaterial(mat3);

  //create lights
  Light light1;
  light1.setPosition(Vector(0.0, 5.0, 5.0));
  light1.setDiffuseColor(Color(0.6, 0.6, 0.6));
  Light light2;
  light2.setPosition(Vector(2.0, 5.0, 1.0));
  light2.setDiffuseColor(Color(0.7, 0.7, 0.9));

  //setup scene
  //Scene scene;
  scene.addObject(sp1);
  scene.addObject(sp2);
  scene.addObject(sp3);
  scene.addObject(sp4);
  scene.addObject(sp5);
  scene.addObject(sp6);
  scene.addObject(sp7);
  scene.addObject(sp8);
  //grid of green balls
  Object o[16];
  Sphere s[16];
  for(int x = 0; x < 4; x++)
  {
    for(int y = 0; y < 4; y++)
    {
      s[x*4+y] = Sphere(Vector(x+3, y, 14), 0.4);
      o[x*4+y].setShape(s[x*4+y]);
      o[x*4+y].setMaterial(mat4);
      scene.addObject(o[x*4+y]);
    }
  }

  scene.addLight(light1);
  scene.addLight(light2);
  scene.setOutputImage(image);


  Color** result = new Color*[SCR_HEIGHT];
  for(int i = 0; i < SCR_HEIGHT; i++)
  {
    result[i] = new Color[SCR_WIDTH];
  }

  //we want adaptive subsampling
  if(as)
  {
    sample(result, AS_DELTA, 0, 0, SCR_WIDTH, SCR_HEIGHT);
  }else{
    //brute force
    for(int y = 0; y < SCR_HEIGHT; y++)
    {
      screenPos = C0 + (double)y*m_DY;
      for(int x = 0; x < SCR_WIDTH; x++)
      {
        Vector dir = screenPos - cameraPos;
        dir.normalize();
        Ray r = Ray(cameraPos, dir);
        int depth = 0;
        result[y][x] = scene.trace(r, REFRACTION_INDEX_AIR, depth).c;
        screenPos += m_DX;
      }
    }
  }

  //store the image
  for(int y = 0; y < SCR_HEIGHT; y ++)
  {
    for(int x = 0; x < SCR_WIDTH; x++)
    {
      sf::Color col(result[y][x].r*255,
                    result[y][x].g*255,
                    result[y][x].b*255);
      image.setPixel(x,y,col);
    }
  }
  image.saveToFile("result.png");

  //clean up
  for(int i = 0; i < SCR_HEIGHT; i++)
  {
    delete[] result[i];
  }
  delete[] result;

  return 0;
}
