#ifndef _VERTEXARRAY_H_
#define _VERTEXARRAY_H_

//Temp Type Defines for OpenGL
typedef unsigned int GLuint;

//Includes
#include <memory>
#include <vector>

class VertexBuffer;

class VertexArray
{
public:

	VertexArray();

	void Bind() const;
	void UnBind() const;

	void AddBuffer(std::shared_ptr<VertexBuffer> _Buffer);

	~VertexArray();

private:

	GLuint m_ID; //Set the Vertex Array Objecy ID
	uint32_t m_BufferIndex = 0;

	std::vector<std::shared_ptr<VertexBuffer>> m_Buffers;

};

#endif
