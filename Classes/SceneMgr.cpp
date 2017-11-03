#include "SceneMgr.h"
#include "MonsterManager.h"
MapUI* SceneMgr::mapUI = NULL;
SceneMgr* SceneMgr::sceneMgr = NULL;
void SceneMgr::changeScene(String name)
{
	
	scene->removeAllChildren();

	while (MonsterManager::getMonsterManager()->monsters.size() != 0)
	{
		MonsterManager::getMonsterManager()->monsters.popBack();
	}
	
	mapUI = MapUI::create(name.getCString());
	JoyStick * joystick = JoyStick::create();
	mapUI->addChild(joystick, 128);
	scene->addChild(mapUI);
}

 Scene* SceneMgr::createScene()
{
	 CCLOG("SCENEMANAGER..................");
	scene = Scene::create();
	mapUI = MapUI::create("sg.tmx");
	scene->addChild(mapUI);
	JoyStick* joystick = JoyStick::create();
	mapUI->addChild(joystick, 128);
	return scene;
}
