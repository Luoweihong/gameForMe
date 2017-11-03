#include "MonsterManager.h"
#include "monster.h"
MonsterManager * MonsterManager::monsterManager = NULL;

void MonsterManager::setMap(MapUI *map)
{
    this->map = map;
}


void MonsterManager::addMonster()
{
    CCTMXTiledMap*	 map = (CCTMXTiledMap *)this->map->getChildByTag(10);
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
            monster->initWithSpriteFrame(SpriteFrameCache::sharedSpriteFrameCache()->getSpriteFrameByName("yudu1.png"));
            monster->retain();
            map->addChild(monster, 127);
			//monsters.pushBack(monster);
			monster->setPosition(ccp(x, y));
			monster->setWalkDistance(monster->getPositionX());
			monster->setAnchorPoint(Vec2(0, 0));
            if (map ==nullptr) {
                return;
            }
            
			
            
		}
	}

}

