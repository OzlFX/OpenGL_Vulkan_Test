#ifndef _INDEXBUFFER_H_
#define _INDEXBUFFER_H_

//Temp Type Defines for OpenGL
typedef unsigned int GLuint;

class IndexBuffer
{
public:

	IndexBuffer(GLuint* _Indices, GLuint _Count);

	void Bind() const;
	void Unbind() const;

	GLuint GetCount() const { return m_Count; } //Get the amount of indices
	GLuint* GetIndicies() const { return m_Indicies; }

	~IndexBuffer();

private:

	GLuint m_ID; //Define ID
	GLuint m_Count;
	GLuint* m_Indicies;
};

#endif
