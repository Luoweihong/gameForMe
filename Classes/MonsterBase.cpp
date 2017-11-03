#pragma once
#include "MonsterBase.h"
#include "config.h"
MonsterBase * MonsterBase::create(String name)
{
	MonsterBase * monster = new MonsterBase;

	if (!monster->init(name))
	{
		return NULL;
	}
	monster->autorelease();
	
	return monster;
}

bool MonsterBase::init(String name)
{
	if (!Sprite::init())
	{
		return false;
	}
	state = NORMAL;
	setmonsterName(name);
	initMember((char *)getmonsterName().getCString());
	return true;
}


void MonsterBase::initMember(char * name)
{
	DataManager* dataManager = DataManager::getDataManager();
	ValueMap vm = dataManager->readDataFromJson("Role.json", name);
	setmonsterName(vm[name].asString());
	setHp(vm["Hp"].asInt());
	setAttack(vm["Attack"].asInt());
}
bool MonsterBase::canMove(float dt)
{
	return true;
}

bool MonsterBase::canMoveLeft(float dt)
{

	return true;

}
