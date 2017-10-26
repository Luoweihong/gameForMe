#include "cocos2d.h"
#include "Common.h"
USING_NS_CC;
class MonsterBase :public Sprite
{
public:
	typedef enum state
	{
		NORMAL = 0,
		ATTACK,
		DEAD,
		WALK
	}STATE;
	STATE state;
	virtual bool init(String name);

	bool canMove(float dt);
	bool canMoveLeft(float dt); 

	void initMember(char * name);
	 CC_SYNTHESIZE(String, _monsterName, monsterName);
	 CC_SYNTHESIZE(int, _hp, Hp);
	 CC_SYNTHESIZE(int, _attack, Attack);
	 CC_SYNTHESIZE(float, _walkDistance, WalkDistance);
	 CC_SYNTHESIZE(int, _speed, Speed);
	 static MonsterBase * create(String name);

	 void MonsterBase::runAnimate(char * filename, int count)
	 {
		 Animate * animate = Common::createAnimate(filename, count);
		 this->runAction(animate);
	 }

};