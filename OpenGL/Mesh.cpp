#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Mesh.h"

//Mesh Constructor which loads a defined object file
Mesh::Mesh(std::string& _File)
{

}

//Test Mesh Constructor for Triangle data loading
Mesh::Mesh(const GLfloat _PosData[])
{
	m_Buffer = std::make_unique<VertexBuffer>();
	m_IndexBuffer = std::make_unique<IndexBuffer>(3, 3 / sizeof(GLuint));
	m_VertexArray = std::make_unique<VertexArray>();

	m_Buffer->Bind();
	m_Buffer->SetData(_PosData);
	m_Buffer->UnBind();

	m_VertexArray->Bind();
	m_VertexArray->AddBuffers(m_Buffer, m_IndexBuffer);
}

//Default Mesh Constructor for no defined object, uses default mesh
Mesh::Mesh()
{

}

void Mesh::CreateMesh(const GLfloat _PosData[])
{
	
}