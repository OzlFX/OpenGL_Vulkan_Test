#ifndef _MESH_H_
#define _MESH_H_

//Includes
#include <string>
#include <memory>

#include "IndexBuffer.h"

//Temp Type Defines for OpenGL
typedef float GLfloat;

class VertexBuffer;
class VertexArray;

class Mesh
{
public:
	
	Mesh(std::string& _File);
	Mesh(const GLfloat _PosData[]);
	Mesh(); //Default Object

	//Getters
	std::shared_ptr<IndexBuffer>& GetIndexBuffer() { return m_IndexBuffer; }

private:

	//Functions
	void CreateMesh(const GLfloat _PosData[]);

	//Vars
	std::shared_ptr<VertexBuffer> m_Buffer;
	std::shared_ptr<IndexBuffer> m_IndexBuffer;
	std::shared_ptr<VertexArray> m_VertexArray;

};

#endif
