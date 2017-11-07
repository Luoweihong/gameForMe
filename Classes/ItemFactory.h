#include "cocos2d.h"
#include "EntityBase.h"
USING_NS_CC;


class ItemFactory
{
public:
	virtual Entity* createItem()=0 ;


};