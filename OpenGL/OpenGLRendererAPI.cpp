#include "OpenGLRendererAPI.h"

#include <GL/glew.h>
static void GLAPIENTRY
MessageCallback(GLenum _Source,
	GLenum _Type,
	GLuint _ID,
	GLenum _Severity,
	GLsizei _length,
	const GLchar* _Message,
	const void* _UserParam)
{
	fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
		(_Type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
		_Type, _Severity, _Message);
}

void OpenGLRendererAPI::Init()
{
	glDebugMessageCallback(MessageCallback, nullptr);
	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
}

void OpenGLRendererAPI::SetViewport(uint32_t _X, uint32_t _Y, uint32_t _Width, uint32_t _Height)
{
	glViewport(_X, _Y, _Width, _Height);
}

void OpenGLRendererAPI::SetClearColour(const float _R, const float _G, const float _B, const float _A)
{
	glClearColor(_R, _G, _B, _A);
}

void OpenGLRendererAPI::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT);
}

void OpenGLRendererAPI::Draw(const std::shared_ptr<Mesh>& _Object)
{
	//glDrawElements(GL_TRIANGLES, _Object->GetVertexCount(), GL_UNSIGNED_INT, &_Object->GetIndexData());
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

void OpenGLRendererAPI::Shutdown()
{
}
