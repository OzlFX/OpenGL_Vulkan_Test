#include <GL/glew.h>

#include "Mesh.h"
#include "RendererAPI.h"

RendererAPI::API RendererAPI::s_API = RendererAPI::API::OpenGL;

static void GLAPIENTRY
MessageCallback(GLenum source,
	GLenum type,
	GLuint id,
	GLenum severity,
	GLsizei length,
	const GLchar* message,
	const void* userParam)
{
	fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
		(type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
		type, severity, message);
}

void RendererAPI::Init()
{
	glDebugMessageCallback(MessageCallback, nullptr);
	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
}

void RendererAPI::SetViewport(uint32_t _X, uint32_t _Y, uint32_t _Width, uint32_t _Height)
{
	glViewport(_X, _Y, _Width, _Height);
}

void RendererAPI::SetClearColour(const float _R, const float _G, const float _B, const float _A)
{
	glClearColor(_R, _G, _B, _A);
}

void RendererAPI::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT);
}

void RendererAPI::Draw(const std::shared_ptr<Mesh>& _Object)
{
	//glDrawElements(GL_TRIANGLES, _Object->GetVertexCount(), GL_UNSIGNED_INT, &_Object->GetIndexData());
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

std::unique_ptr<RendererAPI> RendererAPI::Create()
{
	switch (s_API)
	{
	case RendererAPI::API::None: return nullptr;
	case RendererAPI::API::OpenGL: return std::unique_ptr<RendererAPI>();
	}

	return nullptr;
}

RendererAPI::~RendererAPI()
{
}
