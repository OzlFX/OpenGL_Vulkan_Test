#ifndef _OPENGLCONTEXT_H_
#define _OPENGLCONTEXT_H_

#include "Context.h"

struct GLFWwindow;

class OpenGLContext : public Context
{
public:

	OpenGLContext(GLFWwindow* _Window);

	virtual void Init() override;
	virtual void SwapBuffers() override;

private:

	GLFWwindow* m_WindowHandle;

};

#endif
