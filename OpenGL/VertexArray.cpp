#include <exception>
#include <GL/glew.h>

#include "VertexBuffer.h"
#include "VertexArray.h"

VertexArray::VertexArray()
{
	m_ID = 0;

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
void VertexArray::UnBind() const
{
	glBindVertexArray(0);
}

///We hard code this for now since we are working with just one triangle.
///Will need to get components (data per line i.e. position vectors) later for models.
//Set the buffer data to draw
void VertexArray::AddBuffers(std::shared_ptr<VertexBuffer> _Buffer, std::shared_ptr<IndexBuffer> _Index)
{
	_Buffer->Bind(); //Bind the newly created VBO to the GPU
	
	//Assign the VBO to the first index and flag it for use
	glEnableVertexAttribArray(m_BufferIndex);
	glVertexAttribPointer(m_BufferIndex, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
	
	m_BufferIndex++;

	_Buffer->UnBind();
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_ID); //Delete VAO
}