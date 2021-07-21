#ifndef _SHADERSYSTEM_H_
#define _SHADERSYSTEM_H_

#include <unordered_map>
#include <glm/glm.hpp>

//Temp Type Defines for OpenGL
typedef char GLchar;
typedef unsigned int GLuint;

class ShaderSystem
{
public:
	
	ShaderSystem(const GLchar* _Vert, const GLchar* _Frag);

	void Bind() const;
	void Unbind() const;

	void CreateProgram();
	
	void SetUniform3f(const std::string& _Name, float _V0, float _V1, float _V2);
	void SetUniform3f(const std::string& _Name, glm::vec3 _Value);

	void SetUniform4f(const std::string& _Name, float _V0, float _V1, float _V2, float _V3);
	void SetUniform4f(const std::string& _Name, glm::vec4 _Value);

	void SetUniformMat4(const std::string& _Name, glm::mat4 _Value);

	~ShaderSystem();

private:

	void CompileShaders();
	int GetUniformLocation(const std::string& _Name);

	std::unordered_map<std::string, int> m_UniformLocationCache;

	GLuint m_ProgramID;
	GLuint m_VertShaderID;
	GLuint m_FragShaderID;

	const GLchar* m_VertSrc;
	const GLchar* m_FragSrc;

};

#endif
