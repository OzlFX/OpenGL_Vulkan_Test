#ifndef _VULKANCONTEXT_H_
#define _VULKANCONTEXT_H_

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vector>
#include <string>
#include <optional>

#include "Context.h"

struct GLFWwindow;

class VulkanContext : public Context
{
public:

	VulkanContext(GLFWwindow* _Window);

	virtual void Init() override;
	virtual void SwapBuffers() override;

	~VulkanContext();

private:

	struct QueueFamilyIndices
	{
		std::optional<uint32_t> m_GraphicsFamily;
		std::optional<uint32_t> m_PresentFamily;

		bool IsComplete() {
			return m_GraphicsFamily.has_value() &&
				m_PresentFamily.has_value();
		}
	};

	void CreateSurface();
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
	VkSurfaceKHR m_Surface;

	VkPhysicalDevice m_PhysicalDevice = VK_NULL_HANDLE;
	VkDevice m_Device;
	VkQueue m_GraphicsQueue;
	VkQueue m_PresentQueue;

#ifdef NDEBUG
	const bool m_EnableValidationLayers = false;
#else
	const bool m_EnableValidationLayers = true;
#endif // NDEBUG

	GLFWwindow* m_WindowHandle;

};

#endif
