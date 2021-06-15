#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "VulkanRendererAPI.h"

void VulkanRendererAPI::Init()
{
	///May need to move all this
	VkApplicationInfo appInfo{};

	//Create and define the vulkan application info
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pApplicationName = "VULKAN - TRIANGLE";
	appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.pEngineName = "No Engine";
	appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.apiVersion = VK_API_VERSION_1_0;

	//Create the creation info
	VkInstanceCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	createInfo.pApplicationInfo = &appInfo;

	//Setup vulkan for glfw
	uint32_t glfwExtensionCount = 0;
	const char** glfwExtensions;
	glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

	createInfo.enabledExtensionCount = glfwExtensionCount;
	createInfo.ppEnabledExtensionNames = glfwExtensions;

	createInfo.enabledLayerCount = 0;

	if (vkCreateInstance(&createInfo, nullptr, &m_Instance) != VK_SUCCESS)
		throw std::exception();
}

void VulkanRendererAPI::SetViewport(uint32_t _X, uint32_t _Y, uint32_t _Width, uint32_t _Height)
{
	
}

void VulkanRendererAPI::SetClearColour(const float _R, const float _G, const float _B, const float _A)
{
	
}

void VulkanRendererAPI::Clear()
{
	
}

void VulkanRendererAPI::Draw(const std::shared_ptr<Mesh>& _Object)
{
	
}