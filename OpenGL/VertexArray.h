#ifndef _VERTEXARRAY_H_
#define _VERTEXARRAY_H_

// Temp Type Defines for OpenGL
typedef unsigned int GLuint;
typedef unsigned int GLenum;

// Includes
#include <memory>
#include <vector>

#include "BufferLayout.h"

class VertexBuffer;
class IndexBuffer;

class VertexArray
{
public:

	VertexArray();

	void Bind() const;
	void Unbind() const;

	void AddBuffer(const std::shared_ptr<VertexBuffer>& _Buffer);
	void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& _IndexBuffer);

	const std::vector<std::shared_ptr<VertexBuffer>>& GetBuffers() const { return m_Buffers; }
	const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const { return m_IndexBuffer; }

	~VertexArray();

private:

	GLenum DataTypeToOpenGLType(DataType _Type);

	GLuint m_ID; // Set the Vertex Array Objecy ID
	uint32_t m_BufferIndex = 0;

	std::shared_ptr<IndexBuffer> m_IndexBuffer;

	std::vector<std::shared_ptr<VertexBuffer>> m_Buffers;

};

#endif
