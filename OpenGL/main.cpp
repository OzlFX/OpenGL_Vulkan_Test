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

	//Load the shaders from file
	std::string BasicVert = Resource::Load("../Resources/Shaders/BasicVertexShader.vert");
	std::string BasicFrag = Resource::Load("../Resources/Shaders/BasicFragmentShader.frag");

	std::unique_ptr<Window> window = Window::Create(840, 640, "OpenGL/Vulkan"); //Create the window
	Renderer::Init(); //Initialise the renderer
	
	std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>(); //Create a mesh
	std::shared_ptr<ShaderSystem> ShaderSys = std::make_shared<ShaderSystem>(BasicVert.c_str(), BasicFrag.c_str()); //Setup the shader system and parse in the shader files
	ShaderSys->CreateProgram(); //Create the shader program
	ShaderSys->Bind(); //Bind the shader for use
	//ShaderSys->SetUniform4f("in_Colour", 0.75f, 0.5f, 0.5f, 1.0f);
	//Unbinds
	mesh->Unbind();
	ShaderSys->Unbind();
	mesh->CleanUp();

	//Main run handler
	while (!window->CloseEvent())
	{
		Renderer::SetClearColour(.5f, .05f, .5f, 1.0f); //Set the clear colour to purple
		Renderer::Clear(); //Clear the renderer
		
		Renderer::Submit(mesh, ShaderSys); //Submit the mesh and shader to be used
		window->OnUpdate(); //Update the window
	}

	//Shutdowns
	Renderer::Shutdown();
	window->Shutdown();

	return 0;
}