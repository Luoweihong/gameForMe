#include "cocos2d.h"

USING_NS_CC;

class FlyWord:public Node
{
public:
	static FlyWord* create(const char * word,int fontSize,Vec2 begin);


	bool init(const char * word, const int fontsize, Vec2 begin);
	void Flying();

	void Flyend();
protected:
private:

	int _fontSize;//字体大小
	CCPoint _begin;//要添加到的怪物的中心点
	CCLabelBMFont* m_plabel;//字体类型

};