#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <string>

#include "Context.h"

struct GLFWwindow;

class Window
{
public:

	static std::unique_ptr<Window> Create(unsigned int _Width, unsigned int _Height, const std::string& _Title);

	Window(unsigned int _Width, unsigned int _Height, const std::string& _Title);

	bool IsVSync() const { return m_VSync; }

	void OnUpdate();

	void SetVSync(bool _Enabled);

	bool CloseEvent();

	void Shutdown();

private:

	std::unique_ptr<Context> m_Context;

	GLFWwindow* m_Window;
	bool m_VSync = false;
};

#endif
