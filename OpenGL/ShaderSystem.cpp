#include <iostream>
#include <GL/glew.h>
#include <vector>

#include "VertexArray.h"
#include "ShaderSystem.h"

ShaderSystem::ShaderSystem(const GLchar* _Vert, const GLchar* _Frag)
{
	m_ProgramID = 0;
	m_VertShaderID = 0;
	m_FragShaderID = 0;

	m_VertSrc = _Vert;
	m_FragSrc = _Frag;
}

//Bind our Shader Program
void ShaderSystem::Bind() const
{
	glUseProgram(m_ProgramID);
}

//Unbind our Shader Program
void ShaderSystem::Unbind() const
{
	glUseProgram(0);
}

void ShaderSystem::CreateProgram()
{
	CompileShaders();

	m_ProgramID = glCreateProgram();

	glAttachShader(m_ProgramID, m_VertShaderID);
	glAttachShader(m_ProgramID, m_FragShaderID);

	//Bind the VAO positions to the first slot during link
	//glBindAttribLocation(m_ProgramID, 0, "in_Pos");

	if (glGetError() != GL_NO_ERROR)
		throw std::exception();

	glLinkProgram(m_ProgramID);

	//Check if link was successful
	GLint isLinked;
	glGetProgramiv(m_ProgramID, GL_LINK_STATUS, &isLinked);

	if (isLinked == GL_FALSE)
	{
		GLint maxLength;
		glGetProgramiv(m_ProgramID, GL_INFO_LOG_LENGTH, &maxLength); //Get log length

		std::vector<GLchar> infoLog(maxLength); //Create container for log info
		glGetProgramInfoLog(m_ProgramID, maxLength, &maxLength, infoLog.data()); //Add info to container
		std::cout << infoLog.data() << std::endl; //Print info

		//Delete ShaderSystem
		glDeleteProgram(m_ProgramID);
		glDeleteShader(m_VertShaderID);
		glDeleteShader(m_FragShaderID);
	}

	//Detach and destroy shaders from the program
	glDetachShader(m_ProgramID, m_VertShaderID);
	glDeleteShader(m_VertShaderID);
	glDetachShader(m_ProgramID, m_FragShaderID);
	glDeleteShader(m_FragShaderID);
}

void ShaderSystem::SetUniform4f(const std::string& _Name, float _V0, float _V1, float _V2, float _V3)
{
	glUniform4f(GetUniformLocation(_Name), _V0, _V1, _V2, _V3);
}

int ShaderSystem::GetUniformLocation(const std::string& _Name)
{
	if (m_UniformLocationCache.find(_Name) != m_UniformLocationCache.end())
		return m_UniformLocationCache[_Name];

	int location = glGetUniformLocation(m_ProgramID, _Name.c_str());
	if (location == -1)
		std::cout << "ERROR: Uniform " << _Name << " does not exist!" << std::endl;
		//throw std::exception();

	m_UniformLocationCache[_Name] = location;

	return location;
}

//Compile the shaders for use
void ShaderSystem::CompileShaders()
{
	m_VertShaderID = glCreateShader(GL_VERTEX_SHADER); //Create a new vertex shader
	glShaderSource(m_VertShaderID, 1, &m_VertSrc, NULL); //Attach shader source code

	glCompileShader(m_VertShaderID); //Compile the Vertex Shader

	//Check if the shader creation is successful
	GLint success = 0;
	glGetShaderiv(m_VertShaderID, GL_COMPILE_STATUS, &success); //Get the vertex ID and check its compile status

	if (!success)
	{
		std::cout << "Vertex Shader Failed to compile" << std::endl;
		throw std::exception();
	}

	m_FragShaderID = glCreateShader(GL_FRAGMENT_SHADER); //Create a new fragment shader
	glShaderSource(m_FragShaderID, 1, &m_FragSrc, NULL); //Attach shader source code

	glCompileShader(m_FragShaderID); //Compile the Fragment Shader

	//Check if the shader creation is successful
	glGetShaderiv(m_FragShaderID, GL_COMPILE_STATUS, &success); //Get the vertex ID and check its compile status

	if (!success)
	{
		std::cout << "Fragment Shader Failed to compile" << std::endl;
		throw std::exception();
	}
}

ShaderSystem::~ShaderSystem()
{
	glDeleteProgram(m_ProgramID);
}