#ifndef _BUFFERLAYOUT_H_
#define _BUFFERLAYOUT_H_

//Includes
#include <vector>

//Defines
#define GL_FLOAT 0x1406
#define GL_UNSIGNED_INT 0x1405
#define GL_UNSIGNED_BYTE 0x1401

#define GL_FALSE 0
#define GL_TRUE 1

struct BufferElement
{
	unsigned int m_Type;
	unsigned int m_Count;
	unsigned char m_Normalised;

	static unsigned int GetSizeOfType(unsigned int _Type)
	{
		switch (_Type)
		{
			case GL_FLOAT:			return 4;
			case GL_UNSIGNED_INT:	return 4;
			case GL_UNSIGNED_BYTE:	return 1;
		}

		return 0;
	}
};

class BufferLayout
{
public:

	BufferLayout() : m_Stride(0)
	{

	}

	template<typename T>
	void Push(unsigned int _Count)
	{
		static_assert(false);
	}

	template<>
	void Push<float>(unsigned int _Count)
	{
		m_Elements.push_back({ GL_FLOAT, _Count, GL_FALSE });
		m_Stride += _Count * BufferElement::GetSizeOfType(GL_FLOAT);
	}
	
	template<>
	void Push<unsigned int>(unsigned int _Count)
	{
		m_Elements.push_back({ GL_UNSIGNED_INT, _Count, GL_FALSE });
		m_Stride += _Count * BufferElement::GetSizeOfType(GL_UNSIGNED_INT);
	}
	
	template<>
	void Push<unsigned char>(unsigned int _Count)
	{
		m_Elements.push_back({ GL_UNSIGNED_BYTE, _Count, GL_TRUE });
		m_Stride += _Count * BufferElement::GetSizeOfType(GL_UNSIGNED_BYTE);
	}

	inline const std::vector<BufferElement>& GetElements() const { return m_Elements; }
	inline unsigned int GetStride() const { return m_Stride; }

private:

	std::vector<BufferElement> m_Elements;
	unsigned int m_Stride;
};

#endif
