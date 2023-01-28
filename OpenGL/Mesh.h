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
	
	//Mesh(const std::string& _File);
	//Mesh(GLfloat &_pos, GLuint &_indices);
	Mesh(); //Default Mesh

	void Bind() const; //Bind the Mesh Data for usage in the renderer
	void Unbind() const; //Unbind the Mesh Data from the renderer

	void CleanUp() const; //Cleanup the Mesh data, unbinding everything

	const GLuint& GetVertexCount() const { return m_VertexArray->GetIndexBuffer()->GetCount(); } //Get the object Index Count
	const GLuint& GetIndexData() const { return *m_VertexArray->GetIndexBuffer()->GetIndicies(); } //Get the object's Indicies

private:

	//Vars
	std::shared_ptr<VertexBuffer> m_Buffer;
	std::shared_ptr<IndexBuffer> m_IndexBuffer;
	std::shared_ptr<VertexArray> m_VertexArray;

};

#endif
