#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "Resource.h"

#define STB_IMAGE_IMPLEMENTATION

class Texture
{
public:

	Texture(std::string& _File);

	void Bind(unsigned int _Slot = 0) const; //Bind a texture to a slot
	void Unbind() const;

	~Texture();

private:

	unsigned int m_ID;
	std::string& m_FilePath;
	unsigned char* m_Buffer;
	int m_Width, m_Height, m_BPP;

};

#endif
