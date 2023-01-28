#include <GL/glew.h>
#include <fstream>
#include <iostream>

#include "Mesh.h"
#include "BufferLayout.h"

//Mesh Constructor which loads a defined object file
Mesh::Mesh(const std::string& _File)
{
	/// This will be replaced with a robust utility to load files
	std::ifstream input(_File.c_str()); //Load the file

	//Check if the file is not open, throw an error if not
	if (!input.is_open())
		std::cerr << "File could not be opened\n";

	m_VertexArray = std::make_shared<VertexArray>();

	GLfloat posData;
	GLuint indices;

	m_Buffer = std::make_shared<VertexBuffer>(posData, sizeof(posData));
	BufferLayout Layout = { { DataType::Float3, "in_Pos" },
							{ DataType::Float4, "in_Colour"} };

	m_IndexBuffer = std::make_shared<IndexBuffer>(indices, sizeof(indices));

	//m_Buffer->SetData(pos, sizeof(pos));
	m_Buffer->SetLayout(Layout);

	m_VertexArray->AddBuffer(m_Buffer);
	m_VertexArray->SetIndexBuffer(m_IndexBuffer);
}

//Mesh Constructor which loads a defined object from position and
// index data
Mesh::Mesh(GLfloat &_pos, GLuint &_indices)
{
	m_VertexArray = std::make_shared<VertexArray>();

	m_Buffer = std::make_shared<VertexBuffer>(_pos, sizeof(_pos));
	BufferLayout Layout = { { DataType::Float3, "in_Pos" },
							{ DataType::Float4, "in_Colour"} };

	m_IndexBuffer = std::make_shared<IndexBuffer>(_indices, sizeof(_indices));

	//m_Buffer->SetData(pos, sizeof(pos));
	m_Buffer->SetLayout(Layout);

	m_VertexArray->AddBuffer(m_Buffer);
	m_VertexArray->SetIndexBuffer(m_IndexBuffer);
}

//Default Mesh Constructor for no defined object, uses default mesh
Mesh::Mesh()
{
	//Create an array of vertex positions for our makeshift triangle
	const GLfloat pos[] = 
	{
		 -1.5f, -0.5f, 0.0f, 0.18f, 0.6f, 0.96f, 1.0f,
		 -0.5f, -0.5f, 0.0f, 0.18f, 0.6f, 0.96f, 1.0f,
		 -0.5f,  0.5f, 0.0f, 0.18f, 0.6f, 0.96f, 1.0f,
		 -1.5f,  0.5f, 0.0f, 0.18f, 0.6f, 0.96f, 1.0f,

		  0.5f, -0.5f, 0.0f, 0.6f, 0.87f, 0.02f, 1.0f,
		  1.5f, -0.5f, 0.0f, 0.6f, 0.87f, 0.02f, 1.0f,
		  1.5f,  0.5f, 0.0f, 0.6f, 0.87f, 0.02f, 1.0f,
		  0.5f,  0.5f, 0.0f, 0.6f, 0.87f, 0.02f, 1.0f
	};

	//Use the indices to render our triangle as a square by plotting 
	//the points to rerender in a defined order
	GLuint indices[] =
	{ 
		0, 1, 2, 2, 3, 0,
		4, 5, 6, 6, 7, 4
	};

	m_VertexArray = std::make_shared<VertexArray>();

	m_Buffer = std::make_shared<VertexBuffer>(pos, sizeof(pos));
	BufferLayout Layout = { { DataType::Float3, "in_Pos" },
							{ DataType::Float4, "in_Colour"} };
	
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
