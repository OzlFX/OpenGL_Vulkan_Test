#include "ResourceLoader.h"

std::string Load(const std::string& _File)
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