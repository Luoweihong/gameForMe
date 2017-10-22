#pragma once
#include "cocos2d.h"
#include "JoyStick.h"
USING_NS_CC;


class Hero :public Sprite
{
public:
	typedef enum face
	{
		LEFT=0,
		RIGHT
		
	}FACE;
	
	bool init();
	void run();
	void update(float dt);
	void updataStatus();
	void move(float dt);
	bool canMoveUp(float dt);
	void moveUp(float dt);
	bool canMoveDown(float);
	void moveDown(float);
	bool canMoveLeft(float);
	bool canMoveRight(float);
	void moveRight(float);
	void moveLeft(float);
	CCTMXTiledMap * getMap()
	{
		return (CCTMXTiledMap*)getParent();
	}
	static Hero * create();
	CC_SYNTHESIZE(int, speed, Speed);
	CC_SYNTHESIZE(int, _speedUp, SpeedUp);
	CC_SYNTHESIZE(int, _speedDown, SpeedDown);
	CC_SYNTHESIZE(int, _speedAcc, SpeedAcc);



};
