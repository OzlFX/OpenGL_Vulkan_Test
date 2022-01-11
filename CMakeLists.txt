cmake_minimum_required(VERSION 3.19)
project(OpenGL_Vulkan)

include_directories(
	src
	Dependencies/glm
	Dependencies/imgui
	Dependencies/stb_image
	Dependencies/stb_vorbis
	Dependencies/GLFW/include
	Dependencies/glew-2.2.0/include
)

link_directories(
	${CMAKE_SOURCE_DIR}/Dependencies/GLFW/lib
	${CMAKE_SOURCE_DIR}/Dependencies/glew-2.2.0/lib/Release/x64
	${CMAKE_SOURCE_DIR}/Dependencies/Vulkan/lib
)

#Add main executable
add_executable(OpenGL_Vulkan
	OpenGL/BufferLayout.h
	OpenGL/Context.h
	OpenGL/Context.cpp
	OpenGL/OpenGLContext.h
	OpenGL/OpenGLContext.cpp
	OpenGL/EntryPoint.h
	OpenGL/IndexBuffer.h
	OpenGL/IndexBuffer.cpp
	OpenGL/Mesh.h
	OpenGL/Mesh.cpp
	OpenGL/Renderer.h
	OpenGL/Renderer.cpp
	OpenGL/RendererAPI.h
	OpenGL/RendererAPI.cpp
	OpenGL/OpenGLRendererAPI.h
	OpenGL/OpenGLRendererAPI.cpp
	OpenGL/VulkanRendererAPI.h
	OpenGL/VulkanRendererAPI.cpp
	OpenGL/Resource.h
	OpenGL/ShaderSystem.h
	OpenGL/ShaderSystem.cpp
	OpenGL/Texture.h
	OpenGL/Texture.cpp
	OpenGL/VertexArray.h
	OpenGL/VertexArray.cpp
	OpenGL/VertexBuffer.h
	OpenGL/VertexBuffer.cpp
	OpenGL/Window.h
	OpenGL/Window.cpp
	OpenGL/main.cpp
)

target_link_libraries(OpenGL_Vulkan glfw3 glew32 vulkan-1)