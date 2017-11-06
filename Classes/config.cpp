#include "config.h"

DataManager * DataManager::dataManager = NULL;

ValueMap DataManager::readDataFromJson(char * filename,char * ObjectName)
{
	rapidjson::Document doc;
	if (!FileUtils::getInstance()->isFileExist(filename))
	{
		CCLOG("json file is not find [%s]", filename);
		
	}
	std::string data = FileUtils::getInstance()->getStringFromFile(filename);
	doc.Parse<rapidjson::kParseDefaultFlags>(data.c_str());

	if (doc.HasParseError() || !doc.IsArray())
	{
		log("get json data err!");
	}
	for (unsigned int i = 0; i < doc.Size();i++)
	{
		rapidjson::Value &v = doc[i];
		
		if (v.HasMember("MonsterName"))
		{
			
			String name = v["MonsterName"].GetString();
			if (!strcmp(name.getCString(),ObjectName))
			{
				ValueMap vm;
				vm["MonsterName"] = Value(v["MonsterName"].GetString());
				vm["Hp"] = Value(v["Hp"].GetInt());
				vm["Attack"] = Value(v["Attack"].GetInt());
				vm["speed"] = Value(v["speed"].GetInt());
				vm["type"] = Value(v["type"].GetInt());
				vm["Resource"] = Value(v["Resource"].GetString());
				return vm;

			}
		
		}


	}

}

