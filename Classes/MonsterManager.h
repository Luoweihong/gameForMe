#pragma once
#include "cocos2d.h"
#include "MonsterBase.h"
USING_NS_CC;
class MonsterManager 
{
public:
	CCTMXTiledMap * map;
	
	void setMap(CCTMXTiledMap *map)
	{
		this->map = map;
	}

	
	void addMonster();
	static MonsterManager * getMonsterManager()
	{
		if (monsterManager!=NULL)
		{
			return monsterManager;
		}
		monsterManager = new MonsterManager;

	}
	std::vector<MonsterBase *> monsters;
protected:
private:
	MonsterManager(){

	}
	static MonsterManager* monsterManager;
};