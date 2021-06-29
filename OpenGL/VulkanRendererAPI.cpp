#include "VulkanRendererAPI.h"
#include <iostream>

void VulkanRendererAPI::Init()
{
	if (m_EnableValidationLayers && !CheckValidationLayerSupport())
	{
		std::cout << "Validation Layers requested but not available!\n";
		throw std::exception();
	}

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

	auto extensions = GetRequiredExtensions();

	createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
	createInfo.ppEnabledExtensionNames = extensions.data();

	VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{};
	if (m_EnableValidationLayers)
	{
		createInfo.enabledLayerCount = static_cast<uint32_t>(m_ValidationLayers.size());
		createInfo.ppEnabledLayerNames = m_ValidationLayers.data();

		PopulateDebugMessengerCreateInfo(debugCreateInfo);
		createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)&debugCreateInfo;
	}
	else
	{
		createInfo.enabledLayerCount = 0;
		createInfo.pNext = nullptr;
	}
	
	if (vkCreateInstance(&createInfo, nullptr, &m_Instance) != VK_SUCCESS)
		throw std::exception();

	PickPhysicalDevice();
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

void VulkanRendererAPI::Shutdown()
{
	if (m_EnableValidationLayers)
		DestroyDebugUtilsMessengerEXT(m_Instance, &m_DebugMessenger, nullptr);

	vkDestroyInstance(m_Instance, nullptr);
}

void VulkanRendererAPI::PickPhysicalDevice()
{
	VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;

	uint32_t deviceCount = 0;
	vkEnumeratePhysicalDevices(m_Instance, &deviceCount, nullptr);

	if (deviceCount == 0)
	{
		std::cout << "Could not find GPUs with Vulkan support!\n";
		throw std::exception();
	}

	std::vector<VkPhysicalDevice> devices(deviceCount);
	vkEnumeratePhysicalDevices(m_Instance, &deviceCount, devices.data());

	for (const auto& device : devices)
	{
		if (IsDeviceSuitable(device))
		{
			physicalDevice = device;
			break;
		}
	}

	if (physicalDevice == VK_NULL_HANDLE)
	{
		std::cout << "Failed to find a compatible GPU\n";
		///Eventually, we want to switch back to OpenGL if Vulkan cant be used.
		///For now, throw exception
		throw std::exception();
	}
}

bool VulkanRendererAPI::IsDeviceSuitable(VkPhysicalDevice _Device)
{
	QueueFamilyIndices indices = FindQueueFamilies(_Device);
	return indices.IsComplete();
}

VulkanRendererAPI::QueueFamilyIndices 
VulkanRendererAPI::FindQueueFamilies(VkPhysicalDevice _Device)
{
	QueueFamilyIndices indices;

	uint32_t queueFamilyCount = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(_Device, &queueFamilyCount, nullptr); //Get queue family properties

	std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
	vkGetPhysicalDeviceQueueFamilyProperties(_Device, &queueFamilyCount, queueFamilies.data());

	int i = 0;
	for (const auto& queueFamily : queueFamilies)
	{
		if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
			indices.m_GraphicsFamily = i;

		if (indices.IsComplete())
			break;

		i++;
	}

	return indices;
}

VkResult VulkanRendererAPI::CreateDebugUtilsMessengerExt(VkInstance _Instance,
	const VkDebugUtilsMessengerCreateInfoEXT* _CreateInfo,
	const VkAllocationCallbacks* _Allocator,
	VkDebugUtilsMessengerEXT* _DebugMessenger)
{
	//Get the create debug messenger extended function's memory address
	auto func = (PFN_vkCreateDebugUtilsMessengerEXT) 
		vkGetInstanceProcAddr(_Instance, "vkCreateDebugUtilsMessengerEXT");

	//Check if the function is valid and can be found
	if (func != nullptr)
	{
		return func(_Instance, _CreateInfo, _Allocator, _DebugMessenger);
	}
	else
	{
		return VK_ERROR_EXTENSION_NOT_PRESENT;
	}
}

void VulkanRendererAPI::DestroyDebugUtilsMessengerEXT(VkInstance _Instance,
	VkDebugUtilsMessengerEXT* _DebugMessenger,
	const VkAllocationCallbacks* _Allocator)
{
	//Get the destroy debug messenger extended function's memory address
	auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)
		vkGetInstanceProcAddr(_Instance, "vkDestroyDebugUtilsMessengerEXT");

	if (func != nullptr)
		func(_Instance, m_DebugMessenger, _Allocator);
}

bool VulkanRendererAPI::CheckValidationLayerSupport()
{
	uint32_t layerCount;
	vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

	std::vector<VkLayerProperties> availableLayers(layerCount);
	vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

	//Loop through the layers
	for (auto& layerName : m_ValidationLayers)
	{
		bool layerFound = false;

		//Loop through the Vulkan layer properties
		for (const auto& layerProperties : availableLayers)
		{
			//Compare the current layer name with the validation layer vector
			//to find the validation layer, break once found
			if (strcmp(layerName, layerProperties.layerName) == 0)
			{
				layerFound = true;
				break;
			}
		}

		if (!layerFound)
			return false;
	}

	return true;
}

std::vector<const char*> VulkanRendererAPI::GetRequiredExtensions()
{
	//Setup vulkan for glfw
	uint32_t glfwExtensionCount = 0;
	const char** glfwExtensions;
	glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

	std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

	//Enable debug extension in debug mode
	if (m_EnableValidationLayers)
		extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);

	return extensions;
}

void VulkanRendererAPI::SetupDebugMessenger()
{
	if (!m_EnableValidationLayers) return;

	VkDebugUtilsMessengerCreateInfoEXT createInfo;
	PopulateDebugMessengerCreateInfo(createInfo);

	if (CreateDebugUtilsMessengerExt(m_Instance, &createInfo, nullptr, &m_DebugMessenger) != VK_SUCCESS)
	{
		std::cout << "Failed to setup debug messenger!\n";
		throw std::exception();
	}
}

VKAPI_ATTR VkBool32 VKAPI_CALL VulkanRendererAPI::DebugCallback(
	VkDebugUtilsMessageSeverityFlagBitsEXT _MessageSeverity, 
	VkDebugUtilsMessageTypeFlagsEXT _MessageType, 
	const VkDebugUtilsMessengerCallbackDataEXT* _CallbackData, 
	void* _UserData)
{
	std::cerr << "Validation layer: " << _CallbackData->pMessage << "\n";

	return VK_FALSE;
}

void VulkanRendererAPI::PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& _CreateInfo)
{
	_CreateInfo = {};
	_CreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
	_CreateInfo.messageSeverity = 
		VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | 
		VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | 
		VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;

	_CreateInfo.messageType =
		VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
		VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
		VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;

	_CreateInfo.pfnUserCallback = DebugCallback;
}
