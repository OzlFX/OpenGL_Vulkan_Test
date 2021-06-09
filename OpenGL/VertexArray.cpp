#include <exception>
#include <GL/glew.h>

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "BufferLayout.h"
#include "VertexArray.h"

VertexArray::VertexArray()
	: m_ID(0)
{
	glGenVertexArrays(1, &m_ID); //Create a new VAO on the GPU using the VAO id

	if (!m_ID)
		throw std::exception();
}

//Bind our Vertex Array
void VertexArray::Bind() const
{
	//Create a new VAO on the GPU using the VAO id
	glBindVertexArray(m_ID); 
}

//Unbind our Vertex Array
void VertexArray::Unbind() const
{
	glBindVertexArray(0);
}

///We hard code this for now since we are working with just one triangle.
///Will need to get components (data per line i.e. position vectors) later for models.
//Set the buffer data to draw
void VertexArray::AddBuffer(const std::shared_ptr<VertexBuffer>& _Buffer, const std::shared_ptr<BufferLayout>& _Layout)
{
	Bind();
	_Buffer->Bind(); //Bind the desired VBO to the GPU
	
	unsigned int offset = 0;

	const auto& elements = _Layout->GetElements();
	//Assign the VBO to the first index and flag it for use
	for (unsigned int i = 0; i < elements.size(); i++)
	{
		const auto& element = elements[i];
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, element.m_Count, element.m_Type,
			element.m_Normalised, _Layout->GetStride(), (const void*)offset);

		offset += element.m_Count * BufferElement::GetSizeOfType(element.m_Type);
	}
	//m_BufferIndex++;
	m_Buffers.push_back(_Buffer);

	_Buffer->Unbind();
}

void VertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& _IndexBuffer)
{
	_IndexBuffer->Bind();
	m_IndexBuffer = _IndexBuffer;
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_ID); //Delete VAO
}