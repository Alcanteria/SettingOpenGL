#include "Shader_Manager.h"

using namespace Managers;

std::map<std::string, GLuint> Shader_Manager::programs;

Shader_Manager::Shader_Manager(void)
{

}

Shader_Manager::~Shader_Manager(void)
{
	std::map<std::string, GLuint>::iterator i;
	for (i = programs.begin(); i != programs.end(); ++i)
	{
		GLuint pr = i->second;
		glDeleteProgram(pr);
	}
	programs.clear();
}

std::string Shader_Manager::ReadShader(const std::string& filename)
{
	std::string shaderCode;
	std::ifstream file(filename, std::ios::in);

	if (!file.good())
	{
		std::cout << "Can't read file: " << filename.c_str() << std::endl;
		std::terminate();
	}

	file.seekg(0, std::ios::end);
	shaderCode.resize((unsigned int)file.tellg());
	file.seekg(0, std::ios::beg);
	file.read(&shaderCode[0], shaderCode.size());
	file.close();

	return shaderCode;
}

GLuint Shader_Manager::CreateShader(GLenum shaderType, const std::string& source, std::string& shaderName)
{
	int compile_result = 0;

	GLuint shader = glCreateShader(shaderType);
	const char *shader_code_ptr = source.c_str();
	const int shader_code_size = source.size();

	glShaderSource(shader, 1, &shader_code_ptr, &shader_code_size);
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_result);

	// Check for errors.
	if (compile_result == GL_FALSE){

		int info_log_length = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &info_log_length);
		std::vector<char> shader_log(info_log_length);
		glGetShaderInfoLog(shader, info_log_length, NULL, &shader_log[0]);
		std::cout << "ERROR compiling shader: " << shaderName.c_str() << std::endl << &shader_log[0] << std::endl;
		return 0;
	}
	return shader;
}

void Shader_Manager::CreateProgram(const std::string& shaderName, const std::string& vertexShaderFilename, const std::string& fragmentShaderFilename)
{
	// Read the shader files and save the code.
	std::string vertex_shader_code = ReadShader(vertexShaderFilename);
	std::string fragment_shader_code = ReadShader(fragmentShaderFilename);

	// NOT SURE IF THIS IS RIGHT. LOOK HERE FIRST IF YOU HAVE ISSUES.
	GLuint vertex_shader = CreateShader(GL_VERTEX_SHADER, vertex_shader_code, vertexShaderFilename.c_str);
	GLuint fragment_shader = CreateShader(GL_FRAGMENT_SHADER, fragment_shader_code, fragmentShaderFilename.c_str);

	int link_result = 0;

	// Create the program handle, attach the shaders and link it.
	GLuint program = glCreateProgram();
	glAttachShader(program, vertex_shader);
	glAttachShader(program, fragment_shader);

	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &link_result);

	// Check for link errors.
	if (link_result == GL_FALSE){

		int info_log_length = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &info_log_length);
		std::vector<char> program_log(info_log_length);
		glGetProgramInfoLog(program, info_log_length, NULL, &program_log[0]);
		std::cout << "Shader Loader : LINK ERROR" << std::endl << &program_log[0] << std::endl;
	}
	programs.insert(std::pair<std::string, GLuint>(shaderName, program));
}

const GLuint Shader_Manager::GetShader(const std::string& shaderName)
{
	// Need to find out how to check if this value is in the map before you return it.
	
	return programs.at(shaderName);
}