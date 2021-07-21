#include <iostream>
#include <GL/glew.h>
//#include <vulkan/vulkan.h>
#include <memory>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "Renderer.h"
#include "Mesh.h"
#include "ShaderSystem.h"

int main()//int argc, char *argv[])
{
	bool running = true;
	
	 //Set the renderer api

	glfwInit(); //Init glfw
	
	if (Renderer::GetAPI() == RendererAPI::API::Vulkan)
	{
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		std::cout << "API: VULKAN" << std::endl;
	}

	GLFWwindow* window = glfwCreateWindow(840, 640, "OpenGL/Vulkan", nullptr, nullptr);

	if (Renderer::GetAPI() == RendererAPI::API::OpenGL)
	{
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		std::cout << "API: OPENGL" << std::endl;
	}

	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE); //Prevent window resizing

	if (Renderer::GetAPI() == RendererAPI::API::OpenGL)
	{
		glfwMakeContextCurrent(window); //Create the context for the window

		//Initialise GLEW
		const GLenum err = glewInit();
		if (GLEW_OK != err)
			std::cout << glewGetErrorString(err) << std::endl;

		std::cout << glGetString(GL_VERSION) << std::endl;
	}

	//Create vertex shader source
	const GLchar* VertSRC =
		"#version 330 core\n"
		"\n"
		"layout(location = 0) in vec3 in_Pos;\n"
		"layout(location = 1) in vec4 in_Colour;\n"
		"\n"
		"uniform mat4 u_ViewProjection;\n"
		"uniform mat4 u_Transform;\n"
		"\n"
		"out vec4 out_Colour;\n"
		"out vec3 out_Pos;\n"
		"\n"
		"void main()\n"
		"{\n"
		"	out_Colour = in_Colour;"
		"	out_Pos = in_Pos;"
		"	gl_Position = u_ViewProjection * u_Transform * vec4(in_Pos, 1.0);\n"
		"}\n";

	//Create fragment shader source
	const GLchar* FragSRC =
		"#version 330 core\n"
		"\n"
		"layout(location = 0) out vec4 Colour;\n"
		"\n"
		"in vec4 out_Colour;\n"
		"in vec3 out_Pos;\n"
		"\n"
		"uniform vec4 in_Colour;\n"
		"\n"
		"void main()\n"
		"{\n"
		"	Colour = out_Colour;\n"
		"}\n";

	Renderer::Init();
	
	std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>();
	std::shared_ptr<ShaderSystem> ShaderSys = std::make_shared<ShaderSystem>(VertSRC, FragSRC);
	ShaderSys->CreateProgram();
	ShaderSys->Bind();
	ShaderSys->SetUniform4f("in_Colour", 0.75f, 0.5f, 0.5f, 1.0f);
	mesh->Unbind();
	ShaderSys->Unbind();
	mesh->CleanUp();

	//Main run handler
	while (!glfwWindowShouldClose(window))
	{
		Renderer::SetClearColour(.5f, .05f, .5f, 1.0f); //Set the clear colour to purple
		Renderer::Clear();
		
		Renderer::Submit(mesh, ShaderSys);

		glfwSwapBuffers(window); //Swap the window buffers after clearing has occured
		glfwPollEvents();
	}

	Renderer::Shutdown();
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}