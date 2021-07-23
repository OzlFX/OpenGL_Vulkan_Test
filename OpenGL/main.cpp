#include <iostream>
#include <memory>

#include "Renderer.h"
#include "Window.h"
#include "Mesh.h"
#include "ShaderSystem.h"

int main()//int argc, char *argv[])
{
	bool running = true;
	
	 //Set the renderer api


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

	
	std::unique_ptr<Window> window = Window::Create(840, 640, "OpenGL/Vulkan");
	Renderer::Init();
	
	std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>();
	std::shared_ptr<ShaderSystem> ShaderSys = std::make_shared<ShaderSystem>(VertSRC, FragSRC);
	ShaderSys->CreateProgram();
	ShaderSys->Bind();
	//ShaderSys->SetUniform4f("in_Colour", 0.75f, 0.5f, 0.5f, 1.0f);
	mesh->Unbind();
	ShaderSys->Unbind();
	mesh->CleanUp();

	//Main run handler
	while (!window->CloseEvent())
	{
		Renderer::SetClearColour(.5f, .05f, .5f, 1.0f); //Set the clear colour to purple
		Renderer::Clear();
		
		Renderer::Submit(mesh, ShaderSys);
		window->OnUpdate();
	}

	Renderer::Shutdown();
	window->Shutdown();

	return 0;
}