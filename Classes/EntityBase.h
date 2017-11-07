#include "cocos2d.h"
USING_NS_CC;

class Entity : public Node
{
public:
	virtual void bindEntity();

	bool init();

	CC_SYNTHESIZE(int, goodsId, goodsId);
	CC_SYNTHESIZE(int, goodsType, goodsType);
	CC_SYNTHESIZE(String, goodName, goodsName);
	CC_SYNTHESIZE(String, goodsIcon, goodsIcon);

	void displaywithFile();


};