#ifndef _VERTEXARRAY_H_
#define _VERTEXARRAY_H_

//Temp Type Defines for OpenGL
typedef unsigned int GLuint;

//Includes
#include <memory>

class VertexBuffer;
class IndexBuffer;

class VertexArray
{
public:

	VertexArray();

	void Bind() const;
	void UnBind() const;

	void AddBuffers(std::shared_ptr<VertexBuffer> _Buffer, std::shared_ptr<IndexBuffer> _Index);

	~VertexArray();

private:

	GLuint m_ID; //Set the Vertex Array Objecy ID
	uint32_t m_BufferIndex = 0;

};

#endif
