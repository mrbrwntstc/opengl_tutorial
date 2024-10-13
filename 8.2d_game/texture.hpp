#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include <glad/glad.h>

class Texture2D
{
public: // fields
  unsigned int ID;
  unsigned int Width;
  unsigned int Height;
  unsigned int Internal_Format;
  unsigned int Image_Format;
  unsigned int Wrap_S;
  unsigned int Wrap_T;
  unsigned int Filter_Min;
  unsigned int Filter_Max;
public: // methods
  Texture2D();
  void Generate(unsigned int width, unsigned int height, unsigned char* data);
  void Bind() const;
};

#endif // __TEXTURE_H__