#ifndef _VULKANRENDERERAPI_H_
#define _VULKANRENDERERAPI_H_

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vector>
#include <string>

#include "RendererAPI.h"

class VulkanRendererAPI : public RendererAPI
{
public:

	virtual void Init() override;

	virtual void SetViewport(uint32_t _X, uint32_t _Y, uint32_t _Width, uint32_t _Height) override;
	virtual void SetClearColour(const float _R, const float _G, const float _B, const float _A) override;
	virtual void Clear() override;

	virtual void Draw(const std::shared_ptr<Mesh>& _Object) override;

	virtual void Shutdown() override;

private:

	bool CheckValidationLayerProperties(); //Check Layer Validation
	std::vector<const char*> GetRequiredExtensions(); //Get the required extensions

	const std::vector<std::string> m_ValidationLayers = { "VK_LAYER_KHRONOS_validation" };

	static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(
		VkDebugUtilsMessageSeverityFlagBitsEXT _MessageSeverity,
		VkDebugUtilsMessageTypeFlagsEXT _MessageType,
		const VkDebugUtilsMessengerCallbackDataEXT* _pCallbackData,
		void* _pUserData
	);

	VkInstance m_Instance;

#ifdef NDEBUG
	const bool m_EnableValidationLayers = false;
#else
	const bool m_EnableValidationLayers = true;
#endif // NDEBUG

};

#endif
