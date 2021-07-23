#ifndef _CONTEXT_H_
#define _CONTEXT_H_

#include <memory>

class Context
{
public:

	virtual ~Context() = default;

	virtual void Init() = 0;
	virtual void SwapBuffers() = 0;

	static std::unique_ptr<Context> Create(void* _Window);

};

#endif
