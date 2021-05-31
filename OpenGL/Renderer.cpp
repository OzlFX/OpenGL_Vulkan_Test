#include "Mesh.h"
#include "ShaderSystem.h"
#include "Renderer.h"

void Renderer::Init()
{
	s_RendererAPI->Init(RendererAPI::API::OpenGL);
}

void Renderer::Shutdown()
{

}

void Renderer::WindowResize(uint32_t _Width, uint32_t _Height)
{
	s_RendererAPI->SetViewport(0, 0, _Width, _Height);
}

void Renderer::Submit(const std::shared_ptr<Mesh>& _Mesh, const std::shared_ptr<ShaderSystem>& _Shader)
{
	_Shader->Bind();
	s_RendererAPI->Draw(_Mesh);
}

void Renderer::SetClearColour(const float _R, const float _G, const float _B, const float _A)
{
	s_RendererAPI->SetClearColour(_R, _G, _B, _A);
}

void Renderer::Clear()
{
	s_RendererAPI->Clear();
}