#ifndef _VULKANCONTEXT_H_
#define _VULKANCONTEXT_H_

#include "Context.h"

struct GLFWwindow;

class VulkanContext : public Context
{
public:

	VulkanContext(GLFWwindow* _Window);

	virtual void Init() override;
	virtual void SwapBuffers() override;

private:

	GLFWwindow* m_WindowHandle;

};

#endif
