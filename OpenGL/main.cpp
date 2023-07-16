#include <iostream>
#include <memory>

#include "Renderer.h"
#include "Window.h"
#include "Mesh.h"
#include "ShaderSystem.h"

#include "ResourceLoader.h"

typedef float GLfloat;

int main()//int argc, char *argv[])
{
	bool running = true;

	const GLfloat pos[] =
	{
		 -0.5f, -0.5f, 0.0f, 0.18f, 0.6f, 0.96f, 1.0f,
		 -1.5f, -0.5f, 0.0f, 0.18f, 0.6f, 0.96f, 1.0f,
		 -1.5f,  0.5f, 0.0f, 0.18f, 0.6f, 0.96f, 1.0f,
		 -0.5f,  0.5f, 0.0f, 0.18f, 0.6f, 0.96f, 1.0f,

		  0.5f, -0.5f, 0.0f, 0.6f, 0.87f, 0.02f, 1.0f,
		  1.5f, -0.5f, 0.0f, 0.6f, 0.87f, 0.02f, 1.0f,
		  1.5f,  0.5f, 0.0f, 0.6f, 0.87f, 0.02f, 1.0f,
		  0.5f,  0.5f, 0.0f, 0.6f, 0.87f, 0.02f, 1.0f
	};

	GLuint indices[] =
	{
		0, 1, 2, 2, 3, 0,
		4, 5, 6, 6, 7, 4
	};

	//Load the shaders from file
	std::string BasicVert = ResourceLoader::Load("../Resources/Shaders/BasicVertexShader.vert");
	std::string BasicFrag = ResourceLoader::Load("../Resources/Shaders/BasicFragmentShader.frag");

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

	std::unique_ptr<Window> window = Window::Create(840, 640, "OpenGL/Vulkan"); //Create the window
	Renderer::Init(); //Initialise the renderer
	
	std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>(pos, sizeof(pos), indices, sizeof(indices)); //Create a mesh
	std::shared_ptr<ShaderSystem> ShaderSys = std::make_shared<ShaderSystem>((const GLchar*)BasicVert.c_str(), (const GLchar*)BasicFrag.c_str()); //Setup the shader system and parse in the shader files
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