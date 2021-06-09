#ifndef _BUFFERLAYOUT_H_
#define _BUFFERLAYOUT_H_

//Includes
#include <vector>
#include <string>

//Defines
#define GL_FLOAT 0x1406
#define GL_UNSIGNED_INT 0x1405
#define GL_UNSIGNED_BYTE 0x1401

#define GL_FALSE 0
#define GL_TRUE 1

struct BufferElement
{
	std::string m_Name;
	unsigned int m_Type;
	unsigned int m_Count;
	size_t m_Offset;
	unsigned char m_Normalised;

	BufferElement() = default;

	BufferElement(unsigned int _Type, const std::string& _Name, bool _Normalised = false)
		: m_Name(_Name), m_Type(_Type), m_Count(GetSizeOfType(_Type)), m_Offset(0), m_Normalised(_Normalised)
	{
	}

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

	BufferLayout() {}

	BufferLayout(std::initializer_list<BufferElement> _Elements)
		: m_Elements(_Elements)
	{
		CalculateOffsetAndStride();
	}

	const std::vector<BufferElement>& GetElements() const { return m_Elements; }
	uint32_t GetStride() const { return m_Stride; }

	std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
	std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
	std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
	std::vector<BufferElement>::const_iterator end() const { return m_Elements.begin(); }

private:

	void CalculateOffsetAndStride()
	{
		size_t offset = 0;
		m_Stride = 0;

		for (auto& element : m_Elements)
		{
			element.m_Offset = offset;
			offset += element.GetSizeOfType(element.m_Type);
			m_Stride += element.GetSizeOfType(element.m_Type);
		}
	}

	std::vector<BufferElement> m_Elements;
	unsigned int m_Stride = 0;
};

#endif
