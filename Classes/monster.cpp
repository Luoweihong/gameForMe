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
	setSpeed(100);
	scheduleUpdate();
	animateNormal = nullptr;
	animatewalk = nullptr;
	state = NORMAL;
	face = LEFT;
	
	
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
	if (state==MonsterBase::STATE::WALK)
	{
		if (animatewalk == nullptr)
		{
			Animate *animatewalk = Common::createAnimate("./monster/yuduwalk.plist", "yuduwalk", 8);
			this->animatewalk = animatewalk;
			runAction(animatewalk);

		}
		
		if (face == FACE::LEFT)
		{
			CCLOG("faceLEft%d",face);
			setFlippedX(true);
			if (this->getWalkDistance() - this->getPositionX() > 300)
			{
				
				face = FACE::RIGHT;
				changeState(dt);
				return;
			}
			setPositionX(this->getPositionX() - dt*getSpeed());
		}
		else
		{
			CCLOG("faceRight%d", face);
			setFlippedX(false);
			if (this->getPositionX()-this->getWalkDistance() > 200)
			{

				face = FACE::LEFT;
				changeState(dt);
				return;
			}
			setPositionX(this->getPositionX() + dt*getSpeed());

		}
	}
	else if (state == MonsterBase::STATE::NORMAL)
	{
		if (animateNormal == nullptr)
		{
			CCLOG("noraml");
			Animate *animateNormal = Common::createAnimate("./monster/yudu.plist", 14);
			this->animateNormal = animateNormal;
			runAction(animateNormal);
			scheduleOnce(schedule_selector(Monster::changeState, this), 2);
		}
		

	}
}



void Monster::changeState(float dt)
{
	
	if (this->state ==NORMAL )
	{
		CCLOG("change state");
		stopAllActions();
		this->state = WALK;
		animateNormal = nullptr;
		CCLOG("%p", animateNormal);

	}
	else
	{
		stopAllActions();
		this->state = NORMAL;
		animatewalk = nullptr;
		
	}
}

