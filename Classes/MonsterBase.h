#pragma once
#include "cocos2d.h"
#include "Common.h"
#include "stateMachine.h"
USING_NS_CC;
class MonsterBase :public Sprite
{
public:
	typedef enum 
	{
		NORMAL = 0,
		ATTACK,
		DEAD,
		WALK,
		NONE,
		BEATTACK
	}STATE;

	typedef enum 
	{
		LEFT = 0,
		RIGHT
	}FACE;
	FACE face;
	STATE state;
	virtual bool init(String name);
	CCTMXTiledMap * getMap()
	{
		return (CCTMXTiledMap *)getParent();
	}

	bool canMove(float dt);
	void update(float dt);
	virtual void changeState(float dt)=0;
	void initMember(char * name);
	 CC_SYNTHESIZE(String, _monsterName, monsterName);
	 CC_SYNTHESIZE(int, _hp, Hp);
	 CC_SYNTHESIZE(int, _attack, Attack);
	 CC_SYNTHESIZE(float, _walkDistance, WalkDistance);
	 CC_SYNTHESIZE(int, _speed, Speed);
	 static MonsterBase * create(String name);

	 void runAnimate(char * filename, int count)
	 {
		 Animate * animate = Common::createAnimate(filename, count);
		 this->runAction(animate);
	 }
	 RepeatForever * animatewalk;
	 RepeatForever * animateNormal;
	 CCAnimate * animateHit;
	 CCAnimate * animateDie;
};