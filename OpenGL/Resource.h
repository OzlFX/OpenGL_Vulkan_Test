#ifndef _RESOURCE_H_
#define _RESOURCE_H_

#include <fstream>
#include <iostream>
#include <unordered_map>
#include <string>

class Resource
{
public:

	static const std::string Load(const std::string& _File)
	{
		std::ifstream file(_File.c_str());
		std::string OutputFile;

		//Check to see if the file is open
		if (!file.is_open())
		{
			std::cout << "Error: " << _File << " not found!\n";
		}

		//Copy contents of the file into the string
		while (!file.eof())
		{
			std::string line;
			std::getline(file, line);
			OutputFile += line + "\n";
		}

		return OutputFile;
	}

private:

	///Caching files may need to be done in the object that calls the loading
	int GetResourceLocation(const std::string& _File)
	{
		if (m_ResourceCache.find(_File) != m_ResourceCache.end())
			return m_ResourceCache[_File];
		///Not finished whilst planning takes place
		int location = 0;
		if (location == -1)
			std::cout << "ERROR: something went wrong with the file: " << _File << "!\n";

		m_ResourceCache[_File] = location;

		return location;
	}

	std::unordered_map<std::string, int> m_ResourceCache;

};

#endif
