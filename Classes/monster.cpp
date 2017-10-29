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
	Common::createAnimate("./monster/yudu.plist", 14);
	Common::createAnimate("./monster/yuduwalk", "yuduwalk", 8);
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
			RepeatForever  *animatewalk = CCRepeatForever::create(CCAnimate::create(CCAnimationCache::sharedAnimationCache()->animationByName("yuduwalk")));
			this->animatewalk = animatewalk;
			runAction(animatewalk);

		}
		
		if (face == FACE::LEFT)
		{
			
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
			RepeatForever *animateNormal =CCRepeatForever::create(CCAnimate::create(CCAnimationCache::sharedAnimationCache()->animationByName("yudu")));

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
		
		stopAllActions();
		this->state = WALK;
		animateNormal = nullptr;
	}
	else
	{
		stopAllActions();
		this->state = NORMAL;
		animatewalk = nullptr;
	}
}

