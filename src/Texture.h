#ifndef TEXTURE_H
#define TEXTURE_H

#include <cmath>

#include "Color.h"
#include "Vector.h"

class Perlin
{
public:
  Perlin();
  static Perlin & getInstance()
  {
    static Perlin instance;
    return instance;
  }

  int p[512];
};

enum TextureType {Turbulence, Marble};

class Texture
{
public:
  //! Basic constructor
  Texture();
  //! Primary constructor
  Texture(TextureType type, const Color & col1, const Color & col2);

  //! Texture type getter
  TextureType getType();
  //! Get Texture color at given position
  Color getValue(Vector & poi);
  //! Texture type setter
  void setType(TextureType type);
  //! Color setter
  void setColor(int index, const Color & col);
protected:
private:
  TextureType tType; /*!< Texture type. */
  Color color1;     /*!< First color to mix. */
  Color color2;     /*!< Second color to mix */
};

double fade(double t);
double lerp(double t, double a, double b);
double grad(int hash, double x, double y, double z);
double noise(double x, double y, double z);

#endif // TEXTURE_H
