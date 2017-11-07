#include "cocos2d.h"
USING_NS_CC;

class Entity : public Node
{
public:
	virtual void bindEntity();

	bool init();

	CC_SYNTHESIZE(int, goodsId, getgoodsId);



};