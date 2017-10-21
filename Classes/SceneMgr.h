#include "cocos2d.h"
#include "mapUI.h"
#include "JoyStick.h"

class SceneMgr
{
public:
	static MapUI* mapUI;
	
	Scene* createScene()
	{
		Scene * s = Scene::create();
		mapUI = MapUI::create("sg.tmx");
		s->addChild(mapUI);
		JoyStick* joystick = JoyStick::create();
		mapUI->addChild(joystick,128);
		return s;
	}
	

	static MapUI* getMap()
	{
		return mapUI;
	}


};