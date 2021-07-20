#include <GL/glew.h>

#include "Mesh.h"
#include "BufferLayout.h"

//Mesh Constructor which loads a defined object file
//Mesh::Mesh(std::string& _File)
//{
//
//}

//Default Mesh Constructor for no defined object, uses default mesh
Mesh::Mesh()
{
	//Create an array of vertex positions for our makeshift triangle
	const GLfloat pos[] = {
		-0.5f, -0.5f, 0.0f,
		 0.0f, -0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f
	};

	//Use the indices to render our triangle as a square by plotting 
	//the points to rerender in a defined order
	GLuint indices[] =
	{ 
		0, 1, 2, 2, 3, 0
	};

	m_Buffer = std::make_shared<VertexBuffer>(pos, sizeof(pos));
	BufferLayout Layout = { { DataType::Float3, "in_Pos" } };
	m_VertexArray = std::make_shared<VertexArray>();
	m_IndexBuffer = std::make_shared<IndexBuffer>(indices, sizeof(indices));

	//m_Buffer->SetData(pos, sizeof(pos));
	m_Buffer->SetLayout(Layout);

	m_VertexArray->AddBuffer(m_Buffer);
	m_VertexArray->SetIndexBuffer(m_IndexBuffer);
}

void Mesh::Bind() const
{
	m_VertexArray->Bind();
}

void Mesh::Unbind() const
{
	m_VertexArray->Unbind();
}

void Mesh::CleanUp() const
{
	m_Buffer->Unbind();
	m_IndexBuffer->Unbind();
}
