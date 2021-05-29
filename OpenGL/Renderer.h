#ifndef _RENDERER_H_
#define _RENDERER_H_

//Includes
#include <memory>

#include "RendererAPI.h"

class ShaderSystem;
class Mesh;

class Renderer
{
public:

	static void Init();
	static void Shutdown();

	static void WindowResize(uint32_t _Width, uint32_t _Height);

	static void Submit(const std::shared_ptr<Mesh>& _Mesh, const std::shared_ptr<ShaderSystem>& _Shader);

	static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	static void SetClearColour(const float _R, const float _G, const float _B, const float _A);
	static void Clear();

private:

	static std::unique_ptr<RendererAPI> s_RendererAPI;

};

#endif
