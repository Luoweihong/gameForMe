#include "SceneMgr.h"

MapUI* SceneMgr::mapUI = NULL;
SceneMgr* SceneMgr::sceneMgr = NULL;
void SceneMgr::changeScene(String name)
{
	//¥¥Ω®TMX
	//ƒ√µΩµÿÕº≤„
	//≥ı ºªØ ˝æ›

	mapUI->removeAllChildren();
	//mapUI->init(name.getCString());
	JoyStick * joystick = JoyStick::create();
	mapUI->addChild(joystick, 128);
}

 Scene* SceneMgr::createScene()
{
	 CCLOG("SCENEMANAGER..................");
	Scene * s = Scene::create();
	mapUI = MapUI::create("sg.tmx");
	s->addChild(mapUI);
	JoyStick* joystick = JoyStick::create();
	mapUI->addChild(joystick, 128);
    return s;
}
