#ifndef _VERTEXARRAY_H_
#define _VERTEXARRAY_H_

//Temp Type Defines for OpenGL
typedef unsigned int GLuint;

//Includes
#include <memory>
#include <vector>

class VertexBuffer;
class BufferLayout;
class IndexBuffer;

class VertexArray
{
public:

	VertexArray();

	void Bind() const;
	void Unbind() const;

	void AddBuffer(const std::shared_ptr<VertexBuffer>& _Buffer, const std::shared_ptr<BufferLayout>& _Layout);
	void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& _IndexBuffer);

	const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const { return m_IndexBuffer; }

	~VertexArray();

private:

	GLuint m_ID; //Set the Vertex Array Objecy ID
	uint32_t m_BufferIndex = 0;

	std::shared_ptr<IndexBuffer> m_IndexBuffer;

	std::vector<std::shared_ptr<VertexBuffer>> m_Buffers;

};

#endif
