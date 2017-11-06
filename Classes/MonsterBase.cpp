#pragma once
#include "MonsterBase.h"
#include "config.h"
#include "Hero.h"
#include "MonsterManager.h"


//bool MonsterBase::init(String name)
//{
//	if (!Sprite::init())
//	{
//		return false;
//	}
//	state = NORMAL;
//	setmonsterName(name);
//	initMember((char *)getmonsterName().getCString());
//	return true;
//}

void MonsterBase::update(float dt)
{

	if (!canMove(dt))
	{
		if (face == FACE::LEFT)
		{
			face = RIGHT;
		}
		else
		{
			face = LEFT;
		}
	}
	if (state == STATE::WALK)
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
			if (this->getPositionX() - this->getWalkDistance() > 200)
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
			//CCLOG("noraml");
			RepeatForever *animateNormal = CCRepeatForever::create(CCAnimate::create(CCAnimationCache::sharedAnimationCache()->animationByName("yudu")));

			this->animateNormal = animateNormal;
			runAction(animateNormal);
			
			scheduleOnce(SEL_SCHEDULE(&MonsterBase::changeState), 2);
		}
	}
	else if (state == MonsterBase::ATTACK)
	{
		CCTMXTiledMap  * map = getMap();
		Hero * hero = (Hero *)map->getChildByName("hero");

		float heroX = hero->getPositionX();
		float monsterX = this->getPositionX();
		int abs = fabs(monsterX - heroX);

		if (monsterX - heroX >= 0.0000001)
		{

			if (face != FACE::LEFT)
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




		if (abs <= 100)
		{
			if (animateHit == nullptr)
			{
				stopAllActions();
				CCAnimate *hit = CCAnimate::create((CCAnimationCache::sharedAnimationCache()->animationByName("yuduhit")));
				animateHit = (Animate *)hit;



				CCCallFunc * callback = CCCallFunc::create([this](){
					animateHit = nullptr;
					animatewalk = nullptr;
					animateNormal = nullptr;
					scheduleUpdate();

				});
				DelayTime * delay = DelayTime::create(0.1f);
				Sequence * squence = Sequence::create(animateHit, delay, callback, NULL);
				runAction(squence);
				unscheduleUpdate();
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


			//¸úËæÓ¢ÐÛ
			if (monsterX - heroX > 0)
			{
				setPositionX(this->getPositionX() - dt*getSpeed());
			}
			else
			{
				setPositionX(this->getPositionX() + dt*getSpeed());
			}

		}

	}
	else if (state == MonsterBase::DEAD)
	{
		if (animateDie == nullptr)
		{
			stopAllActions();
			Animate  *animateDie = CCAnimate::create(CCAnimationCache::sharedAnimationCache()->animationByName("yududie"));
			this->animateDie = animateDie;
			CCCallFunc *callfun = CCCallFunc::create([&, this](){
				state = NONE;
				animateDie = nullptr;
				animateHit = nullptr;
				animateNormal = nullptr;
				removeFromParentAndCleanup(true);
				MonsterManager::getMonsterManager()->monsters.eraseObject(this);
				//CCLOG("%d", MonsterManager::getMonsterManager()->getMonsters().size());
				scheduleUpdate();
			});
			Sequence * sequence = Sequence::create(animateDie, callfun, NULL);
			runAction(sequence);
			unscheduleUpdate();
		}
	}
}




void MonsterBase::initMember(char * name)
{
	DataManager* dataManager = DataManager::getDataManager();
	ValueMap vm = dataManager->readDataFromJson("monster.json", name);
	setmonsterName(vm[name].asString());	
	setHp(vm["Hp"].asInt());
	setAttack(vm["Attack"].asInt());

}

bool MonsterBase::init(String name)
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
	animateDie = nullptr;
	state = MonsterBase::NORMAL;
	face = LEFT;



	Common::createAnimate("yudu.plist", 14);
	Common::createAnimate("yuduwalk", "yuduwalk", 8);
	Common::createAnimate("yuduhit", "yuduhit", 15, 1);
	Common::createAnimate("yududie", "yududie", 6, 1);
	
	return true;
}



bool MonsterBase::canMove(float dt)
{

	CCTMXTiledMap * map = getMap();
	if (map == NULL)
	{
		return false;
	}
	CCRect RcMonster = boundingBox();

	CCPoint pt[3];
	pt[0] = ccp(RcMonster.getMidX(), RcMonster.getMinY());
	pt[1] = ccp(RcMonster.getMidX(), RcMonster.getMinY());
	pt[2] = ccp(RcMonster.getMidX(), RcMonster.getMinY());

	if (pt[0].y >= map->getContentSize().height)
		return true;	
	for (int i = 0; i < 3; i++)
	{
		CCPoint ptTile = Common::Point2Tile2(map, pt[i]);
		static const char* layerName[2] = { "land", "land2" };
		for (int j = 0; j < sizeof(layerName) / 4; ++j)
		{
			CCTMXLayer* layer = map->layerNamed(layerName[j]);
			if (layer == NULL)
			{
				continue;
			}
			int gid = layer->tileGIDAt(ptTile);
			if (gid != 0)
			{
		
				return true;
			}
		}
	}
	return false;

}
