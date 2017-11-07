#include "NPC.h"
#include "Common.h"
bool NPC::init(String name)
{
	setNpcName(name);
	bindEntity();
	setListener();
	return true;
}

void NPC::bindEntity()
{
	SpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(getNpcName().getCString());
	
	char  displayFrame[100];

	sprintf(displayFrame, "%s %s", getNpcName().getCString(), "(1).png");

	initWithFile(displayFrame);
	runAction(Common::createAnimate(getNpcName().getCString(), getNpcName().getCString(),8));
	

	setAnchorPoint(Vec2(0, 0));
}

void NPC::setListener()
{
	EventListenerTouchOneByOne * evListener = EventListenerTouchOneByOne::create();


	evListener->onTouchBegan = [&](Touch * pt,Event* event){
		//返回NPC 的地址 让 主角去 寻找
		Vec2 PtInMap = getParent()->convertToNodeSpace(pt->getLocation());

		if (this->boundingBox().containsPoint(PtInMap))
		{
			NotificationCenter::getInstance()->postNotification("click npc", this);

		}

		
		return true;
	};
	evListener->onTouchEnded = [&](Touch * pt, Event *event){

	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(evListener,this);


}

NPC * NPC::create(String name)
{
	NPC * npc = new NPC;

	if (!npc->init(name))
	{
		return nullptr;
	}
	npc->autorelease();

	return npc;
}
