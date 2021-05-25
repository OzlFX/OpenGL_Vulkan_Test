#ifndef _SHADERSYSTEM_H_
#define _SHADERSYSTEM_H_

//Temp Type Defines for OpenGL
typedef char GLchar;
typedef unsigned int GLuint;

class ShaderSystem
{
public:
	
	ShaderSystem(const GLchar* _Vert, const GLchar* _Frag);

	void Bind() const;
	void UnBind() const;

	void CreateProgram();
	
	~ShaderSystem();

private:

	void CompileShaders();

	GLuint m_ProgramID;
	GLuint m_VertShaderID;
	GLuint m_FragShaderID;

	const GLchar* m_VertSrc;
	const GLchar* m_FragSrc;

};

#endif
