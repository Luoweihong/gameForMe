#include "cocos2d.h"
#include "EntityBase.h"
USING_NS_CC;
class NPC :public Sprite
{
public:
	bool init(String name);
	
	 void bindEntity();
	 void setListener();


	 static NPC * create(String name);
	 CC_SYNTHESIZE(String, NpcName, NpcName);

};
