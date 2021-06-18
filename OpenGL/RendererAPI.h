#ifndef _RENDERERAPI_H_
#define _RENDERERAPI_H_

//Includes
#include <memory>

#include "Mesh.h"

class RendererAPI
{
public:
	enum class API
	{
		None = 0, OpenGL = 1, Vulkan = 2
	};

	virtual ~RendererAPI() = default;

	virtual void Init() = 0;

	virtual void SetViewport(uint32_t _X, uint32_t _Y, uint32_t _Width, uint32_t _Height) = 0;
	virtual void SetClearColour(const float _R, const float _G, const float _B, const float _A) = 0;
	virtual void Clear() = 0;

	virtual void Draw(const std::shared_ptr<Mesh>& _Object) = 0;

	virtual void Shutdown() = 0;

	static const API GetAPI() { return s_API; }
	
	static std::unique_ptr<RendererAPI> Create();

private:

	static API s_API;

};

#endif
