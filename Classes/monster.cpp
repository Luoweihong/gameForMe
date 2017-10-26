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
	setWalkDistance(this->getPositionX());
	setSpeed(50);
	scheduleUpdate();
	
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

void Monster::update(float dt)
{
	

	if (state!=WALK)
	{
		state = WALK;
		stopAllActions();
		Animate *animate = Common::createAnimate("./monster/yuduwalk.plist", "yuduwalk", 8);
		setFlippedX(-1);
		runAction(animate);
	}
	if (this->getWalkDistance()-this->getPositionX()>300)
	{
		
		return;
	}
	setPositionX(this->getPositionX()-dt*getSpeed());


}


