#pragma once
#include <fstream>
#include <iostream>
#include <map>
#include <vector>
#include "../Dependencies/freeglut/freeglut.h"
#include "../Dependencies/glew/glew.h"

namespace Managers
{
	class Shader_Manager
	{

	public :
		Shader_Manager(void);
		~Shader_Manager(void);

		void CreateProgram(const std::string& shaderName, const std::string& VertexShaderFilename, const std::string& FragmentShaderFilename);
		static const GLuint GetShader(const std::string&);

	private:

		std::string ReadShader(const std::string& source);
		GLuint CreateShader(GLenum shaderType, const std::string& source, std::string& shaderNAme);
		static std::map<std::string, GLuint> programs;
	};
}