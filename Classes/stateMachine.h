#pragma  once
#include "cocos2d.h"
USING_NS_CC;
class StateMachine
{
public:
	typedef enum face
	{
		LEFT = 0,
		RIGHT
	}FACE;
	void init()
	{
		 face = FACE::LEFT;
	}
	FACE getState()
	{
		return  face;
	}
	void ChangeState(FACE faceto)
	{
		if (face!=faceto)
		{
			face = faceto;
		}
	}

	FACE face;
};