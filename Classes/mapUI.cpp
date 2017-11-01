#include "mapUI.h"
#include "Hero.h"
#include "JoyStick.h"
#include "Common.h"
#include "monster.h"
#include "MonsterManager.h"
bool MapUI::init(String name)
{
	if (!Layer::init())
	{
		return false;
	}
	tmx = CCTMXTiledMap::create(name.getCString());
	this->addChild(tmx, 1, 10);
	hero = Hero::create();
	MonsterManager *monsterManager=MonsterManager::getMonsterManager();
	monsterManager->setMap(tmx);
	monsterManager->addMonster();
	initHero(hero,"hero");
	setTouchEnabled(true);
	initScreen();
	return true;
}

MapUI* MapUI::create(String name)
{
	MapUI *mapUI = new MapUI;
	if (!mapUI->init(name))
	{
		return NULL;
	}
	mapUI->autorelease();

	return mapUI;
}

void MapUI::initHero(Sprite * hero,char * name)
{
	//¶ÁÈ¡TMXÎÄ¼þ


	TMXObjectGroup * objectGroup;
	objectGroup = tmx->objectGroupNamed(name);
	
	if (objectGroup!=NULL)
	{
		ValueVector arrGroup = objectGroup->getObjects();
		int n = arrGroup.size();
		for (int k = 0; k < n;++k)
		{
			ValueMap objInfo = arrGroup.at(k).asValueMap();
			float x = objInfo.at("x").asFloat();
			float y = objInfo.at("y").asFloat();
			hero->setPosition(ccp(x, y));
			CCLOG("x:%f y: %f\n", x, y);
			tmx->addChild(hero,50,name);
		}
	}
}



void MapUI::initJoyStick()
{

}



void MapUI::initScreen()
{
	Node *node = CSLoader::createNode("MainScene.csb");

	addChild(node,255);
}


