#include "json/rapidjson.h"
#include "json/document.h"
#include "cocos2d.h"
USING_NS_CC;

class  DataManager
{
public:
	ValueMap readDataFromJson(char *filename,char* ObjectName);
	

	static DataManager * getDataManager();
private:
	static DataManager * dataManager;
	DataManager()
	{

	}
};