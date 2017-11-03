#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/Cocostudio.h"
class Hero;
USING_NS_CC;
using namespace ui;

class MapUI :public Layer
{
public:
	bool init(String name);
	CCTMXTiledMap* tmx;
	static MapUI* create(String name);
	void initHero(Sprite *,char *);
	void initJoyStick();
	void initScreen();
	Hero * hero;
	Hero * getHero()
	{
		return hero;
	}
};
