#include <GL/glew.h>

#include "Mesh.h"

//Mesh Constructor which loads a defined object file
Mesh::Mesh(std::string& _File)
{

}

//Default Mesh Constructor for no defined object, uses default mesh
Mesh::Mesh()
{
	//Create an array of vertex positions for our makeshift triangle
	const GLfloat pos[] = {
		.0f, .5f, .0f,
		-.5f, -.5f, .0f,
		.5f, -.5f, .0f
	};

	m_Buffer = std::make_shared<VertexBuffer>();
	m_VertexArray = std::make_unique<VertexArray>();

	m_Buffer->Bind();
	m_Buffer->SetData(pos, 3);

	m_VertexArray->Bind();
	m_VertexArray->AddBuffer(m_Buffer);
	m_VertexArray->Unbind();
	m_Buffer->Unbind();
}

void Mesh::Bind() const
{
	m_VertexArray->Bind();
}

void Mesh::Unbind() const
{
	m_VertexArray->Unbind();
}

int Mesh::GetVertexCount()
{
	return m_VertexArray->GetVertexCount();
}

void Mesh::CreateMesh(const GLfloat* _PosData)
{
	
}