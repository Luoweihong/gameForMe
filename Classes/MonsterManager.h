#include "cocos2d.h"
USING_NS_CC;
class MonsterManager 
{
public:
	CCTMXTiledMap * map;
	
	void setMap(CCTMXTiledMap *map)
	{
		this->map = map;
	}

	Vector<Sprite *> monsters;
	void addMonster();
	static MonsterManager * getMonsterManager()
	{
		if (monsterManager!=NULL)
		{
			return monsterManager;
		}
		monsterManager = new MonsterManager;

	}
protected:
private:
	MonsterManager(){

	}
	static MonsterManager* monsterManager;
};