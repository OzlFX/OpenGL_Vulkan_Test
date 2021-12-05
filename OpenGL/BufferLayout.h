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

enum class DataType
{
	None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
};

static uint32_t GetSizeOfType(DataType _Type)
{
	switch (_Type)
	{
		case DataType::Float:		return 4;
		case DataType::Float2:		return 4 * 2;
		case DataType::Float3:		return 4 * 3;
		case DataType::Float4:		return 4 * 4;
		case DataType::Mat3:		return 4 * 3 * 3;
		case DataType::Mat4:		return 4 * 4 * 4;
		case DataType::Int:			return 4;
		case DataType::Int2:		return 4 * 2;
		case DataType::Int3:		return 4 * 3;
		case DataType::Int4:		return 4 * 4;
		case DataType::Bool:		return 1;
	}

	return 0;
}

struct BufferElement
{
	std::string m_Name;
	DataType m_Type;
	uint32_t m_Size;
	size_t m_Offset;
	unsigned char m_Normalised;

	BufferElement() = default;

	BufferElement(DataType _Type, const std::string& _Name, bool _Normalised = false)
		: m_Name(_Name), m_Type(_Type), m_Size(GetSizeOfType(_Type)), m_Offset(0), m_Normalised(_Normalised)
	{
	}

	uint32_t GetComponentCount() const
	{
		switch (m_Type)
		{
			case DataType::Float:		return 1;
			case DataType::Float2:		return 2;
			case DataType::Float3:		return 3;
			case DataType::Float4:		return 4;
			case DataType::Mat3:		return 3;
			case DataType::Mat4:		return 4;
			case DataType::Int:			return 1;
			case DataType::Int2:		return 2;
			case DataType::Int3:		return 3;
			case DataType::Int4:		return 4;
			case DataType::Bool:		return 1;
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
	std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }

private:

	void CalculateOffsetAndStride()
	{
		size_t offset = 0;
		m_Stride = 0;

		for (auto& element : m_Elements)
		{
			element.m_Offset = offset;
			offset += element.m_Size;
			m_Stride += element.m_Size;
		}
	}

	std::vector<BufferElement> m_Elements;
	uint32_t m_Stride = 0;
};

#endif
