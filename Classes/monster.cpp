#include "monster.h"
#include "config.h"
#include "Common.h"
bool Monster::init(String name)
{
	if (!Sprite::init())
	{
		return false;
	}
	setmonsterName(name);
	initMember((char *)getmonsterName().getCString());
	return true;
}

Monster * Monster::create(String name)
{
	Monster * monster = new Monster;
	
	if (!monster->init(name))
	{
		return NULL;
	}
	monster->autorelease();
	return monster;
}

void Monster::runAnimate(char * filename,int count)
{
	Animate * animate =Common::createAnimate(filename, count);

	this->runAction(animate);

}

void Monster::initMember(char * name)
{
	DataManager* dataManager= DataManager::getDataManager();
	ValueMap vm = dataManager->readDataFromJson("Role.json",name);
	setmonsterName(vm[name].asString());
	setHp(vm["Hp"].asInt());
	setAttack(vm["Attack"].asInt());
}

