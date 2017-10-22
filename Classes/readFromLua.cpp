#include "readFromLua.h"
USING_NS_CC;


char ** ReadLua::readTable(char *)
{

}

int ReadLua::readLine(char * filename, char *name)
{
	std::string pathKey = CCFileUtils::sharedFileUtils()->fullPathForFilename("1.lua");
	unsigned char* pBuffer = NULL;
	unsigned long bufferSize = 0;
	pBuffer = CCFileUtils::sharedFileUtils()->getFileData(pathKey.c_str(), "r", (ssize_t *)&bufferSize);

	std::string s = (char*)pBuffer;
	std::string inFile = s.substr(0, bufferSize);

	size_t size = inFile.size();
	std::string::size_type pos;
	for (size_t i = 0; i < size; i++)
	{
		pos = inFile.find("\n", i);
		if (pos < size)
		{
			std::string s = inFile.substr(i, pos - i - 1);
			/*此处s即获取到的单行信息*/
			if (strcmp(s.c_str(),name))
			{
				pos = inFile.find("\n", i);
				

			}

			i = pos;
		}
	}
}
