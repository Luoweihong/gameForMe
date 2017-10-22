#include "cocos2d.h"
#include "mapUI.h"
#include "JoyStick.h"
#include "config.h"

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
	
  	void changeScene(String name);


	static MapUI* getMap()
	{
		return mapUI;
	}
	static SceneMgr * getSceneMgr()
	{
		if (sceneMgr != NULL)
		{
			return sceneMgr;
		}
		sceneMgr = new SceneMgr();
		return sceneMgr;
	}

private:
	SceneMgr()
	{

	}
	static SceneMgr * sceneMgr;
};