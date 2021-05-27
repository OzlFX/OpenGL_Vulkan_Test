#include <GL/glew.h>

#include "Mesh.h"
#include "RendererAPI.h"

void RendererAPI::Init(API _API)
{
	s_API = _API;
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
	glDrawArrays(GL_TRIANGLES, 0, _Object->GetIndexBuffer()->GetCount());
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
