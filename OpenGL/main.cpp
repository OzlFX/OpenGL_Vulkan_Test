#include <iostream>
#include <memory>

#include "Renderer.h"
#include "Window.h"
#include "Mesh.h"
#include "ShaderSystem.h"

#include "Resource.h"

int main()//int argc, char *argv[])
{
	bool running = true;
	
	 //Set the renderer api

	std::string BasicVert = Resource::Load("../Resources/Shaders/BasicVertexShader.vert");
	std::string BasicFrag = Resource::Load("../Resources/Shaders/BasicFragmentShader.frag");

	std::unique_ptr<Window> window = Window::Create(840, 640, "OpenGL/Vulkan");
	Renderer::Init();
	
	std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>();
	std::shared_ptr<ShaderSystem> ShaderSys = std::make_shared<ShaderSystem>(BasicVert.c_str(), BasicFrag.c_str());
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