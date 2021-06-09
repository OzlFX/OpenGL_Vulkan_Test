#ifndef _MESH_H_
#define _MESH_H_

//Includes
#include <string>
#include <memory>

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"

class Mesh
{
public:
	
	//Mesh(std::string& _File);
	//Mesh(const GLfloat* _PosData);
	Mesh(); //Default Object

	void Bind() const;
	void Unbind() const;

	void CleanUp() const;

	const GLuint& GetVertexCount() const { return m_VertexArray->GetIndexBuffer()->GetCount(); }

private:

	//Vars
	std::shared_ptr<VertexBuffer> m_Buffer;
	std::shared_ptr<IndexBuffer> m_IndexBuffer;
	std::shared_ptr<VertexArray> m_VertexArray;

};

#endif
