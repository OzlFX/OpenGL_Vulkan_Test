#include "VulkanContext.h"
#include <iostream>
#include <set>

VulkanContext::VulkanContext(GLFWwindow* _Window)
	: m_WindowHandle(_Window)
{
}

void VulkanContext::Init()
{
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	std::cout << "API: VULKAN" << std::endl;

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

	SetupDebugMessenger();
	CreateSurface();
	PickPhysicalDevice();
	CreateLogicalDevice();
}

void VulkanContext::SwapBuffers()
{
}

/* Private Functions for Vulkan */

void VulkanContext::CreateSurface()
{
	if (glfwCreateWindowSurface(m_Instance, m_WindowHandle, nullptr, &m_Surface) != VK_SUCCESS)
	{
		std::cout << "Failed to create window surface\n";
		throw std::exception();
	}
}

void VulkanContext::PickPhysicalDevice()
{
	uint32_t deviceCount = 0;
	vkEnumeratePhysicalDevices(m_Instance, &deviceCount, nullptr);

	if (deviceCount == 0)
	{
		//std::cout << "Could not find GPUs with Vulkan support!\n";
		//throw std::exception();
		throw std::runtime_error("Could not find GPUs with Vulkan support!");
	}

	std::vector<VkPhysicalDevice> devices(deviceCount);
	vkEnumeratePhysicalDevices(m_Instance, &deviceCount, devices.data());

	for (const auto& device : devices)
	{
		if (IsDeviceSuitable(device))
		{
			m_PhysicalDevice = device;
			break;
		}
	}

	if (m_PhysicalDevice == VK_NULL_HANDLE)
	{
		std::cout << "Failed to find a compatible GPU\n";
		///Eventually, we want to switch back to OpenGL if Vulkan cant be used.
		///For now, throw exception
		throw std::exception();
	}
}

bool VulkanContext::IsDeviceSuitable(VkPhysicalDevice _Device)
{
	QueueFamilyIndices indices = FindQueueFamilies(_Device);
	return indices.IsComplete();
}

VulkanContext::QueueFamilyIndices
VulkanContext::FindQueueFamilies(VkPhysicalDevice _Device)
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

		VkBool32 presentSupport = false;
		vkGetPhysicalDeviceSurfaceSupportKHR(_Device, i, m_Surface, &presentSupport);

		if (presentSupport)
			indices.m_PresentFamily = i;

		if (indices.IsComplete())
			break;

		i++;
	}

	return indices;
}

void VulkanContext::CreateLogicalDevice()
{
	QueueFamilyIndices indices = FindQueueFamilies(m_PhysicalDevice);

	std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;

	std::set<uint32_t> uniqueQueueFamilies = 
	{ 
		indices.m_GraphicsFamily.value(), 
		indices.m_PresentFamily.value()
	};

	float queuePriority = 1.0f;
	for (uint32_t queueFamily : uniqueQueueFamilies)
	{
		VkDeviceQueueCreateInfo queueCreateInfo{};
		queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		queueCreateInfo.queueFamilyIndex = queueFamily;
		queueCreateInfo.queueCount = 1;
		queueCreateInfo.pQueuePriorities = &queuePriority;
		queueCreateInfos.push_back(queueCreateInfo);
	}

	VkPhysicalDeviceFeatures deviceFeatures{};

	//Create the logical device info
	VkDeviceCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
	createInfo.pQueueCreateInfos = queueCreateInfos.data();

	createInfo.pEnabledFeatures = &deviceFeatures;

	createInfo.enabledExtensionCount = 0;

	//Check if the validation layers are enabled
	if (m_EnableValidationLayers)
	{
		createInfo.enabledLayerCount = static_cast<uint32_t>(m_ValidationLayers.size()); //Get the enabled layers
		createInfo.ppEnabledLayerNames = m_ValidationLayers.data(); //Get the layer names
	}
	else
	{
		createInfo.enabledLayerCount = 0; //Disable layers for the created info
	}

	if (vkCreateDevice(m_PhysicalDevice, &createInfo, nullptr, &m_Device) != VK_SUCCESS)
	{
		std::cout << "Logical device creation failed\n";
		throw std::exception();
	}

	vkGetDeviceQueue(m_Device, indices.m_GraphicsFamily.value(), 0, &m_GraphicsQueue);
	vkGetDeviceQueue(m_Device, indices.m_PresentFamily.value(), 0, &m_PresentQueue);
}

VkResult VulkanContext::CreateDebugUtilsMessengerExt(VkInstance _Instance,
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

void VulkanContext::DestroyDebugUtilsMessengerEXT(VkInstance _Instance,
	VkDebugUtilsMessengerEXT* _DebugMessenger,
	const VkAllocationCallbacks* _Allocator)
{
	//Get the destroy debug messenger extended function's memory address
	auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)
		vkGetInstanceProcAddr(_Instance, "vkDestroyDebugUtilsMessengerEXT");

	if (func != nullptr)
		func(_Instance, m_DebugMessenger, _Allocator);
}

bool VulkanContext::CheckValidationLayerSupport()
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

std::vector<const char*> VulkanContext::GetRequiredExtensions()
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

void VulkanContext::SetupDebugMessenger()
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

VKAPI_ATTR VkBool32 VKAPI_CALL VulkanContext::DebugCallback(
	VkDebugUtilsMessageSeverityFlagBitsEXT _MessageSeverity,
	VkDebugUtilsMessageTypeFlagsEXT _MessageType,
	const VkDebugUtilsMessengerCallbackDataEXT* _CallbackData,
	void* _UserData)
{
	std::cerr << "Validation layer: " << _CallbackData->pMessage << "\n";

	return VK_FALSE;
}

void VulkanContext::PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& _CreateInfo)
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

VulkanContext::~VulkanContext()
{
	vkDestroyDevice(m_Device, nullptr);

	if (m_EnableValidationLayers)
		DestroyDebugUtilsMessengerEXT(m_Instance, &m_DebugMessenger, nullptr);

	vkDestroySurfaceKHR(m_Instance, m_Surface, nullptr);
	vkDestroyInstance(m_Instance, nullptr);
}
