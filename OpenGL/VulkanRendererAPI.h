#ifndef _VULKANRENDERERAPI_H_
#define _VULKANRENDERERAPI_H_

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vector>
#include <string>
#include <optional>

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

	struct QueueFamilyIndices
	{
		std::optional<uint32_t> m_GraphicsFamily;

		bool IsComplete() { return m_GraphicsFamily.has_value(); }
	};

	void PickPhysicalDevice();
	bool IsDeviceSuitable(VkPhysicalDevice _Device);
	QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice _Device);

	void CreateLogicalDevice();

	VkResult CreateDebugUtilsMessengerExt(VkInstance _Instance,
		const VkDebugUtilsMessengerCreateInfoEXT* _CreateInfo,
		const VkAllocationCallbacks* _Allocator,
		VkDebugUtilsMessengerEXT* _DebugMessenger); //Proxy function to handle address lookup of debug messenger

	void DestroyDebugUtilsMessengerEXT(VkInstance _Instance,
		VkDebugUtilsMessengerEXT* _DebugMessenger, 
		const VkAllocationCallbacks* _Allocator); //Proxy function to handle destruction of debug messenger

	bool CheckValidationLayerSupport(); //Check Layer Validation
	std::vector<const char*> GetRequiredExtensions(); //Get the required extensions

	const std::vector<const char*> m_ValidationLayers = { "VK_LAYER_KHRONOS_validation" };

	void SetupDebugMessenger();

	static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(
		VkDebugUtilsMessageSeverityFlagBitsEXT _MessageSeverity,
		VkDebugUtilsMessageTypeFlagsEXT _MessageType,
		const VkDebugUtilsMessengerCallbackDataEXT* _CallbackData,
		void* _UserData
	);

	void PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& _CreateInfo);

	VkInstance m_Instance;
	VkDebugUtilsMessengerEXT m_DebugMessenger;

	VkPhysicalDevice m_PhysicalDevice = VK_NULL_HANDLE;
	VkDevice m_Device;

#ifdef NDEBUG
	const bool m_EnableValidationLayers = false;
#else
	const bool m_EnableValidationLayers = true;
#endif // NDEBUG

};

#endif
