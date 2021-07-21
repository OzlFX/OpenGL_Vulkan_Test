#include "Mesh.h"
#include "ShaderSystem.h"
#include "Renderer.h"
#include <glm/ext.hpp>

std::unique_ptr<RendererAPI> Renderer::s_RendererAPI = RendererAPI::Create();

void Renderer::Init()
{
	s_RendererAPI->Init();
}

void Renderer::Shutdown()
{
	s_RendererAPI->Shutdown();
}

void Renderer::WindowResize(uint32_t _Width, uint32_t _Height)
{
	s_RendererAPI->SetViewport(0, 0, _Width, _Height);
}

void Renderer::Submit(const std::shared_ptr<Mesh>& _Mesh, const std::shared_ptr<ShaderSystem>& _Shader)
{
	glm::mat4 proj = glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, -1.0f, 1.0f);
	_Shader->Bind();
	_Mesh->Bind();
	_Shader->SetUniform4f("in_Colour", 0.75f, 0.5f, 0.5f, 1.0f);
	_Shader->SetUniformMat4("u_ViewProjection", proj);
	_Shader->SetUniformMat4("u_Transform", glm::mat4(1.0f));
	s_RendererAPI->Draw(_Mesh);
	_Mesh->Unbind();
	_Shader->Unbind();
}

void Renderer::SetClearColour(const float _R, const float _G, const float _B, const float _A)
{
	s_RendererAPI->SetClearColour(_R, _G, _B, _A);
}

void Renderer::Clear()
{
	s_RendererAPI->Clear();
}
