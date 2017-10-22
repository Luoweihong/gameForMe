#include "cocos2d.h"
#include "tinyxml2/tinyxml2.h"
class ReadLua
{
public:
	char ** readTable(char *);

	void setFilename(char * name);

	int readLine(char * filename, char *name);
	int getRow()
	{
		return row;
	}
private:
	char * filename;
	int row;
};


