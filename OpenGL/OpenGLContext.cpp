#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "OpenGLContext.h"

OpenGLContext::OpenGLContext(GLFWwindow* _Window)
	: m_WindowHandle(_Window)
{
}

void OpenGLContext::Init()
{
	glfwMakeContextCurrent(m_WindowHandle); //Create the context for the window

		//Initialise GLEW
	const GLenum err = glewInit();
	if (GLEW_OK != err)
		std::cout << glewGetErrorString(err) << std::endl;

	std::cout << glGetString(GL_VERSION) << std::endl;
}

void OpenGLContext::SwapBuffers()
{
	glfwSwapBuffers(m_WindowHandle);
}
