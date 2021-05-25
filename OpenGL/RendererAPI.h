#ifndef _RENDERERAPI_H_
#define _RENDERERAPI_H_

//Includes
#include <memory>

class VertexArray;

class RendererAPI
{
public:
	enum class API
	{
		None = 0, OpenGL = 1, Vulkan = 2
	};

	void Init();

	void SetClearColour(const float _R, const float _G, const float _B, const float _A);
	void Clear();

	void Draw(const std::unique_ptr<VertexArray> _Object);

	static std::unique_ptr<RendererAPI> Create();

	~RendererAPI();

private:

	static API s_API;

};

#endif
