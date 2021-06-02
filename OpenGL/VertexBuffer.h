#ifndef _VERTEXBUFFER_H_
#define _VERTEXBUFFER_H_

//Temp Type Defines for OpenGL
typedef unsigned int GLuint;
typedef float GLfloat;

class VertexBuffer
{
public:

	VertexBuffer();
	VertexBuffer(const void* _Data, int _ComponentSize);

	void Bind() const;
	void Unbind() const;

	void SetData(const void* _Data, int _ComponentSize = 3);
	int GetSize() { return m_DataSize; }
	int GetComponentCount() { return m_Components; }

	~VertexBuffer();

private:

	GLuint m_ID; //Define ID
	int m_Components;
	int m_DataSize;

};

#endif
