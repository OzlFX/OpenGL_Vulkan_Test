#include <iostream>
#include <GL/glew.h>
#include <vulkan/vulkan.h>
#include <SDL/SDL.h>
#include <memory>

#include "Renderer.h"
#include "Mesh.h"
#include "ShaderSystem.h"

int main(int argc, char *argv[])
{
	bool running = true;

	//Initialise SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		throw std::exception();

	//Create a new SDL window for OpenGL
	SDL_Window* window = SDL_CreateWindow("OpenGL", 
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 840, 640, 
		SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

	//Create SDL context
	if (!SDL_GL_CreateContext(window))
		throw std::exception();

	//Initialise GLEW
	if (glewInit() != GLEW_OK)
		throw std::exception();

	std::cout << glGetString(GL_VERSION) << std::endl;

	const GLfloat pos[] = {
		.0f, .5f, .0f,
		-.5f, -.5f, .0f,
		.5f, -.5f, .0f
	};

	GLuint indices[] = { 0, 1, 2 };

	//Create vertex shader source
	const GLchar* VertSRC =
		"#version 330 core\n"
		"\n"
		"layout(location = 0) in vec3 in_Pos;\n"
		"\n"
		"out vec3 out_Pos;\n"
		"\n"
		"void main()\n"
		"{\n"
		"	out_Pos = in_Pos;"
		"	gl_Position = vec4(in_Pos, 1.0);\n"
		"}\n";

	//Create fragment shader source
	const GLchar* FragSRC =
		"#version 330 core\n"
		"\n"
		"layout(location = 0) out vec4 color;\n"
		"\n"
		"in vec3 out_Pos;\n"
		"\n"
		"uniform vec4 in_Colour;\n"
		"\n"
		"void main()\n"
		"{\n"
		"	color = in_Colour;\n"
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

	//std::shared_ptr<VertexBuffer> Buffer = std::make_shared<VertexBuffer>(pos, sizeof(pos));
	//std::shared_ptr<IndexBuffer> IB = std::make_shared<IndexBuffer>(indices, sizeof(indices) / sizeof(GLuint));
	//std::shared_ptr<VertexArray> VAO = std::make_shared<VertexArray>();
	//VAO->AddBuffer(Buffer);
	//VAO->SetIndexBuffer(IB);

	///Pass the 'mesh' (vao) to the render system with the shader, draw the object
	/* VERTEXBUFFER */
	/*
	GLuint VBO_ID = 0; //Set the Vertex Buffer Object ID

	//Create a new VBO using the VBO id
	glGenBuffers(1, &VBO_ID);

	//Check if the VBO was created successfully
	if (!VBO_ID)
		throw std::exception();

	//Bind the VBO data
	glBindBuffer(GL_ARRAY_BUFFER, VBO_ID);

	//Upload a copy of the data from memory to VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(pos), pos, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0); //Reset the state
	*/
	/* VERTEX ARRAY */
	/*GLuint VAO_ID = 0; //Set the Vertex Array Objecy ID

	//Create a new VAO on the GPU using the VAO id
	glGenVertexArrays(1, &VAO_ID);

	//check if the VAO was created successfully
	if (!VAO_ID)
		throw std::exception();

	//Bind the newly created VAO on the GPU
	glBindVertexArray(VAO_ID);

	//Bind the newly created VBO to the GPU
	//glBindBuffer(GL_ARRAY_BUFFER, VBO_ID);

	//Assign the VBO to the first index and flag it for use
	//Stride is 12 (3 * 4)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);

	//Unbind our VBO and VAO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	std::shared_ptr<ShaderSystem> ShaderSys = std::make_shared<ShaderSystem>(VertSRC, FragSRC);
	ShaderSys->CreateProgram();
	ShaderSys->Bind();
	ShaderSys->SetUniform4f("in_Colour", 0.75f, 0.5f, 0.5f, 1.0f);
	ShaderSys->Unbind();*/
	/*
	//Create a new vertex shader
	GLuint VertShaderID = glCreateShader(GL_VERTEX_SHADER);
	
	//Attach shader source code
	glShaderSource(VertShaderID, 1, &VertSRC, NULL);

	//Compile the shader
	glCompileShader(VertShaderID);

	//Check if the shader creation is successful
	GLint success = 0;
	glGetShaderiv(VertShaderID, GL_COMPILE_STATUS, &success); //Get the vertex ID and check its compile status
	
	if (!success)
	{
		std::cout << "Vertex Shader Failed to compile" << std::endl;
	}

	//Create a new fragment shader
	GLuint FragShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	//Attach shader source code
	glShaderSource(FragShaderID, 1, &FragSRC, NULL);

	//Compile the shader
	glCompileShader(FragShaderID);

	//Check if the shader creation is successful
	glGetShaderiv(FragShaderID, GL_COMPILE_STATUS, &success); //Get the vertex ID and check its compile status

	if (!success)
	{
		std::cout << "Fragment Shader Failed to compile" << std::endl;
	}

	//Create new shader program
	GLuint programID = glCreateProgram();

	//Attach shaders to the shader program
	glAttachShader(programID, VertShaderID);
	glAttachShader(programID, FragShaderID);

	//Bind the VAO positions to the first slot during link
	//glBindAttribLocation(programID, 0, "in_Pos");

	//Link the program to the GPU
	glLinkProgram(programID);

	//Check if link was successful
	glGetProgramiv(programID, GL_LINK_STATUS, &success);

	if (!success)
		throw std::exception();

	//Detach and destroy shaders from the program
	glDetachShader(programID, VertShaderID);
	glDeleteShader(VertShaderID);
	glDetachShader(programID, FragShaderID);
	glDeleteShader(FragShaderID);
	*/

	//Main run handler
	while (running)
	{
		SDL_Event event = { 0 };

		//SDL Event handler
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				running = false;
			}
		}

		Renderer::SetClearColour(.5f, .05f, .5f, 1.0f); //Set the clear colour to purple
		Renderer::Clear();
		//glClearColor(.5f, .05f, .5f, 1.0f);
		//glClear(GL_COLOR_BUFFER_BIT);
		
		//Allow OpenGL to use our shader program & VAO
		//ShaderSys->Bind();
		//glBindVertexArray(VAO_ID);
		//VAO->Bind();
		//Draw
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		//glDrawElements(GL_TRIANGLES, VAO->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, indices);
		//Reset the state
		//glBindVertexArray(0);
		//VAO->Unbind();
		//ShaderSys->Unbind();
		
		Renderer::Submit(mesh, ShaderSys);

		SDL_GL_SwapWindow(window); //Swap the window buffers after clearing has occured
	}

	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}