#include "UIMgr.h"
#include "SceneMgr.h"

UIMgr* UIMgr::_uiMgr = nullptr;

Node* UIMgr::getCsb(String name)
{
	Node * node = CSLoader::createNode(name.getCString());
	Layout * layout=(Layout *)node->getChildByName("NPC_TALK");
	SceneMgr::mapUI->addChild(node,128);

	
	Node * SpriteImg=(Node *)layout->getChildByName("Node");

	ImageView * image=(ImageView *)SpriteImg->getChildByName("Npc_Image");
	TextureCache::sharedTextureCache()->addImage("NpcImage.png");

	image->loadTexture("NpcImage.png", TextureResType::LOCAL);
	image->setScale(1);



	EventListenerTouchOneByOne * evListener = EventListenerTouchOneByOne::create();

	evListener->onTouchBegan = [&,node](Touch * pt,Event * event){
		CCLOG("touch");
		node->setVisible(false);
		node->removeFromParent();
		return true;
	};

	node->getEventDispatcher()->addEventListenerWithSceneGraphPriority(evListener, node); 
	return node;
}

UIMgr * UIMgr::getUIMgr()
{
	if (_uiMgr == nullptr)
	{
		_uiMgr = new UIMgr;
	}
	return _uiMgr;
}

