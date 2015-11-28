#ifndef _SHADER_H
#define _SHADER_H


//Note: glew header should be included before glfw header else you will get
//lot of compilation errors.
#include <GL/glew.h>
//#include <GLFW/glfw3.h>

#include <iostream>
#include <cstdio>
#include <string>
#include <fstream>
#include <sstream>

class Shader
{
  GLuint createShader(std::string shaderCode, GLenum shaderType);
  GLboolean checkStatus(GLuint id);
public:
  Shader(const char *vtxShaderFilename, const char *frgmShaderFilename);
  void Use();
  GLuint programId;
};

#endif
