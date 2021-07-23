#include <iostream>

#include <GL/glew.h>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "Window.h"

Window::Window(unsigned int _Width, unsigned int _Height, const std::string& _Title)
{
	glfwInit(); //Init glfw

	m_Window = glfwCreateWindow(_Width, _Height, _Title.c_str(), nullptr, nullptr);

	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE); //Prevent window resizing

	m_Context = Context::Create(m_Window);
	m_Context->Init();
}

std::unique_ptr<Window> Window::Create(unsigned int _Width, unsigned int _Height, const std::string& _Title)
{
	return std::make_unique<Window>(_Width, _Height, _Title);
}

void Window::OnUpdate()
{
	m_Context->SwapBuffers();
	glfwPollEvents();
}

void Window::SetVSync(bool _Enabled)
{
	if (_Enabled)
		glfwSwapInterval(1);
	else
		glfwSwapInterval(0);
}

bool Window::CloseEvent()
{
	return glfwWindowShouldClose(m_Window);
}

void Window::Shutdown()
{
	glfwDestroyWindow(m_Window);
	glfwTerminate();
}
