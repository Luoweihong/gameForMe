#include "cocos2d.h"
#include "stateMachine.h"
#include "Common.h"
#include "MonsterBase.h"
USING_NS_CC;

class Monster : public MonsterBase
{
public:
	bool init(String name);
	static Monster * create(String name);
	void update(float dt);
	void changeState(float dt);
	Animate *animatewalk;
	Animate *animateNormal;


};