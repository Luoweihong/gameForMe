#include "cocos2d.h"
#include "stateMachine.h"
USING_NS_CC;

class Monster : public Sprite
{
public:
	typedef enum state
	{
		NORMAL = 0,
		ATTACK,
		DEAD
	};
	bool init(String name);
	static Monster * create(String name);
	void runAnimate(char * filename,int count);
	void initMember(char * name);
	CC_SYNTHESIZE(String, _monsterName, monsterName);
	CC_SYNTHESIZE(int, _hp, Hp);
	CC_SYNTHESIZE(int, _attack, Attack);
	StateMachine * state;

};