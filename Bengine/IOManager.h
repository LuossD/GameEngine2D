#pragma once
#include <vector>
#include <string>

namespace Bengine
{
	class IOManager
	{
	public:
		static bool readFileToBuf(const std::string& filePath, std::vector<unsigned char>& buf);

	};
}
