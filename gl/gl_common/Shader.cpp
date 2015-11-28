#include "Shader.h"
#include <vector>

#pragma comment(lib, "glew32.lib")
GLboolean Shader::checkStatus(GLuint id)
{
	GLint status(0);
	GLboolean isShader = glIsShader(id);

	if (isShader)
		glGetShaderiv(id, GL_COMPILE_STATUS, &status);
	else
		glGetProgramiv(id, GL_LINK_STATUS, &status);

	if (!status)
	{
		GLint length = 0;
		if (isShader)
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		else
			glGetProgramiv(id, GL_INFO_LOG_LENGTH, &length);

		std::vector<char> log(length);
		if (isShader)
			glGetShaderInfoLog(id, length, &length, &log[0]);
		else
			glGetProgramInfoLog(id, length, &length, &log[0]);
		std::cerr << &log[0];

		return GL_FALSE;
	}

	return GL_TRUE;
}

GLuint Shader::createShader(std::string shaderCode, GLenum shaderType)
{
	GLuint shaderId = glCreateShader(shaderType);
	const char *source = shaderCode.c_str();
	GLint length = shaderCode.size();

	glShaderSource(shaderId, 1, &source, &length);
	glCompileShader(shaderId);
	if(!checkStatus(shaderId))
	{
       abort();
       return -1;
    }

	return shaderId;
}

Shader::Shader(const char *vtx, const char *fgmt)
{
  if (!vtx || !fgmt) return;
  std::ifstream vtxFile, fgmtFile;
  std::stringstream vtxSstream, fgmtSstream;
  std::string vtxCode, fgmtCode;

  vtxFile.open(vtx);
  fgmtFile.open(fgmt);

  vtxSstream << vtxFile.rdbuf();
  fgmtSstream << fgmtFile.rdbuf();

  vtxCode = vtxSstream.str();
  fgmtCode = fgmtSstream.str();

  vtxFile.close();
  fgmtFile.close();

  #ifdef DEBUG
  std::cout << "Vertex Shader:" << vtxCode << std::endl;
  std::cout << "Fragment Shader: " << fgmtCode << std::endl;
  #endif

  GLuint vtxShaderId, fgmtShaderId;

  vtxShaderId = createShader(vtxCode, GL_VERTEX_SHADER);
  fgmtShaderId = createShader(fgmtCode, GL_FRAGMENT_SHADER);

  programId = glCreateProgram();
  glAttachShader(programId, vtxShaderId);
  glAttachShader(programId, fgmtShaderId);

  glLinkProgram(programId);
  if (!checkStatus(programId))
  {
	  abort();
  }
}

void Shader::Use()
{
	glUseProgram(programId);
}
