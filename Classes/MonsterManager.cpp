#include "MonsterManager.h"
#include "monster.h"
MonsterManager * MonsterManager::monsterManager = NULL;
void MonsterManager::addMonster()
{
	TMXObjectGroup * objectGroup;
	objectGroup = map->objectGroupNamed("monster");
	
	if (objectGroup != NULL)
	{
		ValueVector arrGroup = objectGroup->getObjects();
		int n = arrGroup.size();
		for (int k = 0; k < n; ++k)
		{
			ValueMap objInfo = arrGroup.at(k).asValueMap();
			String name = objInfo.at("name").asString();
			float x = objInfo.at("x").asFloat();
			float y = objInfo.at("y").asFloat();
			Monster *monster = Monster::create(name);
			monsters.pushBack(monster);
			monster->setPosition(ccp(x, y));
			monster->setWalkDistance(monster->getPositionX());
			monster->setAnchorPoint(Vec2(0, 0));
			map->addChild(monster, 127);
		}
	}

}

