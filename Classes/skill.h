#include "cocos2d.h"
USING_NS_CC;

//����������
class Skill
{
public:
	Node * Receiver;

	CC_SYNTHESIZE(int, _skillCD, Skill_cd);
	CC_SYNTHESIZE(int, _skillID, Skill_id);
	Skill();

};