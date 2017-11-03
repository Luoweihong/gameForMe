#include "json/rapidjson.h"
#include "json/document.h"
#include "cocos2d.h"
USING_NS_CC;

class  DataManager
{
public:
	ValueMap readDataFromJson(char *filename,char* ObjectName);
	

	static DataManager * getDataManager()
	{
		if (dataManager!=NULL)
		{
			return dataManager;
		}
		dataManager = new DataManager;
		return dataManager;
	}
private:
	DataManager()
	{

	}

	static DataManager * dataManager;
};