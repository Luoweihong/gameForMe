#pragma once
#include "MonsterBase.h"
#include "cocos2d.h"
#include "stateMachine.h"
#include "Common.h"
USING_NS_CC;
class Monster : public MonsterBase
{
public:
	bool init(String name);
	static Monster * create(String name);
	void update(float dt);
	void changeState(float dt);
	RepeatForever * animatewalk;
	RepeatForever * animateNormal;
	CCAnimate * animateHit;
	CCAnimate * animateDie;
	void getDownHP(int num);
	CCTMXTiledMap * getMap()
	{
		return (CCTMXTiledMap *) getParent();
	}

};