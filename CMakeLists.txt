cmake_minimum_required(VERSION 3.19)
project(OpenGL_Vulkan)

include_directories(
	src
	Dependencies/glm
	Dependencies/stb_image
	Dependencies/stb_vorbis
	Dependencies/GLFW/include
	Dependencies/glew-2.2.0/include
	Dependencies/Vulkan/1.2.198.1/include
	Dependencies/assimp/include
)

link_directories(
	${CMAKE_SOURCE_DIR}/Dependencies/GLFW/lib
	${CMAKE_SOURCE_DIR}/Dependencies/glew-2.2.0/lib/Release/x64
	${CMAKE_SOURCE_DIR}/Dependencies/Vulkan/1.2.198.1/lib
	${CMAKE_SOURCE_DIR}/Dependencies/assimp/lib/release
)

#add_library(
#	glfw3 SHARED IMPORTED
#	glew32 SHARED IMPORTED
#	vulkan-1 SHARED IMPORTED
#	assimp-vc143-mt SHARED IMPORTED
#)

#set_property(
#	TARGET glfw3 PROPERTY IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/Dependencies/GLFW/lib
#	TARGET glew32 PROPERTY IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/Dependencies/glew-2.2.0/bin/Release/x64
#	TARGET vulkan-1 PROPERTY IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/Dependencies/Vulkan/1.2.198.1/bin
#	TARGET assimp-vc143-mt PROPERTY IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/Dependencies/assimp/DLL/Release
#)

#set_property(
#	TARGET glfw3 PROPERTY IMPORTED_IMPLIB ${CMAKE_SOURCE_DIR}/Dependencies/GLFW/lib
#	TARGET glew32 PROPERTY IMPORTED_IMPLIB ${CMAKE_SOURCE_DIR}/Dependencies/glew-2.2.0/lib/Release/x64
#	TARGET vulkan-1 PROPERTY IMPORTED_IMPLIB ${CMAKE_SOURCE_DIR}/Dependencies/Vulkan/1.2.198.1/lib
#	TARGET assimp-vc143-mt PROPERTY IMPORTED_IMPLIB ${CMAKE_SOURCE_DIR}/Dependencies/assimp/lib/Release
#)

#Add main executable
add_executable(OpenGL_Vulkan
	OpenGL/Resource.h
	OpenGL/ResourceLoader.h
	OpenGL/ResourceLoader.cpp
	OpenGL/BufferLayout.h
	OpenGL/Context.h
	OpenGL/Context.cpp
	OpenGL/OpenGLContext.h
	OpenGL/OpenGLContext.cpp
	OpenGL/VulkanContext.h
	OpenGL/VulkanContext.cpp
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

target_link_libraries(OpenGL_Vulkan glfw3 glew32 opengl32 vulkan-1 assimp-vc143-mt)

target_compile_features(OpenGL_Vulkan PUBLIC cxx_std_17)