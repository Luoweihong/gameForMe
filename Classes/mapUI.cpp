#include "mapUI.h"
#include "Hero.h"
#include "JoyStick.h"
#include "Common.h"
#include "monster.h"
#include "MonsterManager.h"
#include "FlyWord.h"
#include "NPC.h"
bool MapUI::init(String name)
{
	CCLOG("MAPUI");
	if (!Layer::init())
	{
		return false;
	}
	tmx = CCTMXTiledMap::create(name.getCString());
	this->addChild(tmx, 1, 10);
	CCLOG("%f,%f", tmx->getContentSize().width, tmx->getContentSize().height);

	hero = Hero::create();
	MonsterManager *monsterManager=MonsterManager::getMonsterManager();
	monsterManager->setMap(tmx);
	monsterManager->addMonster();
	
	initNpc("NPC");
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
	//读取TMX文件


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
			tmx->addChild(hero,127,name);
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
	node->setVisible(false);


}

void MapUI::initNpc(String name)
{
	//TMX 拿到 obj
	TMXObjectGroup * objectGroup;
	objectGroup = tmx->objectGroupNamed(name.getCString());

	if (objectGroup != NULL)
	{
		ValueVector arrGroup = objectGroup->getObjects();
		int n = arrGroup.size();
		for (int k = 0; k < n; ++k)
		{
			ValueMap objInfo = arrGroup.at(k).asValueMap();
			float x = objInfo.at("x").asFloat();
			float y = objInfo.at("y").asFloat();
			NPC  * npc = NPC::create("sunshangxiang");
			npc->setPosition(ccp(x, y));
			CCLOG("x:%f y: %f\n", x, y);
			tmx->addChild(npc, 127, name.getCString());
		}
	}
}


