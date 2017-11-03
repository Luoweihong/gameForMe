#pragma once
#include "cocos2d.h"
#include "mapUI.h"
#include "JoyStick.h"
#include "config.h"

class SceneMgr
{
public:
	static MapUI* mapUI;
	
	Scene* createScene();
	
  	void changeScene(String name);
	Scene * scene;

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