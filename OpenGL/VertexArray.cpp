#include <exception>
#include <GL/glew.h>
#include <iostream>

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
void VertexArray::AddBuffer(const std::shared_ptr<VertexBuffer>& _Buffer)
{
	//if (_Buffer->GetLayout().GetElements().size() < 1)
	//	std::cout << "Vertex Buffer Layout is empty for some reason!" << std::endl;
	
	Bind();
	_Buffer->Bind(); //Bind the desired VBO to the GPU
	
	/// Stride needs to check the data type (GL_FLOAT etc.) and * that by the component number
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
	//glEnableVertexAttribArray(0);

	const auto& layout = _Buffer->GetLayout();
	//Assign the VBO to the first index and flag it for use
	for (const auto& element : layout)
	{
		switch (element.m_Type)
		{
			case DataType::Float:
			case DataType::Float2:
			case DataType::Float3:
			case DataType::Float4:
			{
				glEnableVertexAttribArray(m_BufferIndex);
				glVertexAttribPointer(m_BufferIndex,
					element.GetComponentCount(),
					DataTypeToOpenGLType(element.m_Type),
					element.m_Normalised ? GL_TRUE : GL_FALSE,
					layout.GetStride(),
					(const void*)element.m_Offset);
				m_BufferIndex++;
				break;
			}
			case DataType::Int:
			case DataType::Int2:
			case DataType::Int3:
			case DataType::Int4:
			case DataType::Bool:
			{
				glEnableVertexAttribArray(m_BufferIndex);
				glVertexAttribIPointer(m_BufferIndex,
					element.GetComponentCount(),
					DataTypeToOpenGLType(element.m_Type),
					layout.GetStride(),
					(const void*)element.m_Offset);
				m_BufferIndex++;
				break;
			}
			case DataType::Mat3:
			case DataType::Mat4:
			{
				uint8_t count = element.GetComponentCount();
				for (uint8_t i = 0; i < count; i++)
				{
					glEnableVertexAttribArray(m_BufferIndex);
					glVertexAttribPointer(m_BufferIndex,
						count,
						DataTypeToOpenGLType(element.m_Type),
						element.m_Normalised ? GL_TRUE : GL_FALSE,
						layout.GetStride(),
						(const void*)(element.m_Offset + sizeof(float) * count * i));
					glVertexAttribDivisor(m_BufferIndex, 1);
					m_BufferIndex++;
				}
				break;
			}
		}
	}

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

GLenum VertexArray::DataTypeToOpenGLType(DataType _Type)
{
	switch (_Type)
	{
		case DataType::Float:    return GL_FLOAT;
		case DataType::Float2:   return GL_FLOAT;
		case DataType::Float3:   return GL_FLOAT;
		case DataType::Float4:   return GL_FLOAT;
		case DataType::Mat3:     return GL_FLOAT;
		case DataType::Mat4:     return GL_FLOAT;
		case DataType::Int:      return GL_INT;
		case DataType::Int2:     return GL_INT;
		case DataType::Int3:     return GL_INT;
		case DataType::Int4:     return GL_INT;
		case DataType::Bool:     return GL_BOOL;
	}

	return 0;
}
