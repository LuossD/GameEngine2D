#include "IOManager.h"
#include <fstream>
#include <iostream>

namespace Bengine
{
	bool IOManager::readFileToBuf(const std::string& filePath, std::vector<unsigned char>& buf)
	{
		std::ifstream file(filePath, std::ios::binary);
		if (file.fail())
		{
			perror(filePath.c_str());
			return false;
		}
		//Seek to the end.
		file.seekg(0, std::ios::end);

		//Get the file size.
		int fileSize = file.tellg();
		file.seekg(0, std::ios::beg);
		//Reduce the file size by any header bytes that might be present.Better safe than sorry
		fileSize -= file.tellg();
		buf.resize(fileSize);
		file.read((char*)&(buf[0]), fileSize);
		file.close();

		return true;
	}
}