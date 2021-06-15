#ifndef _VULKANRENDERERAPI_H_
#define _VULKANRENDERERAPI_H_

#include "RendererAPI.h"

class VulkanRendererAPI : public RendererAPI
{
public:

	virtual void Init() override;

	virtual void SetViewport(uint32_t _X, uint32_t _Y, uint32_t _Width, uint32_t _Height) override;
	virtual void SetClearColour(const float _R, const float _G, const float _B, const float _A) override;
	virtual void Clear() override;

	virtual void Draw(const std::shared_ptr<Mesh>& _Object) override;

private:

	VkInstance m_Instance;

};

#endif
