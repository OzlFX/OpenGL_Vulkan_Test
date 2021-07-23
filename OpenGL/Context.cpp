#include "Context.h"
#include "OpenGLContext.h"

std::unique_ptr<Context> Context::Create(void* _Window)
{
    return std::make_unique<OpenGLContext>(static_cast<GLFWwindow*>(_Window));
}
