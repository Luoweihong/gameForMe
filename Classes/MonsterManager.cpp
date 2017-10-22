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
			float x = objInfo.at("x").asFloat();
			float y = objInfo.at("y").asFloat();
			String name = objInfo.at("type").asString();
			Monster *monster=Monster::create("monster");
			monster->initWithFile("./monster/yudu1.png");
			monster->runAnimate("./monster/yudu.plist", 14);
			monsters.pushBack(monster);
			monster->setPosition(ccp(x, y));
			monster->setAnchorPoint(Vec2(0, 0));
			map->addChild(monster, 127);
		}
	}

}

