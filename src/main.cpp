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

#include "Vector.h"

using namespace std;

int main()
{
  double l;
  Vector v1(2.5, 3.0, 1.0);
  Vector v2(1.0, 2.0, 2.0);
  Vector v3;

  l = v1.length();
  cout << v1 << endl;
  cout << "Not normalized length = " << l << endl;
  v1.normalize();
  cout << v1 << endl;
  l = v1.length();
  cout << "Normalized length = " << l << endl;
  v1 *= 2.0;
  cout << v1 << endl;
  v3 = cross(v1, v2);
  cout << dot(v1, v3) << endl;
  return 0;
}
