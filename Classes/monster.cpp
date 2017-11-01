#include "monster.h"
#include "config.h"
#include "Common.h"
#include "Hero.h"
#include "FlyWord.h"
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
	animateHit = nullptr;
	state = MonsterBase::NORMAL;
	face = LEFT;
	Common::createAnimate("./monster/yudu.plist", 14);
	Common::createAnimate("./monster/yuduwalk", "yuduwalk", 8);
	Common::createAnimate("./monster/yuduhit","yuduhit",10,1);
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
	if (state==STATE::WALK)
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
			scheduleOnce(SEL_SCHEDULE(&Monster::changeState), 2);
		}
	}
	else if (state == MonsterBase::ATTACK)
	{
		CCTMXTiledMap  * map=getMap();
		Hero * hero=(Hero *)map->getChildByName("hero");
		
		float heroX = hero->getPositionX();
		float monsterX = this->getPositionX();
		int abs = fabs(monsterX - heroX);
		if (monsterX-heroX>=0.0000001)
		{
		
			if (face!= FACE::LEFT)
			{
				face = FACE::LEFT;
				
			}
			setFlippedX(true);
		} 
		else
		{
	
			if (face != FACE::RIGHT)
			{
				face = FACE::RIGHT;
				
			}
			setFlippedX(false);
		}




		if (abs<=100)
		{

			if (animateHit == nullptr)
			{
				stopAllActions();
				animatewalk = nullptr;
				animateNormal = nullptr;
				CCAnimate *hit = CCAnimate::create((CCAnimationCache::sharedAnimationCache()->animationByName("yuduhit")));
				animateHit = (RepeatForever  *)hit;
				
				
				
				CCCallFunc * callback = CCCallFunc::create([this](){
					animateHit = nullptr;
					animatewalk == nullptr;
					this->scheduleUpdate();
				});
				DelayTime * delay = DelayTime::create(0.1f);
				Sequence * squence = Sequence::create(animateHit,delay ,callback, NULL);
				unscheduleUpdate();
				runAction(squence);
			}
			
		} 
		else
		{
			if (animatewalk == nullptr)
			{
				stopAllActions();
				animateHit = nullptr;
				animateNormal = nullptr;
				RepeatForever *animatewalk = CCRepeatForever::create(CCAnimate::create(CCAnimationCache::sharedAnimationCache()->animationByName("yuduwalk")));
				this->animatewalk = animatewalk;
				runAction(animatewalk);
			}


			//����Ӣ��
			if (monsterX-heroX>0)
			{
				setPositionX(this->getPositionX()-dt*getSpeed());
			} 
			else
			{
				setPositionX(this->getPositionX()+dt*getSpeed());
			}

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

void Monster::getDownHP(int num)
{
	
	FlyWord * flyword = FlyWord::create("-10", 20, Vec2(this->getContentSize().width / 3, this->getContentSize().height));
	addChild(flyword, 127);


}

