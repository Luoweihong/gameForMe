#include "SceneMgr.h"

MapUI* SceneMgr::mapUI = NULL;
SceneMgr* SceneMgr::sceneMgr = NULL;
void SceneMgr::changeScene(String name)
{
	//创建TMX
	//拿到地图层
	//初始化数据

	mapUI->removeAllChildren();
	mapUI->init(name.getCString());
	JoyStick * joystick = JoyStick::create();
	mapUI->addChild(joystick, 128);
}

