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

//Classifies the Data Type for usage
enum class DataType
{
	None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
};

//Gets the size of the data based on the elements used
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

//Handles the elements of the object, keeping track of the vertex position ect.
struct BufferElement
{
	std::string m_Name;
	DataType m_Type;
	uint32_t m_Size;
	size_t m_Offset;
	unsigned char m_Normalised;

	BufferElement() = default;

	//Initialise the Buffer Element data
	BufferElement(DataType _Type, const std::string& _Name, bool _Normalised = false)
		: m_Name(_Name), m_Type(_Type), m_Size(GetSizeOfType(_Type)), m_Offset(0), m_Normalised(_Normalised)
	{
	}

	//Gets the Component Count of the object based on the buffer element's DataType
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

//Contains the Layout of the object for rendering
class BufferLayout
{
public:

	BufferLayout() {}

	//Initialise the Buffer Layout using an initializer_list to create it on the fly rather than using an object
	BufferLayout(std::initializer_list<BufferElement> _Elements)
		: m_Elements(_Elements)
	{
		CalculateOffsetAndStride();
	}

	const std::vector<BufferElement>& GetElements() const { return m_Elements; } //Get the stored BufferElements
	uint32_t GetStride() const { return m_Stride; } //Get the object stride

	/* BufferLayout vector iterator functions for cleaner code by reducing the length of the code when accessed elsewhere */
	std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); } //Get the beginning iterator of the BufferElement vector
	std::vector<BufferElement>::iterator end() { return m_Elements.end(); } //Get the ending iterator of the BufferElement vector
	std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); } //Get the beginning const iterator of the BufferElement vector
	std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); } //Get the ending const iterator of the BufferElement vector

private:

	/* Sets the offset and stride of the object's Buffer Layout to the size of each element within the element
	   vector. This allows for the program to read each vertex correctly, for example, three floats on a line 
	   would be one vertex. */
	//Calculates the offset and stride of the object
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
